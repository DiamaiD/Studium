
def leap(year: int) -> bool:
    if year < 1583:
        print("Year musst be greater than 1582")
        return None
    if year % 400 == 0:
        return True
    elif year % 100 == 0:
        return False
    elif year % 4 == 0:
        return True
    else:
        return False