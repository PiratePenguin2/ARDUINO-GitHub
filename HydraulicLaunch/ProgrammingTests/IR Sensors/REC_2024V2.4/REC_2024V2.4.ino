//Penn State Ride Engineering Competition, V2.4: Final System
// 1 = track, 0 = station
// 1 for limit pin = station
// 2 for limit pin = track

#include <Servo.h>
#include <AccelStepper.h>

//Pin Definitions
#define stepper1Pin 2
#define dir1Pin 3
#define stepper2Pin 4
#define dir2Pin 5
#define stepper3Pin 1
#define dir3Pin 0
#define ServoPin 6
#define ServoPin2 7
#define limit1Pin 8i
#define limit1Pin_2 9
#define limit2Pin 10
#define limit2Pin_2 11
#define StationLimitPin 12
#define StationLimitPin2 13

#define EStopPin A0
#define RideStopPin A1
#define ResetPin A2

#define InfSensor1 A3
#define InfSensor2 A4
#define DropSensor A5

// add limit_2's to moveposition stuff

//Variable Definitions
int currentPosition;
int previousPosition;
bool RideStopPressed = false;
bool EStopPressed = false;
bool TrainLock = false;
int ServoPos = 0;
bool TrainOffLift = false;

int prevTime = millis();
int currentTime = millis();

Servo myservo;


//setup

void setup() {
  // put your setup code here, to run once:
  pinMode(EStopPin, INPUT_PULLUP);
  pinMode(RideStopPin, INPUT_PULLUP);
  pinMode(ResetPin, INPUT_PULLUP);
  pinMode(stepper1Pin, OUTPUT);
  pinMode(dir1Pin, OUTPUT);
  pinMode(limit1Pin, INPUT_PULLUP);
  pinMode(limit2Pin, INPUT_PULLUP);
  pinMode(stepper3Pin, OUTPUT);
  pinMode(dir3Pin, OUTPUT);

  
  pinMode(limit1Pin_2, INPUT_PULLUP);
  pinMode(limit2Pin_2, INPUT_PULLUP);
  pinMode(InfSensor1, INPUT);
  pinMode(InfSensor2, INPUT);
  pinMode(DropSensor, INPUT);
  pinMode(stepper2Pin, OUTPUT);
  pinMode(dir2Pin, OUTPUT);
  pinMode(ServoPin, OUTPUT);
  pinMode(StationLimitPin, INPUT_PULLUP);
  pinMode(StationLimitPin2, INPUT_PULLUP);


  if(digitalRead(limit1Pin) != LOW)
    {
      movePosition(0);
    }
  
  
  digitalWrite(EStopPin, LOW);
  digitalWrite(RideStopPin, LOW);
  digitalWrite(ResetPin, LOW);
  

  Serial.begin(9600);
  }

//FUNCTIONS
//ESTOP
void EStop() {
  //Write ESTOP, cut power COMPLETELY

  digitalWrite(stepper1Pin, LOW);

  digitalWrite(dir1Pin, LOW);

  digitalWrite(ServoPin, LOW);
}

void SetPinsLow() {
  digitalWrite(stepper1Pin, LOW);
  digitalWrite(stepper2Pin, LOW);
  digitalWrite(ServoPin, LOW);
}

bool CheckSpecial(bool trackMove)  //trackMove is true when track is moving while special button is pressed
{ //Implement drive tires into this :( Do we have to take into account 11.3.2? Stop can only be reset if the system knows that all hazards are removed.
  int EStopState = digitalRead(EStopPin);
  int RideStopState = digitalRead(RideStopPin);
  //booleans to long set button to pressed
  
  if(EStopState == LOW && !trackMove)
  {
    Serial.println("ESTOP ACTIVATED");
    EStop();

    while(digitalRead(ResetPin) == HIGH)
    {
      EStop();
    }

    Serial.println("Reset activated");
    Serial.println("All systems functional.");
    Serial.println("Normal operation");
    return(true);
  }
  
  if(RideStopState == LOW && !trackMove)
  {
    Serial.println("Ride Stop Activated");
    SetPinsLow();
    while(digitalRead(ResetPin) == HIGH)
    {
      SetPinsLow();
    }
    
    Serial.println("Reset activated");
    Serial.println("All systems functional.");
    Serial.println("Normal operation");
    return(true);
  }
  
  if (EStopState == LOW && trackMove) {
    Serial.println("ESTOP ACTIVATED");
    
    while(digitalRead(ResetPin) == HIGH)
    {
      EStop();
    }
    
    Serial.println("Reset activated");
    currentPosition = 0;
    movePosition(1);
    currentPosition = 1;
    Serial.println("All systems functional.");
    Serial.println("Normal operation");
    return(true);
    
  }
  
  if(RideStopState == LOW && trackMove)
  {
    Serial.println("Manual Ride Stop Activated");
    RideStopPressed = true;
    
    if (currentPosition == 1) 
    {
    movePosition(1); // changed from 0 to 1
    currentPosition = 1; // changed from 0 to 1
    } 
    if (currentPosition == 0) // changed from else to new if statemetn and changed the 1's to 0's for function values
    { 
    movePosition(0);
    currentPosition = 0;
    }
    if (currentPosition != 1 && currentPosition != 0) // checks to see if train is between station and track when ridestop is called, if so then it moves to track by default
    {
      movePosition(1);
      currentPosition = 1;
    }

    
   // -------------------------------------------------------------------------------------
   // WHY IS THIS HERE??? CAN WE JUST MAKE IT SO IF BOTH ARE PRESSED THEN ESTOP BY DEFAULT?
   // -------------------------------------------------------------------------------------


    while(digitalRead(ResetPin) == HIGH)
    {
      digitalWrite(stepper1Pin, LOW);

      digitalWrite(dir1Pin, LOW);
    }
    
    if(RideStopPressed && EStopPressed && trackMove)
    {
    currentPosition = 1;
    movePosition(0);
    currentPosition = 0;
    RideStopPressed = false;
    EStopPressed = false;
    }
    Serial.println("Reset activated");
    Serial.println("All systems functional.");
    Serial.println("Normal operation");
    return(true);
    
  }
    // end confusion code
    
    return (false);
}

  bool movePosition(int pos) {
    // Check if the first limit switch is not pressed
    bool stop = false;

    if (pos == 0) {
      if (digitalRead(limit1Pin) == HIGH || digitalRead(limit1Pin_2) == HIGH) {
        // First limit switch is not pressed, spin motor in one direction
        digitalWrite(dir1Pin, HIGH);               // Set direction to forward
        while (digitalRead(limit1Pin) == HIGH && digitalRead(limit1Pin_2) == HIGH) {  // Keep spinning until limit switch 1 is pressed
          digitalWrite(stepper1Pin, HIGH);
          delayMicroseconds(1000);
          digitalWrite(stepper1Pin, LOW);
          delayMicroseconds(1000);

          /*
          stop = CheckSpecial(true);
          if (stop) {
            return false;
          } 
          */
          
        }


        // First limit switch is pressed, stop motor
        digitalWrite(stepper1Pin, LOW);
        delay(3000);  // Pause for 3 seconds
      }
    }

    else if (pos == 1) {
      if (digitalRead(limit2Pin) == HIGH && digitalRead(limit2Pin_2) == HIGH) {
        // Second limit switch is not pressed, spin motor in the opposite direction
        digitalWrite(dir1Pin, LOW);                // Set direction to reverse
        while (digitalRead(limit2Pin) == HIGH && digitalRead(limit2Pin_2) == HIGH) {  // Keep spinning until limit switch 2 is pressed
          digitalWrite(stepper1Pin, HIGH);
          delayMicroseconds(1000);
          digitalWrite(stepper1Pin, LOW);
          delayMicroseconds(1000);
          /*
          stop = CheckSpecial(true);
          if (stop) {
            return false;
          }
          */
          
        }
        // Second limit switch is pressed, stop motor
        digitalWrite(stepper1Pin, LOW);
        delay(3000);  // Pause for 3 seconds
      }
    }

    else {
      Serial.println("Invalid position passed through");
    }

    return (true);
  }

  void DetectTrainPass()
  {
    delay(2500);
    if(InfSensor1 == HIGH && InfSensor2 == LOW)
    {
      delay(2000);

      // Servo Move in Code
      for(ServoPos = 15; ServoPos <= 0; ServoPos++)
      {
      myservo.write(ServoPos);
      delay(30);
      }
      // Stepper Motor Slowly Spins to Slow Train
      digitalWrite(dir2Pin, LOW);
      while(InfSensor1 == HIGH && InfSensor2 == HIGH) // Slowly move train to proper position then lock train
      {
      digitalWrite(stepper2Pin, HIGH);
      delayMicroseconds(2500);
      digitalWrite(stepper2Pin, LOW);
      delayMicroseconds(2500);
      }
    }
  }

  void Kick1()
  {
    while(digitalRead(StationLimitPin) == HIGH || digitalRead(StationLimitPin2) == HIGH)
    {
      //stepper shit (move train into station using wheels on both the transfer track and in the station until the train is actually in the station)
      digitalWrite(dir2Pin, HIGH);
      digitalWrite(stepper2Pin, HIGH);
      delayMicroseconds(1000);
      digitalWrite(stepper2Pin, LOW);
      delayMicroseconds(1000);
      
      CheckSpecial(false);
    }
    digitalWrite(stepper2Pin, LOW);
    delayMicroseconds(3000);
  }

  void Kick2()
  {
    //stepper in station high til certain time frame has passed (5 sec)
    prevTime = millis();
    currentTime = millis();
    bool stop;
    while(currentTime - prevTime < 5000) //Allows us to checkspecial while the stepper is running...kind of important...or we can just let estop not work for those 5 seconds :)
    {
      currentTime = millis();
      CheckSpecial(false);
      digitalWrite(dir3Pin, HIGH);
      digitalWrite(stepper3Pin, HIGH);
      delayMicroseconds(1000);
      digitalWrite(stepper3Pin, LOW);
      delayMicroseconds(1000);
      //Run stepper while in loop
    }
    digitalWrite(stepper3Pin, LOW);
    delayMicroseconds(3000);

  }

  void loop()
   {
    /*
    // put your main code here,to run repeatedly:
    EStopPressed = false;
    RideStopPressed = false;
    Serial.println("Normal cycle.");

    //CheckSpecial(false);
    
    while(digitalRead(DropSensor) == LOW)
    {
      digitalRead(DropSensor);
    }
    DetectTrainPass();
    
    
    movePosition(0);
    Serial.println("Track aligned with station.");
    
    if(digitalRead(limit1Pin) == LOW && digitalRead(limit1Pin_2) == LOW)
    {
      Kick1();
    }
    else
    {
      Serial.println("DANGER: TRANSFER TRACK NOT IN CORRECT PLACE! MOVE TO CORRECT POSITION MANUALLY!");
      while(digitalRead(limit1Pin) == LOW || digitalRead(limit1Pin_2) == LOW)
      {
        digitalRead(limit1Pin);
      }
      Kick1();
    }

    //servo down
    movePosition(1);
    Serial.println("Train returned to station, and transfer is in place. Press Reset button to confirm dispatch.");
    
    while(digitalRead(ResetPin) == HIGH)
    {
      digitalRead(ResetPin);
    }
    Serial.println("Dispatch");
    

    if(digitalRead(limit2Pin) == LOW && digitalRead(limit2Pin_2) == LOW)
    {
      Kick2();
    }
    else
    {
      Serial.println("DANGER: TRANSFER TRACK NOT IN CORRECT PLACE! MOVE TO CORRECT POSITION MANUALLY!");
      while(digitalRead(limit2Pin) == LOW || digitalRead(limit2Pin_2) == LOW)
      {
        digitalRead(limit2Pin);
      }
      Kick2();
    }
    */


    

    
    
    //TESTING
    movePosition(1);
  
    

  }
