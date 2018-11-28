/*

  Magic 8 Ball for regular non-i2c LCD
  Requires 16x2 LCD + Tilt switch 

*/

// pins
#define TILT 8

// include the regular LCD library code:
#include <LiquidCrystal.h>


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


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
  lcd.begin(16, 2);

  // Print a message to the LCD.
  lcd.setCursor(0, 0);
  lcd.print("Question?");
    
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
