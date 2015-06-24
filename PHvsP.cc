//************** Copyright: Martin Gascon. Stanford University ***************************************
//included libraries
#include "libraries.h" 
#include "functions.h" 

#define N 10000 	// Maximum number of data to represent
using namespace std;	//std contains all the classes, objects and functions of the standard C++ library.

#define FILES 0
#define GRAPH 1


int main(int argc, char **argv)
{
// ROOT OPTIONS
TRint *theApp = new TRint("Rint", &argc, argv);
gROOT->SetStyle("Plain");
gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);
gStyle->SetOptFit(0);  


// DECLARATION OF VARIABLES
Float_t x[N],y[N],dx[N],dy[N],y2[N],dy2[N],y3[N],dy3[N],y4[N],dy4[N],ref=1,I1=0,I2=0,I3=0,I4=0,I5=0,I6=0,I7=0,I8=0,I9=0; 	
Float_t xb[N],yb[N],dxb[N],dyb[N],y2b[N],dy2b[N],y3b[N],dy3b[N],y4b[N],dy4b[N],d,e,f,g,h,l,o,p;
Float_t xc[N],yc[N],dxc[N],dyc[N],y2c[N],dy2c[N],y3c[N],dy3c[N],y4c[N],dy4c[N];
	      
Int_t i,k,m,col=1,col2=1,col3=1,norm=1,norm2=1,norm3=1;  
char title[100]="title",file[100],file2[100],xaxis[100]="x-axis title",yaxis[100]="y-axis title";
char file3[100],file4[100],file5[100],file6[100],file7[100],file8[100],*sepa,latex1[100],tau1[100],tau2[100],Amp1[100],Amp2[100];
char fitf4[100]="[0]*exp(-x/[1])+[2]*exp(-x/[3])";


// OUTPUT FILES
#if FILES
	ofstream *out1 = new ofstream("dtimes.txt",ios::app);
	ofstream *out2 = new ofstream("amplis.txt",ios::app);
#endif

TLatex *tx = new TLatex();

TCanvas *c = new TCanvas("c","Graph2D example",200,10,700,500);
c->SetFillColor(0);
c->GetFrame()->SetFillColor(0); 
c->GetFrame()->SetBorderMode(-1);
c->GetFrame()->SetBorderSize(10);

TVirtualPad *vp =  c->cd(1);
vp->SetFillColor(10);
///vp->SetLogx();
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
	case 2: m=sprintf(file,"%s.txt",argv[1]);		// FILENAME TO REPRESENT (XY GRAPHS ONLY)	
		col=6;
		break;		
	case 5: m=sprintf(file,"%s.txt",argv[1]);                // Filename file columns
		col=atoi(argv[2]);
		m=sprintf(file2,"%s.txt",argv[3]);				// columns 
		col2=atoi(argv[4]);		
		break;
	case 6: m=sprintf(file,"%s.txt",argv[1]);                // Filename file columns
		col=atoi(argv[2]);				// columns 
		m=sprintf(file2,"%s.txt",argv[3]); 
		m=sprintf(file3,"%s.txt",argv[4]); 
		m=sprintf(file4,"%s.txt",argv[5]); 
		break;

	default:
		MsgError();
		exit(1);
		break;
	};   


ifstream *in = new ifstream(file);
if(!*in) 
	{cout << " ERROR OPENING FILE " <<  file << endl; 
	return 1;
	}
else    {
	i=0;
	while (!in->eof())
		{
		 *in >> x[i] >> dx[i] >> y[i] >> dy[i] >> y2[i] >> dy2[i];  
		i++;
		}
	}


for (k=0;k<i;k++)			
	{
//	x[k]=x[k]*1;                 
//	x[k]=1/sqrt(y[k]);                 
//	dx[k]=0.0005*dy[k]/sqrt(y[k]);
//	y[k]=y2[k]/1;               // calculate ER vs 1/sqrt(ph.ch)
//	y[k]=y[k]*1;
//	dy[k]=dy2[k]/1;
	if (argc>3) 
		{
		y[k]=y[k]/norm;
		dy[k]=dy[k]/norm;	
		x[k]=x[k]*1;
		}
	}



if (col==2)
	{
	TGraph *gr0 = new TGraph(i-2,x,y);		// Graph declaration
	gr0->SetLineColor(2);					
	gr0->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
	gr0->SetMarkerColor(2);						
	gr0->SetMarkerStyle(20);					
	gr0->SetTitle(title);					
	gr0->GetXaxis()->SetTitle(xaxis);				
	gr0->GetYaxis()->SetTitle(yaxis);				
	gr0->GetXaxis()->SetTitleSize(0.06);
	gr0->GetYaxis()->SetTitleSize(0.06);
	gr0->GetXaxis()->SetLabelSize(0.05);
	gr0->GetYaxis()->SetLabelSize(0.05);
	gr0->GetXaxis()->CenterTitle();					
	gr0->GetYaxis()->CenterTitle();	
	gr0->Draw("AcP");

#if FILES 
	*out1 << sepa << "\t"  << "0.5" <<std::fixed << std::setprecision(4) <<"\t" << e << "\t" << g <<"\t" << h <<"\t" << l << endl;
	*out2 << sepa << "\t"  << "0.5" <<std::fixed << std::setprecision(1) <<"\t" << d << "\t" << f <<"\t" << o <<"\t" << p << endl;
#endif


	}


if ((col==4)||(col==5)||(col==6)||(col==8)||(col==10))
	{
	TGraphErrors *gr1 = new TGraphErrors(i-1,x,y,dx,dy);		// Graph declaration
	gr1->SetLineColor(2);					
	gr1->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
	gr1->SetMarkerColor(2);						
	gr1->SetMarkerStyle(20);					
	gr1->SetTitle(title);					
	gr1->GetXaxis()->SetTitle(xaxis);				
	gr1->GetYaxis()->SetTitle(yaxis);				
	gr1->GetXaxis()->SetTitleSize(0.06);
	gr1->GetYaxis()->SetTitleSize(0.06);
	gr1->GetXaxis()->SetLabelSize(0.05);
	gr1->GetYaxis()->SetLabelSize(0.05);
	gr1->GetXaxis()->CenterTitle();					
	gr1->GetYaxis()->CenterTitle();	
	gr1->Draw("AP");

	if (col==5)
		{
		TGraphErrors *gr1 = new TGraphErrors(i-1,x,y,0,dy);		// Graph declaration
		gr1->SetLineColor(2);					
		gr1->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
		gr1->SetMarkerColor(2);						
		gr1->SetMarkerStyle(20);					
		gr1->SetTitle(title);					
		gr1->GetXaxis()->SetTitle(xaxis);				
		gr1->GetYaxis()->SetTitle(yaxis);				
		gr1->GetXaxis()->SetTitleSize(0.06);
		gr1->GetYaxis()->SetTitleSize(0.06);
		gr1->GetXaxis()->SetLabelSize(0.05);
		gr1->GetYaxis()->SetLabelSize(0.05);
		gr1->GetXaxis()->CenterTitle();					
		gr1->GetYaxis()->CenterTitle();	
		gr1->Draw("AP");
		}
	if ((col==5)||(col==6)||(col==8)||(col==10)) 	
		{		
		if (col==5)	 	
			{
			TGraphErrors *gr2 = new TGraphErrors(i-1,x,y2,0,dy2);		// Graph declaration
			gr2->SetLineColor(4);						// Line color 0=white 1=black, 2=red
			gr2->SetLineWidth(2);						
			gr2->SetMarkerColor(4);						
			gr2->SetMarkerStyle(20);	
			gr2->SetMarkerSize(0.4);
			gr2->GetXaxis()->CenterTitle("Pressure (kpsi)");					
			gr2->GetYaxis()->CenterTitle("Photopeak channel");											
			gr2->Draw("lPsame");
			}
		if (col>5)	 	
			{
			TGraphErrors *gr2 = new TGraphErrors(i-1,x,y2,dx,dy2);		// Graph declaration
			gr2->SetLineColor(4);						// Line color 0=white 1=black, 2=red
			gr2->SetLineWidth(2);						
			gr2->SetMarkerColor(4);						
			gr2->SetMarkerStyle(20);											
			gr2->Draw("lPsame");
			}
		if (col>7)
			{		
			TGraphErrors *gr3 = new TGraphErrors(i-1,x,y3,dx,dy3);		// Graph declaration
			gr3->SetLineColor(kGreen+3);						// Line color 0=white 1=black, 2=red
			gr3->SetLineWidth(2);						
			gr3->SetMarkerColor(kGreen+3);						
			gr3->SetMarkerStyle(20);									
			gr3->Draw("lPsame");
			}
		if (col>9)
			{		
			TGraphErrors *gr4 = new TGraphErrors(i-1,x,y4,dx,dy4);		// Graph declaration
			gr4->SetLineColor(kGreen+3);						// Line color 0=white 1=black, 2=red
			gr4->SetLineWidth(2);						
			gr4->SetMarkerColor(kGreen+3);						
			gr4->SetMarkerStyle(20);
			gr4->SetMarkerSize(0.4);										
			gr4->Draw("lPsame");
			}

		}
	}


if (argc>4)
{
	ifstream *in2 = new ifstream(file2);
	if(!*in2) 
		{cout << " ERROR OPENING FILE " <<  file2 << endl; 
		return 1;
		}
	else   
		{
		i=0;
		while (!in2->eof())
			{
			if (col2==2) *in2 >> xb[i] >> yb[i];
			if (col2==4) *in2 >> xb[i] >> dxb[i] >> yb[i] >> dyb[i];  		//if (col==4) *in >> x[i] >> y[i] >> dx[i] >> dy[i];
			if (col2==5) *in2 >> xb[i] >> yb[i] >> dyb[i] >> y2b[i] >> dy2b[i];
			if (col2==6) *in2 >> xb[i] >> dxb[i] >> yb[i] >> dyb[i] >> y2b[i] >> dy2b[i];  
			if (col2==8) *in2 >> xb[i] >> dxb[i] >> yb[i] >> dyb[i] >> y2b[i] >> dy2b[i] >> y3b[i] >> dy3b[i];
			if (col2==10) *in2 >> xb[i] >> dxb[i] >> yb[i] >> dyb[i] >> y2b[i] >> dy2b[i] >> y3b[i] >> dy3b[i] >> y4b[i] >> dy4b[i];
			i++;
			}
		}

	for (k=0;k<i;k++)			
		{
		if (argc>6) 
			{
			yb[k]=yb[k]/norm2;
			dyb[k]=dyb[k]/norm2;	
			xb[k]=xb[k]*1;
	
			}
		}

	if (col2==2)
		{
		TGraph *gr0b = new TGraph(i-2,xb,yb);		// Graph declaration
		gr0b->SetLineColor(4);					
		gr0b->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
		gr0b->SetMarkerColor(4);						
		gr0b->SetMarkerStyle(20);					
		gr0b->SetTitle(title);					
		gr0b->GetXaxis()->SetTitle(xaxis);				
		gr0b->GetYaxis()->SetTitle(yaxis);				
		gr0b->GetXaxis()->SetTitleSize(0.06);
		gr0b->GetYaxis()->SetTitleSize(0.06);
		gr0b->GetXaxis()->SetLabelSize(0.05);
		gr0b->GetYaxis()->SetLabelSize(0.05);
		gr0b->GetXaxis()->CenterTitle();					
		gr0b->GetYaxis()->CenterTitle();	
		gr0b->Draw("samelP");
		}


	if ((col2==4)||(col2==5)||(col2==6)||(col2==8)||(col2==10))
		{
		TGraphErrors *gr1b = new TGraphErrors(i-1,xb,yb,dxb,dyb);		// Graph declaration
		gr1b->SetLineColor(4);					
		gr1b->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
		gr1b->SetMarkerColor(4);						
		gr1b->SetMarkerStyle(20);					
		gr1b->SetTitle(title);					
		gr1b->GetXaxis()->SetTitle(xaxis);				
		gr1b->GetYaxis()->SetTitle(yaxis);				
		gr1b->GetXaxis()->SetTitleSize(0.06);
		gr1b->GetYaxis()->SetTitleSize(0.06);
		gr1b->GetXaxis()->SetLabelSize(0.05);
		gr1b->GetYaxis()->SetLabelSize(0.05);
		gr1b->GetXaxis()->CenterTitle();					
		gr1b->GetYaxis()->CenterTitle();	
		gr1b->Draw("samelP");
	
		if (col2==5)
			{
			TGraphErrors *gr1b = new TGraphErrors(i-1,xb,yb,0,dyb);		// Graph declaration
			gr1b->SetLineColor(4);					
			gr1b->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
			gr1b->SetMarkerColor(4);						
			gr1b->SetMarkerStyle(21);					
			gr1b->SetTitle(title);					
			gr1b->GetXaxis()->SetTitle(xaxis);				
			gr1b->GetYaxis()->SetTitle(yaxis);				
			gr1b->GetXaxis()->SetTitleSize(0.06);
			gr1b->GetYaxis()->SetTitleSize(0.06);
			gr1b->GetXaxis()->SetLabelSize(0.05);
			gr1b->GetYaxis()->SetLabelSize(0.05);
			gr1b->GetXaxis()->CenterTitle();					
			gr1b->GetYaxis()->CenterTitle();	
			gr1b->Draw("sameP");
			}
	if ((col2==5)||(col2==6)||(col2==8)||(col2==10)) 	
		{		
		if (col2==5)	 	
			{
			TGraphErrors *gr2b = new TGraphErrors(i-1,xb,y2b,0,dy2b);		// Graph declaration
			gr2b->SetLineColor(4);						// Line color 0=white 1=black, 2=red
			gr2b->SetLineWidth(2);						
			gr2b->SetMarkerColor(4);						
			gr2b->SetMarkerStyle(20);											
			gr2b->Draw("lPsame");
			}
		if (col2>5)	 	
			{
			TGraphErrors *gr2b = new TGraphErrors(i-1,xb,y2b,dxb,dy2b);		// Graph declaration
			gr2b->SetLineColor(4);						// Line color 0=white 1=black, 2=red
			gr2b->SetLineWidth(2);						
			gr2b->SetMarkerColor(4);						
			gr2b->SetMarkerStyle(20);											
			gr2b->Draw("lPsame");
			}
		if (col2>7)
			{		
			TGraphErrors *gr3b = new TGraphErrors(i-1,xb,y3b,dxb,dy3b);		// Graph declaration
			gr3b->SetLineColor(kGreen+3);						// Line color 0=white 1=black, 2=red
			gr3b->SetLineWidth(2);						
			gr3b->SetMarkerColor(kGreen+3);						
			gr3b->SetMarkerStyle(20);									
			gr3b->Draw("lPsame");
			}
		if (col2>9)
			{		
			TGraphErrors *gr4b = new TGraphErrors(i-1,xb,y4b,dxb,dy4b);		// Graph declaration
			gr4b->SetLineColor(6);						// Line color 0=white 1=black, 2=red
			gr4b->SetLineWidth(2);						
			gr4b->SetMarkerColor(6);						
			gr4b->SetMarkerStyle(20);									
			gr4b->Draw("lPsame");
			}

		}
	}
}


if (argc==6||argc>8)
{
	ifstream *in3 = new ifstream(file3);
	if(!*in3) 
		{cout << " ERROR OPENING FILE " <<  file3 << endl; 
		return 1;
		}
	else   
		{
		i=0;
		while (!in3->eof())
			{
			if (col3==2) *in3 >> xc[i] >> yc[i];
			if (col3==4) *in3 >> xc[i] >> dxc[i] >> yc[i] >> dyc[i];  		//if (col==4) *in >> x[i] >> y[i] >> dx[i] >> dy[i];
			if (col3==5) *in3 >> xc[i] >> yc[i] >> dyc[i] >> y2c[i] >> dy2c[i];
			if (col3==6) *in3 >> xc[i] >> dxc[i] >> yc[i] >> dyc[i] >> y2c[i] >> dy2c[i];  
			if (col3==8) *in3 >> xc[i] >> dxc[i] >> yc[i] >> dyc[i] >> y2c[i] >> dy2c[i] >> y3c[i] >> dy3c[i];
			if (col3==10) *in3 >> xc[i] >> dxc[i] >> yc[i] >> dyc[i] >> y2c[i] >> dy2c[i] >> y3c[i] >> dy3c[i] >> y4c[i] >> dy4c[i];
			i++;
			}
		}

	for (k=0;k<i;k++)			
		{
		if (argc==10)
			{
			yc[k]=yc[k]/norm3;
			dyc[k]=dyc[k]/norm3;	
			xc[k]=xc[k]*6.9;
	
			}
		}

	if (col3==2)
		{
		TGraph *gr0c = new TGraph(i-2,xc,yc);		// Graph declaration
		gr0c->SetLineColor(6);					
		gr0c->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
		gr0c->SetMarkerColor(6);						
		gr0c->SetMarkerStyle(20);					
		gr0c->SetTitle(title);					
		gr0c->GetXaxis()->SetTitle(xaxis);				
		gr0c->GetYaxis()->SetTitle(yaxis);				
		gr0c->GetXaxis()->SetTitleSize(0.06);
		gr0c->GetYaxis()->SetTitleSize(0.06);
		gr0c->GetXaxis()->SetLabelSize(0.05);
		gr0c->GetYaxis()->SetLabelSize(0.05);
		gr0c->GetXaxis()->CenterTitle();					
		gr0c->GetYaxis()->CenterTitle();	
		gr0c->Draw("samelP");
		}


	if ((col3==4)||(col3==5)||(col3==6)||(col3==8)||(col3==10))
		{
		TGraphErrors *gr1c = new TGraphErrors(i-1,xc,yc,dxc,dyc);		// Graph declaration
		gr1c->SetLineColor(kGreen+3);					
		gr1c->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
		gr1c->SetMarkerColor(kGreen+3);						
		gr1c->SetMarkerStyle(20);					
		gr1c->SetTitle(title);					
		gr1c->GetXaxis()->SetTitle(xaxis);				
		gr1c->GetYaxis()->SetTitle(yaxis);				
		gr1c->GetXaxis()->SetTitleSize(0.06);
		gr1c->GetYaxis()->SetTitleSize(0.06);
		gr1c->GetXaxis()->SetLabelSize(0.05);
		gr1c->GetYaxis()->SetLabelSize(0.05);
		gr1c->GetXaxis()->CenterTitle();					
		gr1c->GetYaxis()->CenterTitle();	
		gr1c->Draw("samelP");
	
		if (col3==5)
			{
			TGraphErrors *gr1c = new TGraphErrors(i-1,xc,yc,0,dyc);		// Graph declaration
			gr1c->SetLineColor(kGreen+3);					
			gr1c->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
			gr1c->SetMarkerColor(kGreen+3);						
			gr1c->SetMarkerStyle(21);					
			gr1c->SetTitle(title);					
			gr1c->GetXaxis()->SetTitle(xaxis);				
			gr1c->GetYaxis()->SetTitle(yaxis);				
			gr1c->GetXaxis()->SetTitleSize(0.06);
			gr1c->GetYaxis()->SetTitleSize(0.06);
			gr1c->GetXaxis()->SetLabelSize(0.05);
			gr1c->GetYaxis()->SetLabelSize(0.05);
			gr1c->GetXaxis()->CenterTitle();					
			gr1c->GetYaxis()->CenterTitle();	
			gr1c->Draw("sameP");
			}
	if ((col3==5)||(col3==6)||(col3==8)||(col3==10)) 	
		{		
		if (col3==5)	 	
			{
			TGraphErrors *gr2c = new TGraphErrors(i-1,xc,y2c,0,dy2c);		// Graph declaration
			gr2c->SetLineColor(kGreen+3);						// Line color 0=white 1=black, 2=red
			gr2c->SetLineWidth(2);						
			gr2c->SetMarkerColor(kGreen+3);						
			gr2c->SetMarkerStyle(20);											
			gr2c->Draw("lPsame");
			}
		if (col3>5)	 	
			{
			TGraphErrors *gr2c = new TGraphErrors(i-1,xc,y2c,dxc,dy2c);		// Graph declaration
			gr2c->SetLineColor(kGreen+3);						// Line color 0=white 1=black, 2=red
			gr2c->SetLineWidth(2);						
			gr2c->SetMarkerColor(kGreen+3);						
			gr2c->SetMarkerStyle(20);											
			gr2c->Draw("lPsame");
			}
		if (col3>7)
			{		
			TGraphErrors *gr3c = new TGraphErrors(i-1,xc,y3c,dxc,dy3c);		// Graph declaration
			gr3c->SetLineColor(kGreen+3);						// Line color 0=white 1=black, 2=red
			gr3c->SetLineWidth(2);						
			gr3c->SetMarkerColor(kGreen+3);						
			gr3c->SetMarkerStyle(20);									
			gr3c->Draw("lPsame");
			}
		if (col3>9)
			{		
			TGraphErrors *gr4c = new TGraphErrors(i-1,xc,y4c,dxc,dy4c);		// Graph declaration
			gr4c->SetLineColor(6);						// Line color 0=white 1=black, 2=red
			gr4c->SetLineWidth(2);						
			gr4c->SetMarkerColor(6);						
			gr4c->SetMarkerStyle(20);									
			gr4c->Draw("lPsame");
			}

		}
	}

}




/*
TLatex *tx = new TLatex();
tx->SetNDC();
tx->SetTextFont(62);
tx->SetTextColor(36);
tx->SetTextAlign(12);
tx->SetTextSize(0.05);
tx->SetTextColor(2);
tx->DrawLatex(0.8,0.40,"Serie 1");*/
/*
TMarker *marker = new TMarker(260,0.83,21);
marker->SetMarkerColor(2);
marker->SetMarkerSize(1.0);
marker->Draw();
*/
if ((col==5)||(col==6)||(col==8))
	{
	tx->SetTextColor(4);
	tx->DrawLatex(0.8,0.35,"Serie 2");
	TMarker *marker2 = new TMarker(260,0.79,20);
	marker2->SetMarkerColor(4);
	marker2->SetMarkerSize(1.0);
	marker2->Draw();
	if (col==8) 
		{
		tx->SetTextColor(kGreen+3);
		tx->DrawLatex(0.8,0.30,"Serie 3");
		TMarker *marker3 = new TMarker(260,0.75,22);
		marker3->SetMarkerColor(kGreen+3);
		marker3->SetMarkerSize(1.0);
		marker3->Draw();
		}	

	}



if(argc==2&&col!=2)
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
			if (col==2) *in2 >> x[i] >> y[i];
			if (col==4) *in2 >> x[i] >> dx[i] >> y[i] >> dy[i];  //if (col==4) *in >> x[i] >> y[i] >> dx[i] >> dy[i];
			if (col==5) *in2 >> x[i] >> y[i] >> dy[i] >> y2[i] >> dy2[i];
			if (col==6) *in2 >> x[i] >> dx[i] >> y[i] >> dy[i] >> y2[i] >> dy2[i];
			if (col==8) *in2 >> x[i] >> dx[i] >> y[i] >> dy[i] >> y2[i] >> dy2[i] >> y3[i] >> dy3[i];
			if (col==10) *in2 >> x[i] >> dx[i] >> y[i] >> dy[i] >> y2[i] >> dy2[i] >> y3[i] >> dy3[i] >> y4[i] >> dy4[i];
			i++;
			}
		}
	
	for (k=0;k<i;k++)			
		{
		x[k]=x[k]*6.9;                 
		if (norm==1) 	
			{
			y[k]=y[k]/4723;
			dy[k]=dy[k]/4723;	
			}
		cout << y[k] << " " << y[0] << endl;
		}
	
	
	
	if ((col==4)||(col==5)||(col==6)||(col==8))
		{
		TGraphErrors *gr1 = new TGraphErrors(i-1,x,y,dx,dy);		// Graph declaration
		gr1->SetLineColor(kBlue);					
		gr1->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
		gr1->SetMarkerColor(kBlue);						
		gr1->SetMarkerStyle(20);					
		gr1->SetTitle(title);					
		gr1->GetXaxis()->SetTitle(xaxis);				
		gr1->GetYaxis()->SetTitle(yaxis);				
		gr1->GetXaxis()->SetTitleSize(0.06);
		gr1->GetYaxis()->SetTitleSize(0.06);
		gr1->GetXaxis()->SetLabelSize(0.05);
		gr1->GetYaxis()->SetLabelSize(0.05);
		gr1->GetXaxis()->CenterTitle();					
		gr1->GetYaxis()->CenterTitle();	
		gr1->Draw("samecP");
		if ((col==5)||(col==6)||(col==8)) 	
			{		
			TGraphErrors *gr2 = new TGraphErrors(i-1,x,y2,dx,dy2);		// Graph declaration
			gr2->SetLineColor(4);						// Line color 0=white 1=black, 2=red
			gr2->SetLineWidth(2);						
			gr2->SetMarkerColor(4);						
			gr2->SetMarkerStyle(20);											
			gr2->Draw("cPsame");
			if (col==8)
				{		
				TGraphErrors *gr3 = new TGraphErrors(i-1,x,y3,dx,dy3);		// Graph declaration
				gr3->SetLineColor(kGreen+3);						// Line color 0=white 1=black, 2=red
				gr3->SetLineWidth(2);						
				gr3->SetMarkerColor(kGreen+3);						
				gr3->SetMarkerStyle(20);									
				gr3->Draw("cPsame");
				}
			}
		}
	
}

if (argc==8)
	{
	ifstream *in3 = new ifstream(file3);
	if(!*in3) 
		{cout << " ERROR OPENING FILE " <<  file3 << endl; 
		return 1;
		}
	else   
		{
		i=0;
		while (!in3->eof())
			{
			*in3 >> x[i] >> y[i];
			i++;
			}
		}
	TGraph *gr0c = new TGraph(i-2,x,y);		// Graph declaration
	gr0c->SetLineColor(5);					
	gr0c->SetLineWidth(2);						// Line color 0=white 1=black, 2=red
	gr0c->SetMarkerColor(5);						
	gr0c->SetMarkerStyle(20);					
	gr0c->Draw("samelP");
	}


	
#if GRAPH
	theApp->Run(kTRUE);						
	delete theApp;
#endif 

return 0;
}
