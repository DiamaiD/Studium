#!/usr/bin/python3

# from ev3dev2.sensor import INPUT_1
# from ev3dev2.sensor import INPUT_2
# from ev3dev2.sensor import INPUT_3
from ev3dev2.sensor import *
from ev3dev2.motor import *
#from ev3dev2.sensor import OUTPUT_B
from ev3dev2.sensor.lego import *
from ev3dev2.led import Leds
from ev3dev2.sound import Sound
import threading
from queue import Queue
import time

ls1 = LightSensor(INPUT_3)
ls2 = LightSensor(INPUT_1)
leds = Leds()
us = UltrasonicSensor()
# tank_drive = MoveTank(OUTPUT_A, OUTPUT_B)
left_motor = LargeMotor(OUTPUT_A)
right_motor = LargeMotor(OUTPUT_B)

# from ev3dev2.sound import Sound
sound = Sound()
# sound.speak('Hallo ich bin Roberto ihr Pimmelberger!')
schwarz = 40
speed1 = 0
speed2 = 0
basetime = 0.1
normalspeed = 75
turnlow = 15
speedincrement = 10
maxspeed = 100

def turn():
    global speed1, speed2
    left_motor.run_direct()
    right_motor.run_direct()
    while True:
        if ls1.reflected_light_intensity < schwarz and ls2.reflected_light_intensity < schwarz:
            speed1 = normalspeed
            speed2 = normalspeed
            left_motor.duty_cycle_sp = speed1
            right_motor.duty_cycle_sp = speed2
        elif ls1.reflected_light_intensity < schwarz and ls2.reflected_light_intensity > schwarz:
            speed1 = turnlow
            speed2 += speedincrement
            if speed2 > maxspeed:
                speed2 = maxspeed
            left_motor.duty_cycle_sp = speed1
            right_motor.duty_cycle_sp = speed2
        elif ls1.reflected_light_intensity > schwarz and ls2.reflected_light_intensity < schwarz:
            speed1 += speedincrement
            speed2 = turnlow
            if speed1 > maxspeed:
                speed1 = maxspeed
            left_motor.duty_cycle_sp = speed1
            right_motor.duty_cycle_sp = speed2
        elif ls1.reflected_light_intensity > schwarz and ls2.reflected_light_intensity > schwarz:
            speed1 = -50
            speed2 = -50
            left_motor.duty_cycle_sp = speed1
            right_motor.duty_cycle_sp = speed2
            time.sleep(basetime)
            speed1 = 50
            left_motor.duty_cycle_sp = speed1
            right_motor.duty_cycle_sp = speed2
        time.sleep(0.002)
        # time.sleep(basetime)
        # else:
        #     sound.speak('Alarm!')
turn()
# thread1 = threading.Thread( target=basespeed, args=() )
# thread2 = threading.Thread( target=turn, args=() )

# thread1.start()
# thread2.start()