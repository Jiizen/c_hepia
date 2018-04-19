### Bonus : effet miroir sur l'axe horizontal ### 

clc;
clear all;
close all;

A = imread("kawaii_ice.jpg");

for i=1:(rows(A)/2) %parcoure la moitié du nombre de lignes
  for j=1:columns(A)
      A((rows(A)-i), j, :) = A(i, j, :); 
      %copie la pemière ligne sur la dernière
      %et ainsi de suite jusqu'à a moitié de l'image
  endfor
endfor 

imshow(A)