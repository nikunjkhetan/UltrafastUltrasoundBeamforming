classdef DASDPC < recon.DAS
    %DAS parent beamforming class
    %   Matlab superclass that contains beamforming subclasses that apply
    %   DAS fundamentals. The parent class contains the properties while
    %   the subclasses implement the actual beamforming methods and contain
    %   the unique properties associated with each method
    
    properties
        wis(1,:) char
    end
    
    methods
        % Constructor
        function obj = DASDPC(param)
            
            % Input Checking
            if nargin == 0
                error('Please specify input parameter struct');
            elseif ~isstruct(param)
                error('Please specify input parameters as single struct');
            elseif nargin >= 2
                error('Too many input parameters');
            end
            
            obj = obj@recon.DAS(param);

            wisdom = generateWisdom(int16(obj.szZ), 1, obj);
            obj.wis = wisdom;
            
        end

        image = computeDASDPC(obj, RFData);        
        [image,chkT] = computeDASDPCTimed(obj, RFData);
        wisdom = generateWisdom(sizeVec, nXforms, obj);
    end
end