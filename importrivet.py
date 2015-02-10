#!/usr/bin/env python
import rivet
import pickle
import recastapi.analysis
import feedparser
import bibtexparser

def isArxiv(refstring):
    if refstring.lower().startswith('arxiv:'): return True
    if refstring.lower().startswith('hep-ex'): return True
    return False

def isDOI(refstring):
    if refstring.lower().startswith('doi:'): return True

def getTitleFromArxiv(query):
  feed = feedparser.parse('http://export.arxiv.org/api/query?search_query={}'.format(query))
  assert len(feed['entries'])==1
  return ' '.join(feed['entries'][0]['title'].split()) #remove whitespace

def getLinkFromArxiv(query):
  feed = feedparser.parse('http://export.arxiv.org/api/query?search_query={}'.format(query))
  filtered = filter(lambda x:query in x['link'],feed['entries'])
  assert len(filtered)==1
  return feed['entries'][0]['link'] #remove whitespace


import re
def getArxivSearchTerm(refname):
  #new style e.g. '1234.5493'
  match = re.search('[0-9]{4}.[0-9]{4}',refname)
  if match: return match.group(0)

  #old style e.g. 'arxiv:hep-ex/0211007'
  match = re.search('[a-z\-]+/[0-9]+',refname)
  if match: return match.group(0)

  raise NotImplementedError

def getTitle(rivetanalysis):
  #first try bibTeX
  if rivetanalysis.bibTeX():
    parsed = bibtexparser.loads(rivetanalysis.bibTeX().replace(',',',\n')).entries
    assert len(parsed)==1
    assert parsed[0].has_key('title')
    return parsed[0]['title']
  #try going through arXiv
  arxivrefs = filter(isArxiv,rivetanalysis.references())
  if len(arxivrefs)==1:
    return getTitleFromArxiv(getArxivSearchTerm(arxivrefs[0]))
  
  #nothing worked.. use the Rivet Title :(
  print rivetanalysis.name()
  raise RuntimeError
  return rivetanalysis.name()
        

def main():
    #get all rivet LHC analyses
    a = {x:rivet.AnalysisLoader.getAnalysis(x) for x in  rivet.AnalysisLoader.analysisNames()}
    a = {k:v for k,v in a.iteritems() if 'LHC' in v.collider() and v.experiment() in ['ATLAS','CMS'] and v.status() == 'VALIDATED'}
    
    rivetmap = {}
    for k,v in a.iteritems():
      user = 'lheinric'
      title = ' '.join(getTitle(v).split())

      description = v.description()
      collaboration = 'Atlas' if (v.experiment().lower()=='atlas') else v.experiment()

      if(collaboration not in ['Atlas','D0','CDF','CMS','ALEPH']): continue

      try:
        e_print = ','.join([getLinkFromArxiv(getArxivSearchTerm(r)) for r in filter(isArxiv,v.references())])
      except AssertionError:
        print k
        raise RuntimeError
      doi = ','.join(filter(isDOI,v.references()))
      journal = ','.join(filter(lambda x:not (isDOI(x) or isArxiv(x)),v.references()))
      inspireurl = 'http://inspirehep.net/record/{}'.format(v.inspireId()) if v.inspireId() else ''

      print "----------"
      print title
      print "ANALYSIS {}".format(title)
      print "COLLABORATION: {}".format(collaboration)
      print "EPRINT: {}".format(e_print)
      print "JOURNAL: {}".format(journal)
      print "DOI: {}".format(doi)
      print "INSPIREURL: {}".format(inspireurl)
      print "DESCRIPTION: {}".format(description)
      print "----------\n\n"
      # uuid = recastapi.analysis.createAnalysis(user,title,collaboration,e_print,journal,doi,inspireurl,description)
      # rivetmap[k] = uuid
      
    # pickle.dump(rivetmap,open('rivetmap.pickle','w'))
    
      
if __name__ == '__main__':
  main()