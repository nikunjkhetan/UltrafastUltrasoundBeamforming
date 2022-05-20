#ifndef FFTWHELPER_H_INCLUDED
#define FFTWHELPER_H_INCLUDED

void fft2D(Eigen::Ref<Eigen::MatrixXcd> inMat, const fftw_plan& p);

fftw_plan planIFFT(int N);
fftw_plan planFFT(int N);

Eigen::MatrixXcd hilbert(Parameters& p, const Eigen::Ref<const Eigen::MatrixXd>& bfFrame,
                         const fftw_plan& p1, const fftw_plan& p2);

#endif // FFTWHELPER_H_INCLUDED
