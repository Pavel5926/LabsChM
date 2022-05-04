f = @(x) sqrt(x) + cos(x);
fnsmooth = @(x) sqrt(x) + abs(cos(x));
nodes = 1000;
filename_max_err = 'gmax.csv';
filename_GofX_357 = 'g357.csv';
filename_h= 'h.csv';
filename_x = 'xout.csv';
filename_max_err_prev_sm = 'E:\ChM\Lab2.1\Project1\Project1\max.csv';
filename_max_err_prev_nsm = 'E:\ChM\Lab2.1\Project1\Project1\nsmoothmax.csv'
dim = 3:100;
a = 5; b = 10; 

f_h = fopen(filename_h, 'r');
f_gofx = fopen(filename_GofX_357,'r'); 
f_x = fopen(filename_x, 'r');
f_merr = fopen(filename_max_err, 'r');
f1_err_sm = fopen(filename_max_err_prev_sm, 'r');
f1_err_nsm = fopen(filename_max_err_prev_nsm, 'r');
g3915ofx = fscanf(f_gofx, '%f;', [nodes, 3]);
lspc = fscanf(f_x, '%f;',[1, nodes]);
m_err = fscanf(f_merr,'%f;', [1, 98]);
m1_err_sm = fscanf(f1_err_sm,'%f;', [1,98]);
m1_err_nsm = fscanf(f1_err_nsm,'%f;', [1,98]);
hmas = fscanf(f_h,'%f;', [1,98]);
g3ofx = g3915ofx(:,1);
g9ofx = g3915ofx(:,2);
g15ofx = g3915ofx(:,3);

figure;
subplot(2,2,1)
fplot (f,[a, b]);
legend({'sqrt(x) + cos(x)'},'Location','northeast')
title('Smooth Matlab function')
xlabel ('x')
ylabel ('y')
subplot(2,2,2)
plot (linspace(a, b, nodes),f(linspace(a, b, nodes)),'b');
%fplot (f,[a, b]);
hold on
grid on
plot(lspc, g3ofx,'r');
plot(lspc, g9ofx,'k');
plot(lspc, g15ofx,'y');
plot(linspace(a,b,4),f(linspace(a,b,4)),"Marker","*","LineStyle","none");
plot(linspace(a,b,10),f(linspace(a,b,10)),"Marker","o","LineStyle","none");
plot(linspace(a,b,16),f(linspace(a,b,16)),"Marker","diamond","LineStyle","none");
legend({'f(x) = sqrt(x) + cos(x)','Spline. Intervals: 5','Spline. Intervals: 9', 'Spline. Intervals: 15','Nodes:6','Nodes: 10','Nodes: 16'},'Location','northeast')
title('Polynoms')
xlabel ('x')
ylabel ('S_{n}(x)')

subplot(2,2,3)
semilogy(dim,m_err)
hold on
semilogy(dim,m1_err_sm)
legend({'Spline','Newton'},'Location','northwest')
title('Max err of num of nodes')
xlabel ('num of nodes')
ylabel ('max err')

subplot(2,2,4)
semilogy(lspc,abs(g3ofx-f(lspc')));
hold on
grid on
semilogy(lspc,abs(g9ofx-f(lspc')));
semilogy(lspc,abs(g15ofx-f(lspc')));
legend({'|S_3(x)-f(x)|','|S_9(x)-f(x)|','|S_{15}(x)-f(x)|'},'Location','southeast')
title('S(x)-f(x)')
xlabel ('x')
ylabel ('S_{n}')


% second part of work for non-smooth function
a = 5; b = 10;
figure;
subplot(2,2,1)
fplot (fnsmooth,[a, b]);
legend({'sqrt(x) + cos(x)'},'Location','northwest')
title('non-smooth Matlab function')
xlabel ('x')
ylabel ('y')

filename_max_err_nsmooth = 'gnmax.csv';
filename_GofX_357_nsmooth = 'gn357.csv';
filename_x_nsmooth = 'xout.csv';

f_gofx_nsmooth = fopen(filename_GofX_357_nsmooth,'r'); 
f_x_nsmooth = fopen(filename_x_nsmooth, 'r');
f_merr_nsmooth = fopen(filename_max_err_nsmooth, 'r');
g3915ofx_nsmooth = fscanf(f_gofx_nsmooth, '%f;', [nodes, 3]);
lspc_nsmooth = fscanf(f_x_nsmooth, '%f;',[1, nodes]);
m_err_nsmooth = fscanf(f_merr_nsmooth,'%f;', [1, 998]);
g3ofx_nsmooth = g3915ofx_nsmooth(:,1);
g9ofx_nsmooth = g3915ofx_nsmooth(:,2);
g15ofx_nsmooth = g3915ofx_nsmooth(:,3);

subplot(2,2,2)
plot (linspace(a, b, nodes),fnsmooth(linspace(a, b, nodes)),'b');
hold on
grid on
plot(lspc_nsmooth, g3ofx_nsmooth);

plot(lspc_nsmooth, g9ofx_nsmooth);
plot(lspc_nsmooth, g15ofx_nsmooth);
plot(linspace(a,b,6),fnsmooth(linspace(a,b,6)),"Marker","*","LineStyle","none");
plot(linspace(a,b,10),fnsmooth(linspace(a,b,10)),"Marker","o","LineStyle","none");
plot(linspace(a,b,16),fnsmooth(linspace(a,b,16)),"Marker","diamond","LineStyle","none");
legend({'fn(x) = sqrt(x) + |cos(x)|','Spline. Intervals: 5','Spline. Intervals: 9', 'Spline. Intervals: 15','Nodes:6','Nodes: 15','Nodes: 16'},'Location','northwest')
title('Splines')
xlabel ('x')
ylabel ('S_{n}(x)')

subplot(2,2,3)
semilogy(dim,m_err_nsmooth)
hold on
semilogy(dim,m1_err_nsm)
legend({'|fn - max err|'},'Location','northwest')
title('Max err of num of nodes')
xlabel ('x')
ylabel ('y')
legend({'Spline','Newton'},'Location','northwest')
title('Max err of num of nodes')
xlabel ('num of nodes')
ylabel ('max err')

subplot(2,2,4)
semilogy(lspc_nsmooth,abs(g3ofx_nsmooth-fnsmooth(lspc_nsmooth')));
hold on
grid on
semilogy(lspc_nsmooth,abs(g9ofx_nsmooth-fnsmooth(lspc_nsmooth')));
semilogy(lspc_nsmooth,abs(g15ofx_nsmooth-fnsmooth(lspc_nsmooth')));
legend({'|S_5(x)-f(x)|','|S_9(x)-f(x)|','|S_{15}(x)-f(x)|'},'Location','southeast')
title('S(x)-f(x)')
ylabel ('S_{n}(x)-nsmf(x)')
xlabel ('x')

figure;
subplot(1,2,1)
loglog(hmas, m_err)
hold on 
grid on
loglog(hmas,m_err_nsmooth)
loglog(hmas, (5/384*0.9980).*hmas.^4)
legend({'smooth','nsmooth','Ch^4'},'Location','southeast')
title('max err/x ')
ylabel ('max err')
xlabel ('h')
subplot(1,2,2)
loglog(hmas, m1_err_sm)
hold on 
grid on
loglog(hmas,m1_err_nsm)
legend({'smooth','nsmooth'},'Location','southeast')
title('max err/x (Newton)')
ylabel ('max err')
xlabel ('h')