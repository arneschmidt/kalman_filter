close all;
clear all;
arduino=serial('COM3','BaudRate',9600);
figure('units','normalized','position',[0,0,1,1]); 
hold on;
fopen(arduino); 
pause(1);
fprintf(arduino,'%s',[255]);


I=[1, 0;
   0, 1];
length=50; %Festlegen der Anzahl der Iterationsschritte
k=1:1:length; %Werte der x-Achse bei der Visualisierung
T= 0.05;   %Zeitspanne enes Iterationsschrittes


flushinput(arduino);
pause(0.1);
a=fscanf(arduino,'%f'); %Erster Messwert
if size(a)==0
    fprintf(arduino,'%s',[0]);
    fclose(arduino);
    quit
end

%% Initiaisierung der Matritzen
F= [1, -T;
    0, 1];
x= [a;
    5];
P= [0.0251, -0.0221;
    -0.0221, 0.4330];
H= [ 1, 0];
Q= [0.01, 0.01;
    0.01, 0.01];
R= 0.0857;

for i=1:length
    z=fscanf(arduino,'%f');  % aktueller Messwert
%% Vorhersage
xpred= F*x;
Ppred= F*P*F' + Q;

%% Korrektur
K = Ppred*H'/(H*P*H'+R);
x = xpred + (K *(z-H*xpred));
P = (I - K*H)*Ppred;

%% Erstellen einer Messwertliste
X(i)=x(1);
Xpred(i)=xpred(1);
Z(i)=z;

%% Echtzeit-Visualisierung
plot(k(1:i),Z,'b',k(1:i),Xpred,'r',k(1:i),X,'k', 'Linewidth',3);
h_legend=legend('Messwert','Vorhergesagter Wert','Kalman-Filter-Schätzwert');

set(h_legend,'FontSize',14);

axis([0,length,a-0.3*length,a+3]);
xlabel('Iterationsschritte');
ylabel('Abstand in cm');
drawnow;
end


fprintf(arduino,'%s',[0]);
fclose(arduino);


