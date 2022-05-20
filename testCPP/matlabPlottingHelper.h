#ifndef MATLABPLOTTINGHELPER_H_INCLUDED
#define MATLABPLOTTINGHELPER_H_INCLUDED

void plotData(const Eigen::Ref<const Eigen::MatrixXd>& reconFrame);

void plotDPC(const Eigen::Ref<const Eigen::MatrixXd>& reconFrame);

void plotBModeDPC(const Eigen::Ref<const Eigen::MatrixXd>& reconBMode, const Eigen::Ref<const Eigen::MatrixXd>& reconDPC, Parameters& p);

void plotSlidingData(const Eigen::Ref<const Eigen::MatrixXd>& reconFrame, Parameters& p);

void plotSlidingRFData(Eigen::Ref<Eigen::Matrix<short int, -1, -1>> SIG, Parameters& p);

void plotIDXT(const Eigen::Ref<const Eigen::MatrixXf>& idxtChk, Parameters& p);

void plotDTX(Eigen::Ref<Eigen::MatrixXd> dTX, Parameters& p);

void plotDPC(Eigen::Ref<Eigen::MatrixXcd> Recon, Parameters& p);

void animateData(const Eigen::Ref<const Eigen::MatrixXd>& Recon, Parameters& p);

#endif // MATLABPLOTTINGHELPER_H_INCLUDED
