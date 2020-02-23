#!/usr/bin/python3

from ev3dev2.sensor import *
from ev3dev2.motor import *
from ev3dev2.sensor.lego import *
from ev3dev2.led import Leds
from ev3dev2.sound import Sound
import time

ls1 = LightSensor(INPUT_4) # links
ls2 = LightSensor(INPUT_1) # rechts
ls3 = ColorSensor(INPUT_2) # mitte
leds = Leds()
us = UltrasonicSensor()
# tank_drive = MoveTank(OUTPUT_A, OUTPUT_B)
left_motor = LargeMotor(OUTPUT_D)
right_motor = LargeMotor(OUTPUT_A)
mid_motor = LargeMotor(OUTPUT_C)

# from ev3dev2.sound import Sound
sound = Sound()
# sound.speak('Hallo ich bin Roberto ihr Pimmelberger!')
schwarzcolor = 40
schwarz = 35
speedleft = 0
speedright = 0
speedmid = 0
basetime = 0.1
defaultspeed = 75
normalspeed = defaultspeed
turnlow = -5
maxspeed = 100
increment_of_increment = normalspeed/12 # alt 8
listenlänge = 5
wandabstand = 20
torabstand = 10
kurvengeschwindigkeit = 50 # alt 30
radkoeffizient = 16.7/9.7 # alt 16.7/9.7
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
    lichtwerte = []
    aenderungen = 0

    

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
            # speedleft = normalspeed
            # speedright = normalspeed
            # if normalspeed*radkoeffizient > 100:
            #     speedmid = 100
            # else:
            #     speedmid = normalspeed*radkoeffizient
            # oldmid = 0
            # mid = 0
            # for i in range(40):
            #     midlight = ls3.reflected_light_intensity
            #     oldmid = mid
            #     if midlight < schwarzcolor:
            #         mid = 1
            #     else:
            #         mid = 0
            #     if oldmid != mid:
            #         aenderungen += 1
            #     time.sleep(0.001)

            left_motor.duty_cycle_sp = 0
            right_motor.duty_cycle_sp = 0
            mid_motor.duty_cycle_sp = 0
            time.sleep(60)
            
            # if aenderungen >= 3:
            #    klotz()
                
                
            

        left_motor.duty_cycle_sp = speedleft
        right_motor.duty_cycle_sp = speedright
        mid_motor.duty_cycle_sp = speedmid

        time.sleep(0.001)
        # if turned_right >= 1 or turned_left >= 1:
        #     left_motor.duty_cycle_sp = 0
        #     right_motor.duty_cycle_sp = 0

def turn(drehung=180):
    if drehung == 90:
        koeff = 2
    elif drehung == 180:
        koeff = 1
    left_motor.duty_cycle_sp = normalspeed
    right_motor.duty_cycle_sp = - normalspeed
    mid_motor.duty_cycle_sp = 0
    global speedleft, speedright, speedmid
    if normalspeed == 50:
        time.sleep(basetime*15/koeff) # 11 bei 50 speed, 6.5 bei 75
    elif normalspeed == 75:
        time.sleep(basetime*6.3/koeff)

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
        

        
def klotz():
    turn(90)
    speedincrement = kurvengeschwindigkeit
    turned_right = 0
    turned_left = 0

    left_motor.duty_cycle_sp = normalspeed
    right_motor.duty_cycle_sp = normalspeed
    if normalspeed*radkoeffizient > 100:
        mid_motor.duty_cycle_sp = 100
    else:
        mid_motor.duty_cycle_sp = normalspeed*radkoeffizient

    time.sleep(basetime*5)

    while True:

        leftlight = ls1.reflected_light_intensity
        rightlight = ls2.reflected_light_intensity
        midlight = ls3.reflected_light_intensity
        abstand = us.distance_centimeters

        if abstand < 20:
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

        left_motor.duty_cycle_sp = speedleft
        right_motor.duty_cycle_sp = speedright
        mid_motor.duty_cycle_sp = - speedmid
    
    left_motor.duty_cycle_sp = normalspeed
    right_motor.duty_cycle_sp = normalspeed
    if normalspeed*radkoeffizient > 100:
        mid_motor.duty_cycle_sp = 100
    else:
        mid_motor.duty_cycle_sp = normalspeed*radkoeffizient

    while True:
        abstand = us.distance_centimeters
        if abstand > 20:
            break
        time.sleep(basetime)
    
    left_motor.duty_cycle_sp = - normalspeed
    right_motor.duty_cycle_sp = - normalspeed
    if normalspeed*radkoeffizient > 100:
        mid_motor.duty_cycle_sp = 100
    else:
        mid_motor.duty_cycle_sp = normalspeed*radkoeffizient

    time.sleep(basetime*10)
    while True:
        midlight = ls3.reflected_light_intensity
        if midlight < schwarzcolor:
            time.sleep(basetime)
            midlight = ls3.reflected_light_intensity
            if midlight < schwarzcolor:
                break
    
    time.sleep(basetime*6)

    left_motor.duty_cycle_sp = - normalspeed
    right_motor.duty_cycle_sp = normalspeed
    mid_motor.duty_cycle_sp = 15
    
    time.sleep(basetime*6)

    left_motor.duty_cycle_sp = normalspeed
    right_motor.duty_cycle_sp = normalspeed
    if normalspeed*radkoeffizient > 100:
        mid_motor.duty_cycle_sp = 100
    else:
        mid_motor.duty_cycle_sp = normalspeed*radkoeffizient

    time.sleep(basetime*3)

    
    

    

run()