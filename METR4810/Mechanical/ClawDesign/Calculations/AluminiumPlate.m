clear,clc;

% Unities (SI)

% mass Kg

% Length m

% Density Kg/(m^3)

% Acceleration N/Kg m/(s^2)

% Volume (m^3)

% Surface Area (m^2)

% Force N

% Torque Nm


%Constants

waterDensity = 1000; % Density of water

g = 9.81; % gravitational acceleration

%Plate


thicknessPlate = 0.003; %Thickness of the plate

widthPlate = 0.08; %Width of the plate

lengthPlate = 0.1; %Length of the plate

h = thicknessPlate; % heigth for the formula see below

b = lengthPlate; %width of the plate

I = (b * h^3)/12; %second moment of area

y = h/2; %furthest point from neutral axis

%Motor

weightMotor = 0.055;

lengthMotor = 0.0407;

widthMotor = 0.0197;

heightMotor = 0.0429;

volumeMotor = lengthMotor * widthMotor *heightMotor;

gravityMotor = weightMotor * g;

buancyMotor = volumeMotor * g * waterDensity;

%Pipe + Submarine + Rock => PSR

weightPSR = 1.0854;

gravityPSR = g * weightPSR;

buancyPSR = 5.4163;

%Total claw

gravityClaw = gravityPSR + 2 * gravityMotor;

buancyClaw = buancyPSR + 2 * buancyMotor;

forceClaw = gravityClaw - buancyClaw;

torqueClaw = forceClaw * 0.08;


E = 69 * 10^9; %young modulus of aluminium


sigmaMax = torqueClaw * y / I;

strain = sigmaMax / E; %strain

sigmaAllowedAluminium = 100 * 10^6;

ratioMaxAllowed = sigmaMax/sigmaAllowedAluminium;


