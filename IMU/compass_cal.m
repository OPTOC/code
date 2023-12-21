clc
file_path = 'compass2.xlsx';
num_data = xlsread(file_path);

mag1_data = num_data(:, 1); % 第一列的数值数据
mag2_data = num_data(:, 2); % 第二列的数值数据
mag3_data = num_data(:, 3); % 第三列的数值数据


gyro1_data = num_data(:, 4); 
gyro2_data = num_data(:, 5);
gyro3_data = num_data(:, 6); 
gyro3_data = num_data(:, 6); 

gcc -compatibleArrayDims ekf_mag_cali.c;

ekf_mag_cali(mag1_data,mag2_data,mag3_data,gyro1_data,gyro2_data,gyro3_data);