/******************************************************************************
 Definition file
 Package:      mpi GP utility functions
 Date created: 10/09/2002
 Written by:   Dylan Mawhinney

 See header file for details
***************************************************************************/

#include "GPmpi.h"

#include <string>

using namespace std;


void sendIndividuals(int numToSend, GeneticProgram **programList, int node)
{
   int i;   
   string *programStrings;   //String representation of each of the programs
   int programID;            //ID of the program being sent

   int maxMessageLength=0;       //Maximum size of the mpi message we will send 
   char *sendBuffer;         //The buffer to store our message
   int sendBufferPos = 0;    //Position counter
   int length1, length2;

   
   programStrings = new string[numToSend];

   //Print each program into the corresponding string
   for (i=0; i<numToSend; i++)
   {
      programList[i]->print(programStrings[i]);
   }

   //Compute the maximum packed length of the MPI message
   for(i=0; i<numToSend; i++)
   {
      MPI_Pack_size(2, MPI_INT, MPI_COMM_WORLD, &length1);
      MPI_Pack_size(programStrings[i].length(), MPI_CHAR,
                    MPI_COMM_WORLD, &length2);

      maxMessageLength += (length1 + length2);
   }

   //Allocate the message buffer
   sendBuffer = new char[maxMessageLength];

   //Pack all the programs into one message
   for(i=0; i<numToSend; i++)
   {
      //Pack the program id
      programID = programList[i]->getProgramID();
      MPI_Pack(&programID, 1, MPI_INT, sendBuffer, maxMessageLength,
               &sendBufferPos, MPI_COMM_WORLD);

      //Pack the length of the program string
      length1 = programStrings[i].length();
      MPI_Pack(&length1, 1, MPI_INT, sendBuffer,
               maxMessageLength, &sendBufferPos, MPI_COMM_WORLD);

      //Pack the program string
      MPI_Pack((void *)(programStrings[i].c_str()), programStrings[i].length(),
               MPI_CHAR, sendBuffer, maxMessageLength, &sendBufferPos,
               MPI_COMM_WORLD);
   }

   //Send the total number of individuals to node
   MPI_Send(&numToSend, 1, MPI_INT, node, 0, MPI_COMM_WORLD);
   //Send the total number of bytes
   MPI_Send(&maxMessageLength, 1, MPI_INT, node, 0, MPI_COMM_WORLD);
   //Send the packed message
   MPI_Send(sendBuffer, sendBufferPos, MPI_PACKED, node, 0,
            MPI_COMM_WORLD);
   
   delete [] programStrings; 
   delete [] sendBuffer;
}

int getIndividuals(int maxInd, GeneticProgram **programList, int *node)
{
   int i;

   int numberToReceive=0;  //Number of program we will receive    
   int messageSizeBytes=0; //Size of the message in bytes
   char *recvBuffer;       //message storage
   int recvBufferPos;      //position in memory storage
   string programString;   //string representation of the program

   MPI_Status status;

   //Read the number of programs we are going to receive
   MPI_Recv(&numberToReceive, 1, MPI_INT, MPI_ANY_SOURCE, 0,
            MPI_COMM_WORLD, &status);

   *node = status.MPI_SOURCE;  //Store the source of this message

   //Check for invalid number of programs to receive
   if (numberToReceive <= 0)
      return 0;
   else if (numberToReceive > maxInd)
   {
      cerr << "Error, the number of programs received is greater than "  
           << "the maximum possible." << endl;

      return GPMPI_ERROR;
   }

   //Find out how many bytes the message is
   MPI_Recv(&messageSizeBytes, 1, MPI_INT, MPI_ANY_SOURCE, 0,
            MPI_COMM_WORLD, &status); 

   if (messageSizeBytes <= 0)
      return GPMPI_ERROR;

   //Allocate the correct number of bytes for the incoming message
   recvBuffer = new char[messageSizeBytes];

   //Receive the message
   MPI_Recv(recvBuffer, messageSizeBytes, MPI_PACKED, MPI_ANY_SOURCE, 0,
            MPI_COMM_WORLD, &status);

   recvBufferPos = 0;

   //For each program
   for (i=0; i<numberToReceive; i++)
   {
      programString = "";   
      int stringLength;
      char *programData;
      int programID;

      //Get the programID of the next program
      MPI_Unpack(recvBuffer, messageSizeBytes, &recvBufferPos, &programID,
                 1, MPI_INT, MPI_COMM_WORLD);
      //Set the programID
      programList[i]->setProgramID(programID);

      //Get the length of the program string
      MPI_Unpack(recvBuffer, messageSizeBytes, &recvBufferPos, &stringLength,
                 1, MPI_INT, MPI_COMM_WORLD);

      //Allocate enough memory for the string.
      programData = new char[stringLength + 1];

      //Unpack the string into the newly allocated memory
      MPI_Unpack(recvBuffer, messageSizeBytes, &recvBufferPos, programData,
                 stringLength, MPI_CHAR, MPI_COMM_WORLD);

      programData[stringLength] = '\0';

      programString = programData;

      //Pass the string to the GeneticProgram class so it can parse
      //it and build a new program tree
      programList[i]->deleteTree();
      programList[i]->parseProgram(programString);

      delete [] programData;
   } 

   delete [] recvBuffer;

   return i;
}

void sendFitnesses(int numToSend, GeneticProgram **programList, int node)
{
   int i;

   char *sendBuffer;        //The buffer to store the message to be sent
   int sendBufferPos=0;     //Buferr position counter
   int maxMessageLength=0;  //The largest possible size of the message 
 
   int length1, length2;
   double programFitness;   //The fitness of a program
   int programID;           //The program id

   //Compute the maximum length of sending an ID and fitness 
   //for every individual
   for (i=0; i<numToSend; i++)
   {
      MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &length1);
      MPI_Pack_size(1, MPI_DOUBLE, MPI_COMM_WORLD, &length2);

      maxMessageLength += (length1 + length2);
   }

   //Allocate the max number of bytes
   sendBuffer = new char[maxMessageLength];

   for (i=0; i<numToSend; i++)
   {
      programID = programList[i]->getProgramID();    
      programFitness = programList[i]->getFitness();

      //Pack the program id into the message
      MPI_Pack(&programID, 1, MPI_INT, sendBuffer, maxMessageLength,
               &sendBufferPos, MPI_COMM_WORLD);

      //Pack the fitness into the message
      MPI_Pack(&programFitness, 1, MPI_DOUBLE, sendBuffer, maxMessageLength,
                &sendBufferPos, MPI_COMM_WORLD);
   }

   //Send the now packed message back to the client
   MPI_Send(sendBuffer, sendBufferPos, MPI_PACKED, node,
            0, MPI_COMM_WORLD);

   delete [] sendBuffer;
}

void getFitnesses(int maxNum, GeneticProgram **programList)
{
   char *recvBuffer;       //message storage
   int recvBufferPos=0;    //position in memory storage
   int bytesRead=0;        //Number of bytes received

   int length1, length2;
   int maxMessageSize;

   int programID;
   double programFitness;

   MPI_Status status;

   //FIX:
   //This code may only work on homogeneous systems
   //I'm assuming that an int and a double packed
   //is the same size on the sending machine as it is
   //on the receiving machine.
   //Probably not a good assumption to make.

   MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &length1);
   MPI_Pack_size(1, MPI_DOUBLE, MPI_COMM_WORLD, &length2);

   maxMessageSize = (length1 + length2) * maxNum; 

   recvBuffer = new char[maxMessageSize];

   MPI_Recv(recvBuffer, maxMessageSize, MPI_PACKED, MPI_ANY_SOURCE,
            0, MPI_COMM_WORLD, &status);

   MPI_Get_count(&status, MPI_PACKED, &bytesRead);

   while(recvBufferPos < bytesRead)   
   {
      MPI_Unpack(recvBuffer, maxMessageSize, &recvBufferPos, &programID, 1,
                    MPI_INT, MPI_COMM_WORLD);

      MPI_Unpack(recvBuffer, maxMessageSize, &recvBufferPos, &programFitness,
                 1, MPI_DOUBLE, MPI_COMM_WORLD);

      programList[programID]->setFitness(programFitness);
   }

   delete [] recvBuffer;
}
