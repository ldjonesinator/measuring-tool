// defines pins numbers
const int trigPin = 2;
const int echoPin = 3;

// defines ultrasonic sensor variables
const int SAMPLE_SIZE = 10;
const int DELTA_T = 5; // 5 ms
const unsigned int TIMEOUT = 23500; // in microseconds which would give approx 4 m (the sensor's max range)
long duration;
int distance;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH, TIMEOUT);
  // Calculating the distance
  return duration * 340*100/1000000 / 2;
}

int getSensorSamples(int samples, int time_gap) {
  int total = 0;
  int distance;
  size_t n = 1;
  for (size_t i = 0; i < samples; i ++) {
    distance = getDistance();
    if (distance != 0) {
      n ++;
    }
    total += distance;
    delay(time_gap);
  }
  return total / n;
}

void loop() {
  // Clears the trigPin
  distance = getSensorSamples(SAMPLE_SIZE, DELTA_T);
  // Prints the distance on the Serial Monitor
  if (distance <= 2) {
    Serial.println("Too far or Too close");
  } else {
    Serial.print("Distance: ");
    Serial.println(distance);
  }
  
}