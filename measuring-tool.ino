#include "pitches.h"

// defines pins numbers
const int TRIG_PIN = 2;
const int ECHO_PIN = 3;
const int NOTE_PIN = 8;

// defines ultrasonic sensor variables
const int SAMPLE_SIZE = 10;
const int DELTA_T = 5; // 5 ms
const unsigned int TIMEOUT = 23500; // in microseconds which would give approx 4 m (the sensor's max range)

int distance;


const unsigned int NOTE_DURATION = 16; // milliseconds
const int MAX_BEEP_TIME = 2000; // 2 s
int wait_time;
unsigned long start_time;


void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
}

int getDistance() {
  unsigned long duration;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  // Sets the TRIG_PIN on HIGH state for 10 micro seconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  // Reads the ECHO_PIN, returns the sound wave travel time in microseconds
  duration = pulseIn(ECHO_PIN, HIGH, TIMEOUT);
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
  start_time = millis();
  // Clears the TRIG_PIN
  distance = getSensorSamples(SAMPLE_SIZE, DELTA_T);
  // Prints the distance on the Serial Monitor
  if (distance <= 2) {
    Serial.println("Too far or Too close");
  } else {
    Serial.print("Distance: ");
    Serial.println(distance);

    tone(NOTE_PIN, NOTE_C4, NOTE_DURATION);
    wait_time = 20 * distance;
    Serial.print("Time: ");
    Serial.println(wait_time + (millis() - start_time));
    Serial.println((millis() - start_time));
    delay(wait_time);

    noTone(NOTE_PIN);
  }

  
}