#ifndef BFMACQHELPER_H_INCLUDED
#define BFMACQHELPER_H_INCLUDED

void bfmDAS(const Parameters& p, int& idx, Eigen::Ref<Eigen::MatrixXd> bfFrame,
            const Eigen::Ref<const Eigen::Matrix<short int, -1, -1>>& SIG);

void bfmDPC(const Parameters& p, int& idx, Eigen::Ref<Eigen::MatrixXd> bfFrame,
            const Eigen::Ref<const Eigen::Matrix<short int, -1, -1>>& SIG);


#endif // BFMACQHELPER_H_INCLUDED
