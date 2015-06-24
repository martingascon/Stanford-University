//************** Copyright: Martin Gascon. Stanford University ***************************************
//included libraries
#include "libraries.h" 
#include "functions.h" 

using namespace std;  //std contains all the classes, objects and functions of the standard C++ library.

#define FILES 0
#define GRAPH 1

int main(int argc, char **argv) // argc = integer number of arguments; ** = points to a string; argv = string of parameters
{
//********************************** Variables declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv); // TRint = type of variable; theApp is name of variable you deine; * is a pointer to one character
gROOT->SetStyle("Plain"); 
gStyle->SetOptStat(0);    // display stats
gStyle->SetOptFit(0);     // display fit parameters 1 = on, 0 = off

Int_t i,j,k,l,m,N1=0,N2=0,NP=0;  
Char_t file[100],file2[100],ci[100]="",tit1[100],tit2[100],tit3[100],tit4[100]; //title is a string with 150 characters   //*sepa,,
Float_t minxt=0,maxxt=0,minyt=10,maxyt=0,minpt=10,maxpt=0,minyz=100,maxyz=0; 	



TH2F *h2x,*h2y,*h2pen,*h2yzero;              //,*h2xy;


TCanvas *c1 = new TCanvas("c1","Graph2D example",0,0,1400,800);
c1->SetFillColor(0);
c1->GetFrame()->SetFillColor(0); 
c1->GetFrame()->SetBorderMode(-1);
c1->GetFrame()->SetBorderSize(10);
c1->SetTitle("Canvas1");

TCanvas *c1b = new TCanvas("c1b","Graph2D example",0,0,1400,800);
c1b->SetFillColor(0);
c1b->GetFrame()->SetFillColor(0); 
c1b->GetFrame()->SetBorderMode(-1);
c1b->GetFrame()->SetBorderSize(10);
c1b->SetTitle("Canvas2");

TCanvas *c1c = new TCanvas("c1c","Graph2D example",0,0,1400,800);
c1c->SetFillColor(0);
c1c->GetFrame()->SetFillColor(0); 
c1c->GetFrame()->SetBorderMode(-1);
c1c->GetFrame()->SetBorderSize(10);
c1c->SetTitle("Canvas3");

TCanvas *c1d = new TCanvas("c1d","Graph2D example",0,0,1400,800);
c1d->SetFillColor(0);
c1d->GetFrame()->SetFillColor(0); 
c1d->GetFrame()->SetBorderMode(-1);
c1d->GetFrame()->SetBorderSize(10);
c1d->SetTitle("Canvas4");

TCanvas *c2 = new TCanvas("c2","Graph2D example",200,10,700,510);
c2->SetFillColor(0);
c2->GetFrame()->SetFillColor(0); 
c2->GetFrame()->SetBorderMode(-1);
c2->GetFrame()->SetBorderSize(10);
c2->SetTitle("Vm");


TVirtualPad *vp2 =  c2->cd();
vp2->SetFillColor(10);
vp2->SetBorderSize(2);
vp2->SetFrameFillColor(0);
vp2->SetLeftMargin(.05); 
vp2->SetRightMargin(.15);
vp2->SetBottomMargin(.05);
vp2->SetTopMargin(.15);

TCanvas *c3 = new TCanvas("c3","Graph2D example",210,20,710,520);
c3->SetFillColor(0);
c3->GetFrame()->SetFillColor(0); 
c3->GetFrame()->SetBorderMode(-1);
c3->GetFrame()->SetBorderSize(10);
c3->SetTitle("Min dI/dV");

TVirtualPad *vp3 =  c3->cd();
vp3->SetFillColor(10);
vp3->SetBorderSize(2);
vp3->SetFrameFillColor(0);
vp3->SetLeftMargin(.10);
vp3->SetRightMargin(.15);
vp3->SetBottomMargin(.10);
vp3->SetTopMargin(.10);

TCanvas *c4 = new TCanvas("c4","Graph2D example",220,30,720,530);
c4->SetFillColor(0);
c4->GetFrame()->SetFillColor(0); 
c4->GetFrame()->SetBorderMode(-1);
c4->GetFrame()->SetBorderSize(10);
c4->SetTitle("Slope");

TVirtualPad *vp4 =  c4->cd();
vp4->SetFillColor(10);
vp4->SetBorderSize(2);
vp4->SetFrameFillColor(0);
vp4->SetLeftMargin(.10);
vp4->SetRightMargin(.15);
vp4->SetBottomMargin(.10);
vp4->SetTopMargin(.10);

TCanvas *c5 = new TCanvas("c5","Graph2D example",230,40,730,540);
c5->SetFillColor(0);
c5->GetFrame()->SetFillColor(0); 
c5->GetFrame()->SetBorderMode(-1);
c5->GetFrame()->SetBorderSize(10);
c5->SetTitle("Y0");

TVirtualPad *vp5 =  c5->cd();
vp5->SetFillColor(10);
vp5->SetBorderSize(2);
vp5->SetFrameFillColor(0);
vp5->SetLeftMargin(.10);
vp5->SetRightMargin(.15);
vp5->SetBottomMargin(.10);
vp5->SetTopMargin(.10);

switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: m=sprintf(file,"%s.dat",argv[1]);		// FILENAME 	
		break;						 

	case 3: m=sprintf(file,"%s.dat",argv[1]);		// FILENAME 	
	 	m=sprintf(file2,"%s.dat",argv[2]);	
		break;	


default:
		MsgError();
		exit(1);
		break;
	};   


ifstream *in = new ifstream(file);
if(!*in) 
	{cout << " ERROR OPENING FILE " <<  file << endl; 
	}
else    {
	i=1;
	do	// do-while to find where the data starts
		{
		*in >> ci;   
		//cout << ci << endl;
	  		
		if ((strstr(ci,"NRows")!=NULL))  
			{
			*in >> ci;*in >> ci; 
	 		N1=atoi(ci);
			*in >> ci;*in >> ci;*in >> ci;  
			N2=atoi(ci);		
			*in >> ci; *in >> ci;*in >> ci; 
			NP=atoi(ci);
			cout << "NRows = "<< N2 << endl;
			cout << "NCols = "<< N1 << endl;
			cout << "Pages = "<< NP << endl;
			}
		if ((strstr(ci,"array:")!=NULL))	 i=0;
		}
	while (i!=0);               
	Float_t datos[N1][N2][NP], x[NP],miny[N1][N2],minx[N1][N2],aux[NP];
	TGraph *gr[N1][N2], *gr2[N1][N2];
	TGraphSmooth *gs[N1][N2];
	c1->Divide(15,15);
	c1b->Divide(15,15);
	c1c->Divide(15,15);
	c1d->Divide(15,15);
	for (i=0;i<NP;i++)		// load the values for x[i]
		{			
		*in >>  ci;               
		aux[i]=atof(ci);    	
		x[i]=-aux[i];
		}
	for (k=0;k<N2;k++)		// Initizialize minx and miny
		for (l=0;l<N1;l++)
		  	{
			minx[k][l]=100; 
			miny[k][l]=100;			
			}	

	i=1;
	do	// do-while to find where the data starts
		{
		*in >> ci;   
		if ((strstr(ci,"Data:")!=NULL))	 i=0;
		}
	while (i!=0);      
	for (k=0;k<N2;k++)			// I read the data and put them into a matrix
		for (l=0;l<N1;l++)
			for (j=0;j<NP;j++)
				{			
				*in >>  ci;               
				datos[k][l][j]=atof(ci);	 //cout <<	datos[k][l][j] << "\t";		//if (j==(NP-1)) cout<< endl;
				}
	delete in;


//	#if FILES
//		m=sprintf(tit1,"%s.root",argv[1]);
//		TFile *myfile = new TFile(tit1,"RECREATE");
//	#endif 







	if (argc==3)			// In case there is anothe file to be used as normalization
		{

		ifstream *in2 = new ifstream(file2);
		if(!*in2) 
			{cout << " ERROR OPENING FILE " <<  file2 << endl; 
			}
		else    {
			i=1;
			do	// do-while to find where the data starts
				{
				*in2 >> ci;  
				if ((strstr(ci,"array:")!=NULL))	 i=0;
				}
			while (i!=0);   

			Float_t datosb[N1][N2][NP], xb[NP],auxb[NP]; //minxb[N1][N2],
			//TGraph *grb[N1][N2], *gr2b[N1][N2];
			//TGraphSmooth *gsb[N1][N2];
			for (i=0;i<NP;i++)		// load the values for x[i]
				{			
				*in2 >>  ci;               
				auxb[i]=atof(ci);    	
				xb[i]=-auxb[i];
				}

			do	// do-while to find where the data starts
				{
				*in2 >> ci;   
				if ((strstr(ci,"Data:")!=NULL))	 i=0;
				}
			while (i!=0);  

			for (k=0;k<N2;k++)			// I read the data and put them into a matrix
				for (l=0;l<N1;l++)
					for (j=0;j<NP;j++)
						{			
						*in2 >>  ci;               
						datosb[k][l][j]=atof(ci);	 //cout <<	datos[k][l][j] << "\t";		//if (j==(NP-1)) cout<< endl;
						}
			delete in2;

			for (k=0;k<N2;k++)			// I read the data and put them into a matrix
				for (l=0;l<N1;l++)
					for (j=0;j<NP;j++)
						{			
						if (datosb[k][l][j]!=0)					
							datos[k][l][j]=(float)(datos[k][l][j]/datosb[k][l][j]);
						else
							datos[k][l][j]=(float)(datos[k][l][j]/(datosb[k][l][j+1]));				
						}
	
			}


		}












	for (k=0;k<N2;k++)			// I read the data and put them into a matrix
		for (l=0;l<N1;l++)
			{
			gr[k][l] = new TGraph(NP-2,x,datos[k][l]);				// Graph declaration
			gr[k][l]->SetLineColor(2);					
			gr[k][l]->SetLineWidth(3);						// Line color 0=white 1=black, 2=red
			gr[k][l]->SetMarkerColor(2);					//gr[0]->SetMarkerStyle(20);			
  			gs[k][l] = new TGraphSmooth("normal");
  			gr2[k][l] = gs[k][l]->SmoothSuper(gr[k][l],"",1);
 			gr2[k][l]->SetLineColor(2);					
			gr2[k][l]->SetLineWidth(3);				// Line color 0=white 1=black, 2=red
			gr2[k][l]->SetMarkerColor(2);
			if ((k<15)&&(l<15)) {c1->cd(1+k*15+l); gr2[k][l]->Draw("AlP");}
			if ((k<15)&&(l>14)&&(l<30)) { c1b->cd(1+k*15+l-15);gr2[k][l]->Draw("AlP");}
			if ((l<15)&&(k>14)&&(k<30)) { c1c->cd(1+(k-15)*15+l);gr2[k][l]->Draw("AlP");}
			if ((k>14)&&(l>14)) {c1d->cd(1+(k-15)*15+l-15); gr2[k][l]->Draw("AlP");}		
				
			//if ((k==0)&&(l==0)) 
			//c1->cd(0);
			//else 	gr[k][l]->Draw("samelP");	
//			#if FILES
//				m=sprintf(cnt,"%dx_%dy",l+1,k+1);
//				TCanvas *c4 = new TCanvas(cnt,"Graph2D example",200,10,700,510);
//				c4->cd();
//				gr[k][l]->Draw("alP");
//				c4->Write();
//				c4->Clear();
//			#endif 
			}	

	
	Int_t pm[N2][N1];
	Float_t slope[N2][N1],interc[N2][N1],yzero[N2][N1]; 
	Double_t ax[NP],ay[NP];


	for (k=0;k<N2;k++)		
		for (l=0;l<N1;l++)
			for (j=0;j<NP-2;j++)
				{
				m=gr2[k][l]->GetPoint(j,ax[j],ay[j]);
				datos[k][l][j]=(float)ay[j];     //cout << datos[k][l][j]  << "=datos    ay[]= " << ay[j] <<endl;
				}




	for (k=0;k<N2;k++)			
		for (l=0;l<N1;l++)
			for (j=0;j<NP;j++)
				{
				

				if (miny[k][l]>datos[k][l][j])
					{
					miny[k][l]=datos[k][l][j];			
					minx[k][l]=x[j];			
					pm[k][l]=j;
					}				
				}



	for (k=0;k<N2;k++)			// I read the data and put them into a matrix
		for (l=0;l<N1;l++)
			{
			TF1 *g1   = new TF1("g1","pol1",x[pm[k][l]+1],x[pm[k][l]+20]);    // minx[k][l]+0.002,minx[k][l]+0.022
			if ((k<15)&&(l<15)) {c1->cd(1+k*15+l); gr2[k][l]->Fit(g1,"RQ");}
			if ((k<15)&&(l>14)&&(l<30)) { c1b->cd(1+k*15+l-15);gr2[k][l]->Fit(g1,"RQ");}
			if ((l<15)&&(k>14)&&(k<30)) { c1c->cd(1+(k-15)*15+l);gr2[k][l]->Fit(g1,"RQ");}
			if ((k>14)&&(l>14)) { c1d->cd(1+(k-15)*15+l-15);gr2[k][l]->Fit(g1,"RQ");}						
			slope[k][l] = g1->GetParameter(1);  // get the slope of the fit  
			interc[k][l] = g1->GetParameter(0); 
			yzero[k][l] =  -1*interc[k][l]/slope[k][l];
			//yzero[k][l] =  0.1/slope[k][l]-1*interc[k][l]/slope[k][l];
			//cout << slope[k][l] << " pendiente " << k << " " << l << endl;				c1->cd(0);	
			}
	

	
#if FILES
	m=sprintf(tit4,"%s_yzero.txt",argv[1]);
	ofstream *out4 = new ofstream(tit4,ios::app);			
	for (k=0;k<N2;k++)			// I read the data and put them into a matrix
		for (l=0;l<N1;l++)
			{
			*out4 << yzero[k][l] << "\t"; 
			if (l==(N1-1)) 	*out4 << endl;       // if we got to the end, newline
			}
#endif



	minpt=slope[0][0];
	maxpt=slope[0][0];
	for (k=0;k<N2;k++)			// I look for the lowest min slope and the biggest min in slope
		for (l=0;l<N1;l++)
			{
			if (slope[k][l]<minpt) minpt=slope[k][l];
			if (slope[k][l]>maxpt) maxpt=slope[k][l];
			}
	h2pen = new TH2F("h2pen","",N2,minpt,maxpt,N1,minpt,maxpt);	


#if FILES
	m=sprintf(tit3,"%s_slope.txt",argv[1]);
	ofstream *out3 = new ofstream(tit3,ios::app);			
	for (k=0;k<N2;k++)			// I read the data and put them into a matrix
		for (l=0;l<N1;l++)
			{
			*out3 << slope[k][l] << "\t"; 
			if (l==(N1-1)) 	*out3 << endl;       // if we got to the end, newline
			}
#endif





	c4->cd();
	
	for (k=0;k<N2;k++)			// I read the data and put them into a matrix
		for (l=0;l<N1;l++)
			h2pen->SetBinContent(k+1,l+1,slope[k][l]);
	set_plot_style();
	h2pen->Draw("COLZ");
	h2pen->GetXaxis()->SetLabelSize(0);
	h2pen->GetYaxis()->SetLabelSize(0);
	h2pen->GetXaxis()->SetTickLength(0);
	h2pen->GetYaxis()->SetTickLength(0);
	h2pen->GetXaxis()->SetAxisColor(0);
	h2pen->GetYaxis()->SetAxisColor(0);

	h2pen->Smooth();


	//****************************************************** for yzero plot (limits and graph)

	minyz=yzero[0][0];
	maxyz=yzero[0][0];
	for (k=0;k<N2;k++)			// I look for the lowest min intersection in X and the biggest min in intersection in X
		for (l=0;l<N1;l++)
			{
			if (yzero[k][l]<minpt) minyz=yzero[k][l];
			if (yzero[k][l]>maxpt) maxyz=yzero[k][l];
			}
	
	h2yzero = new TH2F("h2yzero","",N2,minyz,maxyz,N1,minyz,maxyz);	

	c5->cd();
	
	for (k=0;k<N2;k++)			// I read the data and put them into a matrix
		for (l=0;l<N1;l++)
			h2yzero->SetBinContent(k+1,l+1,yzero[k][l]);
	set_plot_style();
	h2yzero->Draw("COLZ");
	h2yzero->GetXaxis()->SetLabelSize(0);
	h2yzero->GetYaxis()->SetLabelSize(0);
	h2yzero->GetXaxis()->SetTickLength(0);
	h2yzero->GetYaxis()->SetTickLength(0);
	h2yzero->GetXaxis()->SetAxisColor(0);
	h2yzero->GetYaxis()->SetAxisColor(0);
	h2yzero->Smooth();

	//******************************************************

	minxt=minx[0][0];
	maxxt=minx[0][0];
	
	for (k=0;k<N2;k++)			// I look for the lowest min voltage/amp and the biggest min in voltage/amp
		for (l=0;l<N1;l++)
			{
			if (minx[k][l]<minxt) minxt=minx[k][l];
			if (minx[k][l]>maxxt) maxxt=minx[k][l];
			if (miny[k][l]<minyt) minyt=miny[k][l];
			if (miny[k][l]>maxyt) maxyt=miny[k][l];
			}
	//cout << minyt << "=minyt   "<< maxyt << " =maxyt"<<endl; 




	c2->cd();
	//cout << "minxt="<< minxt << "  maxxt=" << maxxt << endl;
	h2x = new TH2F("h2x","",N2,minxt,maxxt,N1,minxt,maxxt);	
	for (k=0;k<N2;k++)			// I read the data and put them into a matrix
		for (l=0;l<N1;l++)
			h2x->SetBinContent(k+1,l+1,minx[k][l]);
		set_plot_style();
		h2x->Draw("COLZ");
		h2x->GetXaxis()->SetLabelSize(0);
		h2x->GetYaxis()->SetLabelSize(0);
		h2x->GetXaxis()->SetTickLength(0);
		h2x->GetYaxis()->SetTickLength(0);
		h2x->GetXaxis()->SetAxisColor(0);
		h2x->GetYaxis()->SetAxisColor(0);
		h2x->Smooth();


	c3->cd();
	h2y = new TH2F("h2y","",N2,minyt,maxyt,N1,minyt,maxyt);	
	for (k=0;k<N2;k++)			// I read the data and put them into a matrix
		for (l=0;l<N1;l++)
			{
			h2y->SetBinContent(k+1,l+1,miny[k][l]);
			}


	set_plot_style();
	h2y->Draw("COLZ");
	h2y->GetXaxis()->SetLabelSize(0);
	h2y->GetYaxis()->SetLabelSize(0);
	h2y->GetXaxis()->SetTickLength(0);
	h2y->GetYaxis()->SetTickLength(0);
	h2y->GetXaxis()->SetAxisColor(0);
	h2y->GetYaxis()->SetAxisColor(0);
	h2y->Smooth();
/*
	c3->cd();
//Float_t aux1,aux2;
	h2xy = new TH2F("h2xy","",N2,minxt*minyt,maxxt*maxyt,N1,minxt*minyt,maxyt*maxyt);	
	for (k=0;k<N2;k++)			// I read the data and put them into a matrix
		for (l=0;l<N1;l++)
			{
			//aux1=h2x->GetBinContent(k+1,l+1);
			//aux2=h2y->GetBinContent(k+1,l+1);

			h2xy->SetBinContent(k+1,l+1,minx[k][l]*miny[k][l]);
			//if (k==(N2-1)) cout <<  endl;
			}


	set_plot_style();
	h2xy->Draw("COLZ");
	h2xy->GetXaxis()->SetLabelSize(0);
	h2xy->GetYaxis()->SetLabelSize(0);
	h2xy->Smooth();
*/
c1->cd();



m=sprintf(tit1,"%s_x.png",argv[1]);
m=sprintf(tit2,"%s_y.png",argv[1]);

#if FILES

	c1->SaveAs(tit1);
	c2->SaveAs(tit2);
	m=sprintf(tit1,"minX_%s.txt",argv[1]);
	m=sprintf(tit2,"minY_%s.txt",argv[1]);
	ofstream *out1 = new ofstream(tit1,ios::app);
	ofstream *out2 = new ofstream(tit2,ios::app);
	for (l=0;l<N1;l++)
		for (k=0;k<N2;k++)
			{			
			*out1 << minx[k][l] << endl;// if (k==(N2-1)) *out1 <<  endl;
			*out2 << miny[k][l] << endl; //if (k==(N2-1)) *out2 <<  endl;

			}

	//c1->Write();
	//c2->Write();
	//h2x->Write();
	//h2y->Write();
	//myfile->Close();
#endif


//h1 = new TH1F("h1","",NP-2,x[0],x[NP-1]);	


/*
for (k=1;k<2;k++)			// I read the data and put them into a matrix
	for (l=1;l<2;l++)
		for (j=0;j<NP;j++)
				{			
				h1->SetBinContent(j,datos[k][l][j]);
				}	


	

h1->Draw("lp");



TF1 *f1 = new TF1("f1","pol2",la,lb); 				
	
	//f1->SetParLimits(0,50,150);		
	//f1->SetParLimits(0,0.03,0.05);
	//f1->SetParLimits(0,5,50);
	//f1->SetParLimits(0,05,0.9);


	f1->SetParameter(0,2.6);	f1->SetParameter(1,0.48);	
	f1->SetParameter(2,4); 		f1->SetParameter(3,0.3);	
	

	gr0->Fit("f1","QR+");
	gr0->Fit("f1","R");
*/
	}






/*




/*
gr[0] = new TGraph(NP-2,x,datos[0][0]);				// Graph declaration
gr[0]->SetLineColor(2);					
gr[0]->SetLineWidth(3);						// Line color 0=white 1=black, 2=red
gr[0]->SetMarkerColor(2);					//gr[0]->SetMarkerStyle(20);					
gr[0]->Draw("AlP");

gr[1] = new TGraph(NP,x,datos[1][0]);
gr[1]->SetLineColor(4);					
gr[1]->SetLineWidth(3);						// Line color 0=white 1=black, 2=red
gr[1]->SetMarkerColor(4);					//gr[0]->SetMarkerStyle(20);					
gr[1]->Draw("samelP");
*/

#if GRAPH
	theApp->Run(kTRUE);
	delete theApp;
#endif 

return 0;
}
