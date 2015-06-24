//************** Copyright: Martin Gascon. Stanford University ***************************************
//included libraries
#include "libraries.h" 
#include "functions.h" 

using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

//************** SETTINGS THAT CAN BE MODIFIED 

#define N 2000 	// Number of Data per pulse
#define Z 100	// Maximum Number of pulses per file	

//************** SETTINGS THAT CAN BE MODIFIED - END 


int main(int argc, char **argv)
{
TRint *theApp = new TRint("Rint", &argc, argv);
char file[100],file2[100],ci[100];
Int_t h,i,j,m,nini,nfin;      // initial and final file numbers

switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: m=sprintf(file,"w00000%s.txt",argv[1]);
		nini=atoi(argv[1]);nfin=nini;
		break;
	case 3: m=sprintf(file,"w00000%s.txt",argv[1]);
		nini=atoi(argv[1]);nfin=atoi(argv[2]);
		break;
	default:
		MsgError();
		exit(1);
		break;
	};   
m=system("clear");
cout << "Program to convert TDS files to single txt pulses"  << endl;
cout << "****************************************************"  << endl;
m=system("mkdir ../pulses"); cout << "Folder pulses was created"  << endl;
cout << "Still working, please wait .... " <<  endl << endl ;

for (j=nini;j<(nfin+1);j++) 						//sumo desde nini a nfin los 8000 ficheros
{	
	m=sprintf(file,"w00000%.4d.txt",j);  					//cargo en file el nombre del fichero
	ifstream *in = new ifstream(file);				// in es puntero asignado a fichero
	if(!*in) 							// Si no se puede abrir in 
	{	cout << " ERROR OPENING FILE " <<  file << endl;	// Imprime que hay un error
		return 1;						// Salida 1 => error
	}
	else    
	{	
	for (i=0;i<Z;i++)                            // cargo los datos en datosy, y2
		{
		      	m=sprintf(file2,"../pulses/%.4d.txt",i+(j-nini)*Z);  
			ofstream *out2 = new ofstream(file2,ios::app);
			for (h=0;h<N;h++)
				{
				*in >> ci;
				*out2 << ci <<  endl;
				}
		delete out2;
	        if ((i%50)==0) cout << "completed: " << i+(j-nini)*Z  <<"/"<< (nfin-nini)*Z+Z << endl;
		}		
	
	}
}
cout << "Finished. Thanks for your patiente.		     "  << endl;
cout << "****************************************************"  << endl << endl;

delete theApp;
return 0;
}

