#!/usr/bin/python3

def fahrenheit_to_celsius(fahrenheit):
    return ((fahrenheit-32)*5/9)

def celsius_to_kelvin(celsius):
    return (celsius+273.15)

def fahrenheit_to_kelvin(fahrenheit):
    return celsius_to_kelvin(fahrenheit_to_celsius(fahrenheit))

fahrenheit = float(input("Geben sie die Temperatur in Fahrenheit als\
Fließkommazahl ein: "))

print("Fahrenheit: ", fahrenheit)
print("Celsius: ", round(fahrenheit_to_celsius(fahrenheit), 2))
print("Kelvin: ", round(fahrenheit_to_kelvin(fahrenheit), 2))

