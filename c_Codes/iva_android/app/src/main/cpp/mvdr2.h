//
// Created by cxk131330 on 10/5/2017.
//

#ifndef AUDIOTWOMICS_2_MVDR2_H
#define AUDIOTWOMICS_2_MVDR2_H


#include <stdio.h>
#include <string.h>
#include "Transforms.h"

typedef struct iva_parameters {
    int frame_len,nfft,frame_shift,overlap,shift,nframes,nfreq,sp,maxiter, framecounter;
    double *sum1_r,*sum1_i,*sum2_r,*sum2_i,*sum, *Ssq_1, *Ssq_2, *Ssq1_1, *Ssq1_2;
    double *win, *ones, *Rxx1_real, *Rxx1_imag, *Rxx2_real, *Rxx2_imag, *Rxx3_real, *Rxx3_imag, *Rxx4_real, *Rxx4_imag, *Rxx1_real_1, *Rxx1_real_2;
    double *xwin1,*xwin2,*xn1_real,*xn2_real,*xn1_imag,*xn2_imag;
    double **xwin;
    double **x1;
    double **Xn_1_real, **Xn_2_real,**Xn_1_img, **Xn_2_img, *Xmean1_real, *Xmean1_imag, *Xmean2_real, *Xmean2_imag, **Xp1_real, **Xp2_real, **Xp1_imag, **Xp2_imag, **S1, **S2,**S1_r,**S1_i,**S2_r,**S2_i;
   void(*enhance_signal)(struct iva_parameters *iva, double *input1, double *input2, int framecounter);
    int a;
    double *b,*c, *D1, *D2, *aa1, *aa2, *fw_1_r,*fw_2_r,*fw_3_r,*fw_4_r,*fw_1_i,*fw_2_i,*fw_3_i,*fw_4_i;
    double *E1_real, *E1_imag, *E2_real, *E2_imag, *E3, *E4,*w_11_r,*w_11_i,*w_44_r,*w_44_i;
    double *Q1_real, *Q1_imag, *Q3_real, *Q3_imag, *Q2, *Q4, *W1_r,*W2_r,*W3_r,*W4_r,*W1_i,*W2_i,*W3_i,*W4_i, *phi1_real, *phi1_imag, *phi2_real, *phi2_imag,obj;
    double *dWp1_r,*dWp2_r,*dWp2_i,*dWp3_r,*dWp3_i,*dWp4_r,dlw,det_r,det_i,*dWp1_i,*dWp4_i,*w_1_r,*w_2_r,*w_3_r,*w_4_r,*w_1_i,*w_2_i,*w_3_i,*w_4_i, *dWp11_r,*dWp22_r,*dWp22_i,*dWp33_r,*dWp33_i,*dWp44_r, *dWp11_i,*dWp44_i, det_r1,det_i1;
    double *S12_r, *S12_i, *S22_r, *S22_i,*X_final1_r, *X_final1_i, *X_final2_r, *X_final2_i, *sk1, *sk2, *v1, *v2, *yf1, *yf2;
}iva_parameters;

void enhance_signal(iva_parameters *iva, double *input1, double *intput2, int framecounter);
iva_parameters* newparameters(int nfft, int framelen, int frame_shift, int maxiter);
double* calc_hanning(int m, int n);
double* hanning(int n);



#endif //AUDIOTWOMICS_2_MVDR2_H
