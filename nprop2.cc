//************** Copyright: Martin Gascon. Stanford University ***************************************
//included libraries
#include "libraries.h" 
#include "functions.h" 

using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

#define N 10000 				       // Número máximo de data 

#define FILES 0


int main(int argc, char **argv)
{
//********************************** Declaracion de variables ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);
Float_t x[7]={0,0.15,0.350,0.500,0.700,0.99,1},np[7]={0,0,0,0,0,0,0}, sx[7]={0.007,0.007,0.007,0.007,0.007,0.007,0.007},snp[7]={0,0,0,0,0,0,0};    //CsI(Tl)
//Float_t x[7]={0,0.145,0.214,0.283,0.352,0.414,0.49},np[7]={0,0,0,0,0,0,0}, sx[7]={0.007,0.007,0.007,0.007,0.007,0.007,0.007},snp[7]={0,0,0,0,0,0,0};   //LaBr3
Float_t x2[10]={0,0,0,0,0,0,0,0,0,0}, y2[10]={0,0,0,0,0,0,0,0,0,0},dx2[10]={0,0,0,0,0,0,0,0,0,0}, dy2[10]={0,0,0,0,0,0,0,0,0,0};

Float_t datax[N],datay[N],datay2[N],errorx[N],errory[N],errory2[N],ref=0,dref=0; 		      
Int_t i,k,m1;  
char file1[100],file2[100],file3[100],file4[100],file5[100],file6[100],file7[100],file8[100];


TCanvas *c1 = new TCanvas("c","Graph2D example",200,10,700,500);
c1->SetFillColor(0);
//c1->SetLogx();
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

//*********************************** Cuerpo del programa   *************************************
switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: m1=sprintf(file1,"%s.txt",argv[1]);		// FILENAME-A FILENAME-B 
		break;
	case 3: m1=sprintf(file1,"%s.txt",argv[1]);		// FILENAME-A FILENAME-B 
		m1=sprintf(file2,"%s.txt",argv[2]);
		break;
	case 4: m1=sprintf(file1,"%s.txt",argv[1]);		// FILENAME-A FILENAME-B 
		m1=sprintf(file2,"%s.txt",argv[2]);
		m1=sprintf(file3,"%s.txt",argv[3]);
		break;
	case 5: m1=sprintf(file1,"%s.txt",argv[1]);		// FILENAME-A FILENAME-B 
		m1=sprintf(file2,"%s.txt",argv[2]);
		m1=sprintf(file3,"%s.txt",argv[3]);
		m1=sprintf(file4,"%s.txt",argv[4]);
		break;
	case 6: m1=sprintf(file1,"%s.txt",argv[1]);		// FILENAME-A FILENAME-B 
		m1=sprintf(file2,"%s.txt",argv[2]);
		m1=sprintf(file3,"%s.txt",argv[3]);
		m1=sprintf(file4,"%s.txt",argv[4]);
		m1=sprintf(file5,"%s.txt",argv[5]);
		break;
	case 7: m1=sprintf(file1,"%s.txt",argv[1]);		// FILENAME-A FILENAME-B 
		m1=sprintf(file2,"%s.txt",argv[2]);
		m1=sprintf(file3,"%s.txt",argv[3]);
		m1=sprintf(file4,"%s.txt",argv[4]);	
		m1=sprintf(file5,"%s.txt",argv[5]);
		m1=sprintf(file6,"%s.txt",argv[6]);
		break;
	case 8: m1=sprintf(file1,"%s.txt",argv[1]);		// FILENAME-A FILENAME-B 
		m1=sprintf(file2,"%s.txt",argv[2]);
		m1=sprintf(file3,"%s.txt",argv[3]);
		m1=sprintf(file4,"%s.txt",argv[4]);	
		m1=sprintf(file5,"%s.txt",argv[5]);
		m1=sprintf(file6,"%s.txt",argv[6]);
		m1=sprintf(file7,"%s.txt",argv[7]);	
		break;
	default:
		MsgError();
		exit(1);
		break;
	};   


if (argc>1) 
	{
	ifstream *in = new ifstream(file1);
	if(!*in) 
		{cout << " ERROR OPENING FILE " <<  file1 << endl; 
		return 1;
		}
	else    {
		i=0;
		while (!in->eof())
			{
			*in >> datax[i] >> errorx[i] >> datay[i] >> errory[i] >> datay2[i] >> errory2[i] ;  
			if (datax[i]==662) {ref=datay[i]; dref=errorx[i]; cout << ref <<  " "<< datax[i] << endl;}
			i++;
			}
		}
	for (k=0;k<i-1;k++)
		{
		np[0]=np[0]+(((datay[k]/ref*662/datax[k])-1)*((datay[k]/ref*662/datax[k])-1));		
		snp[0]=snp[0]+((errory[k]*errory[k]/(ref*ref)) + (datay[k]*datay[k]*dref*dref/(ref*ref*ref*ref)));
		//snp[0]=snp[0]+((errory[k]*errory[k]/(ref*ref*ref*ref*662*662*662*662/(datax[k]*datax[k]*datax[k]*datax[k]))) + (datay[k]*datay[k]*datay[k]*datay[k]*dref*dref*662*662*662*662/(ref*ref*ref*ref*datax[k]*datax[k]*datax[k]*datax[k])));
		cout << np[0] << endl;
		}
	np[0]=float(1/(k+1.0))*np[0];
	np[0]=1-sqrt(np[0]);

	snp[0]=(np[0]-1)*(np[0]-1)*sqrt(snp[0]);
	//cout << " final np= " << np[0] << endl;
	//snp[0]=sqrt(snp[0]);
	//snp[0]=2915*float(1/(k+1.0))*snp[0];

	//snp[0]=np[0]*np[0]*sqrt(snp[0]);
	cout << " final np= " << np[0] << "  snp = " << snp[0] << "  Points: " << k <<endl;
	delete in;	
	}

if (argc>2)
	{
	ifstream *in2 = new ifstream(file2);
	if(!*in2) 
		{cout << " ERROR OPENING FILE " <<  file2 << endl; 
		return 1;
		}
	else    {
		i=0;
		while (!in2->eof())
			{
			*in2 >> datax[i] >> errorx[i] >> datay[i] >> errory[i] >> datay2[i] >> errory2[i] ;  
			if (datax[i]==662) {ref=datay[i]; dref=errorx[i]; cout << ref <<  " "<< datax[i] << endl;}
			i++;
			}
		}
	for (k=0;k<i-1;k++)
		{
		np[1]=np[1]+(((datay[k]/ref*662/datax[k])-1)*((datay[k]/ref*662/datax[k])-1));
		snp[1]=snp[1]+((errory[k]*errory[k]/(ref*ref)) + (datay[k]*datay[k]*dref*dref/(ref*ref*ref*ref)));
		cout << np[1] << endl;		
		}
	np[1]=float(1/(k+1.0))*np[1];
	np[1]=1-sqrt(np[1]);
	snp[1]=np[1]*np[1]*sqrt(snp[1]);
	cout << " final np= " << np[1] << endl;	
	delete in2;
	}


if (argc>3)
	{
	ifstream *in3 = new ifstream(file3);
	if(!*in3) 
		{cout << " ERROR OPENING FILE " <<  file3 << endl; 
		return 1;
		}
	else    {
		i=0;
		while (!in3->eof())
			{
			*in3 >> datax[i] >> errorx[i] >> datay[i] >> errory[i] >> datay2[i] >> errory2[i] ;  
			if (datax[i]==662) {ref=datay[i]; dref=errorx[i]; cout << ref <<  " "<< datax[i] << endl;}
			i++;
			}
		}


	for (k=0;k<i-1;k++)
		{
		np[2]=np[2]+(((datay[k]/ref*662/datax[k])-1)*((datay[k]/ref*662/datax[k])-1));
		snp[2]=snp[2]+((errory[k]*errory[k]/(ref*ref)) + (datay[k]*datay[k]*dref*dref/(ref*ref*ref*ref)));
		cout << np[2] << endl;		
		}
	np[2]=float(1/(k+1.0))*np[2];
	np[2]=1-sqrt(np[2]);
	snp[2]=np[2]*np[2]*sqrt(snp[2]);
	cout << " final np= " << np[2] << endl;
	delete in3;
	}


if (argc>4)
	{
	ifstream *in4 = new ifstream(file4);
	if(!*in4) 
		{cout << " ERROR OPENING FILE " <<  file4 << endl; 
		return 1;
		}
	else    {
		i=0;
		while (!in4->eof())
			{
			*in4 >> datax[i] >> errorx[i] >> datay[i] >> errory[i] >> datay2[i] >> errory2[i] ;  
			if (datax[i]==662) {ref=datay[i]; dref=errorx[i]; cout << ref <<  " "<< datax[i] << endl;}
			i++;
			}
		}


	for (k=0;k<i-1;k++)
		{
		np[3]=np[3]+(((datay[k]/ref*662/datax[k])-1)*((datay[k]/ref*662/datax[k])-1));	
		snp[3]=snp[3]+((errory[k]*errory[k]/(ref*ref)) + (datay[k]*datay[k]*dref*dref/(ref*ref*ref*ref)));
		cout << np[3] << endl;		
		}
	np[3]=float(1/(k+1.0))*np[3];
	np[3]=1-sqrt(np[3]);	
	snp[3]=np[3]*np[3]*sqrt(snp[3]);
	cout << " final np= " << np[3] << endl;
	delete in4;
	}

if (argc>5)
	{
	ifstream *in5 = new ifstream(file5);
	if(!*in5) 
		{cout << " ERROR OPENING FILE " <<  file5 << endl; 
		return 1;
		}
	else    {
		i=0;
		while (!in5->eof())
			{
			*in5 >> datax[i] >> errorx[i] >> datay[i] >> errory[i] >> datay2[i] >> errory2[i] ;  
			if (datax[i]==662) {ref=datay[i]; dref=errorx[i]; cout << ref <<  " "<< datax[i] << endl;}
			i++;
			}
		}

	for (k=0;k<i-1;k++)
		{
		np[4]=np[4]+(((datay[k]/ref*662/datax[k])-1)*((datay[k]/ref*662/datax[k])-1));
		snp[4]=snp[4]+((errory[k]*errory[k]/(ref*ref)) + (datay[k]*datay[k]*dref*dref/(ref*ref*ref*ref)));
		cout << np[4] << endl;		
		}
	np[4]=float(1/(k+1.0))*np[4];
	np[4]=1-sqrt(np[4]);
	snp[4]=np[4]*np[4]*sqrt(snp[4]);
	cout << " final np= " << np[4] << endl;
	delete in5;
	}


if (argc>6)
	{
	ifstream *in6 = new ifstream(file6);
	if(!*in6) 
		{cout << " ERROR OPENING FILE " <<  file6 << endl; 
		return 1;
		}
	else    {
		i=0;
		while (!in6->eof())
			{
			*in6 >> datax[i] >> errorx[i] >> datay[i] >> errory[i] >> datay2[i] >> errory2[i] ;  
			if (datax[i]==662) {ref=datay[i]; dref=errorx[i]; cout << ref <<  " "<< datax[i] << endl;}
			i++;
			}
		}


	for (k=0;k<i-1;k++)
		{
		np[5]=np[5]+(((datay[k]/ref*662/datax[k])-1)*((datay[k]/ref*662/datax[k])-1));	
		snp[5]=snp[5]+((errory[k]*errory[k]/(ref*ref)) + (datay[k]*datay[k]*dref*dref/(ref*ref*ref*ref)));
		cout << np[5] << endl;		
		}
	np[5]=float(1/(k+1.0))*np[5];
	np[5]=1-sqrt(np[5]);	
	snp[5]=np[5]*np[5]*sqrt(snp[5]);
	cout << " final np= " << np[5] << endl;
	delete in6;
	}

if (argc>7)
	{
	ifstream *in7 = new ifstream(file7);
	if(!*in7) 
		{cout << " ERROR OPENING FILE " <<  file7 << endl; 
		return 1;
		}
	else    {
		i=0;
		while (!in7->eof())
			{
			*in7 >> datax[i] >> errorx[i] >> datay[i] >> errory[i] >> datay2[i] >> errory2[i] ;  
			if (datax[i]==662) {ref=datay[i]; dref=errorx[i]; cout << ref <<  " "<< datax[i] << endl;}
			i++;
			}
		}

	for (k=0;k<i-1;k++)
		{
		np[6]=np[6]+(((datay[k]/ref*662/datax[k])-1)*((datay[k]/ref*662/datax[k])-1));	
		snp[6]=snp[6]+((errory[k]*errory[k]/(ref*ref)) + (datay[k]*datay[k]*dref*dref/(ref*ref*ref*ref)));
		cout << np[6] << endl;		
		}
	np[6]=float(1/(k+1.0))*np[6];
	np[6]=1-sqrt(np[6]);	
	snp[6]=np[6]*np[6]*sqrt(snp[6]);
	cout << " final np= " << np[6] << endl;
	delete in7;
	}




	
TGraphErrors *gr1 = new TGraphErrors(7,x,np,sx,snp);		
gr1->SetMarkerColor(kRed);
gr1->SetMarkerStyle(21);
gr1->SetMarkerSize(1.5);
gr1->GetXaxis()->SetTitle("Pressure (GPa)");		// Escribe como titulo del eje x lo que hay en ejex
gr1->GetYaxis()->SetTitle("1-#sigma_{NP}");         // Escribe como titulo del eje y lo que hay en ejey
gr1->GetXaxis()->CenterTitle();			// Para centrar el titulo del eje x
gr1->GetYaxis()->CenterTitle();			// Para centrar el titulo del eje x	
gr1->GetXaxis()->SetLabelColor(1);			
gr1->GetYaxis()->SetLabelColor(1);
gr1->GetXaxis()->SetTitleOffset(1.2);	
gr1->Draw("ap");					

		
Int_t l=0;

//ifstream *in8 = new ifstream("LaBr3_NPP.txt");
ifstream *in8 = new ifstream("CsI_NPP.txt");
if(!*in8) 
	{
	cout << " ERROR OPENING FILE " <<  "LaBr3_NPP.dat" << endl;
	}
	else    
	{
		l=0;
		while (!in8->eof())
			{
			*in8 >> x2[l] >> errorx[l] >> datay[l] >>  y2[l];  
			//cout << x2[l] << " dataxxxx " << y2[l] <<endl;
			l++;
			}
	
	delete in8;
	cout << l << " points "<<endl;
	TGraphErrors *gr2 = new TGraphErrors(10,x2,y2,dx2,dy2);		
	gr2->SetLineColor(kBlue);
	gr2->SetLineWidth(2);

	gr2->SetMarkerColor(kBlue);
	gr2->SetMarkerStyle(21);
	gr2->SetMarkerSize(0);
	gr2->Draw("samel");
	}




#if FILES 
	ofstream *out2 = new ofstream("ONEminusSigmaNPvsP.txt",ios::app); // file recording all the decay times as function of T
	for (k=0;k<argc-1;k++)
		{
		*out2 << x[k] <<"\t"<< sx[k] <<"\t" << np[k] << "\t" << snp[k] << endl;  // *1000 is in ns
		}
#endif






TLatex *tf = new TLatex();
tf->SetNDC();
tf->SetTextFont(62);
tf->SetTextAlign(12);
tf->SetTextSize(0.04);
tf->SetTextColor(kBlue);
//tf->DrawLatex(0.5,0.4,"#sigma_{NP} = [ ^{1}/_{N} #Sigma(1-Y_{i}/Y_{662})]^{^{1}/_{2}}");
tf->SetTextSize(0.03);
//tf->DrawLatex(0.5,0.35,"Dorenbos et al. NIMA486(2002)208");
tf->DrawLatex(0.5,0.35,"CsI (Setyawan et al.)");
gROOT->SetStyle("Plain");
gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);
gStyle->SetOptFit(0);  
					
theApp->Run(kTRUE);					// Para hacer el ejecutable
delete theApp;
return 0;




}
