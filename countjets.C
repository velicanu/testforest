#include "HiForestAnalysis/hiForest.h"


const float pi = 3.1415926;

void countjets(string filename, double ptcut)
{
  HiForest * c = new HiForest(filename.data(),"forest",cPPb,0);
  c->InitTree();
  int nentries = (int)c->GetEntries();
  int njets = 0;
  TFile * outf = new TFile("recothreejets.root","recreate");
  TH1D * hj3pt = new TH1D("hj3pt","",50,0,200);
  TH1D * hj13dphi = new TH1D("hj13dphi","",50,-pi,pi);
  TH1D * hj23dphi = new TH1D("hj23dphi","",50,-pi,pi);
  TH1D * hj13deta = new TH1D("hj13deta","",50,-5,5);
  TH1D * hj23deta = new TH1D("hj23deta","",50,-5,5);
  TH1D * hj123dpt = new TH1D("hj123dpt","",50,-200,200);
  // c->LoadNoTrees();
  // c->hasSkimTree = true;
  // c->hasAk3JetTree = true;
  for (int i_entry = 0; i_entry < nentries; ++i_entry)
  {
    c->GetEntry(i_entry);
    if(c->skim.pHBHENoiseFilter && c->skim.pPAcollisionEventSelectionPA)
    {
      std::vector<int> vjets ; 
      for(int i = 0 ; i < c->ak3PF.nref-1 ; ++i)
      {
        if(fabs(c->ak3PF.jteta[i]) > 2.0) continue;  //find jets in |eta| < 2
        vjets.push_back(i);
      }
      if( vjets.size()<3 ) continue;
      if(fabs(c->ak3PF.jteta[vjets[0]]) > 1.6 || fabs(c->ak3PF.jteta[vjets[1]]) > 1.6) continue; //enforce leading and subleading are withing |eta|<1.6
      if(c->ak3PF.jtpt[vjets[0]] < 120 ) continue;
      if(c->ak3PF.jtpt[vjets[1]] <  50 ) continue;
      if(c->ak3PF.jtpt[vjets[2]] <  15 ) continue;
      float dijetdphi = fabs(c->ak3PF.jtphi[vjets[0]] - c->ak3PF.jtphi[vjets[1]]);
      if(dijetdphi > pi) dijetdphi = 2 * pi - dijetdphi;
      if(dijetdphi < 5 * pi / 6) continue;
      
      //! Fill third jet histograms
      hj3pt->Fill(c->ak3PF.jtpt[vjets[2]]);
      float j13dphi, j23dphi, j13deta, j23deta, j123dpt;
      j13dphi = c->ak3PF.jtphi[vjets[0]] - c->ak3PF.jtphi[vjets[2]];
      j23dphi = c->ak3PF.jtphi[vjets[1]] - c->ak3PF.jtphi[vjets[2]];
      j13deta = c->ak3PF.jteta[vjets[0]] - c->ak3PF.jteta[vjets[2]];
      j23deta = c->ak3PF.jteta[vjets[1]] - c->ak3PF.jteta[vjets[2]];
      j123dpt = c->ak3PF.jtpt[vjets[0]] - c->ak3PF.jtpt[vjets[1]] - c->ak3PF.jtpt[vjets[2]];
      hj13dphi->Fill(j13dphi);
      hj23dphi->Fill(j23dphi);
      hj13deta->Fill(j13deta);
      hj23deta->Fill(j23deta);
      hj123dpt->Fill(j123dpt);
      
    }
    if(i_entry % 10000 == 0 ) cout<<i_entry<<" / "<<nentries<<endl;
  }
  cout<<njets<<endl;
  outf->Write();
  outf->Close();
}

void countgenjets(string filename, double ptcut)
{
  HiForest * c = new HiForest(filename.data(),"forest",cPPb,0);
  c->InitTree();
  int nentries = (int)c->GetEntries();
  int njets = 0;
  TFile * outf = new TFile("threegenjets.root","recreate");
  TH1D * hj3pt = new TH1D("hg3pt","",50,0,200);
  TH1D * hj13dphi = new TH1D("hg13dphi","",50,-pi,pi);
  TH1D * hj23dphi = new TH1D("hg23dphi","",50,-pi,pi);
  TH1D * hj13deta = new TH1D("hg13deta","",50,-5,5);
  TH1D * hj23deta = new TH1D("hg23deta","",50,-5,5);
  TH1D * hj123dpt = new TH1D("hg123dpt","",50,-200,200);
  // c->LoadNoTrees();
  // c->hasSkimTree = true;
  // c->hasAk3JetTree = true;
  for (int i_entry = 0; i_entry < nentries; ++i_entry)
  {
    c->GetEntry(i_entry);
    if(c->skim.pHBHENoiseFilter && c->skim.pPAcollisionEventSelectionPA)
    {
      std::vector<int> vjets ; 
      for(int i = 0 ; i < c->ak3PF.ngen-1 ; ++i)
      {
        if(fabs(c->ak3PF.refeta[i]) > 2.0) continue;  //find jets in |eta| < 2
        vjets.push_back(i);
      }
      if( vjets.size()<3 ) continue;
      if(fabs(c->ak3PF.refeta[vjets[0]]) > 1.6 || fabs(c->ak3PF.refeta[vjets[1]]) > 1.6) continue; //enforce leading and subleading are withing |eta|<1.6
      if(c->ak3PF.refpt[vjets[0]] < 120 ) continue;
      if(c->ak3PF.refpt[vjets[1]] <  50 ) continue;
      if(c->ak3PF.refpt[vjets[2]] <  15 ) continue;
      float dijetdphi = fabs(c->ak3PF.refphi[vjets[0]] - c->ak3PF.refphi[vjets[1]]);
      if(dijetdphi > pi) dijetdphi = 2 * pi - dijetdphi;
      if(dijetdphi < 5 * pi / 6) continue;
      
      //! Fill third jet histograms
      hj3pt->Fill(c->ak3PF.refpt[vjets[2]]);
      float j13dphi, j23dphi, j13deta, j23deta, j123dpt;
      j13dphi = c->ak3PF.refphi[vjets[0]] - c->ak3PF.refphi[vjets[2]];
      j23dphi = c->ak3PF.refphi[vjets[1]] - c->ak3PF.refphi[vjets[2]];
      j13deta = c->ak3PF.refeta[vjets[0]] - c->ak3PF.refeta[vjets[2]];
      j23deta = c->ak3PF.refeta[vjets[1]] - c->ak3PF.refeta[vjets[2]];
      j123dpt = c->ak3PF.refpt[vjets[0]] - c->ak3PF.refpt[vjets[1]] - c->ak3PF.refpt[vjets[2]];
      hj13dphi->Fill(j13dphi);
      hj23dphi->Fill(j23dphi);
      hj13deta->Fill(j13deta);
      hj23deta->Fill(j23deta);
      hj123dpt->Fill(j123dpt);
      
    }
    if(i_entry % 10000 == 0 ) cout<<i_entry<<" / "<<nentries<<endl;
  }
  cout<<njets<<endl;
  outf->Write();
  outf->Close();
}

int main(int argc, char *argv[])
{
  if(argc != 3)
  {
    cout<<"usage ./countjets.exe <filename> <jetptcut>"<<endl;
    return 1;
  }
  countjets(argv[1], std::atof(argv[2]));
  countgenjets(argv[1], std::atof(argv[2]));
  return 0;
}

// int getleadingindex(HiForest * c, std::vector<int> vjets)
// {
  // int maxindex = -1;
  // double maxpt = -1;
  // for (int i = 0; i < vjets.size(); ++i)
  // {
    // if(fabs(c->ak3PF.jteta[j]) < 2.0)
  // }
  // return maxindex;
// }

// int getsubleadingindex(HiForest * c, std::vector<int> vjets)
// {

// }