float baseline = 0;

void setup() {
  pinMode(A0, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  analogReference(EXTERNAL);

  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  
  Serial.begin(9600);
  int steps = 4;
  Serial.print("Calibrating... ");
  for(int step = 0; step < steps; step++) {
    float tempC = readingToTemp(analogRead(A0));
    baseline += tempC;
    delay(1000);
  }
  baseline /= steps;
  Serial.print("Calibration completed. Baseline temperature is (in C): ");
  Serial.println(baseline);

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
}

void loop() {
  float tempC = readingToTemp(analogRead(A0));

  if (tempC > baseline+1 && tempC <= baseline+2) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  } else if (tempC > baseline+2 && tempC <= baseline+3) {
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  } else if (tempC > baseline+3 && tempC <= baseline+4) {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
  } else if (tempC > baseline+4) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
  } else {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }
  
  delay(1000);   
}

float readingToTemp(int reading) {
  float voltage = (reading * 3.3) / 1024.0;
  return (voltage - 0.5) * 100 ;
}
