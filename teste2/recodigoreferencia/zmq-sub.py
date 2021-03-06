import sys
import zmq

# Subscribe to zipcode, default is NYC, 10001
topicfilter = "10001"

# Socket to talk to server
context = zmq.Context()
socket = context.socket(zmq.SUB)


print "Collecting updates from weather server..."
socket.connect ("tcp://localhost:5558")

socket.setsockopt(zmq.SUBSCRIBE, topicfilter)



# Process 5 updates
total_value = 0
for update_nbr in range (5):
    string = socket.recv()
    topic, messagedata = string.split()
    total_value += int(messagedata)
    print topic, messagedata

print "Average messagedata value for topic '%s' was %dF" % (topicfilter, total_value / update_nbr)
