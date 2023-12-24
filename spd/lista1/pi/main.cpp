//calculo de pi utilizando pthreads
#include <pthread.h>
#include <chrono>
#include <iostream>
#include <cmath>
#include <iomanip>

int main()
{
    long long num_steps = 100000000;
    long double step,i;
    long double x, pi, sum = 0.0;

    std::cout<<"Calculando pi para "<< num_steps <<" passos..."<<std::endl;
    auto t1 = std::chrono::high_resolution_clock::now();
    step = 1.0/(long double)num_steps;
    for(i = 0.0; i < num_steps; i++) {
        x = (i + 0.5) * step;
        sum += 4.0/(1.0 + x*x);
    }
    pi = step * sum;
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << "\n Valor aproximado = " << std::setprecision(50) << pi;
    std::cout << "\n Tempo de execução = " << duration << "ms\n";
    return 0;

}