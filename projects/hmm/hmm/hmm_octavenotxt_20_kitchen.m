function [gesturenum value] = hmm_octavenotxt_20_kitchen(dataa)


addpath("/home/gang/projects/hmm/HMMall/HMM");
addpath("/home/gang/projects/hmm/HMMall/KPMstats");
addpath("/home/gang/projects/hmm/HMMall/KPMtools");

load HMMparameters4d_20_kitchen.mat;

%load hmmdata.mat;

thres = sum(var(dataa));
for i =1 : 15
   a = dataa(i,:);  
  [value clst(i)] = min(sum(((repmat(a,8,1) - C).^2)'));
end 
%sequence length

%load test.txt;


loglik(1) = dhmm_logprob(clst, prior21, transmat21, obsmat21);
loglik(2) = dhmm_logprob(clst, prior22, transmat22, obsmat22);
loglik(3) = dhmm_logprob(clst, prior23, transmat23, obsmat23);
loglik(4) = dhmm_logprob(clst, prior24, transmat24, obsmat24);
loglik(5) = dhmm_logprob(clst, prior25, transmat25, obsmat25);
loglik(6) = dhmm_logprob(clst, prior26, transmat26, obsmat26);

%plot(a);

%for i=1:3
%if loglik(i)<-1000
%loglik(i)=-1000;
%end
%end
%for i=1:3
%log_ratio(i) = 1/loglik(i)/sum(1./loglik);
%end

[value class] = max(loglik); 



%like=value;


%if (class==1 && value > -10) | (class==1 && value < -70)
if class==1 && (value <-200)
gesturenum = 0;
elseif (class==2 && value<-200)
% || (class==2 && value>-2.7*2) 
gesturenum = 0;
elseif (class==3 && value <-200) 
gesturenum = 0;
elseif (class==4 && value <-200)
gesturenum = 0;
elseif (class==5 && value <-200)
gesturenum = 0;

else
gesturenum = class;
end



%plot(gesturenum);
%figure

            
