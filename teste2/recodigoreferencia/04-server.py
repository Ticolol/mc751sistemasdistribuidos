from socket import *
import thread
import time
import random
import string
import sys

BUFF = 512

def response(key):
	return 'Falou, cliente otario\n'

def handler(clientsock,addr):
	print("Created")
	while 1:
		data = clientsock.recv(BUFF)
		if not data: break
		clientsock.send(response(data))
		print ( repr(addr) + " falou: " + repr(data) + "\n" )
	clientsock.close()
	print("Cliente " + repr(addr) + " terminou")
	sys.stdout.flush()

if __name__=='__main__':
	ADDR = ('localhost', 8888)
	serversock = socket(AF_INET, SOCK_STREAM)
	serversock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
	serversock.bind(ADDR)
	serversock.listen(5)
	while 1:
		clientsock, addr = serversock.accept()
		thread.start_new_thread(handler, (clientsock, addr))
