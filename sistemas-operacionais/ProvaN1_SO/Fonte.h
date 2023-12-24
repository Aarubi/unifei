#include <iostream>
#include <thread>
#include <vector>
#include <ctime>
#include <mutex>
#include <map>
#include <unistd.h>
#include "Robo.h"
#include "Buffer.h"
#include <chrono>

const int randMax = 4000; //Determina tempo máximo em ms
const int randMin = 100; //Determina tempo mínima em ms

class Fonte
{
private:
    std::string tipo; //tipo (nome) da fonte
    unsigned long time; //tempo da fonte
    
public:
    Fonte();
    Fonte(unsigned long,std::string);
    unsigned long getTime();
    void getRobotsPosition(std::vector<Robo>,int ,Buffer &); //captura posições do robo
    void setTime(int);
    std::string getTitle(){return tipo;}
};
// std::map<char,Robo>