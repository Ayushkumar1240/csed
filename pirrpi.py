from requests.auth import HTTPBasicAuth

import RP1.GPIO as GPIO 
from gpiozero import MotionSensor

from getpass import getpass 
import time

from time import sleep 
import requests
import http.client as http_client
http_client.HTTPConnection.debug=1

pir-MotionSensor (4) 
webhost= "http://dcs.glaitm.org:7080"
App_key="55e4e110-e869-4701-aefa-1314467707ce"
ThingNamel="pirsensorthing"
Property1="data"
header = {"Content-Type": "application/json", "appkey" :App_key}

while True:
    try:
        var= pir.wait_for_motion()
        time.sleep(1)
        payload=(Propertyl: var)
        print (1)
        responsel=requests. put (webhost+"/Thingworx/Things/"+ Thing Namel+"/Properties/*" headers= header, json = payload, verify=False) 
        print (responsel)
        pir.wait for no motion()
        time.sleep(1) print("")
        except Exception as error:
        print("error") 
        break 
    except KeyboardInterrupt: 
        print("user Interrupt")
        break
        
        
       