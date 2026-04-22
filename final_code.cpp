#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define IR_PIN  2
#define PIR_PIN 3
//#define UV_PIN  A0

int productCount = 0;
unsigned long lastCountTime = 0;
unsigned long lastPIRTime = 0;
const int COOLDOWN_MS = 50;
const int IDLE_TIMEOUT = 500;

bool conveyorActive = false;
bool lastIRState = false;

void setup() {
  pinMode(IR_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);

  lcd.init();
  lcd.backlight();

  // Startup screen
  lcd.setCursor(0, 0);
  lcd.print("Product Counter");
  lcd.setCursor(0, 1);
  lcd.print("System Ready...");
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Belt: IDLE");
  lcd.setCursor(0, 1);
  lcd.print("Count: 0");

  Serial.begin(9600);
}

void loop() {
  bool pirDetected = digitalRead(PIR_PIN) == HIGH; 
  bool irDetected  = digitalRead(IR_PIN) == LOW;   // LOW = object detected
  unsigned long now = millis();

  // ---- PIR: Conveyor Active/Idle ----
  if (pirDetected) {
    lastPIRTime = now;

    if (!conveyorActive) {
      conveyorActive = true;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Belt: ACTIVE");
      lcd.setCursor(0, 1);
      lcd.print("Count: ");
      lcd.print(productCount);
      Serial.println("Belt ACTIVE");
    }
  }

  // No PIR for 5 sec → idle
  if (conveyorActive && (now - lastPIRTime > IDLE_TIMEOUT)) {
    conveyorActive = false;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Belt: IDLE");
    lcd.setCursor(0, 1);
    lcd.print("Count: ");
    lcd.print(productCount);
    Serial.println("Belt IDLE");
  }

  // ---- IR: Count only when belt is ACTIVE ----
  if (conveyorActive) {

    // Detect object ENTERING (IR goes LOW)
    if (irDetected && !lastIRState && (now - lastCountTime > COOLDOWN_MS)) {
      productCount+=1;
      lastCountTime = now;

      // Show "Item Detected!" on row 0
      lcd.setCursor(0, 0);
      lcd.print("Item Detected!  ");

      // Show updated count on row 1
      lcd.setCursor(0, 1);
      lcd.print("Count: ");
      lcd.print(productCount);
      lcd.print("   ");

      Serial.print("Item Detected! Count: ");
      Serial.println(productCount);
    }

    // When object moves AWAY (IR goes HIGH again) → back to ACTIVE display
    if (!irDetected && lastIRState) {
      lcd.setCursor(0, 0);
      lcd.print("Belt: ACTIVE    ");
    }

    lastIRState = irDetected;
  }
}
