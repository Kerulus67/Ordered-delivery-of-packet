#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <ctype.h>
#include <stdio.h>
#include <cstring>
using namespace std;


//////////// The .H file included in the main file //////////

#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
class Queue
{
  int max;     // Size of the Queue
  int* nodes;   // Pointer to assign array in the heap

  public:
    Queue(int size)
    {
      max = size + 1;
      nodes = new int[max]; // assigning the array in the heap with (max) size

      for (int i = 0; i < max; i++)
        nodes[i] = -1;  /// emptying all the queue by assign -1 to every node
    }

    int enqueue(int value)
    {
      if (nodes[value] != -1)
      {return 1;}
      else
      {
      nodes[value] = value;
      return 0;
      }
    };

    int buffersearch (int start)
    {

      for (int i = 0; i < max; i++)
      {
        if(nodes[i] == start)
        {
          cout<<nodes[i]<<" ";
          nodes[i] = -1;
          start = (start + 1) % (max);
        }
      }
 if (start == 0) // wrapping up function to make sure the buffersearch function will wrap up
 {
	  for (int i = 0; i < max; i++)
	  {
	    if(nodes[i] == start)
	    {
	      cout<<nodes[i]<<" ";
	      nodes[i] = -1;
	      start = (start + 1) % (max);
	    }
	  }
 }

      return start;
    };

    void printarray(int start, int window)
    {

      for (int i = 0 ; i < max ; i++){
        if (nodes[i] != -1 && nodes[i] + max <= start + window)
        nodes[i] += max + 1;
      }

      for (int i = 0; i < max; i++) {
      for (int j = 1; j < (max - i); j++)
      {
          if (nodes[j - 1] > nodes[j])
          {
              int temp = nodes[j - 1];
              nodes[j - 1] = nodes[j];
              nodes[j] = temp;
          }
      }
      }

      for (int i = 0; i < max; i++){
        if (nodes[i] != -1)
        cout<<nodes[i] % (max + 1)<< " ";
      }

    }
};
#endif



//////////// end of .H file //////////////////////


int main (int argc, char *argv[]){

int seqNumBits;
int winSizeBits;
int initSeq;
int dropFlag;
int drop[200];
int dropCounter;
int maxNumber;
int FlagErrorSeqNumBits;
int FlagErrorInitSeq;
int FlagErrorPacketID;
int FlagErrorWinSize;
int FlagErrorArguments;


dropCounter = 0;
dropFlag = 0;
FlagErrorSeqNumBits = 0;
FlagErrorInitSeq = 0;
FlagErrorPacketID = 0;
FlagErrorWinSize = 0;
FlagErrorArguments = 0;

if (argc < 5)
{
  FlagErrorArguments = 1;
}
if(argc >= 2)
{
seqNumBits = atoi(argv[1]);
}
if(argc >= 3)
{
winSizeBits = atoi(argv[2]);
}
if (argc >= 4)
{
initSeq = atoi(argv[3]);
maxNumber = pow(2,seqNumBits) - 1;
}
if(argc >= 2)
{
for(int j = 0; j < strlen(argv[1]); j++)
{
if (seqNumBits <= 0 || !isdigit(argv[1][j]))
{
	FlagErrorSeqNumBits = 1;
}
}
}

if(argc >= 3)
{

for(int j = 0; j < strlen(argv[2]); j++)
{
if (!isdigit(argv[2][j]))
{
	FlagErrorWinSize = 1;
}
}
if (FlagErrorSeqNumBits == 0)
{
	if (winSizeBits <= 0 || winSizeBits > maxNumber)
	{
		FlagErrorWinSize = 1;
	}
}
}



if(argc >= 4)
{
for(int j = 0; j < strlen(argv[3]); j++)
{
if (!isdigit(argv[3][j]))
{
	FlagErrorInitSeq = 1;
}
}
if (FlagErrorSeqNumBits == 0)
{
	if (initSeq < 0 || initSeq>maxNumber)
	{
		FlagErrorInitSeq = 1;
	}
}
}

for(int i = 0 ; i < 200 ; i++)
{
	drop[i] = -1;
}


if(argc >= 5)
{
for (int i = 4 ; i < argc ; i++)
{
	int x = atoi(argv[i]);
	for( int j = 0 ; j < strlen(argv[i]); j++)
	{
		if(!isdigit(argv[i][j]))
			{
			     FlagErrorPacketID = 1;
			}
	}
	if(FlagErrorSeqNumBits == 0)
	{
		if(x > maxNumber || x < 0)
		{
			FlagErrorPacketID = 1;
		}
	}
}
}
///////////Error Handling/////////////////////


if(FlagErrorArguments == 1 || FlagErrorSeqNumBits == 1 || FlagErrorWinSize == 1 || FlagErrorInitSeq == 1 || FlagErrorPacketID == 1)
{
	if(FlagErrorArguments == 1)
	{
		cout<<"Invalid number of arguments ";
	}
	if(FlagErrorSeqNumBits == 1)
	{
		cout<<"Invalid seqNumBits ";
	}
	if(FlagErrorWinSize == 1)
	{
		cout<<"Invalid winSize ";
	}
	if(FlagErrorInitSeq == 1)
	{
		cout<<"Invalid initSeq ";
	}
	if(FlagErrorPacketID == 1)
	{
		cout<<"Invalid packet ID ";
	}
	return 0;
}
else
{








Queue packet(maxNumber);
cout << "R ";
maxNumber++;

for (int i = 4 ; i < argc ; i++)
{
  int x = atoi(argv[i]);

    if (x == initSeq)
      {
        cout <<x<<" ";
        initSeq = (initSeq + 1) % maxNumber; // Wrapping Up statement
        initSeq = packet.buffersearch(initSeq);
      }
    	else
    	{

        // Check if out of bounds
        if (initSeq + winSizeBits < maxNumber)   //(x < initSeq) || (x > ((initSeq + winSizeBits)))
        {
        	if ((x < initSeq) || (x >= (initSeq + winSizeBits)))
        	{
        		drop[dropCounter] = x;
        		dropCounter++;
        	}
        	else
        	{
                dropFlag = packet.enqueue(x);
                if( dropFlag == 1)
                {
                	drop[dropCounter] = x;
                	dropCounter++;
                }

                initSeq = packet.buffersearch(initSeq);
        	}
        }
        else if(initSeq + winSizeBits >= maxNumber)
        {
        	if( (x < initSeq) && (x >= ((initSeq + winSizeBits) % maxNumber)))
        	{
        		drop[dropCounter] = x;
        		dropCounter++;
        	}
        	else
        	{
                dropFlag = packet.enqueue(x);
                if( dropFlag == 1)
                {
                	drop[dropCounter] = x;
                	dropCounter++;
                }

                initSeq = packet.buffersearch(initSeq);
        	}
        }
      }


}

cout << "E " << initSeq << " W ";
packet.printarray(initSeq, winSizeBits);
cout << "D ";
for(int i = 0 ; i < 200 ; i++)
{
	if (drop[i] != -1)
		cout<<drop[i]<<" ";
}
}
return 0;
}
