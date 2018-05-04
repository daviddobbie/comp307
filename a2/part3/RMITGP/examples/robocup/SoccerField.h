#ifndef _SOCCERFIELD_H_
#define _SOCCERFIELD_H_

/******************************************************************************
 Header file
 Class:        SoccerField 
 Date created: 02/10/2002
 Written by:   Dylan Mawhinney

 The SoccerField class contains all the objects which are present on the
 field, this includes goals, lines, flags, players, balls etc.
******************************************************************************/

#include <string>

#include "Marker.h"
#include "MovableObject.h"

#include <vector>

class SoccerField 
{
   public:
      typedef enum {UNDEF, LEFT_SIDE, RIGHT_SIDE} SideType;

   private:
      Goal leftGoal, rightGoal;
      vector<Flag *> flagList;
      vector<Line *> lineList;

      Ball theBall;
      vector<PlayerObject *> leftTeam;
      vector<PlayerObject *> rightTeam;

      vector<MovableObject *> movables;
      vector<Marker *> markers;

      int lastUpdateTime;

      string teamName;
      SideType sideType;

   public:
      SoccerField(string team, SideType side);
      virtual ~SoccerField();

      void parseMessage(string &message);

      void getBall(string &message, string::iterator &i);
      void getGoal(string &message, string::iterator &i);
      void getFlag(string &message, string::iterator &i);
      void getLine(string &message, string::iterator &i);
      void getPlayer(string &message, string::iterator &i);

      int getNumbers(string &message, string::iterator &i, string numbers[6]);

      void skip(string &message, string::iterator &i);

   protected:
};

#endif
