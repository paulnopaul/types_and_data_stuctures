from random import *


def mgen(r, c):
    return [[randint(1, 100) if randint(0, 100) > 90 else 0
             for x in range(c)] for y in range(r)]


def mpr(r, c):
    for row in mgen(r, c):
        for elem in row:
            print(elem, end=" ")
        print()
    
r, c = 20, 20
print(r, c)
mpr(r, c)
print()
mpr(1, c)

