
***********************************************************

GRAPHING CAPABILITIES

***********************************************************


There are two scripts here which will allow you to graph the
run logs that rmitgp prints out. This is a good way of seeing
the improvement on a generation by generation basis.



SCRIPTS:

jplot_fitness
  - Uses jgraph to plot the graph

gplot_fitness
  - Uses gnuplot to plot the graph

  
USE:
  From the directory containing the run log call the script.
  By default it assumes run logs will be called 

  run-log.txt

  If the run log is not of that name you may enter the file
  name as a parameter.

  jplot_fitness alt-run-log.txt


  To then view the graph use

  gv graphname


  The script will tell you the name of the graph at the end
  of the run.

