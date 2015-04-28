%% Vulture Neck Redesign
%Created on 10/23/2013 and Last Modified on 10/23/2013

close all
clear all
clc
%% Variables
r1 = 8.50;  %inches
r2 = 5.5283361; %inches
r3 = 3:.25:8;    %inches
theta1 = 289.06;    %degrees
angleNeckR2 = 18.258469;    %inches

%% Calculations
% a = r1*cosd(theta1);
% b = r1*sind(theta1);

gamma = acosd((r3.^2 - r1^2 - r2^2)/(-2*r1*r2));
beta = acosd((r2^2 - r1^2 - r3.^2)./(-2*r1.*r3));
  
theta2 = gamma+theta1-360;
theta3 = -180+theta1-beta;

alpha = -(theta2 + angleNeckR2);