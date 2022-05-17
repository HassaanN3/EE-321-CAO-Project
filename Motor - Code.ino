//Car run straight test

const int left_forward = 2;
const int right_forward = 3;
const int left_backward = 4;
const int right_backward = 5;

void setup() {
  pinMode(left_forward, OUTPUT);
  pinMode(left_backward, OUTPUT);
  pinMode(right_forward, OUTPUT);
  pinMode(right_backward, OUTPUT);
}

void loop() {
  digitalWrite(left_forward, HIGH);
  digitalWrite(right_forward, HIGH);
  digitalWrite(left_backward, LOW);
  digitalWrite(right_backward, LOW);
  delay(2000);
  //car goes straight for 2 seconds

  digitalWrite(left_forward, LOW);
  digitalWrite(right_forward, LOW);
  digitalWrite(left_backward, HIGH);
  digitalWrite(right_backward, HIGH);
  delay(2000);\
  //car reverses for 2 seconds
}
