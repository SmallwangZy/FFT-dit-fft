#include <iostream>
#include<complex>
#include<cmath>
#include<fstream>
#include "mydsp.h"
#include <vector>
#include <chrono>

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    std::fstream file("Input.txt", std::ios::in);    
    if(!file.is_open()){
        std::cout << "open failed!!!" << std::endl;
        return 0;
    } 
    else   
    {               
        std::cout << "Open File Successfully!!!\ndata:";
        double num;
        int count = 0;
        std::vector<double> nums_vec;
        while (file >> num) {
            std::cout << num << " ";
            count ++;
            nums_vec.push_back(num);
        }
        file.close();
        /*
            count : 实际拥有元素的数量
            seq_nums : 补全后元素的个数
            seqs : 补全之后的堆数组
        */
        int seq_nums = FindMinBin(count);
        std::cout << "\nnumbers:" << count << "\n";
        std::cout << "add points at:" << seq_nums << '\n';
        double* seqs = new double[seq_nums]();
        for(int index = 0;index <seq_nums;index++){
            if(index < count)
                seqs[index] = nums_vec[index];
            else
                seqs[index] = 0;
        }
        DispSeqs(seqs,seq_nums);
        int fft_N = seq_nums;  
        int temp;
        //通过倒位序算法建立FFT的时域动态数组
        std::cout << "\nReversed Sequence index:";
        std::complex<double> *fft = new std::complex<double>[fft_N]();
        for(int index = 0;index < fft_N;index ++){
            temp = reverse(index,std::log2(fft_N));
            std::cout << temp << ' ';
            fft[index].real(seqs[temp]);
            fft[index].imag(0);
        }
        delete [] seqs;
        //开始FFT的计算
        int M = std::log2(fft_N);
        int group,i,layer;
        for(layer=1;layer<=M;layer++)   //遍历每个层
    	    for(group=0;group<fft_N/pow(2,layer);group++)    //遍历层下的每个组
        	    for(i=0;i<pow(2,layer-1);i++)        //遍历组内的每个蝶形单元
            	    butterfly(group*pow(2,layer)+i,group*pow(2,layer)+i+pow(2,layer-1),w(i,pow(2,layer)),fft);
        std::cout << "\nfft outputs:";
        std::ofstream outfile("Output.txt");
        // 遍历数组，并将每个复数写入文件中
        for (i = 0; i < fft_N; i++) {
            std::cout << fft[i] << " ";
            outfile << fft[i].real() << " + " << fft[i].imag() << "i" << std::endl;
        }
        delete [] fft;
    }
    std::cout << '\n';
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "cost time:" << duration.count() << " us" << std::endl;
    system("pause");
    return 0;
}


