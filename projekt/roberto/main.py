#!/usr/bin/python3

from ev3dev2.sensor import *
from ev3dev2.motor import *
from ev3dev2.sensor.lego import *
from ev3dev2.led import Leds
from ev3dev2.sound import Sound
import time

ls1 = LightSensor(INPUT_2)
ls2 = LightSensor(INPUT_1)
ls3 = ColorSensor(INPUT_4)
leds = Leds()
us = UltrasonicSensor()
# tank_drive = MoveTank(OUTPUT_A, OUTPUT_B)
left_motor = LargeMotor(OUTPUT_B)
right_motor = LargeMotor(OUTPUT_A)
mid_motor = LargeMotor(OUTPUT_D)

# from ev3dev2.sound import Sound
sound = Sound()
# sound.speak('Hallo ich bin Roberto ihr Pimmelberger!')
schwarzcolor = 30
schwarz = 35
speedleft = 0
speedright = 0
speedmid = 0
basetime = 0.1
normalspeed = 75
turnlow = -5
maxspeed = 100
increment_of_increment = normalspeed/8
listenlänge = 5
wandabstand = 20
torabstand = 10
kurvengeschwindigkeit = 30
radkoeffizient = 17.7/9.7
# leds.set_color("LEFT", "GREEN")
# leds.set_color("RIGHT", "GREEN")
# while True:
#     leftlight = ls1.reflected_light_intensity
#     rightlight = ls2.reflected_light_intensity
#     midlight = ls3.reflected_light_intensity
#     # if leftlight < schwarz:
#     #     leds.set_color("LEFT", "RED")
#     # if rightlight < schwarz:
#     #     leds.set_color("RIGHT", "RED")
#     if midlight < schwarzcolor:
#         leds.set_color("RIGHT", "RED")
#         leds.set_color("LEFT", "RED")
    
def run():
    global speedleft, speedright, speedmid
    left_motor.run_direct()
    right_motor.run_direct()
    mid_motor.run_direct()
    geradendurchlauf = 1
    speedincrement = kurvengeschwindigkeit
    turned_right = 0
    turned_left = 0
    while True:
        
        leftlight = ls1.reflected_light_intensity
        rightlight = ls2.reflected_light_intensity
        midlight = ls3.reflected_light_intensity
        abstand = us.distance_centimeters
        if midlight	> schwarzcolor and abstand < wandabstand:
            start_turn()
        elif midlight < schwarzcolor and abstand < torabstand:
            left_motor.duty_cycle_sp = 0
            right_motor.duty_cycle_sp = 0
            mid_motor.duty_cycle_sp = 0
            while True:
                abstand = us.distance_centimeters
                if abstand > torabstand+1:
                    break
        elif midlight < schwarzcolor and (leftlight > schwarz and rightlight > schwarz):
            speedleft = normalspeed
            speedright = normalspeed
            speedmid = normalspeed*radkoeffizient
            speedincrement = kurvengeschwindigkeit
            turned_left = 0
            turned_right = 0
            if speedmid > 100:
                speedmid = 100
        elif leftlight > schwarz and rightlight < schwarz:
            speedleft = speedincrement
            speedright = normalspeed - speedincrement
            speedmid = speedincrement/2
            if speedleft > normalspeed:
                speedleft = normalspeed
            if speedright < - normalspeed:
                speedright = - normalspeed
            if speedmid > normalspeed/2:
                speedmid = normalspeed/2
            speedincrement += increment_of_increment
            turned_right += 1
        elif  leftlight < schwarz and rightlight > schwarz:
            speedleft = normalspeed - speedincrement
            speedright = speedincrement
            speedmid = speedincrement/2
            if speedright > normalspeed:
                speedright = normalspeed
            if speedleft < - normalspeed:
                speedleft = - normalspeed
            if speedmid > normalspeed/2:
                speedmid = normalspeed/2
            speedincrement += increment_of_increment
            turned_left += 1
        elif midlight > schwarzcolor and (leftlight > schwarz and rightlight > schwarz):
            speedleft = normalspeed
            speedright = normalspeed
            speedmid = normalspeed*radkoeffizient
            if speedmid > 100:
                speedmid = 100
        # if (leftlight < schwarz or rightlight < schwarz) and abstand < torabstand:
        #     left_motor.duty_cycle_sp = 0
        #     right_motor.duty_cycle_sp = 0
        #     while True:
        #         abstand = us.distance_centimeters
        #         if abstand > torabstand+1:
        #             break
        # elif leftlight < schwarz and rightlight < schwarz and abstand > torabstand:
        #     speed1 = (normalspeed*2 + normalspeed/geradendurchlauf*8) / 10
        #     speed2 = (normalspeed*2 + normalspeed/geradendurchlauf*8) / 10
        #     speedincrement = kurvengeschwindigkeit
        #     if geradendurchlauf > 1:
        #         geradendurchlauf -= 1
        #     turned_left = 0
        #     turned_right = 0
        # elif leftlight < schwarz and rightlight > schwarz:
        #     geradendurchlauf = 30
        #     speed1 = turnlow
        #     speed2 = speedincrement
        #     if speed2 > 100:
        #         speed2 = maxspeed
        #     speedincrement += increment_of_increment
        #     turned_left += 1
        # elif leftlight > schwarz and rightlight < schwarz:
        #     geradendurchlauf = 30
        #     speed1 =  speedincrement
        #     speed2 = turnlow
        #     if speed1 > 100:
        #         speed1 = maxspeed
        #     speedincrement += increment_of_increment
        #     turned_right += 1
        # elif leftlight > schwarz and rightlight > schwarz and abstand < wandabstand:
        #     start_turn()
        # else:
        #     search_direction()

        left_motor.duty_cycle_sp = speedleft
        right_motor.duty_cycle_sp = speedright
        mid_motor.duty_cycle_sp = - speedmid

        time.sleep(0.001)
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
    mid_motor.duty_cycle_sp = 0
    if normalspeed == 50:
        time.sleep(basetime*20) # 20 bei 50 speed, 12 bei 75
    elif normalspeed == 75:
        time.sleep(basetime*12)
    left_motor.duty_cycle_sp = normalspeed
    right_motor.duty_cycle_sp = normalspeed
    mid_motor.duty_cycle_sp = normalspeed*radkoeffizient

    if speedmid > 100:
        speedmid = 100

    while True:
        midlight = ls3.reflected_light_intensity

        if midlight < schwarz:
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