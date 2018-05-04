*****************************Using Parsimony Pressure*********************

To use Parsimony pressure, You need to include the following line of code:

   symConfig.parsimonypres = new Parsimony(1.0);

 Here, symConfig is an instance of GPConfig. The initialization on the right 
hand side of the above statement can have any of the subclasses of Parsimony.
This includes:
   symConfig.parsimonypres = new LinearParsimony(1.0);
   symConfig.parsimonypres = new SinParsimony(1.0);
   symConfig.parsimonypres = new ConstantParsimony(1.0);
   symConfig.parsimonypres = new LimitParsimony(1.0, 200);
   
 Each subclass applies parsimony pressure, such that, the average size of the
population varies in Linear, Sinusoidal, Constant or Limit to 200, manner. The
parameter "1.0" may need to be optimized for specific problems.


##############################################################################

NOTE: while using Parsimony Pressure it is important to consider the maximum
depth and the initial depth of the GP programs. The maximum depth is the
maximum possible size of the GP tree. The initial depth is the maximum possible
size of a tree when the initial population is generated. They can be
initialized as follows:
   
   pop.setDepthLimit(symConfig.maxDepth);
   pop.setinitDepthLimit(7);


   Please note the order in which the depth is initialised, it must be done in
the same manner, depthLimit before initdepthLimit. This is due to backward 
compatibility reasons, function setdepthLimit() initialises initdepthLimit as
well.


##############################################################################

NOTE: The parsimony pressure may only be used with roulette wheel selection.
That is the selection Operator must be initialised as follows:

   symConfig.selectionOperator = new Selection();

 Again, symConfig is an instance of GPConfig.


However, if one needs to test out the parsimony performance on a tournament
selection operator, the "TournamentSelection.cpp" file in the "src" folder must
be first modified as follows:

   comment out line 38 :
      else if (config->fitnessObject->isBetter(pop[individual], pop[bestIndividual]))
   un-comment line 39-41:
      else//Normalized fitness used to apply parsimony pressure
      if(pop[individual]->getNormFitness() > 
                                        pop[bestIndividual]->getNormFitness())
      
  Please note that this change means the tournament selection uses normalised
fitness to compare between two individuals. Hence, (due to the ">" symbol) 
fitness functions are restricted to have lower fitness values as better fitness values.

#############################################################################
