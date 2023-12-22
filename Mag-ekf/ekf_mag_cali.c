/*** ekf_mag_cali.c**/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "mex.h"

#define DEBUG_MATLAB 1

#ifdef DEBUG_MATLAB

#define DEBUG_Q                             0               //打印矩阵Q[0][0] Q[1][1] Q[2][2]
#define DEBUG_H                             0               //打印H矩阵
#define DEBUG_P                             0               //打印P矩阵
#define DEBUG_X_NOW                         0               //打印X_Now矩阵
#define DEBUG_EKF_W                         1               //打印软铁标定矩阵 EKF_W[3][3] 
#define DEBUG_EKF_V                         1               //打印硬铁标定矩阵 EKF_V[3] 
#define DEBUG_P_INIT                        0               //打印初始P矩阵

#define DEBUG_X_PREDICT                     0               //打印x预测矩阵
#define DEBUG_YK                            0               //打印Yk矩阵
#define DEBUG_INNOVATION                    0               //打印innovation矩阵
#define Print_wile                          0               //打印循环次数
#define Print_plot                          0               //打印plot
#endif

#define N_STATE 12

float dt = 0.01;
float mrw = 24;         //磁场强度的随机游走
float wrm = 1.1/180*3.1415926535;   //角速度的随机游走
int   phi = 200;
double Ak3[3][3];
float Ak[3][3];                 //由角速度构成的反对称矩阵
float P[12][12];                //状态协方差矩阵
float Q[12][12];                //误差协方差矩阵
float X_Pre[12];                //状态转移阵
float X_Now[12];                //状态转移阵
float B_Now[3];                 //B

float EKF_W[3][3];      //软铁干扰
float EKF_V[3];         //硬铁干扰

float mag_last_data[3];
float mag_pre_data[3];       //预测出来的磁力计数据
float gyro_last_data[3];
static int ceshi = 0;
void printMatrix(int rows, int cols,float matrix[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // 使用 %4d 控制整数的打印宽度为4，保持间距一致
            printf("%.4f ", matrix[i][j]);
        }
        printf("\n");  // 换行到下一行
    }
    printf("\n");  // 换行到下一行
}
void ceshi_printf(int x, int rows, int cols, float matrix[rows][cols])
{
    if(ceshi == x)
    printMatrix(rows,cols,matrix);
}
void subtractMatrices(float A[12][12], float B[12][12], float result[12][12]) {
    int rows=12, cols=12;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
}
void addMatrices(float A[3][3], float B[3][3], float result[3][3]) {
    int rows=3, cols=3;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
}
void scalarMultiply(int rows, int cols, float matrix[rows][cols], float scalar) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] *= scalar;
        }
    }
}
// 3 12
void matrix_transpose(int m, int n, float A[][n], float result[][m]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result[j][i] = A[i][j];
        }
    }
}
void matrix_transpose1(int m, int n, float A[][n], float result[][m]) {
    float temp[n][m];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            temp[j][i] = A[i][j];
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = temp[i][j];
        }
    }
}

void matrix_inverse(float mat[3][3], float result[3][3]) {
    float det = mat[0][0] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]) -
                mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]) +
                mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);

    if (fabs(det) < 1e-10) {
        // 矩阵不可逆
        return;
    }

    float inv_det = 1.0 / det;

    result[0][0] = (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]) * inv_det;
    result[0][1] = (mat[0][2] * mat[2][1] - mat[0][1] * mat[2][2]) * inv_det;
    result[0][2] = (mat[0][1] * mat[1][2] - mat[0][2] * mat[1][1]) * inv_det;
    result[1][0] = (mat[1][2] * mat[2][0] - mat[1][0] * mat[2][2]) * inv_det;
    result[1][1] = (mat[0][0] * mat[2][2] - mat[0][2] * mat[2][0]) * inv_det;
    result[1][2] = (mat[0][2] * mat[1][0] - mat[0][0] * mat[1][2]) * inv_det;
    result[2][0] = (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]) * inv_det;
    result[2][1] = (mat[0][1] * mat[2][0] - mat[0][0] * mat[2][1]) * inv_det;
    result[2][2] = (mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0]) * inv_det;
}
void matrix_normal(float mat[3][3]) 
{
    float det = mat[0][0] * (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2]) -
                mat[0][1] * (mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2]) +
                mat[0][2] * (mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1]);

    if (fabs(det) > 1e-6) {
        float inv_det = 1.0 / det;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                mat[i][j] *= inv_det;
            }
        }
    } else {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                mat[i][j] = (i == j) ? 1.0 : 0.0;
            }
        }
    }
}

void matrix_multiply(int m, int n, int p, float A[][n], float B[][p], float result[][p]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            result[i][j] = 0.0;
            for (int k = 0; k < n; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matrix_vector_multiply(int m, int n, float A[][n],const float* x, float result[m]) {
    for (int i = 0; i < m; i++) {
        result[i] = 0.0;
        for (int j = 0; j < n; j++) {
            result[i] += A[i][j] * x[j];
        }
    }
}
void Q_update(float compass_data[3])
{
    memset(Q, 0, N_STATE * N_STATE * sizeof(float));
    Q[0][0] = (wrm*phi*dt*(compass_data[1] + compass_data[2]))  *  (wrm*phi*dt*(compass_data[1] + compass_data[2]));
	Q[1][1] = (wrm*phi*dt*(compass_data[0] + compass_data[2]))  *  (wrm*phi*dt*(compass_data[0] + compass_data[2]));
	Q[2][2] = (wrm*phi*dt*(compass_data[0] + compass_data[1]))  *  (wrm*phi*dt*(compass_data[0] + compass_data[1]));
    #if DEBUG_Q
        mexPrintf("Q[0][0] : %f, Q[1][1] : %f, Q[2][2] : %f\n",Q[0][0],Q[1][1],Q[2][2]);
    #endif    
}

void P_init(void)
{
    memset(P, 0, N_STATE * N_STATE * sizeof(float));
    P[0][0] = 500.0f;
	P[1][1] = 500.0f;
	P[2][2] = 500.0f;

	P[3][3] = 1e-4f;
	P[4][4] = 1e-4f;
	P[5][5] = 1e-4f;
	P[6][6] = 1e-4f;
	P[7][7] = 1e-4f;
	P[8][8] = 1e-4f;

	P[9][9] = 500.0f;
	P[10][10] = 500.0f;
	P[11][11] = 500.0f;

    #if DEBUG_P_INIT
        mexPrintf("P_init: ");
        for(int i=0;i<N_STATE;i++)
        {
            for(int j=0;j<N_STATE;j++)
            {
                mexPrintf(" %f ",P[i][j]);
            }
        }
        mexPrintf("\n");
    #endif
}

void X_Init(void)
{
    memset(EKF_W, 0, 3 * 3 * sizeof(float));
    for(int i=0;i<3;i++)
    {
        mag_last_data[i] = 1.0f;
        gyro_last_data[i] = 1.0f;
        EKF_W[i][i] = 1.0f;
        EKF_V[i] = 0.0f;
    }
}

void X_Predict(float compass_data[3], float gyro[3], float dt)
{
    float Wx[3][3]={0};
    float w_calX_Ak[3][3]={0};
    float w_calX_Ak_scaled[3][3]={0};
//     for(int i=0;i<3;i++)
//     {
//          Ak3[i][i] =  1.0f;       
//     } 
   //构建反对称矩阵,equ 6 
    /*      0        */  Wx[0][1] = -gyro[2]; Wx[0][2] = gyro[1];
    Wx[1][0] =  gyro[2]; /*      0        */  Wx[1][2] = -gyro[0];
    Wx[2][0] =  -gyro[1]; Wx[2][1] =  gyro[0]; /*      0        */
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) {
                Ak[i][j] = 1.0;
            } else {
                Ak[i][j] = 0.0;
            }
        }
    }    
    matrix_multiply(3, 3, 3, Wx, Ak, w_calX_Ak);  //单位阵和对角线为相乘无意义，省略
    // 乘以常数 0.01   
    scalarMultiply(3, 3, w_calX_Ak, 0.01);   
    // 相加到 Ak  
    addMatrices(Ak,w_calX_Ak,Ak); 
    matrix_normal(Ak);                        //Ak = matrix_normal(Ak);
    matrix_transpose1(3,3,Ak,Ak);                //Ak = Ak';

    matrix_vector_multiply(3,3,Ak,compass_data,mag_pre_data); //h_p_pre   = Ak * h_p_last;  
    
    for(int i=0;i<3;i++)
    {
        X_Pre[i] = mag_pre_data[i];
        X_Pre[i+3] = EKF_W[i][i];
        X_Pre[i+9] = EKF_V[i];
    }
    //软铁干扰矩阵上三角赋值更新
    X_Pre[6] = EKF_W[0][1];
    X_Pre[7] = EKF_W[0][2];
    X_Pre[8] = EKF_W[1][2]; 

    #if DEBUG_X_PREDICT
        mexPrintf("X_PREDICT: ");
        for(int i=0;i<N_STATE;i++)
        {
            mexPrintf(" %f ",X_Pre[i]);
        }
        mexPrintf("\n");
    #endif
}

void P_Predict(float compass_data[3], float gyro[3], float dt)
{
    float F[N_STATE][N_STATE]={0};
    float F_T[N_STATE][N_STATE]={0};
    float temp[12][12]={0};
    memset(F, 0, N_STATE * N_STATE * sizeof(float));

     for(int i=0;i<3;i++)
     {
         for(int j=0;j<3;j++)
         F[i][j] = Ak[i][j];
     }

	F[3][3] = 1.0f;
	F[4][4] = 1.0f;
	F[5][5] = 1.0f;
	F[6][6] = 1.0f;
	F[7][7] = 1.0f;
	F[8][8] = 1.0f;
	F[9][9] = 1.0f;
	F[10][10] = 1.0f;
	F[11][11] = 1.0f;
    
    matrix_multiply(12,12,12,F,P,temp);
    matrix_transpose(12,12,F,F_T);   
    matrix_multiply(12,12,12,temp,F_T,P);  
    
	for (int i = 0; i < N_STATE; i++)
	{
        for(int j = 0; j < N_STATE; j++)
        {
            P[i][j] =P[i][j] + Q[i][j];         //equ 20
        }
	}
    #if DEBUG_P
        mexPrintf("P: ");
        for(int i=0;i<12;i++)
        {
            for(int j=0;j<12;j++)
            {
                mexPrintf(" %f ",P[i][j]);
            }
        }
        mexPrintf("\n");
    #endif
}

void plot(int n,int m, float A[n][m])
{
    mexPrintf("plot: ");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            mexPrintf(" %f ",A[i][j]);
        }
        mexPrintf("\n");
    }
    mexPrintf("\n");
}

void plot1(int n, float A[n])
{
    mexPrintf("plot1111: ");
    for(int i=0;i<n;i++)
    {
        mexPrintf(" %f ",A[i]);
    }
    mexPrintf("\n");
}
void EKF_Update(float compass_data[3],float dt)
{
    float R[3][3]={0};
    float H[3][12]={0};
    float K[12][3]={0};
    float Temp[3][12]={0};
    float Temp1[12][3]={0};
    float H_T[12][3]={0};
    float Sk[3][3]={0};
    float Sk_Inverse[3][3]={0};
    float Yk[3]={0};
    float mag_half_cali[3]={0};
    float innovation[12]={0};
    float Temp2[12][12]={0};
    float eye[12][12]={0};

    float P_N_Temp[12][12]={0};
    float P_N_eye[12][12]={0};
    float P_N_sub[12][12]={0};
    float P_N_new[12][12]={0};

    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if( i == j)
                R[i][j] = mrw * mrw;                   //Rk  = mrw^2 * eye(3);
            else
                 R[i][j] = 0;
        }
    }
    
    memset(H, 0, 12 * 3 * sizeof(float));
    for(int i=0;i<3;i++)
    {
       for(int j=0;j<3;j++)
       {
            H[i][j] = EKF_W[i][j];          //hk  = [W_last hWk eye(3)];   
       }
       H[i][i+3] = mag_pre_data[i];
       H[i][i+9] = 1.0f;
    }
    H[0][6] = mag_pre_data[1];
    H[0][7] = mag_pre_data[2];
    H[1][6] = mag_pre_data[0];
    H[1][8] = mag_pre_data[2];
    H[2][7] = mag_pre_data[0];
    H[2][8] = mag_pre_data[1];
    #if DEBUG_H
        mexPrintf("H: ");
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<12;j++)
            {
                mexPrintf(" %f ",H[i][j]);
            }
        }
        mexPrintf("\n");
    #endif

    matrix_multiply(3,12,12,H,P,Temp);
    matrix_transpose(3,12,H,H_T);
    float Sk_Temp[3][3];
    matrix_multiply(3,12,3,Temp,H_T,Sk_Temp);
    addMatrices(Sk_Temp,R,Sk);                                 //Sk        = hk * P_pre * hk' + Rk;

    matrix_multiply(12,12,3,P,H_T,Temp1);
    matrix_inverse(Sk,Sk_Inverse);
    matrix_multiply(12,3,3,Temp1,Sk_Inverse,K);                //Kk        = P_pre * hk' / Sk;
    
    #if Print_plot
    plot(12,3,K);
    #endif
    matrix_vector_multiply(3,3,EKF_W,mag_pre_data,mag_half_cali);
    for(int i=0;i<3;i++)
    {
        Yk[i] = compass_data[i] - mag_half_cali[i] - EKF_V[i];
    }
    //     yk   = h_p_now - W_last * h_p_pre - b_last; 
    #if DEBUG_YK
        mexPrintf("Yk: %f %f %f\n",Yk[0],Yk[1],Yk[2]);
    #endif   
    matrix_vector_multiply(12,3,K,Yk,innovation);
    #if DEBUG_INNOVATION
        mexPrintf("innovation: ");
        for(int i=0;i<12;i++)
        {
            mexPrintf(" %f ",innovation[i]);
        }
        mexPrintf("\n");
    #endif
    for(int i=0;i<12;i++)
    {
        X_Now[i] = X_Pre[i] + innovation[i];        //X_now = X_pre + Kk * yk;
        eye[i][i]= 1.0f;
    }
    #if DEBUG_X_NOW
        mexPrintf("X_Now: ");
        for(int i=0;i<12;i++)
        {
            mexPrintf(" %f ",X_Now[i]);
        }
        mexPrintf("\n");
    #endif
    matrix_multiply(12,3,12,K,H,Temp2);
    #if 0
        mexPrintf("K: ");
        for(int i=0;i<12;i++)
        {
            for(int j=0;j<3;j++)
            {
                mexPrintf(" %f ",K[i][j]);
            }
        }
        mexPrintf("\n");
    #endif
    matrix_multiply(12,3,12,K,H,P_N_Temp);    
    for(int i=0; i<12; i++)
            P_N_eye[i][i] = 1.0f;
    subtractMatrices(P_N_eye,P_N_Temp,P_N_sub);  
    matrix_multiply(12,12,12,P_N_sub,P,P_N_new);
    for(int i = 0; i < 12; i++)
        for(int j = 0; j < 12; j++)
            P[i][j] = P_N_new[i][j];  //P_now     = (eye(12) - Kk * hk) * P_pre;
    float balance = pow(fabs(X_Now[3] * X_Now[4] * X_Now[5]), 1.0 / 3.0);        //balance  = abs(W_last(1,1) * W_last(2,2) * W_last(3,3))^(1/3);

    // mexPrintf("balance: %f\n",balance);
    //更新软铁，硬铁标定参数
    B_Now[0] = X_Now[0] / balance;B_Now[1] = X_Now[1] / balance; B_Now[2] = X_Now[2] / balance;
    EKF_W[0][0] = X_Now[3] / balance; EKF_W[0][1] = X_Now[6] / balance; EKF_W[0][2] = X_Now[7] / balance; 
    EKF_W[1][0] = X_Now[6] / balance; EKF_W[1][1] = X_Now[4] / balance; EKF_W[1][2] = X_Now[8] / balance; 
    EKF_W[2][0] = X_Now[7] / balance; EKF_W[2][1] = X_Now[8] / balance; EKF_W[2][2] = X_Now[5] / balance; 
    EKF_V[0]=X_Now[9]; EKF_V[1]=X_Now[10]; EKF_V[2]=X_Now[11];
    
}
void EKF_FUNSION(double compass_datain1,double compass_datain2,double compass_datain3, double gyro_datain1,double gyro_datain2,double gyro_datain3
,double compass_datain1_now,double compass_datain2_now,double compass_datain3_now)
{
    static int ekf_init_state=0;
    float compass_data[3]={0};
    float compass_data_now[3]={0};
    float gyro[3]={0};
    //降落后需复位，待写..
    compass_data[0] = compass_datain1;
    compass_data[1] = compass_datain2;
    compass_data[2] = compass_datain3;
    gyro[0] = gyro_datain1;
    gyro[1] = gyro_datain2;
    gyro[2] = gyro_datain3;
    compass_data_now[0] = compass_datain1_now;
    compass_data_now[1] = compass_datain2_now;
    compass_data_now[2] = compass_datain3_now;
    
    if(isnan(compass_data[0]) || isnan(compass_data[1]) || isnan(compass_data[2]) || isnan(gyro[0]) || isnan(gyro[1]) || isnan(gyro[2]))
    {
        mexPrintf("data is nan.\n");
        mexEvalString("drawnow;");          //立即显示
    }

    if(!ekf_init_state) //初始化
    {
        ekf_init_state = 1;
        P_init();
        X_Init();
        // X_Predict(mag_last_data,gyro_last_data,dt);
        // EKF_Update(compass_data,dt);
        // mexPrintf("ekf_init_state.\n");
        // mexEvalString("drawnow;");
    }
    else{     
        if(ekf_init_state == 1){
            ekf_init_state = 2;
        Q_update(mag_last_data);
         X_Predict(mag_last_data,gyro_last_data,dt);
        P_Predict(mag_last_data,gyro_last_data,dt);
        }
        else
        {
            Q_update(B_Now);
             X_Predict(B_Now,gyro_last_data,dt);
            P_Predict(B_Now,gyro_last_data,dt);
        }
  
        if(1) //磁力计正常更新，陀螺正常更新
        {
            EKF_Update(compass_data,dt);
        }
    }
    //保存k-1时刻的数据
    for(int i=0;i<3;i++)
    {
        mag_last_data[i] = compass_data[i];
        gyro_last_data[i] = gyro[i];
    }
}
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) 
{
    // 检查输入参数
    if (nrhs != 6) {
        mexErrMsgIdAndTxt("mexFunction:invalidNumInputs", "Three input arguments are required.");
    }
    double mag1_dataa;double mag2_dataa;double mag3_dataa;
    double mag1_dataa_now;double mag2_dataa_now;double mag3_dataa_now;
    double gyro1_dataa;double gyro2_dataa;double gyro3_dataa;
    // 获取输入矩阵
    double* mag1_data = mxGetPr(prhs[0]);
    double* mag2_data = mxGetPr(prhs[1]);
    double* mag3_data = mxGetPr(prhs[2]);
    double* gyro1_data = mxGetPr(prhs[3]);
    double* gyro2_data = mxGetPr(prhs[4]);
    double* gyro3_data = mxGetPr(prhs[5]);
    int mag_numRows = mxGetM(prhs[0]);
    int gyro_numRows = mxGetM(prhs[3]);

    plhs[0] = mxCreateDoubleMatrix(3, 3, mxREAL);
    double* EKF_W_OUTPUT = mxGetPr(plhs[0]);
    plhs[1] = mxCreateDoubleMatrix(1, 3, mxREAL);
    double* EKF_V_OUTPUT = mxGetPr(plhs[1]);
    for (int i = 0; i < 3666; i++) //mag_numRows
    {      
        #if Print_wile
        mexPrintf("第 %d 次循环\n", i);
        #endif
         mag1_dataa_now = mag1_data[i+1];mag2_dataa_now = mag2_data[i+1];mag3_dataa_now = mag3_data[i+1];
        mag1_dataa = mag1_data[i];mag2_dataa = mag2_data[i];mag3_dataa = mag3_data[i];
        gyro1_dataa = gyro1_data[i];gyro2_dataa = gyro2_data[i];gyro3_dataa = gyro3_data[i];
        EKF_FUNSION(mag1_dataa,mag2_dataa,mag3_dataa,gyro1_dataa,gyro2_dataa,gyro3_dataa,mag1_dataa_now,mag2_dataa_now,mag3_dataa_now);
        #if DEBUG_EKF_W  
        mexPrintf("EKF_W :");
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                mexPrintf(" %f ", EKF_W[i][j]);
            }
        }
        mexPrintf("\n");
    #endif
    #if DEBUG_EKF_V  
        mexPrintf("EKF_V :");
        for(int i=0;i<3;i++)
        mexPrintf(" %f ", EKF_V[i]);
        mexPrintf("\n");
    #endif    
    }    
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            EKF_W_OUTPUT[i * 3 + j] = EKF_W[i][j];
        }
        EKF_V_OUTPUT[i]= EKF_V[i];
    }
    //将输出保存到工作区
    mexPutVariable("base", "EKF_W_C", plhs[0]);
    mexPutVariable("base", "EKF_V_C", plhs[1]);
}