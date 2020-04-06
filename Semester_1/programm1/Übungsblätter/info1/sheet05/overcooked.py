#!/usr/bin/python3

recipes = [("Daiquiri", ["Rum", "Limette", "Zucker"]),
    ("Mojito", ["Rum", "Limette", "Zucker", "Minze", "Soda"]),
    ("Whiskey Sour", ["Whiskey", "Zitrone", "Zucker"]),
    ("Tequila Sour", ["Tequila", "Zitrone", "Zucker"]),
    ("Moscow Mule", ["Vodka", "Limette", "Ginger ale"]),
    ("Munich Mule", ["Gin", "Limette", "Ginger ale"]),
    ("Cuba Libre", ["Rum", "Coke"])]

def mixable(xs: list) -> list:
    """ Überprüfen ob die vorhandenen Zutat für bestimmte Cocktails ausreichen
    """
    cocktail_possible = []
    for cocktail in recipes:
        notin = 0
        for incredient in cocktail[1]:
            if incredient not in xs:
                notin += 1
                break
        if notin == 0:
            cocktail_possible.append(cocktail[0])
    return cocktail_possible
