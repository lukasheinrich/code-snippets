#!/usr/bin/env python
import pyAMI.client
import pyAMI.query
import itertools
import IPython
import argparse
from PyJobTransforms.trfAMI import TagInfo

parser = argparse.ArgumentParser()
parser.add_argument('dataset',type=str,help='dataset to inspect. e.g.: mc12_8TeV.105200.McAtNloJimmy_CT10_ttbar_LeptonFilter.merge.NTUP_SUSY.e1513_s1499_s1504_r3945_r3549_p1328/')

args = parser.parse_args()

def ioargs(datatype):
    specialcases = {
        'EVNT':{'in':'inputEvgenFile','out':None},
        'HITS':{'in':'inputHitsFile','out':'outputHitsFile'},
    }
    return specialcases.get(datatype,{'in':'input{0}File'.format(datatype),'out':'output{0}File'.format(datatype)})

def trfcmds(dataset):
    ami = pyAMI.client.AMI()
    trfcmd = []
    for step in trfsteps(ami,dataset):
        taginfo = TagInfo(step['tag'])
        tr = taginfo.trfs[0]
        if 'Merging' in tr.name or 'Generate' in tr.name: continue
        trargs = dict([(k,v) for k,v in tr.physics.iteritems() if k != 'DBRelease'])
        trargs = {}
        trargs['AMI'] = step['tag']
        trargs[ioargs(step['in'])['in']] = 'step.{0}.pool.root'.format(step['in'])
        trargs[ioargs(step['out'])['out']] = 'step.{0}.pool.root'.format(step['out'])
        cmd = tr.name+' '+' '.join(['{}=\'{}\''.format(k,v) for k,v in trargs.iteritems()])
        trfcmd += ['asetup {0},slc5,here && {1} maxEvents=1'.format(tr.release,cmd)]
    return trfcmd

def trfsteps(ami,dataset):
    provenance = pyAMI.query.get_provenance(ami,dataset) #just for fun but slow
    datainfos = [(k,pyAMI.query.get_dataset_info(ami,p[0])) for k,p in provenance.iteritems()]
    type_and_tag = sorted([(k,d.info.get('dataType'),d.info.get('version')) for k,d in datainfos])
    transformed = [(t,v.split('_')[-1]) for (k,t,v) in type_and_tag if v is not None]
    a,b = itertools.tee(transformed)
    next(b,None)
    trfs = list(itertools.izip(a,b))
    return [{'in':t[0][0],'out':t[1][0],'tag':t[1][1]} for t in trfs]

def main():
    for cmd in trfcmds(args.dataset):
        print '-------'
        print cmd
                  
if __name__ == '__main__':
    main()
