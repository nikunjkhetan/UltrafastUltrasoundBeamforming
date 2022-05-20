# UltrafastUltrasoundBeamforming
Repository for Custom C++ Ultrasound Beamforming Code

Structure of Repository:

Main Library Project file is in upper folder. Open that to load Code::Blocks library project. The output library is stored in lib\bin\... where there is a Release Folder and a Debug Folder with respective copies. Anything that needs the beamformer functions refers to these libraries which are '.a' files.

FFTW dll and lib file plus eigen library and other lib/dll files are also included in lib folder on the top level of the lib folder.

All header files are in the inc folder. 

All source .cpp files are located in src folder.

All data files (.bin files and .mat files) are located in the data folder. 

The mex source files are also included in the src folder but in their own subdirectory. The final versions of the mex files end up saved in their respective spots inside the +recon folder.

The testCPP project has its own source files that are meant to help load and test the code in a cpp environment to give access to debuggers and profilers (eventually Intel profiler). Here are the various build options necessary for both c++ projects and their respective builds:



testCPP Release Build:

Name											Purpose:
(Linker Search Paths)
C:\Program Files\MATLAB\R2020b\extern\bin\win64						All the key matlab DLLs to be linked.
C:\GitHub\UltrafastUltrasoundBeamforming\lib						All custom DLLs/other downloaded external DLLs to be linked.

(Compiler Search Paths)
C:\Program Files\MATLAB\R2020b\extern\include						All the matlab headers to be included in this directory
C:\GitHub\UltrafastUltrasoundBeamforming\inc						Include directory with header files
C:\GitHub\UltrafastUltrasoundBeamforming\lib\eigen-3.4.0				Eigen Library
C:\GitHub\UltrafastUltrasoundBeamforming\data						Data file locations


(Linker Settings aka libraries to link)
C:\Program Files\CodeBlocks\MinGW\bin\libgomp-1.dll					OMP library
C:\Program Files\MATLAB\R2020b\extern\lib\win64\mingw64\libMatlabDataArray.lib		Matlab Data Array Library
C:\Program Files\MATLAB\R2020b\extern\lib\win64\mingw64\libMatlabEngine.lib		Matlab Engine Library
C:\Program Files\MATLAB\R2020b\extern\bin\win64\libMatlabDataArray.dll.a		Redundant Matlab Engine Library?
C:\GitHub\UltrafastUltrasoundBeamforming\lib\libfftw3-3.lib				FFTW library
C:\GitHub\UltrafastUltrasoundBeamforming\lib\bin\Release\libBeamformingLibrary.a	Beamforming static library


(Compiler Flags)
-std=c++17
-O3
-fopenmp
-march=nehalem
-ffast-math
-fno-math-errno

