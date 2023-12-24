#ifndef ROBO_H
#define ROBO_H

#include <mutex>

const int altura = 400; //altura da sala em cm
const int largura = 300; //largura da sala em cm

class Robo
{
private:

    std::mutex *mut =new std::mutex();
    /*Posição (x,y) atual*/
    unsigned int posX; 
    unsigned int posY;

    /*Posição (x,y) anterior*/
    unsigned int posXOld;
    unsigned int posYOld;

    unsigned int sourceTime; //Tempo de mudança da fonte

    char id;
    unsigned int getX(){return posX;}
    unsigned int getY(){return posY;}
    unsigned int getXOld(){return posXOld;}
    unsigned int getYOld(){return posYOld;}
    void setTime(unsigned long);
    unsigned long getSourceTime(){return sourceTime;}
    void move();
public:
    Robo();
    Robo(char);
    
    void insertData(unsigned int) ;
    void readData(unsigned int &,unsigned int &,unsigned int &,unsigned int &,double &);
    void getInfo();
    char getId(){return id;}

};

#endif // 




