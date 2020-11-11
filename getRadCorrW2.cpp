#include <iostream>
#include <iomanip>
#include <fstream>
#include "TPaveLabel.h"
#include "TH2F.h"
#include "TCanvas.h"

using namespace std;

TGraph2D* getRadCorrW2(string target="c", Int_t choice=1){
  TGraph2D *graph;
  Float_t result=0;
  TString fname;
  ifstream file;
  string word;
  if(target=="c")fname = "src/model/abel/shms_c10.6_all.dat_inel_f1f220";
  if(target=="d")fname = "src/model/abel/shms_d10.6_all.dat_inel_f1f220";
  if(target=="h")fname = "src/model/abel/shms_h10.6_all.dat_inel_f1f220";

  file.open(fname);
  cout <<" Is the File open?"<<  file.is_open()<<endl;
    if(file.is_open()==1)
      {
      Int_t nlines=0;
      while(!file.eof())
	{
	  for (Int_t i=0;i<5;i++)
	    {
	      file >> word;
	    }
	  nlines++;
	}
      cout<<"There are " << nlines << " in " << fname<<endl;
      file.close();
      // start at top of file
      file.open(fname);
      //      const int size=nlines-1;
      const int size=nlines;
      Double_t eBeam[size];
      Double_t w2[size];
      Double_t theta[size];
      Double_t born[size];
      Double_t rci[size];
      Double_t y[size];

      for (Int_t i=0;i<size;i++)
	{
	  file >> eBeam[i];
	  file >> w2[i];
	  file >> theta[i];
	  file >> born[i];
	  file >> rci[i];
	  if(choice==1)y[i]=born[i];
	  if(choice==2)y[i]=rci[i];
	  if(choice==3)y[i]=born[i]/rci[i];
	}

      graph=new TGraph2D(size,w2,theta,y);
        }//if file is open
  file.close();
  return graph;
}
