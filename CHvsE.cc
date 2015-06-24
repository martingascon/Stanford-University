//************** Copyright: Martin Gascon. Stanford University ***************************************
//included libraries
#include "libraries.h" 
#include "functions.h" 

#define N 10000 				       // Max number of data points
using namespace std;

int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);

Int_t i,k,m; 
char file[100],serie1[100]="Title of series 1",serie2[100]="Title of series 2"; 	//legend
Float_t x[N],y[N],y2[N],ex[N],ey[N],ey2[N],mins1,maxs1,mins2,maxs2;    
Float_t datosx[N],datosy[N],datosy2[N],errorx[N],errory[N],errory2[N]; 		      
//char fitf[100]="pol1";
char fitf[100]="[0]-[1]*log(x)"; // defines fitting function used for this set of data where [0] and [1] are the coefficients

gROOT->SetStyle("Bold"); 
TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);
c1->SetFillColor(0);
//c1->SetLogx();
//c1->SetLogy();
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);
 
TH1F *hr = c1->DrawFrame(-0.5,90,1600,8000);      

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
		case 2: m=sprintf(file,"%s.txt",argv[1]);	//stop program if you only have 1 argument
			break;
		case 4: m=sprintf(file,"%s.txt",argv[1]);
			m=sprintf(serie1,"%s",argv[2]);
			m=sprintf(serie2,"%s",argv[3]);
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
	while (!in->eof())	//continue reading if you haven't reached the end of the file
		{
		*in >> datosx[i] >> errorx[i] >> datosy[i] >> errory[i] >> datosy2[i] >> errory2[i] ;  //reading each horizontal line at a time
		i++;
		}
	}
for (k=0;k<i-1;k++)	//assign data values into a separate place to work with them
	{
	
	x[k]=datosx[k];         
	y[k]=datosy[k];
	y2[k]=datosy2[k];
	ex[k]=errorx[k];         
	ey[k]=errory[k];
	ey2[k]=errory2[k];
	}



TGraphErrors *gr1 = new TGraphErrors(k,x,y,ex,ey); // Graph with error bars
TF1 *f1 = new TF1("f1",fitf,1,20); // TF1 is a 1-D function ; if you use fitf, you are using function defined above (custom); you can fit with "gaus" or "pol0", "pol1", "pol2", etc. (built in to root); you can also do fits after you've generated the plot by right clicking on it.

//f1 refers to fitting function
f1->SetLineColor(kRed); //see tables for numbers and associated colors and codes
f1->SetParameter(0,7000);        // for first coefficient, [0], first guess for fit is 7000				
f1->SetParameter(1,4000);         // for 2nd coefficient, [1], first guess for fit is 4000

//gr1 refers to graph
gr1->SetMarkerColor(kBlack);
gr1->SetMarkerStyle(20); //marker shapes
gr1->SetMarkerSize(1.5); //marker size
gr1->Draw("p");		// graph styles: p is datapoints only, cp is curve and points, lp is line and points	
gr1->Fit("f1","R+");	//fit data points in graph with function f1; R+ means open range (defined by f1 from above, i.e. 1,20)


TLatex *tx1 = new TLatex();             // defines a legend (TLatex)
tx1->SetNDC();				// define coodinates normalized from 0 to 1
tx1->SetTextFont(62);			// defines font
tx1->SetTextColor(36);			// defines text colour
tx1->SetTextAlign(12);			// defines text aling 
tx1->SetTextSize(0.06);			// defines size of the text
tx1->SetTextColor(1);			// 
tx1->DrawLatex(0.3,0.8,"T = xK ");	// position of legend


gStyle->SetOptFit(0);					// don't show fit info
theApp->Run(kTRUE);					// make the executalbe
delete theApp;
return 0;
}



