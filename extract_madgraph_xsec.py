#!/bin/env

#
# small script to extract cross section from madgraph banners...
#

import json
import xml.etree.ElementTree  as ET
import re
import click


@click.command()
@click.argument("bannerfile")
def extract(bannerfile): 
    x = ET.parse(open(bannerfile))
    xsecline = filter(lambda x: 'Integrated weight' in x,x.find('header/MGGenerationInfo').text.split('\n'))[0]
    data = {"xsec":float(xsecline.split(':')[1]), "unit":re.match('.*Integrated weight \((.*)\)',xsecline).group(1)}
    print json.dumps(data)

if __name__ == '__main__':
    extract()
