function gesturenum = testinghmm_4doctave 
clear;
 clc;
 addpath("/home/ye/octave_test/test/HMMall/HMM");
addpath("/home/ye/octave_test/test/HMMall/KPMstats");
addpath("/home/ye/octave_test/test/HMMall/KPMtools");


load HMMparameters4d.mat;
load hmmdata.mat;
load hmmtest.txt;

[m n] = size(hmmtest);
data = hmmtest(m-9:m, :);

for i =1 : 10
   a = data(i,:);  
  [value clst(i)] = min(          sum(((repmat(a,6,1) - C).^2)')    );
end 
%sequence length
l=10;
%load test.txt;
data = clst; 

loglik(1) = dhmm_logprob(data, prior21, transmat21, obsmat21);
loglik(2) = dhmm_logprob(data, prior22, transmat22, obsmat22);
loglik(3) = dhmm_logprob(data, prior23, transmat23, obsmat23);



[value class] = max(loglik); 

threshold1=-10;


if value<threshold1
    gesturenum = 0; %no gesture made.
else gesturenum = class;
end




            


