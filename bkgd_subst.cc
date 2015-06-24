//************** Copyright: Martin Gascon. Stanford University ***************************************
//included libraries
#include "libraries.h" 
#include "functions.h" 

using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

//************** SETTINGS THAT CAN BE MODIFIED 

#define N 8192 	// Number of Data per spectrum in the MCA

//************** SETTINGS THAT CAN BE MODIFIED - END 
// int argc means you are declaring an integer number of arguments which you will enter into the command line. So for example, int argc has a value of 4 if you have "MCA file 1000 2000" written in the command line.
// argv indexes each of the above arguments. 

int main(int argc, char **argv)
{
Float_t data[N],data1[N],factor=0.0; 	// declares float numbers for data and data1, each of which accomodates 8192 values (data = channels, data1 is counts)	      
Int_t i,k,m1,m2,m3,aux=0;  // counters
char ar[100],file1[100],file2[100],file12[100]="added_spectra.mca",ci[100]; // file1 is the mca file (raw data saved) and file2 is another file for background data; file12 is the final result (after subtraction)-> this is the file you fit.

switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: MsgError();
		exit(1);
		break;						 
	case 3: m1=sprintf(file1,"%s.mca",argv[1]);		// FILENAME-A FILENAME-B 
		m2=sprintf(file2,"%s.mca",argv[2]);
		break;
	case 4: m1=sprintf(file1,"%s.mca",argv[1]);		// FILENAME-A FILENAME-B  FILENAME-AB    
		m2=sprintf(file2,"%s.mca",argv[2]);
		m3=sprintf(file12,"%s.mca",argv[3]);
		break;
	case 5: m1=sprintf(file1,"%s.mca",argv[1]);		// FILENAME-A FILENAME-B  FILENAME-AB    
		m2=sprintf(file2,"%s.mca",argv[2]);
		m3=sprintf(file12,"%s.mca",argv[3]);
		factor=atof(argv[4]);				// deals with the factor (in case you need to scale up the background to match acquisition time of actual measurement
		break;

	default:
		MsgError();
		exit(1);
		break;

	};   
//*********************************** Body of the program   *************************************

ifstream *in1 = new ifstream(file1); //point to first data point in file1
ifstream *in2 = new ifstream(file2); //point to first data point in file2
ofstream *out = new ofstream(file12); //output to first data point in file12

if(!*in1) 
	{cout << " ERROR OPENING FILE " <<  file1 << endl; 
	return 1; //end prog
	}
else    {	//if you are able to open the program
	i=1;

	do	{
		*in1 >> ci;		//drop what you are pointing into ci (copying original data into a separate place to work with)
		if ((strstr(ci,"DATA")!=0))	i=0;	// compare contents of ci (header lines) to "data"; once they match, drop out of loop
		}
	while (i!=0);

	for (i=0;i<N;i++) //out of header, now reading data
		*in1 >> data[i];                   // place actual PHS counts data into "data[i]"
	delete in1;   				//remove pointer	
	}

if(!*in2) 	// do same with other file (background file)
	{cout << " ERROR OPENING FILE " <<  file2 << endl; 
	return 1;
	}
else    {
	i=1;
	do	{
		*in2 >> ci;
		if ((strstr(ci,"DATA")!=NULL))	i=0;
		}
	while (i!=0);
	for (i=0;i<N;i++)
		*in2 >> data1[i];       // place background PHS counts data into "data1[i]"           
	delete in2;   
	}


m1=sprintf(ar,"<<DATA>>"); *out << ar << endl;

for (k=0;k<N;k++)
	{
	aux = data[k]-((float)data1[k]*factor); // doing the calc
	if (aux<0) aux=0; // if value is negative, just use zero
	*out << aux << endl; // place calculated value into output file12
	}

m1=sprintf(ar,"<<END>>");
*out << ar << endl; 
delete out;	//remove pointer to file12
return 0;
}
