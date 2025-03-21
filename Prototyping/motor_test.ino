const int PWM1 = 5;
const int PWM2 = 6;
const int DIR1 = 4;
const int DIR2 = 7;


void setup() {
  pinMode(DIR1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);
}

void loop() {
  //digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(DIR1, HIGH);
  digitalWrite(DIR2, LOW);

  int i;
  for (i = 50; i < 256; i++) {
    analogWrite(PWM1, i);
    analogWrite(PWM2, i);
    delay(40);
  }
  for (i = 255; i > 49; i--) {
    analogWrite(PWM1, i);
    analogWrite(PWM2, i);
    delay(40);
  }
  digitalWrite(DIR1, LOW);
  digitalWrite(DIR2, HIGH);
  for (i = 50; i < 256; i++) {
    analogWrite(PWM1, i);
    analogWrite(PWM2, i);
    delay(40);
  }
  for (i = 255; i > 49; i--) {
    analogWrite(PWM1, i);
    analogWrite(PWM2, i);
    delay(40);
  }

}
