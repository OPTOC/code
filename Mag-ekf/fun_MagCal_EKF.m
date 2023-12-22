function [dataout] = fun_MagCal_EKF(datain)
%{

���룺datain ������
    datain.h_p1 ��һʱ�̴ų���У׼ֵ
    datain.h_p0 ��ʱ�̴����ƶ���
    datain.w_cal ��ʱ�������ǵ�У׼ֵ
    datain.dt ����ʱ����
    datain.phi �����ǵĿ��Ʋ���
    datain.mrw ������������׼��
    datain.wrw ������������׼��
    datain.W ��һʱ�̵���ž���
    datain.V ��һʱ�̵�Ӳ�ž���
    datain.P ��һʱ�̵ķ������

�����dataout ������
    dataout.B ��ʱ��У׼��Ĵų�����
    dataout.W ��ʱ��У׼�����ž���
    dataout.V ��ʱ��У׼���Ӳ�ž���
    dataout.P ��ʱ��У׼��ķ������
%}

persistent  cisi;
function printMatrix(rows, cols, matrix)
    for i = 1:rows
        for j = 1:cols
            fprintf('%.4f ', matrix(i, j));
        end
        fprintf('\n');
    end
    fprintf('\n');
end

function ceshi_printf(x, rows, cols, matrix)
    if x == cisi
        printMatrix(rows, cols, matrix);
    end
end
%% preparation ����׼��
h_p_now = datain.h_p1;
h_p_last = datain.h_p0;
w_cal_last = datain.w_cal; 
parameter = datain.dt*datain.phi;
mrw = datain.mrw;
wrw = datain.wrw ;
W_last = datain.W;
b_last = datain.V;
P_last = datain.P;


%% calculate the rotarion matrix Ak �����ת����
Ak = eye(3);
% w_calX����[�أ룭��] * �£㣬�룭����
w_calX = [0 -w_cal_last(3) w_cal_last(2);
          w_cal_last(3) 0 -w_cal_last(1);
          -w_cal_last(2) w_cal_last(1) 0]; 
% equ 6



% disp(Ak );
% disp(w_calX );
% disp(w_calX * Ak); 
%Ak = ( eye(3) + w_calX * dt)  
% w_calX����[�أ룭��] * �£㣬�룭��


Ak = Ak + w_calX * Ak * 0.01 ;  %equ 7  => equ12                                  % equ 12 ��ʱ��ȷ
Ak = Ak';%Ak'��Ak��ת

% fprintf("����\n"); 
% disp(Ak );
%��ת�ú��  ���ȳ˺�ת�õõ��Ľ����һ�µ�
%% equation 
h_p_pre   = Ak * h_p_last;                                                  % equ 8
% if isempty(cisi) %������
%     cisi = 1;
%     disp(" %f \n" ,Ak(:,1)*h_p_last(1));
%     disp(" %f \n" ,Ak(:,2)*h_p_last(2));
%     disp(" %f \n" ,Ak(:,3)*h_p_last(3)); 
%     disp(Ak);
%     disp(h_p_last);
%     disp(h_p_pre);
% end
X_pre     = [h_p_pre; W_last(1,1); W_last(2,2); W_last(3,3);                % equ 11
             W_last(1,2); W_last(1,3); W_last(2,3); b_last];    
if isempty(cisi) %������ 
    cisi = 1;  
else      
    cisi = cisi + 1;  
 end    
if cisi == 2
%     ceshi_printf(2,3,3,h_p_pre);
    format short;  
     disp( X_pre );     
end 
%% equation 
% parameter ��*dt  
% wrw ��
%A=[0,Z,Y;  
%   Z,0,X; 
%   Y,X,0] = AT
% AAT = [Z^2+Y^2   0      0
%        0      X^2+Z^2   0
%        0         0   X^2+Y^2]  ����Q_element = �զ�sqrt(BBT)dt
Q_element = parameter*wrw.*[(h_p_last(2)+h_p_last(3)) 0 0 
                        0 (h_p_last(1)+h_p_last(3)) 0
                        0 0 (h_p_last(1)+h_p_last(2))];
% disp(Q_element);
%is_matrix = ismatrix(Q_element);  �ж��ǲ��Ǿ���
%disp(h_p_last);
%fprintf( '����:%d\n',);
% base = parameter^2*wrw^2.*mean(h_p_last*h_p_last');
% Q_element = diag(base);

Qk        = [Q_element^2 zeros(3,9)
             zeros(9,3)  zeros(9,9)];                                       % equ15

Fk        = [Ak  zeros(3,9);
             zeros(9,3) eye(9,9)];                                          % equ 16
%yk = Zk -h(Xk-1) Zk = h(Xk) + Vk
yk        = h_p_now - W_last * h_p_pre - b_last; 

 
hWk       = [h_p_pre(1) 0 0 h_p_pre(2) h_p_pre(3) 0;
             0 h_p_pre(2) 0 h_p_pre(1) 0 h_p_pre(3);
             0 0 h_p_pre(3) 0 h_p_pre(1) h_p_pre(2)];                       % equ 18
hk        = [W_last hWk eye(3)];                                            % equ 18
 
P_pre     = Fk * P_last * Fk' + Qk;                                          % equ 20

Rk        = mrw^2 * eye(3);                                                  
Sk        = hk * P_pre * hk' + Rk;                                           % equ 21

Kk        = P_pre * hk' / Sk;                                               % equ 21

X_now     = X_pre + Kk * yk;                                                % equ 22

P_now     = (eye(12) - Kk * hk) * P_pre;                                    % equ 23
%% output the result
h_p_cal   = X_now(1:3);
W_last    = [X_now(4) X_now(7) X_now(8)
             X_now(7) X_now(5) X_now(9)
             X_now(8) X_now(9) X_now(6)];
% normalization ��һ��
balance   = abs(W_last(1,1) * W_last(2,2) * W_last(3,3))^(1/3);
% balance = trace(W_last)/3;
dataout.W = W_last / balance;
dataout.B = h_p_cal * balance;
dataout.V = X_now(10:12);
dataout.P = P_now;
dataout.h_p_pre = 0;
dataout.Kk = 0;
end
