#!/usr/bin/python

class Ingredient():
    def __init__(self, name: str, preis: int, vegetarisch: bool):
        self.name = name
        self.preis = preis
        self.vegetarisch = vegetarisch


class Recipe():
    def __init__(self, name: str, zutaten: list):
        self.name = name
        self.zutaten = zutaten
    
def recipe_price(rezept: Recipe):
    total = 0
    for zutat in rezept.zutaten:
        total += zutat.preis
    return total

def is_veggi(rezept: Recipe):
    print(str(True))
    for zutat in rezept.zutaten:
        if not zutat.vegetarisch:
            return False
    return True

def recipe_str(rezept: Recipe):
    if len(rezept.zutaten) == 1:
        zutatenliste = rezept.zutaten[0].name
    elif len(rezept.zutaten) == 0:
        zutatenliste = "nothing"
    elif len(rezept.zutaten) == 2:
        zutatenliste = rezept.zutaten[0].name+" and "+rezept.zutaten[1].name
    else:
        zutatenliste = rezept.zutaten[0].name
        for zutat in rezept.zutaten[1:-1]:
            zutatenliste += ", "+zutat.name
        zutatenliste = zutatenliste+" and "+rezept.zutaten[-1].name

    if is_veggi(rezept):
        vege = "It is vegetarian"
    else:
        vege = "It is not vegetarian"

    return "A "+rezept.name+" has "+zutatenliste+". "+vege+\
        " and costs "+str(float(recipe_price(rezept))/100)+" Euro"