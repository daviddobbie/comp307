To execute the descisionTree classifier, we use the command:

Template
 .\dt training_file test_file

Example:
 .\dt .\hepatitis-training.dat .\hepatitis-test.dat

The assumption for this program is the values are all space separated with no 
erronous classifications in the training set.

Compilation:
This is C++ code so I have used the following command to compile the program:

g++ main.cpp -o dt

In Windows, we may need to have libstdc++-6.dll in the folder file system.