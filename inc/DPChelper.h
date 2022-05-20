#ifndef DPCHELPER_H_INCLUDED
#define DPCHELPER_H_INCLUDED

void applyDPC(const Eigen::Ref<const Eigen::MatrixXcd>& Recon, Parameters& p, Eigen::Ref<Eigen::MatrixXd> DPC);

Eigen::MatrixXcd linInterp(const Eigen::Ref<const Eigen::MatrixXcd>& Recon, Parameters& p, const Eigen::Ref<const Eigen::VectorXd>& xq);


#endif // DPCHELPER_H_INCLUDED
