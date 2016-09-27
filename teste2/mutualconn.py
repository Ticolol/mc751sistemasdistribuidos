from socket import *
import thread
import threading
import time
import random
import string
import sys

BUFF = 1024

def runClient(taddr, data):
	time.sleep(1)
	csock = socket(AF_INET, SOCK_STREAM)
	csock.connect(taddr)
	csock.send(data)
	check = csock.recv(BUFF)
	print(check)
	csock.close()

def connectTwins(myId,myPort,twinPort):
	data = "I came from server " + `myId` 
	# Create address infos
	shost = 'localhost'
	sport = myPort
	saddr = (shost, sport)
	nclients = 10
	thost = 'localhost'
	tport = twinPort
	taddr = (thost, tport)
	print("Server " + `myId` + "-> sending message: " + data)
	# Create server
	ssock = socket(AF_INET, SOCK_STREAM)
	ssock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)#Allows reuse of port
	ssock.bind(saddr)
	ssock.listen(nclients)
	# Run client
	thread.start_new_thread(runClient, (taddr, data))#threadfy
	# Listen to client
	while 1:
		csock, addr = ssock.accept()
		rcvdata = csock.recv(BUFF)
		print("Server " + `myId` + "-> received message: " + rcvdata)
		csock.send('Thanks from server ' + `myId`)
		csock.close()
	ssock.close()



if __name__=='__main__':
	print('started')
	thread.start_new_thread(connectTwins, (1, int(sys.argv[1]), int(sys.argv[2])))
	thread.start_new_thread(connectTwins, (2, int(sys.argv[2]), int(sys.argv[1])))
	print('ended')
	time.sleep(3)

"""
host = 'localhost'
port = int(sys.argv[1])
addr = (host, port)
print(sys.argv[1])
nclients = 10
s = socket(AF_INET, SOCK_STREAM)
s.bind(addr)
s.listen(nclients)
conn, addr = s.accept()
while 1:
	data = conn.recv(1024)
	if not data: 
		break
	conn.send(data)
conn.close()
"""
