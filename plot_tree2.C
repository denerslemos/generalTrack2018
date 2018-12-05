#import "TTree.h"
#import "TFile.h"
#import "TCanvas.h"
#import "TH1.h"
#import "THStack.h"
#import "TString.h"
#include <cstring>
#include <ctime>

void plot_tree2(){

using namespace std;

clock_t sec0,sec1;

sec0 = clock();

//read files

TFile *file1 = TFile::Open("/afs/cern.ch/work/d/ddesouza/public/trackingtest/HiForest2015.root");//2015 Data Sample
TFile *file2 = TFile::Open("/afs/cern.ch/work/d/ddesouza/public/trackingtest/HiMCForest_new.root");//Hydjet MC Sample
TFile *file3 = TFile::Open("/eos/cms/store/group/phys_heavyions/bdiab/PbPb2018/Forests/StreamerForests/HIPhysicsMinimumBias0/v2_reduced/000/326/722/HiForest_326722_part1.root");//2018 Data Sample (Run 326722)


// make histos

//ntrk hist
TH1F *hist1ntrk = new TH1F("hist1ntrk","hist1ntrk",101,-0.5,10000.);
TH1F *hist2ntrk = new TH1F("hist2ntrk","hist2ntrk",101,-0.5,10000.);
TH1F *hist3ntrk = new TH1F("hist3ntrk","hist3ntrk",101,-0.5,10000.);

//nHits hist
TH1F *hist1nhit = new TH1F("hist1nhit","hist1nhit",21,8,30);
TH1F *hist2nhit = new TH1F("hist2nhit","hist2nhit",21,8,30);
TH1F *hist3nhit = new TH1F("hist3nhit","hist3nhit",21,8,30);

//chi2 hist
TH1F *hist1chi2 = new TH1F("hist1chi2","hist1chi2",81,-0.1,3.);
TH1F *hist2chi2 = new TH1F("hist2chi2","hist2chi2",81,-0.1,3.);
TH1F *hist3chi2 = new TH1F("hist3chi2","hist3chi2",81,-0.1,3.);


//read Trees
TTree * tree1 = (TTree *)file1->Get("anaTrack/trackTree");
tree1->SetBranchStatus("*",0);  // disable all branches
tree1->SetBranchStatus("trkPt",1); //activate this
tree1->SetBranchStatus("trkPtError",1); //activate this
tree1->SetBranchStatus("nTrk",1); //activate this
tree1->SetBranchStatus("trkNHit",1); //activate this
tree1->SetBranchStatus("trkChi2",1); //activate this
tree1->SetBranchStatus("trkNdof",1); //activate this
tree1->SetBranchStatus("highPurity",1); //activate this
tree1->SetBranchStatus("trkDxy1",1); //activate this
tree1->SetBranchStatus("trkDxyError1",1); //activate this
tree1->SetBranchStatus("trkDz1",1); //activate this
tree1->SetBranchStatus("trkDzError1",1); //activate this


TTree * tree2 = (TTree *)file2->Get("ppTrack/trackTree");
tree2->SetBranchStatus("*",0);  // disable all branches
tree2->SetBranchStatus("trkPt",1); //activate this
tree2->SetBranchStatus("trkPtError",1); //activate this
tree2->SetBranchStatus("nTrk",1); //activate this
tree2->SetBranchStatus("trkNHit",1); //activate this
tree2->SetBranchStatus("trkChi2",1); //activate this
tree2->SetBranchStatus("trkNdof",1); //activate this
tree2->SetBranchStatus("highPurity",1); //activate this
tree2->SetBranchStatus("trkDxy1",1); //activate this
tree2->SetBranchStatus("trkDxyError1",1); //activate this
tree2->SetBranchStatus("trkDz1",1); //activate this
tree2->SetBranchStatus("trkDzError1",1); //activate this



TTree * tree3 = (TTree *)file3->Get("ppTrack/trackTree");
tree3->SetBranchStatus("*",0);  // disable all branches
tree3->SetBranchStatus("trkPt",1); //activate this
tree3->SetBranchStatus("trkPtError",1); //activate this
tree3->SetBranchStatus("nTrk",1); //activate this
tree3->SetBranchStatus("trkNHit",1); //activate this
tree3->SetBranchStatus("trkChi2",1); //activate this
tree3->SetBranchStatus("trkNdof",1); //activate this
tree3->SetBranchStatus("highPurity",1); //activate this
tree3->SetBranchStatus("trkDxy1",1); //activate this
tree3->SetBranchStatus("trkDxyError1",1); //activate this
tree3->SetBranchStatus("trkDz1",1); //activate this
tree3->SetBranchStatus("trkDzError1",1); //activate this



// make selections

TString selection = "highPurity && trkNHit>11 && trkPtError/trkPt<0.1 && trkDxy1/trkDxyError1 < 3.0 && trkDz1/trkDzError1 < 3.0";



//make the plots

//-------------------------------NTRK-------------------------------------------------

TCanvas* c4 = new TCanvas();
gStyle->SetOptStat(0);
gStyle->SetOptTitle(0);
c4->cd();

tree3->Draw("nTrk>>hist3ntrk",selection,"HIST");
hist3ntrk->Scale(1./hist3ntrk->Integral());
hist3ntrk->SetLineColor(4);
hist3ntrk->SetLineWidth(2);
hist3ntrk->GetXaxis()->SetTitle("trk N_{trk}");
hist3ntrk->GetYaxis()->SetTitle("Normalized Distributions");

tree1->Draw("nTrk>>hist1ntrk",selection,"HISTSAME");
hist1ntrk->Scale(1./hist1ntrk->Integral());
hist1ntrk->SetLineColor(2);
hist1ntrk->SetLineStyle(9);
hist1ntrk->SetLineWidth(2);

tree2->Draw("nTrk>>hist2ntrk",selection,"HISTSAME");
hist2ntrk->Scale(1./hist2ntrk->Integral());
hist2ntrk->SetLineColor(1);
hist2ntrk->SetLineStyle(2);
hist2ntrk->SetLineWidth(2);

auto legend4 = new TLegend(0.7,0.7,0.87,0.85);
legend4->AddEntry(hist2ntrk,"MC");
legend4->AddEntry(hist1ntrk,"2015 Data");
legend4->AddEntry(hist3ntrk,"2018 Data");
legend4->SetBorderSize(0);
legend4->Draw();

c4->SetLogy(1);
c4->Print("./ntrk_comp.pdf");
c4->Update();




//-------------------------------NHITS-------------------------------------------------

TCanvas* c5 = new TCanvas();
gStyle->SetOptStat(0);
gStyle->SetOptTitle(0);
c5->cd();

tree3->Draw("trkNHit>>hist3nhit",selection,"HIST");
hist3nhit->Scale(1./hist3nhit->Integral());
hist3nhit->SetLineColor(4);
hist3nhit->SetLineWidth(2);
hist3nhit->GetXaxis()->SetTitle("trk N_{hits}");
hist3nhit->GetYaxis()->SetTitle("Normalized Distributions");

tree1->Draw("trkNHit>>hist1nhit",selection,"HISTSAME");
hist1nhit->Scale(1./hist1nhit->Integral());
hist1nhit->SetLineColor(2);
hist1nhit->SetLineStyle(9);
hist1nhit->SetLineWidth(2);

tree2->Draw("trkNHit>>hist2nhit",selection,"HISTSAME");
hist2nhit->Scale(1./hist2nhit->Integral());
hist2nhit->SetLineColor(1);
hist2nhit->SetLineStyle(2);
hist2nhit->SetLineWidth(2);


auto legend5 = new TLegend(0.7,0.7,0.87,0.85);
legend5->AddEntry(hist2nhit,"MC");
legend5->AddEntry(hist1nhit,"2015 Data");
legend5->AddEntry(hist3nhit,"2018 Data");
legend5->SetBorderSize(0);
legend5->Draw();

c5->SetLogy(1);
c5->Print("./nhits_comp.pdf");
c5->Update();

//-------------------------------CHI2-------------------------------------------------

TCanvas* c6 = new TCanvas();
gStyle->SetOptStat(0);
gStyle->SetOptTitle(0);
c6->cd();

tree3->Draw("trkChi2/trkNdof>>hist3chi2",selection,"HIST");
hist3chi2->Scale(1./hist3chi2->Integral());
hist3chi2->SetLineColor(4);
hist3chi2->SetLineWidth(2);
hist3chi2->GetXaxis()->SetTitle("trk #chi^{2}/Ndof");
hist3chi2->GetYaxis()->SetTitle("Normalized Distributions");


tree1->Draw("trkChi2/trkNdof>>hist1chi2",selection,"HISTSAME");
hist1chi2->Scale(1./hist1chi2->Integral());
hist1chi2->SetLineColor(2);
hist1chi2->SetLineStyle(9);
hist1chi2->SetLineWidth(2);

tree2->Draw("trkChi2/trkNdof>>hist2chi2",selection,"HISTSAME");
hist2chi2->Scale(1./hist2chi2->Integral());
hist2chi2->SetLineColor(1);
hist2chi2->SetLineStyle(2);
hist2chi2->SetLineWidth(2);

//c6->SetLogy(1);
auto legend6 = new TLegend(0.7,0.7,0.87,0.85);
legend6->AddEntry(hist2chi2,"MC");
legend6->AddEntry(hist1chi2,"2015 Data");
legend6->AddEntry(hist3chi2,"2018 Data");
legend6->SetBorderSize(0);
legend6->Draw();

c6->Print("./chi2_comp.pdf");
c6->Update();

//-------------------------------ENDED-------------------------------------------------

sec1 = clock();

double elapsed_secs = double(sec1-sec0) / CLOCKS_PER_SEC;

cout <<"Total Time = " << elapsed_secs << "[s]" << endl;

}

