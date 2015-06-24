//************** Copyright: Martin Gascon. Stanford University ***************************************
//included libraries
#include "libraries.h" 
#include "functions.h" 

using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

int main(int argc, char **argv) // argc = integer number of arguments; ** = points to a string; argv = string of parameters
{
//********************************** Variables declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv); // TRint = type of variable; theApp is name of variable you deine; * is a pointer to one character
Int_t k,m,a=600,b=800,c=1,d=1,e=1,f=1,cont=0,reb=1,N=8192,con=0;  
Float_t me[3],si[3],dm[3],ds[3],data[N],x[N],y[N]; //[n] refers to a vector 		      
Float_t integral=0,r[3],dr[3];
char file[100],title[150]=""; //title is a string with 150 characters
Float_t ndf=0,chis=0,chiondf=0,ochiondf=0; 
double ra,rb,rc,rd,sa,sb,sc,sd,oa,ob,oc,od;


gROOT->SetStyle("Plain"); 
gStyle->SetOptStat(0);    // display stats
gStyle->SetOptFit(0);     // display fit parameters 1 = on, 0 = off



switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: m=sprintf(file,"%s.mca",argv[1]);		// FILENAME 	
		break;						 
default:
		MsgError();
		exit(1);
		break;

	};   


Float_t datos[25][25][201];

ifstream *in = new ifstream(file);
if(!*in) 
	{cout << " ERROR OPENING FILE " <<  file << endl; 
	}
else    {
	i=1;
	do	
		{
		*in >> ci;
		//if ((strstr(ci,"LIVE_TIME")!=NULL))  strcpy(livetime,ci);
		//if ((strstr(ci,"START_TIME")!=NULL))  strcpy(starttime,ci);
		if ((strstr(ci,"# Start of Data:")!=NULL))	
			{
			i=0;
			}
		}
	while (i!=0);
	
	for (i=0;i<201;i++)
		{			
		*in >> datos[0][0][i];                  
				
		//if ((strstr(ci,"END")!=NULL)) i=Nmax;
		}
	n=i;
	}
delete in;


	for (i=0;i<201;i++)
		{			
		cout << datos[0][0][i] << endl;                  
				

		}


/*

TH1I *H = new TH1I("H",file,N,0,N-1);  // declaration of the histogram	 
for (k=0;k<N;k++)			
	{
	x[k]=k;                 
	y[k]=data[k];
	H->Fill(x[k],y[k]);		// fill the histogram
	}
H->SetMarkerColor(7);
H->SetFillColor(19);
H->SetLineColor(2);
H->SetLineWidth(2);
H->SetMarkerStyle(8);
H->SetMarkerSize(1);
H->SetTitle(title);
H->GetXaxis()->SetTitle("Channel");
H->GetYaxis()->SetTitle(" Counts ");
H->GetXaxis()->CenterTitle();
H->GetYaxis()->CenterTitle();
H->Rebin(reb);
if (argc==2) argc=4;   // takes A and B as default values
if (argc==3) argc=4;  // takes A and B as default values
if (argc==5) argc=4;   // takes A and B as default values
if (argc==7) argc=6;  // takes A and B as default values
if (argc==9) argc=8;  // takes A and B as default values


Double_t par1[5];
Double_t par2[8],parg1[3],parg2[3],pare2[2];
Double_t par3[11],parg3[3],pare3[2];

TF1 *eg1   = new TF1("eg1",fit_egaus,a,b,5);
TF1 *g1    = new TF1("g1","gaus",a,b);
TF1 *e1    = new TF1("e1",Background_exp,a*0.9,b*1.1,2);

////////////////****************************
//TF1 *eg2x   = new TF1("eg2x",fit_gaus2e,a,b,8);
//TF1 *g2x    = new TF1("g2x","gaus",a*0.8,b*1.2);
//TF1 *e2xa    = new TF1("e2xa",Background_exp,a*0.9,b*1.1,2);
//TF1 *e2xb    = new TF1("e2xb",Background_exp2,a*0.9,b*1.1,2);
////////////////****************************

TF1 *eg2   = new TF1("eg2",fit_egaus2,a,d,8);
TF1 *g2    = new TF1("g2","gaus",c,d);
TF1 *e2    = new TF1("e2",Background_lin,a*0.9,d*1.1,2);


TF1 *eg3   = new TF1("eg3",fit_egaus3,a,f,11);
TF1 *g3    = new TF1("g3","gaus",e,f);
TF1 *e3    = new TF1("e3",Background_exp,a*0.9,f*1.1,2);


TF1 *total1 = new TF1("total1",fit_egaus,a,b,5);
//TF1 *total2x = new TF1("total2x",fit_gaus2e,a,c,8);
TF1 *total2 = new TF1("total2",fit_egaus2,a,d,8);
TF1 *total3 = new TF1("total3",fit_egaus3,a,f,11);

total1->SetLineColor(4);
total2->SetLineColor(4);
total3->SetLineColor(4);

switch (argc)
	{
	case 4:	H->Fit(g1,"NQR+");
		g1->GetParameters(&parg1[0]);		
		H->Fit(eg1,"NR+");	
		eg1->GetParameters(&par1[0]);
		total1->SetParameters(par1);
		H->Fit(total1,"R+");

		do
			{
			H->Fit(total1,"RNQ+");
			total1->GetParameters(&par1[0]);
			g1->SetParameters(par1[2],par1[3],par1[4]);
			e1->SetParameters(par1[0],par1[1]);
			me[0] = total1->GetParameter(3); 
			si[0] = total1->GetParameter(4);
			dm[0] = total1->GetParError(3);
			ds[0] = total1->GetParError(4);		
			Resol_eg(total1,r[0],dr[0]);
 			ra = 10*gRandom->Rndm();
			rb = 10*gRandom->Rndm();
   			sa = 10*gRandom->Rndm();
			sb = 10*gRandom->Rndm();
			if (sa>5) sa=-1; else sa=1;
			if (sb>5) sb=-1; else sb=1;
			a=a+sa*int(ra); b=b+sb*int(rb);
			chis = total1->GetChisquare();  
			ndf= total1->GetNDF();		
			chiondf=chis/ndf;
			con++;
 			cout << " limits =>  a=" << a << " b=" << b << " chiondf="<< chiondf << " con=" << con <<endl;		
			} 
		while (chiondf>1.05&&con<10);
		H->Fit(total1,"R");
		total1->GetParameters(&par1[0]);
		g1->SetParameters(par1[2],par1[3],par1[4]);
		e1->SetParameters(par1[0],par1[1]);
		me[0] = total1->GetParameter(3); 
		si[0] = total1->GetParameter(4);
		dm[0] = total1->GetParError(3);
		ds[0] = total1->GetParError(4);		
		Resol_eg(total1,r[0],dr[0]);
		g1->Draw("same");
		e1->Draw("same");
		e1->SetLineColor(kGreen+3);
  		PrintStats(total1,cont,r[0],dr[0],me[0],dm[0],integral);
		PrintLegend(r[0],dr[0],me[0],dm[0]);
		break;
	case 6:	H->Fit(g1,"NQR+");
		g1->GetParameters(&parg1[0]);		
		H->Fit(g2,"NQR+");
		g2->GetParameters(&parg2[0]);	
		H->Fit(e2,"NQR+");
		e2->GetParameters(&pare2[0]);	
		eg2->SetParameters(pare2[0],pare2[1],parg1[0],parg1[1],parg1[2],parg2[0],parg2[1],parg2[2]);	
		H->Fit(eg2,"NR");
		eg2->GetParameters(&par2[0]);
		total2->SetParameters(par2);
		H->Fit(total2,"QR+");
 		chis = total2->GetChisquare();  
		ndf= total2->GetNDF();		
		chiondf=chis/ndf;
		do
			{
			ochiondf=chiondf;
			oa=a;ob=b;oc=c;od=d;
	  		ra = 20*gRandom->Rndm();
			rb = 20*gRandom->Rndm();
   			rc = 20*gRandom->Rndm();
			rd = 20*gRandom->Rndm();
   			sa = 10*gRandom->Rndm();
			sb = 10*gRandom->Rndm();
   			sc = 10*gRandom->Rndm();
			sd = 10*gRandom->Rndm();			
			if (sa>5) sa=-1; else sa=1;
			if (sb>5) sb=-1; else sb=1;
			if (sc>5) sc=-1; else sc=1;		
			if (sd>5) sd=-1; else sd=1;
			a=a+sa*int(ra); b=b+sb*int(rb); c=c+sc*int(rc); d=d+sd*int(rd);
			H->Fit(e2,"QR+");
			e2->GetParameters(&pare2[0]);	
			eg2->SetParameters(pare2[0],pare2[1],parg1[0],parg1[1],parg1[2],parg2[0],parg2[1],parg2[2]);	
			H->Fit(eg2,"QR+");
			eg2->GetParameters(&par2[0]);
			total2->SetParameters(par2);
			H->Fit(total2,"QR+");
			total2->GetParameters(&par2[0]);	
			g1->SetParameters(par2[2],par2[3],par2[4]);
			g2->SetParameters(par2[5],par2[6],par2[7]);
			e2->SetParameters(par2[0],par2[1]);
			Resol_eg(total2,r[0],dr[0]);
			Resol_eg2(total2,r[1],dr[1]);
 			chis = total2->GetChisquare();  
			ndf= total2->GetNDF();		
			chiondf=chis/ndf;
			/*if (ochiondf<chiondf)
				{chiondf=ochiondf; a=oa;b=ob;c=oc;d=od;}
			else			
				{
				con++;
 				cout << "a=" << a << " b=" << b <<" c=" << c << " d=" << d <<" chiondf="<< chiondf << " con=" << con <<endl;		
				}	*/		
		/*	} 
		while (chiondf>1.05&&con<1);
		H->Fit(total2,"R");
		total2->GetParameters(&par2[0]);	
		g1->SetParameters(par2[2],par2[3],par2[4]); 
		g2->SetParameters(par2[5],par2[6],par2[7]);
		e2->SetParameters(par2[0],par2[1]);
		g1->Draw("same");
		g2->Draw("same");
		e2->Draw("same");
		e2->SetLineColor(kGreen+3);
		me[0] = total2->GetParameter(3); me[1] = total2->GetParameter(6); 
		si[0] = total2->GetParameter(4); si[1] = total2->GetParameter(7);
		dm[0] = total2->GetParError(3);  dm[1] = total2->GetParError(6);
		ds[0] = total2->GetParError(4);	 ds[1] = total2->GetParError(7);	
		Resol_eg(total2,r[0],dr[0]);
		Resol_eg2(total2,r[1],dr[1]);
		PrintStats(total2,cont,r[0],dr[0],me[0],dm[0],integral);
		PrintStats(total2,cont,r[1],dr[1],me[1],dm[1],integral);
		PrintLegend(r[0],dr[0],me[0],dm[0]);
		PrintLegend2(r[1],dr[1],me[1],dm[1]);
		break;
	case 8: H->Fit(g1,"NQR+");
		g1->GetParameters(&parg1[0]);		
		H->Fit(g2,"NQR+");
		g2->GetParameters(&parg2[0]);	
		H->Fit(g3,"NQR+");
		g3->GetParameters(&parg3[0]);	
		H->Fit(e3,"NQR+");
		e3->GetParameters(&pare3[0]);	
		eg3->SetParameters(pare3[0],pare3[1],parg1[0],parg1[1],parg1[2],parg2[0],parg2[1],parg2[2],parg3[0],parg3[1],parg3[2]);	
		H->Fit(eg3,"NR");
		eg3->GetParameters(&par3[0]);
		total3->SetParameters(par3);
		H->Fit(total3,"R+");
		H->Fit(total3,"R+");
		H->Fit(total3,"R+");
		total3->GetParameters(&par3[0]);	
		g1->SetParameters(par3[2],par3[3],par3[4]);
		g2->SetParameters(par3[5],par3[6],par3[7]);
		g3->SetParameters(par3[8],par3[9],par3[10]);
		e3->SetParameters(par3[0],par3[1]);
		g1->Draw("same");
		g2->Draw("same");
		g3->Draw("same");
		e2->Draw("same");
		e2->SetLineColor(kGreen+3);
		me[0] = total3->GetParameter(3); me[1] = total3->GetParameter(6);  me[2] = total3->GetParameter(9); 
		si[0] = total3->GetParameter(4); si[1] = total3->GetParameter(7);  si[2] = total3->GetParameter(10);
		dm[0] = total3->GetParError(3);  dm[1] = total3->GetParError(6);   dm[2] = total3->GetParError(9);
		ds[0] = total3->GetParError(4);	 ds[1] = total3->GetParError(7);   ds[2] = total3->GetParError(10);		
		Resol_eg(total3,r[0],dr[0]);
		Resol_eg2(total3,r[1],dr[1]);
		Resol_eg3(total3,r[2],dr[2]);
		PrintStats(total3,cont,r[0],dr[0],me[0],dm[0],integral);
		PrintStats(total3,cont,r[1],dr[1],me[1],dm[1],integral);
		PrintStats(total3,cont,r[2],dr[2],me[2],dm[2],integral);
		PrintLegend(r[0],dr[0],me[0],dm[0]);
		PrintLegend2(r[1],dr[1],me[1],dm[1]);
		PrintLegend3(r[2],dr[2],me[2],dm[2]);
		break;
	}


*/

gROOT->SetStyle("Bold"); 
gStyle->SetOptStat(0);    // display stats
gStyle->SetOptFit(0);     // display fit parameters 1 = on, 0 = off


theApp->Run(kTRUE);
delete theApp;
return 0;
}
