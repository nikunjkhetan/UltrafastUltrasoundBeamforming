#ifndef BINARYFILEREADER_H_INCLUDED
#define BINARYFILEREADER_H_INCLUDED

template <typename T>
void readFile(const char* fname, int byteSz, int numVals, T* outVal);

void readRF(Parameters& p, Eigen::Ref<Eigen::Matrix<short int, -1, -1>> SIG, std::string suffix);

void readRFmultiFrame(Parameters& p, Eigen::Ref<Eigen::Matrix<short int, -1, -1>> SIG, std::string suffix);

void init(Parameters& p, std::string suffix);


#endif // BINARYFILEREADER_H_INCLUDED
