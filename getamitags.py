#!/usr/bin/env python
import pyAMI.client
import pyAMI.query
import itertools
import IPython
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('dataset',type=str,help='dataset to inspect. e.g.: mc12_8TeV.105200.McAtNloJimmy_CT10_ttbar_LeptonFilter.merge.NTUP_SUSY.e1513_s1499_s1504_r3945_r3549_p1328/')

args = parser.parse_args()

def main():
    ami = pyAMI.client.AMI()
#provenance = pyAMI.query.get_provenance(ami,dataset) #just for fun but slow
    print 'getting AMI tags for {}'.format(args.dataset)
    
    leafversion = pyAMI.query.get_dataset_info(ami,args.dataset).info['version']
    amitags = pyAMI.query.get_configtags(ami,leafversion)
    summary = [{'step':entry['productionStep'],'trf':entry['transformation'],'tag':entry['tag']} for entry in amitags[1:]]
    for s in summary: print s

if __name__ == '__main__':
    main()
