#include <DS3231.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Wire.h>
//all part function only system and kaypad not
//Keypad pin start from red  2.3.4.5.6.7.8.9
//DS3231  rtc(A2, A3);DS3231  rtc(SDA, SCL);
//servo,orange to pin10,red is +,brown is -
//lcd scl is A5 and sda is A4
//FOR LOAD CELL CAN USE PIN A1 AND A0
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Three columns

// Define the Keymap

char keys[ROWS][COLS] = {

  {'1','2','3','A'},

  {'4','5','6','B'},

  {'7','8','9','C'},

  {'*','0','#','D'}

};

// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.

byte rowPins[ROWS] = { 2, 3, 4, 5 };

// Connect keypad COL0, COL1 and COL2 to these Arduino pins.

byte colPins[COLS] = { 6, 7, 8, 9 };

//  Create the Keypad
  Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

 

DS3231  rtc(A2, A3);
Servo servo_test;      //initialize a servo object for the connected servo  
LiquidCrystal_I2C lcd(0x27,16,2);

 //int angle = 0;    
// int potentio = A0;      // initialize the A0analog pin for potentiometer
 int t1, t2, t3, t4, t5, t6;

 
boolean feed = false; // condition for alarm

 char key;
 int r[6];
 
 void setup() 
 { 
  lcd.init();                      // initialize the lcd 
  lcd.init();
  lcd.backlight();
  servo_test.attach(10);   // attach the signal pin of servo to pin9 of arduino
  rtc.begin();
  lcd.begin(16,2);
  servo_test.write(55); 
  Serial.begin(9600);

  
 } 
 
 void loop() 
 { 

 lcd.setCursor(0,0);
 char buttonPress;
 buttonPress = kpd.getKey();
  
  if (buttonPress == 'A'){
      lcd.clear();
      lcd.print("Set feeding Time");
  }

  if(buttonPress == '*'){
    //stop feeding
    servo_test.write(55); // set motor to zero to stop
    feed = false;
   }

  if(buttonPress == '#'){
    //stop feeding
    servo_test.write(100);
    feed = true;    
  }
 

//Serial.println(buttonPress);

 lcd.print("Time:  ");
 String t = "";
 t = rtc.getTimeStr(); 
 t1 = t.charAt(0)-48;
 t2 = t.charAt(1)-48;
 t3 = t.charAt(3)-48;
 t4 = t.charAt(4)-48;
 t5 = t.charAt(6)-48;
 t6 = t.charAt(7)-48;
 
 lcd.print(rtc.getTimeStr());
 lcd.setCursor(0,1);
 lcd.print("Date: ");
 lcd.print(rtc.getDateStr());
 
 if (t1==r[0] && t2==r[1] && t3==r[2] && t4==r[3]&& t5<1 && t6<3 && feed==true)
 { 
  servo_test.write(100);                   //command to rotate the servo to the specified angle 
   delay(400);   
  servo_test.write(55); 
  feed=false;
 } 
 }       
void startMotor(){
  Serial.println("Starting Motor");
  servo_test.write(100);                   //command to rotate the servo to the specified angle 
   delay(400);   
  servo_test.write(55); 
  feed=false;
//  StepsRequired  =  0;//steper stop
//  steppermotor.step(StepsRequired);
}
void setFeedingTime()
{
  feed = true;
   int i=0;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set feeding Time");
  lcd.clear();
  lcd.print("HH:MM");
  lcd.setCursor(0,1);

  
  while(1){
    key = kpd.getKey();

    char j;
    
  if(key!=NO_KEY){
    
    lcd.setCursor(j,1);
    
    lcd.print(key);
    
    r[i] = key-48;
    i++;
    j++;

    if (j==2)
    {
      lcd.print(":"); j++;
    }
    delay(500);
  }

  if (key == 'D')
  {key=0; break; }
  }
}
