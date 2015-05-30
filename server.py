import subprocess
from flask import Flask, request
app = Flask(__name__)
@app.route('/')
def render():
  path = request.args.get('notebook', '')
  out,err = subprocess.Popen(['ipython','nbconvert','--to','html',path,'--stdout'],stdout=subprocess.PIPE).communicate()
  return out
if __name__ == '__main__':
    app.run()