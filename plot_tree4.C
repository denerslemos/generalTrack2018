#import "TTree.h"
#import "TFile.h"
#import "TCanvas.h"
#import "TH1.h"
#import "THStack.h"
#import "TString.h"
#include <cstring>
#include <ctime>

void plot_tree4(){

using namespace std;

clock_t sec0,sec1;

sec0 = clock();

//read files

TFile *file1 = TFile::Open("/afs/cern.ch/work/d/ddesouza/public/trackingtest/HiForest2015.root");//2015 Data Sample
TFile *file2 = TFile::Open("/afs/cern.ch/work/d/ddesouza/public/trackingtest/HiMCForest_new.root");//Hydjet MC Sample
TFile *file3 = TFile::Open("/eos/cms/store/group/phys_heavyions/bdiab/PbPb2018/Forests/StreamerForests/HIPhysicsMinimumBias0/v2_reduced/000/326/722/HiForest_326722_part1.root");//2018 Data Sample (Run 326722)

// make histos

//xVtx Err hist
TH1F *hist1xVtxerr = new TH1F("hist1xVtxerr","hist1xVtxerr",21,-0.02,0.06);
TH1F *hist2xVtxerr = new TH1F("hist2xVtxerr","hist2xVtxerr",21,-0.02,0.06);
TH1F *hist3xVtxerr = new TH1F("hist3xVtxerr","hist3xVtxerr",21,-0.02,0.06);

//yVtx Err hist
TH1F *hist1yVtxerr = new TH1F("hist1yVtxerr","hist1yVtxerr",21,-0.02,0.06);
TH1F *hist2yVtxerr = new TH1F("hist2yVtxerr","hist2yVtxerr",21,-0.02,0.06);
TH1F *hist3yVtxerr = new TH1F("hist3yVtxerr","hist3yVtxerr",21,-0.02,0.06);


//zVtx Err hist
TH1F *hist1zVtxerr = new TH1F("hist1zVtxerr","hist1zVtxerr",51,-0.02,0.15);
TH1F *hist2zVtxerr = new TH1F("hist2zVtxerr","hist2zVtxerr",51,-0.02,0.15);
TH1F *hist3zVtxerr = new TH1F("hist3zVtxerr","hist3zVtxerr",51,-0.02,0.15);



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
tree1->SetBranchStatus("xVtxErr",1); //activate this
tree1->SetBranchStatus("yVtxErr",1); //activate this
tree1->SetBranchStatus("zVtxErr",1); //activate this


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
tree2->SetBranchStatus("xVtxErr",1); //activate this
tree2->SetBranchStatus("yVtxErr",1); //activate this
tree2->SetBranchStatus("zVtxErr",1); //activate this


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
tree3->SetBranchStatus("xVtxErr",1); //activate this
tree3->SetBranchStatus("yVtxErr",1); //activate this
tree3->SetBranchStatus("zVtxErr",1); //activate this


// make selections

TString selection = "highPurity && trkNHit>11 && trkPtError/trkPt<0.1 && trkDxy1/trkDxyError1 < 3.0 && trkDz1/trkDzError1 < 3.0";



//make the plots
//-------------------------------zVtxErr-------------------------------------------------

TCanvas* c10 = new TCanvas();
gStyle->SetOptStat(0);
gStyle->SetOptTitle(0);
c10->cd();

tree3->Draw("zVtxErr>>hist3zVtxerr",selection,"HIST");
hist3zVtxerr->Scale(1./hist3zVtxerr->Integral());
hist3zVtxerr->SetLineColor(4);
hist3zVtxerr->SetLineWidth(2);
hist3zVtxerr->GetXaxis()->SetTitle("zVtxerr");
hist3zVtxerr->GetYaxis()->SetTitle("Normalized Distributions");

tree1->Draw("zVtxErr>>hist1zVtxerr",selection,"HISTSAME");
hist1zVtxerr->Scale(1./hist1zVtxerr->Integral());
hist1zVtxerr->SetLineColor(2);
hist1zVtxerr->SetLineStyle(9);
hist1zVtxerr->SetLineWidth(2);

tree2->Draw("zVtxErr>>hist2zVtxerr",selection,"HISTSAME");
hist2zVtxerr->Scale(1./hist2zVtxerr->Integral());
hist2zVtxerr->SetLineColor(1);
hist2zVtxerr->SetLineStyle(2);
hist2zVtxerr->SetLineWidth(2);

auto legend10 = new TLegend(0.7,0.7,0.87,0.85);
legend10->AddEntry(hist2zVtxerr,"MC");
legend10->AddEntry(hist1zVtxerr,"2015 Data");
legend10->AddEntry(hist3zVtxerr,"2018 Data");
legend10->SetBorderSize(0);
legend10->Draw();
c10->SetLogy(1);
c10->Print("./zVtxerr_comp.pdf");
c10->Update();


//-------------------------------xVtxErr-------------------------------------------------

TCanvas* c11 = new TCanvas();
gStyle->SetOptStat(0);
gStyle->SetOptTitle(0);
c11->cd();

tree3->Draw("xVtxErr>>hist3xVtxerr",selection,"HIST");
hist3xVtxerr->Scale(1./hist3xVtxerr->Integral());
hist3xVtxerr->SetLineColor(4);
hist3xVtxerr->SetLineWidth(2);
hist3xVtxerr->GetXaxis()->SetTitle("xVtxerr");
hist3xVtxerr->GetYaxis()->SetTitle("Normalized Distributions");

tree1->Draw("xVtxErr>>hist1xVtxerr",selection,"HISTSAME");
hist1xVtxerr->Scale(1./hist1xVtxerr->Integral());
hist1xVtxerr->SetLineColor(2);
hist1xVtxerr->SetLineStyle(9);
hist1xVtxerr->SetLineWidth(2);

tree2->Draw("xVtxErr>>hist2xVtxerr",selection,"HISTSAME");
hist2xVtxerr->Scale(1./hist2xVtxerr->Integral());
hist2xVtxerr->SetLineColor(1);
hist2xVtxerr->SetLineStyle(2);
hist2xVtxerr->SetLineWidth(2);

auto legend11 = new TLegend(0.7,0.7,0.87,0.85);
legend11->AddEntry(hist2xVtxerr,"MC");
legend11->AddEntry(hist1xVtxerr,"2015 Data");
legend11->AddEntry(hist3xVtxerr,"2018 Data");
legend11->SetBorderSize(0);
legend11->Draw();
c11->SetLogy(1);
c11->Print("./xVtxerr_comp.pdf");
c11->Update();


//-------------------------------yVtxErr-------------------------------------------------

TCanvas* c12 = new TCanvas();
gStyle->SetOptStat(0);
gStyle->SetOptTitle(0);
c12->cd();

tree3->Draw("yVtxErr>>hist3yVtxerr",selection,"HIST");
hist3yVtxerr->Scale(1./hist3yVtxerr->Integral());
hist3yVtxerr->SetLineColor(4);
hist3yVtxerr->SetLineWidth(2);
hist3yVtxerr->GetXaxis()->SetTitle("yVtxerr");
hist3yVtxerr->GetYaxis()->SetTitle("Normalized Distributions");

tree1->Draw("yVtxErr>>hist1yVtxerr",selection,"HISTSAME");
hist1yVtxerr->Scale(1./hist1yVtxerr->Integral());
hist1yVtxerr->SetLineColor(2);
hist1yVtxerr->SetLineStyle(9);
hist1yVtxerr->SetLineWidth(2);

tree2->Draw("yVtxErr>>hist2yVtxerr",selection,"HISTSAME");
hist2yVtxerr->Scale(1./hist2yVtxerr->Integral());
hist2yVtxerr->SetLineColor(1);
hist2yVtxerr->SetLineStyle(2);
hist2yVtxerr->SetLineWidth(2);

auto legend12 = new TLegend(0.7,0.7,0.87,0.85);
legend12->AddEntry(hist2yVtxerr,"MC");
legend12->AddEntry(hist1yVtxerr,"2015 Data");
legend12->AddEntry(hist3yVtxerr,"2018 Data");
legend12->SetBorderSize(0);
legend12->Draw();
c12->SetLogy(1);
c12->Print("./yVtxerr_comp.pdf");
c12->Update();



//-------------------------------ENDED-------------------------------------------------

sec1 = clock();

double elapsed_secs = double(sec1-sec0) / CLOCKS_PER_SEC;

cout <<"Total Time = " << elapsed_secs << "[s]" << endl;

}

