#include "incHeaders.h"
#include "incCustomHeader.h"


void applyDPC(const Eigen::Ref<const Eigen::MatrixXcd>& Recon, Parameters& p, Eigen::Ref<Eigen::MatrixXd> DPC)
{
    double wvlToM = p.c/p.fc;
    double intShift = ((p.TXangle.tail(p.na-1).array() - p.TXangle.head(p.na-1).array())).sum()*180/M_PI/(p.na-1)/1.6;// 1.6 value found by trial and error, could need correction
    double fovShift = p.dz*p.tShift/(p.fs/p.fc);

    Eigen::VectorXd xShift = (p.TXangle.array().sin()/p.TXangle.array().cos())*fovShift/p.pitch;

    for(int i = 0; i < p.na-1; i++)
    {
        double xShiftPair = -(xShift(i+1)-xShift(i))*wvlToM*0.5;

        Eigen::VectorXd xq1 = p.xCoord.array() + xShiftPair;
        Eigen::VectorXd xq2 = p.xCoord.array() - xShiftPair - p.pitch*intShift;

        Eigen::MatrixXcd RShift1 = linInterp(Recon(Eigen::seq(i*p.szZ,(i+1)*p.szZ-1),Eigen::all),p,xq1.array()/p.pitch);
        Eigen::MatrixXcd RShift2 = linInterp(Recon(Eigen::seq((i+1)*p.szZ,(i+2)*p.szZ-1),Eigen::all),p,xq2.array()/p.pitch);

        DPC.array() += ((RShift1.array()*(RShift2.array().conjugate())).arg()/(-xShiftPair*2));
    }
}


Eigen::MatrixXcd linInterp(const Eigen::Ref<const Eigen::MatrixXcd>& Recon, Parameters& p, const Eigen::Ref<const Eigen::VectorXd>& xq)
{
    Eigen::MatrixXcd intRecon(p.szZ,p.szX);
    for(int i = 0; i < p.szX; i++)
    {

        if (xq(i) < p.xCoord(0)/p.pitch)
        {
            intRecon.col(i) = Recon.col(0).array() + (xq(i) - p.xCoord(0)/p.pitch)*(Recon.col(1).array() - Recon.col(0).array())/((p.xCoord(1) - p.xCoord(0))/p.pitch);
        }
        else if (xq(i) > p.xCoord(Eigen::last)/p.pitch)
        {
            intRecon.col(i) = Recon.col(p.szX-2).array() + (xq(i) - p.xCoord(p.szX-2)/p.pitch)*(Recon.col(p.szX-1).array() - Recon.col(p.szX-2).array())/((p.xCoord(p.szX-1) - p.xCoord(p.szX-2))/p.pitch);
        }
        else
        {
            int xi = static_cast<int>(xq(i) - p.xCoord(0)/p.pitch);
            intRecon.col(i) = Recon.col(xi).array() + (xq(i) - p.xCoord(xi)/p.pitch)*(Recon.col(xi+1).array()-Recon.col(xi).array())/((p.xCoord(xi+1)-p.xCoord(xi))/p.pitch);
        }

    }

    return intRecon;
}
