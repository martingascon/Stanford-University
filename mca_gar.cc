//************** Copyright: Martin Gascon. Stanford University ***************************************
//included libraries
#include "libraries.h" 
#include "functions.h" 

using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

int main(int argc, char **argv)
{
//********************************** variable declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);
Int_t i,k,m,a=1,b=1000,cont=0,reb,N=8192;  
Float_t mean,sigma,dmean,dsigma,r,dr,r2,dr2,data[N],x[N],y[N],sig_left=1.8,sig_right=1.8; 		      
Float_t integral=0;
char file[100],title[150]="",ci[100]="";
gROOT->SetStyle("Bold");


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

TF1 *g2 = new TF1("g2","gaus",a,b);          // this is used to find the best rebining - begin
TH1I *h2 = (TH1I*)H->Clone("h2");                 

H->Fit(g2,"QR"); 
mean = g2->GetParameter(1); 
sigma = g2->GetParameter(2);
dmean = g2->GetParError(1);
dsigma =g2->GetParError(2);					
a=Int_t(mean-sig_left*sigma);                            // sig_left and sig_right are the values to integrate 
b=Int_t(mean+sig_right*sigma);				// on the left and on the right of the peak (default: 1.8)

integral=h2->Integral(a,b);
cout << integral << endl;
Int_t final=0;				// this is used to find the best rebining -  begin
do 
{	H->Fit(g2,"QR");
	Resol_g(g2,r,dr);
	h2->Rebin(2);
	h2->Fit(g2,"QR");
	Resol_g(g2,r2,dr2);


	if (r>r2) 
		{
		H=h2;
		cont++;
		}
	else
		final=1;
}
while ((final==0)&&(cont<15));              // this is used to find the best rebining - end


cout << "value for a: " << a << ", value for b: " << b << endl;

H->Fit(g2,"R+"); 


Resol_g(g2,r,dr);

H->Draw();
mean = g2->GetParameter(1); 
sigma = g2->GetParameter(2);
dmean = g2->GetParError(1);
dsigma =g2->GetParError(2);
	
PrintStats(g2,cont,r,dr,mean,dmean,integral);
PrintLegend(r,dr,mean,dmean);


gStyle->SetOptStat(0);   
gStyle->SetOptFit(0);     
theApp->Run(kTRUE);

delete theApp;
return 0;
}
