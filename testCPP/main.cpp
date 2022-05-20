#include "incHeaders.h"
#include "incCustomHeader.h"
#include "BinaryFileReader.h"
#include "genTestWisdom.h"
#include "matlabPlottingHelper.h"

using namespace std;

int main()
{
    Parameters p;
    string suffix = "Tall.bin";
    init(p,suffix);

    Eigen::Matrix<short int, -1, -1> SIG(p.szRF,p.nc);
    readRF(p,SIG,suffix);

    int16_t Nvec[2] = {(int16_t) p.szZ,(int16_t) p.numEl};
    genWisdom(Nvec,2,p);

    p.tShift = 0;

    Eigen::MatrixXd reconBMode = Eigen::MatrixXd::Zero(p.szZ, p.szX);
    Eigen::MatrixXd reconFrame = Eigen::MatrixXd::Zero(p.szZ, p.szX);

    computeDAS(p,SIG,reconBMode);
    p.tShift = 600;
    computeDPC(p,SIG,reconFrame);
    reconFrame.array() /= reconFrame.array().abs().maxCoeff();
//    plotDPC(reconFrame);
    plotBModeDPC(reconBMode,reconFrame,p);

    // Clean up and initialize outputs


    cout << "Hello world!" << endl;
    return 0;
}
