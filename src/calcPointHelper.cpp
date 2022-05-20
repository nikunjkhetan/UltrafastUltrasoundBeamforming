#include "incHeaders.h"
#include "incCustomHeader.h"

// *********** Manual Interpolation Implementations *************

void calcPointLinear(const Eigen::Ref<const Eigen::VectorXd>& idxt,
               const Eigen::Ref<const Eigen::Matrix<short int, -1, -1>>& SIG,
               double& bfVal) {

    Eigen::VectorXd bfPTVec(idxt.size());
    #pragma omp simd
    for (int j = 0; j < idxt.size(); j++) {
        int vIDX = static_cast<int>(idxt(j));
        double interp1 = vIDX + 1 - idxt(j);
        double interp2 = idxt(j) - vIDX;
        bfPTVec(j) = (SIG(vIDX,j)*interp1 + SIG(vIDX+1,j)*interp2);
    }
    bfVal = bfPTVec.sum();

}

void calcPointQuadratic(const Eigen::Ref<const Eigen::VectorXd>& idxt,
               const Eigen::Ref<const Eigen::Matrix<short int, -1, -1>>& SIG,
               double& bfVal) {

    Eigen::VectorXd bfPTVec(idxt.size());
    #pragma omp simd
    for (int j = 0; j < idxt.size(); j++) {
        int vIDX = static_cast<int>(idxt(j));
        double idxd = idxt(j) - vIDX;
        double interp1 = (idxd+1)*(idxd+2)/2;
        double interp2 = idxd*(idxd+2);
        double interp3 = idxd*(idxd+1)/2;
        bfPTVec(j) = (SIG(vIDX,j)*interp1 + SIG(vIDX+1,j)*interp2 + SIG(vIDX+1,j)*interp3);
    }
    bfVal = bfPTVec.sum();

}

void calcPoint5Point(const Eigen::Ref<const Eigen::VectorXd>& idxt,
               const Eigen::Ref<const Eigen::Matrix<short int, -1, -1>>& SIG,
               double& bfVal) {

    Eigen::VectorXd bfPTVec(idxt.size());
    #pragma omp simd
    for (int j = 0; j < idxt.size(); j++) {
        int vIDX = static_cast<int>(idxt(j));
        double idxd = idxt(j) - vIDX;
        double interp1 = (idxd)*(idxd)/7 + idxd/5 - 3/35;
        double interp2 = -(idxd)*(idxd)/14 + idxd/10 + 12/35;
        double interp3 = -idxd*(idxd)/7 + 17/35;
        double interp4 = -(idxd)*(idxd)/14 - idxd/10 + 12/35;
        double interp5 = (idxd)*(idxd)/7 - idxd/5 - 3/35;
        bfPTVec(j) = (SIG(vIDX-2,j)*interp1 + SIG(vIDX-1,j)*interp2 +
                      SIG(vIDX,j)*interp3 + SIG(vIDX+1,j)*interp4 +
                      SIG(vIDX+2,j)*interp5);
    }
    bfVal = bfPTVec.sum();

}

// *********** SIMD Interpolation Implementations *************

void calcPointSIMD(const Parameters& p, const Eigen::Ref<const Eigen::VectorXd>& idxt,
                const Eigen::Ref<const Eigen::Matrix<short int, -1, -1>>& SIG,
                double& bfVal) {
     __m128d acc = _mm_setzero_pd();
     for (int j = 0; j < idxt.size(); j++) {
         acc = _mm_add_pd( acc, computePoint(idxt.data()+j, SIG.data() + j * SIG.rows()) );
     }
     bfVal = _mm_cvtsd_f64(_mm_hadd_pd(acc, acc));
 }
