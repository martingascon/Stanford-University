//************** Copyright: Martin Gascon. Stanford University ***************************************
//included libraries
#include "libraries.h" 
#include "functions.h" 


#define N 10000 				       // Número máximo de Datos 
using namespace std;

int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);

gROOT->SetStyle("Plain");
gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);
gStyle->SetOptFit(0);  

Int_t i,k,m; 
char file[100],file2[100],formulae[100],texto1[100],texto2[100];
Float_t x[N],x2[N],ex2[N],y[N],y2[N],ex[N],ey[N],ey2[N],ref=1,dref=0,ref2=1,dref2=0;
Float_t datosx[N],datosx2[N],datosy[N],datosy2[N],errorx[N],errorx2[N],errory[N],errory2[N]; 		      

TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);

TVirtualPad *vp =  c1->cd(1);
vp->SetFillColor(10);
///vp->SetLogx();
vp->SetBorderSize(2);
vp->SetFrameFillColor(0);
vp->SetLeftMargin(.12);
vp->SetRightMargin(.01);
vp->SetBottomMargin(.15);
vp->SetTopMargin(.01);


/* 
TH1F *hr = c1->DrawFrame(0,0.3,350,1.1);      

hr->SetXTitle("Temperature (K)");		// Escribe como titulo del eje x lo que hay en ejex
hr->SetYTitle("Photopeak Channel");   	        // Escribe como titulo del eje y lo que hay en ejey
hr->GetXaxis()->CenterTitle();			// Para centrar el titulo del eje x
hr->GetYaxis()->CenterTitle();			// Para centrar el titulo del eje x	
hr->GetXaxis()->SetLabelColor(1);			
hr->GetYaxis()->SetLabelColor(1);
hr->GetXaxis()->SetMoreLogLabels();
//hr->GetYaxis()->SetMoreLogLabels();
*/
switch (argc)
	{
	case 2: m=sprintf(file,"%s.txt",argv[1]);
		break;
	case 3: m=sprintf(file,"%s.txt",argv[1]);
		m=sprintf(file2,"%s.txt",argv[2]);
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
	i=0;
	while (!in->eof())
		{
		*in >> datosx[i] >> errorx[i] >> datosy[i] >> errory[i] >> datosy2[i] >> errory2[i] ;  
		if (datosx[i]==290) {ref=datosy[i]; dref=errory[i];} //set reference point to normalize to 290K value
		i++;
		
		}
	}
for (k=0;k<i-1;k++)
	{
	x[k]=datosx[k];         
	y[k]=datosy[k]/ref;	//normalize wrt 290K value
	ex[k]=errorx[k];         
	ey[k]=errory[k]/ref;	//normalize error wrt 290K value
	}


TGraphErrors *gr1 = new TGraphErrors(k,x,y,ex,ey);	// Graph declaration
gr1->SetLineColor(2);					
gr1->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
gr1->SetMarkerColor(2);						
gr1->SetMarkerStyle(20);					
//gr1->SetTitle(title);					
gr1->GetXaxis()->SetTitle("Temperature (K)");				
gr1->GetYaxis()->SetTitle("Photopeak Channel");				
	gr1->GetXaxis()->SetTitleSize(0.06);
	gr1->GetYaxis()->SetTitleSize(0.06);
	gr1->GetXaxis()->SetLabelSize(0.05);
	gr1->GetYaxis()->SetLabelSize(0.05);
	gr1->GetXaxis()->CenterTitle();					
	gr1->GetYaxis()->CenterTitle();	
	gr1->Draw("AP");

TLatex *tx1 = new TLatex();
tx1->SetNDC();
tx1->SetTextFont(62);
tx1->SetTextColor(36);
tx1->SetTextAlign(12);
tx1->SetTextSize(0.06);
tx1->SetTextColor(2);
tx1->DrawLatex(0.7,0.8,"serie 1 ");



if (argc==3)
{
	ifstream *in2 = new ifstream(file2);
	if(!*in2) 
		{cout << " ERROR OPENING FILE " <<  file << endl; 
		return 1;
		}
	else    {
		i=0;
		while (!in2->eof())
			{
			*in2 >> datosx2[i] >> errorx2[i] >> datosy2[i] >> errory2[i] ;  
			if (datosx2[i]==290) { ref2=datosy2[i]; dref2=errory2[i]; }
			i++;
			}
		}
	for (k=0;k<i-1;k++)
		{
		x2[k]=datosx2[k];         
		y2[k]=datosy2[k]/ref2;
		ex2[k]=errorx2[k];         
		ey2[k]=errory2[k]/ref2;
		}

TGraphErrors *gr2 = new TGraphErrors(k,x2,y2,ex2,ey2);
gr2->SetMarkerColor(kBlue);
gr2->SetMarkerStyle(20);
gr2->SetMarkerSize(1.5);
gr2->Draw("cpsame");

TF1 *fmott = new TF1("fmott","1/(1+[0]*exp(-[1]/(x*8.6173324e-5)))",120,300); // EXPO + GAUS (5 par)
fmott->SetParameter(0,200);
fmott->SetParameter(1,0.004305);	
fmott->SetLineWidth(3);
fmott->SetLineStyle(9);
fmott->SetLineColor(kGreen+3);
gr2->Fit("fmott","NQR");

Float_t a1,a2;

a1=fmott->GetParameter(0);
a2=fmott->GetParameter(1);
m=sprintf(formulae,"1/(1+%f*exp(-%f/(x*8.6173324e-5)))",a1,a2);

TF1 *fmott2 = new TF1("fmott2",formulae,1,300); // EXPO + GAUS (5 par)
fmott2->SetLineWidth(3);
fmott2->SetLineStyle(9);
fmott2->SetLineColor(kGreen+3);
fmott2->Draw("same");

TLatex *tx2 = new TLatex();
tx2->SetNDC();
tx2->SetTextFont(62);
tx2->SetTextColor(36);
tx2->SetTextAlign(12);
tx2->SetTextSize(0.04);
tx2->SetTextColor(kGreen+3);
tx2->DrawLatex(0.5,0.4,"#eta(T)= [1+#omega_{0}.exp(-#epsilon/#kappaT)]^{-1}");

m=sprintf(texto1,"#omega_{0} = %.2f",a1);
tx2->DrawLatex(0.5,0.3,texto1);

m=sprintf(texto2,"#epsilon = %.3f eV",a2);
tx2->DrawLatex(0.5,0.25,texto2);

TLatex *tf = new TLatex();
tf->SetNDC();
tf->SetTextFont(62);
tf->SetTextColor(36);
tf->SetTextAlign(12);
tf->SetTextSize(0.06);
tf->SetTextColor(kBlue);
tf->DrawLatex(0.7,0.75,"serie 2");

}



//fmott->Draw("same");
	
gStyle->SetOptFit(0);             		
theApp->Run(kTRUE);				
delete theApp;
return 0;
}
