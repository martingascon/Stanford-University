//************** Copyright: Martin Gascon. Stanford University ***************************************
//included libraries
#include "libraries.h" 
#include "functions.h" 

using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

#define N 10000 				       // Número máximo de data 


int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);
Float_t x[N],y[N],y2[N],ex[N],ey[N],ey2[N];    
Float_t datax[N],datay[N],datay2[N],errorx[N],errory[N],errory2[N],ref=1,dref=0,p0=0,p1=1; 		      
Int_t i,k,m1;  
char file1[100],file2[100],file3[100],file4[100];

gROOT->SetStyle("Bold"); 
TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);
c1->SetFillColor(0);
c1->SetLogx();
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);
 
TH1F *hr = c1->DrawFrame(19,0.98,1900,1.04);      
hr->SetXTitle("Energy photon (keV)");		// Escribe como titulo del eje x lo que hay en ejex
hr->SetYTitle("Relative Light Yield (662 keV)");         // Escribe como titulo del eje y lo que hay en ejey
hr->GetXaxis()->CenterTitle();			// Para centrar el titulo del eje x
hr->GetYaxis()->CenterTitle();			// Para centrar el titulo del eje x	
hr->GetXaxis()->SetLabelColor(1);			
hr->GetYaxis()->SetLabelColor(1);
hr->GetXaxis()->SetMoreLogLabels();


//*********************************** Cuerpo del programa   *************************************
switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;	 
	case 2: m1=sprintf(file1,"%s.txt",argv[1]);		// FILENAME-A FILENAME-B 
		break;
	case 3: m1=sprintf(file1,"%s.txt",argv[1]);		// FILENAME-A FILENAME-B  FILENAME-AB    
		m1=sprintf(file2,"%s.txt",argv[2]);		// FILENAME-A FILENAME-B  FILENAME-AB   
		break;
	case 4: m1=sprintf(file1,"%s.txt",argv[1]);		// FILENAME-A FILENAME-B  FILENAME-AB    
		m1=sprintf(file2,"%s.txt",argv[2]);		// FILENAME-A FILENAME-B  FILENAME-AB   
		m1=sprintf(file3,"%s.txt",argv[3]);		// FILENAME-A FILENAME-B  FILENAME-AB 
		break;
	case 5: m1=sprintf(file1,"%s.txt",argv[1]);		// FILENAME-A FILENAME-B  FILENAME-AB    
		m1=sprintf(file2,"%s.txt",argv[2]);		// FILENAME-A FILENAME-B  FILENAME-AB   
		m1=sprintf(file3,"%s.txt",argv[3]);		// FILENAME-A FILENAME-B  FILENAME-AB 
		m1=sprintf(file4,"%s.txt",argv[4]);		// FILENAME-A FILENAME-B  FILENAME-AB 
		break;


	default:
		MsgError();
		exit(1);
		break;

	};   
   


//factors
/*  
g=25
p0           7.43660e-04   
p1          -2.17196e-07   
p2           2.62968e-11  

g=50 
p0           3.58165e-04   
p1          -5.00505e-08  
p2           2.90891e-12 
  
g=75 
p0           2.42324e-04  
p1          -2.29743e-08  
p2           9.09320e-13  
*/
//for 9K
p0= 5.41453; p1=6.91071;

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
		if (datax[i]==662)   {ref=p1*datax[i]+p0; dref=errorx[i];}      //{ ref=datay[i]; dref=errorx[i];  }  
		i++;
		}
	}
delete in;
for (k=0;k<i-1;k++)
	{
	x[k]=datax[k];         
	y[k]=(p1*datax[k]+p0)/ref*662/datax[k];       //datay[k]/ref*662/datax[k];
	y2[k]=datay2[k];
	ex[k]=errorx[k];         
	ey[k]= 662/datax[k]*(p1*datax[k]+p0)/ref*sqrt((dref/ref)*(dref/ref)+(errory[k]/(p1*datax[k]+p0))*(errory[k]/(p1*datax[k]+p0)));
	//ey[k]= 662/datax[k]*(datay[k])/ref*sqrt((dref/ref)*(dref/ref)+(errory[k]/(datay[k]))*(errory[k]/(datax[k])));
	ey2[k]=errory2[k];
	}

TGraphErrors *gr1 = new TGraphErrors(k,x,y,ex,ey);	
gr1->SetMarkerColor(kRed);
gr1->SetMarkerStyle(21);
gr1->SetMarkerSize(1.5);
gr1->SetLineColor(kRed);
gr1->Draw("cp");				

TLatex *tx1 = new TLatex();
tx1->SetNDC();
tx1->SetTextFont(62);
tx1->SetTextColor(36);
tx1->SetTextAlign(12);
tx1->SetTextSize(0.06);
tx1->SetTextColor(kRed);
tx1->DrawLatex(0.7,0.8,"T = 9K ");




//for 30K
p0= 4.0951; p1=7.04904 ;
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
		if (datax[i]==662) {ref=p1*datax[i]+p0; dref=errorx[i];}
		i++;
		}
	}
delete in2;
for (k=0;k<i-1;k++)
	{
	x[k]=datax[k];         
	y[k]=(p1*datax[k]+p0)/ref*662/datax[k];
	y2[k]=datay2[k];
	ex[k]=errorx[k];         
	ey[k]= 662/datax[k]*(p1*datax[k]+p0)/ref*sqrt((dref/ref)*(dref/ref)+(errory[k]/(p1*datax[k]+p0))*(errory[k]/(p1*datax[k]+p0)));
	ey2[k]=errory2[k];
	}

TGraphErrors *gr2 = new TGraphErrors(k,x,y,ex,ey);	
gr2->SetMarkerColor(kBlue);
gr2->SetMarkerStyle(21);
gr2->SetMarkerSize(1.5);
gr2->SetLineColor(kBlue);
gr2->Draw("cp");				

TLatex *tx2 = new TLatex();
tx2->SetNDC();
tx2->SetTextFont(62);
tx2->SetTextColor(36);
tx2->SetTextAlign(12);
tx2->SetTextSize(0.06);
tx2->SetTextColor(kBlue);
tx2->DrawLatex(0.7,0.75,"T = 30K ");




//for 77K
p0=3.3419 ; p1=7.65051 ;

ifstream *in3 = new ifstream(file3);
if(!*in3) 
	{cout << " ERROR OPENING FILE " <<  file3 << endl; 
	return 1;
	}
else    {
	i=0;
	while (!in3->eof())
		{
		*in3 >> datax[i] >> errorx[i] >> datay[i] >> errory[i] >> datay2[i] >> errory2[i] ;  
		if (datax[i]==662) {ref=p1*datax[i]+p0; dref=errorx[i];}
		i++;
		}
	}
delete in3;
for (k=0;k<i-1;k++)
	{
	x[k]=datax[k];         
	y[k]=(p1*datax[k]+p0)/ref*662/datax[k];
	y2[k]=datay2[k];
	ex[k]=errorx[k];         
	ey[k]= 662/datax[k]*(p1*datax[k]+p0)/ref*sqrt((dref/ref)*(dref/ref)+(errory[k]/(p1*datax[k]+p0))*(errory[k]/(p1*datax[k]+p0)));
	ey2[k]=errory2[k];
	}

TGraphErrors *gr3 = new TGraphErrors(k,x,y,ex,ey);	
gr3->SetMarkerColor(kGreen+3);
gr3->SetMarkerStyle(21);
gr3->SetMarkerSize(1.5);
gr3->SetLineColor(kGreen+3);
gr3->Draw("cp");				

TLatex *tx3 = new TLatex();
tx3->SetNDC();
tx3->SetTextFont(62);
tx3->SetTextColor(36);
tx3->SetTextAlign(12);
tx3->SetTextSize(0.06);
tx3->SetTextColor(kGreen+3);
tx3->DrawLatex(0.7,0.7,"T = 77K ");


//for 287K
p0=2.01138 ; p1=10.235 ;

ifstream *in4 = new ifstream(file4);
if(!*in4) 
	{cout << " ERROR OPENING FILE " <<  file4 << endl; 
	return 1;
	}
else    {
	i=0;
	while (!in4->eof())
		{
		*in4 >> datax[i] >> errorx[i] >> datay[i] >> errory[i] >> datay2[i] >> errory2[i] ;  
		if (datax[i]==662) {ref=p1*datax[i]+p0; dref=errorx[i];}
		i++;
		}
	}
delete in4;
for (k=0;k<i-1;k++)
	{
	x[k]=datax[k];         
	y[k]=(p1*datax[k]+p0)/ref*662/datax[k];
	y2[k]=datay2[k];
	ex[k]=errorx[k];         
	ey[k]= 662/datax[k]*(p1*datax[k]+p0)/ref*sqrt((dref/ref)*(dref/ref)+(errory[k]/(p1*datax[k]+p0))*(errory[k]/(p1*datax[k]+p0)));
	ey2[k]=errory2[k];
	}

TGraphErrors *gr4 = new TGraphErrors(k,x,y,ex,ey);	
gr4->SetMarkerColor(kBlack);
gr4->SetMarkerStyle(21);
gr4->SetMarkerSize(1.5);
gr4->SetLineColor(kBlack);
gr4->Draw("cp");				

TLatex *tx4 = new TLatex();
tx4->SetNDC();
tx4->SetTextFont(62);
tx4->SetTextColor(36);
tx4->SetTextAlign(12);
tx4->SetTextSize(0.06);
tx4->SetTextColor(kBlack);
tx4->DrawLatex(0.7,0.65,"T = 287K ");

gStyle->SetOptFit(0);             		        // Muestro los data del Fit
					// Dibujo la leyenda
theApp->Run(kTRUE);					// Para hacer el ejecutable
delete theApp;
return 0;
}
