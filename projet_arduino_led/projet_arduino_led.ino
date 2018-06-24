/** 
 *  Projet Arduino avec un capteur pour changer la couleur 
 *  et un autre pour changer l'intensité
 *  
 *  25/06/2018
 *  
 *  Maryam Abloua et Evlyn Dezegher
 */

#define sensorA0 A0 // Capteur pour la couleur 
#define sensorA1 A1 // Capteur pour l'intensité

const int R = 9; // Broche Rouge
const int G = 10; // Broche Vert
const int B = 11; // Broche Bleu 

#define ALLUME LOW
#define ETEINT HIGH

// Configuration par défaut 
void setup()
{
  Serial.begin(9600); 

  // Broches de sortie
  pinMode(R, OUTPUT); 
  pinMode(G, OUTPUT); 
  pinMode(B, OUTPUT); 

  // Couleurs toutes éteintes au démarrage
  digitalWrite (R, ETEINT); 
  digitalWrite (G, ETEINT); 
  digitalWrite (B, ETEINT); 
}

// Lecture en boucle des capteurs
void loop()
{
  /**************** Capteur pour la couleur (A0) ****************/ 

  float voltsA0 = analogRead(sensorA0)*0.0048828125; 
  int distanceA0 = 13*pow(voltsA0, -1); /* Distance en centimètres */ 
  int couleur;

  /* Définition des couleurs
   *  
   * Intervalle 0 à 7 cm : Rouge --> extinction de bleu et vert
   * Intervalle 7 à 14 cm : Vert --> extinction de rouge et bleu 
   * Reste : Bleu --> extinction de rouge et vert
   */
 if(distanceA0 >= 0 && distanceA0 < 7) {
      couleur = R; 
      digitalWrite(G, ETEINT);
      digitalWrite(B, ETEINT);
  } else if(distanceA0 >= 7 && distanceA0 < 14) {
      couleur = G;
      digitalWrite(R, ETEINT);
      digitalWrite(B, ETEINT);
  } else {
      couleur = B;
      digitalWrite(R, ETEINT);
      digitalWrite(G, ETEINT);
  } 

  /**************** Capteur pour l'intensité (A1) ****************/ 
  
  float voltsA1 = analogRead(sensorA1)*0.0048828125; 
  int distanceA1 = 13*pow(voltsA1, -1); /* Distance en centimètres */ 

  /* Définition de l'intensité 
   * 
   * Intervalle 0 à 7 cm : 0
   * Intervalle 7 à 14 cm : 128
   * Reste : 255 
   */
  if(distanceA1 >= 0 && distanceA1 < 7) {
      analogWrite(couleur, 0); 
  } else if(distanceA1 >= 7 && distanceA1 < 14) {
      analogWrite(couleur, 128); 
  } else {
      analogWrite(couleur, 255); 
  } 
}

