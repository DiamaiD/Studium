#!/usr/bin/python3

fahrenheit = float(input("Geben sie, für die Umrechnung in Celsius, die Temperatur\n\
in Fahrenheit als Fließkommazahl ein: "))

print("Fahrenheit: ", fahrenheit)
print("Celsius: ", round((fahrenheit-32)*5/9, 2))
