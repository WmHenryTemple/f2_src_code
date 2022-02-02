#include "getCSBerr.cpp"
#include "getKineUnc.cpp"
//#include "getRadError.cpp"

double getGlobalError(TGraph2D* grd,TGraph2D*  grh, Float_t ep, Double_t w2, Double_t thetac, Double_t hsec,Float_t deltah,string spec, string angle, string target, string mom, double xb, TGraph * g, TH1F* hkinErr, int bin, double lte, double qerr, double boil_err){
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

  //Pion Contamination Error


  double pion_err=0.001;
  if(angle=="39")pion_err=.002;
  double density_err=.0075;
  double cer_err=0.003;

  if(target=="r"){
    pion_err=0.0014;
    if(angle=="39")pion_err=.0028;    
    density_err=0.011;
    cer_err=0.001;
  }
  

  double kin_err=hkinErr->GetBinContent(bin);//can handle h Vs d vs r

  double csb_h_err=getCSBerr(thetac,hsec,deltah,1.01,0,grh);
  double csb_d_err=getCSBerr(thetac,hsec,deltah,2.01,0,grd);
  if(spec=="hms")csb_h_err=csb_h_err/.03;
  if(spec=="hms")csb_d_err=csb_d_err/.03;
  double csb_err=0;
  if(target=="r")csb_err=sqrt(pow(csb_h_err,2)+pow(csb_d_err,2));
  if(target=="h")csb_err=csb_h_err;
  if(target=="d")csb_err=csb_d_err;  


  double acc_err=0.0018/pow(w2-1.1,1.13);
  double rad_err= g->Eval(xb)/100.;

  double result = sqrt(pow(pion_err,2) + pow(density_err,2) + pow(cer_err,2) + pow(boil_err,2) + pow(kin_err,2) + pow(csb_err,2) + pow(acc_err,2) + pow(rad_err,2)+pow(lte,2));

  cout <<  pion_err  <<"\t"<<density_err<<"\t"<<cer_err<<"\t"<<boil_err<<"\t"<<kin_err<<"\t"<<csb_err<<"\t"<<acc_err<<"\t" <<rad_err<<"\t"<< lte <<"\t"<<qerr<<"\t"<<boil_err<<"\t"<<result << endl;

  ofile << spec_flag <<"\t"<<ang<<"\t"<<xb<<"\t";
  ofile <<  pion_err  <<"\t"<<density_err<<"\t"<<cer_err<<"\t"<<boil_err<<"\t"<<kin_err<<"\t"<<csb_err<<"\t"<<acc_err<<"\t"<<rad_err<<"\t"<< lte <<"\t"<<qerr<<"\t"<<boil_err<<"\t"<<result << endl;

  ofile.close();
  return result;
}  
