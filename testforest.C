#include "HiForestAnalysis/hiForest.h"

void testforest(int iteration, string filename, double jetetamin, double jetetamax)
{
  HiForest * c = new HiForest(filename.data(),"forest",cPPb,0);
  c->InitTree();
  double xbins[41] = {0,3,4,5,7,9,12,15,18,21,24,28,32,37,43,49,56,64,74,84,97,114,133,153,174,196,220,245,272,300,330,362,395,430,468,507,548,592,638,686,1000};
  int etamin = jetetamin*10;
  int etamax = jetetamax*10;
  TFile * outf = new TFile(Form("outf_InEtaBin%d_%d__%d.root",etamin,etamax,iteration),"recreate");
  TH1F * jetspectra = new TH1F(Form("JetPtInEtaBin%d_%d",etamin,etamax),";jet p_{T};",40,xbins);
  for (int i = 0; i < c->GetEntries(); ++i)
  {
    if(i%10000==0) cout<<i<<"/"<<c->GetEntries()<<endl;
    c->GetEntry(i);
    for (int j = 0; j < c->akPu3PF.nref; ++j)
    {
      if(c->akPu3PF.jteta[j] < jetetamin || c->akPu3PF.jteta[j] > jetetamax) continue;
      jetspectra->Fill(c->akPu3PF.jtpt[j]);
    }
  }
  outf->Write();
  outf->Close();
}

int main(int argc, char *argv[])
{
  if(argc != 5)
  {
    cout<<"usage ./testforest.exe <filename> <jetetamin> <jetetamax>"<<endl;
    return 1;
  }
  testforest(std::atoi(argv[1]),argv[2],std::atof(argv[3]),std::atof(argv[4]));
  return 0;
}
