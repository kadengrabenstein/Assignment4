# Assignment 4: FCFS Reader/Writer PROGRAMMING 

## Partners

Michael Walker and Kaden Grabenstein

## How to Compile
1. Use "make" to compile both the semaphore and monitor solution.
2. ./assign4sem_exe input to run semaphore solution (input is 10 separate digits being either 1(writer) or 0(reader))
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

startRead() { <br/>
  check if there is a writer or waiting writer <br/>
  if true, then reader waits, otherwise reader reads <br/>
  calls end read function <br/>
}
endRead() { <br/>
  decrement the number of readers <br/>
  if last reader, then signal canWrite <br/>
}
startWrite() { <br/>
  lock mutex <br/>
  check if there is a writer or active readers <br/>
  if true, writer waits, otherwise writer writes <br/>
  calls end write function <br/>
}
endWrite() { <br/>
  unlock mutex <br/>
  if there are waiting readers, signal canRead <br/>
  otherwise signal canWrite <br/>
}
main{<br/>
initialize semaphores reader and writer<br/>
iterate through and create threads based on input<br/>
}