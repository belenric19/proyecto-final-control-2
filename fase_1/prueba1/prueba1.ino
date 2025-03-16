// ----- CONTROL PWM DE UNA BOMBA DE AGUA -----

// Pines bomba de agua
const int PWMA = 2;
const int AIN1 = 3;
const int STBY = 4;

// Pines potenciómetro
const int pot = A0;
int lectura_pot;

// Pines sensor de corriente
const int sensor_corriente = A8;
float sensibilidad = 0.100; 

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

  // Lectura de la corriente desde el sensor
  float I = get_corriente(200); 
  Serial.print("Corriente: ");
  Serial.println(I, 3);

  if (I >= 1.0) {
    digitalWrite(STBY, LOW);
    digitalWrite(AIN1, LOW); 
    digitalWrite(PWMA, LOW); 
    Serial.println("Corriente mayor a 1A");
  }
  
  delay(100); 
}

float get_corriente(int n_muestras){
  float voltajeSensor;
  float corriente = 0;
  for (int i = 0; i < n_muestras; i++) {
    voltajeSensor = analogRead(sensor_corriente) * (5.0 / 1023.0); 
    corriente = corriente + (voltajeSensor - 2.5) / sensibilidad; 
  }
  corriente = corriente / n_muestras;
  return corriente;
}
