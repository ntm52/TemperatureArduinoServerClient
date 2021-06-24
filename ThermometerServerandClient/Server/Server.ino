int tempPin = 0;
int tempDesired = 0;

void setup() {

  Serial.begin(9600);

}

void loop() {

  if (Serial.available() > 0) {
    tempDesired = Serial.read();

    Serial.println(tempDesired, DEC);

    int tempReading = analogRead(tempPin);

    double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
    tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK)) * tempK);

    float tempCTemporary = tempK - 273.15;
    int tempF = (tempCTemporary * 9.0) / 5.0 + 32.0;
    int tempC = tempCTemporary * 1;
    // Temperatures received, do something with them

    if (tempDesired == 0) {
      Serial.write(tempF);
    } else {
      Serial.write(tempC);
    }
    
  }

}
