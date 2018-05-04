/******************************************************************************
 Definition file
 Class:        RobocupFitness
 Date created: 29/08/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

//Thread stuff
#include <pthread.h>
#define _REENTRANT
#include <errno.h>

#include <time.h>

using namespace std;

#include <float.h> //for DBL_MAX
#include <math.h>

#include <string>

#include "ReturnAction.h"
#include "RobocupFitness.h"

#include "SoccerPlayer.h"

//Robocup server includes
#include "field.h"   //Needed for stadium
#include "types.h"    //Needed for PM_PlayOn
#include "serializer.h" //Needed for serializer factory
#include "serializerplayerstdv8.h"

#include "GPConfig.h"

#include <unistd.h>  //Needed for sleep

//main.C in rcssserver source code
void * serverMain(void *);
extern Stadium Std;

RobocupFitness::RobocupFitness(GPConfig *conf) : Fitness(conf), players(NULL)
{
}

void RobocupFitness::initFitness()
{
   rcss::SerializerFactory::Registerer< 8, rcss::SerializerPlayerStdv8 > reg8;
   startServer();
}

void RobocupFitness::startServer()
{
   int ret;

   if (ret = pthread_create(&serverID, NULL, serverMain, (void *)NULL))
   {
      errno = ret;
      perror("Error occured");
      cerr << "Unable to start robocup server. Exiting " << ret << endl;
      exit(-1);
   }

   sleep(3);
}

void RobocupFitness::assignFitness(GeneticProgram* pop[], int popSize)
{
   int i,j;
   struct timespec ts;
   ReturnAction actions;
   string actionString;

   SoccerPlayer thePlayer(&Std, "GP");

   thePlayer.connectToServer();

   for(i=0; i<popSize; i++)
   {
      j=0;
      pop[i]->setFitness(0.5);

      thePlayer.setProgram(pop[i]);
      thePlayer.reset();

      _Start(Std);
      thePlayer.play();

      Std.time = 0;
      Std.change_play_mode(PM_BeforeKickOff);
      Std.reset_player_comm_flag();
   }

   thePlayer.disconnectFromServer();
}


bool RobocupFitness::solutionFound(GeneticProgram* pop[], int popSize)
{
   int i=0;
   for (; i<popSize; i++)
   {
      if (pop[i]->getFitness() <= 0.0001)
         return true;
   }
   return false;
}

bool RobocupFitness::isBetter(GeneticProgram* gp1, GeneticProgram* gp2)
{
   return (gp1->getFitness() < gp2->getFitness());
}

bool RobocupFitness::isWorse(GeneticProgram* gp1, GeneticProgram* gp2)
{
   return (gp1->getFitness() > gp2->getFitness());
}

bool RobocupFitness::isEqual(GeneticProgram* gp1, GeneticProgram* gp2)
{
   return (gp1->getFitness() == gp2->getFitness());
}

double RobocupFitness::best()
{
   return 0.0;
}

double RobocupFitness::worst()
{
   return DBL_MAX;
}
