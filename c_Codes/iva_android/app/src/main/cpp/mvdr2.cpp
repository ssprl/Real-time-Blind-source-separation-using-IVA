//
// Created by cxk131330 on 10/5/2017.
//

#include "mvdr2.h"
//#include "mvdr.h"
iva_parameters* newparameters(int nfft, int framelen, int frame_shift, int maxiter)
{
   iva_parameters* newparameters = (iva_parameters*)malloc(sizeof(iva_parameters));
    newparameters->sum1_r = (double*)calloc(1025,sizeof(double));
    newparameters->sum1_i = (double*)calloc(1025,sizeof(double));
    newparameters->sum2_r = (double*)calloc(1025,sizeof(double));
    newparameters->sum2_i = (double*)calloc(1025,sizeof(double));
    newparameters->nfft = nfft;
    newparameters->maxiter = maxiter;
    newparameters->frame_len = framelen;
    newparameters->frame_shift = frame_shift;
    newparameters->win= (double*)calloc(nfft,sizeof(double));
    newparameters->xwin1 = (double*)calloc(nfft,sizeof(double));
    newparameters->xwin2 = (double*)calloc(nfft, sizeof(double));
    newparameters->xn1_real = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->xn2_real = (double*)calloc(nfft/2+1, sizeof(double));
    newparameters->xn1_imag = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->xn2_imag = (double*)calloc(nfft/2+1, sizeof(double));
    newparameters->ones = (double*)calloc(100,sizeof(double));
    newparameters->x1 = (double**)calloc(nfft, sizeof(double));
    newparameters->Rxx1_real_1 = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->Rxx1_real_2 = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->Rxx1_real = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->Rxx1_imag = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->Rxx2_real = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->Rxx2_imag = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->Rxx3_real = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->Rxx3_imag = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->Rxx4_real = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->Rxx4_imag = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->aa1 = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->aa2 = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->E1_real = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->E1_imag = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->E2_real = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->E2_imag = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->E3 = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->E4 = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->Q1_real = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->Q1_imag = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->Q3_real = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->Q3_imag = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->Q2 = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->Q4 = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->W1_r = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->W2_r = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->W3_r = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->W4_r = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->W1_i = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->W2_i = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->W3_i = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->W4_i = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->Ssq_1 = (double*)calloc(100,sizeof(double));
    newparameters->Ssq_2 = (double*)calloc(100,sizeof(double));
    newparameters->Ssq1_1 = (double*)calloc(100,sizeof(double));
    newparameters->Ssq1_2 = (double*)calloc(100,sizeof(double));
    newparameters->phi1_real = (double*)calloc(100,sizeof(double));
    newparameters->phi1_imag = (double*)calloc(100,sizeof(double));
    newparameters->phi2_real = (double*)calloc(100,sizeof(double));
    newparameters->phi2_imag = (double*)calloc(100,sizeof(double));
    newparameters->dWp1_r = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->dWp1_i = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->dWp4_i = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->dWp2_i = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->dWp2_r = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->dWp3_i = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->dWp3_r = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->dWp4_r = (double*)calloc(nfft/2+1,sizeof(double));

    newparameters->dWp11_r = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->dWp11_i = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->dWp44_i = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->dWp22_i = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->dWp22_r = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->dWp33_i = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->dWp33_r = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->dWp44_r = (double*)calloc(nfft/2+1,sizeof(double));

    newparameters->w_1_r = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->w_2_r = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->w_3_r = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->w_4_r = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->w_1_i = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->w_2_i = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->w_3_i = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->w_4_i = (double*)calloc(nfft/2+1,sizeof(double));

    newparameters->fw_1_r = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->fw_2_r = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->fw_3_r = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->fw_4_r = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->fw_1_i = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->fw_2_i = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->fw_3_i = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->fw_4_i = (double*)calloc(nfft/2+1,sizeof(double));

    newparameters->w_11_r = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->w_11_i = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->w_44_r = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->w_44_i = (double*)calloc(nfft/2+1,sizeof(double));

    newparameters->S12_r=(double*)calloc(nfft/2+1,sizeof(double));
    newparameters->S12_i=(double*)calloc(nfft/2+1,sizeof(double));
    newparameters->S22_r=(double*)calloc(nfft/2+1,sizeof(double));
    newparameters->S22_i=(double*)calloc(nfft/2+1,sizeof(double));

    newparameters->X_final1_r=(double*)calloc(nfft,sizeof(double));
    newparameters->X_final1_i=(double*)calloc(nfft,sizeof(double));
    newparameters->X_final2_r=(double*)calloc(nfft,sizeof(double));
    newparameters->X_final2_i=(double*)calloc(nfft,sizeof(double));

    newparameters->sk1=(double*)calloc(160000+(2*nfft),sizeof(double));
    newparameters->sk2=(double*)calloc(160000+(2*nfft),sizeof(double));
    newparameters->v1=(double*)calloc(160000+(2*nfft),sizeof(double));
    newparameters->v2=(double*)calloc(160000+(2*nfft),sizeof(double));

    newparameters->yf1=(double*)calloc(160000,sizeof(double));
    newparameters->yf2=(double*)calloc(160000,sizeof(double));

for (int i = 0; i<(160000+(2*nfft)); i++)
        newparameters->x1[i] = (double*)calloc(2, sizeof(double));

    newparameters->xwin = (double**)calloc(nfft, sizeof(double));
    for (int i = 0; i<nfft; i++)
        newparameters->xwin[i] = (double*)calloc(2, sizeof(double));

    newparameters->Xn_1_real = (double**)calloc(nfft/2+1, sizeof(double));
    for (int i = 0; i<nfft/2+1; i++)
        newparameters->Xn_1_real[i] = (double*)calloc(100, sizeof(double));

    newparameters->Xn_2_real = (double**)calloc(nfft/2+1, sizeof(double));
    for (int i = 0; i<nfft/2+1; i++)
        newparameters->Xn_2_real[i] = (double*)calloc(100, sizeof(double));

    newparameters->Xn_1_img = (double**)calloc(nfft/2+1, sizeof(double));
    for (int i = 0; i<nfft/2+1; i++)
        newparameters->Xn_1_img[i] = (double*)calloc(100, sizeof(double));

    newparameters->Xn_2_img = (double**)calloc(nfft/2+1, sizeof(double));
    for (int i = 0; i<nfft/2+1; i++)
        newparameters->Xn_2_img[i] = (double*)calloc(100, sizeof(double));

    newparameters->Xp1_real = (double**)calloc(nfft/2+1, sizeof(double));
    for (int i = 0; i<nfft/2+1; i++)
        newparameters->Xp1_real[i] = (double*)calloc(100, sizeof(double));

    newparameters->Xp2_real = (double**)calloc(nfft/2+1, sizeof(double));
    for (int i = 0; i<nfft/2+1; i++)
        newparameters->Xp2_real[i] = (double*)calloc(100, sizeof(double));

    newparameters->Xp1_imag = (double**)calloc(nfft/2+1, sizeof(double));
    for (int i = 0; i<nfft/2+1; i++)
        newparameters->Xp1_imag[i] = (double*)calloc(100, sizeof(double));

    newparameters->Xp2_imag = (double**)calloc(nfft/2+1, sizeof(double));
    for (int i = 0; i<nfft/2+1; i++)
        newparameters->Xp2_imag[i] = (double*)calloc(100, sizeof(double));

    newparameters->S1 = (double**)calloc(nfft/2+1, sizeof(double));
    for (int i = 0; i<nfft/2+1; i++)
        newparameters->S1[i] = (double*)calloc(100, sizeof(double));

    newparameters->S2 = (double**)calloc(nfft/2+1, sizeof(double));
    for (int i = 0; i<nfft/2+1; i++)
        newparameters->S2[i] = (double*)calloc(100, sizeof(double));

    newparameters->S1_r = (double**)calloc(nfft/2+1, sizeof(double));
    for (int i = 0; i<nfft/2+1; i++)
        newparameters->S1_r[i] = (double*)calloc(100, sizeof(double));

    newparameters->S1_i = (double**)calloc(nfft/2+1, sizeof(double));
    for (int i = 0; i<nfft/2+1; i++)
        newparameters->S1_i[i] = (double*)calloc(100, sizeof(double));

    newparameters->S2_r = (double**)calloc(nfft/2+1, sizeof(double));
    for (int i = 0; i<nfft/2+1; i++)
        newparameters->S2_r[i] = (double*)calloc(100, sizeof(double));

    newparameters->S2_i = (double**)calloc(nfft/2+1, sizeof(double));
    for (int i = 0; i<nfft/2+1; i++)
        newparameters->S2_i[i] = (double*)calloc(100, sizeof(double));

    newparameters->Xmean1_real = (double*)calloc(100, sizeof(double));
    newparameters->Xmean1_imag = (double*)calloc(100, sizeof(double));

    newparameters->Xmean2_real = (double*)calloc(100, sizeof(double));
    newparameters->Xmean2_imag = (double*)calloc(100, sizeof(double));
    newparameters->b = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->c = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->D1 = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->D2 = (double*)calloc(nfft/2+1,sizeof(double));
    newparameters->enhance_signal = enhance_signal;
    return newparameters;
}


double* hanning(int n)
{
    double* w = (double *)calloc(n+1, sizeof(double));
    double* w1;
    int half;
    if (n % 2 == 0) {
        half = n / 2;
        w1 = calc_hanning(half, n);
        memcpy(w, w1, half*sizeof(double));
        for (int i = 0 ; i < half; i++)
        {
            w[i + half] = w1[half-i];

        }
    }
    else
    {
        half = (n + 1) / 2;
        w1 = calc_hanning(half, n);
        memcpy(w, w1, half * sizeof(double));
        for (int i = 0; i < half; i++)
        {
            w[i + half] = w1[half-i];
        }
    }
    return w;
}

double* calc_hanning(int m,int n)
{
    double* w = (double *) calloc(m, sizeof(double));
    double res;
    for (int i = 1; i <= m; i++) {
        res = (M_PI*2 * (i))/(n + 1);
        w[i] = 0.5 * ((double)1 - cos(res));

    }


    return w;
}
void enhance_signal(iva_parameters *iva, double *input1, double *input2, int framecounter)
{
    Transform *X1;
    Transform *X2;
    Transform *Y1;
    Transform *Y2;
    X1=newTransform(iva->nfft);
    X2=newTransform(iva->nfft);
    Y1=newTransform(iva->nfft);
    Y2=newTransform(iva->nfft);

    iva->win = hanning(iva->nfft-1);
    for (int i = 0; i < iva->nfft; i++)
    {
        iva->win[i] = iva->win[i]*2/2048;
        //printf("%.32lf\n", iva->win[i]);
    }
    iva->overlap = 0.75*iva->nfft;
    iva->shift = iva->nfft - iva->overlap;
    iva->nfreq = (iva->nfft/2)+1;
    for (int i = 0; i < iva->nfft ; i++)
    {
        iva->x1[i][0] = input1[i];
        iva->x1[i][1]= input2[i];
        //printf("%d %f\n",i, sub_data1[i]);
    }
    int n=framecounter;
        iva->sp = (n*iva->shift)+1;
        if(n<101)
        {
            for(int j =0;j<2;j++)
            {
            for(int i=0;i<iva->nfft;i++)
            {
                iva->xwin[i][j]=iva->win[i]*iva->x1[i+iva->sp-1][j];
            }
            }
            for(int i=0;i<iva->nfft;i++)
            {
               iva->xwin1[i]= iva->xwin[i][0];
                 iva->xwin2[i]= iva->xwin[i][1];
            }
            X1->doTransform(X1,iva->xwin1);
            X2->doTransform(X2,iva->xwin2);
            for(int i=0;i<iva->nfft/2+1;i++)
            {
                iva->xn1_real[i]= X1->real[i];
                iva->xn1_imag[i] = X1->imaginary[i] * (-1);
                iva->xn2_real[i]= X2->real[i];
                iva->xn2_imag[i] = X2->imaginary[i] * (-1);

            }

                for(int i=0;i<iva->nfft/2+1;i++)
                {
                    iva->Xn_1_real[i][n-1]=iva->xn1_real[i];
                    iva->Xn_2_real[i][n-1]=iva->xn2_real[i];
                    iva->Xn_1_img[i][n-1]=iva->xn1_imag[i];
                    iva->Xn_2_img[i][n-1]=iva->xn2_imag[i];
                  //  printf("%.32lf %d\n",(iva->Xn_1_real[i][n-1]),n-1);
                }

        }
        else
        {
            break;
        }


    for(int k =0; k<iva->nfreq;k++)
    {
        for(int i =0;i<100;i++)
        {
            iva->sum1_r[k] += iva->Xn_1_real[k][i];
            iva->sum1_i[k] += iva->Xn_1_img[k][i];
            iva->sum2_r[k] += iva->Xn_2_real[k][i];
            iva->sum2_i[k] += iva->Xn_2_img[k][i];
            iva->ones[i]=1;

        }

        iva->sum1_r[k] = iva->sum1_r[k]/100;
        iva->sum1_i[k] = iva->sum1_i[k]/100;
        iva->sum2_r[k] = iva->sum2_r[k]/100;
        iva->sum2_i[k] = iva->sum2_i[k]/100;


        for(int i =0;i<100;i++)
        {

            iva->Xmean1_real[i]=iva->sum1_r[k]*iva->ones[i];
            iva->Xmean1_imag[i]=iva->sum1_i[k]*iva->ones[i];
            iva->Xmean2_real[i]=iva->sum2_r[k]*iva->ones[i];
            iva->Xmean2_imag[i]=iva->sum2_i[k]*iva->ones[i];


        }
    for(int i =0;i<100;i++)
    {
        iva->Xn_1_real[k][i] = (iva->Xn_1_real[k][i] - iva->Xmean1_real[i]);
        iva->Xn_1_img[k][i] = (iva->Xn_1_img[k][i] - iva->Xmean1_imag[i]);
        iva->Xn_2_real[k][i] = (iva->Xn_2_real[k][i] -iva->Xmean2_real[i]);
        iva->Xn_2_img[k][i] = (iva->Xn_2_img[k][i] - iva->Xmean2_imag[i]);
       // printf("%.32lf\n",iva->Xn_1_real[k][i]);
    }
        for(int i =0;i<100;i++)
        {
            iva->Rxx1_real[k] += ((iva->Xn_1_real[k][i]*iva->Xn_1_real[k][i])+(iva->Xn_1_img[k][i]*iva->Xn_1_img[k][i]))/100;
            iva->Rxx2_real[k] += ((iva->Xn_1_real[k][i]*iva->Xn_2_real[k][i])+(iva->Xn_1_img[k][i]*iva->Xn_2_img[k][i]))/100;
            iva->Rxx2_imag[k] += (-(iva->Xn_1_real[k][i]*iva->Xn_2_img[k][i])+(iva->Xn_1_img[k][i]*iva->Xn_2_real[k][i]))/100;
            iva->Rxx4_real[k] += ((iva->Xn_2_real[k][i]*iva->Xn_2_real[k][i])+(iva->Xn_2_img[k][i]*iva->Xn_2_img[k][i]))/100;
        // printf("%.32lf\n",iva->Rxx1_real[i]);
        }

        iva->a=1;
        iva->b[k]= (-(iva->Rxx1_real[k]+iva->Rxx4_real[k]));
        iva->c[k]=((iva->Rxx1_real[k]*iva->Rxx4_real[k])-(iva->Rxx2_real[k]*iva->Rxx2_real[k])-(iva->Rxx2_imag[k]*iva->Rxx2_imag[k]));

        iva->D1[k] =(-iva->b[k] - sqrt(iva->b[k] * iva->b[k] - 4.0 * iva->a * iva->c[k])) / (2.0 * iva->a);
        iva->D2[k] =(-iva->b[k] + sqrt(iva->b[k] * iva->b[k] - 4.0 * iva->a * iva->c[k])) / (2.0 * iva->a);



        iva->Rxx1_real_1[k]=iva->Rxx1_real[k]-iva->D1[k];
        iva->aa1[k] = sqrt(pow(iva->Rxx1_real_1[k],2)+pow(iva->Rxx2_real[k],2)+pow(iva->Rxx2_imag[k],2));
//        if((copysignf(1.0, iva->Rxx2_real[k])==-1)&&(copysignf(1.0, iva->Rxx2_imag[k])==1))
//        {
            iva->E1_real[k] = -iva->Rxx2_real[k]/iva->aa1[k];
            iva->E1_imag[k] = -iva->Rxx2_imag[k]/iva->aa1[k];
            iva->E3[k] = iva->Rxx1_real_1[k]/iva->aa1[k];
//        }
//        else
//        {
//            iva->E1_real[k] = iva->Rxx2_real[k]/iva->aa1[k];
//            iva->E1_imag[k] = iva->Rxx2_imag[k]/iva->aa1[k];
//            iva->E3[k] = -iva->Rxx1_real_1[k]/iva->aa1[k];
       // }
        iva->Rxx1_real_2[k]=iva->Rxx1_real[k]-iva->D2[k];
        iva->aa2[k] = sqrt(pow(iva->Rxx2_real[k],2)+pow(iva->Rxx1_real_2[k],2)+pow(iva->Rxx2_imag[k],2));
        iva->E2_real[k] = -iva->Rxx2_real[k]/iva->aa2[k];
        iva->E2_imag[k] = -iva->Rxx2_imag[k]/iva->aa2[k];
        iva->E4[k] = iva->Rxx1_real_2[k]/iva->aa2[k];


        iva->D1[k]=pow(iva->D1[k],-0.5);
        iva->D2[k]=pow(iva->D2[k],-0.5);

        iva->Q1_real[k] = iva->D2[k] * iva->E2_real[k];
        iva->Q1_imag[k] = iva->D2[k] * (-iva->E2_imag[k]);
        iva->Q3_real[k] = iva->D1[k] * iva->E1_real[k];
        iva->Q3_imag[k] = iva->D1[k] * (-iva->E1_imag[k]);
        iva->Q2[k] = iva->D2[k] * iva->E4[k];
        iva->Q4[k] = iva->D1[k] * iva->E3[k];
//        iva->Q1_real[0]=-iva->Q1_real[0];
//         iva->Q1_real[iva->nfreq-1]=-iva->Q1_real[iva->nfreq-1];
//        iva->Q2[0]=-iva->Q2[0];
//        iva->Q2[iva->nfreq-1]=-iva->Q2[iva->nfreq-1];


        for(int i =0;i<100;i++)
        {
            iva->Xp1_real[k][i] = (iva->Q1_real[k]*iva->Xn_1_real[k][i])-(iva->Q1_imag[k]*iva->Xn_1_img[k][i])+(iva->Q2[k]*iva->Xn_2_real[k][i]);
            iva->Xp2_real[k][i] = ((iva->Q3_real[k]*iva->Xn_1_real[k][i])-(iva->Q3_imag[k]*iva->Xn_1_img[k][i])+(iva->Q4[k]*iva->Xn_2_real[k][i]));
            iva->Xp1_imag[k][i] = ((iva->Q1_real[k]*iva->Xn_1_img[k][i])+(iva->Q1_imag[k]*iva->Xn_1_real[k][i])+(iva->Q2[k]*iva->Xn_2_img[k][i]));
            iva->Xp2_imag[k][i] = ((iva->Q3_real[k]*iva->Xn_1_img[k][i])+(iva->Q3_imag[k]*iva->Xn_1_real[k][i])+(iva->Q4[k]*iva->Xn_2_img[k][i]));
   // printf("%.32lf\n", iva->Xp1_imag[k][i]);

        }
        iva->W1_r[k]=1;
        iva->W4_r[k]=1;

    }

    for(int iter = 0;iter<iva->maxiter;iter++)
    {
        iva->dlw=0;
        for(int k =0; k<iva->nfreq;k++)
        {
       // printf("%.32lf\n",iva->W1_i[k]);
        }
        for(int k =0; k<iva->nfreq;k++)
        {
            for(int i =0;i<100;i++)
            {
                iva->S1_r[k][i]=(iva->W1_r[k]*iva->Xp1_real[k][i])-(iva->W1_i[k]*iva->Xp1_imag[k][i])+(iva->W2_r[k]*iva->Xp2_real[k][i])-(iva->W2_i[k]*iva->Xp2_imag[k][i]);
                iva->S1_i[k][i]=(iva->W1_r[k]*iva->Xp1_imag[k][i])+(iva->W1_i[k]*iva->Xp1_real[k][i])+(iva->W2_r[k]*iva->Xp2_imag[k][i])+(iva->W2_i[k]*iva->Xp2_real[k][i]);
                iva->S2_r[k][i]=(iva->W3_r[k]*iva->Xp1_real[k][i])-(iva->W3_i[k]*iva->Xp1_imag[k][i])+(iva->W4_r[k]*iva->Xp2_real[k][i])-(iva->W4_i[k]*iva->Xp2_imag[k][i]);
                iva->S2_i[k][i]=(iva->W3_r[k]*iva->Xp1_imag[k][i])+(iva->W3_i[k]*iva->Xp1_real[k][i])+(iva->W4_r[k]*iva->Xp2_imag[k][i])+(iva->W4_i[k]*iva->Xp2_real[k][i]);
                iva->S1[k][i]=pow((sqrt(pow(iva->S1_r[k][i],2)+pow(iva->S1_i[k][i],2))),2);
                iva->S2[k][i]=pow((sqrt(pow(iva->S2_r[k][i],2)+pow(iva->S2_i[k][i],2))),2);
             // printf("%.32lf\n",iva->Xp1_real[k][i]);
            }

        }
        for(int i =0;i<100;i++)
        {
            iva->Ssq_1[i]=0;
            iva->Ssq_2[i]=0;
        }
    for(int i =0;i<100;i++)
    {
        for(int k =0; k<iva->nfreq;k++)
        {
            iva->Ssq_1[i] += iva->S1[k][i];
            iva->Ssq_2[i] += iva->S2[k][i];


        }

        iva->Ssq_1[i]=sqrt(iva->Ssq_1[i]);
        iva->Ssq_2[i]=sqrt(iva->Ssq_2[i]);
        iva->Ssq1_1[i]=pow(iva->Ssq_1[i]+1e-6,-1);
        iva->Ssq1_2[i]=pow(iva->Ssq_2[i]+1e-6,-1);

//printf("%.32lf\n",iva->Ssq1_2[i]);
    }
        for(int k =0; k<iva->nfreq;k++)
        {
            iva->dWp1_r[k] = 0;
            iva->dWp2_r[k] = 0;
            iva->dWp3_r[k] = 0;
            iva->dWp4_r[k] = 0;


            iva->dWp2_i[k] = 0;
            iva->dWp3_i[k] = 0;
        }
        for(int k =0; k<iva->nfreq;k++)
        {
            for(int i =0;i<100;i++)
            {
                iva->phi1_real[i]=iva->Ssq1_1[i]*iva->S1_r[k][i];
                iva->phi1_imag[i]=iva->Ssq1_1[i]*iva->S1_i[k][i];
                iva->phi2_real[i]=iva->Ssq1_2[i]*iva->S2_r[k][i];
                iva->phi2_imag[i]=iva->Ssq1_2[i]*iva->S2_i[k][i];


                iva->dWp1_r[k] += (iva->phi1_real[i]*iva->S1_r[k][i])+(iva->phi1_imag[i]*iva->S1_i[k][i]);
                iva->dWp2_r[k] += (iva->phi1_real[i]*iva->S2_r[k][i])+(iva->phi1_imag[i]*iva->S2_i[k][i]);
                iva->dWp3_r[k] += (iva->phi2_real[i]*iva->S1_r[k][i])+(iva->phi2_imag[i]*iva->S1_i[k][i]);
                iva->dWp4_r[k] += (iva->phi2_real[i]*iva->S2_r[k][i])+(iva->phi2_imag[i]*iva->S2_i[k][i]);


                iva->dWp2_i[k] += (iva->phi1_imag[i]*iva->S2_r[k][i])-(iva->phi1_real[i]*iva->S2_i[k][i]);
                iva->dWp3_i[k] += (iva->phi2_imag[i]*iva->S1_r[k][i])-(iva->phi2_real[i]*iva->S1_i[k][i]);

            }
            iva->dWp1_r[k]=1-(iva->dWp1_r[k]/100);
            iva->dWp4_r[k]=1-(iva->dWp4_r[k]/100);
            iva->dWp2_r[k]=-iva->dWp2_r[k]/100;
            iva->dWp3_r[k]=-iva->dWp3_r[k]/100;
            iva->dWp2_i[k]=-iva->dWp2_i[k]/100;
            iva->dWp3_i[k]=-iva->dWp3_i[k]/100;
          // printf("%.32lf %d\n",iva->dWp2_r[k],k);
        }
        for(int k =0; k<iva->nfreq;k++)
        {
            iva->dWp11_r[k]=(iva->dWp1_r[k]*iva->W1_r[k])+(iva->dWp2_r[k]*iva->W3_r[k])-(iva->dWp2_i[k]*iva->W3_i[k])-(iva->dWp1_i[k]*iva->W1_i[k]);
            iva->dWp11_i[k]=(iva->dWp2_r[k]*iva->W3_i[k])+(iva->dWp2_i[k]*iva->W3_r[k])+(iva->dWp1_r[k]*iva->W1_i[k])+(iva->dWp1_i[k]*iva->W1_r[k]);
            iva->dWp22_r[k]=(iva->dWp1_r[k]*iva->W2_r[k])+(iva->dWp2_r[k]*iva->W4_r[k])-(iva->dWp1_i[k]*iva->W2_i[k])-(iva->dWp2_i[k]*iva->W4_i[k]);
            iva->dWp22_i[k]=(iva->dWp1_r[k]*iva->W2_i[k])+(iva->dWp2_i[k]*iva->W4_r[k])+(iva->dWp2_r[k]*iva->W4_i[k])+(iva->dWp1_i[k]*iva->W2_r[k]);
            iva->dWp33_r[k]=(iva->dWp3_r[k]*iva->W1_r[k])+(iva->dWp4_r[k]*iva->W3_r[k])-(iva->dWp3_i[k]*iva->W1_i[k])-(iva->dWp4_i[k]*iva->W3_i[k]);
            iva->dWp33_i[k]=(iva->dWp3_i[k]*iva->W1_r[k])+(iva->dWp4_r[k]*iva->W3_i[k])+(iva->dWp3_r[k]*iva->W1_i[k])+(iva->dWp4_i[k]*iva->W3_r[k]);
            iva->dWp44_r[k]=(iva->dWp3_r[k]*iva->W2_r[k])+(iva->dWp4_r[k]*iva->W4_r[k])-(iva->dWp3_i[k]*iva->W2_i[k])-(iva->dWp4_i[k]*iva->W4_i[k]);
            iva->dWp44_i[k]=(iva->dWp3_r[k]*iva->W2_i[k])+(iva->dWp3_i[k]*iva->W2_r[k])+(iva->dWp4_r[k]*iva->W4_i[k])+(iva->dWp4_i[k]*iva->W4_r[k]);





            iva->det_r=(iva->W1_r[k]*iva->W4_r[k])-(iva->W1_i[k]*iva->W4_i[k])-(iva->W2_r[k]*iva->W3_r[k])+(iva->W2_i[k]*iva->W3_i[k]);
            iva->det_i=(iva->W1_r[k]*iva->W4_i[k])+(iva->W1_i[k]*iva->W4_r[k])-(iva->W2_r[k]*iva->W3_i[k])-(iva->W2_i[k]*iva->W3_r[k]);
            iva->dlw=iva->dlw+log(sqrt(pow(iva->det_r,2)+pow(iva->det_i,2))+1e-6);



        }
        for(int k =0; k<iva->nfreq;k++)
        {
            iva->W1_r[k]=iva->W1_r[k]+(iva->dWp11_r[k]/2);
            iva->W2_r[k]=iva->W2_r[k]+(iva->dWp22_r[k]/2);
            iva->W3_r[k]=iva->W3_r[k]+(iva->dWp33_r[k]/2);
            iva->W4_r[k]=iva->W4_r[k]+(iva->dWp44_r[k]/2);
            iva->W1_i[k]=iva->W1_i[k]+(iva->dWp11_i[k]/2);
            iva->W2_i[k]=iva->W2_i[k]+(iva->dWp22_i[k]/2);
            iva->W3_i[k]=iva->W3_i[k]+(iva->dWp33_i[k]/2);
            iva->W4_i[k]=iva->W4_i[k]+(iva->dWp44_i[k]/2);
            //printf("%.32lf\n",iva->W2_r[k]);
        }
    //printf("%.32lf %d\n",iva->dlw,iter);
        //printf("%.32lf\n",iva->det_r);
//printf("%.32lf %d\n",iva->dlw,iter);
//        for(int i=0;i<100;i++)
//        {
//            iva->obj += iva->Ssq_1[i]+iva->Ssq_2[i];
//        }
//        iva->obj=((iva->obj/100)-iva->dlw)/(2*iva->nfreq);
//        printf("%.32lf\n",iva->obj);
    }
    for(int k =0; k<iva->nfreq;k++)
    {
        iva->det_r1=0;
        iva->det_i1=0;


        iva->w_1_r[k]=(iva->W1_r[k]*iva->Q1_real[k])+(iva->W2_r[k]*iva->Q3_real[k])-(iva->W2_i[k]*iva->Q3_imag[k])-(iva->W1_i[k]*iva->Q1_imag[k]);
        iva->w_1_i[k]=(iva->W2_r[k]*iva->Q3_imag[k])+(iva->W2_i[k]*iva->Q3_real[k])+(iva->W1_r[k]*iva->Q1_imag[k])+(iva->W1_i[k]*iva->Q1_real[k]);
        iva->w_2_r[k]=(iva->W1_r[k]*iva->Q2[k])+(iva->W2_r[k]*iva->Q4[k]);
        iva->w_2_i[k]=(iva->W2_i[k]*iva->Q4[k])+(iva->W1_i[k]*iva->Q2[k]);
        iva->w_3_r[k]=(iva->W3_r[k]*iva->Q1_real[k])+(iva->W4_r[k]*iva->Q3_real[k])-(iva->W4_i[k]*iva->Q3_imag[k])-(iva->W3_i[k]*iva->Q1_imag[k]);
        iva->w_3_i[k]=(iva->W4_r[k]*iva->Q3_imag[k])+(iva->W4_i[k]*iva->Q3_real[k])+(iva->W3_r[k]*iva->Q1_imag[k])+(iva->W3_i[k]*iva->Q1_real[k]);
        iva->w_4_r[k]=(iva->W3_r[k]*iva->Q2[k])+(iva->W4_r[k]*iva->Q4[k]);
        iva->w_4_i[k]=(iva->W4_i[k]*iva->Q4[k])+(iva->W3_i[k]*iva->Q2[k]);

        iva->det_r1=(iva->w_1_r[k]*iva->w_4_r[k])-(iva->w_1_i[k]*iva->w_4_i[k])-(iva->w_2_r[k]*iva->w_3_r[k])+(iva->w_2_i[k]*iva->w_3_i[k]);
        iva->det_i1=(iva->w_1_r[k]*iva->w_4_i[k])+(iva->w_1_i[k]*iva->w_4_r[k])-(iva->w_2_r[k]*iva->w_3_i[k])-(iva->w_2_i[k]*iva->w_3_r[k]);

        iva->w_11_r[k]=((iva->w_4_r[k]*iva->det_r1)+(iva->w_4_i[k]*iva->det_i1))/(pow(iva->det_r1,2)+ pow(iva->det_i1,2));
        iva->w_44_r[k]=((iva->w_1_r[k]*iva->det_r1)+(iva->w_1_i[k]*iva->det_i1))/(pow(iva->det_r1,2)+ pow(iva->det_i1,2));
        iva->w_11_i[k]=((iva->w_4_i[k]*iva->det_r1)-(iva->w_4_r[k]*iva->det_i1))/(pow(iva->det_r1,2)+ pow(iva->det_i1,2));
        iva->w_44_i[k]=((iva->w_1_i[k]*iva->det_r1)-(iva->w_1_r[k]*iva->det_i1))/(pow(iva->det_r1,2)+ pow(iva->det_i1,2));

        iva->fw_1_r[k]=(iva->w_11_r[k]*iva->w_1_r[k])-(iva->w_11_i[k]*iva->w_1_i[k]);
        iva->fw_2_r[k]=(iva->w_11_r[k]*iva->w_2_r[k])-(iva->w_11_i[k]*iva->w_2_i[k]);
        iva->fw_3_r[k]=(iva->w_44_r[k]*iva->w_3_r[k])-(iva->w_44_i[k]*iva->w_3_i[k]);
        iva->fw_4_r[k]=(iva->w_44_r[k]*iva->w_4_r[k])-(iva->w_44_i[k]*iva->w_4_i[k]);

        iva->fw_1_i[k]=(iva->w_11_r[k]*iva->w_1_i[k])+(iva->w_11_i[k]*iva->w_1_r[k]);
        iva->fw_2_i[k]=(iva->w_11_r[k]*iva->w_2_i[k])+(iva->w_11_i[k]*iva->w_2_r[k]);
        iva->fw_3_i[k]=(iva->w_44_r[k]*iva->w_3_i[k])+(iva->w_44_i[k]*iva->w_3_r[k]);
        iva->fw_4_i[k]=(iva->w_44_r[k]*iva->w_4_i[k])+(iva->w_44_i[k]*iva->w_4_r[k]);

    }
    for(int k =0; k<iva->nfreq;k++)
    {
        for(int i =0;i<100;i++)
        {
            iva->S1_r[k][i]=(iva->fw_1_r[k]*iva->Xp1_real[k][i])-(iva->fw_1_i[k]*iva->Xp1_imag[k][i])+(iva->fw_2_r[k]*iva->Xp2_real[k][i])-(iva->fw_2_i[k]*iva->Xp2_imag[k][i]);
            iva->S1_i[k][i]=(iva->fw_1_r[k]*iva->Xp1_imag[k][i])+(iva->fw_1_i[k]*iva->Xp1_real[k][i])+(iva->fw_2_r[k]*iva->Xp2_imag[k][i])+(iva->fw_2_i[k]*iva->Xp2_real[k][i]);
            iva->S2_r[k][i]=(iva->fw_3_r[k]*iva->Xp1_real[k][i])-(iva->fw_3_i[k]*iva->Xp1_imag[k][i])+(iva->fw_4_r[k]*iva->Xp2_real[k][i])-(iva->fw_4_i[k]*iva->Xp2_imag[k][i]);
            iva->S2_i[k][i]=(iva->fw_3_r[k]*iva->Xp1_imag[k][i])+(iva->fw_3_i[k]*iva->Xp1_real[k][i])+(iva->fw_4_r[k]*iva->Xp2_imag[k][i])+(iva->fw_4_i[k]*iva->Xp2_real[k][i]);
        }

    }
        iva->sp = (n*iva->shift)+1;
            for(int j =0;j<2;j++)
            {
                for(int i=0;i<iva->nfft;i++)
                {
                    iva->xwin[i][j]=iva->win[i]*iva->x1[i+iva->sp-1][j];
                }
            }
            for(int i=0;i<iva->nfft;i++)
            {
                iva->xwin1[i]= iva->xwin[i][0];
                iva->xwin2[i]= iva->xwin[i][1];
            }
            X1->doTransform(X1,iva->xwin1);
            X2->doTransform(X2,iva->xwin2);
            for(int i=0;i<iva->nfft/2+1;i++)
            {
                iva->xn1_real[i]= X1->real[i];
                iva->xn1_imag[i] = X1->imaginary[i] * (-1);
                iva->xn2_real[i]= X2->real[i];
                iva->xn2_imag[i] = X2->imaginary[i] * (-1);
                //printf("%.32lf\n",iva->xn2_real[i]);
            }
        for(int k =0; k<iva->nfreq;k++)
        {
            iva->S12_r[k]= (iva->fw_1_r[k]*iva->xn1_real[k])-(iva->fw_1_i[k]*iva->xn1_imag[k])+(iva->fw_2_r[k]*iva->xn2_real[k])-(iva->fw_2_i[k]*iva->xn2_imag[k]);
            iva->S22_r[k]= (iva->fw_3_r[k]*iva->xn1_real[k])-(iva->fw_3_i[k]*iva->xn1_imag[k])+(iva->fw_4_r[k]*iva->xn2_real[k])-(iva->fw_4_i[k]*iva->xn2_imag[k]);
            iva->S12_i[k]= (iva->fw_1_r[k]*iva->xn1_imag[k])+(iva->fw_1_i[k]*iva->xn1_real[k])+(iva->fw_2_r[k]*iva->xn2_imag[k])+(iva->fw_2_i[k]*iva->xn2_real[k]);
             iva->S22_i[k]= (iva->fw_3_r[k]*iva->xn1_imag[k])+(iva->fw_3_i[k]*iva->xn1_real[k])+(iva->fw_4_r[k]*iva->xn2_imag[k])+(iva->fw_4_i[k]*iva->xn2_real[k]);
        }
        for(int i =0;i<iva->nfreq;i++)
        {
            iva->X_final1_r[i]=iva->S12_r[i];
            iva->X_final1_i[i]=iva->S12_i[i];
            iva->X_final2_r[i]=iva->S22_r[i];
            iva->X_final2_i[i]=iva->S22_i[i];
        }
        int j=iva->nfreq-2;
        for(int i= 1;i<iva->nfreq-1;i++)
        {
            iva->X_final1_r[i+iva->nfreq-1]=iva->S12_r[j];
            iva->X_final1_i[i+iva->nfreq-1]=-iva->S12_i[j];
            iva->X_final2_r[i+iva->nfreq-1]=iva->S22_r[j];
            iva->X_final2_i[i+iva->nfreq-1]=-iva->S22_i[j];
            j--;
        }
         Y1->invTransform(Y1,iva->X_final1_r,iva->X_final1_i);
        Y2->invTransform(Y2,iva->X_final2_r,iva->X_final2_i);
        for(int i=0;i<iva->nfft;i++)
        {
            iva->sk1[i+iva->sp-1]=iva->sk1[i+iva->sp-1]+(iva->win[i]*Y1->real[i]);
            iva->sk2[i+iva->sp-1]=iva->sk2[i+iva->sp-1]+(iva->win[i]*Y2->real[i]);
            iva->v1[i+iva->sp-1]=iva->v1[i+iva->sp-1]+(iva->win[i]*iva->win[i]);
            iva->v2[i+iva->sp-1]=iva->v2[i+iva->sp-1]+(iva->win[i]*iva->win[i]);

        }
        for(int i=iva->nfft;i<2*iva->nfft;i++)
        {
            iva->yf1[i-iva->nfft]=iva->sk1[i]/iva->v1[i];
            iva->yf2[i-iva->nfft]=iva->sk2[i]/iva->v2[i];

        }


}



