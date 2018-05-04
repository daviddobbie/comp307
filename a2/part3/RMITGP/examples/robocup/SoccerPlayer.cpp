/******************************************************************************
 Definition file
 Class:        SoccerPlayer
 Date created: 04/09/2002
 Written by:   Dylan Mawhinney

 See header file for details.
***************************************************************************/

using namespace std;

#define _REENTRANT
#include <pthread.h>

#include <cstdio>

#include "SoccerPlayer.h"
#include "Util.h"

//From rcssserver
#include "field.h"
#include "types.h"
#include "player.h"
#include "types.h"

//initialise static data
char *SoccerPlayer::playModeStrings[] = PLAYMODE_STRINGS;

SoccerPlayer::SoccerPlayer(Stadium *stad, char *team) :
                                            controlProgram(NULL),
                                            player(NULL),
                                            std(stad),
                                            teamName(team),
                                            side(UNDEF),
                                            uniformNumber(0)
{
}

SoccerPlayer::~SoccerPlayer()
{
}
     
void SoccerPlayer::connectToServer()
{
   string initString;


   //Create the initialisation string
   initString = "(init ";
   initString.append(teamName);
   initString.append(" (version 8.0))");

   player = std->newClient(0, 0, (char *)initString.c_str());   

   if (player == NULL)
   {
      throw string("SoccerPlayer::connectToServer error unable to connect");
   }
   getMessages(); //Clear any old messages left

   std->send_init_info(*player);
   write_log(*std, *player, initString.c_str(), RECV);
}

void SoccerPlayer::reset()
{
   player->parse_command("(move -20.0 -10.0)");
}

void SoccerPlayer::disconnectFromServer()
{
   player->disable(); 
   player->team->n--;
   player = NULL;
}

void SoccerPlayer::setProgram(GeneticProgram *prog)
{
   controlProgram = prog;
}


void SoccerPlayer::sendAction()
{
   string actionString;

   actionList.getNextAction(actionString);   
   write_log(*std, *player, actionString.c_str(), RECV); 
   player->parse_command(actionString.c_str());      
   gettimeofday(&lastActionTime, NULL); 
}

void SoccerPlayer::play()
{
   int i;
   bool newVisualInfo;
   for(i=0;i<100;)
   {
      newVisualInfo = false;
      //evaluate the program
      getMessages();
      controlProgram->evaluate(&actionList);

      while(!actionList.empty())
      {
         if (getMessages())
            break;

         sendAction();
         wait();
         i++;
      }
   }
}


bool SoccerPlayer::getMessages()
{
   bool newMessage=false;
   string message;

   while(!player->empty())
   {
      //Protect access to the message list via a mutex
      pthread_mutex_lock(&(player->playerMessageLock));
      player->getMessage(message);
      pthread_mutex_unlock(&(player->playerMessageLock));

      parseMessage(message);
   }

   return newMessage;
}

void SoccerPlayer::parseMessage(string &message)
{
   string token;
   string::iterator i;
   i = message.begin();

   int count;

   bool finished = false;

   token = getToken(message, i);

   if (token != "(")
      return;

   token = getToken(message, i);
  
   if (token == "see")
   {
      cout << "Got a see " << message << endl;

      token = getToken(message, i);
      if (sscanf(token.c_str(), "%d", &serverTime) != 1) 
         throw string ("SoccerPlayer::parseMessage error invalid time in see");

      delete oldField; 
      oldField = currentField;
      currentField = new SoccerField();

      currentField->parseMessage(message);

      cout << "Finished see" << endl;
   } 
   else if (token == "init")
   {
      cout << "Got an init message" << endl
           << message << endl;

      token = getToken(message, i);
      if (token == "l")
         side = LEFT_SIDE; 
      else if (token == "r")
         side = RIGHT_SIDE;
      else      
         throw string ("SoccerPlayer::parseMessage Error illegal side");

      token = getToken(message, i);
      if (sscanf(token.c_str(), "%d", &uniformNumber) != 1)
         throw string ("SoccerPlayer::parseMessage Error illegal unum");

      token = getToken(message, i);
      for (count=0; count<PM_MAX; count++)
      {
         if (token == playModeStrings[count])
         {
            currentPlayMode = count;
            break;
         }
      }

      token = getToken(message, i);
      if (token != ")")
         cerr << "Warning. No closing bracket in init message." << endl; 
   }
   else if (token == "hear")
   {
      cout << "Got a hear message" << endl
           << message << endl;
   }
   else 
   {
      cout << "Got a message" << endl
           << message << endl;
   }
}

const int WAIT = 100;

void SoccerPlayer::wait()
{
   struct timespec nextTime;
   pthread_cond_t waitCond;
   pthread_mutex_t waitMutex;
  
   pthread_mutex_init(&waitMutex, NULL); 
   pthread_mutex_lock(&waitMutex);

   nextTime.tv_sec = lastActionTime.tv_sec;
   nextTime.tv_nsec = (lastActionTime.tv_usec * (long)1000) + (WAIT * (long)1000000);

   while(nextTime.tv_nsec > 1000000000)
   {
      nextTime.tv_sec++;
      nextTime.tv_nsec -= 1000000000;
   }

   pthread_cond_timedwait(&waitCond, &waitMutex, &nextTime); 
}
