
def unique(xs: list) -> list:
    index = 0
    xss = []
    for i in xs:
        index += 1
        try:
            if i != xs[index]:
                xss.append(i)
        except:
            xss.append(i)
    return xss