function [gesturenum value gesturenum2 value2] = hmm_dtw(dataa)


addpath("/home/gang/projects/hmm/HMMall/HMM");
addpath("/home/gang/projects/hmm/HMMall/KPMstats");
addpath("/home/gang/projects/hmm/HMMall/KPMtools");

load HMMparameters4d_20.mat;
load template.mat;
%load hmmdata.mat;

thres = sum(var(dataa));
for i =1 : 20
   a = dataa(i,:);  
  [value clst(i)] = min(sum(((repmat(a,6,1) - C).^2)'));
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

var_thres = 100;

%like=value;

if thres<var_thres 
gesturenum = 0;
else 

if class==1 && value<-72
gesturenum = 0;
elseif class==2 && value <-80
gesturenum = 0;
elseif class==3 && value <-200
gesturenum = 0;
elseif (class==4 && value > -5 && value<-4) | (class==4 && value < -200)
gesturenum = 0;
elseif class==5 && value <-200
gesturenum = 0;
else
gesturenum = class;
end


end


%%%dtw

dis(1) = dtw(clst, template1);
dis(2) = dtw(clst, template2);
dis(3) = dtw(clst, template3);
dis(4) = dtw(clst, template4);
dis(5) = dtw(clst, template5);

[value2 class2] = min(dis); 
if value2>0.9
gesturenum2 = 0;
else
gesturenum2 = class2;

end

%plot(gesturenum);
%figure

            


