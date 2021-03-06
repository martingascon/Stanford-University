//************** Copyright: Martin Gascon. Stanford University ***************************************
//included libraries
#include "libraries.h" 
#include "functions.h" 


using namespace std;	//std contains all the classes, objects and functions of the standard C++ library.


int main(int argc, char **argv)
{
//********************************** Variables declaration ***********************************
TRint *theApp = new TRint("Rint", &argc, argv);
Int_t i,j,k,m,a=1,b=1000, old_a=1,old_b=1000,reb=1,first_file=1,last_file=1,con=0,date[3],tim[3],sec=0,factor=1,aux=0,n=8192,N=8192;  
Float_t data[N], sig_left=1.8,sig_right=1.8,mean0=0,r[3],dr[3],me[3],si[3],dm[3],ds[3],ndf=0,chis=0,chiondf=0,chiold=0,days=0;
Double_t par1[6],rana=0,ranb=0,signo=0;						
Char_t file[100],ci[100]="";
TH1I *H; 


ofstream *out = new ofstream("PHvsTime2.txt",ios::app);


for (k=0;k<3;k++) {me[k]=0;si[k]=0;dm[k]=0;ds[k]=0;} // variable initialization


switch (argc)
	{
	case 1: MsgError();
		exit(1);
		break;
	case 2: m=sprintf(file,"%s.mca",argv[1]);		// "FILENAME(WITHOUT NUMBER)"  (ONLY IF THE FILE ENDS IN "1")	
		break;						// ONLY IF A=1 B=1000  
	case 3: m=sprintf(file,"%s.mca",argv[1]);		// "FILENAME(WITHOUT NUMBER) REB"  (ONLY IF FIRSTFILE=1)
		last_file=atoi(argv[2]);			// ONLY IF A=1 B=1000  
		break;
	case 4: m=sprintf(file,"%s.mca",argv[1]);		// "FILENAME(WITHOUT NUMBER) FIRSTFILE LASTFILE"  
		first_file=atoi(argv[2]);			// ONLY IF A=1 B=1000  
		last_file=atoi(argv[3]);		
		break;
	case 5: m=sprintf(file,"%s.mca",argv[1]);		// "FILENAME(WITHOUT NUMBER) FIRSTFILE LASTFILE reb"   
		first_file=atoi(argv[2]);			// ONLY IF A=1 B=1000  
		last_file=atoi(argv[3]);		
		reb=atoi(argv[4]);				// REB = REBINING OF FOR EACH FILE (DEFAULT 1)
		break;
	case 6:	m=sprintf(file,"%s.mca",argv[1]);		// "FILENAME(WITHOUT NUMBER) FIRSTFILE LASTFILE A B" 
		first_file=atoi(argv[2]);			
		last_file=atoi(argv[3]);		
		a=atoi(argv[4]);b=atoi(argv[5]); 		// A AND B DEFINE THE RANGE TO FIT
		break;	
	case 7:	m=sprintf(file,"%s.mca",argv[1]);		// "FILENAME(WITHOUT NUMBER) FIRSTFILE LASTFILE A B REB" 
		first_file=atoi(argv[2]);			
		last_file=atoi(argv[3]);		
		a=atoi(argv[4]);b=atoi(argv[5]); 		// A AND B DEFINE THE RANGE TO FIT
		reb=atoi(argv[6]);				// REB = REBINING OF FOR EACH FILE (DEFAULT 1)
		break;	
	case 8:	m=sprintf(file,"%s.mca",argv[1]);		// "FILENAME(WITHOUT NUMBER) FIRSTFILE LASTFILE A B SIGM_LEFT SIGM_RIGHT" 
		first_file=atoi(argv[2]);			
		last_file=atoi(argv[3]);		
		a=atoi(argv[4]);b=atoi(argv[5]); 		// A AND B DEFINE THE RANGE TO FIT
		sig_left=atof(argv[6]);sig_right=atof(argv[7]); // IF WE WANT TO CHANGE THE SIGMAS ON THE LEFT AND ON THE RIGHT (DEFAULT 1 AND 2 RESP.)
		break;	
	};   



Double_t parg1[3],pare1[3]; 		

for (j=first_file;j<last_file+1;j++)
	{
	if (last_file<10)			m=sprintf(file,"%s%.1d.mca",argv[1],j);
	if ((last_file>9)&&(last_file<100))	m=sprintf(file,"%s%.2d.mca",argv[1],j);
	if ((last_file>99)&&(last_file<1000))	m=sprintf(file,"%s%.3d.mca",argv[1],j);
	if ((last_file>999)&&(last_file<10000))	m=sprintf(file,"%s%.4d.mca",argv[1],j);
	Read_MCA(file, data, days,N);
	H = new TH1I("H",file,N,0,N-1); 
	for (k=0;k<N;k++)			
		{
		H->Fill(k,data[k]);		// fill the histogram
		}
	H->Rebin(reb);
	old_a=a;
	old_b=b;
	TF1 *eg1   = new TF1("eg1",fit_egausb,a,b,6);
	TF1 *g1    = new TF1("g1","gaus",a*0.8,b*1.2);
	TF1 *e1    = new TF1("e1",Background_exp,a*0.9,b*1.1,2);
	TF1 *total1 = new TF1("total1",fit_egausb,a,b,6); // change added 6 instead of 5 and b in egaus
	ifstream *in2 = new ifstream(".param5.txt");
	if(!*in2) 
		{
		cout << " No previous file with parameters was found "  << endl; 
		}
	else    {		
		for (i=0;i<6;i++) 
			*in2 >> par1[i];                  
		eg1->SetParameters(par1[0],par1[1],par1[2],par1[3],par1[4],par1[5]); 
		}	
	H->Fit(eg1,"NR+");		
	eg1->GetParameters(&par1[0]);
	total1->SetParameters(par1);
	eg1->GetParameters(&par1[0]);
	do
		{
		chis = 0; ndf= 0; chiondf= 0;
		H->Fit(total1,"RQN+");
		total1->GetParameters(&par1[0]);
		g1->SetParameters(par1[3],par1[4],par1[5]);       // change indexes starting from 3 instead of 2
		e1->SetParameters(par1[0],par1[1],par1[2]);               // change added par1[2]
		me[0] = total1->GetParameter(4); 
		si[0] = total1->GetParameter(5);
		dm[0] = total1->GetParError(4);
		ds[0] = total1->GetParError(5);		
		Resol_egb(total1,r[0],dr[0]);
		srand ( (unsigned)time(NULL) );
		factor=(int)((b+a)/200);
		if (factor<1) factor=1;
		rana = rand() % factor + 1;
		ranb = rand() % factor + 1;	
		signo = rand() % 10 + 1; 		
		if (signo>5) signo=-1; 	else signo=1;   
		a=a+signo*1*int(rana); b = b+1*signo*int(ranb);	
		if (a<0.0) {a=-a;} if (b<0.0) {b =-b;}
		if (a>b) {aux=a; a=b; b=aux;}	
		total1->SetRange(a,b);
		chis = total1->GetChisquare();  
		ndf= total1->GetNDF();		
		chiondf=chis/ndf;
		con++;
 		cout << "a=" << a << " b=" << b << " X="<< chiondf << " n=" << con <<endl;
		} 
	while (chiondf>1.2&&con<50); 

	H->Fit(total1,"R+");
	total1->GetParameters(&par1[0]);
	total1->SetLineColor(4);
	g1->SetParameters(par1[3],par1[4],par1[5]);
	e1->SetParameters(par1[0],par1[1],par1[2]);
	me[0] = total1->GetParameter(4); 
	si[0] = total1->GetParameter(5);
	dm[0] = total1->GetParError(4);
	ds[0] = total1->GetParError(5);		

	Resol_egb(total1,r[0],dr[0]);
	if (me[0]<0) {me[0]=1;}
	if (me[0]>8000) {me[0]=1;}
	if (dm[0]<0) {dm[0]=10;}
	if (dm[0]>100) {dm[0]=10;}
	if (r[0]<0) {r[0]=1;}
	if (r[0]>100) {r[0]=1;}
	if (dr[0]<0) {dr[0]=0;}
	if (dr[0]>100) {dr[0]=0.9;}
	*out<<std::fixed<<std::setprecision(2) <<days <<"\t"<< 0.14 <<"\t" << std::fixed << std::setprecision(1)<< me[0] <<"\t"<< dm[0]*3 <<"\t"<<  r[0] <<"\t"<< dr[0] << endl;	
	cout<<std::fixed<<std::setprecision(2) <<days <<"\t"<< 0.14 <<"\t" << std::fixed << std::setprecision(1)<< me[0] <<"\t"<< dm[0]*3 <<"\t"<<  r[0] <<"\t"<< dr[0] << endl;
	H->Delete();		
	}


delete theApp;
return 0;
}
