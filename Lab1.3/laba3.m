filename_matrix_A = 'D:\ChislenniyeMetodi\LaB3\MATLAB_EXPORT_MatrixA.csv';
filename_vector_B = 'D:\ChislenniyeMetodi\LaB3\MATLAB_EXPORT_VectorB.csv';
filename_vector_X_ACCURATE = 'D:\ChislenniyeMetodi\LaB3\MATLAB_EXPORT_VectorX_ACCURATE.csv';
filename_norm_A = 'D:\ChislenniyeMetodi\LaB3\MATLAB_EXPORT_Norm_A.csv';

filename_matrix_A_SECOND = 'D:\ChislenniyeMetodi\LaB3\MATLAB_EXPORT_Matrix_A_SECOND.csv';
filename_vector_B_SECOND = 'D:\ChislenniyeMetodi\LaB3\MATLAB_EXPORT_Vector_B_SECOND.csv';

m_A = fopen(filename_matrix_A,'w');
v_B = fopen(filename_vector_B,'w');
v_X = fopen(filename_vector_X_ACCURATE,'w');
ux = fopen(filename_matrix_A_SECOND,'w');
ix = fopen(filename_vector_B_SECOND,'w');

number_of_tests = 10;
dimension = 10;
cond_val = 20;
sum = 0;
det_para = 1.5;
D = diag(linspace(10, cond_val, dimension));
    [Q, R] = qr(rand(dimension));
    A = Q*D*Q';
    A=abs(A);
    X = rand(dimension,1);
    for j = 1:dimension
        for k = 1:dimension
            if j ~= k
                sum = sum + abs(A(j, k));
            end
        end
        for v = 1:dimension
            if j ~= v
            A(j, v) = A(j, v)/(sum);
            A(v, j) = A(v, j)/(sum);
            end
        end
        sum = 0;
    end
    sum = 0;
%Matrix A generation
for i = 1:number_of_tests
    for z = 1:dimension 
        fprintf (v_X,'%0.16f;',X(z,1));
    end
    fprintf(v_X,'\n');
%     for j = 1:dimension
%         for k = 1:dimension
%             if j ~= k
%                 sum = sum + abs(A(j, k));
%             end
%         end
%         for v = 1:dimension
%             if j ~= v
%             A(j, v) = A(j, v)/(sum);
%             end
%         end
%         sum = 0;
%     end
    
    % Matrix A print
    for t= 1:dimension 
        for p = 1:dimension 
            fprintf (m_A,'%0.16f;', A(t,p));
        end
        fprintf(m_A,'\n');
    end
    fprintf(m_A,'\n');
    % Vector B creation and print 
    B = A * X;
    for d = 1:dimension 
        fprintf (v_B,'%0.16f;',B(d,1));
    end
    fprintf(v_B,'\n');
 A(i,i) = A(i,i)-0.31;
 A = A./(det_para)
 %A = abs(A);
end
t = det(A)

% Second plot time_profile data
% 
%     cond_val2 = 10;
%     dimension2 = 50;
% for t = 1:40
%     [Q,R]=qr(rand(dimension2));
%     A2=Q*diag(linspace(1,cond_val2,dimension2))*Q';
%     for w= 1:dimension2 
%         for y = 1:dimension2
%             fprintf (ux,'%0.16f;', A2(w,y));
%         end
%         fprintf(ux,'\n');
%     end
%     X2 = rand(dimension2,1); 
%     B2 = A2*X2;
%     for u = 1:dimension2
%     fprintf (ix, '%0.16f;', B2(u,1));
%     end
%     fprintf(ix,'\n');
%     dimension2 = dimension2 + 50;
% end

fclose(ux);
fclose(ix);
