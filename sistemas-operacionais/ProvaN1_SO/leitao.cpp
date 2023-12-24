/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>


//modelo com semaphoros, adaptar pro nosso codigo (nao sei como vc implementou a classe Semaforo)
#define N 100
typedef int semaphore;
semaphore mutex = 1;
semaphore empty = N;
semaphore full = 0;

void producer (void)
{
  int item;
  while (TRUE)
    {
      produce_item (&item);
      down (&empty);
      down (&mutex);
      enter_item (item);
      up (&mutex);
      up (&full);
    }
}

void consumer (void)
{
  int item;
  while (TRUE)
    {
      down (&full);
      down (&mutex);
      remove_item (item);
      up (&mutex);
      up (&empty);
      consume_item (item);
    }
}


class Semaphore {

    std::condition_variable cv;
    std::mutex mtx;
    int value;

public:

    int up() {
        std::lock_guard<std::mutex> lock(mtx);
        if (++value > 0)
            cv.notify_one();
        return value;
    }

    int down() {
        std::unique_lock<std::mutex> lock(mtx);
        while (value <= 0) {
            cv.wait(lock);
        }
        if (--value > 0) {
            cv.notify_one();
        }
        return value;
    }
};