/*
UV CONTROLLER V.0.1

 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 */

// include the library code:2
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define BUTTON_INC  6
#define BUTTON_DEC  7
#define BUTTON_SEL  8

#define POWER_LED 9

int STATE;
int POSITION = 1;  // 1 = TIME, 2 = POWER
int TIME = 0;
int POWER = 100;
  
  

void setup() {
   
  pinMode(BUTTON_INC, INPUT);           // set pin to input
  digitalWrite(BUTTON_INC, HIGH);       // turn on pullup resistors
  pinMode(BUTTON_DEC, INPUT);           // set pin to input
  digitalWrite(BUTTON_DEC, HIGH);       // turn on pullup resistors
  pinMode(BUTTON_SEL, INPUT);           // set pin to input
  digitalWrite(BUTTON_SEL, HIGH);       // turn on pullup resistors
  
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("UV CTRL 0.1");
  delay(500);
  for (int i = 0; i < 15; i++) {
    lcd.setCursor(i,1);
    lcd.print ("*");
    delay(20);
  }
  delay(1000);
  lcd.clear();
}

void loop() {
  lcd.setCursor(0,0);
  if (POSITION == 1) {lcd.print(">");} else {lcd.print(" ");}
  lcd.print("Time");
  delay(10);
  lcd.setCursor(0,1);
  if (POSITION == 2) {lcd.print(">");} else {lcd.print(" ");}
  lcd.print("Power");
  
  lcd.setCursor(10,0);
  lcd.print(TIME);
  lcd.print("s  ");
  lcd.setCursor(10,1);
  lcd.print(POWER);
  lcd.print("%  ");
  
  if (!digitalRead(BUTTON_INC))
  {
    delay(50);
    if (!digitalRead(BUTTON_INC))
    {
      STATE = 1;  // increment button
    }
  }
  
  if (!digitalRead(BUTTON_DEC))
  {
    delay(50);
    if (!digitalRead(BUTTON_DEC))
    {
      STATE = 2;  // decrement button
    }
  }
  
  if (!digitalRead(BUTTON_SEL))
  {
    delay(100);
    if (!digitalRead(BUTTON_SEL))
    {
      STATE = 3;  // selection button
      delay(100);
    }
  }
  
  switch (STATE) {
    case 1:
      increment();
      break;
     case 2:
      decrement();
      break;
     case 3:
      selection();
      break;
      
     default:
     delay(1);
  }
  
  STATE = 0;
  
  
}

void increment()
{
    if (POSITION == 1)    // time
    {
      TIME++;
      delay(50);
    }
    if (POSITION == 2)   // power
    {
       POWER++;
       if (POWER >= 100) {POWER = 100;}
       delay(50);
    }
}

void decrement()
{
    if (POSITION == 1)    // time
    {
      if (TIME <= 0) { TIME = 0; delay(50); return; }
      TIME--;
      delay(50);
    }
    if (POSITION == 2)   // power
    {
       POWER--;
       if (POWER <= 0) {POWER = 0;}
       delay(50);
    }
}

void selection()
{
  delay(100);
  
  if (digitalRead(BUTTON_SEL)) // ok released, switch selection
  {
    if (POSITION == 1) {POSITION = 2;} else { POSITION = 1; }
    delay (100);  
    return;
  }
  delay (100);
  
  for (int i = 0; i <= 20; i++)
  {
    if (!digitalRead(BUTTON_SEL))
    {
      delay(100);
      if (digitalRead(BUTTON_SEL)) { return; }
    }
   } 
  
  start();

}

void start()
{
  lcd.setCursor(0,0);
  lcd.print("*");
  lcd.setCursor(0,1);
  lcd.print("*");
  delay(1000);
  analogWrite(POWER_LED, POWER*2.55);
  delay(TIME*1000);
}
