#ifndef CALCPOINTHELPER_H_INCLUDED
#define CALCPOINTHELPER_H_INCLUDED

// *********** Manual Interpolation Implementations *************

void calcPointLinear(const Eigen::Ref<const Eigen::VectorXd>& idxt,
               const Eigen::Ref<const Eigen::Matrix<short int, -1, -1>>& SIG,
               double& bfVal);

void calcPointQuadratic(const Eigen::Ref<const Eigen::VectorXd>& idxt,
               const Eigen::Ref<const Eigen::Matrix<short int, -1, -1>>& SIG,
               double& bfVal);

void calcPoint5Point(const Eigen::Ref<const Eigen::VectorXd>& idxt,
               const Eigen::Ref<const Eigen::Matrix<short int, -1, -1>>& SIG,
               double& bfVal);

// *********** SIMD Interpolation Implementations *************

void calcPointSIMD(const Parameters& p, const Eigen::Ref<const Eigen::VectorXd>& idxt,
                const Eigen::Ref<const Eigen::Matrix<short int, -1, -1>>& SIG,
                double& bfVal);

#endif // CALCPOINTHELPER_H_INCLUDED
