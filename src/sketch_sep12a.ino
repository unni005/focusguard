#define TOUCH1_PIN 18
#define TOUCH2_PIN 19
#define IR_PIN 27

const unsigned long IR_CONFIRM_TIME = 2000;

unsigned long irStartTime = 0;
bool sleepSent = false;

void setup() {
  Serial.begin(115200);

  pinMode(TOUCH1_PIN, INPUT);
  pinMode(TOUCH2_PIN, INPUT);
  pinMode(IR_PIN, INPUT);

  Serial.println("FOCUSGUARD STARTED");
}

void loop() {

  int touch1 = digitalRead(TOUCH1_PIN);
  int touch2 = digitalRead(TOUCH2_PIN);
  int ir = digitalRead(IR_PIN);

  // Both touch sensors must be HIGH
  bool sitting = (touch1 == HIGH && touch2 == HIGH);

  // Most IR modules output LOW when detecting an object
  bool handDetected = (ir == LOW);

  if (sitting) {

    if (handDetected) {

      if (irStartTime == 0) {
        irStartTime = millis();
      }

      // Hand must remain detected for 2 seconds
      if ((millis() - irStartTime >= IR_CONFIRM_TIME) &&
          !sleepSent) {

        Serial.println("SLEEP");

        sleepSent = true;
      }
    }
    else {
      irStartTime = 0;
    }
  }
  else {

    irStartTime = 0;
    sleepSent = false;
  }

  // Debug information
  Serial.print("Touch1: ");
  Serial.print(touch1);

  Serial.print(" | Touch2: ");
  Serial.print(touch2);

  Serial.print(" | IR: ");
  Serial.print(ir);

  Serial.print(" | Sitting: ");
  Serial.print(sitting);

  Serial.print(" | Hand: ");
  Serial.println(handDetected);

  delay(100);
}