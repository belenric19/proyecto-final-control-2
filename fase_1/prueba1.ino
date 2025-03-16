// ----- CONTROL PWM DE UNA BOMBA DE AGUA -----

// Pines bomba de agua
const int PWMA = 2;
const int AIN1 = 3;
const int STBY = 4;

// Pines potenciómetro
const int pot = A0;
int lectura_pot;


void setup() {
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(STBY, OUTPUT);

  digitalWrite(STBY, HIGH);

  Serial.begin(9600);
}

void loop() {
  // Control e impresión del PWM de la bomba de agua
  lectura_pot = analogRead(pot);
  int salida = map(lectura_pot, 0, 1023, 0, 255);
  analogWrite(PWMA, salida);
  digitalWrite(AIN1, HIGH);

  Serial.print("PWM: ");
  Serial.println(salida);

  delay(100); 
}
