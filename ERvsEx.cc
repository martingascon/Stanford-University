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
TStyle *MyStyle = new TStyle("Legenda","leyenda");
Float_t x[N],y[N],y2[N],ex[N],ey[N],ey2[N];    
Float_t datosx[N],datosy[N],datosy2[N],errorx[N],errory[N],errory2[N],d,e,f,g,h,o1,o2,o3,pra,prb; 		      
Int_t i,j,k,l,xini,tim,oldtim,m,m1,m2;  
char titulo[100]="titulo",file1[100],file2[100], file3[100], file4[100],serie1[100]="serie 1",serie2[100]="serie 2";
char fitf[100]="([0]/sqrt(x) )",ar[100],ar2[100];//)"
gROOT->SetStyle("Bold"); 
TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);
 
TH1F *hr = c1->DrawFrame(0,0,1500,35);      
hr->SetXTitle("Energy photon (keV)");	// Escribe como titulo del eje x lo que hay en ejex
hr->SetYTitle("Energy resolution (%)");   	        // Escribe como titulo del eje y lo que hay en ejey
hr->GetXaxis()->CenterTitle();			// Para centrar el titulo del eje x
hr->GetYaxis()->CenterTitle();			// Para centrar el titulo del eje x	
hr->GetXaxis()->SetLabelColor(1);			
hr->GetYaxis()->SetLabelColor(1);



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







ifstream *in = new ifstream(file1);
if(!*in) 
	{cout << " ERROR OPENING FILE " <<  file1 << endl; 
	return 1;
	}
else    {
	i=0;
	while (!in->eof())
		{
		*in >> datosx[i] >> errorx[i] >> datosy[i] >> errory[i] >> datosy2[i] >> errory2[i] ;  
		i++;
		}
	}
for (k=0;k<i-1;k++)
	{
	x[k]=datosx[k];         
	y[k]=datosy[k];
	y2[k]=datosy2[k];
	ex[k]=errorx[k];         
	ey[k]=errory[k];
	ey2[k]=errory2[k];
	}


TGraphErrors *gr1 = new TGraphErrors(k,x,y,ex2,ey2);			// Declaración del gráfico 1.
TF1 *f1 = new TF1("f1",fitf,30,1400); 
f1->SetParameter(0,3);				

gr1->SetMarkerColor(kBlue);
gr1->SetMarkerStyle(22);
gr1->SetMarkerSize(1.5);
gr1->Draw("p");					// Pinta el gráfico A:marco P=puntos L=linea C=curva


gr1->Fit("f1","R+");
d=f1->GetParameter(0);
f=f1->GetParError(0);
gr2->Fit("f2","R+");
e=f2->GetParameter(0);
h=f2->GetParError(0);

TLegend *legend=new TLegend(0.54,0.71,0.89,0.86);	// Declaración de la leyenda
TLegend *legend2=new TLegend(0.19,0.2,0.57,0.34);

legend->SetTextFont(72);				// Tipo de fuente de la leyenda
legend->SetTextSize(0.04);				// Tamaño de la fuente de la leyenda
legend->AddEntry(gr1,serie1,"p");
//legend->AddEntry(gr2,serie2,"p");
//m=sprintf(ar,"#delta = (%.2f #pm %.2f) %%",d*100,f*100);//,d,e);
m1=sprintf(ar2,"E.R. = (%.1f #pm %.1f) % @ 662 keV",e/25.729360661,h/25.729360661);//,d,e);


legend2->AddEntry(gr1,ar,"p");				// Añado entrada a la leyenda
legend2->AddEntry(gr2,ar2,"p");

gStyle->SetOptFit(0);             		        // Muestro los datos del Fit
legend->Draw();	
legend2->Draw();						// Dibujo la leyenda
theApp->Run(kTRUE);					// Para hacer el ejecutable
delete theApp;
return 0;
}
