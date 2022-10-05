% meandr.m
clear all
close all
clc
% количество отсчетов:
N=8;
% частота дискретизации:
t=-1:0.01:1;
% значение амплитуды:
A=1;
T=1;
nh=(1:N)*2-1;
% входной сигнал:
harmonics=cos(2*pi*nh'*t/T);
Am=2/pi./nh;
Am(2:2:end)=-Am(2:2:end);
s1=harmonics.*repmat(Am',1,length(t));
s2=cumsum(s1);
for k=1:N
subplot(4,2,k)
plot(t, s2(k,:)),grid
end
