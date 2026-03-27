//
// Created by jjjjo on 3/26/2026.
//

#ifndef ROCKY_TALK_FFT_HPP
#define ROCKY_TALK_FFT_HPP
#include <vector>
#include <complex>
#include <fftw3.h>

void dft_simple(const std::vector<std::complex<double>> &in, std::vector<std::complex<double>> &out);
fftw_complex* fft(double* in, int n);
void fftw_cleanup(fftw_complex* arr);

#endif //ROCKY_TALK_FFT_HPP