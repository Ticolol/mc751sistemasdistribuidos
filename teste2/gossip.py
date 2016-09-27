from socket import *
import thread
import threading
import time
import random
import string
import sys
import math


BUFF = 1024

globalSuccs = 0
globalFails = 0
globalMin = -1
globalMax = 0


def fofocate(data,x,minPort,N, k):
	global globalSuccs
	global globalFails
	global globalMin
	global globalMax
	succs = 0
	fails = 0
	print 'Fofocation for process number ' + `x` + ' started!\n'
	while 1:
		port = random.randint(minPort, minPort+N-1)
		addr = ('localhost', port)
		csock = socket(AF_INET, SOCK_STREAM)
		csock.connect(addr)
		csock.send(data)
		rsp = csock.recv(BUFF)
		if rsp == 'Nothing new':
			fails+=1
			if random.randint(1,k)==k:
				#terminate fofocation process
				print 'Fofocation ' + `x` + ' terminated. Succs: ' + `succs` + '; Fails: ' + `fails` + '\n'
				globalSuccs += succs
				globalFails += fails
				soma = succs + fails
				if soma > globalMax:
					globalMax = soma
				if soma < globalMin or globalMin == -1:
					globalMin = soma
				csock.close()
				exit()
		else:
			succs+=1
		sys.stdout.flush()	


def handler(x,minPort, N, k):
	print('Started process number ' + `x`)
	data = '0'
	saddr = ('localhost', minPort+x)
	nclients = 10
	# Create server
	ssock = socket(AF_INET, SOCK_STREAM)
	ssock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)#Allows reuse of port
	ssock.bind(saddr)
	ssock.listen(nclients)
	while 1:
		csock, addr = ssock.accept()
		rcvdata = csock.recv(BUFF)
		if rcvdata == data :
			#meeeeehhh
			#print 'meeeeehhh'
			csock.send('Nothing new')
		else:
			#neeeewww
			#print 'neeeewww'
			data = rcvdata
			thread.start_new_thread(fofocate, (data,x,minPort, N, k))
			csock.send('NEW')
			csock.close()
		pass
	ssock.close()
	sys.stdout.flush()



if __name__=='__main__':
	global globalSuccs
	global globalFails
	global globalMin
	global globalMax
	N = int(sys.argv[1])
	k = int(sys.argv[2])
	minPort = 31000
	#Create N process
	for x in range(0,N):
		print('Created process number ' + `x`)
		thread.start_new_thread(handler,(x, minPort, N, k))
	#Insert info into first process	
	time.sleep(2)
	print('=== STARTING EXPERIMENT ===')
	csock = socket(AF_INET, SOCK_STREAM)
	csock.connect(('localhost',minPort))
	csock.send('1')
	csock.close()
	while raw_input()!="c":
		pass
	print('=== RESULTS ===')
	globalSuccs+=1
	globalAver=(globalSuccs+globalFails)/N
	print('Processos alcancadas: ' + `globalSuccs` + '/' + `N`)
	print('Indice de fofocas bem sucedidas: ' + `float(float(globalSuccs)/float(globalSuccs + globalFails))`)
	print('Minimo: ' + `globalMin` + '; Maximo: ' + `globalMax` + '; Media: ' + `globalAver`)
	

