#ifndef BUFFER_H
#define BUFFER_H
#include "Robo.h"
#include <cmath>
#include <vector>
#include <mutex>

class Buffer
{
private:
    std::mutex mut;
    unsigned int tam; // tamanho maximo do buffer definido pelo usuário
    std::vector<Robo> robotData;
public:
    Buffer();
    Buffer(unsigned int);
    int getBufferSize();
    void sourceData(Robo);
    float getRobotVelocity(char); //retorna velocidade de robo especificado
};

#endif