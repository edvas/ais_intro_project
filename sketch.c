#include <LiquidCrystal.h>

constexpr uint8_t INPUT_BUTTON_START = 8;
constexpr uint8_t OUTPUT_MOTOR = 10;
constexpr uint8_t OUTPUT_BUZZER = 6;

bool stared = false;
unsigned long time_started = 0;
unsigned long spin_duration = 0; // [ms]

#define SOUND

LiquidCrystal lcd(12, 11, 5, 4, 3, 7);

void setup()
{
  pinMode(INPUT_BUTTON_START, INPUT_PULLUP);
  pinMode(OUTPUT_MOTOR, OUTPUT);
  pinMode(OUTPUT_BUZZER, OUTPUT);
  randomSeed(analogRead(0));
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.print("Start");
}

void loop()
{
  Serial.println(analogRead(5));
  if(time_started == 0 && (!digitalRead(INPUT_BUTTON_START) || analogRead(5) < 300))
  {
    int i = 1000;
    while(i >= 10)
    {
      tone(OUTPUT_BUZZER, 220, i);
      delay(i);
      delay(i);
      i = 0.83 * i;
    }
    
    time_started = millis();
    spin_duration = random(500, 1500); // [ms]
    //Serial.println(spin_duration);
    analogWrite(OUTPUT_MOTOR, 255); //140
    //digitalWrite(OUTPUT_MOTOR, HIGH);

#ifdef SOUND
    tone(OUTPUT_BUZZER, 220, 200);
    delay(200);
    //tone(OUTPUT_BUZZER, 440, 200);
    //delay(200);
    //tone(OUTPUT_BUZZER, 220, 200);
    //delay(200);
    //tone(OUTPUT_BUZZER, 880, 200);
    //delay(200);
#endif
  }

  if(time_started != 0 && millis() >= time_started + spin_duration)
  {
    analogWrite(OUTPUT_MOTOR, 0);
    //digitalWrite(OUTPUT_MOTOR, LOW);
    time_started = 0;

    uint8_t type = random(5);
    lcd.clear();
    switch(type)
    {
      case 0:
        lcd.print("Vann ");
        break;
      case 1:
        lcd.print("Tyrkershot ");
        break;
      case 2:
        lcd.print("Fireball ");
        break;
      case 3:
        lcd.print("Vodka ");
        break;
      default:
        lcd.print("Tequila ");
        break;
    }
    
    
#ifdef SOUND
    tone(OUTPUT_BUZZER, 880, 200);
    //delay(200);
    //tone(OUTPUT_BUZZER, 440, 200);
    //delay(200);
    //tone(OUTPUT_BUZZER, 880, 200);
    //delay(200);
    //tone(OUTPUT_BUZZER, 220, 200);
    //delay(200);
#endif
  }
}
