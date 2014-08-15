#!/usr/bin/env python
from hepmcanalysis.events import events
from hepmcanalysis.streamproxy import ifstream_proxy
import hepmc

def main():
  proxy = ifstream_proxy('./input.hepmc')

  g = hepmc.IO_GenEvent(proxy.stream())
  for i,e in enumerate(events(g)):
    print 'event #{}: number of particles in event: {}'.format(i,len(e.particles()))
    print e

if __name__ == '__main__':
  main()