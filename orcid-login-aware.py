from flask import Flask, redirect, jsonify, session, request, url_for
import flask_login
import json
import requests

class User(flask_login.UserMixin):
  def __init__(self,**kwargs):
    self.orcid = kwargs.get('orcid','no-orcid')
    self.fullname = kwargs.get('fullname','no-name')
  def get_id(self):
    return self.orcid
  def name(self):
    return self.fullname


app = Flask(__name__)
app.debug = True
app.secret_key = 'some_secret'


login_manager = flask_login.LoginManager()
login_manager.init_app(app)

@app.route("/")
def home():
  print url_for('login')
  return 'Hello World!'

ORCID_APPID = 'YOURAPPID'
ORCID_REDIRECT_URI = 'your_login_route.com/login' #should be pointing to the /login route
ORCID_SECRET = 'YOURSECRET'

@app.route('/login')
def login():
  if not request.args.has_key('code'):
    return  redirect('https://orcid.org/oauth/authorize?client_id={}&response_type=code&scope=/authenticate&redirect_uri={}&show_login=true'.format(
    ORCID_APPID,
    ORCID_REDIRECT_URI
  ))
  
  auth_code = request.args.get('code')
  data = {'client_id':ORCID_APPID,'client_secret':ORCID_SECRET,'grant_type':'authorization_code','code':auth_code}

  r = requests.post('https://pub.orcid.org/oauth/token', data = data)
  login_details = json.loads(r.content)

  user = User(orcid = login_details['orcid'], fullname = login_details['name'], authenticated = True)
  flask_login.login_user(user)
  
  return redirect(url_for('/'))

    
@app.route("/logout")
@flask_login.login_required
def logout():
    flask_login.logout_user()
    return redirect('/')  

@login_manager.user_loader
def load_user(userid):
    r = requests.get('http://pub.orcid.org/v1.2/{}/orcid-profile'.format(userid), headers = {'Accept':'application/json'})
    login_bio = json.loads(r.content)['orcid-profile']['orcid-bio']
    return User(orcid = userid, fullname = '{} {}'.format(login_bio['personal-details']['given-names']['value'],login_bio['personal-details']['family-name']['value']))

@login_manager.unauthorized_handler
def unauthorized():
    return 'sorry not authorized'


@app.route("/loggedin")
@flask_login.login_required
def loginview():
  return jsonify(user = flask_login.current_user.name())


if __name__ == '__main__':
  app.run(host = 'localhost',port = 5000)