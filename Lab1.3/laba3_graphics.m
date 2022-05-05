
dimension = 10;
number_of_tests = 10;
filename_vector_x_accurate = 'D:\ChislenniyeMetodi\Lab3\MATLAB_EXPORT_VectorX_ACCURATE.csv';
filename_vector_x_approx = 'D:\ChislenniyeMetodi\Lab3\C_EXPORT_VectorX.csv';
filename_time_profile_SECOND = 'D:\ChislenniyeMetodi\Lab3\C_EXPORT_Time_Profile.csv';
filename_time_profile_SECOND_PREVIOUS = 'D:\ChislenniyeMetodi\Lab2\C_EXPORT_Time_Profile.csv';
filename_iter = 'D:\ChislenniyeMetodi\Lab3\C_EXPORT_Iterations.csv';
v_x_acc = fopen (filename_vector_x_accurate,'r');
v_x_approx = fopen(filename_vector_x_approx,'r');
time_f = fopen(filename_time_profile_SECOND,'r');
time_f_prev = fopen(filename_time_profile_SECOND_PREVIOUS,'r');
iter_f = fopen(filename_iter,'r');
diff_dimension = [50:50:2000]

all_vector_x_accurate=fscanf(v_x_acc,'%f;',[dimension,number_of_tests]);
all_vector_x_approx=fscanf(v_x_approx,'%f;',[dimension,number_of_tests]);
time_data = fscanf(time_f,'%f;',[1,40]);
time_data_prev = fscanf(time_f_prev,'%f;',[1,40]);
iterations = fscanf(iter_f,'%d;',[1,10]);
fclose(v_x_acc);
fclose(v_x_approx);
fclose(time_f);
fclose(iter_f);
for i = 1:number_of_tests
    tmp = all_vector_x_accurate(:,i)-all_vector_x_approx(:,i);
    err(i) = norm(tmp)/norm(all_vector_x_accurate(dimension,i));
end

for m = 1:10
    epsilon(m) = 10.^(-(m+4));
end
num_para = [1:10];
figure;
plot (num_para,err);

hold on
grid on
title('relative error from num of reductions dependence')
xlabel ('num of divisions matrix')
ylabel ('relative error || x - x* || / || x* ||')

figure;
diff_dimension = [50:50:2000];
% cftool
loglog(diff_dimension,time_data)
hold on
grid on
loglog(diff_dimension,time_data_prev)
legend({'test curve','test curve prev lab 2 '},'Location','northwest')
title('time - dimension dependence')
xlabel ('DIMENSION')
ylabel ('TIME')

figure;
semilogx (epsilon,iterations);

hold on
grid on
title('epsilon - iterations dependence')
xlabel ('10^{-15} < eps < 10^{-5}')
ylabel ('num of iterations')
