#ifndef _MARKER_H_
#define _MARKER_H_

/******************************************************************************
 Header file
 Class:        Marker, Flag, Line, Goal
 Date created: 06/09/2002
 Written by:   Dylan Mawhinney

 Markers are objects on the robocup field which don't move and
 can be used for navigation and localisation. The specific types of
 markers on the field are flags and lines. Lines don't have an XY position,
 only a distance and direction, flags and goals have an XY position on the
 field.
******************************************************************************/

#include <string>

class Marker 
{
   private:
      double distance;
      double direction;

      int timeSeen;        //The time at which the player saw the marker
      bool oldInfo;     //Are the details of this marker old?

      string markerCode; //The code for this marker eg "lt"

   public:
      Marker(string code);
      virtual ~Marker();

      virtual void setMarkerCode(string code);
      string getMarkerCode() const; 

      void setDistance(double dist);
      void setDirection(double dir);

      double getDistance() const;
      double getDirection() const;

      void setTimeSeen(int time);
      int getTimeSeen() const;
 
      void setOld(bool value);
      bool isOld() const;  

   protected:
};

class Flag : public Marker
{
   private:
      double xPos;
      double yPos;

   public:
      Flag(string code);
      ~Flag();
     
      void setXPos(double x);
      double getXPos() const;
  
      void setYPos(double y);
      double getYPos() const;
};

class Line : public Marker
{
   public:
      typedef enum {UNDEF, TOP_LINE, BOTTOM_LINE, LEFT_LINE, RIGHT_LINE,
                               CENTER_LINE} LineType;
   private:
      LineType sideType;

   public:
      Line(string code);
      ~Line();

      void setSide(LineType side);
      LineType getSide() const;
};

class Goal : public Marker
{
   public:
     typedef enum {UNDEF, LEFT_GOAL, RIGHT_GOAL} GoalType;

   private:
      GoalType sideType;

      double xPos;
      double yPos;

   public:
      Goal(string code);
      ~Goal();

      void setSide(GoalType side);
      GoalType getSide() const;

      void setXPos(double x);
      double getXPos() const;
 
      void setYPos(double y);
      double getYPos() const;
};

#endif
