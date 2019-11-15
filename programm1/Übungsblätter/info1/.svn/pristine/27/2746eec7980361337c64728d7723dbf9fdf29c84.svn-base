#!/usr/bin/python3

def lineargrade(p: float) -> float:
    if p <= 12:
        return 6.0
    elif p >= 57:
        return 1.0
    else:
        note = ((-5/45)*(p-57)+1)
        if note % 1 >= 0.25 and note % 1 < 0.75:
            return (int(note) + 0.5)
        elif note % 1 >= 0.75:
            return (int(note) + 1.0)
        else:
            return float(int(note))

def passed(p: float) -> bool:
    if lineargrade(p) <= 4.0:
        return True
    else:
        return False

def mark(grade: float) -> str:
    if grade <= 6.0:
        return "F"
    elif grade >= 5.0:
        return "E"
    elif grade >= 4.0:
        return "D"
    elif grade >= 3.0:
        return "C"
    elif grade >= 2.0:
        return "B"
    else:
        return "A"

p = float(input("Geben sie die Punktzahl ein: "))
if p < 0:
    print("Sie haben negative Punkte eingegeben!")
    quit()

note = lineargrade(p)

print ("Erreichte Note:",note)

if passed(p) == True:
    print("==> Bestanden!")
else:
    print("==> nicht Bestanden!")
