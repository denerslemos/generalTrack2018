#import "TTree.h"
#import "TFile.h"
#import "TCanvas.h"
#import "TH1.h"
#import "THStack.h"
#import "TString.h"
#include <cstring>
#include <ctime>

void plot_tree3(){

using namespace std;

clock_t sec0,sec1;

sec0 = clock();

//read files

TFile *file1 = TFile::Open("/afs/cern.ch/work/d/ddesouza/public/trackingtest/HiForest2015.root");//2015 Data Sample
TFile *file2 = TFile::Open("/afs/cern.ch/work/d/ddesouza/public/trackingtest/HiMCForest_new.root");//Hydjet MC Sample
TFile *file3 = TFile::Open("/eos/cms/store/group/phys_heavyions/bdiab/PbPb2018/Forests/StreamerForests/HIPhysicsMinimumBias0/v2_reduced/000/326/722/HiForest_326722_part1.root");//2018 Data Sample (Run 326722)


//xVtx hist
TH1F *hist1xVtx = new TH1F("hist1xVtx","hist1xVtx",21,-0.2,0.2);
TH1F *hist2xVtx = new TH1F("hist2xVtx","hist2xVtx",21,-0.2,0.2);
TH1F *hist3xVtx = new TH1F("hist3xVtx","hist3xVtx",21,-0.2,0.2);

//yVtx hist
TH1F *hist1yVtx = new TH1F("hist1yVtx","hist1yVtx",21,-0.2,0.2);
TH1F *hist2yVtx = new TH1F("hist2yVtx","hist2yVtx",21,-0.2,0.2);
TH1F *hist3yVtx = new TH1F("hist3yVtx","hist3yVtx",21,-0.2,0.2);

//zVtx hist
TH1F *hist1zVtx = new TH1F("hist1zVtx","hist1zVtx",51,-15.,15.);
TH1F *hist2zVtx = new TH1F("hist2zVtx","hist2zVtx",51,-15.,15.);
TH1F *hist3zVtx = new TH1F("hist3zVtx","hist3zVtx",51,-15.,15.);


// make selections
TString selection = "highPurity && trkNHit>11 && trkPtError/trkPt<0.1 && trkDxy1/trkDxyError1 < 3.0 && trkDz1/trkDzError1 < 3.0";



//read Trees
TTree * tree1 = (TTree *)file1->Get("anaTrack/trackTree");
tree1->SetBranchStatus("*",0);  // disable all branches
tree1->SetBranchStatus("trkPt",1); //activate this
tree1->SetBranchStatus("trkPtError",1); //activate this
tree1->SetBranchStatus("trkNHit",1); //activate this
tree1->SetBranchStatus("highPurity",1); //activate this
tree1->SetBranchStatus("trkDxy1",1); //activate this
tree1->SetBranchStatus("trkDxyError1",1); //activate this
tree1->SetBranchStatus("trkDz1",1); //activate this
tree1->SetBranchStatus("trkDzError1",1); //activate this
tree1->SetBranchStatus("xVtx",1); //activate this
tree1->SetBranchStatus("yVtx",1); //activate this
tree1->SetBranchStatus("zVtx",1); //activate this

TTree * tree2 = (TTree *)file2->Get("ppTrack/trackTree");
tree2->SetBranchStatus("*",0);  // disable all branches
tree2->SetBranchStatus("trkPt",1); //activate this
tree2->SetBranchStatus("trkPtError",1); //activate this
tree2->SetBranchStatus("trkNHit",1); //activate this
tree2->SetBranchStatus("highPurity",1); //activate this
tree2->SetBranchStatus("trkDxy1",1); //activate this
tree2->SetBranchStatus("trkDxyError1",1); //activate this
tree2->SetBranchStatus("trkDz1",1); //activate this
tree2->SetBranchStatus("trkDzError1",1); //activate this
tree2->SetBranchStatus("xVtx",1); //activate this
tree2->SetBranchStatus("yVtx",1); //activate this
tree2->SetBranchStatus("zVtx",1); //activate this


TTree * tree3 = (TTree *)file3->Get("ppTrack/trackTree");
tree3->SetBranchStatus("*",0);  // disable all branches
tree3->SetBranchStatus("trkPt",1); //activate this
tree3->SetBranchStatus("trkPtError",1); //activate this
tree3->SetBranchStatus("trkNHit",1); //activate this
tree3->SetBranchStatus("highPurity",1); //activate this
tree3->SetBranchStatus("trkDxy1",1); //activate this
tree3->SetBranchStatus("trkDxyError1",1); //activate this
tree3->SetBranchStatus("trkDz1",1); //activate this
tree3->SetBranchStatus("trkDzError1",1); //activate this
tree3->SetBranchStatus("xVtx",1); //activate this
tree3->SetBranchStatus("yVtx",1); //activate this
tree3->SetBranchStatus("zVtx",1); //activate this


//make the plots

//-------------------------------xVtx-------------------------------------------------

TCanvas* c7 = new TCanvas();
gStyle->SetOptStat(0);
gStyle->SetOptTitle(0);
c7->cd();

tree3->Draw("xVtx>>hist3xVtx",selection,"HIST");
hist3xVtx->Scale(1./hist3xVtx->Integral());
hist3xVtx->SetLineColor(4);
hist3xVtx->SetLineWidth(2);
hist3xVtx->GetXaxis()->SetTitle("xVtx");
hist3xVtx->GetYaxis()->SetTitle("Normalized Distributions");


tree1->Draw("xVtx>>hist1xVtx",selection,"HISTSAME");
hist1xVtx->Scale(1./hist1xVtx->Integral());
hist1xVtx->SetLineColor(2);
hist1xVtx->SetLineStyle(9);
hist1xVtx->SetLineWidth(2);

tree2->Draw("xVtx>>hist2xVtx",selection,"HISTSAME");
hist2xVtx->Scale(1./hist2xVtx->Integral());
hist2xVtx->SetLineColor(1);
hist2xVtx->SetLineStyle(2);
hist2xVtx->SetLineWidth(2);

auto legend7 = new TLegend(0.15,0.7,0.35,0.85);
legend7->AddEntry(hist2xVtx,"MC");
legend7->AddEntry(hist1xVtx,"2015 Data");
legend7->AddEntry(hist3xVtx,"2018 Data");
legend7->SetBorderSize(0);
legend7->Draw();

c7->Print("./xVtx_comp.pdf");
c7->Update();


//-------------------------------yVtx-------------------------------------------------

TCanvas* c8 = new TCanvas();
gStyle->SetOptStat(0);
gStyle->SetOptTitle(0);
c8->cd();

tree3->Draw("yVtx>>hist3yVtx",selection,"HIST");
hist3yVtx->Scale(1./hist3yVtx->Integral());
hist3yVtx->SetLineColor(4);
hist3yVtx->SetLineWidth(2);
hist3yVtx->GetXaxis()->SetTitle("yVtx");
hist3yVtx->GetYaxis()->SetTitle("Normalized Distributions");

tree1->Draw("yVtx>>hist1yVtx",selection,"HISTSAME");
hist1yVtx->Scale(1./hist1yVtx->Integral());
hist1yVtx->SetLineColor(2);
hist1yVtx->SetLineStyle(9);
hist1yVtx->SetLineWidth(2);

tree2->Draw("yVtx>>hist2yVtx",selection,"HISTSAME");
hist2yVtx->Scale(1./hist2yVtx->Integral());
hist2yVtx->SetLineColor(1);
hist2yVtx->SetLineStyle(2);
hist2yVtx->SetLineWidth(2);

auto legend8 = new TLegend(0.15,0.7,0.35,0.85);
legend8->AddEntry(hist2yVtx,"MC");
legend8->AddEntry(hist1yVtx,"2015 Data");
legend8->AddEntry(hist3yVtx,"2018 Data");
legend8->SetBorderSize(0);
legend8->Draw();

c8->Print("./yVtx_comp.pdf");
c8->Update();



//-------------------------------zVtx-------------------------------------------------

TCanvas* c9 = new TCanvas();
gStyle->SetOptStat(0);
gStyle->SetOptTitle(0);
c9->cd();

tree3->Draw("zVtx>>hist3zVtx",selection,"HIST");
hist3zVtx->Scale(1./hist3zVtx->Integral());
hist3zVtx->SetLineColor(4);
hist3zVtx->SetLineWidth(2);
hist3zVtx->GetXaxis()->SetTitle("zVtx");
hist3zVtx->GetYaxis()->SetTitle("Normalized Distributions");

tree1->Draw("zVtx>>hist1zVtx",selection,"HISTSAME");
hist1zVtx->Scale(1./hist1zVtx->Integral());
hist1zVtx->SetLineColor(2);
hist1zVtx->SetLineStyle(9);
hist1zVtx->SetLineWidth(2);

tree2->Draw("zVtx>>hist2zVtx",selection,"HISTSAME");
hist2zVtx->Scale(1./hist2zVtx->Integral());
hist2zVtx->SetLineColor(1);
hist2zVtx->SetLineStyle(2);
hist2zVtx->SetLineWidth(2);

auto legend9 = new TLegend(0.15,0.7,0.35,0.85);
legend9->AddEntry(hist2zVtx,"MC");
legend9->AddEntry(hist1zVtx,"2015 Data");
legend9->AddEntry(hist3zVtx,"2018 Data");
legend9->SetBorderSize(0);
legend9->Draw();

c9->Print("./zVtx_comp.pdf");
c9->Update();

//-------------------------------ENDED-------------------------------------------------

sec1 = clock();

double elapsed_secs = double(sec1-sec0) / CLOCKS_PER_SEC;

cout <<"Total Time = " << elapsed_secs << "[s]" << endl;

}

