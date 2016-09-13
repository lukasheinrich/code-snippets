import matplotlib
matplotlib.use('PS')

import lhcoreader
import sys
import click
import matplotlib.pyplot as plt
import numpy as np

def yield_pts(filename):
    for i,e in enumerate(lhcoreader.read_lhco(filename)):
        parts = e['particles']
        for p in parts:
            yield p['pt']

@click.command()
@click.argument('inputfile')
@click.argument('plotfile')
def cli(inputfile,plotfile):
    plt.hist([x for x in yield_pts(inputfile)], bins = np.linspace(0,200,25))
    plt.savefig(plotfile)

if __name__ == '__main__':
    cli()
