%% BME 354 Arduino Project

function Arduino(Samples)

delete(instrfind({'Port'},{'COM3'}));
S=serial('COM3','BaudRate',9600);
fopen(S);

region1end = input('Region1FinalTemp: ');
region1slope = input('Region1Slope: ');
region2time = input('Region2Time: ');
region3end = input('Region3FinalTemp: ');
region3slope = input('Region3Slope: ');
region45time = input('Region45Time: ');
region6slope = input('Region6Slope: ');
input('Press ENTER when ready!');

t=0:.5:749.5;
y=zeros(1,1500);
counter=1;

figure(1), clf, grid
xlabel('Time [sec]')
ylabel('Temperature [�C]')
axis([0 750 0 1000])

hold on

holder=fscanf(S,'%d');
y(counter)=holder(1);
plot(t(counter),y(counter),'r')
drawnow
counter=counter+1;

region1start = y(1);
region1time = (region1end-region1start)/region1slope;

region2start = region1end;
region2end = region2start;
region2slope = 0;

region3start = region2end;
region3time = (region3end-region3start)/region3slope;

region4start = region3end;
region4slope = region3slope;
region4time = region45time/2;
region4end = region4slope*region4time + region4start;

region5start = region4end;
region5end = region3end;
region5time = region4time;
region5slope = (region5end-region5start)/region5time;

region6start = region5end;
region6end = region1start;
region6slope = -region6slope;
region6time = (region6end-region6start)/region6slope;

region1iter = round(region1time)/0.5;
region2iter = round(region2time)/0.5;
region3iter = round(region3time)/0.5;
region4iter = round(region4time)/0.5;
region5iter = round(region5time)/0.5;
region6iter = round(region6time)/0.5;

for i = 1:region1iter
    z(i) = region1start + region1slope*0.5*i;
end
for i = 1:region2iter
    z(region1iter+i) = region2start + region2slope*0.5*i;
end
for i = 1:region3iter
    z(region1iter+region2iter+i) = region3start + region3slope*0.5*i;
end
for i = 1:region4iter
    z(region1iter+region2iter+region3iter+i) = region4start + region4slope*0.5*i;
end
for i = 1:region5iter
    z(region1iter+region2iter+region3iter+region4iter+i) = region5start + region5slope*0.5*i;
end
for i = 1:region6iter
    z(region1iter+region2iter+region3iter+region4iter+region5iter+i) = region6start + region6slope*0.5*i;
end

tplot = t(1:length(z));
plot(tplot,z,'k-')

while counter<=Samples
    holder=fscanf(S,'%d');
    y(counter)=holder(1);
    plot(t(counter),y(counter),'r')
    drawnow
    counter=counter+1;
end
fclose(S);
delete(S);

Region

end