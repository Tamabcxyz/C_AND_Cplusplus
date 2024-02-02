/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <chrono>
#include <thread>
#include <semaphore>

using namespace std;
using namespace std::literals;
// global binary semaphore instances, object counts are set to zero, object are in non-signaled state
std::binary_semaphore smphSignalMainToThread{0}, smphSignalThreadToMain{0};

void ThreadProc(){
    //wait for a signal from the main process, by attempting to decrement the semaphore
    smphSignalMainToThread.acquire();
    
    //this call blocks until the semaphore's counts
    //is increased from the main process
    std::cout << "[thread] Got the signal\n"; //response message
    
    std::this_thread::sleep_for(3s);
    std::cout << "[thread] Send the signal\n"; //message
    
    //signal the main process back
    smphSignalThreadToMain.release();
}

int main()
{
    //create some worker thread
    std::thread thrWorker(ThreadProc);
    
    std::cout << "[main] Send the signal\n";
    
    //signal the worker thread to start working
    //increasing the semaphore's count
    smphSignalMainToThread.release();
    
    //wait until the worker thread is done doing the worker
    //decrement the semaphore's count
    smphSignalThreadToMain.acquire();
    
    std::cout << "[main] Got the signal\n";//response message
    thrWorker.join();

    return 0;
}