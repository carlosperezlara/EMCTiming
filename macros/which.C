
int which() {
  ifstream fin("logging");
  int lin, tmp;
  TString block;
  for(;;) {
    fin >> lin;
    if(!fin.good()) break;
    fin >> tmp >> tmp >> block;
    if(lin==25) continue;
    cout << lin << " " << block.Data() << endl;
  }
  return 0;
}
