function [ges_type, likelihood, alpha_1] = hhmm_2(alpha_0, Obs, Obs_p)

%Obs is the classification output from low-level, from 1-3
%alpha_0 initially is 1/4.
 Transi_matrix = [0.5 0.4 0.2 0.2 0.2 0.2 0.1; 
                  0.3 0.63 0.4 0.2 0.3 0.2 0.07; 
                  0.2 0.2 0.75 0.2 0.2 0.2 0.25; 
                  0.2 0.2 0.2 0.75 0.2 0.2 0.25; 
                  0.2 0.2 0.2 0.2 0.8 0.2 0.2; 
                  0.2 0.0 0.3 0.0 0.2 0.8 0.20; 
                  1/7 1/7 1/7 1/7 1/7 1/7 1/7];


 Obs_matrix = [0.70 0.01 0.02 0.11 0 0 0.1; 
               0.0 0.50 0.3 0 0.2 0 0.00; 
               0.05 0.3 0.5 0 0 0 0.20; 
               0 0 0 0.75 0 0 0.25; 
               0 0.2 0 0 0.7 0 0.1; 
               0 0 0 0 0 0.78 0.22; 
               0.05 0.05 0.05 0.05 0.05 0.05 0.7];

%without 7
%Transi_matrix = [0.4 0.1 0.05 0.3 0.05 0.1; 
%                 0.2 0.6 0 0 0 0.2; 
%                 0.3 0 0.6 0 0 0.1; 
%                 0.2 0.1 0 0.5 0 0.2; 
%                 0.2 0.2 0 0 0.6 0; 
%                 0.1 0 0.25 0.25 0 0.4];
             
%Obs_matrix = [0.70 0.05 0.01 0.01 0.1 0.01; 
%              0.1 0.8 0.001 0 0.1 0.01; 
%              0.10 0.01 0.80 0.01 0.01 0.01; 
%              0.15 0.01 0.01 0.85 0.01 0.01; 
%              0.05 0.1 0.01 0.01 0.85 0.01; 
%              0.01 0.01 0.02 0.01 0.01 1];


%[value index] = max(alpha_0);

%for j =1:7
%alpha_0(j) = 0.2;
%end
%alpha_0(index) = 0.5;


for j =1:7
alpha_1(j) = Obs_matrix(j, Obs) * Transi_matrix(Obs_p, j);
end


%for j =1:7
%alpha_1(j) = Obs_matrix(j, Obs) * sum (Transi_matrix(:, j).*alpha_0');
%end




%normalized
%for j =1:7
%alpha_1(j) = alpha_1(j)/sum(alpha_1);
%end


[likelihood ges_type] = max(alpha_1);

end


