#include "HiForestAnalysis/hiForest.h"

void testcorrelation(string filename)
{
  HiForest * c = new HiForest(filename.data(),"forest",cPPb,0);
  c->InitTree();
  int nentries = c->GetEntries();
  TFile * outf = new TFile("outf.root","recreate");
  TH1D * hJetEta = new TH1D("hJetEta","title;x-axis title;y-axis title",100,-3,3);
  TH1D * hTrackEta = new TH1D("hTrackEta","title;x-axis title;y-axis title",100,-3,3);
  TH1D * hDeltaEta = new TH1D("hDeltaEta","title;x-axis title;y-axis title",100,-6,6);
  for (int i = 0; i < nentries; ++i)
  {
    if(i%1000 == 0) cout<<i<<"/"<<nentries<<endl;
    c->GetEntry(i);
    if(c->akPu3Calo.nref > 0 )
    {
      float jeteta = c->akPu3Calo.jteta[0] ;
      hJetEta->Fill(jeteta);
      for (int j = 0; j < c->track.nTrk ; ++j)
      {
        float trketa = c->track.trkEta[j] ;
        hTrackEta->Fill(trketa);
        float deltaeta = jeteta - trketa;
        hDeltaEta->Fill(deltaeta);
      }
    }
  }
  outf->Write();
  outf->Close();
}

int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    cout<<"usage ./testcorrelation.exe <filename>"<<endl;
    return 1;
  }
  testcorrelation(argv[1]);
  return 0;
}
