//included libraries
#include "libraries.h" 
#include "functions.h" 		// ****** Own functions#define FILES 0

#define GRAPH 1

#define N1 30
#define N2 30

int main(int argc, char **argv) // argc = integer number of arguments; ** = points to a string; argv = string of parameters
{
//********************************** Variables declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv); // TRint = type of variable; theApp is name of variable you deine; * is a pointer to one character
gROOT->SetStyle("Plain"); 
gStyle->SetOptStat(0);    // display stats
gStyle->SetOptFit(0);     // display fit parameters 1 = on, 0 = off

Int_t i,j,k,l,m;  
Char_t file[100],file2[100],ci[100]="",tit1[100]; //title is a string with 150 characters   
Float_t datos[N1][N2]; 	

TH2F *hyzero;         


TCanvas *c1 = new TCanvas("c1","Graph2D example",0,0,1400,800);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);
c1->SetTitle("Canvas1");

TVirtualPad *vp1 =  c1->cd();
vp1->SetFillColor(10);
vp1->SetBorderSize(2);
vp1->SetFrameFillColor(0);
vp1->SetLeftMargin(.10);
vp1->SetRightMargin(.15);
vp1->SetBottomMargin(.10);
vp1->SetTopMargin(.10);


switch (argc)
	{
	case 1:	exit(1);
		break;
	case 2: m=sprintf(file,"%s.dat",argv[1]);		// FILENAME 	
		break;						 

	case 3: m=sprintf(file,"%s.dat",argv[1]);		// FILENAME 	
	 	m=sprintf(file2,"%s.dat",argv[2]);	
		break;	


default:
		exit(1);
		break;
	};   


ifstream *in = new ifstream(file);
if(!*in) 
	{cout << " ERROR OPENING FILE " <<  file << endl; 
	}
else    {
	i=1;
	Float_t datos[N1][N2];
	TGraph *gr[N1][N2];
	for (k=0;k<N2;k++)			// I read the data and put them into a matrix
		for (l=0;l<N1;l++)
				{			
				*in >>  ci;               
				datos[k][l]=atof(ci);	 
				}
	delete in;


	c1->cd();
	

	for (k=0;k<N2;k++)			// I read the data and put them into a matrix
		for (l=0;l<N1;l++)
			hyzero->SetBinContent(k+1,l+1,datos[k][l]);
	set_plot_style();
	hyzero->Draw("COLZ");
	hyzero->GetXaxis()->SetLabelSize(0);
	hyzero->GetYaxis()->SetLabelSize(0);
	hyzero->GetXaxis()->SetTickLength(0);
	hyzero->GetYaxis()->SetTickLength(0);
	hyzero->GetXaxis()->SetAxisColor(0);
	hyzero->GetYaxis()->SetAxisColor(0);

	hyzero->Smooth();


	m=sprintf(tit1,"%s_yzero.png",argv[1]);


delete theApp;
return 0;

}
