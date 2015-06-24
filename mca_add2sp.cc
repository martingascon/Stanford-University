//************** Copyright: Martin Gascon. Stanford University ***************************************
//included libraries
#include "libraries.h" 
#include "functions.h" 

using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

//************** SETTINGS THAT CAN BE MODIFIED 

#define N 8192 	// Number of Data per spectrum in the MCA

//************** SETTINGS THAT CAN BE MODIFIED - END 

int main(int argc, char **argv)
{
Float_t data[N],data1[N]; 		      
Int_t i,k,m1,m2,m3;  
char ar[100],file1[100],file2[100],file12[100]="added_spectra.mca",ci[100];



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
	default:
		MsgError();
		exit(1);
		break;

	};   
//*********************************** Cuerpo del programa   *************************************

ifstream *in1 = new ifstream(file1);
ifstream *in2 = new ifstream(file2);
ofstream *out = new ofstream(file12);

if(!*in1) 
	{cout << " ERROR OPENING FILE " <<  file1 << endl; 
	return 1;
	}
else    {
	i=1;
	do	{
		*in1 >> ci;
		if ((strstr(ci,"DATA")!=NULL))	i=0;
		}
	while (i!=0);
	for (i=0;i<N;i++)
		*in1 >> data[i];                  
	delete in1;   
	}

if(!*in2) 
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
		*in2 >> data1[i];                  
	delete in2;   
	}

m1=sprintf(ar,"DATA");
*out << ar << endl;
for (k=0;k<N;k++)
	{
	*out << data[k]+data1[k] << endl;
	}
delete out;
return 0;
}
