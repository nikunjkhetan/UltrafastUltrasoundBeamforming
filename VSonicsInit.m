xCoord = ((-Trans.numelements/2):(Trans.numelements/2)-1)*Trans.spacingMm*1e-3;
zCoord = (P.startDepth:0.5:224)*Resource.Parameters.speedOfSound/(Trans.frequency*1e6);

wvlToM = Resource.Parameters.speedOfSound/(Trans.frequency*1e6);

fs = Receive(1).decimSampleRate*1e6;
pitch = Trans.spacingMm*1e-3;
fc = Trans.frequency*1e6;
c = Resource.Parameters.speedOfSound;
fnumber = 0.6;
t0 = (-Receive(1).startDepth + TW.peak + Trans.lensCorrection)/(Trans.frequency*1e6);
ElemPos = Trans.ElementPos(:,1).'*wvlToM;
numEl = int32(Trans.numelements);
szRF=Resource.RcvBuffer.rowsPerFrame;
szRFframe=Receive(1).endSample-Receive(1).startSample;
szX=length(xCoord);
szZ=length(zCoord)-1;
nc=Resource.Parameters.numRcvChannels;
ConnMap=Trans.Connector.';
startSample=[Receive(1:na).startSample];
endSample=[Receive(1:na).endSample];
initFlag=1;