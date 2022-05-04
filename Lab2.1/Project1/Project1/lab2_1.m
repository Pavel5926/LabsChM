f = @(x) sqrt(x) + cos(x);
fnsmooth = @(x) sqrt(x) + abs(cos(x));
nodes = 1000;
filename_max_err = 'E:\ChM\Lab2.1\Project1\Project1\max.csv';
filename_YofX_357 = 'E:\ChM\Lab2.1\Project1\Project1\y357.csv';
filename_linspace = 'E:\ChM\Lab2.1\Project1\Project1\linspace_out.csv';


dim = 3:50;
a = 1; b = 3;
figure;
subplot(2,2,1)
fplot (f,[a, b]);
legend({'sqrt(x) + cos(x)'},'Location','northeast')
title('Smooth Matlab function')
xlabel ('x')
ylabel ('y')

f_yofx = fopen(filename_YofX_357,'r'); 
f_lspc = fopen(filename_linspace, 'r');
f_merr = fopen(filename_max_err, 'r');
y357ofx = fscanf(f_yofx, '%f;', [nodes, 3]);
lspc = fscanf(f_lspc, '%f;',[1, nodes]);
m_err = fscanf(f_merr,'%f;', [1, 998]);
y3ofx = y357ofx(:,1);
y5ofx = y357ofx(:,2);
y7ofx = y357ofx(:,3);

subplot(2,2,2)
plot (linspace(a, b, nodes),f(linspace(a, b, nodes)),'b');
%fplot (f,[a, b]);
hold on
grid on
plot(lspc, y3ofx,'r');
plot(lspc, y5ofx,'k');
plot(lspc, y7ofx,'y');
plot(linspace(a,b,4),f(linspace(a,b,4)),"Marker","*","LineStyle","none");
plot(linspace(a,b,6),f(linspace(a,b,6)),"Marker","o","LineStyle","none");
plot(linspace(a,b,8),f(linspace(a,b,8)),"Marker","diamond","LineStyle","none");
legend({'f(x) = sqrt(x) + cos(x)','Polynom. Degree: 3','Polynom. Degree: 5', 'Polynom. Degree: 7','Nodes 4','Nodes 6','Nodes 8'},'Location','northeast')
title('Polynoms')
xlabel ('x')
ylabel ('P_{n}(x)')

subplot(2,2,3)
semilogy(dim,m_err)
legend({'f(x)- approx(x) (max)'},'Location','northwest')
title('Max err of num of nodes')
xlabel ('max err')
ylabel ('num of nodes')

subplot(2,2,4)
semilogy(lspc,abs(y3ofx-f(lspc')));
hold on
grid on
semilogy(lspc,abs(y5ofx-f(lspc')));
semilogy(lspc,abs(y7ofx-f(lspc')));
legend({'|P_3(x)-f(x)|','|P_5(x)-f(x)|','|P_7(x)-f(x)|'},'Location','northwest')
title('P(x)-f(x)')
xlabel ('x')
ylabel ('P_{n}')

% second part of work for non-smooth function
a = 1; b = 3;
figure;
subplot(2,2,1)
fplot (fnsmooth,[a, b]);
legend({'sqrt(x) + cos(x)'},'Location','northwest')
title('non-smooth Matlab function')
xlabel ('x')
ylabel ('y')

filename_max_err_nsmooth = 'E:\ChM\Lab2.1\Project1\Project1\nsmoothmax.csv';
filename_YofX_357_nsmooth = 'E:\ChM\Lab2.1\Project1\Project1\nsmoothy357.csv';
filename_linspace_nsmooth = 'E:\ChM\Lab2.1\Project1\Project1\nsmoothlinspace_out.csv';

f_yofx_nsmooth = fopen(filename_YofX_357_nsmooth,'r'); 
f_lspc_nsmooth = fopen(filename_linspace_nsmooth, 'r');
f_merr_nsmooth = fopen(filename_max_err_nsmooth, 'r');
y357ofx_nsmooth = fscanf(f_yofx_nsmooth, '%f;', [nodes, 3]);
lspc_nsmooth = fscanf(f_lspc_nsmooth, '%f;',[1, nodes]);
m_err_nsmooth = fscanf(f_merr_nsmooth,'%f;', [1, 48]);
y3ofx_nsmooth = y357ofx_nsmooth(:,1);
y5ofx_nsmooth = y357ofx_nsmooth(:,2);
y7ofx_nsmooth = y357ofx_nsmooth(:,3);

subplot(2,2,2)
plot (linspace(a, b, nodes),f(linspace(a, b, nodes)),'b');
hold on
grid on
plot(lspc_nsmooth, y3ofx_nsmooth);

plot(lspc_nsmooth, y5ofx_nsmooth);
plot(lspc_nsmooth, y7ofx_nsmooth);
plot(linspace(a,b,4),f(linspace(a,b,4)),"Marker","*","LineStyle","none");
plot(linspace(a,b,6),f(linspace(a,b,6)),"Marker","o","LineStyle","none");
plot(linspace(a,b,8),f(linspace(a,b,8)),"Marker","diamond","LineStyle","none");
legend({'fn(x) = sqrt(x) + |cos(x)|','Polynom. Degree: 3','Polynom. Degree: 5', 'Polynom. Degree: 7','Nodes 4','Nodes 6','Nodes 8'},'Location','northwest')
title('Polynoms')
xlabel ('x')
ylabel ('P_{n}(x)')

subplot(2,2,3)
semilogy(dim,m_err_nsmooth)
legend({'|f - max err|'},'Location','northwest')
title('Max err of num of nodes')
xlabel ('x')
ylabel ('y')
legend({'f(x)- approx(x) (max)'},'Location','northwest')
title('Max err of num of nodes')
xlabel ('max err')
ylabel ('num of nodes')

subplot(2,2,4)
semilogy(lspc_nsmooth,abs(y3ofx_nsmooth-f(lspc_nsmooth')));
hold on
grid on
semilogy(lspc_nsmooth,abs(y5ofx_nsmooth-f(lspc_nsmooth')));
semilogy(lspc_nsmooth,abs(y7ofx_nsmooth-f(lspc_nsmooth')));
legend({'|P_3(x)-f(x)|','|P_5(x)-f(x)|','|P_7(x)-f(x)|'},'Location','southeast')
title('P(x)-f(x)')
ylabel ('P_{n}(x)-nsmf(x)')
xlabel ('x')