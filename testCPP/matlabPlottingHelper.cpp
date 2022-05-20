#include "incHeaders.h"
#include "incCustomHeader.h"
#include "MatlabEngine.hpp"
#include "MatlabDataArray.hpp"
#include "matlabPlottingHelper.h"

void plotData(const Eigen::Ref<const Eigen::MatrixXd>& reconFrame)
{
    std::unique_ptr<matlab::engine::MATLABEngine> matlabPtr = matlab::engine::startMATLAB();

    matlab::data::ArrayFactory factory;


    matlab::data::Array outputs = factory.createArray<double>
            ({static_cast<size_t>(reconFrame.rows()),static_cast<size_t>(reconFrame.cols())},
            reconFrame.data(),reconFrame.data()+reconFrame.size());


    matlabPtr->feval(u"imagesc", outputs);
    matlabPtr->feval(u"colormap", factory.createCharArray("gray"));
    matlabPtr->eval(u"caxis([-0.5 0.5]); ");

    char c;
    std::cout << "Type something and hit enter to continue: " << std::endl;
    std::cin >> c;
}

void plotDPC(const Eigen::Ref<const Eigen::MatrixXd>& reconFrame)
{
    std::unique_ptr<matlab::engine::MATLABEngine> matlabPtr = matlab::engine::startMATLAB();

    matlab::data::ArrayFactory factory;


    matlab::data::Array outputs = factory.createArray<double>
            ({static_cast<size_t>(reconFrame.rows()),static_cast<size_t>(reconFrame.cols())},
            reconFrame.data(),reconFrame.data()+reconFrame.size());

    matlabPtr->feval(u"imagesc", outputs);
    matlabPtr->feval(u"colormap", factory.createCharArray("gray"));

    char c;
    std::cout << "Type something and hit enter to continue: " << std::endl;
    std::cin >> c;
}

void plotBModeDPC(const Eigen::Ref<const Eigen::MatrixXd>& reconBMode, const Eigen::Ref<const Eigen::MatrixXd>& reconDPC, Parameters& p)
{
    std::unique_ptr<matlab::engine::MATLABEngine> matlabPtr = matlab::engine::startMATLAB();

    matlab::data::ArrayFactory factory;


    matlab::data::Array BMode = factory.createArray<double>
            ({static_cast<size_t>(reconBMode.rows()),static_cast<size_t>(reconBMode.cols())},
            reconBMode.data(),reconBMode.data()+reconBMode.size());

    matlab::data::Array DPC = factory.createArray<double>
            ({static_cast<size_t>(reconDPC.rows()),static_cast<size_t>(reconDPC.cols())},
            reconDPC.data(),reconDPC.data()+reconDPC.size());

    matlab::data::Array s = factory.createArray<double>({1,1},{p.dz/p.pitch});

    matlabPtr->setVariable(u"s",s);
    matlabPtr->eval(u"figure; subplot(1,2,1);");
    matlabPtr->feval(u"imagesc", BMode);
    matlabPtr->eval(u"colormap(gray); set(gca,'DataAspectRatio',[s, 1, 1]); subplot(1,2,2); colormap(gray);");
    matlabPtr->feval(u"imagesc", DPC);
    matlabPtr->eval(u"caxis([-0.5,0.5])");
    matlabPtr->eval(u"set(gca,'DataAspectRatio',[s, 1, 1]);");

    char c;
    std::cout << "Type something and hit enter to continue: " << std::endl;
    std::cin >> c;
}

void plotSlidingData(const Eigen::Ref<const Eigen::MatrixXd>& reconFrame, Parameters& p)
{
    std::unique_ptr<matlab::engine::MATLABEngine> matlabPtr = matlab::engine::startMATLAB();

    matlab::data::ArrayFactory factory;


    Eigen::MatrixXd Recon = Eigen::MatrixXd::Zero(p.szZ, p.szX*p.na);

    for(int i = 0; i < p.na; i++)
    {

        Recon(Eigen::all,Eigen::seq(i*p.szX,(i+1)*p.szX-1)) = reconFrame(Eigen::seq(i*p.szZ,(i+1)*p.szZ-1),Eigen::all);

    }


    matlab::data::Array outputs = factory.createArray<double>
            ({static_cast<size_t>(Recon.rows()),static_cast<size_t>(Recon.cols())},
            Recon.data(),Recon.data()+Recon.size());

    matlab::data::CharArray path = factory.createCharArray("G:/Shared drives/Biomicroscopy Lab/Active Projects/Ultrasound/Utilities");
    matlab::data::Array params = factory.createArray<int32_t> ({3,1},{p.szZ,p.szX,p.na});

    matlabPtr->feval(u"cd",path);
    matlabPtr->setVariable(u"data",outputs);
    matlabPtr->setVariable(u"params",params);
    matlabPtr->eval(u"data = reshape(data,[params(1),params(2),params(3)]);");
    matlabPtr->eval(u"genSliderV2(data);");
    matlabPtr->eval(u"DPC = sum(data(:,:,1:end-1),3);");
    matlabPtr->eval(u"DPC = DPC/max(abs(DPC(:)));");
    matlabPtr->eval(u"figure; colormap gray; imagesc(DPC); caxis([-0.5 0.5]); ");

    char c;
    std::cout << "Type something and hit enter to continue: " << std::endl;
    std::cin >> c;
}

void plotSlidingRFData(Eigen::Ref<Eigen::Matrix<short int, -1, -1>> SIG, Parameters& p)
{
    std::unique_ptr<matlab::engine::MATLABEngine> matlabPtr = matlab::engine::startMATLAB();

    matlab::data::ArrayFactory factory;


    Eigen::Matrix<short int, -1, -1> Recon = Eigen::Matrix<short int, -1, -1>::Zero(p.szRFframe+1, p.numEl*p.na);

    for(int i = 0; i < p.na; i++)
    {
        Recon(Eigen::all,Eigen::seq(i*p.numEl,(i+1)*p.numEl-1)) = SIG(Eigen::seq(i*(p.szRFframe+1),(i+1)*(p.szRFframe+1)-1),p.ConnMap.array()-1);
    }
    Recon.row(0).setZero();


    matlab::data::Array outputs = factory.createArray<int16_t>
            ({static_cast<size_t>(Recon.rows()),static_cast<size_t>(Recon.cols())},
            Recon.data(),Recon.data()+Recon.size());

    matlab::data::CharArray path = factory.createCharArray("G:/Shared drives/Biomicroscopy Lab/Active Projects/Ultrasound/Utilities");
    matlab::data::Array params = factory.createArray<int32_t> ({3,1},{p.szRFframe+1,p.numEl,p.na});

    matlabPtr->feval(u"cd",path);
    matlabPtr->setVariable(u"data",outputs);
    matlabPtr->setVariable(u"params",params);
    matlabPtr->eval(u"data = reshape(data,[params(1),params(2),params(3)]);");
    matlabPtr->eval(u"genSliderV2(log(abs(double(data))));");

    char c;
    std::cout << "Type something and hit enter to continue: " << std::endl;
    std::cin >> c;
}


void plotIDXT(const Eigen::Ref<const Eigen::MatrixXf>& idxtChk, Parameters& p)
{
    std::unique_ptr<matlab::engine::MATLABEngine> matlabPtr = matlab::engine::startMATLAB();

    matlab::data::ArrayFactory factory;


    matlab::data::Array outputs = factory.createArray<float>
            ({static_cast<size_t>(idxtChk.rows()),static_cast<size_t>(idxtChk.cols())},
            idxtChk.data(),idxtChk.data()+idxtChk.size());

    matlab::data::CharArray path = factory.createCharArray("G:/Shared drives/Biomicroscopy Lab/Active Projects/Ultrasound/Utilities");
    matlab::data::Array params = factory.createArray<int32_t> ({3,1},{p.nPoints,p.numEl,p.na});

    matlabPtr->feval(u"cd",path);
    matlabPtr->setVariable(u"data",outputs);
    matlabPtr->setVariable(u"params",params);
    matlabPtr->eval(u"data = reshape(data,[params(1),params(2),params(3)]);");
    matlabPtr->eval(u"genSliderV2(data);");
    matlabPtr->eval(u"figure; plot(data(7908,:,2))");

    char c;
    std::cout << "Type something and hit enter to continue: " << std::endl;
    std::cin >> c;
}

void plotDTX(Eigen::Ref<Eigen::MatrixXd> dTX, Parameters& p)
{
    std::unique_ptr<matlab::engine::MATLABEngine> matlabPtr = matlab::engine::startMATLAB();

    matlab::data::ArrayFactory factory;


    matlab::data::Array outputs = factory.createArray<double>
            ({static_cast<size_t>(dTX.rows()),static_cast<size_t>(dTX.cols())},
            dTX.data(),dTX.data()+dTX.size());

    matlab::data::CharArray path = factory.createCharArray("G:/Shared drives/Biomicroscopy Lab/Active Projects/Ultrasound/Utilities");
    matlab::data::Array params = factory.createArray<int32_t> ({3,1},{p.szZ,p.szX,p.na});

    matlabPtr->feval(u"cd",path);
    matlabPtr->setVariable(u"data",outputs);
    matlabPtr->setVariable(u"params",params);
    matlabPtr->eval(u"data = reshape(data,[params(1),params(2),params(3)]);");
    matlabPtr->eval(u"genSliderV2(data);");

    char c;
    std::cout << "Type something and hit enter to continue: " << std::endl;
    std::cin >> c;
}

void plotDPC(Eigen::Ref<Eigen::MatrixXcd> reconFrame, Parameters& p)
{
    std::unique_ptr<matlab::engine::MATLABEngine> matlabPtr = matlab::engine::startMATLAB();

    Eigen::MatrixXcd Recon = Eigen::MatrixXcd::Zero(p.szZ, p.szX*p.na);

    for(int i = 0; i < p.na; i++)
    {

        Recon(Eigen::all,Eigen::seq(i*p.szX,(i+1)*p.szX-1)) = reconFrame(Eigen::seq(i*p.szZ,(i+1)*p.szZ-1),Eigen::all);

    }


    matlab::data::ArrayFactory factory;

    double fovShift = p.dz*p.tShift/(p.fs/p.fc);

    matlab::data::Array outputs = factory.createArray<std::complex<double>>
            ({static_cast<size_t>(Recon.rows()),static_cast<size_t>(Recon.cols())},
            Recon.data(),Recon.data()+Recon.size());

    matlab::data::CharArray path = factory.createCharArray("G:/Shared drives/Biomicroscopy Lab/Active Projects/Ultrasound/Utilities");
    matlab::data::Array params = factory.createArray<int32_t> ({3,1},{p.szZ,p.szX,p.na});
    matlab::data::Array TX = factory.createArray<double>({static_cast<size_t>(p.TXangle.size())},p.TXangle.data(),p.TXangle.data()+p.TXangle.size());
    matlab::data::Array xCoord = factory.createArray<double>({static_cast<size_t>(p.xCoord.size())},p.xCoord.data(),p.xCoord.data()+p.xCoord.size());
    matlab::data::Array params2 = factory.createArray<double> ({4,1},{p.c,p.fc,p.pitch,fovShift});

    matlabPtr->feval(u"cd",path);
    matlabPtr->setVariable(u"data",outputs);
    matlabPtr->setVariable(u"params",params);
    matlabPtr->setVariable(u"params2",params2);
    matlabPtr->setVariable(u"xCoord",xCoord);
    matlabPtr->setVariable(u"TXangle",TX);
    matlabPtr->eval(u"data = reshape(data,[params(1),params(2),params(3)]);");
    matlabPtr->eval(u"DPC = applyDPCV4(data,TXangle,xCoord,params2(1),params2(2),params2(3),params2(4));");
    matlabPtr->eval(u"DPC = DPC/max(abs(DPC(:)));");
    matlabPtr->eval(u"figure; colormap gray; imagesc(DPC); caxis([-0.5 0.5]); ");
//    matlabPtr->eval(u"figure; imagesc(sum(angle(data),3)); colormap gray");
//    matlabPtr->eval(u"genSliderV2(data);");

    char c;
    std::cout << "Type something and hit enter to continue: " << std::endl;
    std::cin >> c;
}


void animateData(const Eigen::Ref<const Eigen::MatrixXd>& Recon, Parameters& p)
{
    std::unique_ptr<matlab::engine::MATLABEngine> matlabPtr = matlab::engine::startMATLAB();

    matlab::data::ArrayFactory factory;

    matlab::data::Array outputs = factory.createArray<double>
            ({static_cast<size_t>(Recon.rows()),static_cast<size_t>(Recon.cols())},
            Recon.data(),Recon.data()+Recon.size());

    matlab::data::CharArray path = factory.createCharArray("G:/Shared drives/Biomicroscopy Lab/Active Projects/Ultrasound/Utilities");
    matlab::data::CharArray path2 = factory.createCharArray("G:/Shared drives/Biomicroscopy Lab/Active Projects/Ultrasound/Datasets/Figures Animations and Processed Data");
    matlab::data::Array params = factory.createArray<int32_t> ({3,1},{p.szZ,p.szX,20});

    matlabPtr->feval(u"cd",path2);
    matlabPtr->feval(u"addpath",path);
    matlabPtr->setVariable(u"data",outputs);
    matlabPtr->setVariable(u"params",params);
    matlabPtr->eval(u"data = reshape(data,[params(1),params(2),params(3)]);");
    matlabPtr->eval(u"genAnimation('CalfData',data,1:20,'imagesc',0.5,'frame');");
}
