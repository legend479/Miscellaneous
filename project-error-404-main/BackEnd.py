from flask import Flask, render_template, request
import sqlite3

app = Flask(__name__)

@app.route('/')
@app.route('/home')

def index():
    return render_template('HomePage.html')

connect = sqlite3.connect('database.db')
connect.execute(
    'CREATE TABLE IF NOT EXISTS PLAYLIST (ID TEXT, \
    , albumCoverUrl TEXT, Duration TEXT, Name TEXT)')
  
def AddToPlayList():
    