/*
 * Example on how to use the Wiegand reader library with interruptions.
 */

#include <Wiegand.h>
#include <RFIDkeys.h> //Inside file: String validKeys[] = { "1111", "2222", "3333" }; //ADD KEYS HERE

// These are the pins connected to the Wiegand D0 and D1 signals.
// Ensure your board supports external Interruptions on these pins
#define PIN_D0 2
#define PIN_D1 3

const int ledpin = 4;
const int buzPin = 5;
const int doorReedSwitch = 6;
const int phonePin = 7;
const int relayPin = 8;

int doorState = 0;         // current state of the door
int lastdoorState = 0;     // previous state of the door


bool phoneInputTripped = false;
  
// The object that handles the wiegand protocol
Wiegand wiegand;

// Add your valid rfid keys here. To find you your key just run sketch; hold your new RFID tag in fron ot the reader; 
// and copy the key from serial output of this sketch.
//const uint8_t maxKeyLength = 7; // 
uint8_t owner;



String owners[] = {"Sam","Sam","Sam"};


// Initialize Wiegand reader
void setup() {
  Serial.begin(9600);

  //Install listeners and initialize Wiegand reader
  wiegand.onReceive(receivedData, "Card read: ");
  wiegand.onStateChange(stateChanged, "State changed: ");
  wiegand.begin(WIEGAND_LENGTH_AUTO);

  //initialize pins as INPUT and attaches interruptions
  pinMode(PIN_D0, INPUT);
  pinMode(PIN_D1, INPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_D0), pinStateChanged, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_D1), pinStateChanged, CHANGE);

  //Sends the initial pin state to the Wiegand library
  pinStateChanged();

  pinMode(buzPin, OUTPUT);
  pinMode(ledpin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(phonePin, INPUT);
  pinMode(doorReedSwitch, INPUT_PULLUP);


  digitalWrite(ledpin, HIGH);
  digitalWrite(buzPin, HIGH);
  digitalWrite(relayPin, LOW);
  digitalWrite(phonePin, HIGH);
  

  
}

// Every few milliseconds, check for pending messages on the wiegand reader
// This executes with interruptions disabled, since the Wiegand library is not thread-safe
void loop() { //***********START LOOP********************

//***********RFID CHECKS********************
  noInterrupts();
  wiegand.flush();
  interrupts();
  //Sleep a little -- this doesn't have to run very often.
//  delay(100);  

//***********DOOR PHONE CHECKS********************

  if ((digitalRead(phonePin) == LOW) && (phoneInputTripped == false)) {
    phoneInputTripped = true;  
    phoneEntry();
//    entry(1);   
  }

  
//  ***********DOOR SWITCH CHECKS********************
    // read the doorSwitch input pin:
    doorState = digitalRead(doorReedSwitch);
    // compare the doorState to its previous state
    if (doorState != lastdoorState) {
      if (doorState == HIGH) {
        Serial.println("Door Opened");
        
      }else {
       // if the current state is LOW then the door
      // went from open to closed:
      Serial.println("Door Closed");
      }
       // Delay a little bit to avoid bouncing
       delay(100);
    }
     // save the current state as the last state,
    //for next time through the loop
    lastdoorState = doorState;

    
}//  ***********END LOOP********************



// When any of the pins have changed, update the state of the wiegand library
void pinStateChanged() {
  wiegand.setPin0State(digitalRead(PIN_D0));
  wiegand.setPin1State(digitalRead(PIN_D1));
}

// Notifies when a reader has been connected or disconnected.
// Instead of a message, the seconds parameter can be anything you want -- Whatever you specify on `wiegand.onStateChange()`
void stateChanged(bool plugged, const char* message) {
    Serial.print(message);
    Serial.println(plugged ? "CONNECTED" : "DISCONNECTED");
}

// Notifies when a card was read.
// Instead of a message, the seconds parameter can be anything you want -- Whatever you specify on `wiegand.onReceive()`
void receivedData(uint8_t* data, uint8_t bits, const char* message) {
    Serial.print(message);
String stringOne;
 

    //Print value in HEX or not
    uint8_t bytes = (bits+7)/8;
    for (int i=0; i<bytes; i++) {
//   Serial.print(data[i] >> 4, 16);
//   Serial.print(data[i] & 0xF, 16);
//Serial.println();
//   Serial.print(data[i]);
      stringOne += data[i];
//   key1[i] = data[i];
//     key[i] = i;
        
    }

    
    Serial.print(stringOne);
    Serial.println();

    checkValid(stringOne);
}

void checkValid(String stringOne) {

// Compare this key to the valid once registered here in sketch 
bool valid = false;
int x = 0;
  for (x=0; x<7; x=x+1){
  if ((validKeys[x] == stringOne) && (valid == false) ) {
    Serial.print("Match!");
      if (stringOne == "404136"){
        valid = true;
        samLeaving();
        Serial.print("Sam Leaving!");
      }
      else {
      entry(x);
      valid = true;
      }

    }
  }
  if (valid == false) {
    Serial.print("No Entry!");
    noEntry();
  }

  Serial.println();
}

void entry(int i){


Serial.print("Entry Granted to ");
Serial.print(owners[i]);
//  digitalWrite(ledpin, LOW);
//  delay(500000);
//  digitalWrite(ledpin, HIGH);

  digitalWrite(ledpin, LOW);
  digitalWrite(buzPin, LOW); 
  digitalWrite(relayPin, HIGH);
  delay(20000);
  digitalWrite(buzPin, HIGH);
  delay(20000);
  digitalWrite(buzPin, LOW); 
  delay(20000);
  digitalWrite(buzPin, HIGH);
  delay(20000);
  digitalWrite(buzPin, LOW); 
  delay(20000);
  digitalWrite(buzPin, HIGH);
  delay(20000);
  digitalWrite(buzPin, LOW); 
  delay(20000);
  digitalWrite(buzPin, HIGH);
  delay(20000);
  digitalWrite(buzPin, LOW); 
  delay(20000);
  digitalWrite(buzPin, HIGH);
  delay(20000);
  digitalWrite(buzPin, LOW); 
  delay(20000);
  digitalWrite(buzPin, HIGH);
  delay(20000);
  digitalWrite(buzPin, LOW); 
  delay(20000);
  digitalWrite(buzPin, HIGH);
  delay(900000);
  digitalWrite(ledpin, HIGH);
  digitalWrite(relayPin, LOW);

}

void phoneEntry(){
    digitalWrite(phonePin, HIGH);
    Serial.print("DoorPhoneTripped");
    digitalWrite(relayPin, HIGH);

  digitalWrite(ledpin, LOW);
  digitalWrite(buzPin, LOW); 
  delay(100);
  digitalWrite(buzPin, HIGH);
  delay(100);
  digitalWrite(buzPin, LOW); 
  delay(100);
  digitalWrite(buzPin, HIGH);
  delay(100);
  digitalWrite(buzPin, LOW); 
  delay(100);
  digitalWrite(buzPin, HIGH);
  delay(100);
  digitalWrite(buzPin, LOW); 
  delay(100);
  digitalWrite(buzPin, HIGH);
  delay(100);
  digitalWrite(buzPin, LOW); 
  delay(100);
  digitalWrite(buzPin, HIGH);
  delay(100);
  digitalWrite(buzPin, LOW); 
  delay(100);
  digitalWrite(buzPin, HIGH);
  delay(100);
  digitalWrite(buzPin, LOW); 
  delay(100);
  digitalWrite(buzPin, HIGH);
  delay(5000);
 

  while((digitalRead(phonePin) == LOW)){ //Wait for relay to reset
    phoneInputTripped = true; 
    Serial.print("Waiting for LOW");
  }

  digitalWrite(ledpin, HIGH);
  digitalWrite(relayPin, LOW);
  phoneInputTripped = false;
  
}


void noEntry(){
Serial.print("Entry Denied!");

  digitalWrite(buzPin, LOW); 
  delay(20000);
  digitalWrite(buzPin, HIGH);
  delay(30000);
  digitalWrite(buzPin, LOW); 
  delay(20000);
  digitalWrite(buzPin, HIGH);

}

void samLeaving(){

  digitalWrite(ledpin, LOW); 
  delay(20000);
  digitalWrite(ledpin, HIGH);
  delay(20000);
  digitalWrite(ledpin, LOW); 
  delay(20000);
  digitalWrite(ledpin, HIGH);
  delay(20000);
  digitalWrite(ledpin, LOW); 
  delay(20000);
  digitalWrite(ledpin, HIGH);
  delay(20000);
  digitalWrite(ledpin, LOW); 
  delay(20000);
  digitalWrite(ledpin, HIGH);
  delay(20000);
  digitalWrite(ledpin, LOW); 
  delay(20000);
  digitalWrite(ledpin, HIGH);
  delay(20000);
  digitalWrite(ledpin, LOW); 
  delay(20000);
  digitalWrite(ledpin, HIGH);
  delay(20000);
  digitalWrite(ledpin, LOW); 
  delay(20000);
  digitalWrite(ledpin, HIGH);

}




