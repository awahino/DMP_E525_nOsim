void drawFig4(){
    //open files
    //TFile *finD = TFile::Open("root/fig4.root");
    TFile *finM = TFile::Open("root/compGen.root");

    int Ebeam[] = {30, 250};
    TString model[] = {"G4PreCompound", "ABLA++", "NucDeEx_v2.1"};

    TH1D *hD[2], *hC[2];
    TH1D *hM[2][3], *hT[2][3];
    TLegend *l1;
    TCanvas *c1 = new TCanvas("c1", "", 600, 400);

    for(int i=0;i<1;i++){
        c1->cd(1); //30 MeV
        gPad->SetLogy();
        finM->cd();
        for(int j=0;j<3;j++){
            hT[i][j] = (TH1D*)finM->Get(Form("true_%dMeV_%s", Ebeam[i], model[j].Data()));
            if(j == 0) hT[i][j]->Draw("HIST");
            else hT[i][j]->Draw("HISTsame");
        }
    }
    c1->cd(1);
    l1 = (TLegend*)finM->Get(Form("legend_%dMeV_deex", Ebeam[0]));
        l1->Draw("same");
}


