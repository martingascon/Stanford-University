//************** Copyright: Martin Gascon. Stanford University ******************************************
//This program represent pulses obtained with the Tektronik TDS5000 Oscilloscope 
//included libraries
#include "libraries.h" 
#include "functions.h" 

using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

//************** SETTINGS THAT CAN BE MODIFIED - BEGIN **************************************************

#define N 10000       // Number of points for each pulse (sampling)


//************** SETTINGS THAT CAN BE MODIFIED - END ****************************************************
//**********************************  PROGRAM ***********************************************************

int main(int argc, char **argv)
{
TRint *theApp = new TRint("Rint", &argc, argv);

Float_t x[N],y[N],ynorm[N],Snorm[N],decay=0,dec[10]; 		 
Int_t i,j,k,m,ini=1,fin=10,tot=10,roia=0.4,roib=8,temp=0;  				
char xaxis[100]="time (#mus)",yaxis[100]="voltage (mV)", file[100], file2[100],title[100],legend[100],legend2[100];
char fitf[100]="([0]+[1]*exp(x*[2]))",ci[100];
//char fitf[100]="([0]*exp(x*[1]))";

TCanvas *c = new TCanvas("c","Graph2D example",200,10,1200,700);    //Canvas definition
  c->SetFillColor(10);
  c->SetBorderSize(2);
  c->SetFrameFillColor(0);
  c->SetLogy();

TCanvas *c2 = new TCanvas("c2","Graph2D example",300,10,800,500);    //Canvas definition
  c2->SetFillColor(10);
  c2->SetBorderSize(2);
  c2->SetFrameFillColor(0);
  c2->SetLogy();

gROOT->SetStyle("Plain");          // root options
//gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);
gStyle->SetOptFit(0);
//*********************************** BODY  *************************************
switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: m=sprintf(file,"%s",argv[1]);
		break;
	case 3: m=sprintf(file,"%s",argv[1]);
		ini=atoi(argv[2]);fin=ini;
		break;
	case 4: m=sprintf(file,"%s",argv[1]);
		ini=atoi(argv[2]);fin=atoi(argv[3]);
		break;
	case 5: m=sprintf(file,"%s",argv[1]);
		ini=atoi(argv[2]);fin=atoi(argv[3]);
		temp=atoi(argv[4]); cout << temp << endl;	
		break;
	default:
		MsgError();
		exit(1);
		break;
	};


tot=fin-ini+1;           // total number of pulses 

if (tot<5)             // if the number is <5 divide the canvas in a sigle row
	{
	c->Divide(1,tot);
	}
else
	{
	if (tot<10)
		c->Divide(2,tot/2+1);
	else
		c->Divide(4,tot/4+1);
	}

for (j=ini;j<(fin+1);j++) 	
	{
	m=sprintf(file2,"%s%0.3d.csv",file,j); 
	ifstream *in = new ifstream(file2);
	if(!*in) 
		{
		cout << " ERROR OPENING FILE " <<  file2 << endl; 
		return 1;
		}
	else    
		{
		char *sepa;
		*in >> ci; 
		cout << ci << endl;
		for (i=0;i<N;i++)
			{
			*in >> ci;  
			//cout << ci << endl;
			sepa=strtok(ci,","); k=0;
			//cout << sepa << "=sepa k=" << k << endl;
			while (sepa != NULL)
				{
				if (k==0) x[i]=atof(sepa);
				if (k==1) y[i]=atof(sepa);
				sepa = strtok(NULL,",");
				k++;
				}
			//cout << x[i] << "=x y=" << y[i] << endl;
			}
		}   
	delete in;   	
	Float_t bs=0,aux=0,max=0;                    // I obtain the baseline Baseline 
	for (i=0;i<500;i++)
  		{
  		aux=aux+y[i]*1000;   //previously was 1000     
  		}
	bs=aux/500;

	cout << bs << endl;
/**/	
	for (i=0;i<N;i++)
  		{
  		x[i]=x[i]*1000000;

  		y[i]=-y[i]*1000+bs; //+bs;    //previously was 1000   
		if (max<y[i]) max=y[i];  		
		//cout << x[i] << "=x y=" << y[i] << endl;
		}

	for (i=0;i<N;i++)
  		{
  		ynorm[i]=y[i]/max;  		
		if (j==1) Snorm[i]=ynorm[i];  
		else
			Snorm[i]=Snorm[i]+ynorm[i];
		}
	 
	TGraph *gr1 = new TGraph(N,x,y);	// Graph declaration
	gr1->SetLineColor(4);			// line colour 0=white 1=black, 2=red
	gr1->SetLineWidth(1);			// Line width 
	gr1->SetMarkerColor(4);		
	gr1->SetMarkerStyle(19);		// Styles 19 = dot, 20 = circle, 21 = square
	gr1->GetXaxis()->SetTitle(xaxis);	
	gr1->GetYaxis()->SetTitle(yaxis);	
	gr1->GetXaxis()->CenterTitle();		// to center the title in x axis 
	gr1->GetYaxis()->CenterTitle();
	switch (argc)
		{
		case 2: 
			c2->cd();
			if (j==1) 
				gr1->Draw("AL");
			else
				gr1->SetLineColor(j+3);
				gr1->Draw("Lsame");
			break;
		}		
		
	m=sprintf(title,"Pulse %0.3d",j);
	gr1->SetTitle(title);	
	gr1->SetLineColor(4);
	c->cd(1+(j-ini));			//  
	gr1->Draw("AL");			// Draw A:frame P=dots L=line C=curve	
	TF1 *f1 = new TF1("f1",fitf,roia,roib);                                                 
	f1->SetParameter(0,1);				
	f1->SetParameter(1,2.4);
	f1->SetParameter(2,-0.01);
	f1->SetLineColor(kRed);
	gr1->Fit("f1","R");
	decay=f1->GetParameter(2); // changed..............
	decay=-1/decay;
	dec[j-1]=decay;
	m=sprintf(legend,"#tau= %2.1f #mus",decay);	
	TLatex *tx = new TLatex();
	tx->SetNDC();
	tx->SetTextFont(62);	
	tx->SetTextColor(36);
	tx->SetTextAlign(12);
	tx->SetTextSize(0.06);
	tx->SetTextColor(1);
	tx->DrawLatex(0.45,0.63,legend);
	}
/*
Float_t mean=0,Sx=0;           // Sx Standard deviation
for (i=0;i<10;i++)
 	{
	mean=mean+dec[i];
        }
mean=mean/10;

for (i=0;i<10;i++)
 	{
	Sx=Sx+sqrt(0.1*(dec[i]-mean)*(dec[i]-mean)) ;
        }



c->cd(11);
Float_t decerror=0;
TGraph *gr2 = new TGraph(N,x,Snorm);	// Graph declaration
gr2->SetLineColor(4);			// line colour 0=white 1=black, 2=red
gr2->SetLineWidth(1);			// Line width 
gr2->SetMarkerColor(4);		
gr2->SetMarkerStyle(19);		// Styles 19 = dot, 20 = circle, 21 = square
gr2->GetXaxis()->SetTitle(xaxis);	
gr2->GetYaxis()->SetTitle("Normalized Amplitude");	
gr2->GetXaxis()->CenterTitle();		// to center the title in x axis 
gr2->GetYaxis()->CenterTitle();
m=sprintf(title,"Added Pulses");
gr2->SetTitle(title);	
gr2->Draw("AL");	
TF1 *f2 = new TF1("f2",fitf,roia,roib); 
f2->SetParameter(0,1);				
f2->SetParameter(1,2.45);
f2->SetParameter(2,-0.01);
f2->SetLineColor(kRed);
gr2->Fit("f2","R");
decay=f2->GetParameter(2);
decerror=f2->GetParError(2);
cout << decerror << endl;
decay=-1/decay;
m=sprintf(legend,"#tau= %2.1f #mus",decay);
TLatex *tx2 = new TLatex();	
tx2->SetNDC();
tx2->SetTextFont(62);	
tx2->SetTextColor(36);
tx2->SetTextAlign(12);
tx2->SetTextSize(0.06);
tx2->SetTextColor(1);
tx2->DrawLatex(0.45,0.63,legend);

c->cd(12);
TLatex *tx = new TLatex();
tx->SetNDC();
tx->SetTextFont(62);	
tx->SetTextColor(36);
tx->SetTextAlign(12);
tx->SetTextSize(0.09);
tx->SetTextColor(1);
m=sprintf(legend2,"TEMP = %d K",temp);
tx->DrawLatex(0.25,0.73,legend2);
m=sprintf(legend,"#tau(ave)= (%2.2f #pm %2.2f) #mus",mean,Sx);
tx->DrawLatex(0.15,0.53,legend);
m=sprintf(legend,"#tau(nor)= (%2.5f #pm %2.5f) #mus",decay,decerror);
tx->DrawLatex(0.05,0.38,legend);

c2->cd(0);
*/
//ofstream *out = new ofstream("../../analysis/TauVsTemp.txt",ios::app);
//*out << temp << " " << 5 << " " << mean << " " << Sx  << endl;

theApp->Run(kTRUE);			// makes the executable
delete theApp;
return 0;


}
