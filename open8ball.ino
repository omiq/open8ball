/*

  Magic 8 Ball V2
  Requires 16x2 LCD + Tilt switch 
  See BOM at https://open8ball.com/build
  
*/

// pins
#define TILT 8

// LiquidCrystal I2C
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); 

// Is the switch on/off
bool switchState = 0;

// Magic 8 Ball Responses
String responses[][2] = {
//......1234567890123456                        
  {"2","It is certain.  "},
  {"2","Decidedly so.   "},
  {"2","Without a doubt."},
  {"2","Definitely.     "},
  {"2","Rely on it.     "},
  {"2","As I see it, yes"},
  {"2","Most likely.    "},
  {"2","Outlook good.   "},
  {"2","Yes.            "},
  {"2","Signs point yes."},
  {"1","Reply hazy.     "},
  {"1","Ask again later."},
  {"1","Better not say. "},
  {"1","Cannot predict. "},
  {"1","Concentrate!    "},
  {"0","Dont count on it"},
  {"0","My reply is no. "},
  {"0","Sources say no. "},
  {"0","Outlook not good"},
  {"0","Very doubtful.  "}
  
};

void setup()
{
  
  Serial.begin(9600);
  
  // Activate the built-in pullup
  pinMode(TILT, INPUT_PULLUP);
  
  // set up the LCD's number of columns and rows:
  lcd.init();
  lcd.begin(16, 2);
  lcd.backlight();//To Power ON the back light
    
}

void loop()
{
  // read the state of the tilt switch value
  switchState = digitalRead(TILT);
  
  // if it is activated
  if (switchState == HIGH) {
    
    // output to serial
    Serial.println("TILT!!!");

    // Random choice
    randomSeed(analogRead(0)); 
    int pickedNum = random (0, 19);
    String selectedPositivity = responses[pickedNum][0];
    String selectedResponse = responses[pickedNum][1];

    // Delay a bit before outputting answer
    delay(300);

    // Output ready
    lcd.setCursor(0, 0);
    lcd.print("Answer:                        ");

    // set the cursor to column 0, line 1
    lcd.setCursor(0, 1);
    lcd.print(selectedResponse);
    delay(5000);

  } else {
    
    // Reset
    
    lcd.setCursor(0, 0);
    lcd.print("Question?                       ");
    
    Serial.println("\n");
    lcd.setCursor(0, 1);
    lcd.print("                                ");
  }
  
  // Delay to prevent false positives
  delay(100); 
  
}
