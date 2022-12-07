from gpiozero import MotionSensor
pir=MotionSensor(4)

while True:
    pir.wait_for_motion()
    print("YOU MOVED")
    pir.wait_for_no_motion()