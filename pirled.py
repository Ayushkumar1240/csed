import RPi.GPIO as GPIO
import time

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(11,GPIO.IN)            #read output from pir
GPIO.setup(3,GPIO.OUT)            #led output pin

while True:
    i=GPIO.input(11)
    if i==0:
        print "No intruder", i
        GPIO.output(3,0)
        time.sleep(0.1)
    else:
        if i==1:
            print "intruder detected",i
            GPIO.output(3,1)          #trun on led
            time.sleep(0.1)