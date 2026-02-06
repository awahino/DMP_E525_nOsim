const int NG = 4;
void drawFig14(){
    TString label[] = {
        "4p44",
        "5p27",
        "6p13",
        "total"
    };
    TMultiGraph *gM[NG]; // = new TMultiGraph("gM", "; Neutron Energy /MeV; Cross section /mb");
    TLegend *l1[NG]; // = new TLegend(0.5, 0.5, 0.85, 0.85);
    TFile *fin[NG]; 
    TCanvas *c1;
        if(NG==3){
            c1 = new TCanvas("c1", "", 1300, 400);
            c1->Divide(3, 1);
        }else if(NG==4){
            c1 = new TCanvas("c1", "", 1200, 900);
            c1->Divide(2, 2);
        }
    for(int ich=0;ich<NG;ich++){
        fin[ich] = TFile::Open(Form("root/%s.root", label[ich].Data()), "read");
            fin[ich]->cd();
        gM[ich] = (TMultiGraph*)fin[ich]->Get(Form("gM_%s", label[ich].Data()));
        l1[ich] = (TLegend*)fin[ich]->Get(Form("l1_%s", label[ich].Data()));

        c1->cd(ich+1);
        //gPad->SetLeftMargin(0.09);
        //gPad->SetRightMargin(0.09);
        gM[ich]->GetYaxis()->SetTitleOffset(1.10);
        gM[ich]->Draw("ape");
        if(ich==0) l1[ich]->Draw("same");
    }
    //l1->Draw("");
}

