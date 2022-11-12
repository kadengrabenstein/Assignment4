all: assign4sem_exe assign4mon_exe extrasem_exe extramon_exe

assign4sem_exe: Assign4_sem.c 
	gcc -o assign4sem_exe Assign4_sem.c -lrt -pthread

assign4mon_exe: Assign4_mon.c
	gcc -o assign4mon_exe Assign4_mon.c -lrt -pthread

extrasem_exe: Extra_sem.c
	gcc -o extrasem_exe Extra_sem.c -lrt -pthread

extramon_exe: Extra_mon.c
	gcc -o extramon_exe Extra_mon.c -lrt -pthread
