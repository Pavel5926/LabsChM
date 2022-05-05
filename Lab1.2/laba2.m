%Start Matrix Creation
filename_matrix = 'D:\ChislenniyeMetodi\Lab2\MATLAB_EXPORT_Matrix_A.csv';
filename_vector_x = 'D:\ChislenniyeMetodi\Lab2\MATLAB_EXPORT_Vector_X_ACCURATE.csv';
filename_vector_b = 'D:\ChislenniyeMetodi\Lab2\MATLAB_EXPORT_Vector_B.csv';

filename_matrix_SECOND = 'D:\ChislenniyeMetodi\Lab2\MATLAB_EXPORT_Matrix_A_SECOND.csv';
filename_vector_x_SECOND = 'D:\ChislenniyeMetodi\Lab2\MATLAB_EXPORT_Vector_X_ACCURATE_SECOND.csv';
filename_vector_b_SECOND = 'D:\ChislenniyeMetodi\Lab2\MATLAB_EXPORT_Vector_B_SECOND.csv';
filename_vector_dB_SECOND = 'D:\ChislenniyeMetodi\Lab2\MATLAB_EXPORT_Vector_dB_SECOND.csv';
f = fopen (filename_matrix,'w');
g = fopen (filename_vector_x,'w');
h = fopen (filename_vector_b,'w');

p = fopen(filename_matrix_SECOND,'w');
q = fopen(filename_vector_x_SECOND,'w');
r = fopen(filename_vector_b_SECOND,'w');
s = fopen(filename_vector_dB_SECOND,'w');
%First part of work, Creation 10 A 10x10 matrixes, 10 X vector-columns and
%10 B = A*X vector-columns
n = 10;
B = zeros(10,1);
cond_val = 10;
for k = 1:10  
    [Q,R]=qr(rand(n));
    A=Q*diag(linspace(1,cond_val,n))*Q';
    cond_val = 10.^(k);
%     Matrix A Creation; A(x,y) x - row, y - column
    for i= 1:10
        for j = 1:10
            fprintf (f,'%0.14f;', A(i,j));
        end
        fprintf(f,'\n');
    end
    fprintf(f,'\n');
     X = rand(10,1);
%      Vector X Creation
    for m = 1:10
        fprintf (g, '%0.14f;', X(m,1));
    end
    fprintf(g,'\n');
% Vector B Creation
B = A*X;
for t = 1:10 
    fprintf (h,'%0.14f;',B(t,1));
end
 fprintf(h,'\n');

end
%Second part of work, Creation of ONE A 10x10 matrix, ONE X vector-column
%and 10 B= B+dB vector-column. Matrix A has cond_val2 = 100
n2 = 10;
cond_val2 = 100;
[Q2,R2]=qr(rand(n2));
A2=Q2*diag(linspace(1,cond_val2,n2))*Q2';
%     Matrix A2 Creation; A(x,y) x - row, y - column
    for w= 1:10
        for y = 1:10
            fprintf (p,'%0.16f;', A2(w,y));
        end
        fprintf(p,'\n');
    end
% Vector X2 Creation
  X2 = rand(10,1);
    for z = 1:10
        fprintf (q, '%0.16f;', X2(z,1));
    end
% Vectors B +dB Creations
B2 = A2*X2;
for u = 1:10 
    fprintf (r, '%0.16f;', B2(u,1));
end
fprintf(r,'\n');
    for d = 1:10
        dB = rand(10,1);
        for xi = 1:10 
            fprintf (s, '%0.16f;' , dB(xi,1));
        end
        fprintf(s,'\n');
        B2 = B2 + dB;
        for phi = 1:10
            fprintf (r, '%0.16f;', B2(phi,1));
        end
        fprintf(r,'\n');
    end
fclose (f);
fclose(g);
fclose(h);
fclose(p);
fclose(q);
fclose(r);

