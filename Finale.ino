// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

// These are the pins used for the breakout example
#define BREAKOUT_RESET  9      // VS1053 reset pin (output)
#define BREAKOUT_CS     10     // VS1053 chip select pin (output)
#define BREAKOUT_DCS    8      // VS1053 Data/command select pin (output)
// These are the pins used for the music maker shield
#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)

// These are common pins between breakout and shield
#define CARDCS 4     // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer = 
  // create shield-example object!
  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

int button = 8;
int buttonVal = 0;
int done = 0;
int forceSensor = A0;
int forceVal = 0;
int musicPlaying = 0;
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(button, INPUT);

  if(!musicPlayer.begin()){
    Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
    while (1);
    }
  Serial.println(F("VS1053 found"));
  
  if (!SD.begin(CARDCS)){
    Serial.println(F("SD failed, or not present"));
    while (1);
    }
  else{
    Serial.println("SD Card Successful");
    }
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonVal = digitalRead(button);
  forceVal = analogRead(forceSensor);
  Serial.print("ForceVal: ");
  Serial.print(forceVal);
  Serial.print(" ButtonVal: ");
  Serial.print(buttonVal);
  Serial.print(" Done: ");
  Serial.println(done);
  delay(500);


  if(buttonVal == HIGH && done == 0 && forceVal >= 50){
    done = 1;
    musicPlayer.setVolume(20,20);
    Serial.println("Playing Opening");
    musicPlayer.playFullFile("open2.mp3");
    delay(200);
    }

  if(forceVal <=50 && done == 1){
    done = 2;
    musicPlayer.setVolume(10,10);
    Serial.println("Playing Lifting");
    musicPlayer.playFullFile("lift4.mp3");
    delay(200);
    }

  if(forceVal >= 50 && done == 2 && buttonVal == LOW){
    done = 0;
    delay(200);
    }

}
