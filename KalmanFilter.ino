//Ultraschall:
#define echoPin 6 // Echo Pin
#define trigPin 2 // Trigger Pin
#define ledPin A10

int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
float duration, distance; // Duration used to calculate distance
int v=0;
int i=0;

//Motor:
const int
PWM_A   = 3, PWM_B   = 11 ,
DIR_A   = 12, DIR_B  = 13 ,
BRAKE_A = 9, BRAKE_B = 8;

void setup() {
 Serial.begin (9600);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 
 pinMode(ledPin, OUTPUT);

 
 //Setup Channel A
  pinMode(DIR_A, OUTPUT); //Initiates Motor Channel A pin
  pinMode(BRAKE_A, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B
  pinMode(DIR_B, OUTPUT); //Initiates Motor Channel B pin
  pinMode(BRAKE_B, OUTPUT);  //Initiates Brake Channel B pin
}

void loop() {
i++;
digitalWrite(ledPin, LOW);

/* The following trigPin/echoPin cycle is used to determine the
 distance of the nearest object by bouncing soundwaves off of it. */ 
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;
 
  digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
  digitalWrite(BRAKE_B, LOW);  
  digitalWrite(DIR_A, HIGH);   // setting direction to HIGH the motor will spin forward
  digitalWrite(DIR_B, LOW);
 

 
 Serial.println(distance);
 
    if(Serial.available()>0) // if there is data to read
   {
     delay(1000);
    v=Serial.read(); 
   analogWrite(PWM_A, v-20);     // Set the speed of the motor, 255 is the maximum value
  analogWrite(PWM_B, v); 
  if(v==0) { 
    analogWrite(PWM_A, 0);     // Set the speed of the motor, 255 is the maximum value
  analogWrite(PWM_B, 0); 
  }
  }


 if (i==20) {
 digitalWrite(ledPin, HIGH);
 i=0; }
 
 //Delay 500ms before next reading.
 delay(50);
}
