import RPi.GPIO as GPIO
from mfrc522 import SimpleMRFC522
import time

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
reader=SimpleMRFC522()
buzzer=3
GPIO.setup(buzzer,GPIO.OUT,initial=GPIO.LOW)
GPIO.setup(5,GPIO.OUT)
GPIO.output(5,False)

a=356643256257

try:
    print("place your tag:")
    id, text=reader.read()

    if(id==a):
        print("Access granted")
        GPIO.output(5,GPIO.HIGH)
        time.sleep(1)
    else:
        print("Access Denied")
        GPIO.output(buzzer,GPIO.HIGH)
        time.sleep(1)
finally:
    GPIO.cleanup()