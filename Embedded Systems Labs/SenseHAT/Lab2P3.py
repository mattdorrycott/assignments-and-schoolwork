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
    tilt = sense.get_accelerometer_raw()
    x = tilt['x']
    y = tilt['y']
    z = tilt['z']
    if(x > .3):
        for a in range(0,8):
            for b in range(0,8):
                color = colors[a]
                sense.set_pixel(a,b,color)
            sleep(.1)
            sense.clear()
    elif(x < -.3):
        for a in range(7,-1,-1):
            for b in range(0,8):
                color = colors[a]
                sense.set_pixel(a,b,color)
            sleep(.1)
            sense.clear()
    elif(y > .3):
        for a in range(0,8):
            for b in range(0,8):
                color = colors[a]
                sense.set_pixel(b,a,color)
            sleep(.1)
            sense.clear()
    elif(y < -.3):
        for a in range(7,-1,-1):
            for b in range(0,8):
                color = colors[a]
                sense.set_pixel(b,a,color)
            sleep(.1)
            sense.clear()
    elif(z > .5):
        sense.show_message("Lab 2 task 3", .06)
        sense.clear()
    elif(z < -.5):
        print("Lab 2 task 3")
        sleep(1)

        