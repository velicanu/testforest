#include "HiForestAnalysis/hiForest.h"

// hltpath: 40 = jet40 , 60 = jet60 , 80 = jet80 , else (0) = minbias
void testforest(int iteration, string filename, double jetetamin, double jetetamax, int hltpath)
{
  TH1F::SetDefaultSumw2();
  HiForest * c = new HiForest(filename.data(),"forest",cPPb,0);
  c->InitTree();
  double xbins[40] = {3,4,5,7,9,12,15,18,21,24,28,32,37,43,49,56,64,74,84,97,114,133,153,174,196,220,245,272,300,330,362,395,430,468,507,548,592,638,686,1000};
  int etamin = jetetamin*10;
  int etamax = jetetamax*10;
  TFile * outf;
  TH1F * jetspectra;
  TH1F * njets;
  if(hltpath==80)
  {
    outf = new TFile(Form("normalJet80outf_InEtaBin%d_%d__%d.root",etamin,etamax,iteration),"recreate");
    jetspectra = new TH1F(Form("Jet80JetPtInEtaBin%d_%d",etamin,etamax),";jet p_{T};",39,xbins);
    njets = new TH1F(Form("Jet80nJetsInEtaBin%d_%d",etamin,etamax),";n Jets;",11,-0.5,10.5);
  }
  else if(hltpath==60)
  {
    outf = new TFile(Form("normalJet60outf_InEtaBin%d_%d__%d.root",etamin,etamax,iteration),"recreate");
    jetspectra = new TH1F(Form("Jet60JetPtInEtaBin%d_%d",etamin,etamax),";jet p_{T};",39,xbins);
    njets = new TH1F(Form("Jet60nJetsInEtaBin%d_%d",etamin,etamax),";n Jets;",11,-0.5,10.5);
  }
  else if(hltpath==40)
  {
    outf = new TFile(Form("normalJet40outf_InEtaBin%d_%d__%d.root",etamin,etamax,iteration),"recreate");
    jetspectra = new TH1F(Form("Jet40JetPtInEtaBin%d_%d",etamin,etamax),";jet p_{T};",39,xbins);
    njets = new TH1F(Form("Jet40nJetsInEtaBin%d_%d",etamin,etamax),";n Jets;",11,-0.5,10.5);
  }
  else 
  {
    outf = new TFile(Form("normalMBoutf_InEtaBin%d_%d__%d.root",etamin,etamax,iteration),"recreate");
    jetspectra = new TH1F(Form("MBJetPtInEtaBin%d_%d",etamin,etamax),";jet p_{T};",39,xbins);
    njets = new TH1F(Form("MBnJetsInEtaBin%d_%d",etamin,etamax),";n Jets;",11,-0.5,10.5);
  }
  TH1F * runs = new TH1F(Form("runs"),";runs;",1133,210498,211631);
  
  for (int i = 0; i < c->GetEntries(); ++i)
  {
    if(i%10000==0) cout<<i<<"/"<<c->GetEntries()<<endl;
    c->GetEntry(i);

    // if( c->hlt.Run >= 210498 && c->hlt.Run < 211313 ) continue;  //pPb range
    // if( c->hlt.Run >= 211313 && c->hlt.Run <= 211631 ) continue;
    if(!c->skim.pPAcollisionEventSelectionPA) continue;
    if(!c->skim.pHBHENoiseFilter)            continue;
    float cmetashift = 0.0;
    if( c->hlt.Run >= 210498 && c->hlt.Run < 211313 ) cmetashift = 0.4654;  //pPb range
    if( c->hlt.Run >= 211313 && c->hlt.Run <= 211631 ) cmetashift = -0.4654; //Pbp range

    if(hltpath==80)
    {
      if(!c->hlt.HLT_PAJet80_NoJetID_v1) continue;
    }
    else if(hltpath==60)
    {
      if(!c->hlt.HLT_PAJet60_NoJetID_v1) continue;
    }
    else if(hltpath==40)
    {
      cout<<c->hlt.HLT_PAJet40_NoJetID_v1<<endl;
      if(!c->hlt.HLT_PAJet40_NoJetID_v1) continue;
    }
    else
    {
      if(!c->hlt.HLT_PAZeroBiasPixel_SingleTrack_v1) continue;
    }
    int n_jets = 0;
    for (int j = 0; j < c->akPu3PF.nref; ++j)
    {
      if(c->akPu3PF.jteta[j] + cmetashift < jetetamin || c->akPu3PF.jteta[j] + cmetashift > jetetamax) continue;
      jetspectra->Fill(c->akPu3PF.jtpt[j]);
      n_jets++;
    }
    njets->Fill(n_jets);
    runs->Fill(c->hlt.Run);
  }
  for (int i = 1; i < 40; ++i)
  {
    double value = jetspectra->GetBinContent(i);
    double error = jetspectra->GetBinError(i);
    double width = jetspectra->GetBinWidth(i);
    jetspectra->SetBinContent(i,value/width);
    jetspectra->SetBinError(i,error/width);
  }

  outf->Write();
  outf->Close();
}

int main(int argc, char *argv[])
{
  if(argc != 6)
  {
    cout<<"usage ./testforest.exe <filename> <jetetamin> <jetetamax> <hlt_value>"<<endl;
    return 1;
  }
  testforest(std::atoi(argv[1]),argv[2],std::atof(argv[3]),std::atof(argv[4]),std::atoi(argv[5]));
  return 0;
}
