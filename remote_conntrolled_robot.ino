#include "IRLremote.h"

// Choose a valid PinInterrupt or PinChangeInterrupt* pin of your Arduino board
#define pinIR 2

// Choose the IR protocol of your remote. See the other example for this.
CNec IRLremote;
//CPanasonic IRLremote;
//CHashIR IRLremote;
//#define IRLremote Sony12

#define pinLed LED_BUILTIN

const int enb=3;//defining inputs for the l293d
const int in3=4;
const int in4=5;
const int in1=9;
const int in2=10;
const int ena=11;

void setup()
{
  // Start serial debug output
  while (!Serial);
  Serial.begin(115200);
  Serial.println(F("Startup"));

  // Set LED to output
  pinMode(pinLed, OUTPUT);

  // Start reading the remote. PinInterrupt or PinChangeInterrupt* will automatically be selected
  if (!IRLremote.begin(pinIR))
    Serial.println(F("You did not choose a valid pin."));
  pinMode(enb,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
}

void loop()
{
  // Check if we are currently receiving data
  if (!IRLremote.receiving()) {
    // Run code that disables interrupts, such as some led strips
  }

  // Check if new IR protocol data is available
  if (IRLremote.available())
  {
    // Light Led
    digitalWrite(pinLed, HIGH);

    // Get the new data from the remote
    auto data = IRLremote.read();
 // Print the protocol data
    Serial.print(F("Address: 0x"));
    Serial.println(data.address, HEX);
    Serial.print(F("Command: 0x"));
    Serial.println(data.command );
    Serial.println();
    // Turn Led off after printing the data
    digitalWrite(pinLed, LOW);//all remote sensing stuff till here
  
  if(data.command==146)//making the bot move forward
  {
     digitalWrite(in3,HIGH);
    digitalWrite(in1,HIGH);
    digitalWrite(in4,LOW);
    digitalWrite(in2,LOW);
    analogWrite(enb,200);
    analogWrite(ena,200);
  }
    else if(data.command==216)//making the bot move backward
    {
    digitalWrite(in3,LOW);
    digitalWrite(in1,LOW);
    digitalWrite(in4,HIGH);
    digitalWrite(in2,HIGH);
    analogWrite(ena,200);
    analogWrite(enb,200);
  }
     else if(data.command==159)//making the bot move right
     {
    digitalWrite(in3,LOW);
    digitalWrite(in1,HIGH);
    digitalWrite(in4,HIGH);
    digitalWrite(in2,LOW);
    analogWrite(ena,200);
    analogWrite(enb,200);
    delay(100);
     digitalWrite(in3,HIGH);
    digitalWrite(in1,HIGH);
    digitalWrite(in4,HIGH);
    digitalWrite(in2,HIGH);
  }

    else if(data.command==151)//making the bot move left
    {
      digitalWrite(in3,HIGH);
    digitalWrite(in1,LOW);
    digitalWrite(in4,LOW);
    digitalWrite(in2,HIGH);
    analogWrite(ena,200);
    analogWrite(enb,200);
    delay(151);
     digitalWrite(in3,HIGH);
    digitalWrite(in1,HIGH);
    digitalWrite(in4,HIGH);
    digitalWrite(in2,HIGH);
    }
 
    else// if any other button pressed terminate
    {
      digitalWrite(in3,HIGH);
    digitalWrite(in1,HIGH);
    digitalWrite(in4,HIGH);
    digitalWrite(in2,HIGH);
    
    }
  }
  }
  
  



