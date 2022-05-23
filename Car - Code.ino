//Hassaan Nadeem - 340187 - CAO Project
//Hand Following Car with Web Server

//Including libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"

//Defining pins
#define trigPin 12
#define echoPin 13

#define left_infr 32
#define right_infr 14

#define left_forward 27
#define left_backward 26
#define right_forward 25
#define right_backward 33

//Defining variables
long duration;
int distance;

int left_signal;
int right_signal;

String lastDistance = "0";
String lastMovement = "";
//These two variables are used to store latest distance and movement which are then printed on web server

const char* ssid = "Galaxy A51";
const char* password = "12345679";

//Asynchronous Web Server on port 80
AsyncWebServer server(80);

//Defining functions
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
  Serial.println("Distance: ");
  Serial.println(distance);
  lastDistance = distance;
  return distance;
}

void movement(){
  distance = calc_distance();
  left_signal = digitalRead(left_infr);
  right_signal = digitalRead(right_infr);
  
  /*Serial.println("Left: ");
  Serial.println(digitalRead(left_infr));
  Serial.println("Right: ");
  Serial.println(digitalRead(right_infr));*/
  
  if (distance < 10){
    release();
    lastMovement = "Stop";
  }
  
  else if(distance <= 30 && distance >= 10 && left_signal == 1 && right_signal == 1){ //go straight - follow hand
    straight();
    lastMovement = "Straight";
  }
    
  else if(left_signal == 0 && right_signal == 1){ //Turn right
    right();
    lastMovement = "Right";
  }
  
  else if(right_signal == 0 && left_signal == 1){  //Turn left
    left();
    lastMovement = "Left";
  }
  else{
    lastMovement = "None";
  }
}

void straight(){
  digitalWrite(left_forward, HIGH);
  digitalWrite(right_forward, HIGH);
  digitalWrite(left_backward, LOW);
  digitalWrite(right_backward, LOW);
  delay(50);
  Serial.println("Straight");
}

void left(){        
  digitalWrite(left_forward, LOW);
  digitalWrite(right_forward, HIGH);
  digitalWrite(left_backward, HIGH);
  digitalWrite(right_backward, LOW);
  delay(50);
  Serial.println("Left");
}

void right(){
  digitalWrite(left_forward, HIGH);
  digitalWrite(right_forward, LOW);
  digitalWrite(left_backward, LOW);
  digitalWrite(right_backward, HIGH);
  delay(50);
  Serial.println("Right");
}

void release(){
  digitalWrite(left_forward, LOW);
  digitalWrite(right_forward, LOW);
  digitalWrite(left_backward, LOW);
  digitalWrite(right_backward, LOW);
  Serial.println("Stop");
}

void reset(){
  digitalWrite(left_forward, LOW);
  digitalWrite(right_forward, LOW);
  digitalWrite(left_backward, LOW);
  digitalWrite(right_backward, LOW);  
}

// Replaces placeholder with values
String processor(const String& var){
  //Serial.println(var);
  if(var == "DISTANCE"){
    return lastDistance;
  }
  else if(var == "MOVEMENT"){
    return lastMovement;
  }
  return String();
}

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <h2>ESP32 Web Server</h2>
  <p>
    <span>Distance:</span> 
    <span id="distance">%DISTANCE%</span>cm
  </p>
  <p>
    <span>Movement:</span>
    <span id="movement">%MOVEMENT%</span>
  </p>
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("distance").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/distance", true);
  xhttp.send();
}, 500 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("movement").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/movement", true);
  xhttp.send();
}, 500 ) ;
</script>
</html>)rawliteral";

void setup(){
  // Serial port for debugging purposes
  Serial.begin(9600);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/distance", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", lastDistance.c_str());   //prints last distance on website
  });
  server.on("/movement", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", lastMovement.c_str());   //prints last movement on website
  });

  // Start server
  server.begin();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(left_infr, INPUT);
  pinMode(right_infr, INPUT);
  
  pinMode(left_forward, OUTPUT);
  pinMode(left_backward, OUTPUT);
  pinMode(right_forward, OUTPUT);
  pinMode(right_backward, OUTPUT);

}
 
void loop(){
  movement();
  reset();    //To reset motor signals every loop. Else motors will keep following previous
}
