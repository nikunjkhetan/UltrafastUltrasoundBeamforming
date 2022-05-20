classdef DAS < handle
    %DAS parent beamforming class
    %   Matlab superclass that contains beamforming subclasses that apply
    %   DAS fundamentals. The parent class contains the properties while
    %   the subclasses implement the actual beamforming methods and contain
    %   the unique properties associated with each method
    
    properties
        fs(1,1) double {mustBeReal, mustBeFinite}
        pitch(1,1) double {mustBeReal, mustBeFinite}
        fc(1,1) double {mustBeReal, mustBeFinite}
        c(1,1) double {mustBeReal, mustBeFinite}
        fnumber(1,1) double {mustBeReal, mustBeFinite}
        t0(1,1) double {mustBeReal, mustBeFinite}
        TXangle(1,:) double {mustBeReal, mustBeFinite, mustBeVector}
        ElemPos(1,:) double {mustBeReal, mustBeFinite, mustBeVector}
        xCoord(1,:) double {mustBeReal, mustBeFinite, mustBeVector}
        zCoord(1,:) double {mustBeReal, mustBeFinite, mustBeVector}

        numEl(1,1) int32 {mustBeInteger}
        szRF(1,1) int32 {mustBeInteger}
        szRFframe(1,1) int32 {mustBeInteger}
        szX(1,1) int32 {mustBeInteger}
        szZ(1,1) int32 {mustBeInteger}
        na(1,1) int32 {mustBeInteger}
        nc(1,1) int32 {mustBeInteger}
        ConnMap(1,:) int32 {mustBeInteger, mustBeVector}
        startSample(1,:) int32 {mustBeInteger, mustBeVector}
        endSample(1,:) int32 {mustBeInteger, mustBeVector}
        
        initFlag(1,1) int16 {mustBeInteger}
    end
    
    
    methods
        % Constructor
        function obj = DASoffline(param)
            
            % Input Checking
            if nargin == 0
                error('Please specify input parameter struct');
            elseif ~isstruct(param)
                error('Please specify input parameters as single struct');
            elseif nargin >= 2
                error('Too many input parameters');
            end
            
            % Input form Checking
            obj.checkParams(param);
            
            % Initialize properties
            obj.setParams(param);
        end
        
        
        
    end
        
    methods(Access=protected,Sealed)
        function checkParams(obj,param)
            
            field = ["fs","pitch","fc","c","fnumber","t0","TXangle",...
                "numEl","szRF","szX","szZ","na","ConnMap","startSample",...
                "endSample","ElemPos","xCoord","zCoord","nc"];
            if ~all(isfield(param,field))
                error("Missing field(s): " + strjoin(field(~isfield(param,field)),', '));
            end
            
            % TODO insert variable size and type checks here
            
        end
        
    function setParams(obj,param)
            obj.fs = param.fs;
            obj.pitch = param.pitch;
            obj.fc = param.fc;
            obj.c = param.c;
            obj.fnumber = param.fnumber;
            obj.t0 = param.t0;
            obj.TXangle = param.TXangle;
            obj.numEl = param.numEl;
            obj.szRF = param.szRF;
            obj.szRFframe = param.szRFframe;
            obj.szX = param.szX;
            obj.szZ = param.szZ;
            obj.na = param.na;
            obj.nc = param.nc;
            obj.ConnMap = param.ConnMap;
            obj.startSample = param.startSample;
            obj.endSample = param.endSample;
            obj.ElemPos = param.ElemPos;
            obj.xCoord = param.xCoord;
            obj.zCoord = param.zCoord;
            obj.initFlag = 0;
        end
    end
end
