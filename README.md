# Assignment 4: FCFS Reader/Writer PROGRAMMING 

## Partners

Michael Walker and Kaden Grabenstein

## How to Compile
1. Use "make" to compile both the semaphore and monitor solution.
2. ./assign4sem_exe input to run semaphore solution
3. ./assign4mon_exe input to run monitor solution

## Semaphore Solution Pseudocode
reader{<br/>
  wait(reader)<br/>
  if there are readers then wait(writer)<br/>
  sleep()<br/>
  if there are no more readers then post(writer)<br/>
  post(reader)<br/>
}<br/>

writer{<br/>
  wait(writer)<br/>
  sleep()<br/>
  post(writer)<br/>
  return<br/>
}<br/>
main{<br/>
initialize semaphores reader and writer<br/>
iterate through and create threads based on input<br/>
}


## Monitor Solution Pseudocode


