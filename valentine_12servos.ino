/*************************************************** 
 by: Kenny William Nyallauj

 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

// our servo # counter
uint8_t servonum = 0;

//----Sweeper class---------------------------------------------------
class Sweeper
{
  int pos;              // current servo position 
  int increment;        // increment to move for each interval
  int  updateInterval;      // interval between updates
  unsigned long lastUpdate; // last update of position
  int PWMchannel;
  int posCounter;
  int counter;
  int reset = 0;
  int movementCounter;

public:
  Sweeper(int interval, int channel)
  {
    updateInterval = interval;
    increment = 3;
    PWMchannel = channel;
  }
  
  //counts the position before switches to next movement
  void PositionCounter(){
    
    posCounter = counter;

     if (posCounter >= 0 || posCounter <= 4){
        Serial.println(posCounter);
        Serial.println("movement01");
        movementCounter = 1;
     }
      
     else if (posCounter >= 5 || pos <= 8){
      Serial.println(posCounter);
      Serial.println("movement02");
      movementCounter = 2;
    }
    
    else if (posCounter >= 9){
      Serial.println(posCounter);
      Serial.println("reset");
      counter = reset;
      
    }
 
  }
  
  //get me the movement number
  int GetMovementCounter()
  {
    return movementCounter;
  }
  
  //set angle to each motor, maps the angles to PWM
  void SetAngle(int channel, int angle)
  {
    int ticks = map(angle, 0, 180, SERVOMIN, SERVOMAX);
    pwm.setPWM(channel, 0, ticks);
  }
  

  //update the time
  void Update()
  {
   
       if((millis() - lastUpdate) > updateInterval)  // time to update
      {
        lastUpdate = millis();
        pos += increment;
        
        //check if the position is forward, count it as one
         if (pos >= 0)
        {
          counter++;
        }
        
        SetAngle(PWMchannel, pos);
       // servo.write(pos);
        Serial.println(pos);
        if ((pos >= 180) || (pos <= 0)) // end of sweep
        {
          // reverse direction
          increment = -increment;
        }
       
       //check if the direction is reversed, count it as one 
        if ((pos >= 180) || (pos <= 0))
        {
          counter++;
        }
      }
  }
};

//first movement
Sweeper sweeper1(4, 0);
Sweeper sweeper2(6, 1);
Sweeper sweeper3(8, 2);
Sweeper sweeper4(10, 3);
Sweeper sweeper5(12, 4);
Sweeper sweeper6(14, 5);
Sweeper sweeper7(16, 6);
Sweeper sweeper8(18, 7);
Sweeper sweeper9(20, 8);
Sweeper sweeper10(22, 9);
Sweeper sweeper11(24, 10);
Sweeper sweeper12(26, 11);


//second movement
Sweeper jumbled1(18, 0);
Sweeper jumbled2(5, 1);
Sweeper jumbled3(50, 2);
Sweeper jumbled4(66, 3);
Sweeper jumbled5(10, 4);
Sweeper jumbled6(18, 5);
Sweeper jumbled7(16, 6);
Sweeper jumbled8(18, 7);
Sweeper jumbled9(20, 8);
Sweeper jumbled10(22, 9);
Sweeper jumbled11(24, 10);
Sweeper jumbled12(26, 11);


//----------------------------------------------------
void setup() {
  Serial.begin(9600);
  
  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

}

//------------------------------------------------------------------------------
void loop() {
  
  startPositionCounter();
  updateMovement();  

    
  movement01();
   //movement02();

}

//---------------------------------------------------------------------------
void startPositionCounter(){
  
  sweeper1.PositionCounter();
  sweeper2.PositionCounter();
  sweeper3.PositionCounter();
  sweeper4.PositionCounter();
  sweeper5.PositionCounter();
  sweeper6.PositionCounter();
  sweeper7.PositionCounter();
  sweeper8.PositionCounter();
  sweeper9.PositionCounter();
  sweeper10.PositionCounter();
  sweeper11.PositionCounter();
  sweeper12.PositionCounter();
  
  jumbled1.PositionCounter();
  jumbled2.PositionCounter();
  jumbled3.PositionCounter();
  jumbled4.PositionCounter();
  jumbled5.PositionCounter();
  jumbled6.PositionCounter();
  jumbled7.PositionCounter();
  jumbled8.PositionCounter();
  jumbled9.PositionCounter();
  jumbled10.PositionCounter();
  jumbled11.PositionCounter();
  jumbled12.PositionCounter();
  
}

//---------------------------------------------------------------------------
void updateMovement(){
  
      if(sweeper12.GetMovementCounter() == 1)
    {
      Serial.println("I am now in movement 1");
    }
    
    else if(sweeper12.GetMovementCounter() == 2)
     {
        Serial.println("I will set to movement 2");
        
      if(jumbled1.GetMovementCounter() == 2){
        Serial.println("I am now in movement 2");
      }
        if(jumbled12.GetMovementCounter() == 1)
        {
          Serial.println("I will set to movement 1");
        }
      
     }
}

//---------------------------------------------------------------------------
void movement01(){
 
 sweeper1.Update();
 sweeper2.Update();
 sweeper3.Update();
 sweeper4.Update();
 sweeper5.Update();
 sweeper6.Update();
 sweeper7.Update();
 sweeper8.Update();
 sweeper9.Update();
 sweeper10.Update();
 sweeper11.Update();
 sweeper12.Update();
 
}

//---------------------------------------------------------------------------
void movement02(){
  
 jumbled1.Update();
 jumbled2.Update();
 jumbled3.Update();
 jumbled4.Update();
 jumbled5.Update();
 jumbled6.Update();
 jumbled7.Update();
 jumbled8.Update();
 jumbled9.Update();
 jumbled10.Update();
 jumbled11.Update();
 jumbled12.Update();

}


