

Kp = 200e-06;
Kn = 2*Kp;
I = 40e-06;
Isd = -I/2;
Ids = I/2;

Vgs_carga = 2.0;
Vds_carga =Vgs_carga;
Vgs_par = 1.5;
Vds_par = Vgs_par;
Vto = 1.0;
VA_par = 400;
L = 5e-06;
VDD = 4.0;
CL = 15e-12;
Cc = 5e-12;

%Caracterização do estágio par diferencial
disp("Caracterização do estágio par diferencial \n ---------------------------- \n")
Lambda = 1/VA_par
Wp = (2*L*Ids)/(Kp*(Vgs_carga-Vto)^2*(1+Lambda*Vds_carga))*1e06 % em um
Wn = (2*L*Ids)/(Kn*(Vgs_par-Vto)^2*(1+Lambda*Vds_par))*1e06 % em um

ro1 = VA_par/Ids
ro_par = ro1/2
gm_par = 2*Ids/(Vgs_par-Vto)
Av_par = gm_par*ro_par % pico a pico
dB_par = 20*log10(Av_par)

disp("\n ---------------------------- \n")

%Caracterização do estágio Fonte-Comum (sem carga ativa)
disp("Caracterização do estágio Fonte-Comum \n ---------------------------- \n")

VA_fc = 800;
Ids = I;
Lambda_fc = 1/VA_fc
Wn_fc = (2*L*Ids)/(Kn*(Vgs_carga-Vto)^2*(1+Lambda_fc*Vds_carga))*1e06 % em um
ro_fc = VA_fc/Ids
gm_fc = 2*Ids/(Vgs_carga-Vto)
Av_fc = gm_fc*ro_fc
dB_fc = 20*log10(Av_fc)

fc = 1/(2*pi*ro_fc*Cc)
ft = gm_fc/(2*pi*Cc)


disp("\n ---------------------------- \n")
