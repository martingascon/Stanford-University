//************** Copyright: Martin Gascon. Stanford University ***************************************
//included libraries
#include "libraries.h" 
#include "functions.h" 

using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

int main(int argc, char **argv) // argc = integer number of arguments; ** = points to a string; argv = string of parameters
{
//********************************** Variables declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv); // TRint = type of variable; theApp is name of variable you deine; * is a pointer to one character
Int_t k,m,a=1,reb=2,N=8192;  
Float_t data[N],x[N],y[N]; //[n] refers to a vector 		      
char file[100],title[150]=""; //title is a string with 150 characters

gROOT->SetStyle("Plain"); 
gStyle->SetOptStat(0);    // display stats
gStyle->SetOptFit(0);     // display fit parameters 1 = on, 0 = off

switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: m=sprintf(file,"%s.mca",argv[1]);		// FILENAME 	
		break;						 
	case 3: m=sprintf(file,"%s.mca",argv[1]);		// FILENAME REB
		a=atoi(argv[2]);				//REB = REBINING OF FOR EACH FILE (DEFAULT 1)
		break;

default:
		MsgError();
		exit(1);
		break;

	};   

Read_MCA(file, data,N);

TH1I *H = new TH1I("H",file,2998,501,3499);  // declaration of the histogram	 
for (k=0;k<N;k++)			
	{
	x[k]=k;                 
	y[k]=data[k];
	H->Fill(x[k],y[k]);		// fill the histogram
	}
H->SetMarkerColor(7);
H->SetFillColor(0);
H->SetLineColor(2);
H->SetLineWidth(2);
H->SetMarkerStyle(8);
H->SetMarkerSize(1);
H->SetTitle(title);
H->GetXaxis()->SetTitle("Channel");
H->GetYaxis()->SetTitle(" Counts ");
H->GetXaxis()->CenterTitle();
H->GetYaxis()->CenterTitle();

H->GetYaxis()->SetRangeUser(1,999);
//H->GetXaxis()->SetRange(500,3500);

H->Rebin(reb);

H->Draw();

TLatex *tx = new TLatex();
tx->SetNDC();
tx->SetTextFont(62);
tx->SetTextColor(36);
tx->SetTextAlign(12);
tx->SetTextSize(0.05);
tx->SetTextColor(1);

char pres[100];
m=sprintf(pres,"P = %03d MPa",a*7);

tx->DrawLatex(0.6,0.80,pres);


gROOT->SetStyle("Bold"); 
gStyle->SetOptStat(0);    // display stats
gStyle->SetOptFit(0);     // display fit parameters 1 = on, 0 = off

//PrintStats(g1,cont,r[0],dr[0],mean,dmean,integral);
//PrintLegend(r[0],dr[0],mean,dmean);


theApp->Run(kTRUE);
delete theApp;
return 0;
}
