#include "complex.h"
#include <stdio.h>
#include <string>
#include <Eigen/Dense>
#include "Parameters.h"
#include "fftw3.h"
#include "genTestWisdom.h"

void genWisdom(int16_t Nvec[], int numXform, Parameters& p)
{

    for (int i = 0; i < numXform; i++)
    {
        genPlanFFT((int) Nvec[i]);
    }

//    char *wisPt = fftw_export_wisdom_to_string();
//    std::string wisdom(wisPt);
//    p.wisdom = wisdom;

    p.wisdom = fftw_export_wisdom_to_string();

    fftw_forget_wisdom();
    fftw_cleanup();

}

void genPlanFFT(int N)
{
    fftw_complex *in;
    fftw_complex *out;

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);

    fftw_plan p = fftw_plan_dft_1d(N, in, in, FFTW_FORWARD, FFTW_MEASURE);
    fftw_plan p2 = fftw_plan_dft_1d(N, out, out, FFTW_BACKWARD, FFTW_MEASURE);

    fftw_free(in);
    fftw_free(out);
    fftw_destroy_plan(p);
    fftw_destroy_plan(p2);
}
