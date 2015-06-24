//************** Copyright: Martin Gascon. Stanford University **************************
//included libraries
#include "libraries.h" 
#include "functions.h" 

#define N 8192 	       // Number of data in the mca
using namespace std;


int main(int argc, char **argv)
{
//********************************** Variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);       // It must be to produce a Root executable file with arguments.

Float_t mean,sigma,dmean,dsigma,deltar,r,datos[N],x[N],y[N],dr, siga=2,sigb=2;		      
Int_t i,k,m,a1=5500,a2=6500,b1=5500,b2=6500,c1=5500,c2=6500,d1=5500,d2=6500;  
char file1[100]="a",file2[100]="b",file3[100]="c",file4[100]="d",ci[100]="";

gROOT->SetStyle("Plain");          // root options
gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);
gStyle->SetOptFit(0);

TCanvas *c = new TCanvas("c","Graph2D example",200,10,700,500);    //Canvas definition
  c->SetFillColor(10);
  c->SetBorderSize(2);
  c->SetFrameFillColor(0);
  c->Divide(1,1);




TH1I *H1 = new TH1I("H1",file1,8192,0,8191); 
TH1I *H2 = new TH1I("H2",file2,8192,0,8191); 
TH1I *H3 = new TH1I("H3",file3,8192,0,8191); 
TH1I *H4 = new TH1I("H4",file4,8192,0,8191); 

H1->SetMarkerColor(4);
H1->SetLineColor(kBlack);
H1->SetLineWidth(2);
H1->SetMarkerStyle(8);
H1->SetMarkerSize(1);  
H1->GetXaxis()->SetTitle("Channel");         
H1->GetYaxis()->SetTitle(" Counts ");      
H1->GetXaxis()->CenterTitle();   
H1->GetYaxis()->CenterTitle(); 

H2->SetMarkerColor(4);
H2->SetLineColor(kGreen+3);
H2->SetLineWidth(2);
H2->SetMarkerStyle(8);
H2->SetMarkerSize(1);


H3->SetMarkerColor(4);
H3->SetLineColor(kRed);
H3->SetLineWidth(2);
H3->SetMarkerStyle(8);
H3->SetMarkerSize(1);

H4->SetMarkerColor(4);
H4->SetLineColor(kBlue);
H4->SetLineWidth(2);
H4->SetMarkerStyle(8);
H4->SetMarkerSize(1);



//*********************************** Main body   *************************************
switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: m=sprintf(file1,"%s.mca",argv[1]);		
		m=sprintf(file2,"%s.mca",argv[1]);
		m=sprintf(file3,"%s.mca",argv[1]);
		m=sprintf(file4,"%s.mca",argv[1]);
		break;
	case 3: m=sprintf(file1,"%s.mca",argv[1]);
		m=sprintf(file2,"%s.mca",argv[2]);	
		m=sprintf(file3,"%s.mca",argv[2]);
		m=sprintf(file4,"%s.mca",argv[2]);
		break;
	case 4: m=sprintf(file1,"%s.mca",argv[1]);
		m=sprintf(file2,"%s.mca",argv[2]);
		m=sprintf(file3,"%s.mca",argv[3]);
		m=sprintf(file4,"%s.mca",argv[3]);
		break;
	case 5: {
		m=sprintf(file1,"%s.mca",argv[1]);
		m=sprintf(file2,"%s.mca",argv[2]);
		m=sprintf(file3,"%s.mca",argv[3]);
		m=sprintf(file4,"%s.mca",argv[4]);
		break;
		}
	case 13: {
		m=sprintf(file1,"%s.mca",argv[1]);
		m=sprintf(file2,"%s.mca",argv[2]);
		m=sprintf(file3,"%s.mca",argv[3]);
		m=sprintf(file4,"%s.mca",argv[4]);
		a1=atoi(argv[5]);a2=atoi(argv[6]);
		b1=atoi(argv[7]);b2=atoi(argv[8]);
		c1=atoi(argv[9]);c2=atoi(argv[10]);
		d1=atoi(argv[11]);d2=atoi(argv[12]);
		break;
		}
	};


ifstream *in1 = new ifstream(file1);
ifstream *in2 = new ifstream(file2);
ifstream *in3 = new ifstream(file3);
ifstream *in4 = new ifstream(file4);


//************************************************************************************ read file1
if(!*in1)
	{
	cout << " ERROR OPENING FILE " <<  file1 << endl; 
	return 1;
	}
else    {
	i=1;
	do	{
		*in1 >> ci;
		if ((strstr(ci,"DATA")!=NULL))	
			{
			i=0;
			}
		}
	while (i!=0);
	for (i=0;i<N;i++)
		*in1 >> datos[i];                  
		if ((strstr(ci,"ROI")!=NULL)) i=N;
	delete in1;   
	}

for (k=0;k<N;k++)
	{
	x[k]=k;                 
	y[k]=datos[k];
	H1->Fill(x[k],y[k]);
	}
//************************************************************************************ lectura de fich 2



if (argc>2&&!*in2) 
	{cout << " ERROR OPENING FILE " <<  file2 << endl; 
		return 1;
	}
	else    
	{
		i=1;
		do	{
			*in2 >> ci;
			if ((strstr(ci,"DATA")!=NULL))	
				{
				i=0;
				if (argc==3) *in2 >> ci;
				}
			}
		while (i!=0);
		for (i=0;i<N;i++)
			*in2 >> datos[i];                  
			if ((strstr(ci,"ROI")!=NULL)) i=N;
		delete in2;   
	}

	for (k=0;k<N;k++)
		{
		x[k]=k;                 
		y[k]=datos[k];
		H2->Fill(x[k],y[k]);
		}

//************************************************************************************ lectura de fich 3



if(argc>3&&!*in3) 
	{cout << " ERROR OPENING FILE " <<  file3 << endl; 
	return 1;
	}
else    {
	i=1;
	do	{
		*in3 >> ci;
		if ((strstr(ci,"DATA")!=NULL))	
			{
			i=0;
			if (argc==3) *in3 >> ci;
			}
		}
	while (i!=0);
	for (i=0;i<N;i++)
		*in3 >> datos[i];                  
		if ((strstr(ci,"ROI")!=NULL)) i=N;
	delete in3;   
	}

for (k=0;k<N;k++)
	{
	x[k]=k;                 
	y[k]=datos[k];
	H3->Fill(x[k],y[k]);
	}

//************************************************************************************ lectura de fich 4




if(argc>4&&!*in4) 
	{cout << " ERROR OPENING FILE " <<  file4 << endl; 
	return 1;
	}
else    {
	i=1;
	do	{
		*in4 >> ci;
		if ((strstr(ci,"DATA")!=NULL))	
			{
			i=0;
			if (argc==3) *in4 >> ci;
			}
		}
	while (i!=0);
	for (i=0;i<N;i++)
		*in4 >> datos[i];                  
		if ((strstr(ci,"ROI")!=NULL)) i=N;
	delete in4;   
	}

for (k=0;k<N;k++)
	{
	x[k]=k;                 
	y[k]=datos[k];
	H4->Fill(x[k],y[k]);
	}




/*
TF1 *fitFcn = new TF1("fitFcn",fit_egaus,a1,a2,5);
fitFcn->SetLineWidth(4);
fitFcn->SetLineColor(kBlack);
fitFcn->SetParameters(5,-0.001,1,(a1+a2)/2,100);		// par4 = width, par5 = peak
H1->Fit(fitFcn,"R+");    
mean = fitFcn->GetParameter(3); 
sigma = fitFcn->GetParameter(4);
dmean =fitFcn->GetParError(3);
dsigma =fitFcn->GetParError(4);
a1=Int_t(mean-siga*sigma);                            	// siga y sigb contains the number of sigmas on the left and right
a2=Int_t(mean+sigb*sigma);
fitFcn->SetRange(a1,a2);					
H1->Fit(fitFcn,"R+");					// second try: set start values for some parameters


mean = fitFcn->GetParameter(3); 
sigma = fitFcn->GetParameter(4);
dmean =fitFcn->GetParError(3);
dsigma =fitFcn->GetParError(4);

r = 100*(sigma*2.35/mean);        			// resolution 
deltar=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
dr =sqrt(deltar);
deltar=dr;

*/
H1->Draw();
H2->Draw("same");

//H1->Fit(fitFcn,"R"); 

         		       

//************************************************************************************************************************* histo2 
/*
if (argc>2)
	{
	fitFcn->SetParameters(5,-0.001,1,(b1+b2)/2,100);		// par4 = width, par5 = peak
	H2->Fit(fitFcn,"R+");    
	mean = fitFcn->GetParameter(3); 
	sigma = fitFcn->GetParameter(4);
	dmean =fitFcn->GetParError(3);
	dsigma =fitFcn->GetParError(4);
	b1=Int_t(mean-siga*sigma);                     
	b2=Int_t(mean+sigb*sigma);
	fitFcn->SetRange(b1,b2);					
	H2->Fit(fitFcn,"R+");			
	
	mean = fitFcn->GetParameter(3); 
	sigma = fitFcn->GetParameter(4);
	dmean =fitFcn->GetParError(3);
	dsigma =fitFcn->GetParError(4);

	r = 100*(sigma*2.35/mean);        			
	deltar=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
	dr =sqrt(deltar);
	deltar=dr;
	
	H2->Draw("same");
	H2->Fit(fitFcn,"R"); 
	}
*/


//************************************************************************************************************************* histo3 
/*

if (argc>3)
	{
	fitFcn->SetParameters(5,-0.001,1,(c1+c2)/2,100);		// par4 = width, par5 = peak
	H3->Fit(fitFcn,"R+");    
	mean = fitFcn->GetParameter(3); 
	sigma = fitFcn->GetParameter(4);
	dmean =fitFcn->GetParError(3);
	dsigma =fitFcn->GetParError(4);
	c1=Int_t(mean-siga*sigma);                   
	c2=Int_t(mean+sigb*sigma);
	fitFcn->SetRange(c1,c2);					
	H3->Fit(fitFcn,"R+");				

	mean = fitFcn->GetParameter(3); 
	sigma = fitFcn->GetParameter(4);
	dmean =fitFcn->GetParError(3);
	dsigma =fitFcn->GetParError(4);

	r = 100*(sigma*2.35/mean);        			// calculo la resolución
	deltar=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
	dr =sqrt(deltar);
	deltar=dr;

	H3->Draw("same");
	H3->Fit(fitFcn,"R"); 
	}

//************************************************************************************************************************* histo4  

if (argc>4)
	{
	fitFcn->SetParameters(5,-0.001,1,(d1+d2)/2,100);		// par4 = width, par5 = peak
	H4->Fit(fitFcn,"R+");    
	mean = fitFcn->GetParameter(3); 
	sigma = fitFcn->GetParameter(4);
	dmean =fitFcn->GetParError(3);
	dsigma =fitFcn->GetParError(4);
	d1=Int_t(mean-siga*sigma);                     
	d2=Int_t(mean+sigb*sigma);
	fitFcn->SetRange(d1,d2);					
	H4->Fit(fitFcn,"R+");			

	mean = fitFcn->GetParameter(3); 
	sigma = fitFcn->GetParameter(4);
	dmean =fitFcn->GetParError(3);
	dsigma =fitFcn->GetParError(4);
	
	r = 100*(sigma*2.35/mean);        			// calculo la resolución
	deltar=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
	dr =sqrt(deltar);
	deltar=dr;

	H4->Draw("same");
	H4->Fit(fitFcn,"R"); 
	}
*/
TLegend *legend=new TLegend(0.64,0.61,0.9,0.86);
legend->AddEntry(H1,"a","l");
legend->AddEntry(H2,"b","l");
legend->AddEntry(H3,"c","l");
legend->AddEntry(H4,"d","l");
legend->Draw();
legend->SetFillColor(0);


c->cd(0);

theApp->Run(kTRUE);
delete theApp;
return 0;
}
