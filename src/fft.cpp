//
// Created by jjjjo on 3/26/2026.
//

#include <vector>
#include <complex>
#include <fftw3.h>

const double pi = acos(-1);

/**
 * Performs a recursive discrete fourier transform on an input array--changing its values from
 * a function of amplitude over time to a function of frequency over time--and stores the result in
 * the given output array.
 *
 * @param in input vector
 * @param out output vector
 */
void dft_simple(const std::vector<std::complex<double>> &in, std::vector<std::complex<double>> &out) {
    const size_t n = in.size();
    if (n <= 1) {
        return;
    }

    std::vector<std::complex<double>> even;
    std::vector<std::complex<double>> odd;
    for (size_t i = 0; i < n / 2; ++i) {
        even[i] = in[i * 2];
        odd[i] = in[(i * 2) + 1];
    }

    dft_simple(even, out);
    dft_simple(odd, out);

    for (size_t k = 0; k < n; ++k) {
        std::complex<double> t = std::polar(1.0, -2 * pi * k / n) * odd[k];
        out[k] = even[k] + t;
        out[k + n / 2] = even[k] - t;
    }
}

fftw_complex* fft_init(int n) {
    return static_cast<fftw_complex *>(fftw_malloc(sizeof(fftw_complex) * n));
}

void fftw_cleanup(fftw_complex* arr) {
    fftw_free(arr);
}

fftw_complex* fft(double* in, const int n) {
    auto* out = static_cast<fftw_complex *>(fftw_malloc(sizeof(fftw_complex) * n));

    fftw_plan fft_plan = fftw_plan_dft_r2c_1d(n, in, out, FFTW_ESTIMATE);
    fftw_execute(fft_plan);

    fftw_destroy_plan(fft_plan);
    return out;
}
