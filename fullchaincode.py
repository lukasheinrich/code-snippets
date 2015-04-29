# from adage import adagetask

import subprocess
import logging
import os
log = logging.getLogger(__name__)

from contextlib import contextmanager
import subprocess
import os


@contextmanager
def subprocess_in_env(envscript = None,workdir = None):
  if not workdir:
    workdir = os.getcwd()
    
  if not os.path.exists(workdir):
    os.makedirs(workdir)

  
  setupenv = 'source {0} && '.format(os.path.abspath(envscript)) if envscript else ''

  #helpful SO lesson on scoping: 
  #http://stackoverflow.com/questions/4851463/python-closure-write-to-variable-in-parent-scope#comment5388645_4851555

  def check_call(what):
    return subprocess.check_call('{0} {1}'.format(setupenv,what),cwd = workdir, shell = True)
  
  yield check_call
      

def pack_LHE_File(lhefile,counter,nameformat = None, outputdir = None):
  #nameformat could be e.g. 'basename._{0:05}.events'.format(3)'
  log.info('packaging LHE file {} using ATLAS conventions with counter {}'.format(lhefile,counter))

  if not os.path.exists(lhefile):
    log.error('file {} does not exist'.format(lhefile))
    return None
    
  dirname, basename = os.path.dirname(lhefile), os.path.basename(lhefile)
  
  if not outputdir:
    outputdir = os.getcwd()
  else:
    outputdir = outputdir.rstrip('/')
  
  formattedlhe = None
  if not nameformat:
    formatbase = basename.rsplit('.',1)[0]+'._{}.events'.format('{}'.format(counter).zfill(5))
  else:
    formatbase = nameformat.format()

  formattedlhe = '{}{}'.format('' if not outputdir else (outputdir+'/'),formatbase)

  try:
    os.link(lhefile,formattedlhe)
  except OSError:
    log.error('could not write to outputdir {}'.format(outputdir))
    return None

  try:
    tarballname = formattedlhe.rsplit('.',1)[0]+'.tar.gz'

    log.info('{} | {}'.format(formattedlhe,tarballname))
    
    subprocess.check_call(['tar','--directory',os.path.dirname(formattedlhe),
                           '-cvzf',tarballname,os.path.basename(formattedlhe)])
  finally:
    os.unlink(formattedlhe)

  return tarballname


def evgen(inputtarball,outputpoolfile,jobopts,runnr,seed,firstevt = 0, ecm = 14000, maxevents = 2, workdir = None):
  with subprocess_in_env(envscript = 'evgenenv.sh', workdir = workdir) as check_call:
    template = 'Generate_tf.py --randomSeed {seed} --runNumber {runnr} --ecmEnergy {ecm} --maxEvents {maxevents} --jobConfig {jobopts} --firstEvent {firstevt} --inputGeneratorFile {inputtarball} --outputEVNTFile {outputpoolfile}'

    check_call(template.format(
    seed = seed,
    runnr = runnr,
    ecm = ecm,
    maxevents = maxevents,
    jobopts = os.path.abspath(jobopts),
    firstevt = firstevt,
    inputtarball = os.path.abspath(inputtarball),
    outputpoolfile = os.path.abspath(outputpoolfile)
  ))
  
def sim(evgenfile, outputhitsfile, seed, maxevents = -1, workdir = None):
  with subprocess_in_env(envscript = 'basicathenv.sh', workdir = workdir) as check_call:
    template = 'AtlasG4_trf.py inputEvgenFile={evgenfile} outputHitsFile={outputhitsfile} maxEvents={maxevents} skipEvents=0 randomSeed={seed} geometryVersion={geometry} conditionsTag={conditions}'

    check_call(template.format(
    seed = seed,
    evgenfile = os.path.abspath(evgenfile),
    outputhitsfile = os.path.abspath(outputhitsfile),
    geometry = 'ATLAS-GEO-16-00-00',
    conditions = 'OFLCOND-SDR-BS7T-04-00',
    maxevents = maxevents
  ))
  


def digi(hitsfile, outputrdofile, maxevents = -1, workdir = None):
  with subprocess_in_env(envscript = 'basicathenv.sh', workdir = workdir) as check_call:
    template = 'Digi_trf.py inputHitsFile={hitsfile} outputRDOFile={outputrdofile} maxEvents={maxevents} skipEvents=0 geometryVersion={geometry}  conditionsTag={conditions}'
    
    check_call(template.format(
    hitsfile = os.path.abspath(hitsfile),
    outputrdofile = os.path.abspath(outputrdofile),
    geometry = 'ATLAS-GEO-16-00-00',
    conditions = 'OFLCOND-SDR-BS7T-04-00',
    maxevents = maxevents
  ))

def reco(rdofile, outputaodfile, maxevents = -1, workdir = None):
  with subprocess_in_env(envscript = 'basicathenv.sh', workdir = workdir) as check_call:
    template = 'Reco_trf.py inputRDOFile={rdofile} outputAODFile={outputaodfile} maxEvents={maxevents}'
    
    check_call(template.format(
    rdofile = os.path.abspath(rdofile),
    outputaodfile = os.path.abspath(outputaodfile),
    maxevents = maxevents
  ))
  