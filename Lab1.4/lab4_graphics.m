filename_param = 'D:\ChM\ChMLab4\MATLAB_EXPORT_Param.csv';
filename_eigs_accurate = 'D:\ChM\ChMLab4\MATLAB_EXPORT_Eigenvalues_A.csv';
filename_first_eigs_approx = 'D:\ChM\ChMLab4\C_EXPORT_First_Eig.csv';
filename_first_iter = 'D:\ChM\ChMLab4\C_EXPORT_First_Iter.csv';
filename_second_eigs_approx = 'D:\ChM\ChMLab4\C_EXPORT_Second_Eig.csv';
filename_second_iter = 'D:\ChM\ChMLab4\C_EXPORT_Second_Iter.csv';
filename_f_sep_val_iter = 'D:\ChM\ChMLab4\C_EXPORT_F_Sep_Val_Iter.csv';
filename_s_sep_val_iter = 'D:\ChM\ChMLab4\C_EXPORT_S_Sep_Val_Iter.csv';
filename_f_sep_val_eig = 'D:\ChM\ChMLab4\C_EXPORT_F_Sep_Val_Eig.csv';
filename_s_sep_val_eig = 'D:\ChM\ChMLab4\C_EXPORT_S_Sep_Val_Eig.csv';
fs_E_ACC = fopen(filename_eigs_accurate,'r'); 
f_E = fopen(filename_first_eigs_approx,'r');
f_ITER = fopen(filename_first_iter,'r');
s_E = fopen(filename_second_eigs_approx,'r');
s_ITER = fopen(filename_second_iter,'r');
sep_val_f = fopen(filename_f_sep_val_iter, 'r');
sep_val_s = fopen(filename_s_sep_val_iter,'r');
sep_val_f_e = fopen(filename_f_sep_val_eig, 'r');
sep_val_s_e = fopen(filename_s_sep_val_eig,'r');

for m = 1:10
    epsilon(m) = 10.^(-(m+4));
end
par = fopen(filename_param,'r');
dimension = 10;
number_of_tests = 10;
fs_eigs_accurate = fscanf(fs_E_ACC,'%f;',[dimension, number_of_tests]);
f_eigs_approx = fscanf(f_E,'%f;',[1,dimension]);
s_eigs_approx = fscanf(s_E,'%f;',[1,dimension]);
f_iter = fscanf(f_ITER,'%d;',[dimension, number_of_tests]);
s_iter = fscanf(s_ITER,'%d;',[1,dimension]);
param = fscanf(par,'%f;',[1,dimension]);
sep_f_eig = fscanf(sep_val_f_e, '%f;',[1,dimension]);
sef_s_eig = fscanf(sep_val_s_e,'%f;',[1,dimension]);
sep_f_iter = fscanf(sep_val_f, '%f;',[1,dimension]);
sep_s_iter = fscanf(sep_val_s, '%f;',[1,dimension]);
figure;
loglog(param, f_iter);
hold on
grid on
loglog(param,s_iter);
legend({'first eig val iterations','second eig val iterations'},'Location','northeast')
title('sep.val - 1-2 eig. val dependences')
xlabel ('sep val')
ylabel ('iterations')

figure;
loglog(epsilon,sep_f_iter);
hold on
grid on
plot(epsilon,sep_s_iter);
legend({'first eig val iterations','second eig val iterations'},'Location','southwest')
title('epsilon - 1-2 eig. val dependences')
xlabel ('epsilon')
ylabel ('iterations')
