#include "Fonte.h"

Fonte::Fonte(unsigned long time_S, std::string name):time(time_S),tipo(name){}

unsigned long Fonte::getTime(){return this->time;}

void Fonte::setTime(int time){
    this->time=time;
}

void Fonte::getRobotsPosition(std::vector<Robo> robos,int n, Buffer &buffer){
    
    
    while (1)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(getTime()));
        for (size_t i = 0; i < n; i++)
        {
            
            robos[i].insertData(getTime());       // robô muda de posição
            buffer.sourceData(robos[i]);//peda o tempo da fonte para ser salvo na esturtura do robo
                                        //insere dados no buffer   
        }

        this->setTime(randMin+rand()%(randMax-randMin));
    }
    
    
}

