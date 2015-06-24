//************** Copyright: Martin Gascon. Stanford University ***************************************
//included libraries
#include "libraries.h" 
#include "functions.h" 
#include <math.h> 

#define N 10000 	// Maximum number of data to represent
#define NL 50 		// Number of loops

#define NoG 2 		// Number of gaussian functions to fit
#define FILES 0
#define GRAPH 1
#define FIT 0
#define Elem 1 			// 1: CsI(Tl), 2: LaBr3(Ce), 3: NaI(Tl) 4: LSO



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
Float_t x[10][N],y[10][N],xbl,xmin,xmax,em1,em2,em3,in1,in2,in3,aux; 	
Float_t ndf=0,chis=0,chiondf=0,factor,ndf_old=0,chis_old=0,chiondf_old=0,area=0,integral=0; 
Double_t par1[3],par2[6],par3[9],ra,rb,rc,rd,re,rf,sign=0,parg1[3],parg2[3],parg3[3] ;

TGraph *gr[10];
Char_t title[100]="title",file1[100],file2[100],xaxis[100]="Wavelenght (nm)",yaxis[100]="Intensity (a.u.)";
Char_t file3[100],file4[100],file5[100],file6[100],file7[100],file8[100],ley1[100],ley2[100],ley3[100];
Char_t inte1[100],inte2[100],inte3[100],*sepa,latex1[100];
Char_t fitf[100]= "[0]*exp(-0.5*((x-[1])/[2])*((x-[1])/[2]))+[3]*exp(-0.5*((x-[4])/[5])*((x-[4])/[5]))"; 
Char_t fitf2[100]= "[0]*exp(-0.5*((x-[1])/[2])*((x-[1])/[2]))";

//Int_t i,k,m,a=380,b=410,c=415,d=450,e=400,f=580,con=0;  // for three gaussians and LSO
//Int_t i,k,m,a=380,b=480,c=480,d=650,e=410,f=650,con=0;  // for two gaussians and LSO
//Int_t i,k,m,a=320,b=360,c=360,d=600,e=420,f=650,con=0;  // for two gaussian and LaBr3
Int_t i,k,m,a,b,c,d,e,f,con=0;  // for two gaussian and LaBr3 transmission


switch (Elem)	// FIT REGION DEPENDING ON ELEMENT	
				{
				case 1: // for CsI(Tl)   
					//xbl=860;  xmin=366;  xmax=660;  c=370; d=430;  a=430;  b=750;  em1=550; em2=410;  in1=91;   in2=9;
					xbl=250;  xmin=360;  xmax=800;  c=360; d=490;  a=430;  b=800;  em1=550; em2=410;  in1=91;   in2=9;

					break;	
				case 2: // for LaBr3	  
					xbl=440;  xmin=320;  xmax=440; 	a=320;  b=360;  c=360;  d=440;  em1=354;  em2=388;  in1=52;  in2=48;
					break;
				case 3: // for NaI		 
					xbl=600;  xmin=320;  xmax=650; 	a=320;  b=360;  c=360;  d=650;  em1=340;  em2=430;  in1=20;  in2=80;
					break;	
				case 4: // for LSO		 
					xbl=300;  xmin=374;  xmax=650; 	a=374;  b=410;  c=460;  d=460;  e=460;  f=650; em1=396;  em2=427;  em3=475;  in1=50;  in2=50; in3=20; 
					break;	


				};


   
// OUTPUT FILES
#if FILES
	ofstream *out1 = new ofstream("WLvsP.txt",ios::app);
	ofstream *out2 = new ofstream("IWLvsP.txt",ios::app);
	//ofstream *out3 = new ofstream("opto_area.txt",ios::app);
#endif





TLatex *tx = new TLatex();

TCanvas *c1 = new TCanvas("c1","Graph2D example",200,10,700,500);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);

TVirtualPad *vp =  c1->cd(1);
vp->SetFillColor(10);
//vp->SetLogy();
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
		break;		
	case 3: m=sprintf(file1,"%s.txt",argv[1]);                // Filename file columns
		m=atoi(argv[2]);
		if ((m>100)&&(m<1000))		
			{
			a=m-10;					// A AND B DEFINE THE RANGE TO FIT
			b=m+10; cout << a << " =a" << endl;
			cout << b<< " =b" << endl;
			}
		else 	{
			m=sprintf(file2,"%s.txt",argv[2]); 
			}
		break;
	case 4: m=sprintf(file1,"%s.txt",argv[1]);
		m=atoi(argv[2]);
		if ((m>100)&&(m<1000))		
			{
			a=atoi(argv[2]);				// A AND B DEFINE THE RANGE TO FIT
			b=atoi(argv[3]);       cout << a << " =a" << endl;
			cout << b<< " =b" << endl;
			}
		else 	{
			m=sprintf(file2,"%s.txt",argv[2]); 
			m=sprintf(file3,"%s.txt",argv[3]);
			}
		break;
	case 5: m=sprintf(file1,"%s.txt",argv[1]);                // Filename file columns
		m=sprintf(file2,"%s.txt",argv[2]); 
		m=sprintf(file3,"%s.txt",argv[3]); 
		m=sprintf(file4,"%s.txt",argv[4]); 
		break;
	case 6: m=sprintf(file1,"%s.txt",argv[1]);                // Filename file columns
		m=sprintf(file2,"%s.txt",argv[2]); 
		m=sprintf(file3,"%s.txt",argv[3]); 
		m=sprintf(file4,"%s.txt",argv[4]); 
		m=sprintf(file5,"%s.txt",argv[5]); 
		break;
	case 7: m=sprintf(file1,"%s.txt",argv[1]);                // Filename file columns
		m=sprintf(file2,"%s.txt",argv[2]); 
		m=sprintf(file3,"%s.txt",argv[3]); 
		m=sprintf(file4,"%s.txt",argv[4]); 
		m=sprintf(file5,"%s.txt",argv[5]); 
		m=sprintf(file6,"%s.txt",argv[6]); 
		break;
	case 8: m=sprintf(file1,"%s.txt",argv[1]);                // Filename file columns
		m=sprintf(file2,"%s.txt",argv[2]); 
		m=sprintf(file3,"%s.txt",argv[3]); 
		m=sprintf(file4,"%s.txt",argv[4]); 
		m=sprintf(file5,"%s.txt",argv[5]); 
		m=sprintf(file6,"%s.txt",argv[6]); 
		m=sprintf(file7,"%s.txt",argv[7]); 
		break;
	case 9: m=sprintf(file1,"%s.txt",argv[1]);                // Filename file columns
		m=sprintf(file2,"%s.txt",argv[2]); 
		m=sprintf(file3,"%s.txt",argv[3]); 
		m=sprintf(file4,"%s.txt",argv[4]); 
		m=sprintf(file5,"%s.txt",argv[5]); 
		m=sprintf(file6,"%s.txt",argv[6]); 
		m=sprintf(file7,"%s.txt",argv[7]); 
		m=sprintf(file8,"%s.txt",argv[8]); 
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
	y[0][k]=y[0][k]/440.0;
	if ((x[0][k]>xmin)&&(x[0][k]<xmax)) 	area=area+y[0][k];
	}


gr[0] = new TGraph(i-2,x[0],y[0]);		// Graph declaration
gr[0]->SetLineColor(2);					
gr[0]->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
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




TF1 *g1    = new TF1("g1","gaus",a*0.8,b*1.1);
TF1 *g2    = new TF1("g2","gaus",c*0.8,d*1.2);
TF1 *g3    = new TF1("g3","gaus",e*0.8,f*1.1);    
TF1 *eg2   = new TF1("eg2",fit2gaus,a*0.9,d*1.1,6);			/// for two gaussians
TF1 *eg3   = new TF1("eg3",fit3gaus,a*0.9,f*1.1,9);			/// for three gaussians
TF1 *total1   = new TF1("gaus",gaus1,a*0.9,b*1.1,3);	
TF1 *total2   = new TF1("total2",fit2gaus,a*0.9,d*1.1,6);		 /// for two gaussians
TF1 *total3   = new TF1("total3",fit3gaus,a*0.9,f*1.1,9);		 /// for two gaussians

if (NoG==1)
{  	//g1->SetParameters(5.24e+03,460,62);   			
	gr[0]->Fit(g1,"NQR");									
	chis_old = g1->GetChisquare();								 
	ndf_old= g1->GetNDF();								
	chiondf_old=chis_old/ndf_old;							
	g1->GetParameters(&par1[0]);
	do  
			{
			srand ( (unsigned)time(NULL) );
			factor=(int)((b+a)/200);	
			if (factor<1) factor=1;
			ra = fmod(rand(), factor) +1;
			rb = fmod(rand(), factor) +1;
			sign = rand() % 10 + 1; 		
			if (sign>5) sign=-1; 	else sign=1;   
			a=a+sign*1*int(ra); b = b+1*sign*int(rb);
			total1->SetParameters(par1[0],par1[1],par1[2]);	
			total1->SetRange(a,b);
			gr[0]->Fit(total1,"NQR+");
			chis = total1->GetChisquare();  
			ndf= total1->GetNDF();		
			chiondf=chis/ndf;
			if (chiondf>chiondf_old)			
				{
				a=a-sign*1*int(ra); b = b-1*sign*int(rb);	// back to previous values
				total1->SetRange(a,b);
				gr[0]->Fit(total1,"NQR+");
				}
			else
				{
				chiondf_old=chiondf;
				}
			con++;
 			cout << " limits =>  a=" << a << " b=" << b << " chiondf="<< chiondf << " con=" << con <<endl;		
			} 
		while (chiondf>1.05&&con<NL);
	#if FIT
	gr[0]->Fit(total1,"R");
	total1->GetParameters(&par1[0]);
	m=sprintf(ley1,"Em1 = %.0f nm",par1[1]); 
	m=sprintf(inte1,"%.0f",par1[0]); 
	sepa= strtok(argv[1],"Aug8_empty_  kpsi_300nm_100msec");
	sepa= strtok(argv[1],"Aug8_empty_  kpsi_300nm_100msec");
	m=sprintf(latex1,"P = %s MPa",sepa);
	//sepa= strtok(argv[1],"cryostat_LSOCe_B_ground_ K");   Aug8_empty_0kpsi_300nm_100msec
	//m=sprintf(latex1,"T = %s K",sepa);
	
	area=total1->Integral(460,600);
	tx->SetNDC(); 
	tx->SetTextFont(62);
	tx->SetTextColor(36);
	tx->SetTextAlign(12);
	tx->SetTextSize(0.05);
	//tx->SetTextColor(2);
	tx->DrawLatex(0.7,0.80,ley1);
	tx->SetTextColor(kRed);
	tx->SetTextSize(0.04);
	tx->DrawLatex(0.7,0.40,latex1);

	#endif



}

if (NoG==2)
{  

	/*



		gr[0]->Fit(g1,"NQR+");
		g1->GetParameters(&parg1[0]);		
		gr[0]->Fit(g2,"NQR+");
		g2->GetParameters(&parg2[0]);	

		//gr[0]->Fit(,"NR");
		eg2->GetParameters(&par2[0]); 
		//par2 = {9.093e+03,-4.80e-03,7.22e+03,8.92e+01,2.976e+01,9.024e+02,2.376e+02,3.58e+01};   	//for Ba-133 PV
		//par2 = {9.093e+03,-4.80e-03,7.22e+03,8.92e+01,2.976e+01,9.024e+02,2.376e+02,3.58e+01};   	//for Ba-133 PV
		//par2 = {2.35e+03,-6.69e-03,4.27e+03,1.61e+02,3.436e+01,1.35e+02,3.76e+02,3.08e+01};   	//for Ba-133
		//par2 = {1.544e+04,-2.11e-03,3.259e+04,1.269e+02,4.58e+01,9.57e+03,3.72e+02,8.16e+01}; 	//for Eu-152 PV
		total2->SetParameters(par2);	








	//eg2->SetParameters(5.24e+03,350,62,6.43e+04,380.5,5.9+01);   			
	gr[0]->Fit(eg2,"R");									
	chis_old = eg2->GetChisquare();								 
	ndf_old= eg2->GetNDF();								
	chiondf_old=chis_old/ndf_old;							
	do  
			{
			eg2->GetParameters(&par2[0]);
			total2->SetParameters(par2[0],par2[1],par2[2],par2[3],par2[4],par2[5]);	
			total2->SetRange(a,d);
			gr[0]->Fit(total2,"NQR+");
			srand ( (unsigned)time(NULL) );
			factor=(int)((b+a)/200);	
			if (factor<1) factor=1;
			ra = fmod(rand(), factor) +1;
			rb = fmod(rand(), factor) +1;
			rc = fmod(rand(), factor) +1;
			rd = fmod(rand(), factor) +1;
			sign = rand() % 10 + 1; 		
			if (sign>5) sign=-1; 	else sign=1;   
			a=a+sign*1*int(ra); b = b+1*sign*int(rb);	
			c=c+sign*1*int(rc); d = d+1*sign*int(rd);
			chis = total2->GetChisquare();  
			ndf= total2->GetNDF();		
			chiondf=chis/ndf;
			if (chiondf>chiondf_old)			
				{
				a=a-sign*1*int(ra); b = b-1*sign*int(rb);	// back to previous values
				c=c-sign*1*int(rc); d = d-1*sign*int(rd);
				}
			else
				{
				chiondf_old=chiondf;
				}
			con++;
 			cout << " limits =>  a=" << a << " b=" << b << " chiondf="<< chiondf << " con=" << con <<endl;		
			} 
		while (chiondf>1.05&&con<NL);
	
	gr[0]->Fit(total2,"R+");
	eg2->GetParameters(&par2[0]);
	g1->SetParameters(par2[0],par2[1],par2[2]);
	g2->SetParameters(par2[3],par2[4],par2[5]);
	g1->SetLineColor(kGreen+3);
	g2->SetLineColor(kGreen+3);
	g1->Draw("same");
	g2->Draw("same");
	*/	

  
	TF1 *f1 = new TF1("f1",fitf,xmin,xmax);          		
 	//TF1 *f1 = new TF1("f1",fitf2,xmin,xmax);   
 	f1->SetParameters(in1*280,em1,10,in2*280,em2,-11); 	 	// CsI, (12583, 550,  70, 1177, 410,-23
	//f1->SetParameters(12583,550,70,1177,410,-23); 
	//f1->SetParameters(in1,em1,15);  


	gr[0]->Fit(f1,"R");
	gr[0]->Fit(f1,"R");

	em1=f1->GetParameter(1);
	em2=f1->GetParameter(4);
	in1=f1->GetParameter(0);
	in2=f1->GetParameter(3);

	aux=in1+in2;
	in1=in1/aux;
	in2=in2/aux;
	par2[1]=em1;
	par2[4]=em2;
	m=sprintf(ley1,"Em1 = %.1f nm",par2[1]); 
	m=sprintf(ley2,"Em2 = %.1f nm",par2[4]); 
	//m=sprintf(inte1,"%.0f",par2[0]); 
	//m=sprintf(inte2,"%.0f",par2[3]); 
	sepa= strtok(argv[1],"NaI_ 300nm_10ms_1scan_PV_LaBr3Ce_300nm_10s_1scan_PV_ kpsi");  
	sepa= strtok(argv[1],"LaBr3Ce_300nm_10s_1scan_PV_ kpsi");  
	sepa="0";	
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

	cout << "P" << "\t"  << "0.5" << "\t" << em1 << "\t" << "5" << "\t" << em2 << "\t" << "5"<< endl;
	cout << "P" << "\t"  << "0.5" << "\t" << in1 << "\t" << "5" << "\t" << in2 << "\t" << "5"<< endl;

#if FILES 
 	//*out1 << bl << endl;
	*out1 << sepa << "\t"  << "0.5" << "\t" << em1 << "\t" << "5" << "\t" << em2 << "\t" << "5"<< endl;
	*out2 << sepa << "\t"  << "0.5" << "\t" << in1 << "\t" << "5" << "\t" <<  in2 << "\t" << "5" << endl;
//	*out3 << sepa << "\t"  << "0.5" << "\t" << area << "\t" << area/100 << "\t" << 0 << "\t" << 0 << "\t" << endl;
#endif

}



	
if (NoG==3)
{

	eg3->SetParLimits(0,5000,25000);
	eg3->SetParLimits(1,380,425);
	eg3->SetParLimits(2,5,100);
	eg3->SetParLimits(3,5000,100000);
	eg3->SetParLimits(4,420,440);
	eg3->SetParLimits(5,5,100);
	eg3->SetParLimits(6,1000,5000);
	eg3->SetParLimits(7,440,480);
	eg3->SetParLimits(8,15,100);

	eg3->SetParameters(parg1[0],parg1[1],parg1[2],parg2[0],parg2[1],parg2[2],parg3[0],parg3[1],parg3[2]);	
	//eg3->SetParameters(9.7e+03,396,7.44,1.19e+04,426,1.97+01,1.99e+03,453,3.81e+01);   	/// for three gaussians


	gr[0]->Fit(eg3,"QR+");									/// for three gaussians
	chis_old = eg3->GetChisquare();								/// for three gaussians  
	ndf_old= eg3->GetNDF();									/// for three gaussians
	chiondf_old=chis_old/ndf_old;								/// for three gaussians
	eg3->GetParameters(&par3[0]);
	cout << " chi old =" << chis_old << " chiondf_old = " << chiondf_old << endl;		
	do  
			{
			
	
			if (par3[0]<0) par3[0]=-par3[0];
			if (par3[1]<0) par3[1]=-par3[1];
			if (par3[2]<0) par3[2]=-par3[2];
			if (par3[3]<0) par3[3]=-par3[3];
			if (par3[4]<0) par3[4]=-par3[4];
			if (par3[5]<0) par3[5]=-par3[5];
			if (par3[6]<0) par3[6]=-par3[6];
			if (par3[7]<0) par3[7]=-par3[7];
			if (par3[8]<0) par3[8]=-par3[8];

			srand ( (unsigned)time(NULL) );
			factor=(int)((b+a)/200);	
			if (factor<1) factor=1;
			ra = fmod(rand(), factor) +1;
			rb = fmod(rand(), factor) +1;
			rc = fmod(rand(), factor) +1;
			rd = fmod(rand(), factor) +1;
			re = fmod(rand(), factor) +1;
			rf = fmod(rand(), factor) +1;
			//cout << " ra=" << ra << " rb= " << rb << " rc=" << rc << " rd= " << rd << endl;	
			sign = rand() % 10 + 1; 		
			if (sign>5) sign=-1; 	else sign=1;   
			a=a+sign*1*int(ra); b = b+1*sign*int(rb);	
			c=c+sign*1*int(rc); d = d+1*sign*int(rd);
			e=e+sign*1*int(re); f = f+1*sign*int(rf);
			cout << " a=" << a << " b= " << b << " c=" << c << " d= " << d << endl;	

			cout << " par3[0]=" << par3[0] << " par3[1]= " << par3[1] << " par3[2]=" << par3[2] << " par3[3]= " << par3[3] << endl;	
			total3->SetParameters(par3[0],par3[1],par3[2],par3[3],par3[4],par3[5],par3[6],par3[7],par3[8]);	
			total3->SetRange(a*0.9,f*1.1);		
			gr[0]->Fit(total3,"SQR");
			chis = total3->GetChisquare();  
			ndf= total3->GetNDF();		
			chiondf=chis/ndf;
			if (chiondf>chiondf_old)			
				{
				a=a-sign*1*int(ra); b = b-1*sign*int(rb);	// back to previous values
				c=c-sign*1*int(rc); d = d-1*sign*int(rd);
				e=e-sign*1*int(re); f = f-1*sign*int(rf);
				}
			else
				{
				chiondf_old=chiondf;
				total3->GetParameters(&par3[0]);

				eg3->SetParameters(par3[0],par3[1],par3[2],par3[3],par3[4],par3[5],par3[6],par3[7],par3[8]);	
				eg3->SetRange(a*0.9,f*1.1);
				}
			con++;
 			cout << " limits =>  a=" << a << " f=" << f << " chiondf="<< chiondf << " con=" << con <<endl;		
			} 
		while (chiondf>1.05&&con<50);

	gr[0]->Fit(eg3,"R+");
	eg3->GetParameters(&par3[0]);
	g1->SetParameters(par3[0],par3[1],par3[2]);
	g2->SetParameters(par3[3],par3[4],par3[5]);
	g3->SetParameters(par3[6],par3[7],par3[8]);
	g1->SetLineColor(kGreen+3);
	g2->SetLineColor(kGreen+3);
	g3->SetLineColor(kGreen+3);
	g1->Draw("same");
	g2->Draw("same");
	g3->Draw("same");
	area=g1->Integral(300,900)+g2->Integral(300,900)+g3->Integral(300,900);

	m=sprintf(ley1,"Em1 = %.0f nm",par3[1]); 
	m=sprintf(ley2,"Em2 = %.0f nm",par3[4]); 
	m=sprintf(ley3,"Em3 = %.0f nm",par3[7]); 
	m=sprintf(inte1,"%.0f",par3[0]); 
	m=sprintf(inte2,"%.0f",par3[3]); 
	m=sprintf(inte3,"%.0f",par3[6]); 
	sepa= strtok(argv[1],"cryostat_LSOCe_B_ground_ K");  
	m=sprintf(latex1,"T = %s K",sepa);



	tx->SetNDC(); 
	tx->SetTextFont(62);
	tx->SetTextColor(36);
	tx->SetTextAlign(12);
	tx->SetTextSize(0.05);
	//tx->SetTextColor(2);
	tx->DrawLatex(0.7,0.80,ley1);
	tx->DrawLatex(0.7,0.75,ley2);
	tx->DrawLatex(0.7,0.70,ley3);
	tx->SetTextColor(kRed);
	tx->SetTextSize(0.04);
	tx->DrawLatex(0.7,0.40,latex1);

//#if FILES 
//	*out1 << sepa << "\t"  << "0.5" << "\t" << par3[1] << "\t" << "5" <<"\t" << par3[4] <<"\t" << "5" <<"\t"<<  par3[7] <<"\t"  << "5" << endl;
//	*out2 << sepa << "\t"  << "0.5" << "\t" << inte1 << "\t" << "5" <<"\t" << inte2 <<"\t" << "5" <<"\t"<<  inte3 <<"\t"  << "5" << endl;
//	*out3 << sepa << "\t"  << "0.5" << "\t" << 5.4*area/1.35e+03 << "\t" << 5.4*area/1.35e+05 << "\t" << 0 << "\t" << 0 << "\t" << endl;
//#endif

}


if (argc>2)
{



	ifstream *in2 = new ifstream(file2);
	if(!*in2) {cout << " ERROR OPENING FILE " <<  file2 << endl; return 1;}
	else    Read_2col(file2,x[1],y[1],i);


	Float_t bl=0;
	y[1][0]=0;
	//bl=y[0][1];
	for (k=1;k<i;k++)  if ((x[1][k]>xbl)) 	{bl=y[1][k];k=i; cout << " BL: " << bl << endl;}

	for (k=1;k<i;k++)			
		{
		y[1][k]=y[1][k]-bl;
		y[1][k]=y[1][k]/1152.0;
		if ((x[1][k]>xmin)&&(x[1][k]<xmax))
			area=area+y[1][k];
		}


	gr[1] = new TGraph(i-2,x[1],y[1]);	
	gr[1]->SetLineColor(kBlue);					
	gr[1]->SetLineWidth(2);
	gr[1]->SetMarkerColor(kBlue);							
	gr[1]->Draw("samecP");
}

if (argc>3)
{
	ifstream *in3 = new ifstream(file3);
	if(!*in3) {cout << " ERROR OPENING FILE " <<  file3 << endl; return 1;}
	else   Read_2col(file3,x[2],y[2],i); 


	Float_t bl=0;
	y[2][0]=0;
	//bl=y[0][1];
	for (k=1;k<i;k++)	if ((x[2][k]>xbl)) 	{bl=y[2][k];k=i; cout << " BL: " << bl << endl;}

	for (k=1;k<i;k++)			
		{
		y[2][k]=y[2][k]-bl;
		y[2][k]=y[2][k]/1770.0;
		if ((x[2][k]>xmin)&&(x[2][k]<xmax))
			area=area+y[2][k];
		}
	gr[2] = new TGraph(i-2,x[2],y[2]);	
	gr[2]->SetLineColor(kGreen+3);
	gr[2]->SetLineWidth(2);					
	gr[2]->SetMarkerColor(kGreen+3);							
	gr[2]->Draw("samecP");
}

if (argc>4)
{
	ifstream *in4 = new ifstream(file4);
	if(!*in4) {cout << " ERROR OPENING FILE " <<  file4 << endl; return 1;}
	else   Read_2col(file4,x[3],y[3],i); 

	Float_t bl=0;
	y[3][0]=0;
	//bl=y[0][1];
	for (k=1;k<i;k++)	if ((x[3][k]>xbl)) 	{bl=y[3][k];k=i; cout << " BL: " << bl << endl;}


	for (k=1;k<i;k++)			
		{
		y[3][k]=y[3][k]-bl;	
		y[3][k]=y[3][k]/636.0;
		if ((x[3][k]>xmin)&&(x[3][k]<xmax))
			area=area+y[3][k];
		}






	gr[3] = new TGraph(i-2,x[3],y[3]);	
	gr[3]->SetLineColor(kMagenta+2);					
	gr[3]->SetLineWidth(2);					
	gr[3]->SetMarkerColor(kMagenta+2);							
	gr[3]->Draw("samecP");
}



if (argc>5)
{
	ifstream *in5 = new ifstream(file5);
	if(!*in5) {cout << " ERROR OPENING FILE " <<  file5 << endl; return 1;}
	else   Read_2col(file5,x[4],y[4],i); 
	Float_t bl=0;
	y[4][0]=0;
	//bl=y[0][1];
	for (k=1;k<i;k++)	if ((x[4][k]>xbl)) 	{bl=y[4][k];k=i; cout << " BL: " << bl << endl;}
	for (k=1;k<i;k++)			
		{
		y[4][k]=y[4][k]-bl;
		if ((x[4][k]>xmin)&&(x[4][k]<xmax))
			area=area+y[4][k];
		}
	gr[4] = new TGraph(i-2,x[4],y[4]);	
	gr[4]->SetLineColor(kOrange+2);					
	gr[4]->SetLineWidth(2);					
	gr[4]->SetMarkerColor(kOrange+2);							
	gr[4]->Draw("samecP");
}


if (argc>6)
{
	ifstream *in6 = new ifstream(file6);
	if(!*in6) {cout << " ERROR OPENING FILE " <<  file6 << endl; return 1;}
	else   Read_2col(file6,x[5],y[5],i); 
	
	Float_t bl=0;
	y[5][0]=0;
	//bl=y[0][1];
	for (k=1;k<i;k++)	if ((x[5][k]>xbl)) 	{bl=y[5][k];k=i; cout << " BL: " << bl << endl;}
	for (k=1;k<i;k++)			
		{
		//y[5][k]=y[5][k]-bl;
		if ((x[5][k]>xmin)&&(x[5][k]<xmax))
			area=area+y[5][k];
		}
	for (k=1;k<i;k++) y[5][k]=y[5][k]*214;
	gr[5] = new TGraph(i-2,x[5],y[5]);	
	gr[5]->SetLineColor(kMagenta);					
	gr[5]->SetLineWidth(2);					
	gr[5]->SetMarkerColor(kMagenta);							
	gr[5]->Draw("samecP");
}






/* 	


if (argc>2)
	{
	tx->SetTextColor(4);
	tx->DrawLatex(0.8,0.75,"Serie 2");
	}
if (argc>3) 
	{
	tx->SetTextColor(kGreen+3);
	tx->DrawLatex(0.8,0.70,"Serie 3");
	}	

if (argc>4) 
	{
	tx->SetTextColor(kMagenta+2);
	tx->DrawLatex(0.8,0.65,"Serie 4");
	}	

*/

	
//gr1->FitPanel();						

//#if GRAPH
	theApp->Run(kTRUE);						
	delete theApp;
//#endif 

return 0;
}
