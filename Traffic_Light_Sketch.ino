
// Traffic Lights Circuit
// Includes Sparkfun .wav trigger, Arduino Mega
// Written by Steph Piper under an Open Source licence

const int buttonPin = 9;
const byte LED = 4; 
int buttonState;

 
unsigned long buttonPushedMillis; // when button was released
unsigned long ledTurnedOnAt; // when led was turned on
unsigned long turnOnDelay = 5500; // wait to turn on LED
unsigned long turnOffDelay = 13000; // turn off LED after this time
bool ledReady = false; // flag for when button is let go
bool ledState = false; // for LED is on or not.

void setup() {
  // put your setup code here, to run once:
//Connection to WAV Trigger
pinMode(2, OUTPUT);
// Connection to Traffic Light
pinMode(4, OUTPUT);
// Connection to button
Serial.begin(9600);
pinMode(buttonPin, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  buttonState = digitalRead(buttonPin);

if (buttonState == HIGH) {
  Serial.println("Button On");
   digitalWrite(2, HIGH);
} else {
  Serial.println("Button Off");
  digitalWrite(2, LOW);
}


 // get the time at the start of this loop()
 unsigned long currentMillis = millis(); 
 
 // check the button
 if (buttonState == HIGH) {
  // update the time when button was pushed
  buttonPushedMillis = currentMillis;
  ledReady = true;
 }
  
 // make sure this code isn't checked until after button has been let go
 if (ledReady) {
   //this is typical millis code here:
      if((unsigned long)(currentMillis - buttonPushedMillis) >= turnOnDelay) {
     // okay, enough time has passed since the button was let go.
     digitalWrite(LED, HIGH);
     // setup our next "state"
     ledState = true;
     // save when the LED turned on
     ledTurnedOnAt = currentMillis;
     // wait for next button press
     ledReady = false;
   }
 
 }
 // see if we are watching for the time to turn off LED
 if (ledState) {
   // okay, led on, check for now long
   if ((unsigned long)(currentMillis - ledTurnedOnAt) >= turnOffDelay) {
     ledState = false;
     digitalWrite(LED, LOW);
   }
 
 }
 }
