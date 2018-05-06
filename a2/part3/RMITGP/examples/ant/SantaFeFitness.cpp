/******************************************************************************
 Definition file
 Class:        SantaFeFitness
 Date created: 23/07/2002
 Written by:   Dylan Mawhinney

 See header file for details
******************************************************************************/

using namespace std;

#include <cstdlib>
#include <iostream>

#include <float.h> //for DBL_MAX

#include "SantaFeFitness.h"
#include "GPConfig.h"
#include "ReturnDummy.h"

const int SantaFeFitness::MAP_WIDTH = 32;
const int SantaFeFitness::MAP_HEIGHT = 32;
const int SantaFeFitness::MAX_STEPS = 600;

const int SantaFeFitness::NORTH = 1;
const int SantaFeFitness::EAST = 2;
const int SantaFeFitness::SOUTH = 3;
const int SantaFeFitness::WEST = 4;

SantaFeFitness::SantaFeFitness(GPConfig *conf) : Fitness(conf)
{
   int i;
   map = new int*[MAP_WIDTH];
  
   for (i=0; i<MAP_WIDTH; i++)
   {
      map[i] = new int[MAP_HEIGHT];
   }

   if(TARPEIAN) conf->activateTarpeian(this); // QCS 20121012
   if(DDL) {
   	   conf->activateDDL(this); // QCS 20121012
   	   conf->ddl->setHeavy(true); // QCS 20121012
   	   conf->ddl->setVeryHeavy(true); // QCS 20121012
   }
}

SantaFeFitness::~SantaFeFitness() 
{
   int i;

   for (i=0; i<MAP_WIDTH; i++)
      delete [] map[i];

   delete [] map;
}

void SantaFeFitness::initFitness()
{
   int i, j;
   foodLeft = 89;
   x = 0;
   y = 0;
   direction = EAST;
   simStep = 0;

   int tmp_map[MAP_WIDTH][MAP_HEIGHT] = 
     {{ 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 2, 2, 0, 0 },
      { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0 },
      { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0 },
      { 0, 0, 0, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 2, 2, 0, 0, 0, 0, 2, 0, 0 },
      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0 },
      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0 },
      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0 },
      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0 },
      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0 },
      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 2, 2, 1, 1, 1, 2, 0, 0 },
      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 1, 2, 2, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 2, 1, 2, 2, 2, 0, 0, 0, 0 },
      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0 },
      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0 },
      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 1, 2, 0, 0, 0, 0 },
      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 0, 2, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 0, 1, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 0, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 0, 2, 1, 1, 1, 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }};

   for (i=0; i<MAP_WIDTH; i++)
   {
      for (j=0; j<MAP_HEIGHT; j++)
      {
         map[i][j] = tmp_map[i][j];
      }
   }
}

void SantaFeFitness::assignFitness(GeneticProgram* pop[], int popSize)
{
   int i;
   ReturnDummy rd;

   for(i=0; i<popSize; i++)
   {
      initFitness();

      pop[i]->setFitness(0.0);

      while(simStep < MAX_STEPS)
      {
         pop[i]->evaluate(&rd);
      }

      pop[i]->setFitness(foodLeft);
   }
}

void SantaFeFitness::eat()
{
   if (simStep >= 600)
      return;

   if (map[y][x] == 1)
   {
      foodLeft--;
      map[y][x] = 2;
   }

   simStep++;
}

void SantaFeFitness::move()
{
   if (simStep >= 600)
      return;

   switch(direction)
   {
      case NORTH:
         y--;
         break;
      
      case EAST:
         x++;
         break;
 
      case SOUTH:
         y++;
         break;   

      case WEST:
         x--;
         break;   
   }

   if (x >= MAP_WIDTH)
      x -= MAP_WIDTH;
   else if (x < 0)
      x += MAP_WIDTH;

   if (y >= MAP_HEIGHT)
      y -= MAP_HEIGHT;
   else if (y < 0)
      y += MAP_HEIGHT;

   eat();

   simStep++;
}

void SantaFeFitness::turnLeft()
{
   if (simStep >= 600)
      return;

   if(--direction < NORTH)
      direction = WEST;

   simStep++;
}

void SantaFeFitness::turnRight()
{
   if (simStep >= 600)
      return;

   if(++direction > WEST )
      direction = NORTH;

   simStep++;
}

bool SantaFeFitness::ifFoodAhead()
{
   int tmpX=-1, tmpY=-1;

   switch(direction)
   {
      case NORTH:
         tmpX = x;
         tmpY = y - 1;
         break;
      case WEST:
         tmpX = x - 1;
         tmpY = y;
         break;
      case SOUTH:
         tmpX = x;
         tmpY = y + 1;
         break;
      case EAST:
         tmpX = x + 1;
         tmpY = y;
         break;
   }

   if (tmpX < 0)
      tmpX += MAP_WIDTH;
   if (tmpX >= MAP_WIDTH)
      tmpX -= MAP_WIDTH;

   if (tmpY < 0)
      tmpY += MAP_HEIGHT;
   if (tmpY >= MAP_HEIGHT)
      tmpY -= MAP_HEIGHT;

   if (map[tmpY][tmpX] == 1)
      return true;

   return false;
}

bool SantaFeFitness::solutionFound(GeneticProgram* pop[], int popSize)
{
   int i=0;
   for (; i<popSize; i++)
   {
      if (pop[i]->getFitness() <= 0.000001)
         return true;
   }
   return false;
}

bool SantaFeFitness::isBetter(GeneticProgram* gp1, GeneticProgram* gp2)
{
   return (gp1->getFitness() < gp2->getFitness());
}

bool SantaFeFitness::isWorse(GeneticProgram* gp1, GeneticProgram* gp2)
{
   return (gp1->getFitness() > gp2->getFitness());
}

bool SantaFeFitness::isEqual(GeneticProgram* gp1, GeneticProgram* gp2)
{
   return (gp1->getFitness() == gp2->getFitness());
}

double SantaFeFitness::best()
{
   return 0.0;
}

double SantaFeFitness::worst()
{
   return 89; 
}
