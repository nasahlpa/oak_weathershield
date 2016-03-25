from sseclient import SSEClient
import json
import re
import MySQLdb
import time
DB_USER = "USERNAME"
DB_PW = "PASSWORD"
DB_NAME = "weather"
TOKEN = "DEVICE TOKEN"
DEVICE = "DEVICE ID"

def writeDB(date, temperature, ambient, pressure, humidity):
  db = MySQLdb.connect(host="localhost", user=DB_USER, passwd=DB_PW, db=DB_NAME)
  cursor = db.cursor()
  cursor.execute("INSERT INTO weather (date, temperature, ambient, pressure, humidity) VALUES ('"+date+"', '"+str(temperature)+"', '"+str(ambient)+"', '"+str(pressure)+"', '"+str(humidity)+"');")
  db.commit()
  db.close()

deviceID = 'd957040111349e5e9de61914'
accessToken = 'e61fb85a90a4b5ed7b0e99979133f1ca8a9ede93'
sparkURL = 'https://api.particle.io/v1/devices/' + deviceID + '/events/?access_token=' + accessToken

messages = SSEClient(sparkURL)
parse = re.compile('weather;(.*?)","ttl"')

for msg in messages:
  data = parse.search(msg.data)
  if data:
    data_split = data.group(1).split(';')
    now = time.strftime('%Y-%m-%d %H:%M:%S')
    temperature = data_split[0]
    ambient = data_split[1]
    pressure = data_split[2]
    humidity = data_split[3]
    writeDB(now, temperature, ambient, pressure, humidity)
    
