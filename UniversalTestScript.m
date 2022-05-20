%% Compile Functions
clearvars
% close all


srcFile = 'computeDASBMode';
% srcFile = 'computeDASDPC';

% doublecheck that this matches srcFolder
currentDir = regexp(cd, filesep, 'split');
outputFolder = fullfile(currentDir{:},'+reconraw','@DASBMode');
% outputFolder = fullfile(currentDir{:},'+reconraw','@DASDPC');
% outputFolder = 'C:\Users\verasonics\Desktop\Vantage-4.5.4-2108261500\System\+vsv\+reconraw\@DASDPC';

compiler = true; % true for minGW, false for Visual Studio

compileFunctions(srcFile,outputFolder,compiler);

%% Load Data and Generate Parameters
% CPP Test Data Tall Elasticity targets
dataFile{1} = 'G:\Shared drives\Biomicroscopy Lab\Active Projects\Ultrasound\Datasets\CPP Test Data\Tall10KPA.mat';
filetype = 2;
[param,RFdata] = initParams(dataFile,2);

% beamform = recon.DASBMode(param);
beamform = recon.DASDPC(param);

%% Compute Test Vals

[image,matT] = runTestsBFM(beamform,RFdata,srcFile);

