Float_t getAngle(string angle="21",string spec="shms"){
  Float_t thetac=0;
  if(angle=="39")thetac=38.975;
  if(angle=="33")thetac=32.975;
  if(angle=="29")thetac=28.99;
  if(angle=="25")thetac=24.98;
  if(angle=="21"&&spec=="shms")thetac=21.035;
  if(angle=="21"&&spec=="hms")thetac=20.995;
  if(angle=="59")thetac=58.98;

  return thetac;
}
