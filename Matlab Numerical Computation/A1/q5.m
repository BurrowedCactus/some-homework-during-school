x = linspace(-2*pi,2*pi,100);
y1 = sin(x);
y2 = cos(x);

f1 = figure;
f2 = figure;
figure(f1);

plot(x,y,'*');
plot(X1,Y1,LineSpec1,...,Xn,Yn,LineSpecn);

 
title('Graph of Sine and Cosine Between -2\pi and 2\pi');
xlabel('-2\pi < x < 2\pi'); % x-axis label
ylabel('sine and cosine values'); % y-axis label
grid on;

%interpolation using piecewise linear function

pl = spapi(2,x,y)
hold on;
fnplt (pl, 'r', 2); %2 is the line width

%interpolation using csape function
cap = csape(x,y,'variational'); %natural spline
cap = csape(x,y,'not-a-knot');

%find value evaluated at 0, 0.1, 0.2, ..., 1
fnval( f, 0:0.1:1 )

% refining the partition defined by row array, t, of parameter values
% create a refined row arrray, tref, of parameter values.

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

% convert cell array to vector
%numericCells is a 1-by-3 cell array, but numericVector is a 1-by-3 array of type double.
C = {'one', 'two', 'three'; 
     1, 2, 3}
numericCells = C(2,1:3)
numericVector = cell2mat(numericCells)% [1,2,3]
