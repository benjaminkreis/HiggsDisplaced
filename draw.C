#include "draw.h"

using namespace std;


void draw_in_PV_slices(){

  TString path = "/uscms_data/d3/mwalker/VHdisplaced/20160426_runAnalyisTrees/";

  std::vector<sample*> sampleVector;

  sample sample1(path+"allHistos_WH_HToSSTobbbb_WToLNu_MH125_MS25_ctauS100_13TeV.root");
  sample1.humanName = "sample 1";
  sample1.color = kRed;
  sampleVector.push_back(&sample1);

  sample sample2(path+"allHistos_WH_HToSSTobbbb_WToLNu_MH125_MS10_ctauS10_13TeV.root");
  sample2.humanName = "sample 2";
  sample2.color = kBlue;
  //sampleVector.push_back(&sample2);

  //drawPlots(sampleVector, "ALPHAMAX_ALLCALOJETS", 20, 0, 1, "ALPHAMAX_ALLCALOJETS", "Events", "NGOODVERTICES<10");

  //Gymnastics to plot same sample mutiple times with different cuts
  TString var = "ALPHAMAX_ALLCALOJETSMATCHED"; double min = 0; double max = 1; double ymax = -1;
  //TString var = "MEDIANIPLOG10SIG_ALLCALOJETS"; double min = -2; double max = 4; double ymax = 0.25;
  //TString var = "MEDIANLOG10TRACKANGLE_ALLCALOJETS"; double min = -4.5; double max = 0.5; double ymax = 0.35;

  std::vector<TH1D*> hvec;
  drawPlots(sampleVector, var, 20, min, max, var, "Events", "NGOODVERTICES<=5");
  hvec.push_back((TH1D*)sample1.lastHisto.Clone("upto5"));
  drawPlots(sampleVector, var, 20, min, max, var, "Events", "NGOODVERTICES>5&&NGOODVERTICES<=10");
  hvec.push_back((TH1D*)sample1.lastHisto.Clone("5to10"));
  drawPlots(sampleVector, var, 20, min, max, var, "Events", "NGOODVERTICES>10&&NGOODVERTICES<=15");
  hvec.push_back((TH1D*)sample1.lastHisto.Clone("10to15"));
  drawPlots(sampleVector, var, 20, min, max, var, "Events", "NGOODVERTICES>15&&NGOODVERTICES<=20");
  hvec.push_back((TH1D*)sample1.lastHisto.Clone("15to20"));
  drawPlots(sampleVector, var, 20, min, max, var, "Events", "NGOODVERTICES>20");
  hvec.push_back((TH1D*)sample1.lastHisto.Clone("20up"));

  const int color[7]={1,2,3,4,6,7,8};
  TLegend leg(0.7, 0.6, 0.88, 0.88);
  leg.SetBorderSize(0);
  leg.SetLineStyle(0);
  leg.SetTextFont(42);
  leg.SetFillStyle(0);
  TCanvas c("c", "c1", 640, 640);
  c.cd();
  for(unsigned int i = 0; i<hvec.size(); i++){
    hvec.at(i)->Scale(1.0/hvec.at(i)->Integral());
    if(i==0) hvec.at(i)->GetXaxis()->SetTitle(var);
    if(i==0) hvec.at(i)->GetYaxis()->SetTitle("Arb.");
    if(i==0 && ymax>0) hvec.at(i)->SetMaximum(ymax);
    hvec.at(i)->SetLineColor(color[i]);
    hvec.at(i)->SetLineWidth(2);
    //hvec.at(i)->DrawNormalized("HIST SAMES");
    hvec.at(i)->Draw("HIST SAMES");
    leg.AddEntry(hvec.at(i),hvec.at(i)->GetName(),"L");
  }
  leg.Draw();
  c.Print("overlay_"+var+".pdf");

}


void draw_fixedmass_varylifetime(){

  TString path = "/uscms_data/d3/mwalker/VHdisplaced/20160426_runAnalyisTrees/";
  
  std::vector<sample*> sampleVector;
  
  //WH, pick mass, overlay lifetime
  TString masspoint = "40";
  sample sample1(path+"allHistos_WH_HToSSTobbbb_WToLNu_MH125_MS"+masspoint+"_ctauS0_13TeV.root");
  sample1.humanName = "WH, bbbb, mS="+masspoint+", ctau=0";
  sample1.color = kMagenta;
  sampleVector.push_back(&sample1);

  sample sample2(path+"allHistos_WH_HToSSTobbbb_WToLNu_MH125_MS"+masspoint+"_ctauS1_13TeV.root");
  sample2.humanName = "WH, bbbb, mS="+masspoint+", ctau=1";
  sample2.color = kMagenta+1;
  sampleVector.push_back(&sample2);

  sample sample3(path+"allHistos_WH_HToSSTobbbb_WToLNu_MH125_MS"+masspoint+"_ctauS10_13TeV.root");
  sample3.humanName = "WH, bbbb, mS="+masspoint+", ctau=10";
  sample3.color = kMagenta+2;
  sampleVector.push_back(&sample3);

  sample sample4(path+"allHistos_WH_HToSSTobbbb_WToLNu_MH125_MS"+masspoint+"_ctauS100_13TeV.root");
  sample4.humanName = "WH, bbbb, mS="+masspoint+", ctau=100";
  sample4.color = kMagenta+3;
  sampleVector.push_back(&sample4);

  sample sample5(path+"allHistos_WH_HToSSTobbbb_WToLNu_MH125_MS"+masspoint+"_ctauS1000_13TeV.root");
  sample5.humanName = "WH, bbbb, mS="+masspoint+", ctau=1000";
  sample5.color = kMagenta+4;
  sampleVector.push_back(&sample5);

  drawPlots(sampleVector, "ALPHAMAX_ALLCALOJETS", 20, 0, 1, "ALPHAMAX_ALLCALOJETS", "Events");
  drawPlots(sampleVector, "MEDIANIPLOG10SIG_ALLCALOJETS", 20, -2, 4, "MEDIANIPLOG10SIG_ALLCALOJETS", "Events");
  drawPlots(sampleVector, "MEDIANLOG10TRACKANGLE_ALLCALOJETS", 20, -4.5, 0.5, "MEDIANLOG10TRACKANGLE_ALLCALOJETS", "Events");
  
}


void draw_varymass_fixlifetime(){

  TString path = "/uscms_data/d3/mwalker/VHdisplaced/20160426_runAnalyisTrees/";
  
  std::vector<sample*> sampleVector;
  
  //WH, pick lifetime, vary mass
  TString ctaupoint = "1000";
  sample sample1(path+"allHistos_WH_HToSSTobbbb_WToLNu_MH125_MS10_ctauS"+ctaupoint+"_13TeV.root");
  sample1.humanName = "WH, bbbb, mS=10, ctau="+ctaupoint+"";
  sample1.color = kMagenta;
  sampleVector.push_back(&sample1);

  sample sample2(path+"allHistos_WH_HToSSTobbbb_WToLNu_MH125_MS25_ctauS"+ctaupoint+"_13TeV.root");
  sample2.humanName = "WH, bbbb, mS=25, ctau="+ctaupoint+"";
  sample2.color = kMagenta+1;
  sampleVector.push_back(&sample2);

  sample sample3(path+"allHistos_WH_HToSSTobbbb_WToLNu_MH125_MS40_ctauS"+ctaupoint+"_13TeV.root");
  sample3.humanName = "WH, bbbb, mS=40, ctau="+ctaupoint+"";
  sample3.color = kMagenta+2;
  sampleVector.push_back(&sample3);

  drawPlots(sampleVector, "ALPHAMAX_ALLCALOJETS", 20, 0, 1, "ALPHAMAX_ALLCALOJETS", "Events");
  drawPlots(sampleVector, "MEDIANIPLOG10SIG_ALLCALOJETS", 20, -2, 4, "MEDIANIPLOG10SIG_ALLCALOJETS", "Events");
  drawPlots(sampleVector, "MEDIANLOG10TRACKANGLE_ALLCALOJETS", 20, -4.5, 0.5, "MEDIANLOG10TRACKANGLE_ALLCALOJETS", "Events");
  
}


void draw(){

  draw_in_PV_slices();

}
