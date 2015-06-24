//************** Copyright: Martin Gascon. Stanford University ******************************************
//This program represent pulses obtained with the Tektronik TDS5000 Oscilloscope 
//included libraries
#include "libraries.h" 
#include "functions.h" 

using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

//************** SETTINGS THAT CAN BE MODIFIED - BEGIN **************************************************

#define N 500 	       // Number of points for each pulse (sampling)


//************** SETTINGS THAT CAN BE MODIFIED - END ****************************************************

//**********************************  PROGRAM ***********************************************************


int main(int argc, char **argv)
{
TRint *theApp = new TRint("Rint", &argc, argv);

Float_t data[N],x[N],y[N]; 		 
Int_t i,j,m,pulso,ini=0,fin=0,tot=0;  				
char xaxis[100]="time (#mus)",yaxis[100]="voltage (V)", file[100];

TCanvas *c = new TCanvas("c","Graph2D example",200,10,700,500);    //Canvas definition
  c->SetFillColor(10);
  c->SetBorderSize(2);
  c->SetFrameFillColor(0);


gROOT->SetStyle("Plain");          // root options
gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);
gStyle->SetOptFit(0);
//*********************************** BODY  *************************************
switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: m=sprintf(file,"%s.txt",argv[1]);
		ini=atoi(argv[1]);fin=ini;
		break;
	case 3: m=sprintf(file,"%s.txt",argv[1]);
		ini=atoi(argv[1]);fin=atoi(argv[2]);
		break;
	default:
		MsgError();
		exit(1);
		break;
	};


tot=fin-ini;           // total number of pulses 

if (tot<5)             // if the number is <5 divide the canvas in a sigle row
	{
	c->Divide(1,tot);
	}
else
	{
	if (tot<10)
		c->Divide(2,tot/2+1);
	else
		c->Divide(4,tot/4+1);
	}
pulso=atoi(argv[1]);

for (j=ini;j<(fin+1);j++) 	
	{
	m=sprintf(file,"%d.txt",j); 
	ifstream *in = new ifstream(file);
	if(!*in) 
		{
		cout << " ERROR OPENING FILE " <<  file << endl; 
		return 1;
		}
	else    
		{
		for (i=0;i<(N-1);i++)
			*in  >> data[i];                  
		}   
	delete in;   	


for (i=0;i<(N-1);i++)                                      // cargo los datos en x e y, y2
		{
		x[i]=i*2;
		y[i]=data[i];		
		}   


TGraph *gr1 = new TGraph(N-1,x,y);	// Graph declaration
gr1->SetLineColor(4);			// line colour 0=white 1=black, 2=red
gr1->SetLineWidth(1);			// Line width 
gr1->SetMarkerColor(4);		
gr1->SetMarkerStyle(19);		// Styles 19 = dot, 20 = circle, 21 = square
gr1->GetXaxis()->SetTitle(xaxis);	
gr1->GetYaxis()->SetTitle(yaxis);	
gr1->GetXaxis()->CenterTitle();		// to center the title in x axis 
gr1->GetYaxis()->CenterTitle();				
c->cd(1+(j-ini));			//  
gr1->Draw("AL");			// Draw A:frame P=dots L=line C=curve

	}



c->cd(0);
theApp->Run(kTRUE);			// makes the executable
delete theApp;
return 0;


}
