// Broches d'adresse
//const byte PIN_ENABLE = 5;
/*const byte PIN_ADDR_A = 4;
const byte PIN_ADDR_B = 3;
const byte PIN_ADDR_C = 2;
 
// Broche de signal
const byte PIN_SIG = 6;
 
void setup(){
  Serial.begin(9600);
  pinMode (PIN_SIG, INPUT);
  pinMode(PIN_ADDR_A, OUTPUT);
  pinMode(PIN_ADDR_B, OUTPUT); 
  pinMode(PIN_ADDR_C, OUTPUT); 
  digitalWrite(PIN_ADDR_A, LOW);
  digitalWrite(PIN_ADDR_B, LOW);
  digitalWrite(PIN_ADDR_C, LOW);
  
  //pinMode(PIN_ENABLE, OUTPUT);
  //digitalWrite(PIN_ENABLE, LOW);
 
}
 

void loop(){
 
  // Pour chaque voie on renvoie la valeur sur le port série
  for(byte i = 0; i < 8; i++){
    Serial.print("Voie ");
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(readAnalogMux(i));
  }
  
  // Delai pour l'affichage
  delay(1000);
}
 
int readAnalogMux(byte channel) {
  
  // On sélectionne la voie
  digitalWrite(PIN_ADDR_A, bitRead(channel, 0));
  digitalWrite(PIN_ADDR_B, bitRead(channel, 1));
  digitalWrite(PIN_ADDR_C, bitRead(channel, 2));
 
  // On lit la valeur courante
  return digitalRead(PIN_SIG);
}*/

// Broches d'adresse pour les 74HC4051
const byte PIN_ADDR_A = 4;
const byte PIN_ADDR_B = 3;
const byte PIN_ADDR_C = 2;

// Broches de sélection des multiplexeurs
const byte PIN_EN_1 = 7; // Enable pour le premier multiplexeur
const byte PIN_EN_2 = 8; // Enable pour le deuxième multiplexeur

// Broche de signal commune
const byte PIN_SIG = 6;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_SIG, INPUT);
  pinMode(PIN_ADDR_A, OUTPUT);
  pinMode(PIN_ADDR_B, OUTPUT);
  pinMode(PIN_ADDR_C, OUTPUT);
  pinMode(PIN_EN_1, OUTPUT);
  pinMode(PIN_EN_2, OUTPUT);

  digitalWrite(PIN_ADDR_A, LOW);
  digitalWrite(PIN_ADDR_B, LOW);
  digitalWrite(PIN_ADDR_C, LOW);
  digitalWrite(PIN_EN_1, HIGH); // Désactiver les multiplexeurs au début
  digitalWrite(PIN_EN_2, HIGH);
}

void loop() {
  // Pour chaque voie on renvoie la valeur sur le port série
  for (byte i = 0; i < 16; i++) {
    Serial.print("Voie ");
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(readAnalogMux(i));
  }
  
  // Délai pour l'affichage
  delay(1000);
}

int readAnalogMux(byte channel) {
  if (channel < 8) {
    // Sélectionner le premier multiplexeur
    digitalWrite(PIN_EN_1, LOW);
    digitalWrite(PIN_EN_2, HIGH);
  } else {
    // Sélectionner le deuxième multiplexeur
    digitalWrite(PIN_EN_1, HIGH);
    digitalWrite(PIN_EN_2, LOW);
    channel -= 8; // Ajuster le canal pour le deuxième multiplexeur
  }

  // Sélectionner la voie
  digitalWrite(PIN_ADDR_A, bitRead(channel, 0));
  digitalWrite(PIN_ADDR_B, bitRead(channel, 1));
  digitalWrite(PIN_ADDR_C, bitRead(channel, 2));

  // Lire la valeur courante
  return digitalRead(PIN_SIG);
}
