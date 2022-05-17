const int echoPin = 2
const int trigPin = 3
const int IR = 4;

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT); //trigger pin sends output signal
  pinMode(echoPin, INPUT); //echo pin receives input signal
  pinMode(IR, INPUT);  //Infrared sensor input
}
void loop() {
  digitalWrite(trigPin, LOW); //clear trigger pin from previous loop
  delayMicroseconds(5); //using Microseconds as the delay needs to be very very short - delay uses millisecond
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);  //trigger pin high for 10 microsecond - sound wave sent
  digitalWrite(trigPin, LOW); //reset trigger pin

  duration = pulseIn(echoPin, HIGH);  //reading and storing time it takes for echo
  //duration contains sound travel time in microseconds
 
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  //distance contains distance in centimeter
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  //printing distance in serial monitor
  Serial.println("Infrared: ");
  if(digitalRead(IR)==LOW){
    Serial.println("Detected");
  }
  else{
     Serial.println("Not detected");
  }
}
