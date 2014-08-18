import pyAMI.client
import pyAMI.query
import itertools

dataset = 'mc12_8TeV.105200.McAtNloJimmy_CT10_ttbar_LeptonFilter.merge.NTUP_SUSY.e1513_s1499_s1504_r3945_r3549_p1328/'
ami = pyAMI.client.AMI()
provenance = pyAMI.query.get_provenance(ami,dataset)

#provenance tree can branch (2 parents) ignoring here
provinfos = [pyAMI.query.get_dataset_info(ami,k[0]) for i,k in provenance.iteritems()] 

#just a set of all tags used.. order not preserved 
amitags = set(itertools.chain(*[p.info.get('version','').split('_') for p in provinfos]))
print amitags

#even better
configtags = pyAMI.query.get_dataset_info(ami,dataset).info['version']
pyAMI.query.get_configtags(ami,configtags)
