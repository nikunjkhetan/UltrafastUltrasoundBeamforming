#include "incHeaders.h"
#include "incCustomHeader.h"

void computeDAS(Parameters p, Eigen::Ref<Eigen::Matrix<short int, -1, -1>> SIG,
                Eigen::Ref<Eigen::MatrixXd> reconFrame)
{
    // Define Threads
    omp_set_num_threads(omp_get_max_threads());
    Eigen::setNbThreads(omp_get_max_threads());

    // Generate FFT plans
    fftw_import_wisdom_from_string(p.wisdom.c_str());
    const fftw_plan p1 = planFFT(p.szZ);
    const fftw_plan p2 = planIFFT(p.szZ);

    // Initialize Matrices
    Eigen::MatrixXcd Recon = Eigen::MatrixXcd::Zero(p.szZ*p.na, p.szX);

    for(int i = 0; i < p.na; i++)
    {
        SIG(i*(p.szRFframe+1),Eigen::all).setZero();
        bfmDAS( p, i, reconFrame, SIG(Eigen::seq(i*(p.szRFframe+1),(i+1)*(p.szRFframe+1)-1),p.ConnMap.array()-1) );

        Recon(Eigen::seq(i*p.szZ,(i+1)*p.szZ-1),Eigen::all) = hilbert(p,reconFrame,p1,p2);
    }

    // Compound
    for(int i = 0; i < p.na; i++)
    {
        Recon(Eigen::seq(0,p.szZ-1),Eigen::all) += Recon(Eigen::seq(i*p.szZ,(i+1)*p.szZ-1),Eigen::all);
    }
    reconFrame = Recon(Eigen::seq(0,p.szZ-1),Eigen::all).array().abs().log();

    // Clean up and initialize outputs
    fftw_destroy_plan(p1);
    fftw_destroy_plan(p2);
    fftw_cleanup();
}


void computeDPC(Parameters p, Eigen::Ref<Eigen::Matrix<short int, -1, -1>> SIG,
                Eigen::Ref<Eigen::MatrixXd> reconFrame)
{
    // Define Threads
    omp_set_num_threads(omp_get_max_threads());
    Eigen::setNbThreads(omp_get_max_threads());

    // Generate FFT plans
    fftw_import_wisdom_from_string(p.wisdom.c_str());
    const fftw_plan p1 = planFFT(p.szZ);
    const fftw_plan p2 = planIFFT(p.szZ);

    // Initialize Matrices
    Eigen::MatrixXcd Recon = Eigen::MatrixXcd::Zero(p.szZ*p.na, p.szX);

    for(int i = 0; i < p.na; i++)
    {
        SIG(i*(p.szRFframe+1),Eigen::all).setZero();
        bfmDPC( p, i, reconFrame, SIG(Eigen::seq(i*(p.szRFframe+1),(i+1)*(p.szRFframe+1)-1),p.ConnMap.array()-1) );

        Recon(Eigen::seq(i*p.szZ,(i+1)*p.szZ-1),Eigen::all) = hilbert(p,reconFrame,p1,p2);
    }

    // Compound
    Eigen::MatrixXd DPC = Eigen::MatrixXd::Zero(p.szZ,p.szX);
    applyDPC(Recon,p,reconFrame);

    // Clean up and initialize outputs
    fftw_destroy_plan(p1);
    fftw_destroy_plan(p2);
    fftw_cleanup();
}
