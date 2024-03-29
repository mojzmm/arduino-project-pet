#include <DS3231.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Wire.h>
#include "HX711.h"
//all part function only system and kaypad not
//Keypad pin start from red  2.3.4.5.6.7.8.9
//DS3231  rtc(A2, A3);DS3231  rtc(SDA, SCL);
//servo,orange to pin10,red is +,brown is -
//lcd scl is A5 and sda is A4
//FOR LOAD CELL CAN USE SCK ISPIN A1 AND DT IS A0

//setup load cell
HX711 scale(A1, A0);

float calibration_factor = -400; // this calibration factor is adjusted according to my load cell
float units;
float ounces;
//end setup loadcell
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
  //LOAD CELL
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");

  scale.set_scale();
  scale.tare();  //Reset the scale to 0

  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
  //LOAD CELL
 } 
 
 void loop() 
 {//LOADCELL
    scale.set_scale(calibration_factor); //Adjust to this calibration factor

  Serial.print("Reading: ");
  units = scale.get_units(), 10;
  if (units < 0)
  {
    units = 0.00;
  }
  if (units > 100)
  {
   servo_test.write(100); 
  }
  if (units < 100)
  {
   servo_test.write(55); 
  }
  ounces = units * 0.035274;
  Serial.print(units);
  Serial.print(" grams"); 
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();

  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 1;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 1;
  }//LOAD CELL 

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
