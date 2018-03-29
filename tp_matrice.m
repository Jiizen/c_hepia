# Matrice de 4x4
matrice = (round(rand(6,6)*100))
# matrice = [1:4 ; 3:6; 5:8; 6:9]

# 1. Déterminant
# matrice(2,2) = 0 
# matrice(2) = 0

#Fonction qui calcule de co-facteur
function cof = cofactor(matriceCof, i, j) %cof est la variable retournée
  cof = matriceCof; %on copie la matrice dans cof
  cof(i,:) = []; %supprime ligne
  cof(:,j) = []; %supprime colonne
endfunction

#Fonction qui calcule de déterminant
function det = determinant_2x2(A) 
 # Ne pas oublier de donner une valeur à la fonction det (resultat) 
  det = (A(1,1) * A(2,2)) - (A(2,1) * A(1,2)); 
endfunction

# Fonction déterminant général (NxN) qui s'appelle elle-même
function det = determinant_general(A)
  det = 0; # Initialisation de det 
      if rows(A) == 2  # Si c'est une matrice 2x2, on calcule le déterminant
      det = determinant_2x2(A); 
      else  # Autrement, on calcule le déterminant général (récursivité) 
          for j=1:rows(A)
              cof = cofactor(A, 1, j); # On réduit la matrice d'une dimension 
              det += A(1,j) * (-1)^(1 + j) * determinant_general(cof); # On calcule le déterminant de dimension N-1 (somme)
          endfor
      endif 
endfunction

determinant_general(matrice)
det(matrice)