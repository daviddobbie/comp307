/******************************************************************************
 Definition file
 Class:        SoccerField 
 Date created: 02/10/2002
 Written by:   Dylan Mawhinney

 See header file for details.
******************************************************************************/

#include <cstdio>

#include <vector>
#include <iostream>

using namespace std;

#include "SoccerField.h"
#include "Util.h" //for getToken

SoccerField::SoccerField() : leftGoal("l"), rightGoal("r"), lastUpdateTime(-1)
{
   int i;

   lineList.push_back(new Line("l"));
   lineList.push_back(new Line("r"));
   lineList.push_back(new Line("t"));
   lineList.push_back(new Line("b"));

   for (i=1; i<=11; i++)
   {
      PlayerObject *newPlayer = new PlayerObject();
      newPlayer->setUniformNumber(i);
      newPlayer->setSide(PlayerObject::LEFT_SIDE);
      leftTeam.push_back(newPlayer);

      newPlayer = new PlayerObject();
      newPlayer->setUniformNumber(i);
      newPlayer->setSide(PlayerObject::RIGHT_SIDE);
      rightTeam.push_back(newPlayer);
   }

   vector<Line *>::iterator lineIter;
   vector<Flag *>::iterator flagIter;

   markers.push_back(&leftGoal);
   markers.push_back(&rightGoal);

   for (lineIter = lineList.begin(); lineIter != lineList.end(); lineIter++)
   {
      markers.push_back(*lineIter);
   }

   for (flagIter = flagList.begin(); flagIter!=flagList.end(); flagIter++)
   {
      markers.push_back(*flagIter);
   }

   vector<PlayerObject *>::iterator playIter;

   movables.push_back(&theBall);

   for (playIter = leftTeam.begin(); playIter!=leftTeam.end(); playIter++)
   {
      movables.push_back(*playIter);
   }

   for (playIter = rightTeam.begin(); playIter!=rightTeam.end(); playIter++)
   {
      movables.push_back(*playIter);
   }
}

SoccerField::~SoccerField()
{
   vector<Flag *>::iterator flagIter;
   vector<Line *>::iterator lineIter;
   vector<PlayerObject *>::iterator playIter;

   for (flagIter=flagList.begin(); flagIter!=flagList.end(); flagIter++)
      delete *flagIter;

   for (lineIter=lineList.begin(); lineIter!=lineList.end(); lineIter++)
      delete *lineIter;

   for (playIter=leftTeam.begin(); playIter!=leftTeam.end(); playIter++)
      delete *playIter;

   for (playIter=rightTeam.begin(); playIter!=rightTeam.end(); playIter++)
      delete *playIter;
}

void SoccerField::parseMessage(string &message)
{
   string token;
   string::iterator i = message.begin();

   bool finished = false;
   int count;

   token = getToken(message, i); 

   if (token != "(")
      return;

   token = getToken(message, i); 

   if (token != "see")
      return;

   token = getToken(message, i);

   if(sscanf(token.c_str(), "%d", &lastUpdateTime) != 1)
      return;

   while (!finished)
   {
      for (count = 0; count < 2; count++)
      {
         token = getToken(message, i);
         if (token != "(")
            throw string ("SoccerField::parseMessage parse error in see");
      }

      token = getToken(message, i);
      if (token == "b" || token == "B")
         getBall(message, i);
      else if (token == "g")
         getGoal(message, i);
      else if (token == "f")
         getFlag(message, i);
      else if (token == "l")
         getLine(message, i);
      else if (token == "p")
         getPlayer(message, i);
      else
         skip(message, i);

      if (lookAtToken(message, i) == ")")
         finished = true;
   }
}

void SoccerField::getBall(string &message, string::iterator &i)
{
   string token;
   string numberStrings[6];
   double values[6];
   int totalNumbers;
   int count;

   cout << "Got a ball ";

   theBall.setTimeSeen(lastUpdateTime);

   token = getToken(message, i);

   totalNumbers = getNumbers(message, i, numberStrings);

   for (count=0; count < totalNumbers; count++)
   {
      if (sscanf(numberStrings[count].c_str(), "%lf", &(values[count])) != 1)
         return;
   }
  
   if (totalNumbers == 4)
   {
      theBall.setDistance(values[0]); 
      theBall.setDirection(values[1]); 
      theBall.setChangeInDistance(values[2]); 
      theBall.setChangeInDirection(values[3]); 
   }
   else if (totalNumbers == 2)
   {
      theBall.setDistance(values[0]); 
      theBall.setDirection(values[1]); 
   }
   else if (totalNumbers == 1)
   {
      theBall.setDirection(values[0]);
   }
   else
   {
      cerr << "SoccerField::getBall: got a weird number of numbers " 
           << totalNumbers << endl;
   }
}

void SoccerField::getGoal(string &message, string::iterator &i)
{
   string token;
   string numberStrings[6];
   double values[6];
   int totalNumbers;
   int count;

   Goal *theGoal;

   cout << "Got a goal ";

   token = getToken(message, i);

   if (token == "l")
      theGoal = &leftGoal;
   else
      theGoal = &rightGoal;   

   theGoal->setTimeSeen(lastUpdateTime);

   token = getToken(message, i);

   totalNumbers = getNumbers(message, i, numberStrings);

   for (count=0; count < totalNumbers; count++)
   {
      if (sscanf(numberStrings[count].c_str(), "%lf", &(values[count])) != 1)
         return;
   }

   if (totalNumbers == 2)
   {
      theGoal->setDistance(values[0]);
      theGoal->setDirection(values[1]);
   }
   else if (totalNumbers == 1)
   {
      theGoal->setDirection(values[0]);
   }
   else
   {
      cerr << "SoccerField::getGoal: got a weird number of numbers "
           << totalNumbers << endl;
   }
}

void SoccerField::getFlag(string &message, string::iterator &i)
{
   Flag * newFlag;

   string token;
   string typeString;
   string numberStrings[6];
   double values[6];
   int totalNumbers;
   int count;

   do
   {
      token = getToken(message, i);
      if (token != ")")
         typeString.append(token);
   } while(token != ")");

   newFlag = new Flag(typeString);

   newFlag->setTimeSeen(lastUpdateTime);

   totalNumbers = getNumbers(message, i, numberStrings);

   for (count=0; count < totalNumbers; count++)
   {
      if (sscanf(numberStrings[count].c_str(), "%lf", &(values[count])) != 1)
         return;
   }

   if (totalNumbers == 2)
   {
      newFlag->setDistance(values[0]);
      newFlag->setDirection(values[1]);
   }
   else if (totalNumbers == 1)
   {
      newFlag->setDirection(values[0]);
   }
   else
   {
      cerr << "SoccerField::getFlag: got a weird number of numbers "
           << totalNumbers << endl;
   }

   flagList.push_back(newFlag);
}

void SoccerField::getLine(string &message, string::iterator &i)
{
   Line *newLine;

   string token;
   string numberStrings[6];
   double values[6];
   int totalNumbers;
   int count;

   token = getToken(message, i);

   newLine = new Line(token);

   token = getToken(message, i);

   newLine->setTimeSeen(lastUpdateTime);

   totalNumbers = getNumbers(message, i, numberStrings);

   for (count=0; count < totalNumbers; count++)
   {
      if (sscanf(numberStrings[count].c_str(), "%lf", &(values[count])) != 1)
         return;
   }

   if (totalNumbers == 2)
   {
      newLine->setDistance(values[0]);
      newLine->setDirection(values[1]);
   }
   else if (totalNumbers == 1)
   {
      newLine->setDirection(values[0]);
   }
   else
   {
      cerr << "SoccerField::getLine: got a weird number of numbers "
           << totalNumbers << endl;
   }

   lineList.push_back(newLine);
}

void SoccerField::getPlayer(string &message, string::iterator &i)
{
   PlayerObject *newPlayer;

   string token;
   string numberStrings[6];
   double values[6];
   int totalNumbers;
   int count;

   string team;
   string uniformNumber;
   string goalie;

   team= getToken(message, i);
  
   newPlayer = new PlayerObject();

   if (team!= ')')
   {
      if (team != teamName)
      {
         if (sideType == LEFT_SIDE)
            newPlayer->setSide(Player::RIGHT_SIDE); 
         else
            newPlayer->setSide(Player::LEFT_SIDE); 
      }
      else
      {
         if (sideType == LEFT_SIDE)
            newPlayer->setSide(Player::LEFT_SIDE); 
         else
            newPlayer->setSide(Player::RIGHT_SIDE); 
      }

      uniformNumber = getToken(message, i);
      if (uniformNumber != ')')
      {
         goalie = getToken(message, i);   
      }
   }


   do
   {
      token = getToken(message, i);
      if (token != ")")
         cout << token << " ";
   } while(token != ")");

   do
   {
      token = getToken(message, i);
      if (token != ")")
         cout << token << " ";
   } while(token != ")");

   cout << endl;
}

int SoccerField::getNumbers(string &message, string::iterator &i, 
                             string numbers[6])
{
   string token;
   int count=0;

   do
   {
      token = getToken(message, i);
      if (token != ")")
         numbers[count++] = token;
   } while(token != ")");

   return count;
}

void SoccerField::skip(string &message, string::iterator &i)
{
   string token;

   cout << "!!!Got a miscelaneous ";

   do
   {
      token = getToken(message, i);
      if (token != ")")
         cout << token << " ";
   } while(token != ")");

   do
   {
      token = getToken(message, i);
      if (token != ")")
         cout << token << " ";
   } while(token != ")");

   cout << endl;
}
