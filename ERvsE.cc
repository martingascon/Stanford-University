//************** Copyright: Martin Gascon. Stanford University ***************************************
//included libraries
#include "libraries.h" 
#include "functions.h" 
#include <math.h> 
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
#define N 10000 				       // Data max number

int main(int argc, char **argv) // argc = integer number of arguments; ** = points to a string; argv = string of parameters
{//********************************** Variables declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);
Float_t x[N],y[N],ex[N],ey[N], datax[N],datay[N],datay2[N],errorx[N],errory[N],errory2[N],d,f; 		      
Int_t i,k,m,a=1,b=1400;  
char fitf[100]="sqrt([0]/x+[1])";
char file1[100],file2[100],file3[100],file4[100],file5[100],file6[100],file7[100];
char latex1[100],latex2[100],latex3[100],latex4[100],latex5[100],latex6[100],latex7[100];

gROOT->SetStyle("Plain"); 
gStyle->SetOptStat(0);    // display stats
gStyle->SetOptFit(0);     // display fit parameters 1 = on, 0 = off

TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);
//c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);
c1->SetLogx(); 
//c1->SetLogy(); 

TH1F *hr = c1->DrawFrame(-100,1,1900,65);      
hr->SetXTitle("Pressure (kpsi)");	
hr->SetYTitle("Energy resolution (%)");   	     
hr->GetXaxis()->CenterTitle();			
hr->GetYaxis()->CenterTitle();				
hr->GetXaxis()->SetMoreLogLabels();		
hr->GetYaxis()->SetMoreLogLabels();	
hr->GetXaxis()->SetLabelColor(1);			
hr->GetYaxis()->SetLabelColor(1);

switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: m=sprintf(file1,"%s.txt",argv[1]);		// FILENAME 	
		break;		

	case 3: m=sprintf(file1,"%s.txt",argv[1]);		// FILENAME 	
		m=sprintf(file2,"%s.txt",argv[2]);	
		break;		
				 
	case 4: m=sprintf(file1,"%s.txt",argv[1]);		// FILENAME REB
		a=atoi(argv[2]);				// A AND B DEFINE THE RANGE TO FIT
		b=atoi(argv[3]);
		break;
	case 5: m=sprintf(file1,"%s.txt",argv[1]);		// FILENAME REB
		m=sprintf(file2,"%s.txt",argv[2]);	
		m=sprintf(file3,"%s.txt",argv[3]);	
		m=sprintf(file4,"%s.txt",argv[4]);	
	case 6: m=sprintf(file1,"%s.txt",argv[1]);		// FILENAME REB
		m=sprintf(file2,"%s.txt",argv[2]);	
		m=sprintf(file3,"%s.txt",argv[3]);	
		m=sprintf(file4,"%s.txt",argv[4]);	
		m=sprintf(file5,"%s.txt",argv[5]);	
		break;
	case 7: m=sprintf(file1,"%s.txt",argv[1]);		// FILENAME REB
		m=sprintf(file2,"%s.txt",argv[2]);	
		m=sprintf(file3,"%s.txt",argv[3]);	
		m=sprintf(file4,"%s.txt",argv[4]);	
		m=sprintf(file5,"%s.txt",argv[5]);		
		m=sprintf(file6,"%s.txt",argv[6]);
		break;
	case 8: m=sprintf(file1,"%s.txt",argv[1]);		// FILENAME REB
		m=sprintf(file2,"%s.txt",argv[2]);	
		m=sprintf(file3,"%s.txt",argv[3]);	
		m=sprintf(file4,"%s.txt",argv[4]);	
		m=sprintf(file5,"%s.txt",argv[5]);
		m=sprintf(file6,"%s.txt",argv[6]);
		m=sprintf(file7,"%s.txt",argv[7]);
		break;
default:
		MsgError();
		exit(1);
		break;
	};   



ifstream *in = new ifstream(file1);
if(!*in) 
	{cout << " ERROR OPENING FILE " <<  file1 << endl; 
	return 1;
	}
else    {
	i=0;
	while (!in->eof())
		{
		*in >> datax[i] >> errorx[i] >> datay[i] >> errory[i] >> datay2[i] >> errory2[i] ;  
		i++;
		}
	}
for (k=0;k<i-1;k++)
	{
	x[k]=datax[k];         
	y[k]=datay2[k];
	ex[k]=errorx[k];         
	ey[k]=errory2[k];
	}

TGraphErrors *gr1 = new TGraphErrors(k,x,y,ex,ey);			// Declaración del gráfico 1.
gr1->SetMarkerColor(kRed);
gr1->SetMarkerStyle(20);
gr1->SetMarkerSize(1.0);
gr1->Draw("p");













TF1 *f1 = new TF1("f1",fitf,a,b); 
f1->SetParameter(0,3);				
f1->SetParameter(1,1);
f1->SetLineColor(kRed);
//gr1->Fit("f1","R+");
cout << "a= " << sqrt(f1->GetParameter(0)) << ", b= " << sqrt(f1->GetParameter(1)) << endl;

TLatex *tx1 = new TLatex();
tx1->SetNDC();
tx1->SetTextSize(0.04);
tx1->SetTextColor(kRed);
char *sepa; sepa= strtok(argv[1],"PhvsE _4us");  sepa= strtok(argv[1],"PhvsE K_4us");	 m=sprintf(latex1,"T = %s K",sepa);
tx1->DrawLatex(0.7,0.85,latex1);
d=f1->GetParameter(0);
d=sqrt(d);
f=f1->GetParameter(1);
f=sqrt(f);
//tx1->SetTextColor(kBlue);
//m=sprintf(latex1,"A = %0.2f ",d);
//tx1->DrawLatex(0.2,0.20,latex1);
//m=sprintf(latex1,"B = %0.2f ",f);
//tx1->DrawLatex(0.2,0.15,latex1);





ifstream *in2 = new ifstream(file2);
if(!*in2) 
	{cout << " ERROR OPENING FILE " <<  file2 << endl; 
	return 1;
	}
else    {
	i=0;
	while (!in2->eof())
		{
		*in2 >> datax[i] >> errorx[i] >> datay[i] >> errory[i] >> datay2[i] >> errory2[i] ;  
		i++;
		}
	}
for (k=0;k<i-1;k++)
	{
	x[k]=datax[k];         
	y[k]=datay2[k];
	ex[k]=errorx[k];         
	ey[k]=errory2[k];
	}

TGraphErrors *gr2 = new TGraphErrors(k,x,y,ex,ey);			// Declaración del gráfico 1.
gr2->SetMarkerColor(kBlue);
gr2->SetMarkerStyle(20);
gr2->SetMarkerSize(1.0);
gr2->Draw("samep");



TF1 *f2 = new TF1("f2",fitf,a,b); 
f2->SetParameter(0,3);				
f2->SetParameter(1,1);
f2->SetLineColor(kRed);
//gr1->Fit("f1","R+");
cout << "a= " << sqrt(f2->GetParameter(0)) << ", b= " << sqrt(f2->GetParameter(1)) << endl;








gStyle->SetOptFit(0);             		        
theApp->Run(kTRUE);				
delete theApp;
return 0;
}
