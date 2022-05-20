function [param,RFdata] = initParams(dataFile,filetype)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

    if (filetype == 0) % Loading for CPP test folder
        currentDir = regexp(mfilename('fullpath'), filesep, 'split');
        load(fullfile(currentDir{1:end-1},'data',dataFile),'Trans','P','Resource',...
            'Receive','TW','TX','RcvData');

        TXangle = reshape([TX(:).Steer],2,[]);
        TXangle = TXangle(1,:);
        na = length(TXangle);
        RFdata = RcvData{1}(:,:,1);
        
        VSonicsInit;
    elseif (filetype == 1)  % Verasonics GUI saved data with unscrambled RF output
        load(strcat(dataFile{1},dataFile{3}))
        load(strcat(dataFile{1},dataFile{2}))
        [RFLarge,TXangle,TXdelay,TXapod,Receive,Trans,TW,P] = Unscramble(preSet,RcvData);

        nAng = 15;
        angSamp = linspace(1,size(RFLarge,3),nAng);
        % angSamp = round(linspace(size(RFData,3)/4,3*size(RFData,3)/4,nAng));
        RFdata = RFLarge(:,:,angSamp);
        TXdelay = TXdelay(:,angSamp);
        TXangle = TXangle(angSamp);
        Resource.RcvBuffer.rowsPerFrame = 80000;
        Resource.Parameters.numRcvChannels = 256;
        Resource.Parameters.speedOfSound = 1540;
        na = nAng;
        
        VSonicsInit;
    elseif (filetype == 2)  % "Messy" saved Verasonics data with single frame and scrambled RF data
        load(dataFile{1},'Trans','P','Resource','Receive','TW','TX','RcvData');
        TXangle = reshape([TX(:).Steer],2,[]);
        TXangle = TXangle(1,:);
        na = length(TXangle);
        RFdata = RcvData{1}(:,:,1);
        
        VSonicsInit;
    elseif (filetype == 3)  % "Messy" saved Verasonics data with single frame and performs unscrambling of RF data
        load(dataFile);
        TXangle = reshape([TX(:).Steer],2,[]);
        TXangle = TXangle(1,:);
        na = length(TXangle);
        RFdata = zeros(Receive(1).endSample-Receive(1).startSample+1,Trans.numelements,na);
        for i = 1:na
            RFdata(:,:,i) = RcvData{1}(Receive(i).startSample:Receive(i).endSample,Trans.Connector,1);
        end
        
        VSonicsInit;
    elseif (filetype == 4) % USTB resaved data in custom format
        url='http://ustb.no/datasets/';      % if not found data will be downloaded from here
        dataFile='PICMUS_carotid_cross.uff';
        
        % checks if the data is in your data path, and downloads it otherwise.
        % The defaults data path is under USTB's folder, but you can change this
        % by setting an environment variable with setenv(DATA_PATH,'the_path_you_want_to_use');
        tools.download(dataFile, url, data_path);
        
        b_data=uff.read_object([data_path filesep dataFile],'/beamformed_data');
        
        channel_data=uff.read_object([data_path filesep dataFile],'/channel_data');
        
        fs = channel_data.sampling_frequency;
        pitch = channel_data.probe.pitch;
        if (~isempty(channel_data.pulse))
            fc = channel_data.pulse.center_frequency;
        else
            fc = input('Pulse definition not found, please enter a center frequency or hit enter to quit: ');
            if (isempty(fc))
                "Exiting Program..."
                quit;
            end
        end
        c = channel_data.sound_speed;
        fnumber = 0.6;
        wvlToM = c/fc;
        % assuming L11 probe for now....
        t0 = channel_data.initial_time + (1.25 + 0.6/1000/wvlToM)/fc;
        
        chk = [channel_data.sequence(:).source];
        TXangle = [chk(:).azimuth];
        ElemPos = channel_data.probe.geometry(:,1);
        xCoord = b_data.scan.x_axis;
        zCoord = b_data.scan.z_axis;
        numEl = channel_data.probe.N_elements;
        na = channel_data.N_waves;
        szRFframe = channel_data.N_samples;
        szRF = szRFframe*na;
        szX = b_data.scan.N_x_axis;
        szZ = b_data.scan.N_z_axis;
        nc = numEl;
        ConnMap = 1:numEl;
        startSample = zeros(na,1);
        endSample = zeros(na,1);
        initFlag = 1;
        
        RFdata = zeros(szRF,numEl);
        for i = 1:na
            startSample(i) = ((i-1)*szRFframe+1);
            endSample(i) = i*szRFframe;
            RFdata(startSample(i):endSample(i),:) = channel_data.data(:,:,i);
        end
            
        
    elseif (filetype == 5) 
        load(strcat(dataFile{1},"preSet.mat"))
        clearvars RcvData
        load(strcat(dataFile{1},dataFile{2}))
        TXangle = reshape([TX(:).Steer],2,[]);
        TXangle = TXangle(1,:);
        na = length(TXangle);
        VSonicsInit;
        RFdata = RcvData{1}(:,:,1);
    elseif (filetype == 6)
        load(strcat(dataFile{1},"preSet.mat"))
        clearvars RcvData
        load(strcat(dataFile{1},dataFile{2}))
        TXangle = reshape([TX(:).Steer],2,[]);
        TXangle = TXangle(1,:);
        na = length(TXangle);
        VSonicsInit;
        szRFframe = szRFframe/2;
        RFdata = RcvData{1}(:,:,1);
    elseif (filetype == 7)
        load(dataFile{1})
        TXangle = reshape([TX(:).Steer],2,[]);
        TXangle = TXangle(1,:);
        na = length(TXangle);
        VSonicsInit;
        RFdata = RcvData{1};
    end


    param = struct('fs',fs,...
            'pitch', pitch,...
            'fc', fc,...
            'c', c,...
            'fnumber', fnumber,...
            't0',t0,...
            'TXangle',TXangle,...
            'ElemPos',ElemPos,...
            'xCoord',xCoord,...
            'zCoord',zCoord,...
            'numEl',numEl,...
            'szRF',szRF,...
            'szRFframe',szRFframe,...
            'szX',szX,...
            'szZ',szZ,...
            'na',na,...
            'nc',nc,...
            'ConnMap',ConnMap,...
            'startSample',startSample,...
            'endSample',endSample,...
            'initFlag',1);
        
    param.nPoints = param.szX*param.szZ;
    param.L = param.ElemPos(end)-param.ElemPos(1);
end

