#!/usr/bin/python3

def K(x):
    return x / 100

def M(k):
    return (15 + (3 * k + 3) / 4 - (8 * k + 13) / 25)

def S(k):
    return (3 - (3 * k + 3) / 4)

def A(x):
    return (x % 19)

def D(a,m):
    return ((19 * a + m) % 30)

def R(d,a):
    return((d + a / 11) / 29)

def OG(d,r):
    return (21 + d - r)

def SZ(x,s):
    return (7 - (x + x / 4 + s) % 7)

def OE(og,sz):
    return (7 - (og - sz) % 7)

def OS(og,oe):
    return (og + oe)

def easterdate(x):
    k = K(x)
    m = M(k)
    s = S(k)
    a = A(x)
    d = D(a,m)
    r = R(a,m)
    og = OG(d,r)
    sz = SZ(x,s)
    oe = OE(og,sz)
    return OS(og,oe)
try: 
    jahr = int(input("Geben sie das Jahr zur bestimmung des Osterdatums an: "))
except ValueError:
    print("Geben sie bitte ein Jahr als ganzzahl ein!")
    quit()
print(str(int(easterdate(jahr))) + ". März")
