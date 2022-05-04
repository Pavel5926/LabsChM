approx = importdata ('approx.csv');
epsplot = importdata ('epsplot.csv');
localerr = importdata ('localerr.csv');

y = @(x) x.*sin(x);
a = pi/2;
b = 2*pi;
n = 10;
x = linspace(a,b,10*n);
xapprox = linspace(a,b,n+1);

%2nd plot local global err

h = localerr(:,end);
local = abs(localerr(:,1));
localerr(:,end) = [];
globalerr = localerr(:,end);
% 3rd plot eps iter 
%iter = epsplot(:,5);
%epsplot(:, 5) = [];
%maxeps = epsplot(:,end)
for i = 1:15
    eps(i) = 1 * 10.^(-i);
end

%3rd graph
localRunge = epsplot(:,1);
globalRunge = epsplot(:,2);
iter = epsplot(:,end);

figure;
subplot(1,2,1)
plot(x,y(x));
hold on;
plot(xapprox,approx(1,:));
xlabel('x')
ylabel('y')
legend ({'accurate','approx'},'Location', 'northeast')
title('solution plot')
subplot(1,2,2)
plot(xapprox,y(xapprox) - approx(1,:));
xlabel('x')
ylabel('error')
title('error in nodes n = 10')

figure;
loglog(h,local);
hold on
loglog(h, globalerr);
loglog(h, h.^4)
loglog(h, h.^3)
xlabel('h')
ylabel('local/global errors')
legend({'local err: first element', 'global err : last element','h^4','h^3'},'Location', 'northwest')
title('local and global errors')
figure;
subplot(1,2,1)
loglog(eps,eps);
hold on
loglog(eps,localRunge);
loglog(eps,globalRunge);
xlabel('eps')
ylabel('maxerr')
legend({'y = x eps','local (Runge)','global (Runge)'},'Location', 'northwest')
title('is accurate ?')
subplot(1,2,2)
loglog(eps,iter);
grid on 
xlabel('eps')
ylabel('iter')
title('iter/eps')