% main.m
clear all
close all
clc
% Задаем входную кодовую последовательность:
data=[0 1 1 0 0 0 0 1 0 1 1  1 0 1 1 1 0 1 1 0 0 1 0 0 0 1 1 0 1 1 1 1 0 1 1 0 1 1 1 0 0 1 1 0 1 0 0 1 0 1 1 0 1 1 1 0];
% Задаем входную кодовую последовательность
% для проверки свойства самосинхронизации:
data_sync=[0 0 0 0 0 0 0 1 1 1 1 1 1 1];
% Построение графиков кодированного сигнала
mkdir 'signal';
axis('auto');
% Униполярное кодирование
wave=unipolar(data);
figure()
plot(wave), grid;
ylim([-1 6]);
title('Unipolar');
% Кодирование ami
wave=ami(data);
figure()
plot(wave), grid;
ylim([-6 6]);
title('AMI');
% Кодирование NRZ
wave=bipolarnrz(data);
figure()
plot(wave), grid;
ylim([-6 6]);
title('Bipolar Non-Return to Zero');
% Кодирование RZ
wave=bipolarrz(data);
figure()
plot(wave), grid;
ylim([-6 6]);
title('Bipolar Return to Zero');
% Манчестерское кодирование
wave=manchester(data);
figure()
plot(wave), grid;
ylim([-6 6]);
title('Manchester');
% Дифференциальное манчестерское кодирование
wave=diffmanc(data);
figure()
plot(wave), grid;
ylim([-6 6]);
title('Differential Manchester');
% Построение графиков кодированного сигнала
% для проверки свойства самосинхронизации
mkdir 'sync';
axis('auto');
% Униполярное кодирование
wave=unipolar(data_sync);
figure()
plot(wave), grid;
ylim([-1 6]);
title('Unipolar');
% Кодирование AMI
wave=ami(data_sync);
figure()
plot(wave), grid;
ylim([-6 6]);
title('AMI');
% Кодирование NRZ
wave=bipolarnrz(data_sync);
figure()
plot(wave), grid;
ylim([-6 6]);
title('Bipolar Non-Return to Zero');
% Кодирование RZ
wave=bipolarrz(data_sync);
figure()
plot(wave), grid;
ylim([-6 6]);
title('Bipolar Return to Zero');
% Манчестерское кодирование
wave=manchester(data_sync);
figure()
plot(wave), grid;
ylim([-6 6]);
title('Manchester');
% Дифференциальное манчестерское кодирование
wave=diffmanc(data_sync);
figure()
plot(wave), grid;
ylim([-6 6]);
title('Differential Manchester');

Листинг 5 – Файл main.m
% diffmanc.m
function wave=diffmanc(data)
data=filter(1,[1 1],data);
data=mod(data,2);
wave=manchester(data);


% ami.m
function wave=ami(data)
am=mod(1:length(data(data==1)),2);
am(am==0)=-1;
data(data==1)=am;
wave=maptowave(data);

% unipolar.m
function wave=unipolar(data)
wave=maptowave(data);


% maptowave.m
function wave=maptowave(data) 
data=upsample(data,100);
wave=filter(5*ones(1,100),1,data);

% calcspectre.m
function spectre = calcspectre(wave)
Fd = 512; % Частота дискретизации (Гц)
Fd2 = Fd/2;
Fd3 = Fd/2 + 1;
X = fft(wave,Fd);
spectre = X.*conj(X)/Fd;
f = 1000*(0:Fd2)/Fd;
figure()
plot(f,spectre(1:Fd3)), grid;
xlabel('Frequency (Hz)');

function wave=manchester(data)
data(data==0)=-1;
data=upsample(data,2);
data=filter([-1 1],1,data);
wave=maptowave(data);

function wave=bipolarrz(data)
data(data==0)=-1;
data=upsample(data,2);
wave=maptowave(data);


function wave=bipolarnrz(data)
data(data==0)=-1;
wave=maptowave(data);
