import grovepi
import time
from grove_rgb_lcd import *

# set I2C to use the hardware bus
grovepi.set_bus("RPI_1")

# Connect the Grove Ultrasonic Ranger to digital port D4
# SIG,NC,VCC,GND
ultrasonic_ranger = 4

# Connect the Grove Rotary Angle Sensor to analog port A0
# SIG,NC,VCC,GND
potentiometer = 0

grovepi.pinMode(potentiometer,"INPUT")
time.sleep(1)


# Reference voltage of ADC is 5v
adc_ref = 5

# Vcc of the grove interface is normally 5v
grove_vcc = 5

# Full value of the rotary angle is 300 degrees, as per it's specs (0 to 300)
full_angle = 300

set_val = 0
dist = 0
string1 = ""
string2 = ""

while True:
    try:
        dist = grovepi.ultrasonicRead(ultrasonic_ranger)
        set_val = grovepi.analogRead(potentiometer)

    except Exception as e:
        print ("Error:{}".format(e))
    
    if (dist > set_val):
        setRGB(0,255,0)
        string1 = str(set_val) + "cm" + "\n"
        string2 = str(dist) + "cm"
        setText(string1 + string2)
    else:
        setRGB(255,0,0)
        string1 = str(set_val) + "cm OBJ PRES" + "\n"
        string2 = str(dist) + "cm"
        setText(string1 + string2)
    
    time.sleep(0.1) # don't overload the i2c bus