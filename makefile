all: assign4sem_exe assign4mon_exe

server: server.c
	gcc -o assign4sem_exe Assign4_sem.c -lrt

client: client.c
	gcc -o assign4mon_exe Assign4_mon.c -lrt
