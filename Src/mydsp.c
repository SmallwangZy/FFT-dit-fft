#include "mydsp.h"


uint32_t FindMinBin(uint32_t num)
{
    if((num & (num - 1)) == 0)
    {
        return num;
    }
    uint32_t top = 0x8000000;
    while (!(top & num))
    {
        top = top >> 1;
    }
    top = top << 1;
    return top;
}

//完成一次蝶形计算(原位计算)
void butterfly(int i,int j,std::complex<double> w,std::complex<double> *fft){
    std::complex<double> t=fft[i];
    fft[i]=fft[i]+w*fft[j];
    fft[j]=t-w*fft[j];
}

//完成单位根的计算
std::complex<double> w(int m,int N){
    std::complex<double> c;
    //拆分为实部和虚部的计算
    c.real(cos(2*acos(-1)*m/N));
    c.imag(sin(-2*acos(-1)*m/N));
    return c;
}

//显示一个动态数组
void DispSeqs(double * seq,int len)
{
    std::cout << "added nums:";
    int i = 0;
    for(i = 0;i<len;i++)
        std::cout << seq[i] << ' ';
}

//循环调用获得倒位序列
int reverse(int n,int bitl){
    int i=0,r=0,t;
    while(i<bitl){
       t=n&1;
       n=n>>1;
       r+=t*pow(2,bitl-1-i); 
       i++;
    }
    return r;
}


