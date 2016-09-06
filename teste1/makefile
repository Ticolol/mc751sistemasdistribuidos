

	#@echo MY_VAR IS $(MY_VAR)
	#@echo 'Start execution'
	#@echo -n 'seq: result = '

	#$(eval MYSEQ=$(time --format='   time = %e seconds' ./seq 64))

run:
	@echo 'Compiling...'
	@gcc -lm seq.c -o seq
	@gcc -lm -lpthread thread.c -o thread
	@gcc -lm -lrt process.c -o process
	@echo 'Start execution'
	@echo -n 'seq:     result = ' && time --format='   time = %e seconds' ./seq 64
	@echo -n 'thread:  result = ' && time --format='   time = %e seconds' ./thread 64 8
	@echo -n 'process: result = ' && time --format='   time = %e seconds' ./process 64 8
	@echo 'Finished!'


