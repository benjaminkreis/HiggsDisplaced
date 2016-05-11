#include "TStyle.h"
#include "TROOT.h"
#include "TPad.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "tdrstyle.C"

#include <iostream>

using namespace std;


class sample {
 public:
  sample(TString);
  ~sample();

  TString name;
  TString humanName;

  TFile* file;
  TTree* tree;

  UInt_t color = kBlack;
  
  TH1D lastHisto;
};
sample::sample(TString temp){
  name = temp;
  file = TFile::Open(name);
  tree = (TTree*)file->Get("treeR");
}
sample::~sample(){
  file->Close();
}


void drawPlots(std::vector<sample*> sampleVector, const TString varname, const int nbins, const float low, const float high,
	       const TString xtitle, const TString ytitle, const TString cutstring = "1")
{
  std::cout << "Start drawing" << std::endl;
  gStyle->SetOptStat(0);

  //TStyle* theStyle = 0;
  //initStyle(theStyle);
  //gROOT->SetStyle("CMS");
  setTDRStyle();

  std::map<TString, TH1D> histos;

  std::cout << "size " << sampleVector.size() << std::endl;

  double plotMinimum_ = 0;
  TCanvas thecanvas("c1", "c1", 640, 640);
  thecanvas.cd();
  
  float leg_x1=0.67, leg_y1=0.4, leg_x2=0.9, leg_y2=0.2;
  TLegend leg(leg_x1, leg_y1, leg_x2, leg_y2);
  leg.SetBorderSize(0);
  leg.SetLineStyle(0);
  leg.SetTextFont(42);
  leg.SetFillStyle(0);

  //Draw Histograms
  double max = 0;
  for(unsigned int isample=0; isample<sampleVector.size(); isample++) {

    //Create histogram
    TString hname = "h";
    hname+=isample;  
    histos[sampleVector.at(isample)->name] = TH1D(hname, hname, nbins, low, high);
    histos[sampleVector.at(isample)->name].Sumw2();

    cout << sampleVector.at(isample)->name << endl;
    cout << sampleVector.at(isample)->tree->GetName() << endl;

    //Project
    (sampleVector.at(isample)->tree)->Project(hname, varname, cutstring);
    sampleVector.at(isample)->lastHisto = *(TH1D*)histos[sampleVector.at(isample)->name].Clone("last_"+hname);
    //sampleVector.at(isample)->lastHisto = histos[sampleVector.at(isample)->name].Clone("last_"+hname);
    //sampleVector.at(isample)->lastHisto->SetDirectory(0);

    //Get what you want from histogram
    if( histos[sampleVector.at(isample)->name].GetMaximum() > max ) max = histos[sampleVector.at(isample)->name].GetMaximum();
    
  }

  //Second loop to draw (knowing max)
  int ndrawn = 0;
  for(unsigned int isample=0; isample<sampleVector.size(); isample++) {
    
    //Style
    if(isample==0) histos[sampleVector.at(isample)->name].SetTitle("");
    histos[sampleVector.at(isample)->name].SetLineWidth(2);
    histos[sampleVector.at(isample)->name].SetLineColor(sampleVector.at(isample)->color);
    histos[sampleVector.at(isample)->name].SetMarkerColor(sampleVector.at(isample)->color);
    histos[sampleVector.at(isample)->name].SetXTitle(xtitle);
    histos[sampleVector.at(isample)->name].SetYTitle(ytitle);
    if(high-low < 1.0)  histos[sampleVector.at(isample)->name].SetNdivisions(506);

    //Add to legend
    leg.AddEntry(&histos[sampleVector.at(isample)->name], sampleVector.at(isample)->humanName, "L");

    //Draw histogram
    TString drawOptions = "HIST";
    if(ndrawn>0) drawOptions += " SAME";
    if(ndrawn==0) histos[sampleVector.at(isample)->name].SetMaximum(1.1*max);
    if(ndrawn==0) histos[sampleVector.at(isample)->name].SetMinimum(plotMinimum_);
    histos[sampleVector.at(isample)->name].Draw(drawOptions);
    ndrawn++;
  }
  
  leg.Draw();

  thecanvas.SaveAs("h_"+varname+".pdf");

}//end of drawPlots


