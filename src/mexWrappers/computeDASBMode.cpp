#include "MexHelper.h"

using matlab::mex::ArgumentList;

// defining class MexFunction that inherits from matlab::mex::Function

class MexFunction : public matlab::mex::Function {    
public:
    
    // Pointer to MATLAB engine to call fprintf
    std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();
    // Factory to create MATLAB data arrays
    matlab::data::ArrayFactory factory;

    void operator()(ArgumentList outputs, ArgumentList inputs) {

        // Check High Level Parameter consistency
        checkArguments(outputs, inputs);

        // Load Main Parameters
        matlab::data::Array object(inputs[0]);
        Parameters p;
        initParams(p,object);
        
        // Initialize input RF data
        matlab::data::TypedArray<int16_t> inRF = std::move(inputs[1]);
        Eigen::Matrix<short int, -1, -1> SIG = 
                Eigen::Map< Eigen::Matrix<short int, -1, -1> > 
                (inRF.release().get(), p.szRF, p.nc);
        
        Eigen::MatrixXd reconFrame = Eigen::MatrixXd::Zero(p.szZ, p.szX);
        computeDAS(p, SIG, reconFrame);
        
        
        outputs[0] = factory.createArray<double>
            ({static_cast<size_t>(reconFrame.rows()),static_cast<size_t>(reconFrame.cols())},
            reconFrame.data(),reconFrame.data()+reconFrame.size());
        
    }

    // Check input/output arguments for valid datatypes and sizes
    void checkArguments(ArgumentList outputs, ArgumentList inputs) {
//         if (inputs[0].getType() != matlab::data::ArrayType::STRUCT)
//         {
//             matlabPtr->feval(u"error", 0,
//                              std::vector<matlab::data::Array>({ factory.createScalar("Input Coordinates Should Be in a Struct") }));
//         }
//         
//         if (outputs.size() > 1) {
//             matlabPtr->feval(u"error", 0,
//                              std::vector<matlab::data::Array>({ factory.createScalar("Only one output is returned") }));
//         }
        
    }
    
    void initParams(Parameters& p, matlab::data::Array& obj) {
        
        // Load and initialize parameters
        const matlab::data::TypedArray<double> temp = matlabPtr->getProperty(obj, u"fs");
        p.fs = std::move(temp[0]);
        const matlab::data::TypedArray<double> temp1 = matlabPtr->getProperty(obj, u"pitch");
        p.pitch = std::move(temp1[0]);
        const matlab::data::TypedArray<double> temp2 = matlabPtr->getProperty(obj, u"fc");
        p.fc = std::move(temp2[0]);
        const matlab::data::TypedArray<double> temp3 = matlabPtr->getProperty(obj, u"c");
        p.c = std::move(temp3[0]);
        const matlab::data::TypedArray<double> temp4 = matlabPtr->getProperty(obj, u"fnumber");
        p.fnumber = std::move(temp4[0]);
        const matlab::data::TypedArray<double> temp5 = matlabPtr->getProperty(obj, u"t0");
        p.t0 = std::move(temp5[0]);
        const matlab::data::TypedArray<int> temp7 = matlabPtr->getProperty(obj, u"numEl");
        p.numEl = std::move(temp7[0]); // number of transducer elements
        const matlab::data::TypedArray<int> temp8 = matlabPtr->getProperty(obj, u"szRF");
        p.szRF = std::move(temp8[0]); // number of rows in rcv buffer
        const matlab::data::TypedArray<int> temp19 = matlabPtr->getProperty(obj, u"szRFframe");
        p.szRFframe = std::move(temp19[0]); // number of rows in single rcv acq
        const matlab::data::TypedArray<int> temp9 = matlabPtr->getProperty(obj, u"szX");
        p.szX = std::move(temp9[0]);
        const matlab::data::TypedArray<int> temp10 = matlabPtr->getProperty(obj, u"szZ");
        p.szZ = std::move(temp10[0]);
        const matlab::data::TypedArray<int> temp11 = matlabPtr->getProperty(obj, u"na");
        p.na = std::move(temp11[0]);
        const matlab::data::TypedArray<int> temp18 = matlabPtr->getProperty(obj, u"nc");
        p.nc = std::move(temp18[0]);// number of rcv channels aka columns in buffer

        // Load and initialize vector data
        matlab::data::TypedArray<double> temp6 = matlabPtr->getProperty(obj, u"TXangle");
        p.TXangle = Eigen::Map< Eigen::VectorXd > (temp6.release().get(),p.na);
        matlab::data::TypedArray<double> temp15 = matlabPtr->getProperty(obj, u"ElemPos");
        p.ElemPos = Eigen::Map< Eigen::VectorXd > (temp15.release().get(),p.numEl);
        matlab::data::TypedArray<double> temp16 = matlabPtr->getProperty(obj, u"xCoord");
        p.xCoord = Eigen::Map< Eigen::VectorXd > (temp16.release().get(),p.szX);
        matlab::data::TypedArray<double> temp17 = matlabPtr->getProperty(obj, u"zCoord");
        p.zCoord = Eigen::Map< Eigen::VectorXd > (temp17.release().get(),p.szZ);
        matlab::data::TypedArray<int> temp12 = matlabPtr->getProperty(obj, u"ConnMap");
        p.ConnMap = Eigen::Map< Eigen::VectorXi > (temp12.release().get(),p.numEl);
        matlab::data::TypedArray<int> temp13 = matlabPtr->getProperty(obj, u"startSample");
        p.startSample = Eigen::Map< Eigen::VectorXi > (temp13.release().get(),p.na);
        matlab::data::TypedArray<int> temp14 = matlabPtr->getProperty(obj, u"endSample");
        p.endSample = Eigen::Map< Eigen::VectorXi > (temp14.release().get(),p.na);

        // Dependent Parameters
        p.nPoints = p.szX*p.szZ;
        p.L = p.ElemPos(p.numEl-1)-p.ElemPos(0);
        
    }

};