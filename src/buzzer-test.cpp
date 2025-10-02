#include <Arduino.h>

// Passive buzzer connected between these two pins
const int BUZZER_PIN_1 = 1;
const int BUZZER_PIN_2 = 2;

// Function to play a tone of a specific frequency for a certain duration.
// It works by rapidly switching the polarity of the voltage across the buzzer.
void playTone(int frequency, int duration)
{
  if (frequency == 0)
  {
    delay(duration);
    return;
  }
  // Calculate the period of the wave in microseconds
  long period = 1000000 / frequency;
  // Calculate how many cycles are needed for the given duration
  long cycles = (long)frequency * duration / 1000;

  for (long i = 0; i < cycles; i++)
  {
    // Set pin 1 HIGH and pin 2 LOW
    digitalWrite(BUZZER_PIN_1, HIGH);
    digitalWrite(BUZZER_PIN_2, LOW);
    delayMicroseconds(period / 2);
    // Reverse the polarity: pin 1 LOW and pin 2 HIGH
    digitalWrite(BUZZER_PIN_1, LOW);
    digitalWrite(BUZZER_PIN_2, HIGH);
    delayMicroseconds(period / 2);
  }
}

void setup()
{
  // Set both pins as outputs
  pinMode(BUZZER_PIN_1, OUTPUT);
  pinMode(BUZZER_PIN_2, OUTPUT);
}

void loop()
{
  // Play a simple scale to test the buzzer
  playTone(262, 250); // C4
  playTone(294, 250); // D4
  playTone(330, 250); // E4
  playTone(349, 250); // F4
  playTone(392, 250); // G4
  playTone(440, 250); // A4
  playTone(494, 250); // B4
  playTone(523, 250); // C5

  // Turn off the buzzer (set both pins to LOW)
  digitalWrite(BUZZER_PIN_1, LOW);
  digitalWrite(BUZZER_PIN_2, LOW);

  // Wait for 2 seconds before repeating
  delay(2000);
}
