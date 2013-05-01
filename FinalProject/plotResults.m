clear, clc, close all

load('data5_0_1.mat')
plot(tDesired,Desired,'k-',...
     tActual,Actual,'r.','MarkerSize',1)
grid