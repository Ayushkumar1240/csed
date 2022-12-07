from requests.auth import HTTPBasicAuth
from getpass import getpass
import time
import requests
import http.client as http_client
http_client.HTTPConnection.debuglevel=1
webhost ="http://dcs.glaitm.org:7080"
App_Key=""
ThingName=""
Property1='Distance'
data1=100

headers={'Content-Type':'application/json','appKey':App_Key}

while True:
try:
    time.sleep(3)
    payload={Property1:data1}
    response=requests.put(webhost+'/Thingworx/Things/'+ThingName+'/Properties/*',headers=headers,json=payload)
    print(response)
    time.sleep(2)

except Exception as error:
    print(error)