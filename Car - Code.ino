//Car + Final (Hopefully)

#define trigPin 12
#define echoPin 13

#define left_infr 32
#define right_infr 14

#define left_forward 27
#define left_backward 26
#define right_forward 25
#define right_backward 33

long duration;
int distance;

int left_signal;
int right_signal;

int calc_distance();

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(left_infr, INPUT);
  pinMode(right_infr, INPUT);
  
  pinMode(left_forward, OUTPUT);
  pinMode(left_backward, OUTPUT);
  pinMode(right_forward, OUTPUT);
  pinMode(right_backward, OUTPUT);
}

void loop() {
  distance = calc_distance();
  left_signal = digitalRead(left_infr);
  right_signal = digitalRead(right_infr);
  Serial.println("Left: ");
  Serial.println(digitalRead(left_infr));
  Serial.println("Right: ");
  Serial.println(digitalRead(right_infr));
  
  if (distance < 10){
    stop();
  }
  
  else if(distance <= 20 && distance >= 10 && left_signal == 1 && right_signal == 1){ //go straight - follow hand
    straight();
  }
    
  else if(left_signal == 0 && right_signal == 1){ //Turn right
    right();
  }
  
  else if(right_signal == 0 && left_signal == 1){  //Turn left
    left();
  }

  reset();
}

int calc_distance(){
  long x;
  long y;
  digitalWrite(trigPin, LOW); //clear trigger pin from previous loop
  delayMicroseconds(2); //using Microseconds as the delay needs to be very very short - delay uses millisecond
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);  //trigger pin high for 10 microsecond - sound wave sent
  digitalWrite(trigPin, LOW); //reset trigger pin

  duration = pulseIn(echoPin, HIGH);  //reading and storing time it takes for echo
  //duration contains sound travel time in microseconds
 
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  //distance contains distance in centimeter
  Serial.println("Distance: ");
  Serial.println(distance);
  return distance;
}

void straight(){
  digitalWrite(left_forward, HIGH);
  digitalWrite(right_forward, HIGH);
  digitalWrite(left_backward, LOW);
  digitalWrite(right_backward, LOW);
  delay(200);
  Serial.println("Straight");
}

void left(){
  digitalWrite(left_forward, LOW);
  digitalWrite(right_forward, HIGH);
  digitalWrite(left_backward, HIGH);
  digitalWrite(right_backward, LOW);
  delay(200);
  Serial.println("Left");
}

void right(){
  digitalWrite(left_forward, HIGH);
  digitalWrite(right_forward, LOW);
  digitalWrite(left_backward, LOW);
  digitalWrite(right_backward, HIGH);
  delay(200);
  Serial.println("Right");
}

void stop(){
  digitalWrite(left_forward, LOW);
  digitalWrite(right_forward, HIGH);
  digitalWrite(left_backward, HIGH);
  digitalWrite(right_backward, LOW);
  delay(200); //reverse to stop momentem
  Serial.println("Stop");
}

void reset(){
  digitalWrite(left_forward, LOW);
  digitalWrite(right_forward, LOW);
  digitalWrite(left_backward, LOW);
  digitalWrite(right_backward, LOW);
}
