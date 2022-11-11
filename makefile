all: assign4sem_exe assign4mon_exe

assign4sem_exe: Assign4_sem.c 
	gcc -o assign4sem_exe Assign4_sem.c -lrt -pthread

assign4mon_exe: Assign4_mon.c
	gcc -o assign4mon_exe Assign4_mon.c -lrt -pthread
