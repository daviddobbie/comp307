#ifndef _MOVABLEOBJECT_H_
#define _MOVABLEOBJECT_H_

/******************************************************************************
 Header file
 Class:        MovableObject, Ball, PlayerObject   
 Date created: 06/09/2002
 Written by:   Dylan Mawhinney

 MovableObject is a superclass for all objects which can be sensed by 
 a player on the soccer server field. This excludes lines, flags, and goals
 which are handled by the Marker class. 
******************************************************************************/

#include <string>

class MovableObject 
{
   private:
      double distance;
      double direction;

      double changeInDistance;
      double changeInDirection;

      double approxXPos;
      double approxYPos; 

      int timeSeen;
      bool oldInfo;

   public:
      MovableObject();
      virtual ~MovableObject();

      void setDistance(double dist);
      void setDirection(double dir);

      double getDistance() const;
      double getDirection() const;

      void setChangeInDistance(double dist);
      void setChangeInDirection(double dir);

      double getChangeInDistance() const;
      double getChangeInDirection() const;

      void setApproxXPos(double x);
      void setApproxYPos(double y);

      double getApproxXPos() const;
      double setApproxYPos() const;

      void setTimeSeen(int time);
      int getTimeSeen() const;
 
      void setOld(bool value);
      bool isOld() const;  

   protected:
};

class Ball : public MovableObject
{
   private:
   public:
   protected:
};

class PlayerObject : public MovableObject
{
   public:
      typedef enum {UNDEF, LEFT_SIDE, RIGHT_SIDE} SideType;

   private:
      int uniformNumber;
      SideType sideType;
      bool goalie; 

   public:
      PlayerObject();
      ~PlayerObject();

      void setUniformNumber(int num);
      int getUniformNumber() const;

      void setSide(SideType side);
      SideType getSide() const;

      void setGoalie(bool val);
      bool isGoalie() const;

   protected:
};

#endif
