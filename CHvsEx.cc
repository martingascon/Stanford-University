//************** Copyright: Martin Gascon. Stanford University ***************************************
//included libraries
#include "libraries.h" 
#include "functions.h" 


#define N 10000 				       // Declare maximum number of data
using namespace std;

int main(int argc, char **argv)
{
//********************************** Declare variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);

Int_t i,k,m; 
char file[100],serie1[100]="Title of Series 1",serie2[100]="Title of Series 2";// declare legend
//fitf[100]="expo"; 	
Float_t x[N],y[N],y2[N],ex[N],ey[N],ey2[N],mins1,maxs1,mins2,maxs2;    
Float_t datosx[N],datosy[N],datosy2[N],errorx[N],errory[N],errory2[N]; 		      

gROOT->SetStyle("Bold"); 
TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);
c1->SetFillColor(0);
c1->SetLogx();
c1->SetLogy();
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);

char inputFile0[250] = "PhvsE9K.txt";
char inputFile1[250] = "PhvsE30K.txt";
char inputFile2[250] = "PhvsE77K.txt";
char inputFile3[250] = "PhvsE180K.txt";
char inputFile4[250] = "PhvsE287K.txt";

TH1F *hr = c1->DrawFrame(26,150,1000,16000);   //histogram graph, useful for multiple data sets being plotted (has to do with scaling)   

hr->SetXTitle("Photon Energy (keV)");		// Escribe como titulo del eje x lo que hay en ejex
hr->SetYTitle("Photopeak Channel");   	        // Escribe como titulo del eje y lo que hay en ejey
hr->GetXaxis()->CenterTitle();			// Para centrar el titulo del eje x
hr->GetYaxis()->CenterTitle();			// Para centrar el titulo del eje x	
hr->GetXaxis()->SetLabelColor(1);			
hr->GetYaxis()->SetLabelColor(1);
hr->GetXaxis()->SetMoreLogLabels();
//hr->GetYaxis()->SetMoreLogLabels();

	switch (argc)
		{
		case 1:	break;
		
		default:
			MsgError();
			exit(1);
			break;
		};


TF1 *f1 = new TF1("f1","pol1",30,400); 
f1->SetLineColor(kBlack);

ifstream *in = new ifstream(inputFile0);
Read_6col(inputFile0, x, ex, y, ey, y2, ey2, k);
TGraphErrors *gr1 = new TGraphErrors(k-1,x,y,ex,ey);
gr1->SetMarkerColor(kRed);
gr1->SetMarkerStyle(20);
gr1->SetMarkerSize(1.0);
gr1->Draw("p");			
gr1->Fit("f1","NQR");

TF1 *f1b = new TF1("f1b","[0]+x*[1]",30,1200); 
f1b->SetLineColor(kRed);
Float_t a,b;
a=f1->GetParameter(0);
b=f1->GetParameter(1);
f1b->SetParameter(0,a);
f1b->SetParameter(1,b);
f1b->Draw("same");


ifstream *in2 = new ifstream(inputFile1);
Read_6col(inputFile1, x, ex, y, ey, y2, ey2, k);
TGraphErrors *gr2 = new TGraphErrors(k-1,x,y,ex,ey);
gr2->SetMarkerColor(kBlue);
gr2->SetMarkerStyle(20);
gr2->SetMarkerSize(1.0);
gr2->Draw("psame");			
gr2->Fit("f1","NQR");
TF1 *f2 = new TF1("f2","[0]+x*[1]",30,1200); 
f2->SetLineColor(kBlue);
a=f1->GetParameter(0);
b=f1->GetParameter(1);
f2->SetParameter(0,a);
f2->SetParameter(1,b);
f2->Draw("same");

ifstream *in3 = new ifstream(inputFile2);
Read_6col(inputFile2, x, ex, y, ey, y2, ey2, k);
TGraphErrors *gr3 = new TGraphErrors(k-1,x,y,ex,ey);
gr3->SetMarkerColor(kGreen+3);
gr3->SetMarkerStyle(20);
gr3->SetMarkerSize(1.0);
gr3->Draw("psame");	
gr3->Fit("f1","NQR");
TF1 *f3 = new TF1("f3","[0]+x*[1]",30,1200); 
f3->SetLineColor(kGreen+3);
a=f1->GetParameter(0);
b=f1->GetParameter(1);
f3->SetParameter(0,a);
f3->SetParameter(1,b);
f3->Draw("same");

ifstream *in4 = new ifstream(inputFile3);
Read_6col(inputFile3, x, ex, y, ey, y2, ey2, k);
TGraphErrors *gr4 = new TGraphErrors(k-1,x,y,ex,ey);
gr4->SetMarkerColor(kBlack);
gr4->SetMarkerStyle(20);
gr4->SetMarkerSize(1.0);
gr4->Draw("psame");	
gr4->Fit("f1","NQR");
TF1 *f4 = new TF1("f4","[0]+x*[1]",30,1200); 
f4->SetLineColor(kBlack);
a=f1->GetParameter(0);
b=f1->GetParameter(1);
f4->SetParameter(0,a);
f4->SetParameter(1,b);
f4->Draw("same");


ifstream *in5 = new ifstream(inputFile4);
Read_6col(inputFile4, x, ex, y, ey, y2, ey2, k);
TGraphErrors *gr5 = new TGraphErrors(k-1,x,y,ex,ey);
gr5->SetMarkerColor(kMagenta);
gr5->SetMarkerStyle(20);
gr5->SetMarkerSize(1.0);
gr5->Draw("psame");	
gr5->Fit("f1","NQR+");
TF1 *f5 = new TF1("f5","[0]+x*[1]",30,1200); 
f5->SetLineColor(616);
a=f1->GetParameter(0);
b=f1->GetParameter(1);
f5->SetParameter(0,a);
f5->SetParameter(1,b);
f5->Draw("same");

PrintLatex("T = 9K  ",1,2,1);  // (text, position 1=top left, 2= top right, 3= bottom left, 4 bottom right, color, number of entry)
PrintLatex("T = 30K ",1,4,2);  // (text, position 1=top left, 2= top right, 3= bottom left, 4 bottom right, color, number of entry)
PrintLatex("T = 77K ",1,419,3);  // (text, position 1=top left, 2= top right, 3= bottom left, 4 bottom right, color, number of entry)
PrintLatex("T = 180K",1,1,4);  // (text, position 1=top left, 2= top right, 3= bottom left, 4 bottom right, color, number of entry)
PrintLatex("T = 287K",1,616,5);  // (text, position 1=top left, 2= top right, 3= bottom left, 4 bottom right, color, number of entry)

gROOT->SetStyle("Plain"); 
gStyle->SetOptStat(0);    // display stats
gStyle->SetOptFit(0);     // display fit parameters 1 = on, 0 = off

theApp->Run(kTRUE);					// To make the executable
delete theApp;
return 0;
}
