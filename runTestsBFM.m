function [image,matT] = runTestsBFM(beamform,RFdata,type)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

switch type
    case 'computeDASBMode'
        myFun = @(input) beamform.computeDASBMode(input);
    case 'computeDASDPC'
        myFun = @(input) beamform.computeDASDPC(input);
    otherwise
        error('Invalid Beamformer type')
end


%% Initial Beamform Test
tic; chk = myFun(RFdata); toc
tic; image = myFun(RFdata); toc

figure
colormap gray
imagesc(image)

%% Timing Testing
matT = zeros(100,1);
for i = 1:length(matT)
    tic
    chk = myFun(RFdata);
    matT(i) = toc;
end
mean(matT)
end