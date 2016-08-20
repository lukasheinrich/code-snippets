from flask import Flask, jsonify, session
from flask_oauth import OAuth
import requests
import json

app = Flask(__name__)
app.secret_key = 'secret'
config = json.load(open('config.json'))

oauth = OAuth()
oauth_app = oauth.remote_app('oauth_app',
    base_url=None,
    request_token_url=None,
    access_token_url=config['TOKENURL'],
    authorize_url=config['AUTHORIZEURL'],
    consumer_key = config['APPID'],
    consumer_secret = config['SECRET'],
    request_token_params= {'response_type':'code','scope':'bio'},
    access_token_params = {'grant_type':'authorization_code'},
    access_token_method = 'POST'
)

def user_data(access_token):
    r = requests.get('https://oauthresource.web.cern.ch/api/Me',
        headers = {'Authorization':'Bearer {}'.format(session['access_token'])})
    return r.json()

@app.route(config['REDIRECT_ROUTE'])
@oauth_app.authorized_handler
def login(resp):
    session['access_token'] = resp['access_token']
    data = user_data(session['access_token'])
    return jsonify(data)

@app.route('/')
def home():
    redirect_uri = config['MYHOST']+config['REDIRECT_ROUTE']
    return oauth_app.authorize(callback=redirect_uri)

if __name__ == '__main__':
   app.run(ssl_context = 'adhoc', port = 443)
