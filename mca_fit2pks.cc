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
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);
Int_t i,k,m,a=1,b=1000,c=1000,d=2000,cont=0,reb=1;  
Float_t mean,mean2,sigma,sigma2,dmean,dmean2,dsigma,dsigma2,r,dr,r2,dr2,datos[N],x[N],y[N], cons=1,cons2=1,sig_left=1.8,sig_right=1.8; 		      
char file[100],title[150]="",ci[100]="";
TH1I *H = new TH1I("H",file,8192,0,8191); 
Float_t integral=0,TC=0,dTC=0,I1=0,dI1=0,I2=0,dI2=0;


gROOT->SetStyle("Bold");
gStyle->SetOptStat(0);   
gStyle->SetOptFit(0);     


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
		c=atoi(argv[4]);				// C AND D DEFINE THE RANGE TO FIT
		d=atoi(argv[5]);		
		break;
	case 7: m=sprintf(file,"%s.mca",argv[1]);		// FILENAME A B   
		a=atoi(argv[2]);				// A AND B DEFINE THE RANGE TO FIT
		b=atoi(argv[3]);
		c=atoi(argv[4]);				// C AND D DEFINE THE RANGE TO FIT
		d=atoi(argv[5]);		
		reb=atoi(argv[6]);	
		break;
	case 8: m=sprintf(file,"%s.mca",argv[1]);		// FILENAME A B   
		a=atoi(argv[2]);				// A AND B DEFINE THE RANGE TO FIT
		b=atoi(argv[3]);
		c=atoi(argv[4]);				// C AND D DEFINE THE RANGE TO FIT
		d=atoi(argv[5]);
		sig_left=atoi(argv[6]);
		sig_right=atoi(argv[7]);
		break;
	case 9: m=sprintf(file,"%s.mca",argv[1]);		// FILENAME A B   
		a=atoi(argv[2]);				// A AND B DEFINE THE RANGE TO FIT
		b=atoi(argv[3]);
		c=atoi(argv[4]);				// C AND D DEFINE THE RANGE TO FIT
		d=atoi(argv[5]);		
		reb=atoi(argv[6]);	
		sig_left=atoi(argv[7]);
		sig_right=atoi(argv[8]);	
		break;
	default:
		MsgError();
		exit(1);
		break;

	};   


ifstream *in = new ifstream(file);
if(!*in) 
	{cout << " ERROR OPENING FILE " <<  file << endl; 
	return 1;
	}
else    {
	i=1;
	do	{
		*in >> ci;
		//if ((strstr(ci,"LIVE_TIME")!=NULL))  strcpy(livetime,ci);
		//if ((strstr(ci,"START_TIME")!=NULL))  strcpy(starttime,ci);
		if ((strstr(ci,"DATA")!=NULL))	
			{
			i=0;
			if (argc==3) *in >> ci;
			}
		}
	while (i!=0);
	for (i=0;i<N;i++)
		*in >> datos[i];                  
		if ((strstr(ci,"ROI")!=NULL)) i=N;
	delete in;   
	}
for (k=0;k<N;k++)
	{
	x[k]=k;                 
	y[k]=datos[k];
	H->Fill(x[k],y[k]);
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
/*
TF1 *fitF3 = new TF1("fitF3",fitFunction3,a,b,5);
fitF->SetParameters(500,-3e-4,5,-0.001,1,(b+a)/2,100);	
fitF->SetLineWidth(4);
fitF->SetLineColor(kBlack);
*/
H->Rebin(reb);

TC=H->Integral(0,N);
dTC=sqrt(TC);
integral=H->Integral(a,b);


TF1 *g2 = new TF1("g2","gaus",a,b);
TH1I *h2 = (TH1I*)H->Clone("h2");                 
h2->Fit(g2,"QR");
cons = g2->GetParameter(0);
mean = g2->GetParameter(1);       			// obtengo el valor x del pico
sigma = g2->GetParameter(2);       			// obtengo el sigma


TF1 *g3 = new TF1("g3","gaus",c,d);
TH1I *h3 = (TH1I*)H->Clone("h3");
h3->Fit(g3,"QR"); 
cons2 = g3->GetParameter(0);
mean2 = g3->GetParameter(1);       			
sigma2 = g3->GetParameter(2);    

a=Int_t(mean-sig_left*sigma);                        
b=Int_t(mean+sig_right*sigma);				

cout << cons << " " << mean << " " << sigma << endl;
cout << cons2 << " " << mean2 << " " << sigma2 << endl;


TF1 *fitF = new TF1("fitF","[0]*exp([1]*x) + gaus(2) + gaus(5)",a,d);
//fitF->SetParameters(500,-3e-4,2300,1165,35,2500,1322,35);	
fitF->SetParameters(500,-3e-4,cons,mean,sigma,cons2,mean2,sigma2);	
//TF1 *fitF = new TF1("fitF",fitFunction,a,d,6);
//fitF->SetParameters(2000,1165,35,1500,1321,35);	


fitF->SetLineWidth(4);
fitF->SetLineColor(kBlack);
//H->Fit(fitF,"QR");

	
/*
TF1 *fitF2 = new TF1("fitF2","fitF->GetParameter(2)*TMath::Exp(-0.5*((x[0]-mean)/sigma)*((x[0]-mean)/sigma)",a,b,5);
fitF2->Draw("same");
Resol_e(fitF,r,dr);
H->Fit(fitF,"QR"); 
integral=H->Integral(a,b);
H->Draw();*/

a=Int_t(mean-sig_left*sigma);                         
b=Int_t(mean+sig_right*sigma);			
H->Fit(fitF,"R"); 

cons= fitF->GetParameter(2);
mean = fitF->GetParameter(3);       		
sigma = fitF->GetParameter(4);  
dmean =fitF->GetParError(3);
dsigma =fitF->GetParError(4);
r = 100*(sigma*2.35/mean);        	
dr=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
dr= sqrt(dr);



cons2 = fitF->GetParameter(5); 
mean2 = fitF->GetParameter(6);       			// obtengo el valor x del pico
sigma2 = fitF->GetParameter(7);  
dmean2 =fitF->GetParError(6);
dsigma2 =fitF->GetParError(7);
r2 = 100*(sigma2*2.35/mean2);        			// calculo la resolución
dr2=((235/mean2)*(235/mean2)*dsigma2*dsigma2+(235*sigma2/(mean2*mean2))*(235*sigma2/(mean2*mean2))*dmean2*dmean2);
dr2= sqrt(dr2);



TF1 *f1 = new TF1("f1","[0]*TMath::Exp(-0.5*((x-[1])/[2])*((x-[1])/[2]))",a,d);
TF1 *f2 = new TF1("f2","[0]*TMath::Exp(-0.5*((x-[1])/[2])*((x-[1])/[2]))",a,d);
TF1 *f3 = new TF1("f3","[0]*exp([1]*x)",a,d);
f1->SetParameters(cons,mean,sigma);	
f2->SetParameters(cons2,mean2,sigma2);	
f3->SetParameters(fitF->GetParameter(0),fitF->GetParameter(1));

I1=f1->Integral(b,d);
I2=f2->Integral(a,b);
dI1=sqrt(I1);
dI2=sqrt(I2);


f1->Draw("same");
f2->Draw("same");
f3->Draw("same");

PrintStats(fitF,cont,r,dr,mean,dmean,integral);
PrintLegend(r,dr,mean,dmean);

theApp->Run(kTRUE);
delete theApp;
return 0;
}
