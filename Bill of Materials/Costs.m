clear,clc

%change the number of items when adding new ones
numberItems = 5;


costs = zeros(numberItems,1);


%%%%%%%%%%%%% Already spent money

% 2 DC motors
i = 1;
costs(i) = 5;

%Double H bridge for 2 DC motors
i = i+1;
costs(i) = 2.15;

%item XY
i = i+1;
costs(i) = 10.15;


%Sum of already spent money
spending = sum(costs);

%%%%%%%%%%%%% Estimation

%item 
i = i+1;
costs(i) = 10.15;

%item blablabla
i = i+1;
costs(i) = 0.95;


%Calculate total sum
sumationEstimated = sum(costs);
%Calculate sum of estimated upcoming costs
estimationsSum = sumationEstimated -  spending;


% Print values
fprintf('Spending = %.02f\n', spending);
fprintf('Estimated upcoming costs = %.02f\n', sumationEstimated);
fprintf('Estimated system costs = %.02f\n', estimationsSum);

