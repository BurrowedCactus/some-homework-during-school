x = -1:0.2:7;
y = zeros(size(x));

g = (-1 <= x & x <= 1);
y(g)  = 2 - 2285/1248 * (x(g) + 1) + 1661/4992 * (x(g) + 1).^3;
g = (1 < x & x <= 2);
y(g)=1 + 1349/624* (x(g) - 1) + 1661/832 * (x(g) - 1).^2  - 2891/2496 * (x(g)-1).^3;
g = (2< x & x <= 5);
y(g)=4 + 6689/2496* (x(g) - 2) - 615/416 * (x(g) - 2).^2  + 91/576 * (x(g)-2).^3;
g = (5 < x & x <= 7);
y(g)=3 - 1201/624* (x(g) - 5) - 47/832 * (x(g) - 5).^2  + 47/4992 * (x(g)-5).^3;

plot(x,y,'*-');
