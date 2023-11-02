#ifndef __MYDSP_H__
#define __MYDSP_H__


#include <complex>
#include <iostream>
#include <stdint.h>

uint32_t FindMinBin(uint32_t num);
void butterfly(int i,int j,std::complex<double> w,std::complex<double> *fft);
std::complex<double> w(int m,int N);
void DispSeqs(double * seq,int len);
int reverse(int n,int bitl);


#endif