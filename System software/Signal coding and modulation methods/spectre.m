% spectre.m
clear all
close all
clc
mkdir 'signal';
mkdir 'spectre';
tmax = 0.5;% Длина сигнала (с)
fd = 512; % Частота дискретизации (Гц) (количество отсчётов)
f1 = 10;% Частота первого сигнала (Гц)
f2 = 40;% Частота второго сигнала (Гц)
a1 = 1;% Амплитуда первого сигнала
a2 = 0.7;% Амплитуда второго сигнала
fd2 = fd/2; % Спектр сигнала
% Рассмотрим два сигнала (синусоиды) разной частоты
t = 0:1./fd:tmax; % Массив отсчётов времени
signal1 = a1*sin(2*pi*t*f1);
signal2 = a2*sin(2*pi*t*f2);
figure()
plot(signal1,'b'); % голубая
hold on
plot(signal2,'r'); % красная
hold off
title('Signal');
grid on
% Посчитаем спектр
% Амплитуды преобразования Фурье сигнала 1
spectre1 = abs(fft(signal1,fd));
% Амплитуды преобразования Фурье сигнала 2
spectre2 = abs(fft(signal2,fd));
% Построение спектров сигналов
figure()
plot(spectre1,'b'); % голубая
hold on
plot(spectre2,'r'); % красная
hold off
title('Spectre');
% Исправление графика спектра
f = 1000*(0:fd2)./(2*fd); % Сетка частот
% Нормировка спектров по амплитуде
spectre1 = 2*spectre1/fd2;
spectre2 = 2*spectre2/fd2;
% Построение спектров сигналов
figure()
plot(f,spectre1(1:fd2+1),'b'); % голубая
hold on
plot(f,spectre2(1:fd2+1),'r'); % красная
hold off
xlim([0 100]);
title('Fixed spectre');
xlabel('Frequency (Hz)');
