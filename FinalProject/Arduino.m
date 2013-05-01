function Arduino(Samples)

% Setup COM3 Port
delete(instrfind({'Port'},{'COM4'}));
S = serial('COM4','BaudRate',9600);
fopen(S);

% Enter same input values as those from Arduino
r1.end = input('Enter Region 1 Final Temperature [°C]: ');
r1.slope = input('Enter Region 1 Slope [°C/s]: ');
r2.time = input('Enter Region 2 Time [sec]: ');
r3.end = input('Enter Region 3 Final Temperature [°C]: ');
r3.slope = input('Enter Region 3 Slope [°C/s]: ');
r45time = input('Enter Region 4&5 Time [sec]: ');
r6.slope = input('Enter Region 6 Slope [°C/s]: ');
input('Press ENTER when ready!');

% Initializes Actual values
tActual = 0 : 0.5 : 749.5;
Actual = zeros(1,1500);
counter = 1;

% Starts figure
figure, clf, grid
xlabel('Time [sec]')
ylabel('Temperature [°C]')
axis([0 750 0 350])
hold on

% Obtains first Actual data point
holder = fscanf(S,'%d');
Actual(counter) = holder(1);
plot(tActual(counter),Actual(counter),'r')
drawnow
counter = counter + 1;

% Calculates necessary values to draw Desired graph
r1.start = Actual(1);
r1.time = (r1.end-r1.start)/r1.slope;

r2.start = r1.end;
r2.end = r2.start;
r2.slope = 0;

r3.start = r2.end;
r3.time = (r3.end-r3.start)/r3.slope;

r4.start = r3.end;
r4.slope = r3.slope;
r4.time = r45time/2;
r4.end = r4.slope*r4.time + r4.start;

r5.start = r4.end;
r5.end = r3.end;
r5.time = r4.time;
r5.slope = (r5.end-r5.start)/r5.time;

r6.start = r5.end;
r6.end = r1.start;
r6.slope = -r6.slope;
r6.time = (r6.end-r6.start)/r6.slope;

r1.iter = round(r1.time)/0.5;
r2.iter = round(r2.time)/0.5;
r3.iter = round(r3.time)/0.5;
r4.iter = round(r4.time)/0.5;
r5.iter = round(r5.time)/0.5;
r6.iter = round(r6.time)/0.5;

for i = 1:r1.iter
    Desired(i) = r1.start + r1.slope*0.5*i;
end
for i = 1:r2.iter
    Desired(r1.iter+i) = r2.start + r2.slope*0.5*i;
end
for i = 1:r3.iter
    Desired(r1.iter+r2.iter+i) = r3.start + r3.slope*0.5*i;
end
for i = 1:r4.iter
    Desired(r1.iter+r2.iter+r3.iter+i) = r4.start + r4.slope*0.5*i;
end
for i = 1:r5.iter
    Desired(r1.iter+r2.iter+r3.iter+r4.iter+i) = r5.start + r5.slope*0.5*i;
end
for i = 1:r6.iter
    Desired(r1.iter+r2.iter+r3.iter+r4.iter+r5.iter+i) = r6.start + r6.slope*0.5*i;
end

% Plots Desired graph
tDesired = tActual(1:length(Desired));
plot(tDesired,Desired,'k-')

% Obtains and plots remaining Actual Points
while counter <= Samples
    holder = fscanf(S,'%d');
    Actual(counter) = holder(1);
    plot(tActual(counter),Actual(counter),'r')
    drawnow
    counter = counter + 1;
    save('data.mat','tActual','Actual','tDesired','Desired')
end
fclose(S);
delete(S);

end