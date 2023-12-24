#include "Buffer.h"

Buffer::Buffer(unsigned int TAM):tam(TAM){}

void Buffer::sourceData(Robo boot) {
    mut.lock();
    if(robotData.size()<=tam)
    robotData.push_back(boot);
    mut.unlock();
}

int Buffer::getBufferSize(){
    mut.lock();
    size_t s = robotData.size();
    mut.unlock();
    return s;
}

float Buffer::getRobotVelocity(char robotId){

    unsigned int sumPosX = 0;
    unsigned int sumPosY = 0;

    unsigned int sumPosXOld = 0;
    unsigned int sumPosYOld = 0;

    double sumTempo = 0;
    
    mut.lock();
    for (size_t i = 0; i < robotData.size(); i++)
    {
        if(robotData[i].getId()==robotId){
            robotData[i].readData(sumPosX,sumPosY,sumPosXOld,sumPosYOld,sumTempo);
            robotData.erase(robotData.begin()+i);
        }
    }
    
    mut.unlock();
    //sumTempo /= 1000.0;
    /*Cálculo da velocidade a partir dos dados coletados do robô escolhido */
    float velocidade = (sumTempo!=0)? (sqrt(pow((sumPosX-sumPosXOld),2)+pow((sumPosY-sumPosYOld),2))/sumTempo):0 ; 
    velocidade *=10;
    return velocidade;
}
