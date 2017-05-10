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


%rock

mRock = 0.1; % maximum weight of a rock

rockRadius = 0.025; % approximate radius of a rock

rockVolume = (4/3) * pi * (rockRadius^3); %Use sphere volume to calculate the 

%volume of the rock

gravityForceRock = g * mRock; % gravitational force acting on the rock

buoyancyRock = g * waterDensity * rockVolume ;% buoyant force acting on the rock

rockForce = gravityForceRock - buoyancyRock; %difference between gravity and 

%buoyancy to get the net force acting on the rock





%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%PVC pipe

pipeOuterRadius = 0.055; % outer radius of the pipe

pipeInnerRadius = 0.052; %inner radius of the pipe

pipeThickness = 0.003; % thickness of the pipe

pipeLength = 0.3; % Length of the pipe

pvcDensity = 1350; % Material Density of PVC

pipeSectionSurface = pi * (pipeOuterRadius^2 - pipeInnerRadius^2); % Surface area

%of pipe section

pipeLidSurface = pi * (pipeOuterRadius^2 ); % lid surface area

pipeLengthVolume =pipeSectionSurface * pipeLength; % Volume of the pipe without lids

pipeLidsVolume = pipeLidSurface * pipeThickness; %Volume of one pipe lid

pipeVolume = pipeLengthVolume + 2 * pipeLidsVolume; % total volume of the pipe

mPipe = pvcDensity * pipeVolume; % weight of the pipe

buoyancyPipe = g * waterDensity * pipeVolume; % buoyant force acting on the pipe

gravityForcePipe = g * mPipe; %  gravitational force acting on the pipe

pipeForce = gravityForcePipe - buoyancyPipe; %difference between gravity and 

%buoyancy to get the net force acting on the pipe



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%submarine

mSubmarineMax = 0.5; % maximum submarine weights

mSubmarineMin = 0.3; % minimum submarine weights

gravityForceSubmarine = g * mSubmarineMax; % gravitational force acting on the submarine

%The submarine is roughly approximated to a tube

tubeLength = 0.275; % length of the sumarine

tubeOuterRadius =  0.0384/2; % Outer radius of the submarine

acrylicDensity = 1180; % Density of the submarine (submarine made from acrylic)

VsubmarineApprox = mSubmarineMin / acrylicDensity; % Approximate volume of 

%the submarine (Without  the water volume that is inside it

submarineSectionApprox = VsubmarineApprox /  tubeLength; % Approximate section

%suface area of the  submarine (without the water  inside it)

tubeInnerRadiusApprox = sqrt((tubeOuterRadius^2) - submarineSectionApprox / pi); % Inner 

%radius  of the submarine

VUnderEstimated = VsubmarineApprox / 2; % Under estimate the 

%volume to get a lower boyancy to get a greater net force acting on the submarine

buoyancySubmarine =  g * waterDensity * VUnderEstimated; %  buoancy acting on the pipe

submarineForce = gravityForceSubmarine - buoyancySubmarine; %difference between 

%gravity and buoyancy to get the net force acting on the pipe


%%%%%%%%%%%%%%%%%%% Summation of forces

%Sum of forces for the upper claw

sumUpperClaw = submarineForce + rockForce + (3 / 4) * pipeForce; % the upper claw 

%consists of three quarters of the pipe


%Sum of forces for the lower claw

sumLowerClaw = submarineForce + rockForce + (1 / 4) * pipeForce; % the upper claw

%consists of one quarters of the pipe


%%%%%%%%%%%%%%%%%%%%% Torque estimation

torqueUpperClaw = sumUpperClaw * 0.1; %To over estimate the force is assumed to be

%acting at the furthest point of the pipe.


torqueLowerClaw = sumLowerClaw * 0.05; %To over estimate the force is assumed to be

%acting at the furthest point of the pipe.


%%%%%%%%%%%%%%%%%%%%% Motor torque

torqueMotor = 2.4 * g * 0.01; % Stall Torque: 2.4kg / cm (4.8V)

torqueAllowedKgCmUpper = torqueUpperClaw / g / 0.01; %Torque allowed upperc claw 

torqueAllowedKgCmLower = torqueLowerClaw / g / 0.01; %Torque allowed lower claw

weight = mRock + mPipe +mSubmarineMax;

buoy = buoyancyPipe + buoyancyRock + buoyancySubmarine;