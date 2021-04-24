//
//  main.c
//  iva_1_1
//
//  Created by Shankar, Nikhil on 12/7/17.
//  Copyright © 2017 default. All rights reserved.
//


#include "iva.h"
#include "data.h"
#include "Transforms.h"

int main() {
    int frame_len = 400;
    int nfft = 2048;
    int frame_shift = 160;
    int maxiter = 150;
    iva_parameters *iva;
    iva = newparameters(nfft,frame_len,frame_shift,maxiter);
    iva->enhance_signal(iva, noisyinput, noisyinput2);
    for(int i=0;i<100;i++)
    {
//printf("%.32lf\n",(iva->Xn_1_real[3][i]));
}
   
}


