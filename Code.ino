const int echoPin = 2
const int trigPin = 3
const int led = 4;

long duration;
int distance;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(trigPin, OUTPUT); //trigger pin sends output signal
  pinMode(echoPin, INPUT); //echo pin receives input signal
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

  if(distance <= 20){
    digitalWrite(led, HIGH);
  }
  else{
    digitalWrite(led, LOW);
  }
  //led turns on if distance is less than 20 cm
}
