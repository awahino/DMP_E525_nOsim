void drawFig5(){
    //open files
    TFile *finD = TFile::Open("root/fig5.root");

    int Ebeam[] = {30, 250};
    TString model[] = {"G4PreCompound", "NucDeEx_v2.1"};

    TH1D *hD[2], *hC[2];
    TH1D *hM[2][3], *hT[2][3];
    TLegend *l1;
    TCanvas *c1 = new TCanvas("c1", "", 1100, 500);
        c1->Divide(2, 1);

    for(int i=0;i<2;i++){
        c1->cd(i+1); //30 MeV
        finD->cd();
        hD[i] = (TH1D*)finD->Get(Form("data_%dMeV_stat+syst", Ebeam[i]));
        hC[i] = (TH1D*)finD->Get(Form("data_%dMeV_statonly", Ebeam[i]));
            hD[i]->Draw("pE3");
            hC[i]->Draw("pesame");
        for(int j=0;j<2;j++){
            hM[i][j] = (TH1D*)finD->Get(Form("mc_%dMeV_%s", Ebeam[i], model[j].Data()));
            hM[i][j]->Draw("HISTsame");
        }
    }
    c1->cd(1);
    l1 = (TLegend*)finD->Get(Form("legend_%dMeV", Ebeam[0]));
        l1->Draw("same");
}


