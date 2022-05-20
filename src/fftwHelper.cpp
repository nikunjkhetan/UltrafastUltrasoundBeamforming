#include "incHeaders.h"
#include "incCustomHeader.h"

// *********** FFTW Planned Implementation *************
fftw_plan planFFT(int N) {

    fftw_complex *in;

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);

    fftw_plan p = fftw_plan_dft_1d(N, in, in, FFTW_FORWARD, FFTW_MEASURE | FFTW_WISDOM_ONLY);

    if (p == NULL) {
        p = fftw_plan_dft_1d(N, in, in, FFTW_FORWARD, FFTW_MEASURE);
    }

    fftw_free(in);
    return p;

}

fftw_plan planIFFT(int N) {

    fftw_complex *in;

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);

    fftw_plan p = fftw_plan_dft_1d(N, in, in, FFTW_BACKWARD, FFTW_MEASURE | FFTW_WISDOM_ONLY);

    if (p == NULL) {
        p = fftw_plan_dft_1d(N, in, in, FFTW_BACKWARD, FFTW_MEASURE);
    }

    fftw_free(in);
    return p;
}

/* Computes the 1-D fast Fourier transform. */
void fft2D(Eigen::Ref<Eigen::MatrixXcd> inMat, const fftw_plan& p) {
    #pragma omp parallel for
    for (int i = 0; i < inMat.cols(); i++) {
        fftw_execute_dft(p,reinterpret_cast<fftw_complex*>(&inMat.coeffRef(0,i)),
                         reinterpret_cast<fftw_complex*>(&inMat.coeffRef(0,i)));
    }
}


Eigen::MatrixXcd hilbert(Parameters& p, const Eigen::Ref<const Eigen::MatrixXd>& bfFrame,
                         const fftw_plan& p1, const fftw_plan& p2) {

//     Eigen::MatrixXcd outMat = Eigen::MatrixXcd::Zero(p.szZ, p.szX);
    Eigen::MatrixXcd inMat = Eigen::MatrixXcd::Zero(p.szZ, p.szX);
    inMat.real() = bfFrame;
    int midpt = static_cast<int>(round(p.szZ/2));
    fft2D(inMat,p1);
    inMat(midpt,Eigen::all) /= 2.0;
    inMat(Eigen::seq(0,midpt-1),Eigen::all).setZero();
    fft2D(inMat,p2);

    inMat.array() /= p.szZ;

    return inMat;
}
