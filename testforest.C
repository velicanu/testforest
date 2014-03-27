#include "HiForestAnalysis/hiForest.h"
// #include <TH1D.h>
// #include <TFile.h>
// #include <TCanvas.h>
// #include <TRandom3.h>
// #include <fstream>
// #include <iostream>
// #include <math.h>


void testforest(string filename)
{
  HiForest * c = new HiForest(filename.data(),"forest",cPPb,0);
  c->InitTree();
}

int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    cout<<"usage ./testforest.exe <filename>"<<endl;
    return 1;
  }
  testforest(argv[1]);
  return 0;
}
