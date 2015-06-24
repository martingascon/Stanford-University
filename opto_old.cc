//************** Copyright: Martin Gascon. Stanford University ***************************************
//included libraries
#include "libraries.h" 
#include "functions.h" 
#include <math.h> 

#define N 10000 	// Maximum number of data to represent
#define NL 50 		// Number of loops

#define NoG 1 		// Number of gaussian functions to fit
#define FILES 0
#define GRAPH 1


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
Float_t x[10][N],y[10][N]; 	
TGraph *gr[10];


// OUTPUT FILES
#if FILES
	//ofstream *out1 = new ofstream("opto_em.txt",ios::app);
	ofstream *out2 = new ofstream("opto_inte.txt",ios::app);
	//ofstream *out3 = new ofstream("opto_area.txt",ios::app);
#endif

Int_t i,k,m,a=380,b=410,c=415,d=450,e=400,f=580,con=0;  // for three gaussians and LSO
//Int_t i,k,m,a=380,b=480,c=480,d=650,e=410,f=650,con=0;  // for two gaussians and LSO
//Int_t i,k,m,a=460,b=560,c=480,d=650,e=410,f=650,con=0;  // for one gaussian and LSO

Char_t title[100]="title",file1[100],file2[100],xaxis[100]="Wavelenght (nm)",yaxis[100]="Intensity (a.u.)";
Char_t file3[100],file4[100],file5[100],file6[100],file7[100],file8[100],ley1[100],ley2[100],ley3[100];
Char_t inte1[100],inte2[100],inte3[100],*sepa,latex1[100];
Float_t ndf=0,chis=0,chiondf=0,factor,ndf_old=0,chis_old=0,chiondf_old=0,area=0; 
Double_t par1[3],par2[6],par3[9],ra,rb,rc,rd,re,rf,sign=0,parg1[3],parg2[3],parg3[3] ;

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
if(!*in) {cout << " ERROR OPENING FILE " <<  file1 << endl; return 1;}
else     Read_2col(file1,x[0],y[0],i);

Float_t bl;
bl=y[0][0];
for (k=0;k<i;k++)			
	{
	y[0][k]=y[0][k]-bl;
	if ((x[0][k]>360.0)&&(x[0][k]<650.0))
		area=area+y[0][k];
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



#if FILES 
 	//*out1 << sepa << "\t"  << "0.5" << "\t" << par1[1] << "\t" << "5" << endl;
	//*out2 << sepa << "\t"  << "0.5" << "\t" << inte1 << "\t" << "5" << endl;
	//*out3 << sepa << "\t"  << "0.5" << "\t" << 5.4*area/1.35e+03 << "\t" << 5.4*area/1.35e+05 << "\t" << 0 << "\t" << 0 << "\t" << endl;
	*out2 << a+10 << "\t"  << "0.5" << "\t" << par1[0] << "\t" << "5" << endl;
#endif

}
/*
if (NoG==2)
{  	eg2->SetParameters(5.24e+03,454,62,6.43e+04,475.5,5.9+01);   			
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

	m=sprintf(ley1,"Em1 = %.0f nm",par2[1]); 
	m=sprintf(ley2,"Em2 = %.0f nm",par2[4]); 
	m=sprintf(inte1,"%.0f",par2[0]); 
	m=sprintf(inte2,"%.0f",par2[3]); 
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
	tx->SetTextColor(kRed);
	tx->SetTextSize(0.04);
	tx->DrawLatex(0.7,0.40,latex1);

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


	gr[0]->Fit(eg3,"QR+");								/// for three gaussians
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

#if FILES 
	*out1 << sepa << "\t"  << "0.5" << "\t" << par3[1] << "\t" << "5" <<"\t" << par3[4] <<"\t" << "5" <<"\t"<<  par3[7] <<"\t"  << "5" << endl;
	*out2 << sepa << "\t"  << "0.5" << "\t" << inte1 << "\t" << "5" <<"\t" << inte2 <<"\t" << "5" <<"\t"<<  inte3 <<"\t"  << "5" << endl;
	*out3 << sepa << "\t"  << "0.5" << "\t" << 5.4*area/1.35e+03 << "\t" << 5.4*area/1.35e+05 << "\t" << 0 << "\t" << 0 << "\t" << endl;
#endif

}
*/

if (argc>2)
{



	ifstream *in2 = new ifstream(file2);
	if(!*in2) {cout << " ERROR OPENING FILE " <<  file2 << endl; return 1;}
	else    Read_2col(file2,x[1],y[1],i);
	Float_t bl;
	bl=y[1][0];
	for (k=0;k<i;k++)			
		{
		y[1][k]=y[1][k]-bl;
		}
	gr[1] = new TGraph(i-2,x[1],y[1]);	
	gr[1]->SetLineColor(kBlue);					
	gr[1]->SetLineWidth(3);
	gr[1]->SetMarkerColor(kBlue);							
	gr[1]->Draw("samelP");
}

if (argc>3)
{
	ifstream *in3 = new ifstream(file3);
	if(!*in3) {cout << " ERROR OPENING FILE " <<  file3 << endl; return 1;}
	else   Read_2col(file3,x[2],y[2],i); 
	gr[2] = new TGraph(i-2,x[2],y[2]);	
	gr[2]->SetLineColor(kGreen+3);
	gr[2]->SetLineWidth(3);					
	gr[2]->SetMarkerColor(kGreen+3);							
	gr[2]->Draw("samelP");
}

if (argc>4)
{
	ifstream *in4 = new ifstream(file4);
	if(!*in4) {cout << " ERROR OPENING FILE " <<  file4 << endl; return 1;}
	else   Read_2col(file4,x[3],y[3],i); 
	gr[3] = new TGraph(i-2,x[3],y[3]);	
	gr[3]->SetLineColor(kMagenta+2);					
	gr[3]->SetLineWidth(3);					
	gr[3]->SetMarkerColor(kMagenta+2);							
	gr[3]->Draw("samelP");
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
