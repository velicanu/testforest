#include "HiForestAnalysis/hiForest.h"



void countjets(string filename, double ptcut)
{
  HiForest * c = new HiForest(filename.data(),"forest",cPPb,0);
  c->InitTree();
  int nentries = (int)c->GetEntries();
  int njets = 0;
  c->LoadNoTrees();
  c->hasSkimTree = true;
  c->hasAk3JetTree = true;
  for (int i = 0; i < nentries; ++i)
  {
    c->GetEntry(i);
    if(c->skim.pHBHENoiseFilter && c->skim.pPAcollisionEventSelectionPA)
    {
      cout<<"here   "<<endl;
      for (int j = 0; j < c->ak3PF.nref; ++j)
      {
        if(fabs(c->ak3PF.jteta[j]) < 1 && fabs(c->ak3PF.jtpt[j]) < ptcut ) njets++;
      }
    }
    if(i % 10000 == 0 ) break; cout<<i<<" / "<<nentries<<endl;
  }
  cout<<njets<<endl;
}

int main(int argc, char *argv[])
{
  if(argc != 3)
  {
    cout<<"usage ./countjets.exe <filename> <jetptcut>"<<endl;
    return 1;
  }
  countjets(argv[1], std::atof(argv[2]));
  return 0;
}
