% spectre_sum.m
clear all
close all
clc
mkdir 'signal';
mkdir 'spectre';
% Длина сигнала (с)
tmax = 0.5;
% Частота дискретизации (Гц) (количество отсчётов)
fd = 512;
% Частота первого сигнала (Гц)
f1 = 10;
% Частота второго сигнала (Гц)
f2 = 40;
% Амплитуда первого сигнала
a1 = 1;
% Амплитуда второго сигнала
a2 = 0.7;
% Спектр сигнала
fd2 = fd/2;
% Сумма двух сигналов (синусоиды) разной частоты
% Массив отсчётов времени:
t = 0:1./fd:tmax;
signal1 = a1*sin(2*pi*t*f1);
signal2 = a2*sin(2*pi*t*f2);
signal = signal1 + signal2;
figure()
plot(signal), grid;
title('Signal');
% Подсчет спектра:
% Амплитуды преобразования Фурье сигнала
spectre = fft(signal,fd);
% Сетка частот
f = 1000*(0:fd2)./(2*fd);
% Нормировка спектра по амплитуде:
spectre = 2*sqrt(spectre.*conj(spectre))./fd2;
% Построение спектра сигнала
figure()
plot(f,spectre(1:fd2+1)), grid
xlim([0 100]);
title('Spectre');
xlabel('Frequency (Hz)');
