//************** Copyright: Martin Gascon. Stanford University ***************************************
//Este programa representa un pulso del osciloscopio YOKOGAWA DL 6154 
//included libraries    

#include "libraries.h" 
#include "functions.h" 

using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.


#define N 2500				       // maximum number of data per pulse
using namespace std;

int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);

Float_t datosy[N],x[N],y[N],ysum[N],sum[N],d,e,f,g,h,l; 		
Int_t i,j,m,pulso,ini=0,fin=0,tot=0,a=0,b=200;  			
char title[100]="", xaxis[100]="time (#mus)",yaxis[100]="voltage (mV)";
char file[100], ci[100]="",bq[100]="",ar[100],expo1[100],expo2[100];
//char fitf[100]="([0]*exp(-(x-[4])/[1])+[2]*exp(-(x-[4])/[3]))";//)"       
//char fitf[100]="([0]*exp((x-[6])/[1])+[2]*exp(-(x-[6])/[3])+[4]*exp(-(x-[6])/[5]))";//)" 
 char fitf[100]="([0]*exp(-(x-[2])*[1]))";//)"  // for LSO:Ce


TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,1000,600);   
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);

gROOT->SetStyle("Plain");
//gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);
gStyle->SetOptFit(0);  


switch (argc)		
	{
	case 1: MsgError();
		exit(1);
		break;	
	case 2: m=sprintf(file,"%s.csv",argv[1]);
		break;
	case 3: m=sprintf(file,"%s.csv",argv[1]);
		ini=atoi(argv[2]);fin=ini;
		break;
	case 4: m=sprintf(file,"%s.csv",argv[1]);
		ini=atoi(argv[2]);fin=atoi(argv[3]);
		break;		

	case 6: m=sprintf(file,"%s.csv",argv[1]);
		ini=atoi(argv[2]);fin=atoi(argv[3]);
		a=atoi(argv[4]);b=atoi(argv[5]);	
		break;	

       	default:
		MsgError();
		exit(1);
		break;
	};

tot=fin-ini;
if (tot<5)
	{
	c1->Divide(1,(tot+1));
	}
else
	{
	if (tot<10)
		c1->Divide(2,tot/2+1);
	else
		c1->Divide(4,tot/4+1);
	}
pulso=atoi(argv[1]);

ifstream *in = new ifstream(file);
char *sepa;
Int_t k;
Float_t HRes0=0,HRes1=0,HRes=0,HOff=0,HOff1=0;
m=sprintf(bq,"block%s",argv[2]);
cout << bq << endl;
for (i=0;i<N;i++) ysum[i]=0;
if(!*in){
	cout << " ERROR OPENING FILE " <<  file << endl; 
	return 1;
	}
else    {	
		
	do	{
		*in >> ci;
		i=1;		
		if ((strstr(ci,bq)!=NULL))	// until it find blockXX, being XX the pulse number
			{
			i=0;cout << ci << endl;
			}
	
		if ((strstr(ci,"HResolution,")!=NULL))	// to find the horizontal resolution
			{
			sepa=strtok(ci,"HResolution,"); k=0;
			while (sepa != NULL)			
				{
				if (k==0) HRes0=atof(sepa); 
				if (k==1) HRes1=atof(sepa);
				sepa = strtok(NULL,",");
				k++;
				}
			HRes=HRes0*TMath::Power(10,HRes1);
			cout << " Horizontal resolution: "<< HRes << endl;
			}
		if ((strstr(ci,"HOffset,")!=NULL))	// to find the horizontal offset
			{
			sepa=strtok(ci,"HOffset,"); k=0;
			while (sepa != NULL)			
				{
				if (k==0) HOff=atof(sepa); 
				if (k==1) HOff1=atof(sepa);
				sepa = strtok(NULL,",");
				k++;
				}
			HOff=HOff*TMath::Power(10,HOff1);	
			cout << " Horizontal Offset: "<< HOff << endl;
			}		

		}
	while (i!=0);   ///////////////////////////////////////////// read the first lines until it find block
	for (j=ini;j<(fin+1);j++) 	
		{
		*in >> ci; //  cout << ci << endl;
		for (i=0;i<N-1;i++)
 			{
			*in >> ci; 
			sepa=strtok(ci,","); k=0;
			//cout << ci << endl;
			while (sepa != NULL)
				{
				if (k==0) datosy[i]=atof(sepa); //cout << datosy[i] << endl;
				sepa = strtok(NULL,",");
				k++;
				}
			}

		m=sprintf(bq,"block");		
	  	Float_t max[N],area[N];


		Float_t bs=0,aux=0;                    // I obtain the baseline Baseline 
		for (i=0;i<10;i++)
  			{
  			aux=aux+datosy[i]*1000;   //previously was 1000     
  			}
		bs=aux/10;
		cout << " bs = " << bs << endl;

		max[j]=0;	
		area[j]=0;
	
		for (i=0;i<(N-1);i++)                                 
			{
			x[i]=(HOff+i*HRes)*1000000;// convert to us
			y[i]=-datosy[i]*1000+bs;	   // convert to mV	
			if (max[j]<y[i]) max[j]=y[i];
			area[j]=area[j]+y[i];
			}   
		cout << " area = "<< area[j] << endl;
		for (i=0;i<(N-1);i++)                                 
			{
			y[i]=y[i]/max[j];
			}   

		//for (i=0;i<N;i++)
  			//{
  			//ysum[i]=ysum[i]+y[i];///max[j];  		
			//if (j==1) Snorm[i]=ynorm[i];  
			//else
			//	Snorm[i]=Snorm[i]+ynorm[i];
			//}
				
   		}    

		TGraph *gr1 = new TGraph(N-1,x,y);
		gr1->SetLineColor(4);					
		gr1->SetLineWidth(1);				
		gr1->SetMarkerColor(4);					
		gr1->SetMarkerStyle(19);
		m=sprintf(title,"Pulse %d",j);						
		gr1->SetTitle(title);
		gr1->GetXaxis()->SetTitle(xaxis);			
		gr1->GetYaxis()->SetTitle(yaxis);			
		gr1->GetXaxis()->CenterTitle();				
		gr1->GetYaxis()->CenterTitle();			
		c1->cd(1+(j-ini));					
		gr1->Draw("ALP");  
		TF1 *f1 = new TF1("f1",fitf,a,b); 
		f1->SetParameter(0,100);		// for LSO:Ce		
		f1->SetParameter(1,22);	// for LSO:Ce			
		f1->SetParameter(2,-1);		// for LSO:Ce
		//f1->SetParameter(0,1);				
		//f1->SetParameter(1,140);				
		//f1->SetParameter(2,0.007);	
		//f1->SetParameter(3,1700);	
		//f1->SetParameter(4,40);	
		//f1->SetParameter(5,2000);	
		//f1->SetParameter(6,40);
		gr1->Fit("f1","R+");	
		gr1->Fit("f1","R");	
		d=f1->GetParameter(0);
		e=f1->GetParameter(1);
		f=f1->GetParameter(2);
		//g=f1->GetParameter(3);
		//h=f1->GetParameter(4);
		//l=f1->GetParameter(5);
	        e=1/e;
		m=sprintf(expo1,"%f*exp(-(x+%f)/%f)",d,h,e);
		//m=sprintf(expo2,"%f*exp(-(x+%f)/%f)",f,h,g);
	
 		TF1 *exp1   = new TF1("exp1",expo1,a,b);
		//TF1 *exp2   = new TF1("exp2",expo2,a,b);
		exp1->SetLineColor(2);
		//exp2->SetLineColor(4);
		exp1->Draw("same");
		//exp2->Draw("same");
/**/
		cout << d << " =d " << endl;
		//m=sprintf(ar,"y(x) = %.4f*exp(-(x%.0f)/%.0f)+%.4f*exp(-(x%.0f)/%.0f)",d,h,e,f,h,g);	// Introduce una leyenda con datos
		m=sprintf(ar,"y(x) = %.2f*exp(-(x%.2f)/%.3f)",d,h,e);
 	  	//m=sprintf(ar,"y(x) = %.4f*exp(x/%.0f)+%.4f*exp(-x/%.0f)+%.4f*exp(-x/%.0f)",d,e,f,g,h,l);	// Introduce una leyenda con datos
	
		TLegend *legend=new TLegend(0.40,0.75,0.880,0.88,"adjusted function");	// Declaración de la leyenda
		legend->SetTextFont(72);						// Tipo de fuente de la leyenda
		legend->SetTextFont(1);	
		legend->SetTextSize(0.025);						// Tamaño de la fuente de la leyenda
		legend->AddEntry(ar,ar,"p");				// Añado entrada a la leyenda
		legend->Draw();		
	}
delete in; 
//gr1->FitPanel();				
c1->cd(0);
theApp->Run(kTRUE);					
delete theApp;
return 0;


}
