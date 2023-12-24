clc;

disp("C.I Analógicos - Problema 7");
pkg load io;


#Par Diferencial

R = 1e+03;
RD1 = R;
RD2 = R;
VDD =15
I1 = 10e-03;
Kp = 250e-06;
W = 10.5e-06;
L = 3.5e-06;
VCM = VDD - (R*I1)/2

Vov = sqrt(I1/(Kp*(W/L)))
vov = 7
gm = I1/vov

Ad = gm*R

#Curvas
data = csvread('data-lab7.csv');
 
Vin = data(:,1);

#ID(M1)
IDM1 = data(:,2);

#ID(M2)
IDM2 = data(:,7);






#plot(Vin,IDS);
#legend("")
xlabel('Vin (V)')
ylabel('IDS(mA)')
title('Curva de transferência do Amplificador Diferencial')
set(gca,"linewidth",1,"fontsize",14)
grid on;





