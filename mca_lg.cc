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
Float_t me[3],si[3],dm[3],ds[3],data[N],x[N],y[N],sig_left=1,sig_right=3,days=0; // [n] refers to a vector 		      
Float_t integral=0,r[10],dr[10];
char file[100],title[150]="",res;  //title is a string with 150 characters

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

Double_t par1[5]; 	
	
TF1 *fitFcn = new TF1("fitFcn",fit_lgaus,a,b,5);
fitFcn->SetParameters(5,-0.001,1,(b+a)/2,100);	
fitFcn->SetLineWidth(4);
fitFcn->SetLineColor(kBlack);


H->Fit(fitFcn,"QR"); 
me[0] = fitFcn->GetParameter(3); 
si[0] = fitFcn->GetParameter(4);
dm[0] = fitFcn->GetParError(3);
ds[0] =fitFcn->GetParError(4);					
a=Int_t(me[0]-sig_left*si[0]);                            	// sig_left and sig_right are the values to integrate 
b=Int_t(me[0]+sig_right*si[0]);					// on the left and on the right of the peak (default: 1.8)

cout << "new value for a: " << a << ", new value for b: " << b << endl;
H->Fit(fitFcn,"R"); 
Resol_eg(fitFcn,r[0],dr[0]);

PrintStats(fitFcn,cont,r[0],dr[0],me[0],dm[0],integral);
PrintLegend(r[0],dr[0],me[0],dm[0]);



cout << "Do you want to save your data into data.txt (y/n)?" << endl;  
cin >> res;
if (res=='s'||res=='y')
  	{
	ofstream *out = new ofstream("PHvsTime.txt",ios::app);
	ofstream *dat = new ofstream(".param5.txt",ios::trunc);
	*out <<  std::fixed << std::setprecision(4) << days << "\t"  << 0.0014 << "\t" << std::fixed << std::setprecision(1) << me[0] << "\t" << dm[0]*3 <<"\t" <<  r[0] << "\t" << dr[0] << endl;	
	*dat << par1[0] << "\t" << par1[1] << "\t" << par1[2] << "\t" << par1[3] <<  "\t" << par1[4] << endl;


	}
else
	exit(1);


delete theApp;
return 0;









theApp->Run(kTRUE);
delete theApp;
return 0;
}
