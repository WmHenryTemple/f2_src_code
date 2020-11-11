double getLivetime(Double_t run=2550,TString what="lt"){

  FILE *fp = fopen("src/livetimes.txt","r");  
  Double_t rn, lt, err;
  Int_t ncols; 
  double_t result;
  while (1) { 

    ncols = fscanf(fp,"%lf %lf %lf ",&rn, &lt, &err);
    //    cout << run <<endl;
    if (ncols < 0) break;
    if(rn==run && what=="lt"){result=lt;break;}
    if(rn==run && what=="err"){result=err;break;}
  }
  return result;
}

