#!/usr/bin/env python
import ROOT
import IPython

MGPATH = '/Users/lukas/Code/atlas/threebody/signalprod/mg5amcnlo'

def setup():
    ROOT.gSystem.Load(MGPATH+'/ExRootAnalysis/lib/libExRootAnalysis.so')

def main():
    setup()
    f = ROOT.TFile.Open('ppee/Events/run_01/events.lhe.root')
    t = ROOT.LHEF
    reader = ROOT.ExRootTreeReader(t)
    particles = reader.UseBranch("Particle")
    for i in xrange(0,reader.GetEntries()):
        reader.ReadEntry(i)
        IPython.embed()
    
if __name__ == '__main__':
    main()