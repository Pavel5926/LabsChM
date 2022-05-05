filename_vector_x_accurate = 'D:\ChislenniyeMetodi\Lab2\MATLAB_EXPORT_Vector_X_ACCURATE.csv';
filename_vector_x_approx = 'D:\ChislenniyeMetodi\Lab2\C_EXPORT_Vector_X_APPROX.csv';

filename_vector_x_accurate_SECOND = 'D:\ChislenniyeMetodi\Lab2\MATLAB_EXPORT_Vector_X_ACCURATE_SECOND.csv';
filename_vector_Bchanged_SECOND =  'D:\ChislenniyeMetodi\Lab2\MATLAB_EXPORT_Vector_B_SECOND.csv';
filename_vector_dB_SECOND = 'D:\ChislenniyeMetodi\Lab2\MATLAB_EXPORT_Vector_dB_SECOND.csv';
filename_vector_x_approx_SECOND = 'D:\ChislenniyeMetodi\Lab2\C_EXPORT_Vector_X_APPROX_SECOND.csv';


m = fopen (filename_vector_x_accurate,'r');
k = fopen (filename_vector_x_approx,'r');

u = fopen (filename_vector_x_accurate_SECOND,'r');
h = fopen (filename_vector_x_approx_SECOND,'r');
n = fopen (filename_vector_dB_SECOND,'r');
t = fopen (filename_vector_Bchanged_SECOND, 'r');

all_vector_x_accurate=fscanf(m,'%f;',[10,10]);
all_vector_x_approx=fscanf(k,'%f;',[10,10]);

vector_x_accurate_SECOND=fscanf(u,'%f;',[10,1]);
all_vector_x_approx_SECOND=fscanf(h,'%f;',[10,10]);
B_SECOND=fscanf(t,'%f;',[10,1]);
Bchanged_SECOND = fscanf(t,'%f;',[10,10]);

fclose(m);
fclose(k);
fclose(u);
fclose(h);
fclose(n);

% Preparing the first data for the first plot 
for i = 1:10
    tmp = all_vector_x_accurate(:,i)-all_vector_x_approx(:,i);
    err(i) = norm(tmp)/norm(all_vector_x_accurate(10,i));
end
for j = 1:10
cond(j) = 10.^(j);
end
%Preparing the second data for the second plot
for y = 1:10
    tmp_SECOND = vector_x_accurate_SECOND(:,1)-all_vector_x_approx_SECOND(:,y);
    err_SECOND(y) = norm(tmp_SECOND)/norm(vector_x_accurate_SECOND(:,1));
end

for v = 1:10
       db_SECOND = Bchanged_SECOND(:,v) - B_SECOND(:,1);
       x_B_SECOND(v) = norm(db_SECOND)/norm(B_SECOND);
end

figure;
loglog (cond,err);
xlim([10 10^10])
hold on
grid on
title('relative error from cond val dependence')
xlabel ('conditional value 10 < cond < 10^9')
ylabel ('relative error || x - x* || / || x* ||')

figure;
plot (x_B_SECOND,err_SECOND);
hold on
grid on
title('relative error from cond ||dB||/||B||')
xlabel ('||dB||/||B||')
ylabel ('relative error || x - x* || / || x* ||')


