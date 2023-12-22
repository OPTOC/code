%% format
close all
clear
file_path = 'compass2.xlsx';
%% load the dat
[data_test] = xlsread(file_path);
mag_test = data_test(:,1:3);

testlength      = size( data_test, 1 );
       
[M]          = xlsread (file_path);                                         % �����ʼ����
data.b_p     = M(:,1:3);                                                    % �����Ʋ���ֵ����λΪmG
data.w       = M(:,4:6);                                                    % �����ǲ���ֵ����λrad/s
data.dt      = 0.01;                                                        % ����ʱ��������λs
data.mrw     = 24;   %33     30                                             % �ų�b��random walks����λΪmG
data.wrw     = 1.1/180*pi;                                                  % ���ٶ�w��random walks,��λΪdegree/��s^1/2��                                   % ��������
data.m       = size( data.b_p, 1 );
data.phi     = 200;  %325                                                   % equ 15�еĲ���,��ʾ�����ݵ����ó̶ȣ�Խ����Ϊ�������Խ��
data.P       = [500*eye(3) zeros(3,6)  zeros(3);
                zeros(6,3) 1e-4*eye(6) zeros(6,3);
                zeros(3)   zeros(3,6)  500*eye(3)];                         % �������
W = eye(3);
V = [0 0 0]';
%% calibrated gyroscope measurement at time k-1��equ.16
w_cal        = data.w;

%% Select correction interval
% 5s movement data for calibration
start       = 0;
range       = start+1:1:start+1+testlength - 2 ;
% start       = 0;
% range       = start+1:1:start+1+ 1790;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% EKF Calibration
k = 1;
for i = range
    %% make the datain
    datain.h_p1       = data.b_p(i+1,:)'; %����������
    datain.h_p0       = data.b_p(i,:)';
    datain.dt         = data.dt;
    datain.phi        = data.phi;
    datain.mrw        = data.mrw;
    datain.wrw        = data.wrw;   
    datain.w_cal      = w_cal(i,:);
    if k == 1 
    % Setting the initial value ���ó�ʼֵ
        datain.W      = eye(3); 
        datain.V      = [0 0 0]';
        datain.P      = data.P;
        datain.h_p0   = datain.W ^(-1) * (datain.h_p0 - datain.V);
    else
    % make the value equal to the value at last time ��ֵ��һ�ε����ֵ
        datain.W      = dataout.W;
        datain.V      = dataout.V;
        datain.P      = dataout.P; 
        datain.h_p0   = dataout.B; 
    end
    
    %% EKF
    [dataout] = fun_MagCal_EKF(datain);
    
    %% load the output ��ȡ���
    B_cal_EKF(k,:)    = dataout.B;
    W_cal_EKF(:,:,k)  = [dataout.W(1,1) dataout.W(1,2) dataout.W(1,3);
                         dataout.W(1,2) dataout.W(2,2) dataout.W(2,3);
                         dataout.W(1,3) dataout.W(2,3) dataout.W(3,3)];
    V_cal_EKF(k,:)    = dataout.V;
    P_cal_EKF(k,:)    = [dataout.P(1,1) dataout.P(4,4) dataout.P(5,5) dataout.P(10,10)];
    h_pre_EKF(k,:)    = dataout.h_p_pre;
    Kk(:,:,k)    = dataout.Kk;

    k = k + 1;
end
%% output
EKF_W = W_cal_EKF(:,:,end); %��ž���
EKF_V = V_cal_EKF(end,:)';   %Ӳ�ž���
figure 
plot(V_cal_EKF(:,1))
% ��ʾ���
fprintf( '��ž��� EKF_W:\n  %g %g %g\n  %g %g %g\n  %g %g %g\n',EKF_W);
fprintf( 'Ӳ��ʸ�� EKF_V:\n  %g %g %g\n',EKF_V);

%
% figure;
% plot3(mag_test(:,1),mag_test(:,2),mag_test(:,3));
% hold on;
% plot3(B_cal_EKF(:,1),B_cal_EKF(:,2),B_cal_EKF(:,3));
% legend('raw-data','cali-data');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if 1
%% Ellipsoid Fitting
h = 1;
for i = range 
    dataElli(h,:) = data.b_p(i,:);
    h = h + 1; 
end
[Elli_Winv, Elli_V, Elli_B, Elli_E] = f_Mag_Ellipsoid_Fit(dataElli,10);
% ��ʾ���
fprintf( '��ž��� Elli_Winv:\n  %g %g %g\n  %g %g %g\n  %g %g %g\n',Elli_Winv);
fprintf( 'Ӳ��ʸ�� Elli_V:\n  %g %g %g\n',Elli_V);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% compare

for i= 1:testlength
    normdata(i,:)      = norm(mag_test(i,:));

    B_EKF_WV(i,:)      = EKF_W^(-1)*(mag_test(i,:)' - EKF_V);
    normdata_EKF(i,:)  = norm(B_EKF_WV(i,:));

    B_Elli_WV(i,:)     = Elli_Winv * (mag_test(i,:)' - Elli_V);
    normdata_Elli(i,:) = norm(B_Elli_WV(i,:));

%     B_LM_WV(i,:)        = mag_cali * (mag_test(i,:)' - offset);
end

%% ��֤����
num_data = xlsread(file_path);

column1_data = num_data(:, 1); % ��һ�е���ֵ����
column2_data = num_data(:, 2); % �ڶ��е���ֵ����
column3_data = num_data(:, 3); % �����е���ֵ����

compass_data_raw = [column1_data, column2_data, column3_data];


figure;
plot3(compass_data_raw(:,1),compass_data_raw(:,2),compass_data_raw(:,3),'r');
legend('rawdata');
hold on;
figure;
axis equal;
plot3(B_EKF_WV(:,1),B_EKF_WV(:,2),B_EKF_WV(:,3),'b');
hold on;
plot3(B_Elli_WV(:,1),B_Elli_WV(:,2),B_Elli_WV(:,3),'g');
% hold on;
% plot3(B_LM_WV(:,1),B_LM_WV(:,2),B_LM_WV(:,3),Color='r');
legend('ekf-data','elli-data');
% legend('ekf-data','elli-data','lm-data');

time_out=1;
i=0;
while(time_out)
    i=i+1;
    if i>=length(column3_data)
        time_out=0;
    end
    mag_mod_raw(i,1) = sqrt(compass_data_raw(i,1)^2+compass_data_raw(i,2)^2+compass_data_raw(i,3)^2);
    matlab_mag_mod_ekf(i,1) = sqrt(B_EKF_WV(i,1)^2+B_EKF_WV(i,2)^2+B_EKF_WV(i,3)^2);
    matlab_mag_mod_elli(i,1) = sqrt(B_Elli_WV(i,1)^2+B_Elli_WV(i,2)^2+B_Elli_WV(i,3)^2);
end
figure;
plot(mag_mod_raw);
hold on;
plot(matlab_mag_mod_ekf);
hold on;
plot(matlab_mag_mod_elli);
legend('magmod-raw','magmod-cali-ekf','magmod-cali-elli');


% figure
% plot3(h_pre_EKF(:,1),h_pre_EKF(:,2),h_pre_EKF(:,3),'.')
% hold on
% plot3(data.b_p(range,1),data.b_p(range,2),data.b_p(range,3),'.')
% hold on 
% % plot3(B_cal_EKF(:,1),B_cal_EKF(:,2),B_cal_EKF(:,3),'.')
% axis equal
% grid on 



%% comppute the magnetic field strength ����ų�ǿ��
Bfield_EKF  = mean(normdata_EKF);
Bfield_Elli = mean(normdata_Elli);
Bfield_raw      = mean(normdata);
% standard = 50 * ones(testlength ,1);
standard = ones(testlength ,1);

Q_EKF = (Bfield_raw - Bfield_EKF) / Bfield_raw;                 %����������У׼Ч���ķ�ʽ��Խ��Խ��
Q_Elli = (Bfield_raw - Bfield_Elli) / Bfield_raw;
quality1_EKF  = std(normdata_EKF) / Bfield_EKF  * 100                %RSD ��Ա�׼�ԽС��ɢ�̶�ԽС
quality1_Elli = std(normdata_Elli) / Bfield_Elli * 100

difference_raw = normdata-standard;
difference_EKF = normdata_EKF-standard;
difference_Elli = normdata_Elli-standard;
figure
% plot(difference_raw,'r');hold on 
plot(difference_EKF*100,'b');hold on 
plot(difference_Elli*100,'g');hold on 
% legend('ԭʼ����','EKF������','Elli������')
legend('EKF������','Elli������')
xlabel('ʱ��(unit:0.01s)')
ylabel('����(unit:mG)')
figure;
plot(difference_EKF - difference_Elli);
legend('dis-err')

quality2_raw  = mean(normdata-standard);
quality2_EKF  = mean(normdata_EKF-standard);
quality2_Elli = mean(normdata_Elli-standard);

figure
grid on
[x, y, z] = ellipsoid(0,0,0,Bfield_EKF,Bfield_EKF,Bfield_EKF);
mesh(x, y, z, 'FaceAlpha', 0.1, 'EdgeColor', 'k');
hold on
% [~, X0, ~] = EllipsoidFitting(mag_test(:,1),mag_test(:,2),mag_test(:,3), 1, 1);
[~, X_EKF, ~] = EllipsoidFitting( B_EKF_WV(:,1) , B_EKF_WV(:,2) , B_EKF_WV(:,3), 1, 2);
[~, X_Elli, ~] = EllipsoidFitting( B_Elli_WV(:,1),B_Elli_WV(:,2),B_Elli_WV(:,3), 1, 3);
% legend('����ų�����','ԭʼ����','EKF����','Elli����');
legend('����ų�����','EKF����','Elli����');
plot3(B_EKF_WV(:,1),B_EKF_WV(:,2),B_EKF_WV(:,3),'b');
hold on;
plot3(B_Elli_WV(:,1),B_Elli_WV(:,2),B_Elli_WV(:,3),'g');

xlabel('X (unit:mG)')
ylabel('Y (unit:mG)')
zlabel('Z (unit:mG)')
% plot3(data.b_p(:,1),data.b_p(:,2),data.b_p(:,3),'r.');hold on
% plot3(data.b_p(range,1),data.b_p(range,2),data.b_p(range,3),'ys');hold on
axis vis3d;
axis equal;
grid on

% max_err = max(abs(difference_EKF*100 - difference_Elli*100));
% fprintf( '������ֵ %f \n',max_err);
% figure;
% plot(V_cal_EKF(:,1))
% s = [2 -1 0;
%      0 1 2;
%      1 1 3];
%  s_inv = inv(s);
% disp(s_inv);
end






