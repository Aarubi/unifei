disp("Parâmetros do Circuito");

%Parâmetros do Filtro

%RA:2018010520
%R1 = R2 = Rin ; C1 = C2 = C:

%Frequência de corte = (últimos 2 digitos do RA)*10e+03
fc = 20e+03; %Hz
FSF = 0.8414; %Fator correção de frequência de corte (somente pra Q > 0.7071)
fsfc = fc*FSF
wo = 2*pi*fc %rad/s

Q = 1.305; %Fator de qualidade
Qn = Q/sqrt(1-(1/(4*Q^2))) % Magnitude de pico normalizado
QdB = 20*log10(Qn) %Magnitude de pico em dB


%Ganho do filtro
K = 3 - 1/Q

% Capacitores do Filtro (C1 e C2)
C = 10e-09; %F

% Resistências de entrada (R1 = R2)

Rin = 1/(2*pi*fsfc*C) %Ohm

% Resistências de saída ( R3 e R4)

R3 = 1e+03 %Ohm

R4 = R3*(K-1) %Ohm

% Resposta em Frequência:

%s = tf('s');

N=2; 
flat = sqrt(10^(QdB/20)-1) %Fator de pico
phi = (1/N)*asinh(1/flat); 
sigma1 = pi/4; 
sigma2 = 3*pi/4; 

%Polos do Filtro
p1 = -(sinh(phi)*sin(sigma1)) + (cosh(phi)*cos(sigma1))*i 
p2 = -(sinh(phi)*sin(sigma2)) + (cosh(phi)*cos(sigma2))*i
pw1 = -wo*(sinh(phi)*sin(sigma1)) + wo*(cosh(phi)*cos(sigma1))*i 
pw2 = -wo*(sinh(phi)*sin(sigma2)) + wo*(cosh(phi)*cos(sigma2))*i

%Funções de Transferência
%HSK = ((-real(p1)*(-real(p2))))/((s-real(p1))*(s-real(p2))) 
%Ho = -(real(p1)+real(p2))+(real(p1)*real(p2))
%H = (Ho*K)/((s-real(p1))*(s-real(p2))) 
%H = 1/(s^2+((wo/Q)*s)+(wo^2))





% Chebyshev

%H = cheby1()



% ripple
