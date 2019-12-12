#!/usr/bin/python3

from ev3dev2.sensor import *
from ev3dev2.motor import *
from ev3dev2.sensor.lego import *
from ev3dev2.led import Leds
from ev3dev2.sound import Sound
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
normalspeed = 40
turnlow = 15
speedincrement = 10
increment_of_increment = normalspeed/12
maxspeed = 100
listenlänge = 5
wandabstand = 20
kurvengeschwindigkeit = 20

def run():
    global speed1, speed2
    left_motor.run_direct()
    right_motor.run_direct()

    while True:
        leftlight = ls1.reflected_light_intensity
        rightlight = ls2.reflected_light_intensity
        abstand = us.distance_centimeters
        # speed1 = normalspeed
        # speed2 = normalspeed
        if leftlight < schwarz and rightlight < schwarz and abstand > wandabstand:
            speed1 = normalspeed
            speed2 = normalspeed
            speedincrement = 10
        elif leftlight < schwarz and rightlight > schwarz:
            speed1 = normalspeed - kurvengeschwindigkeit - speedincrement
            speed2 = normalspeed - kurvengeschwindigkeit + speedincrement
            if speed1 <= 0:
                speed1 = 10
            if speed2 > 100:
                speed2 = maxspeed
            speedincrement += increment_of_increment
        elif leftlight > schwarz and rightlight < schwarz:
            speed2 = normalspeed - kurvengeschwindigkeit - speedincrement
            speed1 = normalspeed - kurvengeschwindigkeit + speedincrement
            if speed2 <= 0:
                speed2 = 10
            if speed1 > 100:
                speed1 = maxspeed
            speedincrement += increment_of_increment
        elif leftlight > schwarz and rightlight > schwarz and abstand < wandabstand:
            turn()
        else:
            search_direction()

        left_motor.duty_cycle_sp = speed1
        right_motor.duty_cycle_sp = speed2

        time.sleep(0.001)

def turn():
    left_motor.duty_cycle_sp = normalspeed
    right_motor.duty_cycle_sp = - normalspeed
    time.sleep(basetime*6*75/normalspeed)
    # left_motor.duty_cycle_sp = normalspeed
    # right_motor.duty_cycle_sp = normalspeed
    
    # while True:
    #     leftlight = ls1.reflected_light_intensity
    #     rightlight = ls2.reflected_light_intensity

    #     if leftlight < schwarz or rightlight < schwarz:
    #         break
    #     time.sleep(0.002)

def search_direction():
    left_motor.duty_cycle_sp = normalspeed
    right_motor.duty_cycle_sp = normalspeed
    time.sleep(basetime*3.8*75/normalspeed)
    leftlight = ls1.reflected_light_intensity
    rightlight = ls2.reflected_light_intensity

    if leftlight > schwarz and rightlight > schwarz:
        left_motor.duty_cycle_sp = - normalspeed
        right_motor.duty_cycle_sp = - normalspeed
        time.sleep(basetime*4*75/normalspeed)
        left_motor.duty_cycle_sp = 0
        right_motor.duty_cycle_sp = 0

        left_motor.duty_cycle_sp = normalspeed
        right_motor.duty_cycle_sp = - normalspeed
        time.sleep(basetime*3.5*75/normalspeed)
        left_motor.duty_cycle_sp = 0
        right_motor.duty_cycle_sp = 0
        time.sleep(basetime)
        leftlight = ls1.reflected_light_intensity
        rightlight = ls2.reflected_light_intensity

        if leftlight > schwarz and rightlight > schwarz:
            turn()
            left_motor.duty_cycle_sp = 0
            right_motor.duty_cycle_sp = 0
        

run()