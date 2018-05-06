#ifndef _SOCCERPLAYER_H_
#define _SOCCERPLAYER_H_

/******************************************************************************
 Header file
 Class:        SoccerPlayer
 Date created: 04/09/2002
 Written by:   Dylan Mawhinney

 SoccerPlayer is a class which represents a single player on the soccer
 simulator. A player has a genetic program associated with it which is
 executed to control the players actions. 
***************************************************************************/

#include <string>
#include <sys/time.h>

#include "GeneticProgram.h"
#include "ReturnAction.h"
#include "SoccerField.h"

#include "field.h"

class SoccerPlayer 
{
   private:
      //The genetic program for this player
      GeneticProgram *controlProgram; 

      //The player object for this SoccerPlayer
      Player *player;

      //The stadium this player plays on
      Stadium *std;

      //The name of the team this player is on
      string teamName;

      //The list of actions   
      ReturnAction actionList;

      //Timing variables
      struct timeval lastActionTime;

      int serverTime;

      //Players side left or right
      typedef enum{UNDEF, LEFT_SIDE, RIGHT_SIDE} SideType;
      SideType side;

      SoccerField *currentField;
      SoccerField *oldField;

      int uniformNumber;

      static char *playModeStrings[];
      int currentPlayMode;

   public:
      //Must provide stadium and team name for constructor
      SoccerPlayer(Stadium *stad, char *team);
      virtual ~SoccerPlayer();
     
      void connectToServer();
      void disconnectFromServer();

      void reset();

      void setProgram(GeneticProgram *prog);

      void sendAction();

      bool getMessages();
  
      void parseMessage(string &message);

      void play();

      void wait();

   protected:

};

#endif
