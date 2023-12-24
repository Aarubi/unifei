#include <list>
#include <iostream>
#include <mutex>

class Historico
{
private:
    char roboId;
    int size;
    std::list<float> estrutura;
public:
    Historico(char,int);
    void insertVelocidade(float);
    void print();
    void historicoFunction(std::mutex &mut,float v);
};

