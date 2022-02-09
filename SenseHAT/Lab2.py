from sense_hat import SenseHat, ACTION_PRESSED, ACTION_HELD, ACTION_RELEASED
from time import sleep




sense = SenseHat()

r = [255, 0, 0] #red
g = [0, 255, 0] #green
b = [0, 0, 255] #blue
O = [255, 255, 255]  # White

smile = [
O, O, O, O, O, O, O, O,
O, O, O, O, O, O, O, O,
O, O, b, O, O, b, O, O,
O, O, O, O, O, O, O, O,
O, O, O, g, g, O, O, O,
O, r, O, O, O, O, r, O,
O, O, r, r, r, r, O, O,
O, O, O, O, O, O, O, O
]

sad = [
O, O, O, O, O, O, O, O,
O, O, O, O, O, O, O, O,
O, O, b, O, O, b, O, O,
O, O, O, O, O, O, O, O,
O, O, O, g, g, O, O, O,
O, O, O, O, O, O, O, O,
O, O, r, r, r, r, O, O,
O, r, O, O, O, O, r, O
]

event = None
while True:	
	if event == None: 
		sense.show_message("Hello!")
	event = sense.stick.wait_for_event()
	if event.action == "held" and event.direction == "up":
		sense.set_pixels(sad)
		sleep(1)
		sense.set_pixels(smile)
		sleep(1)
	elif event.action == "held" and event.direction == "down":
		pressure = round(sense.get_pressure())
		message = '%d Millibars' %(pressure)
		sense.show_message(message)
	elif event.action == "held" and event.direction == "right":
		temp = round(sense.get_temperature())
		message = '%d C' %(temp)
		sense.show_message(message)
	elif event.action == "held" and event.direction == "left":
		humidity = round(sense.get_humidity())
		message = '%d %%rh'%(humidity)
		sense.show_message(message)
	elif event.action == "held" and event.direction == "middle":
			sense.clear()
			quit()