/*************************************************** 
 by: Kenny William Nyallau

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

public:
  Sweeper(int interval, int channel)
  {
    updateInterval = interval;
    increment = 1;
    PWMchannel = channel;
  }
  
  void SetAngle(int channel, int angle)
  {
    int ticks = map(angle, 0, 180, SERVOMIN, SERVOMAX);
    pwm.setPWM(channel, 0, ticks);
  }
  

  
  void Update()
  {
   
       if((millis() - lastUpdate) > updateInterval)  // time to update
      {
        lastUpdate = millis();
        pos += increment;
        SetAngle(PWMchannel, pos);
       // servo.write(pos);
        Serial.println(pos);
        if ((pos >= 180) || (pos <= 0)) // end of sweep
        {
          // reverse direction
          increment = -increment;
  
        }
      }
  }
};

//first movement
Sweeper sweeper1(19, 0);
Sweeper sweeper2(20, 1);
Sweeper sweeper3(21, 2);
Sweeper sweeper4(22, 3);
Sweeper sweeper5(23, 4);
Sweeper sweeper6(24, 5);

//second movement
Sweeper jumbled1(18, 0);
Sweeper jumbled2(5, 1);
Sweeper jumbled3(50, 2);
Sweeper jumbled4(66, 3);
Sweeper jumbled5(10, 4);
Sweeper jumbled6(18, 5);


//----------------------------------------------------
void setup() {
  Serial.begin(9600);

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

}

//------------------------------------------------------------------------------
void loop() {
  
   movement01();
  //movement02();


}
//---------------------------------------------------------------------------
void movement01(){
 
 sweeper1.Update();
 sweeper2.Update();
 sweeper3.Update();
 sweeper4.Update();
 sweeper5.Update();
 sweeper6.Update();
 
}

//---------------------------------------------------------------------------
void movement02(){
  
 jumbled1.Update();
 jumbled2.Update();
 jumbled3.Update();
 jumbled4.Update();
 jumbled5.Update();
 jumbled6.Update();

}
