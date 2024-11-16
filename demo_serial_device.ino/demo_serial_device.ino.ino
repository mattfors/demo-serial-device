const int ledPin = LED_BUILTIN;
unsigned long startTime;

void setup() {
  Serial.begin(9600);
  while (!Serial) { }
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  startTime = millis();
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\r');
    input.trim(); // Trim the input string
    String response;

    if (input.startsWith("ECHO ")) {
      response = input.substring(5);
    } else if (input == "TIME") {
      response = getElapsedTime();
    } else if (input == "LIGHT ON") {
      digitalWrite(ledPin, HIGH);
      response = "Light turned on";
    } else if (input == "LIGHT OFF") {
      digitalWrite(ledPin, LOW);
      response = "Light turned off";
    } else if (input == "?") {
      response = "Available commands:\nECHO <message> - Echoes the message back\nTIME - Returns the elapsed time since the program started\nLIGHT ON - Turns on the built-in LED\nLIGHT OFF - Turns off the built-in LED\n? - Provides a summary of possible commands";
    } else {
      response = "E";
    }

    response += "\r\n";
    Serial.print(response);
  }
}

String getElapsedTime() {
  unsigned long elapsedTime = millis() - startTime;
  unsigned long seconds = elapsedTime / 1000;
  unsigned long minutes = seconds / 60;
  seconds = seconds % 60;
  return String(minutes) + "m " + String(seconds) + "s";
}