const double cm2barn = 10e-28; //cm2 to mb
//bool IsLogScale = true;
bool IsLogScale = false;

void drawPlot(int Ebeam = 30, int LogFlag = 0){
    if(!(Ebeam == 30 || Ebeam == 250)){
        cout << "Error!" << endl;
        cout << "Ebeam must be 30 or 250." << endl;
    }
    if(LogFlag == 0 ) IsLogScale = false;
    else IsLogScale = true;

    const int npar=22+1;
    std::string par_list[npar] = {
        "continuum",     // 0
        "7.115",   // 1
        "6.916",   // 2
        "6.32",    // 3
        "6.13",    // 4
        "5.27",    // 5
        "5.104",   // 6 not use
        "4.914",   // 7
        "4.44",    // 8
        "3.839",   // 9 not use
        "3.68",    // 10
        "2.742",   // 11
        "2.30",    // 12
        "5.183",   // 13
        "6.176",   // 14
        "5.240",   // 15
        "7.298",   // 16
        "8.310",   // 17
        "8.869",   // 18
        "9.148",   // 19
        "9.219",   // 20
        "9.921",   // 21
        "nuis"     // 22 nuisance par for syst.
    };

    bool IsDraw[npar][2] = {
        { true,  true}, //"bkg",     //  0
        { true,  true}, //"7p115",   //  1
        { true,  true}, //"6p916",   //  2
        { true,  true}, //"6p32",    //  3
        { true,  true}, //"6p13",    //  4
        { true,  true}, //"5p27",    //  5
        {false, false}, //"5p104",   //  6 used by tano mthesis
        {false, false}, //"4p914",   //  7
        { true,  true}, //"4p44",    //  8
        {false, false}, //"3p839",   //  9 not used by tano mthesis
        { true,  true}, //"3p68",    //  10
        { true,  true}, //"2p742",   //  11
        { true,  true}, //"2p30",    //  12
        { true,  true}, //"5p183",   //  13
        { true,  true}, //"6p176",   //  14
        {false, false}, //"5p240",   //  15
        {false, false}, //"7p298",   //  16
        {false, false}, //"8p310",   //  17
        {false, false}, //"8p869",   //  18
        {false, false}, //"9p148",   //  19
        {false, false}, //"9p219",   //  20
        {false, false}, //"9p921",   //  21
        {false, false}  //"nuis"     //  22 for nuisance
    };

    bool IsFix[npar][2] = {
        {false, false}, //"bkg",     //  0
        {false, false}, //"7p115",   //  1
        {false, false}, //"6p916",   //  2
        {false, false}, //"6p32",    //  3
        {false, false}, //"6p13",    //  4
        {false, false}, //"5p27",    //  5
        {false, false}, //"5p104",   //  6 used by tano mthesis
        {false, false}, //"4p914",   //  7
        {false, false}, //"4p44",    //  8
        { true,  true}, //"3p839",   //  9 not used by tano mthesis
        {false, false}, //"3p68",    //  10
        {false, false}, //"2p742",   //  11
        {false, false}, //"2p30",    //  12
        {false, false}, //"5p183",   //  13
        {false, false}, //"6p176",   //  14
        { true,  true}, //"5p240",   //  15
        { true,  true}, //"7p298",   //  16
        { true,  true}, //"8p310",   //  17
        { true,  true}, //"8p869",   //  18
        { true,  true}, //"9p148",   //  19
        { true,  true}, //"9p219",   //  20
        { true,  true}, //"9p921",   //  21
        {false, false}  //"nuis"     //  22 for nuisance
    };

    Color_t iColor[] = {
        kGray+2,      //"bkg",  // 0
        kOrange+10,   //"7p115",// 1
        kAzure-1,     //"6p916",// 2
        kGreen+3,     //"6p32", // 3
        kTeal,        //"6p13", // 4
        kPink+9,      //"5p27", // 5
        kOrange,      //"5p104",// 6 not use
        kGreen-2,     //"4p914",// 7
        kSpring-1,    //"4p44", // 8
        kOrange-1,    //"3p839",// 9 not use
        kOrange+7,    //"3p68", // 10
        kYellow,      //"2p742",// 11
        kPink+4,      //"2p30", // 12 not use
        kBlue+1,      //"5p183",// 13
        kMagenta+1,   //"6p176",// 14
        kViolet+5,    //"5p240",// 15
        kGreen+3,     //"7p298",// 16
        kPink-2,      //"8p310",// 17
        kOrange+1,    //"8p869",// 18
        kYellow-1,    //"9p148",// 19
        kBlue+4,      //"9p219",// 20
        kViolet+1     //"9p921",// 21
    };

    int fix_idx = 1; //30
    double Target = 0.5*4.644e26; //30
    double flux = 1.356e4; //30
    double flux_err = 0.101;
    double nMC = 1e8; //30
    if(Ebeam == 250){
        fix_idx = 0; //250
        Target = 4.644e26; //250
        flux = 1.224e3; //250
        flux_err = 0.180;
        nMC = 1e8; //250
    }
    int Type = 0, Pre = 2;
    TFile *fin = TFile::Open(Form("root/Fit%03dMeV_Type%02d_Pre%02d.root", Ebeam, Type, Pre), "read");
        fin->cd();
    TH1D* hData = (TH1D*)fin->Get("hData");
    TH1D* hMCT = (TH1D*)hData->Clone("hMCT");
        hMCT->Reset();
        hMCT->SetLineColor(2);
        hMCT->SetLineWidth(2);
        hMCT->SetLineStyle(2);
    TH1D *hMCA[npar];
    double par[npar], parerr[npar];
    double CHIMIN;
    int NDF;
    TTree *tree = (TTree*)fin->Get("result");
        tree->SetBranchAddress("par", par);
        tree->SetBranchAddress("parerr", parerr);
        tree->SetBranchAddress("CHIMIN", &CHIMIN);
        tree->SetBranchAddress("NDF", &NDF);
    tree->GetEntry(0);

    TCanvas *c1 = new TCanvas("c1", "", 600, 300);
        c1->cd();
        if(IsLogScale) gPad->SetLogy();
    hData->GetXaxis()->SetRangeUser(2000, 8000);
    hData->GetXaxis()->SetTitle("Energy [keV]");
    hData->GetYaxis()->SetTitle("Counts [/#muC]");
    hData->Draw("pe");

    TLegend *l1 = new TLegend(0.7, 0.4, 0.95, 0.95);
        l1->SetNColumns(2);
        l1->AddEntry(hData, "Data", "pe");
        l1->AddEntry(hMCT, "Best-fit", "l");
    double total = 0;
    double total_err = 0;
    double total_woCont = 0;
    for(int ip=0;ip<npar;ip++){
        if(!IsFix[ip][fix_idx] && ip < npar-1){ //not fixed pars only
            //cout << Form("%d is not fixed", ip) << endl;
            hMCA[ip] = (TH1D*)fin->Get(Form("hMCA%d", ip));
            hMCA[ip]->SetLineColor(iColor[ip]);
            hMCA[ip]->Draw("HISTsame");

            hMCT->Add(hMCA[ip]);
        }

        double xs = par[ip] * nMC;
            if(ip==npar-1) xs /= 1e5;
            xs /= Target*flux;
            xs /= cm2barn;
        double xssys = xs * flux_err;
        double xserr = parerr[ip] * nMC;
            if(ip==npar-1) xserr /= 1e5;
            xserr /= Target*flux;
            xserr /= cm2barn;
            xserr = sqrt(xserr*xserr + xssys*xssys);
        if(ip!=npar-1) cout << Form("%s: %.2f +/- %.2f /1e5", par_list[ip].c_str(), par[ip]*1e5, parerr[ip]*1e5);
        else cout << Form("%s: %f +/- %f", par_list[ip].c_str(), par[ip], parerr[ip]);
        //cout << Form(" -> %.2f +/- %.2f +/- %.2f mb", xs, xserr, xssys) << endl;
        cout << Form(" -> %.2f +/- %.2f mb", xs, xserr) << endl;
        //total
        if(ip<npar-1){
            total += xs;
            if(ip>0) total_woCont += xs;

            total_err += xserr*xserr;
        }
    }
    hMCT->Draw("HISTsame");
    for(int ip=0;ip<13;ip++){
        if(!IsFix[ip][fix_idx] && ip < npar-1){ //not fixed pars only
            if(ip>0 && IsDraw[ip]){
                l1->AddEntry(hMCA[ip], Form("%1.2f MeV", atof(par_list[ip].c_str())), "l");
                if(ip == 3)
                    l1->AddEntry(hMCA[14], Form("%1.2f MeV", atof(par_list[14].c_str())), "l");
                if(ip == 5)
                    l1->AddEntry(hMCA[13], Form("%1.2f MeV", atof(par_list[13].c_str())), "l");
            } else l1->AddEntry(hMCA[ip], Form("%s", par_list[ip].c_str()), "l");
        }
    }
    if(!IsLogScale) l1->Draw("same");
    TText *text = new TText(0.38, 0.87, Form("%3d MeV", Ebeam));
        text->SetNDC(true);
        text->SetTextAlign(13);
        text->SetTextFont(43);
        text->SetTextSize(20);
    if(!IsLogScale) text->Draw("same");

    cout << Form("total xs = %f +/- %f mb", total, sqrt(total_err)) << endl;
    cout << Form("total xs w/o continuum  = %f +/- %f mb", total_woCont, sqrt(total_err)) << endl;
    cout << Form("CHI/NDF = %f / %d = %f", CHIMIN, NDF, CHIMIN/(double)NDF) << endl;
}
