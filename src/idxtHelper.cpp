#include "incHeaders.h"
#include "incCustomHeader.h"

void calcIDXT(const Parameters& p, const double& XPSF, const double& ZPSF,
               const int& idx, Eigen::Ref<Eigen::VectorXd> idxt) {

    double dTX = ( (sgn(-p.TXangle(idx))*p.L/2 - XPSF)*sin(-p.TXangle(idx)) + ZPSF*cos(p.TXangle(idx)))*p.fs/p.c + p.t0*p.fs;

    idxt = ( (XPSF - p.ElemPos.array()).square() + ZPSF*ZPSF ).sqrt()*p.fs/p.c + dTX;
    idxt = ((abs(XPSF-p.ElemPos.array()) <= ZPSF*0.5/p.fnumber) && (idxt.array() <= (p.szRFframe - 2)) ).select(idxt,0.0);
}

void calcIDXTDPC(const Parameters& p, const double& XPSF, const double& ZPSF,
               const int& idx, Eigen::Ref<Eigen::VectorXd> idxt) {

    double dTX = ( (sgn(-p.TXangle(idx))*p.L/2 - XPSF)*sin(-p.TXangle(idx)) + ZPSF*cos(p.TXangle(idx)) + 2*((p.zCoord(1)-p.zCoord(0))*p.tShift/(p.fs/p.fc))*cos(p.TXangle(idx)))*p.fs/p.c + p.t0*p.fs;

    idxt = ( (XPSF - p.ElemPos.array()).square() + ZPSF*ZPSF ).sqrt()*p.fs/p.c + dTX;
    idxt = ((abs(XPSF-p.ElemPos.array()) <= ZPSF*0.5/p.fnumber) && (idxt.array() <= (p.szRFframe - 2)) ).select(idxt,0.0);
}

template <typename T>
int sgn(T val) { return (T(0) < val) - (val < T(0)); }
