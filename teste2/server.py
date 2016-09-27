from socket import *
import thread
import time
import random
import string
import sys

if __name__=='__main__':
	host = ''
	port = 1122
	nclients = 10
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.bind((host, port))
	s.listen(nclients)
	conn, addr = s.accept()
	while 1:
		data = conn.recv(1024)
		if not data: 
			break
		conn.send(data)
	conn.close()
