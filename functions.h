//************** Copyright: Martin Gascon. Stanford University **************************
//included libraries
#include "libraries.h" 


//***************************** FUNCTIONS DECLARATIONS **********************************
// Palette Definition for ZCol graphs
void set_plot_style();

// MCA functions
void Read_MCA(char *file, Float_t *datos, Float_t &days, Int_t &n);


// read files
void Read_1col(char *file, Float_t *x, Int_t &n);
void Read_2col(char *file, Float_t *x, Float_t *x2, Int_t &n);
void Read_3col(char *file, Float_t *x, Float_t *x2, Float_t *x3, Int_t &n);
void Read_4col(char *file, Float_t *x, Float_t *x2, Float_t *x3, Float_t *x4, Int_t &n);
void Read_5col(char *file, Float_t *x, Float_t *x2, Float_t *x3, Float_t *x4, Float_t *x5, Int_t &n);
void Read_6col(char *file, Float_t *x, Float_t *x2, Float_t *x3, Float_t *x4, Float_t *x5, Float_t *x6, Int_t &n);


// fiting functions
Double_t Background_lin(Double_t *x, Double_t *par);
Double_t Background_exp(Double_t *x, Double_t *par);
Double_t Background_expb(Double_t *x, Double_t *par);                   //new
Double_t Background_exp2(Double_t *x, Double_t *par);
Double_t Signal(Double_t *x, Double_t *par);
Double_t gaus1(Double_t *x, Double_t *par);
Double_t gaus2(Double_t *x, Double_t *par);
Double_t gaus3(Double_t *x, Double_t *par);
Double_t fit_lgaus(Double_t *x, Double_t *par);
Double_t fit_gaus2e(Double_t *x, Double_t *par);
Double_t fit_egaus(Double_t *x, Double_t *par);
Double_t fit_egausb(Double_t *x, Double_t *par);                    //new
Double_t fit_egaus2(Double_t *x, Double_t *par);
Double_t fit_egaus3(Double_t *x, Double_t *par);
Double_t fit_lgaus3(Double_t *x, Double_t *par);

Double_t fit_lga1ga2(Double_t *x, Double_t *par);
Double_t fit2gaus(Double_t *x, Double_t *par);
Double_t fit3gaus(Double_t *x, Double_t *par);

//resolution calculations
void Resol_ga(TF1 *g1, Float_t &r, Float_t &dr);
void Resol_eg(TF1 *g1, Float_t &r, Float_t &dr);
void Resol_egb(TF1 *g1, Float_t &r, Float_t &dr);
void Resol_eg2(TF1 *g1, Float_t &r, Float_t &dr);
void Resol_eg3(TF1 *g1, Float_t &r, Float_t &dr);




// error messages or legends
void MsgError(void);
void PrintStats(TF1 *g1, Int_t &cont, Float_t &r, Float_t &dr, Float_t &mean, Float_t &dmean, Float_t &integral);
void PrintLegend(Float_t &r, Float_t &dr, Float_t &mean, Float_t &dmean);
void PrintLegend2(Float_t &r, Float_t &dr, Float_t &mean, Float_t &dmean);
void PrintLegend3(Float_t &r, Float_t &dr, Float_t &mean, Float_t &dmean);
void PrintLatex(char *text, Int_t position, Int_t color, Int_t &number);



//***************************** FUNCTIONS DECLARATIONS **********************************

void set_plot_style(void)
{
   const Int_t NRGBs = 5;
   const Int_t NCont = 255;

   Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
   Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
   Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
   Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
   //if(gROOT->GetVersionInt()>=52400)
   //  gStyle->CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   //else
     TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
     
   gStyle->SetNumberContours(NCont);
}



// MCA functions
void Read_MCA(char *file, Float_t *datos,  Float_t &days,  Int_t &n)
{
	
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
#define Nmax 8192 
char ci[100]="";
Int_t i,da[3],ti[3],sec=0,da0[3],ti0[3];

ifstream *in = new ifstream(file);
ifstream *in2 = new ifstream(".date.txt");
if(!*in) 
	{cout << " ERROR OPENING FILE " <<  file << endl; 
	}
else    {
	i=1;
	do	
		{
		*in >> ci;
		if ((strstr(ci,"START_TIME")!=NULL))
			{
				
			*in >> ci; 
			*in >> ci; //cout << "da " << ci <<endl;
			da[0]=(int)(ci[0]- '0')*10+(int)(ci[1]- '0'); // we have to substract the ascii value of 0 
			da[1]=(int)(ci[3]- '0')*10+(int)(ci[4]- '0');
			da[2]=(int)(ci[6]- '0')*1000+(int)(ci[7]- '0')*100+(int)(ci[8]- '0')*10+(int)(ci[9]- '0');
			*in >> ci; //cout << "ti " << ci <<endl;
			ti[0]=(int)(ci[0]- '0')*10+(int)(ci[1]- '0'); // we have to substract the ascii value of 0 08/13/2012 14:48:04
			ti[1]=(int)(ci[3]- '0')*10+(int)(ci[4]- '0');
			ti[2]=(int)(ci[6]- '0')*10+(int)(ci[7]- '0');
					
				
			if(*in2) 
				{
				*in2 >> ci;
				da0[0]=(int)(ci[0]- '0')*10+(int)(ci[1]- '0'); // we have to substract the ascii value of 0 
				da0[1]=(int)(ci[3]- '0')*10+(int)(ci[4]- '0');
				da0[2]=(int)(ci[6]- '0')*1000+(int)(ci[7]- '0')*100+(int)(ci[8]- '0')*10+(int)(ci[9]- '0');
				*in2 >> ci;
				ti0[0]=(int)(ci[0]- '0')*10+(int)(ci[1]- '0'); // we have to substract the ascii value of 0 08/13/2012 14:48:04
				ti0[1]=(int)(ci[3]- '0')*10+(int)(ci[4]- '0');
				ti0[2]=(int)(ci[6]- '0')*10+(int)(ci[7]- '0');
				sec=86400*(da[1]-da0[1])+86400*30*(da[0]-da0[0])+86400*30*366*(da[2]-da0[2])+ti[2]+ti[1]*60+ti[0]*3600-(ti0[2]+ti0[1]*60+ti0[0]*3600); //sec since file
				}
			else
				{
				sec=86400*(da[1]-14)+86400*30*(da[0]-8)+86400*30*366*(da[2]-2012)+ti[2]+ti[1]*60+ti[0]*3600-42093; //seconds since 08/01/2012  16:58:14
				}

			//days=sec/86400.0;
			days=sec/86400.0; // divide by 60 if you want min , 3600 if you want hours or  86400 (days)
			cout << "****************************************************************************"<<endl;
			cout << "> "<<da[0]<<"/"<<da[1]<<"/"<<da[2]<<" -- "<<ti[0]<<":"<<ti[1]<<":"<< ti[2]<<"  t(s)= "<< sec << "= "<<days<<" days"<<endl;
			}

		//if ((strstr(ci,"LIVE_ti")!=NULL))  strcpy(liveti,ci);
		//if ((strstr(ci,"START_ti")!=NULL))  strcpy(startti,ci);
		if ((strstr(ci,"DATA")!=NULL))	
			{
			i=0;
			}
		}
	while (i!=0);
	for (i=0;i<Nmax;i++)
		{			
		*in >> datos[i];                  
		if ((strstr(ci,"END")!=NULL)) i=Nmax;
		}
	n=i;
	}
delete in;
}
   
// READ FILES
void Read_1col(char *file, Float_t *x, Int_t &n)
{
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
Int_t i=0;
ifstream *in = new ifstream(file);
if(!*in){cout << " ERROR OPENING FILE " <<  file << endl; }
else    {
	while (!in->eof()) { *in >> x[i]; i++;}	
	n=i;
	}
}


void Read_2col(char *file, Float_t *x, Float_t *x2, Int_t &n)
{
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
Int_t i=0;
ifstream *in = new ifstream(file);
if(!*in){cout << " ERROR OPENING FILE " <<  file << endl;}
else    {
	while (!in->eof()) { *in >> x[i] >> x2[i];  i++; 	}	
	n=i;
	}
}
void Read_3col(char *file, Float_t *x, Float_t *x2, Float_t *x3, Int_t &n)
{
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
Int_t i=0;
ifstream *in = new ifstream(file);
if(!*in){cout << " ERROR OPENING FILE " <<  file << endl;}
else    {
	while (!in->eof()) { *in >> x[i] >> x2[i] >> x3[i];   i++; 	}	
	n=i;
	}
}

void Read_4col(char *file, Float_t *x, Float_t *x2, Float_t *x3, Float_t *x4, Int_t &n)
{
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
Int_t i=0;
ifstream *in = new ifstream(file);
if(!*in){cout << " ERROR OPENING FILE " <<  file << endl;}
else    {
	while (!in->eof()) { *in >> x[i] >> x2[i] >> x3[i] >> x4[i];   i++; 	}	
	n=i;
	}
}




void Read_5col(char *file, Float_t *x, Float_t *x2, Float_t *x3, Float_t *x4, Float_t *x5, Int_t &n)
{
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
Int_t i=0;
ifstream *in = new ifstream(file);
if(!*in){cout << " ERROR OPENING FILE " <<  file << endl;}
else    {
	while (!in->eof()) { *in >> x[i] >> x2[i] >> x3[i] >> x4[i] >> x5[i];   i++; 	}	
	n=i;
	}
}

void Read_6col(char *file, Float_t *x, Float_t *x2, Float_t *x3, Float_t *x4, Float_t *x5, Float_t *x6, Int_t &n)
{
using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.
Int_t i=0;
ifstream *in = new ifstream(file);
if(!*in){cout << " ERROR OPENING FILE " <<  file << endl;}
else    {
	while (!in->eof()) { *in >> x[i] >> x2[i] >> x3[i] >> x4[i] >> x5[i] >> x6[i] ; i++; 	}	
	n=i;
	}
}





// Linear background function
Double_t Background_lin(Double_t *x, Double_t *par)
{  Double_t val = par[0]+par[1]*x[0];
   return val;
}

// Exponential background function
Double_t Background_exp(Double_t *x, Double_t *par)
{  Double_t val = par[0]*TMath::Exp(par[1]*x[0]);
   return val;
}

// Exponential background function
Double_t Background_expb(Double_t *x, Double_t *par)
{  Double_t val = par[0]*TMath::Exp(par[1]*(x[0]-par[2]));
   return val;
}

// Exponential background function
Double_t Background_exp2(Double_t *x, Double_t *par)
{  Double_t val = par[0]*TMath::Exp(par[1]*x[0]);
   return val;
}

// The signal function: a gaussian
Double_t Signal(Double_t *x, Double_t *par)
{  	Double_t arg = 0;
   	if (par[2]) arg = (x[0] - par[1])/par[2];
   		Double_t sig = par[0]*TMath::Exp(-0.5*arg*arg);
   	return sig;
}

// The signal function: doble gaussian gaussian g1
Double_t gaus1(Double_t *x, Double_t *par)
{  Double_t arg = 0;
   if (par[2]) arg = (x[0] - par[1])/par[2];
   Double_t sig = par[0]*TMath::Exp(-0.5*arg*arg);
   return sig;
}

// The signal function: doble gaussian gaussian g2
Double_t gaus2(Double_t *x, Double_t *par)
{  Double_t arg2 = 0;
   if (par[2]) arg2 = (x[0] - par[1])/par[2];
   Double_t sig = par[0]*TMath::Exp(-0.5*arg2*arg2);
   return sig;
}
// The signal function: doble gaussian gaussian g3
Double_t gaus3(Double_t *x, Double_t *par)
{  Double_t arg2 = 0;
   if (par[2]) arg2 = (x[0] - par[1])/par[2];
   Double_t sig = par[0]*TMath::Exp(-0.5*arg2*arg2);
   return sig;
}

// Combined background (linear) + signal
Double_t fit_lgaus(Double_t *x, Double_t *par)
{  	Double_t tot = Background_lin(x,par) + Signal(x,&par[2]);
   	return tot;
}

// Combined background (exponential) + signal
Double_t fit_egaus(Double_t *x, Double_t *par)
{  	Double_t tot = Background_exp(x,par) + Signal(x,&par[2]);            
   	return tot;
}

// Combined background (exponential) + signal                     //new
Double_t fit_egausb(Double_t *x, Double_t *par)
{  	Double_t tot = Background_expb(x,par) + Signal(x,&par[3]);
   	return tot;
}

// Combined background gaus + 2x expo
Double_t fit_gaus2e(Double_t *x, Double_t *par)
{  	Double_t tot = Background_exp(x,par) + Background_exp2(x,&par[2])+gaus1(x,&par[4]);
   	return tot;
}

// Combined background expo + 2x gaus
Double_t fit_egaus2(Double_t *x, Double_t *par)
{  	Double_t tot = Background_exp(x,par) + gaus1(x,&par[2])+gaus2(x,&par[5]);
   	return tot;
}

// Combined background expo + 3x gaus
Double_t fit_egaus3(Double_t *x, Double_t *par)
{  	Double_t tot = Background_exp(x,par) + gaus1(x,&par[2])+gaus2(x,&par[5])+gaus3(x,&par[8]);
   	return tot;
}

// Combined background lineal + 3x gaus
Double_t fit_lgaus3(Double_t *x, Double_t *par)
{  	Double_t tot = Background_lin(x,par) + gaus1(x,&par[2])+gaus2(x,&par[5])+gaus3(x,&par[8]);
   	return tot;
}

// Combined background (exponential) + signal
Double_t fitFcn(Double_t *x, Double_t *par)
{  	Double_t tot = Background_exp(x,par) + Signal(x,&par[2]);
   	return tot;
}
// Combined background + signal
Double_t fit_lga1ga2(Double_t *x, Double_t *par)
{  
    //Double_t tot = gaus1(x,par) + gaus2(x,par);//
	Double_t tot = Background_exp(x,par) + gaus1(x,&par[2]) + gaus2(x,&par[5]);
	return tot;
}


// Combined two gaussian functions
Double_t fit2gaus(Double_t *x, Double_t *par)
{  
	Double_t tot = gaus1(x,par) + gaus2(x,&par[3]);
	return tot;
}

// Combined three gaussian functions
Double_t fit3gaus(Double_t *x, Double_t *par)
{  
	Double_t tot = gaus1(x,par) + gaus2(x,&par[3])+ gaus3(x,&par[6]);
	return tot;
}



//resolution calculations

// calculate the resolution for a gaussian Function
void Resol_ga(TF1 *g1, Float_t &r, Float_t &dr)
{ 
	Float_t mean,sigma,dmean,dsigma;
	mean = g1->GetParameter(1);       			// obtain the mean value
	sigma = g1->GetParameter(2);
	dmean = g1->GetParError(1);		// uncertainty in mean
	dsigma = g1->GetParError(2);		// uncertainty in sigma	
	if (sigma<0) sigma=-sigma;
	if (mean<0) mean=-mean;		
	r = 100*(sigma*2.35/mean);
	dr=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
	dr= sqrt(dr);				// uncertainty in resolution

}


// calculate the resolution for a gaussian + exponential Function
void Resol_eg(TF1 *g1, Float_t &r, Float_t &dr)
{ 
	Float_t mean,sigma,dmean,dsigma;
	mean = g1->GetParameter(3); 	// get the mean value
	sigma = g1->GetParameter(4);	// get the sigma
	if (sigma<0) sigma=-sigma;	
	dmean = g1->GetParError(3);		// uncertainty in mean
	dsigma = g1->GetParError(4);		// uncertainty in sigma			
	if (sigma<0) sigma=-sigma;
	if (mean<0) mean=-mean;		
	r = 100*(sigma*2.35/mean);        	// resolution
	dr=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
	dr= sqrt(dr);				// uncertainty in resolution
	if (dr<0.1) dr=0.1;
}

// calculate the resolution for a gaussian + exponential Function with 3 parameters
void Resol_egb(TF1 *g1, Float_t &r, Float_t &dr)
{ 
	Float_t mean,sigma,dmean,dsigma;
	mean = g1->GetParameter(4); 	// get the mean value
	sigma = g1->GetParameter(5);	// get the sigma
	if (sigma<0) sigma=-sigma;	
	dmean = g1->GetParError(4);		// uncertainty in mean
	dsigma = g1->GetParError(5);		// uncertainty in sigma			
	if (sigma<0) sigma=-sigma;
	if (mean<0) mean=-mean;		
	r = 100*(sigma*2.35/mean);        	// resolution
	dr=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
	dr= sqrt(dr);				// uncertainty in resolution
	if (dr<0.1) dr=0.1;				
}





// calculate the resolution for a 2nd gaussian + exponential Function
void Resol_eg2(TF1 *g1, Float_t &r, Float_t &dr)
{ 
	Float_t mean,sigma,dmean,dsigma;
	mean = g1->GetParameter(6); 	// get the mean value
	sigma = g1->GetParameter(7);	// get the sigma
	dmean = g1->GetParError(6);		// uncertainty in mean
	dsigma = g1->GetParError(7);		// uncertainty in sigma	
	if (sigma<0) sigma=-sigma;
	if (mean<0) mean=-mean;		
	r = 100*(sigma*2.35/mean);        	// resolution
	dr=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
	dr= sqrt(dr);				// uncertainty in resolution
	if (dr<0.1) dr=0.1;
}



// calculate the resolution for a 3rd gaussian + exponential Function
void Resol_eg3(TF1 *g1, Float_t &r, Float_t &dr)
{ 
	Float_t mean,sigma,dmean,dsigma;
	mean = g1->GetParameter(9); 	// get the mean value
	sigma = g1->GetParameter(10);	// get the sigma
	dmean = g1->GetParError(9);		// uncertainty in mean
	dsigma = g1->GetParError(10);		// uncertainty in sigma			
	if (sigma<0) sigma=-sigma;
	if (mean<0) mean=-mean;
	r = 100*(sigma*2.35/mean);        	// resolution
	dr=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
	dr= sqrt(dr);				// uncertainty in resolution
	if (dr<0.1) dr=0.1;
}

// ******************************************************** error messages **************************** 
// Print the error message
void MsgError(void)
{ 	using namespace std;	 
        cout << "									  " << "\n";
        cout << "************************************************************************ " << "\n";
	cout << "SYNTAX ERROR: You entered the incorrect number of arguments.             " << "\n";
	cout << "PROGRAM [FILENAME-WITHOUT EXTENSION] [PARAMETERS] 			  " << "\n";
	cout << "OPEN THE CC FILE FOR ADDITIONAL INFORMATION				  " << "\n";
	cout << "Author: Martin Gascon. Stanford University. 2O11                         " << "\n";
        cout << "*************************************************************************" << "\n";    
        cout << "									  " << "\n";
}

// Print statistics
void PrintStats(TF1 *g1, Int_t &cont, Float_t &r, Float_t &dr, Float_t &mean, Float_t &dmean, Float_t &integral)
{ 	using namespace std;	
	Float_t ndf=0,chis=0,chiondf=0;    //************************************ calculo del chi2 y rebinin
	chis = g1->GetChisquare();  
	ndf= g1->GetNDF();
	chiondf=chis/ndf;
	cout << "*******************************************************************" << endl;
	cout << " X2: " << chis << " -- ndf: " << ndf << " --  X2/ndf: " << chiondf  << " --  Reb: x"<< cont*2 << endl;
	cout << " E.R.: "<< r << "+" << dr << "   --  P.H.: "<< mean << "+" << dmean << endl;
	cout << "*******************************************************************" << endl;      
	cout << "								    " << "\n";
}

// Print Legend
void PrintLegend(Float_t &r, Float_t &dr, Float_t &mean, Float_t &dmean)
{ 	Int_t m; char ar[100];
using namespace std;	
TLegend *legend=new TLegend(0.57,0.92,0.90,0.97); //**************************  leyendas
legend->SetTextFont(72);
legend->SetTextSize(0.04);
m=sprintf(ar,"E.R. = (%2.1f #pm %2.1f) %%",r,dr); 
legend->AddEntry(ar,ar,"p");
legend->SetFillColor(0);
legend->Draw();
TLegend *legend2=new TLegend(0.10,0.92,0.52,0.97);
legend2->SetTextFont(72);
legend2->SetTextSize(0.04);
m=sprintf(ar,"Ph. Ch. = (%2.1f #pm %2.1f)",mean,dmean);  
legend2->AddEntry(ar,ar,"p");
legend2->SetFillColor(0);
legend2->Draw();
}


// Print 2nd. Legend 
void PrintLegend2(Float_t &r, Float_t &dr, Float_t &mean, Float_t &dmean)
{ 	Int_t m; char ar[100];
using namespace std;	
TLegend *legend=new TLegend(0.57,0.87,0.90,0.92); //**************************  leyendas
legend->SetTextFont(72);
legend->SetTextSize(0.04);
m=sprintf(ar,"E.R. = (%2.1f #pm %2.1f) %%",r,dr); 
legend->AddEntry(ar,ar,"p");
legend->SetFillColor(0);
legend->Draw();
TLegend *legend2=new TLegend(0.10,0.87,0.52,0.92);
legend2->SetTextFont(72);
legend2->SetTextSize(0.04);
m=sprintf(ar,"Ph. Ch. = (%2.1f #pm %2.1f)",mean,dmean);  
legend2->AddEntry(ar,ar,"p");
legend2->SetFillColor(0);
legend2->Draw();
}



// Print 3rd. Legend 
void PrintLegend3(Float_t &r, Float_t &dr, Float_t &mean, Float_t &dmean)
{ 	Int_t m; char ar[100];
using namespace std;	
TLegend *legend=new TLegend(0.57,0.82,0.90,0.87); //**************************  leyendas
legend->SetTextFont(72);
legend->SetTextSize(0.04);
m=sprintf(ar,"E.R. = (%2.1f #pm %2.1f) %%",r,dr); 
legend->AddEntry(ar,ar,"p");
legend->SetFillColor(0);
legend->Draw();
TLegend *legend2=new TLegend(0.10,0.82,0.52,0.87);
legend2->SetTextFont(72);
legend2->SetTextSize(0.04);
m=sprintf(ar,"Ph. Ch. = (%2.1f #pm %2.1f)",mean,dmean);  
legend2->AddEntry(ar,ar,"p");
legend2->SetFillColor(0);
legend2->Draw();
}





// Print Latex 
void PrintLatex(char *text, Int_t position, Int_t color, Int_t number)
{ 
using namespace std;	
TLatex *tx1 = new TLatex();
tx1->SetNDC();
tx1->SetTextFont(62);
tx1->SetTextColor(36);
tx1->SetTextAlign(12);
tx1->SetTextSize(0.06);
tx1->SetTextColor(color);
Float_t posx=0,posy=0;
if (position==1) {posx=0.2; posy=0.9-number*0.05;} 
if (position==2) {posx=0.8; posy=0.9-number*0.05;} 
if (position==3) {posx=0.2; posy=0.2-number*0.05;} 
if (position==4) {posx=0.8; posy=0.2-number*0.05;} 
tx1->DrawLatex(posx,posy,text);
}






