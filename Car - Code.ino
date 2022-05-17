//Car + Ultrasonic test

const int trigPin = 12;
const int echoPin = 13;
const int left_forward = 2;
const int right_forward = 3;
const int left_backward = 4;
const int right_backward = 5;

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(left_forward, OUTPUT);
  pinMode(left_backward, OUTPUT);
  pinMode(right_forward, OUTPUT);
  pinMode(right_backward, OUTPUT);
}

void loop() {

  distance = calc_distance();
  if(distance <= 15 && distance >= 5){  //go straight - follow hand
    digitalWrite(left_forward, HIGH);
    digitalWrite(right_forward, HIGH);
    digitalWrite(left_backward, LOW);
    digitalWrite(right_backward, LOW);
    delay(250); //follows for 0.25 seconds and then reads signal again (loop runs again)
  }
  else if(distance < 5){
    digitalWrite(left_forward, LOW);
    digitalWrite(right_forward, HIGH);
    digitalWrite(left_backward, HIGH);
    digitalWrite(right_backward, LOW);
    delay(100); //reverse to stop momentem
  }
}

int calc_distance(){
  digitalWrite(trigPin, LOW); //clear trigger pin from previous loop
  delayMicroseconds(2); //using Microseconds as the delay needs to be very very short - delay uses millisecond
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);  //trigger pin high for 10 microsecond - sound wave sent
  digitalWrite(trigPin, LOW); //reset trigger pin

  duration = pulseIn(echoPin, HIGH);  //reading and storing time it takes for echo
  //duration contains sound travel time in microseconds
 
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  //distance contains distance in centimeter

  return distance;
}
