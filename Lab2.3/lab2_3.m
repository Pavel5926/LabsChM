f = @(x) sqrt(x) + cos(x);
absErrPlot = importdata ('approx_count.csv');
nodesEpsPlot = importdata ('nodes_eps.csv');
accurate = integral(f, 0.1, 1);
for i = 1:12
    eps(i) = 1.* 10.^(-i);
end
% for i = 1:11
%     abs_err(i) = abs(accurate - absErrPlot(i,1));
% end
% for i = 1:11
%     abs_err_thr(i) = abs(accurate - nodesEpsPlot(i,1))
% end

figure;
loglog(eps(1:11),nodesEpsPlot(:,1));
hold on
grid on
loglog(eps,eps);
xlabel('eps');
ylabel('Runge error');
title('Runge error (given epsilon)')
legend({'Runge error','y = x (eps)'},'Location','southeast')

figure;
loglog(nodesEpsPlot(:,3), nodesEpsPlot(:,2));
hold on
grid on
xlabel('eps');
ylabel('num of intervals');
legend({'N(\epsilon)'},'Location','southwest')
title('Num of intervals (epsilon)')

figure;
loglog(eps,absErrPlot(:,1));
hold on
loglog(eps,eps)
loglog(eps, absErrPlot(:,3));
loglog(eps, absErrPlot(:,4));
legend({'y = x (eps)', 'actual','theormax','theormin'},'Location','northwest')
xlabel('eps');
ylabel('errors (min, max, actual (|acc - approx|)');
title('error(\epsilon)')