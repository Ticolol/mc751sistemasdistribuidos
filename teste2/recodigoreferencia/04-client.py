from socket import *

if __name__=='__main__':
	ADDR = ('localhost', 8888)
	clientsock = socket(AF_INET, SOCK_STREAM)
	clientsock.connect(ADDR)
	clientsock.send("What's up doc")
	data = clientsock.recv(1024)
	print "Servidor disse: " + data
	clientsock.close()
