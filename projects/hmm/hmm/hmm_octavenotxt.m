function [value gesturenum] = hmm_octavenotxt(dataa)


addpath("/home/ye/octave_test/test/HMMall/HMM");
addpath("/home/ye/octave_test/test/HMMall/KPMstats");
addpath("/home/ye/octave_test/test/HMMall/KPMtools");

load HMMparameters4d.mat;

%load hmmdata.mat;


for i =1 : 40
   a = dataa(i,:);  
  [value clst(i)] = min(          sum(((repmat(a,8,1) - C).^2)')    );
end 
%sequence length

%load test.txt;


loglik(1) = dhmm_logprob(clst, prior21, transmat21, obsmat21);
loglik(2) = dhmm_logprob(clst, prior22, transmat22, obsmat22);
loglik(3) = dhmm_logprob(clst, prior23, transmat23, obsmat23);
loglik(4) = dhmm_logprob(clst, prior24, transmat24, obsmat24);
loglik(5) = dhmm_logprob(clst, prior25, transmat25, obsmat25);

%plot(a);

[value class] = max(loglik); 

threshold1=-30;
threshold2=-11;
threshold3=-15;
threshold4=-15;
threshold5=-11;

%like=value;
if class==1
    if value>threshold1
    gesturenum = 1; %no gesture made.
    else
    gesturenum = 0;
    end
elseif class ==2 
    if value>threshold2
    gesturenum = 2; %no gesture made.
    else
    gesturenum = 0;
    end

elseif class==3
    if value>threshold3
    gesturenum = 3; %no gesture made.
    else
    gesturenum = 0;
    end
elseif class==4
    if value>threshold4
    gesturenum = 4; %no gesture made.
    else
    gesturenum = 0;
    end
else
    if value>threshold5
    gesturenum = 5; %no gesture made.
    else
    gesturenum = 0;
    end

end

plot(gesturenum,"o"); hold on;





            


