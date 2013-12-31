function [ges_type, likelihood, alpha_1] = hhmm(alpha_0, Obs)

%Obs is the classification output from low-level, from 1-3
%alpha_0 initially is 1/4.
Transi_matrix = [0.75 0.00 0.00 0 0 0 0.25; 0.0 0.75 0.00 0 0 0 0.25; 0.0 0.0 0.75 0 0 0 0.25; 0 0 0 0.75 0 0 0.25; 0.0 0 0 0 0.75 0 0.25; 0.0 0 0 0.0 0 0.8 0.20; 1/7 1/7 1/7 1/7 1/7 1/7 1/7];
Obs_matrix = [0.70 0.02 0.02 0.11 0 0 0.1; 0.0 0.7 0 0 0 0 0.3; 0.05 0.0 0.75 0 0 0 0.20; 0 0 0 0.75 0 0 0.25; 0 0 0 0 0.9 0 0.1; 0 0 0 0 0 0.78 0.22; 0.05 0.05 0.05 0.05 0.05 0.05 0.7];





for j =1:7
alpha_1(j) = Obs_matrix(j, Obs) * sum (Transi_matrix(:, j).*alpha_0');
end


[likelihood ges_type] = max(alpha_1);

end


