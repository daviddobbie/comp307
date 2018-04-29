/* File: common.h
 Author: Will Smart, 2004

 Description: Some specializations of internal types for gpp for regression as featured here
*/

#define FITBETTER(fa,fb) (fa.fitness<fb.fitness)
#define CLEARFIT(fa) fa.fitness=10000000.0;
#define BESTFIT 0.0
#define PROPORTIONALFIT(fa) ((fa.fitness>1000.0)?0.0:1.0-(fa.fitness/1000.0))
#define AIMMSE 0.0001
