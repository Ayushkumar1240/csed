import RPi.GPIO as GPIO
from mfrc522 import SimpleMFRC522
import time

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(3,GPIO.OUT)
GPIO.output(3,False)

a=423243557744638
reader=SimpleMFRC522()

try:
    print("palce your tag to authenticate")
    id, text=reader.read()
    print(type(id))
    print(id)
    print(text)
    if id == a:
        print("led on")
        GPIO.output(3,True)
        time.sleep(1)
        GPIO.output(3,False)
        time.sleep(1)
        print("DONE")
finally:
    GPIO.cleanup()