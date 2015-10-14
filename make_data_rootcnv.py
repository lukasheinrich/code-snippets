#!/usr/bin/env python
import ROOT
import random
def main():
  f = ROOT.TFile.Open('input.root','recreate')

  nom = ROOT.TH1F('nominal_histo','nominal_histo',2,0,2)
  up = ROOT.TH1F('syst_up','syst_up',2,0,2)
  dn = ROOT.TH1F('syst_down','syst_down',2,0,2)

  
  nom.SetBinContent(1,10)
  nom.SetBinContent(2,20)
  nom.Sumw2(0)
  nom.Write()

  up.SetBinContent(1,12)
  up.SetBinContent(2,24)
  up.Sumw2(0)
  up.Write()

  dn.SetBinContent(1,8)
  dn.SetBinContent(2,16)
  dn.Sumw2(0)
  dn.Write()

  data1 = ROOT.TH1F('data1','data1',2,0,2)
  data1.SetBinContent(1,10.2)
  data1.SetBinContent(2,19.7)
  data1.Sumw2(0)
  data1.Write()

  data2 = ROOT.TH2F('data2','data2',6,-3,3,6,-3,3)
  for i in xrange(10000):
    data2.Fill(random.normalvariate(0,1),random.normalvariate(0,1))
  data2.Sumw2(0)
  data2.Write()
  f.Close()
  
if __name__=='__main__':
  main()