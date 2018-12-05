#import "TTree.h"
#import "TFile.h"
#import "TCanvas.h"
#import "TH1.h"
#import "THStack.h"
#import "TString.h"
#include <cstring>
#include <ctime>

void plot_tree1(){

using namespace std;

clock_t sec0,sec1;

sec0 = clock();


TFile *file1 = TFile::Open("/afs/cern.ch/work/d/ddesouza/public/trackingtest/HiForest2015.root");//2015 Data Sample
TFile *file2 = TFile::Open("/afs/cern.ch/work/d/ddesouza/public/trackingtest/HiMCForest_new.root");//Hydjet MC Sample
TFile *file3 = TFile::Open("/eos/cms/store/group/phys_heavyions/bdiab/PbPb2018/Forests/StreamerForests/HIPhysicsMinimumBias0/v2_reduced/000/326/722/HiForest_326722_part1.root");//2018 Data Sample (Run 326722)


// make histos

//pT hist
TH1F *hist1pt = new TH1F("hist1pt","hist1pt",101,-0.5,10.0);
TH1F *hist2pt = new TH1F("hist2pt","hist2pt",101,-0.5,10.0);
TH1F *hist3pt = new TH1F("hist3pt","hist3pt",101,-0.5,10.0);


//eta hist
TH1F *hist1eta = new TH1F("hist1eta","hist1eta",101,-3.,3.);
TH1F *hist2eta = new TH1F("hist2eta","hist2eta",101,-3.,3.);
TH1F *hist3eta = new TH1F("hist3eta","hist3eta",101,-3.,3.);


//phi hist
TH1F *hist1phi = new TH1F("hist1phi","hist1phi",101,-3.5,3.5);
TH1F *hist2phi = new TH1F("hist2phi","hist2phi",101,-3.5,3.5);
TH1F *hist3phi = new TH1F("hist3phi","hist3phi",101,-3.5,3.5);


//read Trees
TTree * tree1 = (TTree *)file1->Get("anaTrack/trackTree");
tree1->SetBranchStatus("*",0);  // disable all branches
tree1->SetBranchStatus("trkPt",1); //activate this
tree1->SetBranchStatus("trkPtError",1); //activate this
tree1->SetBranchStatus("trkEta",1); //activate this
tree1->SetBranchStatus("trkPhi",1); //activate this
tree1->SetBranchStatus("trkNHit",1); //activate this
tree1->SetBranchStatus("highPurity",1); //activate this
tree1->SetBranchStatus("trkDxy1",1); //activate this
tree1->SetBranchStatus("trkDxyError1",1); //activate this
tree1->SetBranchStatus("trkDz1",1); //activate this
tree1->SetBranchStatus("trkDzError1",1); //activate this


TTree * tree2 = (TTree *)file2->Get("ppTrack/trackTree");
tree2->SetBranchStatus("*",0);  // disable all branchesi
tree2->SetBranchStatus("trkPt",1); //activate this
tree2->SetBranchStatus("trkPtError",1); //activate this
tree2->SetBranchStatus("trkEta",1); //activate this
tree2->SetBranchStatus("trkPhi",1); //activate this
tree2->SetBranchStatus("trkNHit",1); //activate this
tree2->SetBranchStatus("highPurity",1); //activate this
tree2->SetBranchStatus("trkDxy1",1); //activate this
tree2->SetBranchStatus("trkDxyError1",1); //activate this
tree2->SetBranchStatus("trkDz1",1); //activate this
tree2->SetBranchStatus("trkDzError1",1); //activate this



TTree * tree3 = (TTree *)file3->Get("ppTrack/trackTree");
tree3->SetBranchStatus("*",0);  // disable all branches
tree3->SetBranchStatus("trkPt",1); //activate this
tree3->SetBranchStatus("trkPtError",1); //activate this
tree3->SetBranchStatus("trkEta",1); //activate this
tree3->SetBranchStatus("trkPhi",1); //activate this
tree3->SetBranchStatus("trkNHit",1); //activate this
tree3->SetBranchStatus("highPurity",1); //activate this
tree3->SetBranchStatus("trkDxy1",1); //activate this
tree3->SetBranchStatus("trkDxyError1",1); //activate this
tree3->SetBranchStatus("trkDz1",1); //activate this
tree3->SetBranchStatus("trkDzError1",1); //activate this

// make selections

TString selection = "highPurity && trkNHit>11 && trkPtError/trkPt<0.1 && trkDxy1/trkDxyError1 < 3.0 && trkDz1/trkDzError1 < 3.0";



//make plots

//-------------------------------ETA-------------------------------------------------

TCanvas* c1 = new TCanvas();
gStyle->SetOptStat(0);
gStyle->SetOptTitle(0);
c1->cd();

tree3->Draw("trkEta>>hist3eta",selection,"HIST");
hist3eta->Scale(1./hist3eta->Integral());
hist3eta->SetLineColor(4);
hist3eta->SetLineWidth(2);
hist3eta->GetXaxis()->SetTitle("trk #eta");
hist3eta->GetYaxis()->SetTitle("Normalized Distributions");

tree1->Draw("trkEta>>hist1eta",selection,"HISTSAME");
hist1eta->Scale(1./hist1eta->Integral());
hist1eta->SetLineColor(2);
hist1eta->SetLineStyle(9);
hist1eta->SetLineWidth(2);

tree2->Draw("trkEta>>hist2eta",selection,"HISTSAME");
hist2eta->Scale(1./hist2eta->Integral());
hist2eta->SetLineColor(1);
hist2eta->SetLineStyle(2);
hist2eta->SetLineWidth(2);

//c1->SetLogy(1);
auto legend1 = new TLegend(0.45,0.15,0.6,0.27);
legend1->AddEntry(hist2eta,"MC");
legend1->AddEntry(hist1eta,"2015 Data");
legend1->AddEntry(hist3eta,"2018 Data");
legend1->SetBorderSize(0);
legend1->Draw();

c1->Print("./eta_comp.pdf");
c1->Update();

//-------------------------------PHI-------------------------------------------------

TCanvas* c2 = new TCanvas();
gStyle->SetOptStat(0);
gStyle->SetOptTitle(0);
c2->cd();

tree3->Draw("trkPhi>>hist3phi",selection,"HIST");
hist3phi->Scale(1./hist3phi->Integral());
hist3phi->SetLineColor(4);
hist3phi->SetLineWidth(2);
hist3phi->GetXaxis()->SetTitle("trk #phi");
hist3phi->GetYaxis()->SetTitle("Normalized Distributions");

tree1->Draw("trkPhi>>hist1phi",selection,"HISTSAME");
hist1phi->Scale(1./hist1phi->Integral());
hist1phi->SetLineColor(2);
hist1phi->SetLineStyle(9);
hist1phi->SetLineWidth(2);

tree2->Draw("trkPhi>>hist2phi",selection,"HISTSAME");
hist2phi->Scale(1./hist2phi->Integral());
hist2phi->SetLineColor(1);
hist2phi->SetLineStyle(2);
hist2phi->SetLineWidth(2);

//c2->SetLogy(1);
auto legend2 = new TLegend(0.2,0.15,0.35,0.27);
legend2->AddEntry(hist2phi,"MC");
legend2->AddEntry(hist1phi,"2015 Data");
legend2->AddEntry(hist3phi,"2018 Data");
legend2->SetBorderSize(0);
legend2->Draw();

c2->Print("./phi_comp.pdf");
c2->Update();

//-------------------------------PT-------------------------------------------------

TCanvas* c3 = new TCanvas();
gStyle->SetOptStat(0);
gStyle->SetOptTitle(0);
c3->cd();

tree3->Draw("trkPt>>hist3pt",selection,"HISTSAME");
hist3pt->Scale(1./hist3pt->Integral());
hist3pt->SetLineColor(4);
hist3pt->SetLineWidth(2);
hist3pt->GetXaxis()->SetTitle("trk p_{T} [GeV]");
hist3pt->GetYaxis()->SetTitle("Normalized Distributions");

tree1->Draw("trkPt>>hist1pt",selection,"HISTSAME");
hist1pt->Scale(1./hist1pt->Integral());
hist1pt->SetLineColor(2);
hist1pt->SetLineStyle(9);
hist1pt->SetLineWidth(2);

tree2->Draw("trkPt>>hist2pt",selection,"HISTSAME");
hist2pt->Scale(1./hist2pt->Integral());
hist2pt->SetLineColor(1);
hist2pt->SetLineStyle(2);
hist2pt->SetLineWidth(2);


auto legend3 = new TLegend(0.7,0.7,0.87,0.85);
legend3->AddEntry(hist2pt,"MC");
legend3->AddEntry(hist1pt,"2015 Data");
legend3->AddEntry(hist3pt,"2018 Data");
legend3->SetBorderSize(0);
legend3->Draw();

c3->SetLogy(1);
c3->Print("./pt_comp.pdf");
c3->Update();


//-------------------------------ENDED-------------------------------------------------

sec1 = clock();

double elapsed_secs = double(sec1-sec0) / CLOCKS_PER_SEC;

cout <<"Total Time = " << elapsed_secs << "[s]" << endl;

}

