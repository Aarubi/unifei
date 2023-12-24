/*
Alunos: 
Gabriel Arthur Teixeira Perpétuo - 2018006170
Arthur Leitão Barbosa - 2018010520
*/

#include <thread>
#include <vector>
#include <ctime>
#include <mutex>
#include <map>
#include <unistd.h>
#include <iomanip>
#include "Robo.h" // Estrutura do Robo
#include "Fonte.h" //Estrutura da Fonte
#include "Buffer.h" //Estrutura do Buffer
#include "Historico.h" //Estrutura do Histórico de Velocidades de cada Robô

int main()
{
    srand(time(0));

    std::mutex mutSource;   //Declara mutex compartilhado para as threads Source
    
    std::vector <Robo> robos{'A','B','C'};  //Inicializa robôs com identificadores (id's)

    /*Determina tempos de cada fonte de forma aleatória*/
    int time1 = randMin+rand()%(randMax-randMin);
    int time2 = randMin+rand()%(randMax-randMin);
    int time3 = randMin+rand()%(randMax-randMin);

    /*'Seta' tempos de cada fonte com respectivo nome */
    Fonte *s1 = new Fonte(time1,"gps");
    Fonte *s2 = new Fonte(time2,"odometro");
    Fonte *s3 = new Fonte(time3,"camera");
    
    /*Cria estrutura de histórico para cada robô*/
    Historico h1(robos[0].getId(),5);
    Historico h2(robos[1].getId(),5);
    Historico h3(robos[2].getId(),5);
    
    /*Exibe tempo em que cada fonte vai operar*/
    std::cout<<"Tempo da fonte "<<s1->getTitle()<<": "<<time1<<std::endl;
    std::cout<<"Tempo da fonte "<<s2->getTitle()<<": "<<time2<<std::endl;
    std::cout<<"Tempo da fonte "<<s3->getTitle()<<": "<<time3<<std::endl;

    /*Usuario insere tamanho máximo do buffer*/
    unsigned int N;
    std::cout<<"Insira o tamanho do Buffer: ";
    std::cin>>N;

    Buffer buffer(N); //Declara buffer

    /*Declara threads em que cada fonte vai operar*/
    std::thread thr_source1(&Fonte::getRobotsPosition,std::ref(s1),robos,robos.size(),std::ref(buffer));
    std::thread thr_source2(&Fonte::getRobotsPosition,std::ref(s2),robos,robos.size(),std::ref(buffer));
    std::thread thr_source3(&Fonte::getRobotsPosition,std::ref(s3),robos,robos.size(),std::ref(buffer));


    /*Laço onde bufer retorna valores que retirou das threads*/
    while (1)
    {   
        
        float v1 = buffer.getRobotVelocity(robos[0].getId());
        float v2 = buffer.getRobotVelocity(robos[1].getId());
        float v3 = buffer.getRobotVelocity(robos[2].getId());

        /*Parte Gŕafica*/
        system("clear");

        /*Exibe ultima velocidade retirada*/
        std::cout<< "Velocidade "<<robos[0].getId()<<": "<< std::setprecision(3)<<v1<<" cm/ms "<<std::endl;
        std::cout<< "Velocidade "<<robos[1].getId()<<": "<< std::setprecision(3)<<v2<<" cm/ms "<<std::endl;
        std::cout<< "Velocidade "<<robos[2].getId()<<": "<< std::setprecision(3)<<v3<<" cm/ms "<<std::endl;
        std::cout<<"Buffsize:"<<buffer.getBufferSize() <<std::endl;

        std::mutex mutHistoric; //Declara mutex compartilhado para as threads Historic
        std::thread thr_historic1(&Historico::historicoFunction,std::ref(h1),std::ref(mutHistoric),v1);
        std::thread thr_historic2(&Historico::historicoFunction,std::ref(h2),std::ref(mutHistoric),v2);
        std::thread thr_historic3(&Historico::historicoFunction,std::ref(h3),std::ref(mutHistoric),v3);

        thr_historic1.join();
        thr_historic2.join();
        thr_historic3.join();
        
        sleep(2); // tempo de refresh
    }
    
    return 0;
}
