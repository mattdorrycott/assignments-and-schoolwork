from sense_hat import SenseHat, ACTION_PRESSED, ACTION_HELD, ACTION_RELEASED
from time import sleep

sense = SenseHat()

r = [255, 0, 0]
g = [0, 255, 0]
b = [0, 0, 255]
y = [255, 255, 0]
p = [255, 105, 180]
v = [143, 0, 255]
o = [255, 165, 0]
i = [75, 0, 130]
E = [0, 0, 0]

colors = [r,o,y,g,b,i,v,p]

while True:
    for a in range(0,8):
        for b in range(0,a+1):
            c = a-b
            color = colors[a]
            sense.set_pixel(c,b,color)
        sleep(.1)
        sense.clear()
    for a in range(6, -1, -1):
        for b in range(0,a+1):
            c = a-b
            color = colors[a]
            sense.set_pixel(8-b-1,8-c-1, color)
        sleep(.1)
        sense.clear()