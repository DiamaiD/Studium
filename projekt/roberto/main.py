#!/usr/bin/python3

from ev3dev2.sensor import INPUT_1
from ev3dev2.sensor import INPUT_2
from ev3dev2.sensor import INPUT_3
#from ev3dev2.sensor import OUTPUT_A
#from ev3dev2.sensor import OUTPUT_B
from ev3dev2.sensor.lego import *
#from ev3dev2.sensor.lego import UltrasonicSensor
from ev3dev2.led import Leds
#from ev3dev2.sonsor.lego import 

ls1 = LightSensor(INPUT_1)
ls2 = LightSensor(INPUT_3)
leds = Leds()
us = UltrasonicSensor()
tank_drive = MoveTank(OUTPUT_A, OUTPUT_B)

while True:
    if ls1.reflected_light_intensity > 33:
        leds.set_color("LEFT","GREEN")
        tank_drive.on_for_rotations(SpeedPercent(50), SpeedPercent(75), 10)
    else:
        leds.set_color("LEFT", "RED")
    # if ls2.reflected_light_intensity < 33:
    #     leds.set_color("RIGHT","GREEN")
    # else:
    #     leds.set_color("RIGHT","RED")