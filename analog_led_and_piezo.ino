int LED_PIN = 6;
int PIEZO_PIN = 8;
int INTENSITY_PIN = A0;

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
}

void loop() {
  int intensity = analogRead(INTENSITY_PIN);

  int lightVal = map(intensity, 0, 1023, 0, 255);
  Serial.println(lightVal);
  analogWrite(LED_PIN, lightVal);

  if (intensity > 32) {
    int toneVal = map(intensity, 0, 1023, 500, 1600);
    tone(PIEZO_PIN, toneVal);
  } else {
    noTone(PIEZO_PIN);
  }
}