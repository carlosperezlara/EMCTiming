#include "configtime.h"

int checkfinal(int twr) {
  TFile *file1 = new TFile("out/allTOF4.root");
  TFile *file2 = new TFile("out/allTOF5.root");
  TH2F *pro1 = (TH2F*) file1->Get("hTOF");
  TH2F *pro2 = (TH2F*) file2->Get("hTOF");
  TH1D *tof4 = pro1->ProjectionY( "TOF4", twr+1, twr+1 );
  TH1D *tof5 = pro2->ProjectionY( "TOF5", twr+1, twr+1 );
  tof4->SetLineColor(kBlue-3);
  float max4 = tof4->GetMaximum();
  float max5 = tof5->GetMaximum();
  tof4->GetYaxis()->SetRangeUser(0,max4>max5?max4:max5);    
  tof5->SetLineColor(kRed-3);
  tof4->Draw();
  tof5->Draw("same");
  return 0;
}
