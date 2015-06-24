//************** Copyright: Martin Gascon. Stanford University ***************************************
//included libraries
#include "libraries.h" 
#include "functions.h" 
#include <math.h> 


using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

int main(int argc, char **argv) // argc = integer number of arguments; ** = points to a string; argv = string of parameters
{
//********************************** Variables declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv); // TRint = type of variable; theApp is name of variable you deine; * is a pointer to one character
Int_t k,m,a=1,b=8000,c=1,d=1,e=1,f=1,cont=0,reb=1,N=8192,con=0;  
Float_t me[3],si[3],dm[3],ds[3],data[N],x[N],y[N]; //[n] refers to a vector 		      
Float_t integral=0,r[3],dr[3];
char file[100],title[150]=""; //title is a string with 150 characters
Float_t ndf=0,chis=0,chiondf=0; 
double rana,ranb,signo=0;


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
	case 3: m=sprintf(file,"%s.mca",argv[1]);		// FILENAME REB
		reb=atoi(argv[2]);				//REB = REBINING OF FOR EACH FILE (DEFAULT 1)
		break;
	case 4: m=sprintf(file,"%s.mca",argv[1]);		// FILENAME A B   
		a=atoi(argv[2]);				// A AND B DEFINE THE RANGE TO FIT
		b=atoi(argv[3]);		
		break;
	case 5: m=sprintf(file,"%s.mca",argv[1]);		// FILENAME A B   
		a=atoi(argv[2]);				// A AND B DEFINE THE RANGE TO FIT
		b=atoi(argv[3]);
		reb=atoi(argv[4]);	
		break;
	case 6: m=sprintf(file,"%s.mca",argv[1]);		// FILENAME A B   
		a=atoi(argv[2]);				// A AND B DEFINE THE RANGE TO FIT
		b=atoi(argv[3]);
		c=atoi(argv[4]);				
		d=atoi(argv[5]);
		break;
	case 7: m=sprintf(file,"%s.mca",argv[1]);		// FILENAME A B   
		a=atoi(argv[2]);				// A AND B DEFINE THE RANGE TO FIT
		b=atoi(argv[3]);
		c=atoi(argv[4]);				
		d=atoi(argv[5]);		
		reb=atoi(argv[6]);	
		break;
	case 8: m=sprintf(file,"%s.mca",argv[1]);		// FILENAME A B   
		a=atoi(argv[2]);				// A AND B DEFINE THE RANGE TO FIT
		b=atoi(argv[3]);
		c=atoi(argv[4]);				
		d=atoi(argv[5]);		
		e=atoi(argv[6]);			
		f=atoi(argv[7]);		
		break;
	case 9: m=sprintf(file,"%s.mca",argv[1]);		// FILENAME A B   
		a=atoi(argv[2]);				// A AND B DEFINE THE RANGE TO FIT
		b=atoi(argv[3]);
		c=atoi(argv[4]);				
		d=atoi(argv[5]);		
		e=atoi(argv[6]);			
		f=atoi(argv[7]);		
		reb=atoi(argv[8]);	
		break;
default:
		MsgError();
		exit(1);
		break;

	};   

Read_MCA(file, data,N);

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
Double_t par2[8],parg1[3],parg2[3],pare2[2],pare1[2];      /// pare1 is new
Double_t par3[11],parg3[3],pare3[2];

TF1 *eg1   = new TF1("eg1",fit_egaus,a,b,5);
TF1 *g1    = new TF1("g1","gaus",a*0.8,b*1.2);
TF1 *e1    = new TF1("e1",Background_exp,a*0.9,b*1.1,2);

////////////////****************************
TF1 *eg2x   = new TF1("eg2x",fit_gaus2e,a,b,7);
TF1 *g2x    = new TF1("g2x","gaus",a*0.8,b*1.2);
TF1 *e2xa    = new TF1("e2xa",Background_exp,a*0.9,b*1.1,2);
TF1 *e2xb    = new TF1("e2xb",Background_exp2,a*0.9,b*1.1,2);
////////////////****************************

TF1 *eg2   = new TF1("eg2",fit_egaus2,a,d,8);
TF1 *g2    = new TF1("g2","gaus",c*0.8,d*1.2);
TF1 *e2    = new TF1("e2",Background_lin,a*0.9,d*1.1,2);


TF1 *eg3   = new TF1("eg3",fit_egaus3,a,f,11);
TF1 *g3    = new TF1("g3","gaus",e,f);
TF1 *e3    = new TF1("e3",Background_lin,a*0.9,f*1.1,2);


TF1 *total1 = new TF1("total1",fit_egaus,a,b,5);
TF1 *total2x = new TF1("total2x",fit_gaus2e,a,b,7);
TF1 *total2 = new TF1("total2",fit_egaus2,a,d,8);
TF1 *total3 = new TF1("total3",fit_egaus3,a,f,11);

total1->SetLineColor(4);
total2x->SetLineColor(4);
total2->SetLineColor(4);
total3->SetLineColor(4);
TF1 *fxx = new TF1("fxx","abs(sin(x)/x)*sqrt(x)",0,10);

switch (argc)
	{
	case 4:	eg2x->SetParameters(1,-0.01,1,0.01,1,(b+a)/2,100);
		H->Fit(eg2x,"NR+");		
		eg2x->GetParameters(&parg2[0]);
		total2x->SetParameters(par2);
		do
			{
			
			H->Fit(total2x,"RNQ+");
			total2x->GetParameters(&par2[0]);
			g2x->SetParameters(par2[4],par2[5],par2[6]);
			e2xa->SetParameters(par2[0],par2[1]);
			e2xb->SetParameters(par2[2],par2[3]);			
			me[0] = total1->GetParameter(5); 
			si[0] = total1->GetParameter(6);
			dm[0] = total1->GetParError(5);
			ds[0] = total1->GetParError(6);		
			Resol_eg(total2x,r[0],dr[0]);
   			rana = fxx->GetRandom();
			ranb = fxx->GetRandom();
			signo = fxx->GetRandom();
			if (signo>5) signo=-1;
			else signo=1;
			a=a+signo*int(rana); b=b+signo*int(ranb);
			chis = total1->GetChisquare();  
			ndf= total1->GetNDF();		
			chiondf=chis/ndf;
			con++;
 			cout << " limits =>  a=" << a << " b=" << b << " chiondf="<< chiondf <<endl;		
			} 
		while (chiondf>1.05&&con<50);
		H->Fit(total2x,"R+");
		total2x->GetParameters(&par2[0]);
			g2x->SetParameters(par2[4],par2[5],par2[6]);
			e2xa->SetParameters(par2[0],par2[1]);
			e2xb->SetParameters(par2[2],par2[3]);	
			me[0] = total2x->GetParameter(5); 
			si[0] = total2x->GetParameter(6);
			dm[0] = total2x->GetParError(5);
			ds[0] = total2x->GetParError(6);		
			Resol_eg(total2x,r[0],dr[0]);
			g2x->Draw("same");
			e2xa->Draw("same");
			e2xb->SetLineColor(kGreen+3);
  		PrintStats(total2x,cont,r[0],dr[0],me[0],dm[0],integral);
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
		//H->Fit(total2,"R+");
		//H->Fit(total2,"R+");
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




gROOT->SetStyle("Bold"); 
gStyle->SetOptStat(0);    // display stats
gStyle->SetOptFit(0);     // display fit parameters 1 = on, 0 = off


theApp->Run(kTRUE);
delete theApp;
return 0;
}
