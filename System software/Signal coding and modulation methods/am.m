% am.m
clear all
close all
clc
mkdir 'signal';
mkdir 'spectre';
% Модуляция синусоид с частотами 50 и 5
% Длина сигнала (с)
tmax = 0.5;
% Частота дискретизации (Гц) (количество отсчётов)
fd = 512;
% Частота сигнала (Гц)
f1 = 5;
% Частота несущей (Гц)
f2 = 50;
% Спектр сигнала
fd2 = fd/2;
% Построение графиков двух сигналов (синусоиды)
% разной частоты
% Массив отсчётов времени:
t = 0:1./fd:tmax;
signal1 = sin(2*pi*t*f1);
signal2 = sin(2*pi*t*f2);
signal = signal1 .* signal2;
figure()
plot(signal, 'b'), grid;
hold on
% Построение огибающей:
plot(signal1, 'r'), grid;
plot(-signal1, 'r'), grid;
hold off
title('Signal');
% Расчет спектра:
% Амплитуды преобразования Фурье-сигнала
spectre = fft(signal,fd);
% Сетка частот
f = 1000*(0:fd2)./(2*fd);
% Нормировка спектра по амплитуде:
spectre = 2*sqrt(spectre.*conj(spectre))./fd2;
% Построение спектра:
figure()
plot(f,spectre(1:fd2+1), 'b'), grid;
xlim([0 100]);
title('Spectre');
xlabel('Frequency (Hz)');
