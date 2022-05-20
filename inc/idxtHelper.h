#ifndef IDXTHELPER_H_INCLUDED
#define IDXTHELPER_H_INCLUDED

void calcIDXT(const Parameters& p, const double& XPSF, const double& ZPSF,
               const int& idx, Eigen::Ref<Eigen::VectorXd> idxt);

void calcIDXTDPC(const Parameters& p, const double& XPSF, const double& ZPSF,
               const int& idx, Eigen::Ref<Eigen::VectorXd> idxt);

template <typename T> int sgn(T val);

#endif // IDXTHELPER_H_INCLUDED
