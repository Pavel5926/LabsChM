f = @(x) x.^2.*cos(2*x) + 1;
figure
%n = 14;
for n = 5:10:65 
subplot(2,1,1)
a = -4; b = -1;
fplot (f,[a, b])
x_i = linspace(a, b, n+1);
hold on
y_i = f(x_i);
plot(x_i, y_i, '*r')
coef = polyfit (x_i,y_i, n);
p = @(x) polyval(coef, x);
xx = linspace(a, b, 1000);
hold on
p_xx = p(xx);
plot(xx, p_xx, '--g');
grid on
legend ('function', 'data','polynomial')
hold off
error = abs(p_xx - f(xx));
subplot(2,1,2)
semilogy(xx,error)
grid on
error_max = max(error);
title (['error max = ', num2str(error_max)])
pause (1)
end
