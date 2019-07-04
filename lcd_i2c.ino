#include <HX711.h>

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

//LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

HX711 scale;
#define DOUT  6
#define CLK  7

float calibration_factor = -7050; //-7050 worked for 440lb max scale setup

//KEYPAD CODE START
RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
//KEYPAD CODE END

void setup(){
  Serial.begin(9600);

  void setupLoadCell(){
    scale.begin(DOUT, CLK);  
  }
  
  void setupKeypad(){
    Serial.begin(9600);
     //rtc ds 321 code
    delay(3000); // wait for console opening
    char str[16];  
    if (! rtc.begin()) {
      Serial.println("Couldn't find RTC");
      while (1);
    }
  
    if (rtc.lostPower()) {
      Serial.println("RTC lost power, lets set the time!");
   
    // Comment out below lines once you set the date & time.
      // Following line sets the RTC to the date & time this sketch was compiled
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    
      // Following line sets the RTC with an explicit date & time
      // for example to set January 27 2017 at 12:56 you would call:
      // rtc.adjust(DateTime(2017, 1, 27, 12, 56, 0));
    }
  }

  void lcdSetup(){
    //LCD I2c CODE
    lcd.init();                      // initialize the lcd 
    lcd.init();
     Print a message to the LCD.
    lcd.backlight();
    lcd.setCursor(1,0);
    lcd.print("hello boss");
    lcd.setCursor(1,1);
    lcd.print("konichiwaa");
    
  }

}


void loop(){

  void loopLoadCell(){
    Serial.println(scale.read()); //reading hx711
  }

  void loopKeypad(){
    //keypad code
    char key = keypad.getKey();
    if (key){
      Serial.println(key);
    }
    if(key == "A"){
      //start setting time
      //set hour, 2 digit
      int count_hour = 0;
    }  
    if(key == "B"{
      // finish setting time
    }
    //rtc code below
    DateTime now = rtc.now();
  
    int alarm_hour = 8;
    int alarm_minute = 0;
  
    if(now.minute() == alarm_minute(){
      if(now.hour() == alarm_hour){
        //do something     
      } 
    }
  }
  
}
