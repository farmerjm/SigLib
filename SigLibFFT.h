#pragma once
#include <vector>

extern "C" {
#include "fftw3.h"
}

namespace SigLib {

    fftw_complex* FFTInternal(double* in, unsigned int N) {
    unsigned int nOut=floor(N/2)+1;
    fftw_complex* out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*nOut);
    fftw_plan p = fftw_plan_dft_r2c_1d(N, in, out, FFTW_ESTIMATE);
    fftw_execute(p);  
    fftw_destroy_plan(p);
    return out;
  }

  std::vector<double>* FFT(std::vector<double>* in) {
    unsigned int n=in->size();
    fftw_complex* out = FFTInternal(in->data(), n);
    std::vector<double>* outVec = new std::vector<double>;
    for (int i=0;i<floor(n)/2+1; i++) outVec->push_back((1/n)*sqrt(out[i][0]*out[i][0]+out[i][1]*out[i][1]));
    fftw_free(out);
    return outVec;
  }

  double GetNyquistFrequency(double sampleTime, unsigned int n) {
    return (1/2)*1/(sampleTime*(n-1));
  }


}
