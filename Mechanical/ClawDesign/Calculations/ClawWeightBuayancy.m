clear,clc;

densityWater = 1000;

%Pipe + submarine +rock + motor PSRM
weightPSRM = 1.1954;

buancyPSRM = 6.0912;

thicknessPlate = 0.003; %Thickness of the plate

widthPlate = 0.08; %Width of the plate

lengthPlate = 0.2; %Length of the plate

plateVolume = thicknessPlate * widthPlate * lengthPlate; %Volume of the plate

aluminiumDensity = 2700;

weightPlate = aluminiumDensity * plateVolume;

buancyPlate = plateVolume * densityWater;

buancyWholeClaw = buancyPlate +buancyPSRM;

weightWholeClaw = weightPlate + weightPSRM;
