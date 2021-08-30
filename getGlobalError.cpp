#include "getCSBerr.cpp"
#include "getKineUnc.cpp"
//#include "getRadError.cpp"

double getGlobalError(TGraph2D* grd,TGraph2D*  grh, Float_t ep, Double_t w2, Double_t thetac, Double_t hsec,Float_t deltah,string spec, string angle, string target, string mom, double xb, TGraph * g, TH1F* hkinErr, int bin){
  double ang=21;
  double spec_flag=0.;
  if(spec=="shms")spec_flag=1.;

  string kin=target+angle+"deg"+mom;
  if(angle=="25")ang=25;
  if(angle=="29")ang=29;
  if(angle=="33")ang=33;
  if(angle=="39")ang=39;
  //  TGraph *g=getRadError(ang, target);

  ofstream ofile;
  ofile.open("globErr.txt",ios::app | ios::out );

  double tgt=1.01;
  if(target=="d")tgt=2.01;

  double pion_err=0.0014;
  if(angle=="39")pion_err=.0028;
  double density_err=.011;
  double cer_err=0.001;
  double boil_err=0.00;//(Include in density_err)
  //  double kin_err=getKineUncRatio(grh, grd, ep, thetac);
  double kin_err=hkinErr->GetBinContent(bin);
  double csb_h_err=getCSBerr(thetac,hsec,deltah,tgt,0,grh);
  double csb_d_err=getCSBerr(thetac,hsec,deltah,tgt,0,grd);
  if(spec=="hms")csb_h_err=csb_h_err/.03;
  if(spec=="hms")csb_d_err=csb_d_err/.03;
  double csb_err=sqrt(pow(csb_h_err,2)+pow(csb_d_err,2));
  double acc_err=0.0018/pow(w2-1.1,1.13);
  double rad_err= g->Eval(xb)/100.;

  double result = sqrt(pow(pion_err,2) + pow(density_err,2) + pow(cer_err,2) + pow(boil_err,2) + pow(kin_err,2) + pow(csb_err,2) + pow(acc_err,2) + pow(rad_err,2));

  cout <<  pion_err  <<"\t"<<density_err<<"\t"<<cer_err<<"\t"<<boil_err<<"\t"<<kin_err<<"\t"<<csb_err<<"\t"<<acc_err<<"\t" <<rad_err<<"\t"<< result << endl;

  ofile << spec_flag <<"\t"<<ang<<"\t"<<xb<<"\t";
  ofile <<  pion_err  <<"\t"<<density_err<<"\t"<<cer_err<<"\t"<<boil_err<<"\t"<<kin_err<<"\t"<<csb_err<<"\t"<<acc_err<<"\t"<<rad_err<<"\t"<< result << endl;

  ofile.close();
  return result;
}  
