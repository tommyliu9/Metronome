/*
  Metronome
  Counts the intervals between the taps and displays the beat via light
*/

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 12;     // the number of the pushbutton pin
const int offbutton = 2;
const int ledPin =  13;      // the number of the LED pin and beeper speaker
const int F = 11;
const int G = 10;
const int E = 9;
const int D = 8;
const int C = 7;
const int B = 6;
const int A = 5;

// variables will change:
int buttonState = 0;// variable for the metronome tap
int offbuttonState = 0; //variable for turning on/off metronome
unsigned long previousMillis = 0;
unsigned long fadeMillis = 0;
long interval_list[4];
long previoustime2 = 0;
long time = 0;
int counter = 0; // counts number of times button has been pressed
bool is_beep = true; // toggles when and when not to beep
int lastbuttonState1 = 0;
int lastbuttonState2 = 0;
long average = 0;

int brightness = 255;
void setup() {
  // initialize the LED pins as an output:
  pinMode(ledPin, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(offbutton, INPUT);
  Serial.begin(9600);
}
void blink() { // Turns on the light
  analogWrite(A, brightness);
  analogWrite(B, brightness);
  analogWrite(C, brightness);
  analogWrite(D, brightness);
  analogWrite(E, brightness);
  analogWrite(F, brightness);
  analogWrite(G, brightness);
  pop();
}
void pop(){ 
  analogWrite(ledPin, 255);
}
void stop_blink(){  // Turns off the light and the speaker
  analogWrite(ledPin, 0);
  brightness = 0;
  analogWrite(A, brightness);
  analogWrite(B, brightness);
  analogWrite(C, brightness);
  analogWrite(D, brightness);
  analogWrite(E, brightness);
  analogWrite(F, brightness);
  analogWrite(G, brightness);

}
void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  offbuttonState = digitalRead(offbutton);
  time = millis(); // Start the timer
  
  if (offbuttonState != lastbuttonState2){ //Toggles the led light and buzzer on/off
    if (offbuttonState == HIGH){
      is_beep = not is_beep;
      Serial.println(is_beep);
  }}
  
  if (buttonState != lastbuttonState1 ){\
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
      interval_list[counter] = time - previousMillis;
      counter ++;
      previousMillis = time;
    }
  }


  if ((time - previousMillis) >= 3000){ // if 3 seconds elaps, the count resets
    previousMillis = time;
    counter = 0;
  }
///////////////////////////////////////////////////////////////// 
  if (counter == 4){ // When the button is pressed 4 times, it will calculate a new interval
    counter = 0;
    long previous_average = average;
    average = 0;
    for (int i = 1; i < 4; i = i + 1){
      average += interval_list[i];
    }
    average /= 3;
    if (average <  50 ){ // Checks whether the bpm is too high( over 240),
      //if it is it will use the old bpm 
      average = previous_average;
    }
    
    Serial.println("BPM: ");
    Serial.println(60.0/(average/1000.0));
    interval_list[4] = interval_list[4];
  }
////////////////////////////////////////////////////////////////
  if ((time - previoustime2) >= average*.25 && (time-previoustime2) < average*0.5){
    brightness = 125;
  }
  
  //Check to see if enough time elapsed for the next beat to drop
  if (((time - previoustime2) >= average) && is_beep){
    previoustime2 = time;
    brightness = 250;
    blink();
  }
  stop_blink();
  
  lastbuttonState1 = buttonState;
  lastbuttonState2 = offbuttonState;
    
}
