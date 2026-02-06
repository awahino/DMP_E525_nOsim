void drawFig6(){
    //open files
    TFile *finD = TFile::Open("root/fig6.root");

    int Ebeam[] = {80, 250};
    TString model[] = {"G4PreCo", "NucDeEx_v2.1"};

    TH1D *hD[2], *hC[2], *hCc[2];
    TH1D *hM[2][3], *hT[2][3];
    TLegend *l1;
    TCanvas *c1 = new TCanvas("c1", "", 500, 500);
        c1->cd(1); //80 MeV

    for(int i=0;i<1;i++){
        finD->cd();
        hD[i] = (TH1D*)finD->Get(Form("data_%dMeV_stat+syst", Ebeam[i]));
            hD[i]->SetMaximum(2.5e-6);
        hC[i] = (TH1D*)finD->Get(Form("data_%dMeV_statonly", Ebeam[i]));
        hCc[i] = (TH1D*)finD->Get(Form("data_%dMeV_with_correction", Ebeam[i]));
            hD[i]->Draw("pE3");
            hC[i]->Draw("pesame");
        for(int j=0;j<2;j++){
            hM[i][j] = (TH1D*)finD->Get(Form("mc_%dMeV_%s", Ebeam[i], model[j].Data()));
            hM[i][j]->Draw("HISTsame");
        }
            hCc[i]->Draw("pesame");
    }
    l1 = (TLegend*)finD->Get(Form("legend_%dMeV", Ebeam[0]));
        l1->Draw("same");
}


