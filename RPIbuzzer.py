import RPi.GPIO as GPIO
from time import sleep

GPIO.setwarnings(False)               #disable warnings                                  
GPIO.setmode(GPIO.BCM)                #select GPIO mode

buzzer=23                             #set buzzer -pin 23 as output
GPIO.setup(buzzer,GPIO.OUT)

while True:                           #run forever loop
    GPIO.output(buzzer,GPIO.HIGH)
    print("beep")
    sleep(0.5)
    GPIO.output(buzzer,GPIO.LOW)
    print("no beep")
    sleep(0.5)