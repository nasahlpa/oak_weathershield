import urllib
import json
import MySQLdb
import time
DB_USER = "TYPE_USERNAME"
DB_PW = "TYPE_PW"
DB_NAME = "TYPE_DB"
TOKEN = "TYPE_TOKEN"
DEVICE = "TYPE_DEVICE"

def writeDB(date, temperature, ambient, pressure, humidity):
  db = MySQLdb.connect(host="localhost", user=DB_USER, passwd=DB_PW, db=DB_NAME)
  cursor = db.cursor()
  cursor.execute("INSERT INTO weather (date, temperature, ambient, pressure, humidity) VALUES ('"+date+"', '"+str(temperature)+"', '"+str(ambient)+"', '"+str(pressure)+"', '"+str(humidity)+"');")
  db.commit()
  db.close()
  
def fetchURL(identifier):
  base = "https://api.particle.io/v1/devices/"
  var = "/"+identifier;
  option = "?access_token=" 
  
  url = base + DEVICE + var + option + TOKEN
  data = urllib.urlopen(url).read()
  data_json = json.loads(data)
  
  return round(float(data_json["result"]), 2)
  
def getData():
  now = time.strftime('%Y-%m-%d %H:%M:%S')
  temp = fetchURL("temperature")
  amb = fetchURL("ambient")
  press = fetchURL("pressure")
  hum = fetchURL("humidity")
  writeDB(now, temp, amb, press, hum)

getData()
