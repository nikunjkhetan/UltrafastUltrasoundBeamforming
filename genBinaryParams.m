% Generate binaries for a given dataset and parameters for codeblocks
% testing

%% Define Filename
clearvars
close all

% dataFilePath = 'Datasets\Spherical Inclusions Data\';
% dataFileName = 'RFData127A12RT4S_20mm'; % file name
% dataPreSets = 'RFData127A12R_preSet';
% dataFile{1} = dataFilePath; dataFile{2} = dataFileName; dataFile{3} = dataPreSets;
% filetype = 1;
% fileSuffix = "Sphere.bin";

% dataFile = 'simData';
% filetype = 0;
% fileSuffix = "sim.bin";

% dataFile{1} = 'G:\Shared drives\Biomicroscopy Lab\Active Projects\Ultrasound\Datasets\FlashAngles Data\PlaneWaveFlashAngles15OffsetPos.mat';
% filetype = 2;
% fileSuffix = "TallElastic.bin";

% dataFile{1} = 'G:\Shared drives\Biomicroscopy Lab\Active Projects\Ultrasound\Datasets\CPP Test Data\TallVerticalPoints.mat';
% filetype = 2;
% fileSuffix = "Tall.bin";

% dataFile{1} = 'G:\Shared drives\Biomicroscopy Lab\Active Projects\Ultrasound\Datasets\CPP Test Data\Type4Sphere_20mm.mat';
% filetype = 2;
% fileSuffix = "Sphere.bin";

% dataFile{1} = 'G:\Shared drives\Biomicroscopy Lab\Active Projects\Ultrasound\Datasets\CPP Test Data\TallElasticTargets.mat';
% filetype = 2;
% fileSuffix = "TallElastic.bin";

% CPP Test Data Tall Elasticity targets
% dataFile{1} = 'G:\Shared drives\Biomicroscopy Lab\Active Projects\Ultrasound\Datasets\CPP Test Data\Tall10KPA.mat';
% filetype = 2;
% fileSuffix = "Tall10KPA.bin";

% PICMUS carotid cross section
% dataFile{1} = 'PICMUS_carotid_cross.uff';
% filetype = 4;
% fileSuffix = "CarotidCross.bin";

% Calf data
% dataFile{1} = "G:\Shared drives\Biomicroscopy Lab\Active Projects\Ultrasound\Datasets\Calf Data\";
% filetype = 5;

% dataFile{2} = "RFdata Angle1 Strained.mat";
% fileSuffix = "Angle1Strain.bin";

% dataFile{2} = "RFdata Angle1 unStrained.mat";
% fileSuffix = "Angle1unStrain.bin";

% Calf data 2
% filetype = 6;

% dataFile{2} = "RFdata Angle2 Strained.mat";
% fileSuffix = "Angle2Strain.bin";

% dataFile{2} = "RFdata Angle2 unStrained.mat";
% fileSuffix = "Angle2unStrain.bin";


% Celiac Trunk
% dataFile{1} = 'G:\Shared drives\Biomicroscopy Lab\Active Projects\Ultrasound\Datasets\random human datasets\RFdata_13-May-2022_20-04-25 celiac trunk.mat';
% filetype = 2;
% fileSuffix = "CeliacTrunk.bin";

dataFile{1} = 'G:\Shared drives\Biomicroscopy Lab\Active Projects\Ultrasound\Datasets\random human datasets\RFdataCalfMultiFrame.mat';
filetype = 7;
fileSuffix = "RFCalfMultiFrame.bin";


%% Load data
[p,RFdata] = initParams(dataFile,filetype);

P.startDepth = 0;
P.endDepth = 224;

wvlToM = p.c/(p.fc);

PData.PDelta = [p.pitch,0,0.5];
PData.Size = [(P.endDepth-P.startDepth)/PData.PDelta(3),192,1];
PData.Origin = [-PData.PDelta(1)*(PData.Size(2)-1)/2,0,P.startDepth];
%% Generate Binary files
% Generate double value binary file


filename = "paramsDoub" + fileSuffix;
fileID = fopen(filename,'w');
fwrite(fileID,p.fs,'double');
fwrite(fileID,p.pitch,'double');
fwrite(fileID,p.fc,'double');
fwrite(fileID,p.c,'double');
fwrite(fileID,p.fnumber,'double');
fwrite(fileID,p.t0,'double');
fwrite(fileID,p.TXangle(1),'double');
fwrite(fileID,mean(diff(p.TXangle)),'double');
fwrite(fileID,PData.PDelta(1),'double');        % 8
fwrite(fileID,PData.Origin(1),'double');        % 9
fwrite(fileID,PData.PDelta(3)*wvlToM,'double'); % 10
fwrite(fileID,PData.Origin(3)*wvlToM,'double'); % 11
fclose(fileID);

% Generate Integer binary file
filename = "paramsINT" + fileSuffix;
fileIDint = fopen(filename,'w');                
fwrite(fileIDint,p.numEl,'int32');              % 0
fwrite(fileIDint,p.szRF,'int32');               % 1
fwrite(fileIDint,p.szRFframe,'int32');          % 2
fwrite(fileIDint,PData.Size(2),'int32');        % 3
fwrite(fileIDint,PData.Size(1),'int32');        % 4
fwrite(fileIDint,p.na,'int32');                 % 5
fwrite(fileIDint,p.nc,'int32');                 % 6
fwrite(fileIDint,p.initFlag,'int32');           % 7
fclose(fileIDint);

% Generate mapping binary file
filename = "paramsMAP" + fileSuffix;
fileIDmap = fopen(filename,'w');
fwrite(fileIDmap,p.ConnMap,'int16');
fclose(fileIDmap);

% Generate RF binary file
filename = "RF" + fileSuffix;
fileIDRF = fopen(filename,'w');
fwrite(fileIDRF,RFdata(:),'int16');
fclose(fileIDRF);

% Generate Element Pos binary file
filename = "paramsPOS" + fileSuffix;
fileIDint = fopen(filename,'w');
fwrite(fileIDint,p.ElemPos,'double');
fclose(fileIDint);