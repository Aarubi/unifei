#include "Robo.h"
#include <iostream>

Robo::Robo():id(0),posX(0),posY(0){}

Robo::Robo(char robot_id):id(robot_id),posX(rand()%altura),posY(rand()%largura){}

void Robo::setTime(unsigned long sourceTime){this->sourceTime=sourceTime;}

void Robo::move(){

    this->posXOld=this->posX;
    this->posYOld=this->posY;

    int32_t deslX = this->posX + (rand()%21)-10;
    int32_t deslY = this->posY + (rand()%21)-10;
    
    
    if(deslX<0){
        this->posX=0;
    }else if(deslX>largura){
        this->posX=largura;
    }else{
        this->posX=deslX;
    }

    if(deslY<0){
        this->posY=0;
    }else if(deslY>altura){
        this->posY=altura;
    }else{
        this->posY=deslY;
    }

}

void Robo::insertData(unsigned int time) {
    mut->lock();
    this->move();
    this->setTime(time);
    mut->unlock();
}

void Robo::readData(unsigned int &x,unsigned int &y,unsigned int &oldX, unsigned int &oldY, double &time) {

    mut->lock();
    x += getX();
    y += getY();
    oldX += getXOld();
    oldY += getYOld();
    time += getSourceTime();
    mut->unlock();
}

void Robo::getInfo(){
    std::cout<<getId()<<": ("<<getX()<<","<<getY()<<")"<<std::endl;
}