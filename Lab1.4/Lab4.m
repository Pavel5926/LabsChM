filename_matrix_A = 'D:\ChM\ChMLab4\MATLAB_EXPORT_Matrix_A.csv';
filename_param = 'D:\ChM\ChMLab4\MATLAB_EXPORT_Param.csv';
filename_eigenvalues = 'D:\ChM\ChMLab4\MATLAB_EXPORT_Eigenvalues_A.csv';
filename_sep_val_matrix_A = 'D:\ChM\ChMLab4\MATLAB_EXPORT_Sep_Val_Matrix_A.csv';
m_A = fopen(filename_matrix_A,'w');
s_A = fopen(filename_sep_val_matrix_A,'w');
par = fopen(filename_param,'w');
eigens = fopen(filename_eigenvalues,'w');
dimension = 10;
cond_val = 20;
number_of_tests = 10;
param = 1.05;
D = diag(linspace(10, cond_val, dimension));
[Q, R] = qr(rand(dimension)/100);
%Tests generation
for i = 1:number_of_tests
    fprintf(par,'%0.14f;', param);
    for j = 1:(dimension-1)
        if j == 1
            D(j, j) = 1;
            D(j+1, j+1) = D(j, j) * param;
        else 
            D(j+1, j+1) = D(j,j) * param;
        end
    end
    %R = rand(dimension)/100;
    A = (Q^-1)*D*Q;
    [PK,l] = eig(A);
    % sep val 1.5 print for the 2nd plot
    if abs(param-1.15) < 10^-6
        for j = 1:dimension
            for k= 1:dimension
                fprintf(s_A,'%0.14f;', A(j,k));
            end
            fprintf(s_A,'\n');

        end
        fprintf(s_A,'\n');
    end
    param = param + 0.1;
    % Matrix A print
    for j = 1:dimension
        for k= 1:dimension
            fprintf(m_A,'%0.14f;', A(j,k));
        end
        fprintf(m_A,'\n');
    end
    fprintf(m_A,'\n');
    
    % Eigenvalues print
    for j = 1: dimension
        fprintf(eigens,'%0.14f;',l(j,j));
    end
    fprintf(eigens,'\n');
end
 
fclose(m_A);
fclose(par);

% A = [3 3 2;5 4 3;9 2 5;];
% [R,l] = eig(A);
