# generalTrack2018

This folder has macros to compare generalTracks quantities for 2018 data with 2015 data and Hydjet MC.

[Here](https://twiki.cern.ch/twiki/pub/CMS/HITracking2018PbPb/Nov9_generalTracksFirstLook.pdf) you can find slides with results generated with this macros for run 326389.

I created four macros to plot the track quantities. Each macro plot three variables.

## How to use

In your `$CMSSW_BASE/src` (i've used CMSSW_10_3_1), run it using:

`root -l -b -q plot_tree1.C &>1.txt &`

`root -l -b -q plot_tree2.C &>2.txt &`

`root -l -b -q plot_tree3.C &>3.txt &`

`root -l -b -q plot_tree4.C &>4.txt &`

I include some test with run 326722.
