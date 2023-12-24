#include "Historico.h"

Historico::Historico(char id,int tam):roboId(id),size(tam){}

void Historico::insertVelocidade(float data){

    if(estrutura.size()>=size){
        estrutura.pop_back();
    }
    estrutura.push_front(data);
}

void Historico::print(){
    std::cout<<"Historico do robo "<<roboId<<" :";
    for (auto i = estrutura.begin(); i != estrutura.end(); i++)
    {
        std::cout<<"|"<<(*i)<<"| ";
    }
    std::cout<<std::endl;
    
}

void Historico::historicoFunction(std::mutex &mut,float v){
    mut.lock();
    /*Armazaena no histórico*/
    this->insertVelocidade(v);
    /*Exibe dados armazenado no histórico*/
    this->print();
    mut.unlock();
}
