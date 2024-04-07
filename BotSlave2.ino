#include <SoftwareSerial.h>

const int motorPin1 = 2;  // Connect to IN1 on the L298N
const int motorPin2 = 4;  // Connect to IN2 on the L298N
const int enablePin12 = 5;  // Connect to ENA on the L298N (enable for Motor A)
const int motorPin3 = 7;  // Connect to IN1 on the L298N
const int motorPin4 = 8;  // Connect to IN2 on the L298N
const int enablePin34 = 6; 

int xValue = 0;
int yValue = 0;


const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data

boolean newData = false;

SoftwareSerial ss(13, 12);

void setup()
{
   Serial.begin(115200);
   ss.begin(9600);
   pinMode(motorPin1, OUTPUT);
   pinMode(motorPin2, OUTPUT);
   pinMode(enablePin12, OUTPUT);
   pinMode(motorPin3, OUTPUT);
   pinMode(motorPin4, OUTPUT);
   pinMode(enablePin34, OUTPUT);
}

void loop()
{
 recvWithEndMarker();
   //showNewData();
   if (newData)
   {
      parseData();
   }
}

void recvWithEndMarker()
{
   static byte ndx = 0;
   char endMarker = '\n';
   char rc;

   while (ss.available() > 0 && newData == false)
   {
      rc = ss.read();

      if (rc != endMarker)
      {
         receivedChars[ndx] = rc;
         ndx++;
         if (ndx >= numChars)
         {
            ndx = numChars - 1;
         }
      }
      else
      {
         receivedChars[ndx] = '\0'; // terminate the string
         ndx = 0;
         newData = true;
      }
   }
}

void showNewData()
{
   if (newData == true)
   {
      Serial.print("This just in ... ");
      Serial.println(receivedChars);
      //newData = false;
   }
}

void parseData()
{
   char *strings[2]; // an array of pointers to the pieces of the above array after strtok()
   char *ptr = NULL; byte index = 0;
   ptr = strtok(receivedChars, ",");  // delimiter comma
   while (ptr != NULL)
   {
      strings[index] = ptr;
      index++;
      ptr = strtok(NULL, ",");
   }
   //Serial.println(index);
   /*
   // print all the parts
   Serial.println("The Pieces separated by strtok()");  
   for (int n = 0; n < index; n++)
   {
      Serial.print("piece ");
      Serial.print(n);
      Serial.print(" = ");
      Serial.println(strings[n]);
   }
   */
   // convert string data to numbers
   xValue = atoi(strings[0]);
   yValue = atoi(strings[1]);
      
   Serial.print("x value = ");
   Serial.print(yValue);
   Serial.print("   y value = ");
   Serial.print(xValue);
   
   Serial.println(); // blank line
   newData = false;




  int speedX = map(yValue, 0, 1023, -255, 255);
  int speedY = map(xValue, 0, 1023, 255, -255);

  // Calculate individual motor speeds
  int leftSpeed = speedY + speedX;
  int rightSpeed = speedY - speedX;

  // Ensure the motor speeds are within the valid range
  leftSpeed = constrain(leftSpeed, -150, 150);
  rightSpeed = constrain(rightSpeed, -150, 150);


  if (leftSpeed<0){
    m34b(-leftSpeed);}
   else{
    m34f(leftSpeed);}
   
  if (rightSpeed<0){
    m12b(-rightSpeed);}
   else{
    m12f(rightSpeed);}




  
}




void Stop() {
  m12f(0);
  m34f(0);}

void m12f(int speeed) {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  analogWrite(enablePin12, speeed);
  }

void m12b(int speeed) {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  analogWrite(enablePin12, speeed);
}

void m34f(int speeed) {
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  analogWrite(enablePin34, speeed);
}

void m34b(int speeed) {
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  analogWrite(enablePin34, speeed);
    }
