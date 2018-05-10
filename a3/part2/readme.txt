To execute the nearestNeighbour classifier, we use the command:

Template
 .\nearestN training_file test_file k

Example (for k = 1):
 .\nearestN .\iris-training.txt .\iris-test.txt 1

The assumption for this program is the values are all space separated with no 
errnous classifications in the training set.

Compilation:
This is C++ code so I have used the following command to compile the program:

g++ main.cpp -o nearestN

In Windows, we may need to have libstdc++-6.dll in the folder file system.


