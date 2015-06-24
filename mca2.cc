//************** Copyright: Martin Gascon. Stanford University ***************************************
//included libraries
#include "libraries.h" 
#include "functions.h" 
#include <math.h> 


using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

int main(int argc, char **argv) // argc = integer number of arguments; ** = points to a string; argv = string of parameters
{
//********************************** Variables declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv); // TRint = type of variable; theApp is name of variable you deine; * is a pointer to one character
Int_t k,m,m1,reb=1,N=8192;  
Float_t data[N],x[N],y[N]; //[n] refers to a vector 		      
char file1[100],file2[100],file3[100],file4[100],file5[100],file6[100],file7[100];
char latex1[100],latex2[100],latex3[100],latex4[100],latex5[100],latex6[100],latex7[100],title[100]="";


gROOT->SetStyle("Plain"); 
gStyle->SetOptStat(0);    // display stats
gStyle->SetOptFit(0);     // display fit parameters 1 = on, 0 = off



switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: m=sprintf(file1,"%s.mca",argv[1]);		// FILENAME 	
		break;						 
	case 3: m=sprintf(file1,"%s.mca",argv[1]);		// FILENAME REB
		m=sprintf(file2,"%s.mca",argv[2]);
		break;
	case 4: m=sprintf(file1,"%s.mca",argv[1]);		// FILENAME REB
		m=sprintf(file2,"%s.mca",argv[2]);
		m=sprintf(file3,"%s.mca",argv[3]);
		break;
	case 5: m=sprintf(file1,"%s.mca",argv[1]);		// FILENAME REB
		m=sprintf(file2,"%s.mca",argv[2]);
		m=sprintf(file3,"%s.mca",argv[3]);
		m=sprintf(file4,"%s.mca",argv[4]);
		break;
	case 6: m=sprintf(file1,"%s.mca",argv[1]);		// FILENAME REB
		m=sprintf(file2,"%s.mca",argv[2]);
		m=sprintf(file3,"%s.mca",argv[3]);
		m=sprintf(file4,"%s.mca",argv[4]);
		m=sprintf(file5,"%s.mca",argv[5]);
		break;
	case 7: m=sprintf(file1,"%s.mca",argv[1]);		// FILENAME REB
		m=sprintf(file2,"%s.mca",argv[2]);
		m=sprintf(file3,"%s.mca",argv[3]);
		m=sprintf(file4,"%s.mca",argv[4]);	
		m=sprintf(file5,"%s.mca",argv[5]);
		m=sprintf(file6,"%s.mca",argv[6]);
		break;
	case 8: m=sprintf(file1,"%s.mca",argv[1]);		// FILENAME REB
		m=sprintf(file2,"%s.mca",argv[2]);
		m=sprintf(file3,"%s.mca",argv[3]);
		m=sprintf(file4,"%s.mca",argv[4]);	
		m=sprintf(file5,"%s.mca",argv[5]);
		m=sprintf(file6,"%s.mca",argv[6]);
		m=sprintf(file7,"%s.mca",argv[7]);
		break;
default:
		MsgError();
		exit(1);
		break;

	};   

Read_MCA(file1, data,N);

TH1I *H = new TH1I("H",file1,N,0,N-1);  // declaration of the histogram	 
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
H->Rebin(reb);
H->Draw();
TLatex *tx1 = new TLatex();
tx1->SetNDC();
tx1->SetTextSize(0.04);
tx1->SetTextColor(kRed);
m1=sprintf(latex1,"%s",argv[1]);
tx1->DrawLatex(0.5,0.85,latex1);


if (argc>2)
	{
	Read_MCA(file2, data,N);
	TH1I *H2 = new TH1I("H2",file2,N,0,N-1);  // declaration of the histogram	
	H2->SetFillColor(0);
	H2->SetLineColor(kBlue);
	H2->SetLineWidth(2);
	H2->SetMarkerStyle(8);
	H2->SetMarkerSize(1); 

	for (k=0;k<N;k++)			
		{
		x[k]=k;                 
		y[k]=data[k];
		H2->Fill(x[k],y[k]);		// fill the histogram
		}
	H2->Draw("same");
	TLatex *tx2 = new TLatex();
	tx2->SetNDC();
	tx2->SetTextSize(0.04);
	tx2->SetTextColor(kBlue);
	m1=sprintf(latex2,"%s",argv[2]);
	tx2->DrawLatex(0.5,0.80,latex2);
	}



if (argc>3)
	{
	Read_MCA(file3, data,N);
	TH1I *H3 = new TH1I("H3",file3,N,0,N-1);  // declaration of the histogram	
	H3->SetFillColor(0);
	H3->SetLineColor(kGreen+3);
	H3->SetLineWidth(2);
	H3->SetMarkerStyle(8);
	H3->SetMarkerSize(1); 

	for (k=0;k<N;k++)			
		{
		x[k]=k;                 
		y[k]=data[k];
		H3->Fill(x[k],y[k]);		// fill the histogram
		}
	H3->Draw("same");
	TLatex *tx3 = new TLatex();
	tx3->SetNDC();
	tx3->SetTextSize(0.04);
	tx3->SetTextColor(kGreen+3);
	m1=sprintf(latex3,"%s",argv[3]);
	tx3->DrawLatex(0.5,0.75,latex3);
	}



if (argc>4)
	{
	Read_MCA(file4, data,N);
	TH1I *H4 = new TH1I("H4",file4,N,0,N-1);  // declaration of the histogram	
	H4->SetFillColor(0);
	H4->SetLineColor(kBlack);
	H4->SetLineWidth(2);
	H4->SetMarkerStyle(8);
	H4->SetMarkerSize(1); 
	for (k=0;k<N;k++)			
		{
		x[k]=k;                 
		y[k]=data[k];
		H4->Fill(x[k],y[k]);		// fill the histogram
		}
	H4->Draw("same");
	TLatex *tx4 = new TLatex();
	tx4->SetNDC();
	tx4->SetTextSize(0.04);
	tx4->SetTextColor(kBlack);
	m1=sprintf(latex4,"%s",argv[4]);
	tx4->DrawLatex(0.5,0.70,latex4);
	}

if (argc>5)
	{
	Read_MCA(file5, data,N);
	TH1I *H5 = new TH1I("H5",file5,N,0,N-1);  // declaration of the histogram	
	H5->SetFillColor(0);
	H5->SetLineColor(kMagenta);
	H5->SetLineWidth(2);
	H5->SetMarkerStyle(8);
	H5->SetMarkerSize(1); 
	for (k=0;k<N;k++)			
		{
		x[k]=k;                 
		y[k]=data[k];
		H5->Fill(x[k],y[k]);		// fill the histogram
		}
	H5->Draw("same");
	TLatex *tx5 = new TLatex();
	tx5->SetNDC();
	tx5->SetTextSize(0.04);
	tx5->SetTextColor(kMagenta);
	m1=sprintf(latex5,"%s",argv[5]);
	tx5->DrawLatex(0.5,0.65,latex5);
	}


if (argc>6)
	{
	Read_MCA(file6, data,N);
	TH1I *H6 = new TH1I("H6",file6,N,0,N-1);  // declaration of the histogram	
	H6->SetFillColor(0);
	H6->SetLineColor(kYellow-5);
	H6->SetLineWidth(2);
	H6->SetMarkerStyle(8);
	H6->SetMarkerSize(1); 
	for (k=0;k<N;k++)			
		{
		x[k]=k;                 
		y[k]=data[k];
		H6->Fill(x[k],y[k]);		// fill the histogram
		}
	H6->Draw("same");
	TLatex *tx6 = new TLatex();
	tx6->SetNDC();
	tx6->SetTextSize(0.04);
	tx6->SetTextColor(kYellow-5);
	m1=sprintf(latex6,"%s",argv[6]);
	tx6->DrawLatex(0.5,0.60,latex6);
	}


if (argc>7)
	{
	Read_MCA(file7, data,N);
	TH1I *H7 = new TH1I("H7",file7,N,0,N-1);  // declaration of the histogram	
	H7->SetFillColor(0);
	H7->SetLineColor(kOrange);
	H7->SetLineWidth(2);
	H7->SetMarkerStyle(8);
	H7->SetMarkerSize(1); 
	for (k=0;k<N;k++)			
		{
		x[k]=k;                 
		y[k]=data[k];
		H7->Fill(x[k],y[k]);		// fill the histogram
		}
	H7->Draw("same");
	TLatex *tx7 = new TLatex();
	tx7->SetNDC();
	tx7->SetTextSize(0.04);
	tx7->SetTextColor(kOrange);
	m1=sprintf(latex7,"%s",argv[7]);
	tx7->DrawLatex(0.5,0.55,latex7);
	}




gStyle->SetOptStat(0);    // display stats
gStyle->SetOptFit(0);     // display fit parameters 1 = on, 0 = off


theApp->Run(kTRUE);
delete theApp;
return 0;
}
