#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <string>
#include <Eigen/Dense>
class Parameters
{
    public:

        double fs, pitch, fc, c, fnumber, t0, L, dz, dTheta;
        int numEl, szRF, szRFframe, szX, szZ, nPoints, na, nc, tShift;
        std::string wisdom;
        Eigen::VectorXd TXangle,ElemPos,xCoord,zCoord;
        Eigen::VectorXi ConnMap,startSample,endSample;

        Parameters();
        virtual ~Parameters();

    protected:

    private:
};

#endif // PARAMETERS_H
