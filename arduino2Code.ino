#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>
void initializeSensorReading();
int data[4];
byte dataIdx = 0;
byte pulseDetected = false;
int lastPulseTime = -1;

void setup() {
  // put your setup code here, to run once:

  Timer1.initialize();
  MFS.initialize(&Timer1);
  initializeSensorReading();
  //Serial.begin(9600);
}
void loop()
{
  if (MFS.getTimer() == 0)
  {
    MFS.setTimer(10000); 
    if (lastPulseTime != -1)
    {
      lastPulseTime = 10000 + lastPulseTime;
    }
  }

  int sensorValue = analogRead(A5); // read the sensor.

  if (sensorValue < 20 || sensorValue > 970)
  {
    if (lastPulseTime != -1 && lastPulseTime - MFS.getTimer() > 700)
    {
      initializeSensorReading();
    }
  }
  else if (sensorValue > (3 * 1024) / 5)
  {
    if (!pulseDetected)
    {
      pulseDetected = true;

      if (lastPulseTime == -1)
      {
        lastPulseTime = MFS.getTimer();
      }
      else
      {
        int pulsePeriod = lastPulseTime - MFS.getTimer(); 
        lastPulseTime = MFS.getTimer();

        int bpm = 60000 / pulsePeriod; // calculate beats per minute.

        if (bpm < 45 || bpm > 230)
        {
          initializeSensorReading();
        }
        else
        {
          data[dataIdx++] = bpm;

          if (dataIdx >= 4)
          {
            dataIdx = 0;
          }

          if (data[0] && data[1] && data[2] && data[3])
          {
            int avgBpm = (data[0] + data[1] + data[2] + data[3]) / 4;

            MFS.blinkDisplay(DIGIT_ALL, OFF);
            MFS.write(avgBpm);
            MFS.beep();
          }
          else
          {

            MFS.blinkDisplay(DIGIT_ALL, ON);
          }
        }
      }
    }
  }
  else if (sensorValue < (1024 / 2))
  {
    pulseDetected = false;
  }

}

void initializeSensorReading()
{
  lastPulseTime = 0;
  dataIdx = 0;
  for (int i = 0; i < 4; i++)
  {
    data[i] = 0;
  }

  MFS.write(0);
  MFS.blinkDisplay(DIGIT_ALL, OFF);
}
