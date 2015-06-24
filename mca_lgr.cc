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
Float_t mean,sigma,dmean,dsigma,data[N],x[N],y[N],sig_left=1,sig_right=3; // [n] refers to a vector 		      
Float_t integral=0,r[10],dr[10],days=0;
char file[100],title[150]=""; //title is a string with 150 characters

TCanvas *c = new TCanvas("c","Graph2D example",200,10,700,500);    //Canvas definition
c->SetFillColor(10);
c->SetBorderSize(2);
c->SetFrameFillColor(0);

gROOT->SetStyle("Bold"); 
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

Read_MCA(file, data, days,N);

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


TF1 *fitFcn = new TF1("fitFcn",fit_lgaus,a,b,5);
fitFcn->SetParameters(5,-0.001,1,(b+a)/2,100);	
fitFcn->SetLineWidth(4);
fitFcn->SetLineColor(kBlack);

/*
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

*/

TH1I *h2 = (TH1I*)H->Clone("h2");                 
TH1I *h4 = (TH1I*)H->Clone("h4");        
TH1I *h8 = (TH1I*)H->Clone("h8");       
TH1I *h16 = (TH1I*)H->Clone("h16");            
TH1I *h32 = (TH1I*)H->Clone("h32");  

h2->Rebin(2);	
h4->Rebin(4);
h8->Rebin(8);	
h16->Rebin(16);
h32->Rebin(32);	


c->cd(1);

H->Fit(fitFcn,"QR"); 
mean = fitFcn->GetParameter(3); 
sigma = fitFcn->GetParameter(4);
dmean = fitFcn->GetParError(3);
dsigma =fitFcn->GetParError(4);					
a=Int_t(mean-sig_left*sigma);                            	// sig_left and sig_right are the values to integrate 
b=Int_t(mean+sig_right*sigma);					// on the left and on the right of the peak (default: 1.8)
cout << "value for a: " << a << ", value for b: " << b << endl;
H->Fit(fitFcn,"QR"); 
Resol_eg(fitFcn,r[0],dr[0]);

//Float par[5]=;

/*
TF1 *fitFcn1 = new TF1("fitFcn1",fitFunction,a,b,5);
fitFcn1->SetParameters(5,-0.001,1,(b+a)/2,100);	
h2->Fit(fitFcn1,"QR");
Resol_e(fitFcn1,r[1],dr[1]);

TF1 *fitFcn2 = new TF1("fitFcn2",fitFunction,a,b,5);
fitFcn2->SetParameters(5,-0.001,1,(b+a)/2,100);	
h4->Fit(fitFcn2,"QR");
Resol_e(fitFcn2,r[2],dr[2]);

TF1 *fitFcn3 = new TF1("fitFcn3",fitFunction,a,b,5);
fitFcn3->SetParameters(5,-0.001,1,(b+a)/2,100);	
h8->Fit(fitFcn3,"QR");
Resol_e(fitFcn3,r[3],dr[3]);

TF1 *fitFcn4 = new TF1("fitFcn4",fitFunction,a,b,5);
fitFcn4->SetParameters(5,-0.001,1,(b+a)/2,100);	
h16->Fit(fitFcn4,"QR");
Resol_e(fitFcn4,r[4],dr[4]);

TF1 *fitFcn5 = new TF1("fitFcn5",fitFunction,a,b,5);
fitFcn5->SetParameters(5,-0.001,1,(b+a)/2,100);	
h32->Fit(fitFcn5,"QR");
Resol_e(fitFcn5,r[5],dr[5]);

cout << " R0= " << r[0] << endl;
cout << " R1= " << r[1] << endl;
cout << " R2= " << r[2] << endl;
cout << " R3= " << r[3] << endl;
cout << " R4= " << r[4] << endl;
cout << " R5= " << r[5] << endl;

*/

integral=h2->Integral(a,b);
cout << integral << endl;
/*
Int_t final=0;				// this is used to find the best rebining -  begin
do 
{	H->Fit(fitFcn,"QR");
	Resol_e(fitFcn,r[0],dr[0]);
	h2->Rebin(2);
	h2->Fit(fitFcn,"QR");
	Resol_e(fitFcn,r[1],dr[1]);


	if (r[0]>r[1]) 
		{
		H=h2;
		cont++;
		}
	else
		final=1;
}
while ((final==0)&&(cont<15));              // this is used to find the best rebining - end

*/







	
/*
TF1 *fitFcn2 = new TF1("fitFcn2","fitFcn->GetParameter(2)*TMath::Exp(-0.5*((x[0]-mean)/sigma)*((x[0]-mean)/sigma)",a,b,5);
fitFcn2->Draw("same");

integral=H->Integral(a,b);
H->Draw();
*/

PrintStats(fitFcn,cont,r[0],dr[0],mean,dmean,integral);
PrintLegend(r[0],dr[0],mean,dmean);

theApp->Run(kTRUE);
delete theApp;
return 0;
}
