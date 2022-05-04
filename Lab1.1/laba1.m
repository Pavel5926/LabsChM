
f = fopen("D:\ChislenniyeMetodi\Lab1\results.csv", "r");
g = fopen("D:\ChislenniyeMetodi\Lab1\middle_results.csv", "r");
h = fopen("D:\ChislenniyeMetodi\Lab1\diff_segments.csv", "r");
transc_bin = fscanf(f, "eps: %e, root: %f, iterations: %d\n", [3,14]);
transc_sec = fscanf(f, "eps: %e, root: %f, iterations: %d\n", [3,14]);
poly_bin = fscanf(f, "eps: %e, root: %f, iterations: %d\n", [3,14]);
poly_sec = fscanf(f, "eps: %e, root: %f, iterations: %d\n", [3,14]);

transc_bin_middle = fscanf(g, "%f,\n",37);
poly_bin_middle = fscanf(g, "%f,\n",38);
transc_sec_middle = fscanf(g, "%f,\n",4);
poly_sec_middle = fscanf(g, "%f,\n",7);

transc_bin_diff = fscanf(h, "eps: %e, iterations: %d, delta:%lf\n", [3,10]);
transc_sec_diff = fscanf(h, "eps: %e, iterations: %d, delta:%lf\n", [3,10]);
poly_bin_diff = fscanf(h, "eps: %e, iterations: %d, delta:%lf\n", [3,10]);
poly_sec_diff = fscanf(h, "eps: %e, iterations: %d, delta:%lf\n", [3,10]);

fclose(f);
fclose(g);
fclose(h);
eps = poly_bin (1,:);
root_poly_bin = poly_bin(2,:);
iterations_poly_bin = poly_bin(3,:);

root_poly_sec = poly_sec(2,:);
iterations_poly_sec = poly_sec(3,:);

root_transc_bin = transc_bin(2,:);
iterations_transc_bin = transc_bin(3,:);

root_transc_sec = transc_sec(2,:);
iterations_transc_sec = transc_sec(3,:);

transc_bin_diff_iter = transc_bin_diff(2,:);
transc_sec_diff_iter = transc_sec_diff(2,:);
poly_bin_diff_iter = poly_bin_diff(2,:);
poly_sec_diff_iter = poly_sec_diff(2,:);
delta = transc_bin_diff(3,:);
x = [0:0.01:2];
polynom = 4 .* x .^ 5 - 8 .* x .^ 4 - x .^ 2 + 3 .* x + 5;
transcendental = x .* cos(x) + 3 .* x .^ 2 - 1;

fzero_polynom = @(x) 4 .* x .^ 5 - 8 .* x .^ 4 - x .^ 2 + 3 .* x + 5;
fzero_transcendental = @(x) x .* cos(x) + 3 .* x .^ 2 - 1;
root_polynom = fzero(fzero_polynom,[1.7,2.0])
root_transcendental = fzero(fzero_transcendental,[0.25,0.5])

figure;
plot (x,polynom);
hold on
plot (x,transcendental)
grid on
title('Polynom and Transcendental function')
xlabel ('0 < x < 2')
ylabel ('-4 < y < 12')
legend({'Polynom','Transcendental'},'Location','southwest')

figure;
semilogy([1:1:38],abs(root_polynom-poly_bin_middle));
hold on
semilogy([1:1:7],abs(root_polynom-poly_sec_middle));
grid on
title('Polynom absolute convergence')
xlabel ('Iterations')
ylabel ('Convergence')
legend({'Bisection','Secant'},'Location','southwest')

figure;
semilogx(eps ,iterations_poly_bin)
hold on
semilogx (eps,iterations_poly_sec)
grid on
title('Polynom input labor')
xlabel ('Epsilon')
ylabel ('Iterations')
legend({'Bisection','Secant'},'Location','southwest')

figure;
loglog(eps,eps)
hold on
loglog (eps, abs(root_polynom-root_poly_bin))
loglog (eps, abs(root_polynom-root_poly_sec))
grid on
title('Polynom desired accuracy')
xlabel ('Epsilon')
ylabel ('Convergence eps')
legend({'Border line y = x','Bisection','Secant'},'Location','northwest')
figure;
semilogy([1:1:37],abs(root_transcendental-transc_bin_middle));
hold on
semilogy([1:1:4],abs(root_transcendental-transc_sec_middle));
grid on
title('Transcendental function absolute convergence')
xlabel ('Iterations')
ylabel ('Convergence')
legend({'Bisection','Secant'},'Location','southwest')

figure;
semilogx(eps ,iterations_transc_bin)
hold on
semilogx (eps,iterations_transc_sec)
grid on
title('Transcendental function input labor')
xlabel ('Epsilon')
ylabel ('Iterations')
legend({'Bisection','Secant'},'Location','northeast')

figure;
loglog(eps,eps)
hold on
loglog (eps, abs(root_transcendental-root_transc_bin))
loglog (eps, abs(root_transcendental-root_transc_sec))
grid on
title('Transcendental function desired accuracy')
xlabel ('Epsilon')
ylabel ('Convergence eps')
legend({'Border line y = x','Bisection','Secant'},'Location','northwest')

figure;
hold on
plot (delta, transc_bin_diff_iter)
plot (delta,transc_sec_diff_iter)
grid on
title('Delta dependence of iterations transcendental')
xlabel ('Delta')
ylabel ('Iterations count')
legend({'Bisection','Secant'},'Location','northwest')

figure;
hold on
plot (delta, poly_bin_diff_iter)
plot (delta,poly_sec_diff_iter)
grid on
title('Delta dependence of iterations polynom')
xlabel ('Delta')
ylabel ('Iterations count')
legend({'Bisection','Secant'},'Location','northwest')
