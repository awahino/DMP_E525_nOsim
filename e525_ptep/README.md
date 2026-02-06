# E525 Data Open
The background (beam-unrelated and non-water components) subtracted spectra and the fit results are in public.
The root files contain
- the observed gamma-ray spectrum in TH1D histogram (hData).
- 15 MC spectra of gamma-rays corresponding to each nuclear level in TH1D histogram (hMCx).
- the fit reasult summarized in TTree (result).
    - npar ...the number of types of gamma-rays assumed in this analysis.
    - fit_min ...the lower edge of the fit range
    - fit_max ...the upper edge of the fit range
    - par[napr] ...the parameter values as the result of fit.
    - parerr[napr] ...the error of each parameter value as the result of fit.
    - CHIMIN ...chi-squared value as the result of fit.
    - NDF ...the number of degree of freedom of the fit.

It was confirmed that ROOT6.32.08 worked to read the root file and make plots.
The other versions of ROOT could work in principle (but not checked).

# Example code to make a plot
The codes to make the following plots are included as the data open.

## Fig.12, 13
For making a plot in Fig.12, you can run the macro by
```
root drawPlot.C'(30, 0)'
```
where the first argument corresponds to beam energy (30 or 250).

The second argument controls the scale of Y axis:
- 0 ...linear scale
- 1 ...log scale

## Fig.14
For making a plot in Fig.14, you can run the macro by
```
root drawFig14.C
```
witout any arguments.
