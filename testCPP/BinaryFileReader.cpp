#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include "incHeaders.h"
#include "incCustomHeader.h"
#include "BinaryFileReader.h"



template <typename T>
void readFile(const char* fname, int byteSz, int numVals, T* outVal)
{
    using namespace std;
    ifstream rf(fname,ios::out | ios::binary);
    if(!rf) {
      cout << "Cannot open file!" << endl;
    }

    cout << "The length of the array is: " << numVals << endl;
    for (int i = 0; i < numVals; i++)
    {
       rf.read((char *) &outVal[i],byteSz);
    //   cout << outVal[i] << "  ";
    }
    cout << endl;
    rf.close();

}

void readRF(Parameters& p, Eigen::Ref<Eigen::Matrix<short int, -1, -1>> SIG, std::string suffix)
{
    std::string folder = "C:/GitHub/UltrafastUltrasoundBeamforming/data/";
    const char* fname = "RF";
    std::string c = folder + fname + suffix;
    int byteSz = 2;
    struct stat results;
    if (stat(c.c_str(), &results) == 0)
    {
        std::cout << results.st_size << std::endl;
    }
    std::ifstream rf(c.c_str(), std::ios::in | std::ios::binary);
    rf.read((char *) SIG.data(),p.szRF*p.nc*byteSz);
    rf.close();

}

void readRFmultiFrame(Parameters& p, Eigen::Ref<Eigen::Matrix<short int, -1, -1>> SIG, std::string suffix)
{
    std::string folder = "C:/GitHub/UltrafastUltrasoundBeamforming/data/";
    const char* fname = "RF";
    std::string c = folder + fname + suffix;
    int byteSz = 2;
    struct stat results;
    if (stat(c.c_str(), &results) == 0)
    {
        std::cout << results.st_size << std::endl;
    }
    std::ifstream rf(c.c_str(), std::ios::in | std::ios::binary);
    rf.read((char *) SIG.data(),p.szRF*20*p.nc*byteSz);
    rf.close();

}

void init(Parameters& p, std::string suffix) {

    std::string folder = "C:/GitHub/UltrafastUltrasoundBeamforming/data/";

    const char* fname = "paramsINT";
    std::string c = folder + fname + suffix;
    int byteSz = 4;
    struct stat results;
    if (stat(c.c_str(), &results) == 0)
    {
        std::cout << results.st_size << std::endl;
    }
    int numVals = results.st_size/byteSz;
    int32_t paramINT[numVals];
    readFile(c.c_str(),byteSz,numVals,paramINT);


    fname = "paramsDoub";
    c = folder + fname + suffix;
    byteSz = 8;
    if (stat(c.c_str(), &results) == 0)
    {
        std::cout << results.st_size << std::endl;
    }
    numVals = results.st_size/byteSz;
    double paramDoub[numVals];
    readFile(c.c_str(),byteSz,numVals,paramDoub);

    fname = "paramsMAP";
    c = folder + fname + suffix;
    byteSz = 2;
    if (stat(c.c_str(), &results) == 0)
    {
        std::cout << results.st_size << std::endl;
    }
    numVals = results.st_size/byteSz;
    int16_t paramMAP[numVals];
    readFile(c.c_str(),byteSz,numVals,paramMAP);


    fname = "paramsPOS";
    c = folder + fname + suffix;
    byteSz = 8;
    if (stat(c.c_str(), &results) == 0)
    {
        std::cout << results.st_size << std::endl;
    }
    numVals = results.st_size/byteSz;
    double paramPOS[numVals];
    readFile(c.c_str(),byteSz,numVals,paramPOS);



    p.numEl = paramINT[0];
    p.szRF = paramINT[1];
    p.szRFframe = paramINT[2];
    p.szX = paramINT[3];
    p.szZ = paramINT[4];
    p.na = paramINT[5];
    p.nc = paramINT[6];

    p.fs = paramDoub[0];
    p.pitch = paramDoub[1];
    p.fc = paramDoub[2];
    p.c = paramDoub[3];
    p.fnumber = paramDoub[4];
    p.t0 = paramDoub[5];
    p.dTheta = paramDoub[7];
    p.dz = paramDoub[10];


    p.TXangle = (Eigen::ArrayXd::LinSpaced(p.na,0,p.na-1))*paramDoub[7] + paramDoub[6];
    Eigen::Vector<short int, -1> chk2 = Eigen::Map<Eigen::Vector<short int,-1>> (paramMAP,p.numEl);
    p.ConnMap = chk2.cast<int>();

    p.zCoord = Eigen::VectorXd::LinSpaced(p.szZ,0,p.szZ-1);
    p.zCoord = p.zCoord.array()*p.dz + paramDoub[11];
    p.xCoord = Eigen::VectorXd::LinSpaced(p.szX,-p.numEl/2,-p.numEl/2 + p.szX-1)*p.pitch;
//    p.xCoord = p.xCoord.array()*paramDoub[8] + paramDoub[9];

    p.ElemPos = Eigen::Map<Eigen::Vector<double,-1>> (paramPOS,p.numEl);

    p.nPoints = p.szX*p.szZ;
    p.L = p.ElemPos(p.numEl-1)-p.ElemPos(0);

}
