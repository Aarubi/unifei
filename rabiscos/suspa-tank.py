import matplotlib
import matplotlib.pyplot as plt
import numpy as np




x1=0.15 #posição inicial da roda;
x2=0.4  #posição inicial do chassi;
posicao1=0
posicao2=0
velocidade1=0 #velocidade inicial da roda;
velocidade2=0 #velocidade inicial do chassi;
aceleracao1=0 #aceleração inicial da roda;
aceleracao2=0 #aceleração inicial do chassi;
M1=10 #massa da roda;
M2=75 #massa de 1/4 do chassi;
k1=51000 #constante de elasticidade do pneu;
k2=78800 #constante de elasticidade do amortecedor;
b=10000 #constante de amortecimento do amortecedor;
deslocamento1=0 #deslocamento inicial da roda;
deslocamento2=0 #deslocamento inicial do chassi;
u=0 #definindo a variável u;
theta=np.pi #definindo theta inicial;
dt=0.001 #incremento do tempo;
t=0 #tempo inicial
tempo=[] #vetor tempo inicial
r=0.4 #raio da lombada
vtheta= np.arange(180,0,dt) #vetor do angulo da lombada
vposicao1=[] #vetor posição da roda
vposicao2=[] #vetor posição do chassi

for t in np.arange(0,10, dt):

    if t < 1: # valor da posição constante até o tempo menor que 1
        posicao1=x1
        posicao2=x2


    elif t>=1 and theta>0 :#valores da função de entrada, variando o angulo theta

        x=[vtheta,t]#vetor de entrada
        u=np.sin(x)*r#função de entrada
        theta=theta-dt#incremento do angulo

        f1=((u*k1)+(k2*deslocamento2)+(b*velocidade2)-(b*velocidade1)-((k1+k2)*deslocamento1))
        f2=((k2*deslocamento1)+(b*velocidade1)-(k2*deslocamento2)-(b*velocidade2))

        aceleracao1=f1/M1 #atualização da aceleração da roda
        aceleracao2=f2/M2 #atualização da aceleração da roda

        deslocamento1=(deslocamento1+(velocidade1*dt)) #atualizações
        deslocamento2=(deslocamento2+(velocidade2*dt)) 

        velocidade1=velocidade1+(aceleracao1*dt)
        velocidade2=velocidade2+(aceleracao2*dt)

        posicao1=x1+(deslocamento1)
        posicao2=x2+(deslocamento2)

        vposicao1=[vposicao1,posicao1]
        vposicao2=[vposicao2,posicao2]

        tempo=[tempo,t]


plt.figure(1)
plt.plot(tempo, vposicao1)
plt.figure(2)
plt.plot(tempo, vposicao2)