#ifndef MAIN2_H_INCLUDED
#define MAIN2_H_INCLUDED

void computeDAS(Parameters p, Eigen::Ref<Eigen::Matrix<short int, -1, -1>> SIG,
                Eigen::Ref<Eigen::MatrixXd> reconFrame);

void computeDPC(Parameters p, Eigen::Ref<Eigen::Matrix<short int, -1, -1>> SIG,
                Eigen::Ref<Eigen::MatrixXd> reconFrame);

#endif // MAIN2_H_INCLUDED
