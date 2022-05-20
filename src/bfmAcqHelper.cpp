#include "incHeaders.h"
#include "incCustomHeader.h"

void bfmDAS(const Parameters& p, int& idx, Eigen::Ref<Eigen::MatrixXd> bfFrame,
            const Eigen::Ref<const Eigen::Matrix<short int, -1, -1>>& SIG) {

    #pragma omp parallel for
    for (int i = 0; i < p.nPoints; i++) {
        Eigen::VectorXd idxt(p.numEl);
        int col = i / p.szZ;
        int row = i % p.szZ;
        calcIDXT(p,p.xCoord(col),p.zCoord(row),idx,idxt);// Calculate delay indices
//        calcPointLinear(idxt,SIG,bfFrame(row,col));
        calcPointSIMD(p,idxt,SIG,bfFrame(row,col));
    }

}

void bfmDPC(const Parameters& p, int& idx, Eigen::Ref<Eigen::MatrixXd> bfFrame,
            const Eigen::Ref<const Eigen::Matrix<short int, -1, -1>>& SIG) {

    #pragma omp parallel for
    for (int i = 0; i < p.nPoints; i++) {
        Eigen::VectorXd idxt(p.numEl);
        int col = i / p.szZ;
        int row = i % p.szZ;
        calcIDXTDPC(p,p.xCoord(col),p.zCoord(row),idx,idxt);// Calculate delay indices
        calcPointSIMD(p,idxt,SIG,bfFrame(row,col));
//        calcPointQuadratic(idxt,SIG,bfFrame(row,col));
    }

}
