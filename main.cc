#include <iostream>
#include "complex.h"
#include "input_image.h"
#include <mpi.h>

#include <cmath>
#include <vector>
#include <thread>

#define DEBUG
#define TIME_THE_PROGRAM

#ifdef TIME_THE_PROGRAM
    #include <chrono> 
#endif

using namespace std;

const float PI = 3.14159265358979f;

void cpuDFT1D(Complex* H, Complex* h, int row, int N) {
    int offset = row * N;
    int realN;
    for (int n = offset; n < offset + N; n++) {
        realN = n - offset;
        for (int k = 0; k < N; k++) {
            Complex W(cos(2 * PI * realN * k / float(N)), -sin(2 * PI * realN * k / float(N)));
            H[n] = H[n] + W * h[k + offset];
        }
    }
}

void cpuDFT1DCol(Complex* H, Complex* h, int num, int N) {
    int p = 0;

    for (int n = num; n < N * (N - 1) + num + 1; n = n + N) {
        for (int k = 0; k < N; k++) {
            Complex W(cos(2 * M_PI * p * k / N), -sin(2 * M_PI * p * k / N));
            H[n] = H[n] + W * h[k * N + num];
        }
        p++;
    }
}

void cpuDFT2D(const char* fileName) {
    unsigned int numOfThreads = 8;

    // read in the file
    InputImage inputImage(fileName);

    int width = inputImage.get_width(); // N
    int N = width;
    int height = inputImage.get_height();

    int widthIter = width / numOfThreads;

    // vector to hold data
    vector<Complex> H(width * height);

    // data
    Complex* h = inputImage.get_image_data();


    #ifdef DEBUG
        cout << widthIter << endl;
    #endif  

    thread t1([&] {
        for (int i = 0; i < widthIter; i++) {
            cpuDFT1D(&H[0], h, i, N);
        }
    });
    thread t2([&] {
        for (int i = widthIter; i < widthIter * 2; i++) {
            cpuDFT1D(&H[0], h, i, N);
        }
    });
    thread t3([&] {
        for (int i = widthIter * 2; i < widthIter * 3; i++) {
            cpuDFT1D(&H[0], h, i, N);
        }
    });
    thread t4([&] {
        for (int i = widthIter * 3; i < widthIter * 4; i++) {
            cpuDFT1D(&H[0], h, i, N);
        }
    });     
    thread t5([&] {
        for (int i = widthIter * 4; i < widthIter * 5; i++) {
            cpuDFT1D(&H[0], h, i, N);
        }
    });
    thread t6([&] {
        for (int i = widthIter * 5; i < widthIter * 6; i++) {
            cpuDFT1D(&H[0], h, i, N);
        }
    });
    thread t7([&] {
        for (int i = widthIter * 6; i < widthIter * 7; i++) {
            cpuDFT1D(&H[0], h, i, N);
        }
    });
    thread t8([&] {
        for (int i = widthIter * 7; i < N; i++) {
            cpuDFT1D(&H[0], h, i, N);
        }
    });       

    t1.join(); t2.join(); t3.join(); t4.join();
    t5.join(); t6.join(); t7.join(); t8.join();

    // Column
    vector<Complex> H2(width * height);
    thread tt1([&] {
        for (int i = 0; i < widthIter; i++) {
            cpuDFT1DCol(&H2[0], &H[0], i, height);
        }
    });
    thread tt2([&] {
        for (int i = widthIter; i < widthIter * 2; i++) {
            cpuDFT1DCol(&H2[0], &H[0], i, height);
        }
    });
    thread tt3([&] {
        for (int i = widthIter * 2; i < widthIter * 3; i++) {
            cpuDFT1DCol(&H2[0], &H[0], i, height);
        }
    });
    thread tt4([&] {
        for (int i = widthIter * 3; i < widthIter * 4; i++) {
            cpuDFT1DCol(&H2[0], &H[0], i, height);
        }
    });
    thread tt5([&] {
        for (int i = widthIter * 4; i < widthIter * 5; i++) {
            cpuDFT1DCol(&H2[0], &H[0], i, height);
        }
    });
    thread tt6([&] {
        for (int i = widthIter * 5; i < widthIter * 6; i++) {
            cpuDFT1DCol(&H2[0], &H[0], i, height);
        }
    });
    thread tt7([&] {
        for (int i = widthIter * 6; i < widthIter * 7; i++) {
            cpuDFT1DCol(&H2[0], &H[0], i, height);
        }
    });
    thread tt8([&] {
        for (int i = widthIter * 7; i < N; i++) {
            cpuDFT1DCol(&H2[0], &H[0], i, height);
        }
    });    

    tt1.join(); tt2.join(); tt3.join(); tt4.join();
    tt5.join(); tt6.join(); tt7.join(); tt8.join();

    Complex* result1D = H2.data();

    inputImage.save_image_data("result.txt", result1D, width, height);

    #ifdef DEBUG
        cout << width << " " << height << endl; 
    #endif  
}

int main(int argc, char** argv) {

    cout << "Depracated. Use main_thread.cc or main_mpi.cc or main_cuda.cu" << endl;
#ifdef TIME_THE_PROGRAM
        auto start = std::chrono::high_resolution_clock::now(); 

        string fileName("../src/Tower256.txt");
        cpuDFT2D(fileName.c_str());

        auto stop = std::chrono::high_resolution_clock::now(); 
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); 
        cout << "Threaded CPU Program took: " << duration.count()/1000000.0 << " seconds." << endl;   
#else
        string fileName("../src/Tower256.txt");
        cpuDFT2D(fileName.c_str());         
#endif     

    return 0;
}