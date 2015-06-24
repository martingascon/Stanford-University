//************** Copyright: Martin Gascon. Stanford University ***************************************
//included libraries
#include "libraries.h" 
#include "functions.h" 
#include <math.h> 

#define N 10000 	// Maximum number of data to represent
#define NL 50 		// Number of loops

#define NoG 2 		// Number of gaussian functions to fit
#define FILES 1
#define GRAPH 0
#define FIT 0
#define Elem 3 			// 1: CsI(Tl), 2: LaBr3(Ce), 3: NaI(Tl) 



using namespace std;	//std contains all the classes, objects and functions of the standard C++ library.

int main(int argc, char **argv)
{
// ROOT OPTIONS
TRint *theApp = new TRint("Rint", &argc, argv);
gROOT->SetStyle("Plain");
gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);
gStyle->SetOptFit(0);  


// DECLARATION OF VARIABLES
Float_t x[10][N],y[10][N],xbl,xmin,xmax,em1,em2,in1,in2,aux,area=0; 
Double_t par2[6],parg1[3],parg2[3];

TGraph *gr[10];
Char_t title[100]="title",file1[100],xaxis[100]="Wavelenght (nm)",yaxis[100]="Intensity (a.u.)";
Char_t ley1[100],ley2[100],inte1[100],inte2[100],*sepa,latex1[100];
Char_t fitf[100]= "[0]*exp(-0.5*((x-[1])/[2])*((x-[1])/[2]))+[3]*exp(-0.5*((x-[4])/[5])*((x-[4])/[5]))"; 

//Char_t fitf2[100]= "[0]*exp(-0.5*((x-[1])/[2])*((x-[1])/[2]))";

 
Int_t i,k,m,a,b,c,d;  // for two gaussian and  

switch (Elem)	// FIT REGION DEPENDING ON ELEMENT	
				{
				case 1: // for CsI(Tl)   
					xbl=860;  xmin=366;  xmax=660;  c=370; d=430;  a=430;  b=750;  em1=550; em2=410;  in1=91;   in2=9;
					break;	
				case 2: // for LaBr3	  
					xbl=440;  xmin=320;  xmax=440; 	a=320;  b=360;  c=360;  d=440;  em1=354;  em2=388;  in1=52;  in2=48;
					break;
				case 3: // for NaI		 
					xbl=700;  xmin=320;  xmax=650; 	a=320;  b=360;  c=360;  d=650;  em1=340;  em2=430;  in1=20;  in2=80;
					break;	
				};


   
// OUTPUT FILES
#if FILES
//	ofstream *out1 = new ofstream("WLvsP.txt",ios::app);
	ofstream *out2 = new ofstream("IWLvsP.txt",ios::app);
#endif





TLatex *tx = new TLatex();

TCanvas *c1 = new TCanvas("c1","Graph2D example",200,10,700,500);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);

TVirtualPad *vp =  c1->cd(1);
vp->SetFillColor(10);//vp->SetLogy();
vp->SetBorderSize(2);
vp->SetFrameFillColor(0);
vp->SetLeftMargin(.12);
vp->SetRightMargin(.01);
vp->SetBottomMargin(.15);
vp->SetTopMargin(.01);



switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: m=sprintf(file1,"%s.txt",argv[1]);		// FILENAME TO REPRESENT (XY GRAPHS ONLY)	
		a=(int)(file1[4]- '0')*100+(int)(file1[5]- '0')*10+(int)(file1[6]-'0');
		a=a-16;	b=a+15; c=a+15;	d=a+30;   
		break;		
	case 3: m=sprintf(file1,"%s.txt",argv[1]);                // Filename file columns
		a=atoi(argv[2]);
		a=a-16;			 
		b=a+15;   
		c=a+15;		 
		d=a+30;   
		break;

	case 5: m=sprintf(file1,"%s.txt",argv[1]);                // Filename file columns
		a=atoi(argv[2]);			 
		b=atoi(argv[3]);   
		c=atoi(argv[3]);		 
		d=atoi(argv[4]);   
		break;
	default:
		MsgError();
		exit(1);
		break;
	};   



	
ifstream *in = new ifstream(file1);
if(!*in) {cout << " ERROR OPENING FILE: " <<  file1 << endl; return 1;}
else   Read_2col(file1,x[0],y[0],i);

Float_t bl=0;
y[0][0]=0;
//bl=y[0][2];
 for (k=1;k<i;k++)  if ((x[0][k]>xbl)) {bl=y[0][k];k=i; cout << " BL: " << bl << endl;}
		 


for (k=1;k<i;k++)			
	{
	y[0][k]=y[0][k]-bl;
	if ((x[0][k]>a)&&(x[0][k]<d)) 	area=area+y[0][k];
	}


gr[0] = new TGraph(i-2,x[0],y[0]);		// Graph declaration
gr[0]->SetLineColor(2);					
gr[0]->SetLineWidth(3);						// Line color 0=white 1=black, 2=red
gr[0]->SetMarkerColor(2);					//gr[0]->SetMarkerStyle(20);					
gr[0]->SetTitle(title);					
gr[0]->GetXaxis()->SetTitle(xaxis);				
gr[0]->GetYaxis()->SetTitle(yaxis);				
gr[0]->GetXaxis()->SetTitleSize(0.06);
gr[0]->GetYaxis()->SetTitleSize(0.06);
gr[0]->GetXaxis()->SetLabelSize(0.05);
gr[0]->GetYaxis()->SetLabelSize(0.05);
gr[0]->GetXaxis()->CenterTitle();					
gr[0]->GetYaxis()->CenterTitle();
gr[0]->GetXaxis()->SetRangeUser(200,790);
gr[0]->Draw("AlP");



if (NoG==2)
{  
	TF1 *g1    = new TF1("g1","gaus",a,b);
	TF1 *g2    = new TF1("g2","gaus",c,d);
	gr[0]->Fit(g1,"NQR+");
	g1->GetParameters(&parg1[0]);		
	gr[0]->Fit(g2,"NQR+");
	g2->GetParameters(&parg2[0]);	
	TF1 *f1 = new TF1("f1",fitf,a,d);          		
	f1->SetParameters(parg1[0],parg1[1],parg1[2],parg2[0],parg2[1],parg2[2]); 	
	gr[0]->Fit(f1,"R");
	gr[0]->Fit(f1,"R");
	em1=f1->GetParameter(1);
	em2=f1->GetParameter(4);
	in1=f1->GetParameter(0);
	in2=f1->GetParameter(3);


	aux=in1+in2;
	//in1=in1/aux;
	//in2=in2/aux;
	par2[1]=em1;
	par2[4]=em2;
	m=sprintf(ley1,"Em1 = %.1f nm",par2[0]); 
	m=sprintf(ley2,"Em2 = %.1f nm",par2[3]); 
	m=sprintf(inte1,"%.0f",par2[0]); 
	m=sprintf(inte2,"%.0f",par2[3]); 
	sepa= strtok(argv[1],"NaI_ nm_10ms_1scan_PV_ kpsi"); 
	
	
	
 
	sepa= strtok(argv[1],"LaBr3Ce_300nm_10s_1scan_PV_ kpsi");  
	m=sprintf(latex1,"P = %s GPa",sepa);



	tx->SetNDC(); 
	tx->SetTextFont(62);
	tx->SetTextColor(36);
	tx->SetTextAlign(12);
	tx->SetTextSize(0.05);
	//tx->SetTextColor(2);
	tx->DrawLatex(0.7,0.90,ley1);
	tx->DrawLatex(0.7,0.85,ley2);
	tx->SetTextColor(kRed);
	tx->SetTextSize(0.04);
	tx->DrawLatex(0.7,0.40,latex1);

	//cout << "P" << "\t"  << "0.5" << "\t" << em1 << "\t" << "5" << "\t" << em2 << "\t" << "5"<< endl;
	//cout << "P" << "\t"  << "0.5" << "\t" << in1 << "\t" << "5" << "\t" << in2 << "\t" << "5"<< endl;

	cout << em1 << "\t"  << "0.5" << "\t" << in1   << endl;
	cout << em2 << "\t"  << "0.5" << "\t" << in2   << endl;




#if FILES 
	//*out1 << sepa << "\t"  << "0.5" << "\t" << em1 << "\t" << "5" << "\t" << em2 << "\t" << "5"<< endl;
	//*out2 << sepa << "\t"  << "0.5" << "\t" << in1 << "\t" << "5" << "\t" <<  in2 << "\t" << "5" << endl;
	*out2 << em1 <<  "\t" << in1   << endl;
	*out2 << em2 <<  "\t" << in2   << endl;



#endif

}

				

#if GRAPH
	theApp->Run(kTRUE);						
	delete theApp;
#endif 

return 0;
}
