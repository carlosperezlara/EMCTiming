float step1_sector[8];
float step4_sector[8];
int isbad[24768];
float tdcmin[24768];
float tdcmax[24768];
const int nbinsx = 242;
double binx[nbinsx];
float MyLC[24768];
float wk0[24768];
float wk1[24768];
float wk2[24768];
float offtwr[24768];
float restwr[24768];
int secs[9] = { 0, 2592, 5184, 7776, 10368,
		12960, 15552, 20160, 24768 };
double SpeedOfLight = 29.979245829979; //[cm/ns]

void LoadLCs() {
  ifstream rr("lcs.txt");
  int N=0;
  for(int tid;;++N) {
    rr >> tid;
    if(!rr.good()) break;
    rr >> MyLC[tid];
  }
  cout << "LOADED LCs FOR " << N << " CHANNELS" << endl;
  rr.close();
}

void ProduceTables() {
  //ofstream ftab1("table1_TOF.txt");
  //ftab1.close();
  //join step1_timemean.dat step4_offset.dat > table1_TOF.txt
  ofstream ftab2("table2_TOF.txt");
  for(int i=0; i!=24768; ++i) {
    if(isbad[i]!=0) restwr[i] = 10; // this will disable the tof in mCAreco
    ftab2 << i << " " << wk0[i] << " " << wk1[i] << " " << wk2[i] << " ";
    ftab2 << offtwr[i] << " " << restwr[i] << " " << MyLC[i] << endl;
  }
  ftab2.close();
}

void definebins() {
  for(int i=0; i!=100; ++i) {
    binx[i] = 50+i*3;
  }
  for(int i=0; i!=50; ++i) {
    binx[i+100] = 350+i*6;
  }
  for(int i=0; i!=50; ++i) {
    binx[i+150] = 650+i*12;
  }
  for(int i=0; i!=30; ++i) {
    binx[i+200] = 1250+i*30;
  }
  for(int i=0; i!=10; ++i) {
    binx[i+230] = 2150+i*100;
  }
  binx[240] = 3500;
  binx[241] = 4000;
}

void LoadBadTowers() {
  for(int i=0; i!=24768; ++i) isbad[i] = 0;
  ifstream badt("badtowerstof.dat");
  int tid, bd;
  int nnn=0;
  for(;;++nnn) {
    badt >> tid;
    if(!badt.good()) break;
    badt >> bd;
    isbad[tid] = bd;
  }
  badt.close();
  cout << " BAD TOWERS LOADED " << nnn << endl;
}

void step1(int myrun) {
  ifstream fin("step1_timemean.dat");
  float tmp;
  int run;
  for(;;) {
    fin >> run;
    if(!fin.good()) break;
    if(run==myrun) {
      cout << "RUN FOUND FOR STEP 1" << endl;
      fin >> step1_sector[0];
      fin >> step1_sector[1];
      fin >> step1_sector[2];
      fin >> step1_sector[3];
      fin >> step1_sector[4];
      fin >> step1_sector[5];
      fin >> step1_sector[6];
      fin >> step1_sector[7];
    } else {
      fin >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp;
    }
  }
  fin.close();
}

void step2() {
  ifstream fin;
  fin.open("step2_walks.dat");
  int NN=0;
  for(;;++NN) {
    int tor=0;
    fin >> tor;
    if(!fin.good()) break;
    fin >> wk0[tor] >> wk1[tor] >> wk2[tor];
  }
  cout << "STEP2. LOAD " << NN << " WALK CORRECTIONS" << endl;
  fin.close();
}

void step4(int myrun) {
  ifstream fin("step4_offset.dat");
  float tmp;
  int run;
  for(;;) {
    fin >> run;
    if(!fin.good()) break;
    if(run==myrun) {
      cout << "RUN FOUND FOR STEP 4" << endl;
      fin >> step4_sector[0];
      fin >> step4_sector[1];
      fin >> step4_sector[2];
      fin >> step4_sector[3];
      fin >> step4_sector[4];
      fin >> step4_sector[5];
      fin >> step4_sector[6];
      fin >> step4_sector[7];
    } else {
      fin >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp;
    }
  }
  fin.close();
}

void step5() {
  ifstream fin;
  fin.open("step5_twroffset.dat");
  int NN=0;
  float tmp;
  for(;;++NN) {
    int tor=0;
    fin >> tor;
    if(!fin.good()) break;
    fin >> tmp >> offtwr[tor] >> restwr[tor];
  }
  cout << "STEP5. LOAD " << NN << " TOWER FINAL CORRECTIONS" << endl;
  fin.close();
  fin.open("step5_twroffset.dat.adds");
  NN=0;
  for(;;++NN) {
    int tor=0;
    fin >> tor;
    if(!fin.good()) break;
    fin >> tmp >> offtwr[tor] >> restwr[tor];
  }
  cout << "STEP5. PLUS " << NN << " FIXES" << endl;
  fin.close();
}


void loadranges() {
  ifstream rr;
  rr.open("ranges.dat");
  for(;;) {
    int tor=0;
    rr >> tor;
    if(!rr.good()) break;
    int a, b;
    rr >> a >> b;
    tdcmin[tor] = a-0.5;
    tdcmax[tor] = b-0.5;
  }
  rr.close();
}
