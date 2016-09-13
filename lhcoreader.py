
def read_lhco(filename):
    event = None
    x = open(filename)
    for line in x:
        if line.strip().startswith('#'): continue
        line = line.strip().split()
        if line[0]=='0':
            if event is not None:
                yield event
            event = {'eventinfo':{'eventnr': line[1], 'trigger': line[2]},'particles':[]}
            continue
        event['particles'] += [{
            'nr':line[0],
            'typ':line[1],
            'eta':line[2],
            'phi':line[3],
            'pt':line[4],
            'jmass':line[5],
            'ntrk':line[6],
            'btag':line[7],
            'hadem':line[8]
        }]
    yield event
