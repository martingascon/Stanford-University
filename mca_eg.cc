//************** Copyright: Martin Gascon. Stanford University ***************************************
//included libraries
#include "libraries.h" 
#include "functions.h" 

using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

int main(int argc, char **argv) // argc = integer number of arguments; ** = points to a string; argv = string of parameters
{
//********************************** Variables declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv); // TRint = type of variable; theApp is name of variable you deine; * is a pointer to one character
Int_t k,m,a=1,b=8000,cont=0,reb=1,N=8192;  
Float_t mean,sigma,dmean,dsigma,ampli,data[N],x[N],y[N],sig_left=2,sig_right=3; //[n] refers to a vector 		      
Float_t integral=0,r[10],dr[10];
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
		reb=atoi(argv[2]);				//REB = REBINING OF FOR EACH FILE (DEFAULT 1)
		break;
	case 4: m=sprintf(file,"%s.mca",argv[1]);		// FILENAME A B   
		a=atoi(argv[2]);				// A AND B DEFINE THE RANGE TO FIT
		b=atoi(argv[3]);		
		break;
	case 5: m=sprintf(file,"%s.mca",argv[1]);		// FILENAME A B   
		a=atoi(argv[2]);				// A AND B DEFINE THE RANGE TO FIT
		b=atoi(argv[3]);
		reb=atoi(argv[4]);	
		break;
	case 6: m=sprintf(file,"%s.mca",argv[1]);		// FILENAME A B   
		a=atoi(argv[2]);				// A AND B DEFINE THE RANGE TO FIT
		b=atoi(argv[3]);
		sig_left=atoi(argv[4]);
		sig_right=atoi(argv[5]);		
		break;
	case 7: m=sprintf(file,"%s.mca",argv[1]);		// FILENAME A B   
		a=atoi(argv[2]);				// A AND B DEFINE THE RANGE TO FIT
		b=atoi(argv[3]);
		reb=atoi(argv[4]);	
		sig_left=atoi(argv[5]);
		sig_right=atoi(argv[6]);	
		break;
	default:
		MsgError();
		exit(1);
		break;

	};   

Read_MCA(file, data,N);

TH1I *H = new TH1I("H",file,N,0,N-1);  // declaration of the histogram	 
for (k=0;k<N;k++)			
	{
	x[k]=k;                 
	y[k]=data[k];
	H->Fill(x[k],y[k]);		// fill the histogram
	}
H->SetMarkerColor(7);
H->SetFillColor(19);
H->SetLineColor(2);
H->SetLineWidth(2);
H->SetMarkerStyle(8);
H->SetMarkerSize(1);
H->SetTitle(title);
H->GetXaxis()->SetTitle("Channel");
H->GetYaxis()->SetTitle(" Counts ");
H->GetXaxis()->CenterTitle();
H->GetYaxis()->CenterTitle();
H->Rebin(reb);

TF1 *fitFcn = new TF1("fitFcn",fit_egaus,a,b,5); // EXPO + GAUS (5 par)
fitFcn->SetParameters(5,-0.001,1,(b+a)/2,100);	
fitFcn->SetLineWidth(4);
fitFcn->SetLineColor(kBlack);

cout << "new value for a: " << a << ", new value for b: " << b << endl;
H->Fit(fitFcn,"R");
ampli = fitFcn->GetParameter(2);
mean = fitFcn->GetParameter(3); 
sigma = fitFcn->GetParameter(4);
dmean = fitFcn->GetParError(3);
dsigma =fitFcn->GetParError(4);		
cout << "new value for mean: " << mean << ", new value for s: " << sigma << endl;
a=Int_t(mean-sig_left*sigma);                            	// sig_left and sig_right are the values to integrate 
b=Int_t(mean+sig_right*sigma);					// on the left and on the right of the peak (default: 1.8)
cout << "new value for a: " << a << ", new value for b: " << b << endl;

H->Fit(fitFcn,"R"); 


TF1 *fgaus = new TF1("fgaus","gaus",a*0.9,b*1.1); // EXPO + GAUS (5 par)
fgaus->SetParameters(ampli,mean,sigma);	
fgaus->SetLineWidth(4);
fgaus->SetLineColor(kBlue);
fgaus->Draw("same");


Resol_eg(fitFcn,r[0],dr[0]);
gROOT->SetStyle("Bold"); 
gStyle->SetOptStat(0);    // display stats
gStyle->SetOptFit(0);     // display fit parameters 1 = on, 0 = off

PrintStats(fitFcn,cont,r[0],dr[0],mean,dmean,integral);
PrintLegend(r[0],dr[0],mean,dmean);


theApp->Run(kTRUE);
delete theApp;
return 0;
}
