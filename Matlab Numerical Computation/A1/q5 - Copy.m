CellA =
CellB =
array = {CellA, CellB, CellC} 
f1 = figure;
figure(f1);

for i = 1:4

x1 = cell2mat(array(i)(:,1));
y1 = cell2mat(array(i)(:,2));
hold on;
plot(x1, y1, '*');

end 

title('Graph of plot with no interpolation');
xlabel('x-axis'); % x-axis label
ylabel('y-axis'); % y-axis label
grid on;


f2 = figure;
figure(f2);

for i = 1:4

x2 = cell2mat(array(i)(:,1));
y2 = cell2mat(array(i)(:,2));
pl = spapi(2,x2,y2);
fnplt(pl, 'r', 2);

end

title('Graph of plot with piecewise linear interpolation');
xlabel('x-axis'); % x-axis label
ylabel('y-axis'); % y-axis label
grid on;




f3 = figure;
title('Graph of plot with natual spline interpolation');

f4 = figure;
title('Graph of plot with not-a-knot spline interpolation');

for i = 1:4

x3a = x1a;
y3a = y1a;
index = zeros(1, length(x3a) - 1);
deltax = x3a(1:length(x3a) - 2) - x3a(2:length(x3a) - 1);
deltay = y3a(1:length(y3a) - 2) - y3a(2:length(y3a) - 1);
delta = sqrt(deltax.^2 + deltay.^2);
t = [0];
t = [t, delta];
splxa = csape(t, x, 'variational');
splya = csape(t, y, 'variational');
splxb = csape(t, x, 'not-a-knot');
splyb = csape(t, y, 'not-a-knot');

N = length(t);
tref = zeros(1, 6*(N-1)+1);
for k = 1:N-1
	i = 6 * (k-1) + 1;
	dt = t(k+1) - t(k);
	tref(i) = t(k);
	tref(i+1) = t(k) + dt/6;
	tref(i+2) = t(k) + 2*dt/6;
	tref(i+3) = t(k) + 3*dt/6;
	tref(i+4) = t(k) + 4*dt/6;
	tref(i+5) = t(k) + 5*dt/6;
end
tref(6*(N-1)+1) = t(N);

xrefa = fnval( splxa, tref );
yrefa = fnval( splya, tref );
xrefb = fnval( splxb, tref );
yrefb = fnval( splyb, tref );

figure(f3);
plot(xrefa, yrefa, '-');

figure(f4);
plot(xrefb, yrefb, '-');
end


