#include "configtime.h"
TH1F *sigmas[8];

int step5_plotter() {
  LoadBadTowers();
  Float_t twr[8][5000];
  Float_t a[8][5000];
  Float_t m[8][5000];
  Float_t s[8][5000];
  int nn[8]={0,0,0,0,0,0,0,0};
  int tmp;
  float ftmp;

  ifstream fin("step5_twroffset.dat");
  for(;;) {
    fin >> tmp;
    if(!fin.good()) break;
    //cout << tmp << " " << isbad[tmp] << endl;
    if(isbad[tmp]!=0) {
      fin >> ftmp >> ftmp >> ftmp;
      continue;
    }
    int ss=0;
    for(int i=0; i!=8; ++i) {
      if(tmp>secs[i]) ss = i;
    }
    //cout << " " << ss << " " << tmp << endl;
    int n = nn[ss];
    twr[ss][n] = tmp;
    fin >> a[ss][n] >> m[ss][n] >> s[ss][n];
    ++nn[ss];
  }
  fin.close();
  ifstream fin("step5_twroffset.dat.adds");
  for(;;) {
    fin >> tmp;
    if(!fin.good()) break;
    int ss=0;
    for(int i=0; i!=8; ++i) {
      if(tmp>secs[i]) ss = i;
    }
    int idx=-1;
    for(int i=0; i!=nn[ss]; ++i) {
      if(twr[ss][i]==tmp) {
	idx = i;
      }
    }
    cout << tmp << " ";
    if(idx>-1) {
      cout << " REPLACING" << endl;
      fin >> a[ss][idx] >> m[ss][idx] >> s[ss][idx];
    } else {
      cout << " SKIPPING" << endl;
      fin >> ftmp >> ftmp >> ftmp;
    }
  }
  for(int ii=0; ii!=8; ++ii) {
    cout << "SECTOR " << ii << endl;
    for(int jj=0; jj!=nn[ii]; ++jj) {
      bool tagged = false;
      //if( a[ii][jj]>4000. || a[ii][jj]<500. ) {
      //	tagged = true;
      //}
      if( m[ii][jj]>+1.0 || m[ii][jj]<-2.0 ) {
	tagged = true;
      }
      if(tagged) {
	cout << twr[ii][jj] << " needs checking " << endl;
      }
    }
  }

  
  TCanvas *main[8];
  TGraph *grA[8];
  TGraph *grM[8];
  TGraph *grS[8];
  for(int i=0; i!=8; ++i) {
    //cout << nn[i] << endl;
    grA[i] = new TGraph(nn[i],twr[i],a[i]);
    grM[i] = new TGraph(nn[i],twr[i],m[i]);
    grS[i] = new TGraph(nn[i],twr[i],s[i]);
    main[i] = new TCanvas();
    main[i]->Divide(1,3);
    main[i]->cd(1); grA[i]->Draw("A*L");
    main[i]->cd(2); grM[i]->Draw("A*L");
    main[i]->cd(3); grS[i]->Draw("A*L");
    grA[i]->GetXaxis()->SetLabelSize(0.1);
    grM[i]->GetXaxis()->SetLabelSize(0.1);
    grS[i]->GetXaxis()->SetLabelSize(0.1);
    grA[i]->GetYaxis()->SetLabelSize(0.1);
    grM[i]->GetYaxis()->SetLabelSize(0.1);
    grS[i]->GetYaxis()->SetLabelSize(0.1);
  }

  LoadLCs();
  step2();
  step5();
  ProduceTables();

  return 0;
}
