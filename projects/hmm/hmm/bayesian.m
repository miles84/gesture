function [gesturenum1 likeli1 gesturenum2 likeli2 ges_type likelihood alpha_1, Obs] = bayesian(dataa,object,alpha_0,Obs_p)


addpath("/home/ascc/projects/hmm/HMMall/HMM");
addpath("/home/ascc/projects/hmm/HMMall/KPMstats");
addpath("/home/ascc/projects/hmm/HMMall/KPMtools");

load HMMparameters4d_20_kitchen.mat;

%load hmmdata.mat;

%thres = sum(var(dataa));
for i =1 : 15
   a = dataa(i,:);  
  [value clst(i)] = min(sum(((repmat(a,8,1) - C).^2)'));
end 
%sequence length

%load test.txt;
%/home/gang/projects/hmm/hmm/hmm_octavenotxt_20_kitchen2.m
%%%%%%%%%%%%%%%%%%%%%%%%%%%without object information%%%%%%%%%
loglik(1) = dhmm_logprob(clst, prior21, transmat21, obsmat21);
loglik(2) = dhmm_logprob(clst, prior22, transmat22, obsmat22);
loglik(3) = dhmm_logprob(clst, prior23, transmat23, obsmat23);
loglik(4) = dhmm_logprob(clst, prior24, transmat24, obsmat24);
loglik(5) = dhmm_logprob(clst, prior25, transmat25, obsmat25);
loglik(6) = dhmm_logprob(clst, prior26, transmat26, obsmat26);

[likeli1 class] = max(loglik); 

if class==1 && (likeli1 <-200)
gesturenum1 = 7;
elseif( (class==2) && (likeli1<-25) && (likeli1>-30) )  || (class==2 && likeli1<-200) 
gesturenum1 = 7;
elseif (class==3 && likeli1 <-200)|| (class==3 && likeli1 >-10)
gesturenum1 = 7;
elseif class==4 && (likeli1 <-120)
gesturenum1 = 7;
elseif class==5 && (likeli1 <-200)
gesturenum1 = 7;
elseif (class==6 && likeli1 <-200) |(class==6 && likeli1 >-21)
gesturenum1 = 7;
%
else
gesturenum1 = class;
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%with object information%%%%%


if object == 1 %milk
loglik(3) = loglik(2)*0.95;
loglik(4) = loglik(4)*5;
loglik(6) = loglik(6)*5;

elseif object==2 % cereal
loglik(1) = loglik(1)*50;
loglik(2) = loglik(2)*50;
loglik(3) = loglik(3)*50;
loglik(4) = loglik(4)*50;
loglik(5) = loglik(5)*50;
loglik(6) = loglik(6)*0.2;

elseif object==3% bowl 
loglik(2) = loglik(2);
loglik(3) = loglik(2);

loglik(4) = loglik(4)*0.5;
loglik(5) = loglik(5)*5;
loglik(6) = loglik(6)*10;

elseif object==4% cup 
loglik(3) = loglik(2)*1.2;
loglik(2) = loglik(2);
loglik(4) = loglik(4)*50;
loglik(5) = loglik(5)*5;
loglik(6) = loglik(6)*30;
elseif  object==5%coffee
loglik(1) = loglik(1)*10;
loglik(2) = loglik(2)*10;
loglik(3) = loglik(3)*10;
loglik(4) = loglik(4)*10;
loglik(5) = loglik(5)*10;
loglik(6) = loglik(6)*0.2;
else %no object is selected
loglik(1) = -1000;
loglik(2) = -1000;
loglik(3) = -1000;
loglik(4) = -1000;
loglik(5) = -1000;
loglik(6) = -1000;


end


[likeli2 class] = max(loglik); 

%if (class==1 && value > -10) | (class==1 && value < -70)
if class==1 && (likeli2 <-200)
gesturenum2 = 7;
elseif( (class==2) && (likeli2<-25) && (likeli2>-30) )  || (class==2 && likeli2<-200) 
gesturenum2 = 7;
elseif (class==3 && likeli2 <-200) || ( (class==3) && (likeli2<-25) && (likeli2>-30) ) 
gesturenum2 = 7;
elseif class==4 && (likeli2 <-120)
gesturenum2 = 7;
elseif class==5 && (likeli2 <-200)
gesturenum2 = 7;
elseif (class==6 && likeli2 <-200) || ( (class==6) && (likeli2<-4) && (likeli2>-5) ) 
gesturenum2 = 7;
%
else
gesturenum2 = class;
end

%%high-level hmm

%if (gesturenum2 != 7)
Obs = gesturenum2;
%%% add condition when hhmm is run
[value index] = max(alpha_0);
if Obs~=7
[ges_type, likelihood, alpha_1] = hhmm_2(alpha_0, Obs, Obs_p);
else %filtering is not working
ges_type = Obs;
likelihood = 101;
alpha_1 = alpha_0;
end
%else
%ges_type = 7;
%likelihood = 100;
%alpha_1 = alpha_0;
%end

end

