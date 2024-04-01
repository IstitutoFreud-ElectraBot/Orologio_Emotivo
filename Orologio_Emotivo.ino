#include <LiquidCrystal.h>
#include <RTClib.h>

RTC_DS3231 rtc;

// LCD display pins configuration
const int rs = 3;
const int en = 5;
const int d4 = 9;
const int d5 = 10;
const int d6 = 11;
const int d7 = 12;
const int buzzerPin = 13; // Passive buzzer pin

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Array of short motivational messages
const char* motivationalMessages[] = {
  "Stay positive!",
  "You got this!",
  "Keep going!",
  "Believe in you!",
  "You're amazing!",
  "Make it happen!",
  "Stay focused!",
  "Dream big!",
  "You can do it!",
  "Never give up!",
  "Success awaits!",
  "Embrace journey!",
  "Progress matters!",
  "Attitude counts!",
  "Work, luck meet!",
  "Challenges!",
  "You're capable!",
  "New beginnings!",
  "You're strong!",
  "Believe, achieve!",
  "You are enough!",
  "Be proud!",
  "Work for it!",
  "Endless potential!",
  "Wisdom from wounds!",
  "Positive action!",
  "Dream, believe, achieve!",
  "Try and succeed!",
  "Stay hungry!",
  "Create success!",
  "No limits!",
  "Push yourself!",
  "Great things!",
  "Create opportunity!",
  "Brave, strong, smart!",
  "Believe in dreams!",
  "Determination!",
  "Continue courage!",
  "Great work, love!",
  "Take shots!",
  "Imagination!",
  "Comfort zone!",
  "Create opportunity!",
  "Believe, achieve!",
  "Story of success!",
  "Prepare greatness!",
  "Expect greatness!",
  "Set new goals!",
  "Love what you do!",
  "Future starts now!",
  "Hard but possible!",
  "Be happy, succeed!",
  "Future today!"
};

void setup() {
  rtc.begin();
  
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
 
  lcd.begin(16, 2);  // Initialize the LCD display with 16 columns and 2 rows
  lcd.clear();
  pinMode(buzzerPin, OUTPUT); // Set the buzzer pin as output
}

void loop() {
  DateTime now = rtc.now();
  printDateTime(now);
  checkMinutes(now);
  checkMotivationalMessage(now);
  delay(1000);
}

void printDateTime(DateTime dt) {
  char dateBuffer[] = "   DD/MM/YYYY   ";
  char timeBuffer[] = "    hh:mm:ss    ";
 
  lcd.setCursor(0, 0);
  lcd.print(dt.toString(dateBuffer));
  lcd.setCursor(0, 1);
  lcd.print(dt.toString(timeBuffer));
}

void checkMinutes(DateTime dt) {
  if (dt.minute() % 10 == 0 && dt.second() == 0) {
    tone(buzzerPin, 1000, 100); // Sound the buzzer for 100ms at 1000Hz
    delay(200); // Wait 200ms before repeating to avoid continuous sounds
  }
}

void checkMotivationalMessage(DateTime dt) {
  // Show a motivational message every minute for 10 seconds
  if (dt.second() == 0) {
    // Select a random motivational message from the array
    int index = random(0, sizeof(motivationalMessages) / sizeof(motivationalMessages[0]));
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(motivationalMessages[index]);
    
    // Wait for 10 seconds
    delay(10000);
    
    // Clear the screen
    lcd.clear();
  }
}
