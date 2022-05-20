classdef DASBMode < recon.DAS
    %DAS parent beamforming class
    %   Matlab superclass that contains beamforming subclasses that apply
    %   DAS fundamentals. The parent class contains the properties while
    %   the subclasses implement the actual beamforming methods and contain
    %   the unique properties associated with each method
        
    
    methods
        % Constructor
        function obj = DASBMode(param)
            
            % Input Checking
            if nargin == 0
                error('Please specify input parameter struct');
            elseif ~isstruct(param)
                error('Please specify input parameters as single struct');
            elseif nargin >= 2
                error('Too many input parameters');
            end
            
            obj = obj@recon.DAS(param);
            
        end
        image = computeDAS(obj, RFData);            
    end
end