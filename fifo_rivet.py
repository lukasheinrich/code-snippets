def run(fifoname):
  os.mkfifo(fifoname)
  pythia = subprocess.Popen(['./implementation/pythia/pythiarun',steername,fifoname])
  rivet = subprocess.call(['rivet','-a','DMHiggsFiducial',fifoname,'-H',yodaname])
  pythia.wait()
  os.remove(fifoname)
