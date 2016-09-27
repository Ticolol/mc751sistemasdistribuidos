import zmq
import random
import sys
import time

context = zmq.Context()
socket = context.socket(zmq.PUB)
socket.bind("tcp://*:5558")

time.sleep(1)


while True:
    topic = random.randrange(9999,10005)
    messagedata = random.randrange(12, 36)
    print "%d %d" % (topic, messagedata)
    socket.send("%d %d" % (topic, messagedata))
    time.sleep(1)
