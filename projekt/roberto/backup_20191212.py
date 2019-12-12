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
schwarz = 50
speed1 = 0
speed2 = 0
basetime = 0.1
normalspeed = 50
turnlow = 5
maxspeed = 100
increment_of_increment = normalspeed/8
listenlänge = 5
wandabstand = 20
torabstand = 5
kurvengeschwindigkeit = 30

def run():
    global speed1, speed2
    left_motor.run_direct()
    right_motor.run_direct()
    geradendurchlauf = 1
    speedincrement = kurvengeschwindigkeit
    turned_right = 0
    turned_left = 0

    while True:
        
        leftlight = ls1.reflected_light_intensity
        rightlight = ls2.reflected_light_intensity
        abstand = us.distance_centimeters

        if (leftlight < schwarz or rightlight < schwarz) and abstand < torabstand:
            left_motor.duty_cycle_sp = 0
            right_motor.duty_cycle_sp = 0
            while True:
                abstand = us.distance_centimeters
                if abstand > wandabstand:
                    break
        elif leftlight < schwarz and rightlight < schwarz and abstand > torabstand:
            speed1 = (normalspeed*2 + normalspeed/geradendurchlauf*8) / 10
            speed2 = (normalspeed*2 + normalspeed/geradendurchlauf*8) / 10
            speedincrement = kurvengeschwindigkeit
            if geradendurchlauf > 1:
                geradendurchlauf -= 1
            # if turned_left >= 1:
            #     speed2 = speed2/2
            # elif turned_right >= 1:
            #     speed1 = speed1/2
            turned_left = 0
            turned_right = 0
        elif leftlight < schwarz and rightlight > schwarz:
            geradendurchlauf = 30
            speed1 = turnlow
            speed2 = speedincrement
            if speed2 > 100:
                speed2 = maxspeed
            speedincrement += increment_of_increment
            turned_left += 1
        elif leftlight > schwarz and rightlight < schwarz:
            geradendurchlauf = 30
            speed1 =  speedincrement
            speed2 = turnlow
            if speed1 > 100:
                speed1 = maxspeed
            speedincrement += increment_of_increment
            turned_right += 1
        elif leftlight > schwarz and rightlight > schwarz and abstand < wandabstand:
            start_turn()
        else:
            search_direction()

        left_motor.duty_cycle_sp = speed1
        right_motor.duty_cycle_sp = speed2

        time.sleep(0.002)
        # if turned_right >= 1 or turned_left >= 1:
        #     left_motor.duty_cycle_sp = 0
        #     right_motor.duty_cycle_sp = 0

def turn():
    left_motor.duty_cycle_sp = normalspeed
    right_motor.duty_cycle_sp = - normalspeed
    if normalspeed == 50:
        time.sleep(basetime*11) # 11 bei 50 speed, 6.5 bei 75
    elif normalspeed == 75:
        time.sleep(basetime*6.5)

def start_turn():
    left_motor.duty_cycle_sp = normalspeed
    right_motor.duty_cycle_sp = - normalspeed
    if normalspeed == 50:
        time.sleep(basetime*11) # 11 bei 50 speed, 6.5 bei 75
    elif normalspeed == 75:
        time.sleep(basetime*6.5)
    left_motor.duty_cycle_sp = normalspeed
    right_motor.duty_cycle_sp = normalspeed
    
    while True:
        leftlight = ls1.reflected_light_intensity
        rightlight = ls2.reflected_light_intensity

        if leftlight < schwarz or rightlight < schwarz:
            break
        time.sleep(0.002)

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
        if normalspeed == 75:
            time.sleep(basetime*3.8) # 5.2 bei 50 normalspeed, 3.8 bei 75
        elif normalspeed == 50:
            time.sleep(basetime*5.2)
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