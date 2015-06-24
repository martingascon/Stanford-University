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
Float_t x[N],y[N],y2[N],y3[N],ex[N],ey[N],ey2[N],ey3[N];    
Int_t i,m1;  
char file1[100];

gROOT->SetStyle("Bold"); 
TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);
c1->SetFillColor(0);
//c1->SetLogx();
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);
 
TH1F *hr = c1->DrawFrame(19,0.,8192,1.1);      
hr->SetXTitle("Photopeak Channel");		// Escribe como titulo del eje x lo que hay en ejex
hr->SetYTitle("Correction factor");         // Escribe como titulo del eje y lo que hay en ejey
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
		*in >> x[i] >> ex[i] >> y[i] >> ey[i] >> y2[i] >> ey2[i] >> y3[i] >> ey3[i];  	
		i++;
		}
	}
delete in;

char fitf[100]="pol2*x";
//char fitf[100] = "TMath::Log(x*[0])"; 
TF1 *f1 = new TF1("f1",fitf,25,3500); 
f1->SetLineColor(2);


TGraphErrors *gr1 = new TGraphErrors(i,y,x,ey,ex);	
gr1->SetMarkerColor(kRed);
gr1->SetMarkerStyle(21);
gr1->SetMarkerSize(1.5);
gr1->SetLineColor(kRed);
gr1->Draw("p");				
gr1->Fit("f1","R");

TLatex *tx1 = new TLatex();
tx1->SetNDC();
tx1->SetTextFont(62);
tx1->SetTextColor(36);
tx1->SetTextAlign(12);
tx1->SetTextSize(0.06);
tx1->SetTextColor(kRed);
tx1->DrawLatex(0.7,0.4,"G = 25 ");

TF1 *f2 = new TF1("f2",fitf,25,6700); 
f2->SetLineColor(kBlue);

TGraphErrors *gr2 = new TGraphErrors(i,y2,x,ey2,ex);	
gr2->SetMarkerColor(kBlue);
gr2->SetMarkerStyle(21);
gr2->SetMarkerSize(1.5);
gr2->SetLineColor(kBlue);
gr2->Draw("p");				
gr2->Fit("f2","R");

TLatex *tx2 = new TLatex();
tx2->SetNDC();
tx2->SetTextFont(62);
tx2->SetTextColor(36);
tx2->SetTextAlign(12);
tx2->SetTextSize(0.06);
tx2->SetTextColor(kBlue);
tx2->DrawLatex(0.7,0.35,"G = 50 ");

TF1 *f3 = new TF1("f3",fitf,25,9400); 
f3->SetLineColor(kGreen+3);

TGraphErrors *gr3 = new TGraphErrors(i,y3,x,ey3,ex);	
gr3->SetMarkerColor(kGreen+3);
gr3->SetMarkerStyle(21);
gr3->SetMarkerSize(1.5);
gr3->SetLineColor(kGreen+3);
gr3->Draw("p");				
gr3->Fit("f3","R");

TLatex *tx3 = new TLatex();
tx3->SetNDC();
tx3->SetTextFont(62);
tx3->SetTextColor(36);
tx3->SetTextAlign(12);
tx3->SetTextSize(0.06);
tx3->SetTextColor(kGreen+3);
tx3->DrawLatex(0.7,0.3,"G = 75 ");







//gStyle->SetOptFit(0);             		        // Muestro los data del Fit
					// Dibujo la leyenda
theApp->Run(kTRUE);					// Para hacer el ejecutable
delete theApp;
return 0;
}
