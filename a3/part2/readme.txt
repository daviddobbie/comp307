To execute the naiveBayes classifier, we use the command:

Template:

.\naiveBayes .\spamLabelled.dat .\spamUnlabelled.dat


The assumption for this program is the values are all space separated with no 
erroneous classifications in the training set.

Compilation:
This is C++ code so I have used the following command to compile the program:

g++ main.cpp -o naiveBayes

In Windows, we may need to have libstdc++-6.dll in the folder file system.


