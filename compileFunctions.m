function compileFunctions(srcFile,outputFolder,compiler)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

    % generate include paths
    currentDir = regexp(mfilename('fullpath'), filesep, 'split');
    currentDir(end) = [];
    ipathEIGEN = ['-I' fullfile(currentDir{:},'lib','eigen-3.4.0')]; % mfilename also includes the filename in the directory, so we need to remove that
    ipathINC = ['-I' fullfile(currentDir{:},'inc')];
    ipathSRC = ['-I' fullfile(currentDir{:},'src')];
    
    % generate full path filenames
    cppFiles{1} = fullfile(currentDir{:},'src','mexWrappers',append(srcFile,'.cpp'));

    % library path using downloaded copy of fftw library
    lpathFFTW = ['-L',fullfile(currentDir{:},'lib')];
    libname = '-llibfftw3-3';
    lpathSTATIC = ['-L',fullfile(currentDir{:},'lib','bin','Release','libBeamformingLibrary.a')];
%     libnameSTATIC = '-llibBeamformingLibrary.a';

    if (compiler)
        mex(append('-setup:',fullfile(matlabroot,'bin',computer('arch'),'mexopts','mingw64_g++.xml')),['C++'])

        mingwFlags = {'CXXFLAGS="$CXXFLAGS -march=native -std=c++14 -fno-math-errno -ffast-math -fopenmp -DNDEBUG"',...
            'LDFLAGS="$LDFLAGS -fopenmp"','CXXOPTIMFLAGS="-O3"'};
        
        mex(ipathEIGEN,ipathINC,ipathSRC,lpathFFTW,libname,lpathSTATIC,...libnameSTATIC,...
            mingwFlags{1},mingwFlags{2},mingwFlags{3},cppFiles{1},'-outdir',outputFolder);

    else
        mex(append('-setup:',fullfile(matlabroot,'bin',computer('arch'),'mexopts','msvcpp2019.xml')),['C++'])

        VSFlags = 'COMPFLAGS="$COMPFLAGS /arch:AVX2 /arch:AVX /std:c++14 /fp:fast /openmp:experimental"';
        
        mex(ipathEIGEN,ipathINC,lpathFFTW,libname,lpathSTATIC,VSFlags,cppFiles{1},'-outdir',outputFolder);
    end

end

