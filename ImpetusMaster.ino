#include <SoftwareSerial.h>

const byte xPin = A0;
const byte yPin = A1;

SoftwareSerial ss(3, 2);

void setup()
{
   Serial.begin(115200);
   ss.begin(9600);
}

void loop()
{
   static unsigned long timer = 0;
   unsigned long interval = 10;
   if (millis() - timer >= interval)
   {
      timer = millis();
      int xValue = analogRead(xPin);
      int yValue = analogRead(yPin);
      if(xValue<575 && xValue>525){xValue=511;}
      if(yValue<570 && yValue>520){yValue=511;}   
      Serial.print("x value = ");
      Serial.print(xValue);
      Serial.print("   y value = ");
      Serial.println(yValue);
      char buffer[15];
      snprintf(buffer, 14, "%d,%d", xValue, yValue);
      //Serial.println(buffer);
      ss.println(buffer);  // must have a line feed (\n) to terminate the packet
   }
}
