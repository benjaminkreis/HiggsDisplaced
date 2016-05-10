#include "draw.h"

using namespace std;


void draw(){

  TString path = "/uscms_data/d3/mwalker/VHdisplaced/20160426_runAnalyisTrees/";


  sample sample1(path+"allHistos_WH_HToSSTobbbb_WToLNu_MH125_MS10_ctauS1_13TeV.root");
  sample1.humanName = "sample 1";
  sample1.color = kRed;

  sample sample2(path+"allHistos_WH_HToSSTobbbb_WToLNu_MH125_MS10_ctauS10_13TeV.root");
  sample2.humanName = "sample 2";
  sample2.color = kBlue;


  std::vector<sample*> sampleVector;
  sampleVector.push_back(&sample1);
  sampleVector.push_back(&sample2);


  drawPlots(sampleVector, "ALPHAMAX_ALLCALOJETS", 20, 0, 1, "ALPHAMAX_ALLCALOJETS", "Events");

}
