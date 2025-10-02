#include <Arduino.h>

// Passive buzzer connected between these two pins
const int BUZZER_PIN_1 = 1;
const int BUZZER_PIN_2 = 2;

// Function to play a tone of a specific frequency for a certain duration,
// with a configurable duty cycle.
// It works by rapidly switching the polarity of the voltage across the buzzer.
// duty: The duty cycle of the wave, from 0 to 100. 50 is a square wave.
void playTone(int frequency, int duration, int duty = 50)
{
  if (frequency == 0 || duty < 0 || duty > 100)
  {
    delay(duration);
    return;
  }
  // Calculate the period of the wave in microseconds
  long period = 1000000 / frequency;
  // Calculate how many cycles are needed for the given duration
  long cycles = (long)frequency * duration / 1000;

  // Calculate the on and off times based on the duty cycle
  long onTime = period * duty / 100;
  long offTime = period - onTime;

  for (long i = 0; i < cycles; i++)
  {
    // Set pin 1 HIGH and pin 2 LOW
    digitalWrite(BUZZER_PIN_1, HIGH);
    digitalWrite(BUZZER_PIN_2, LOW);
    delayMicroseconds(onTime);
    // Set both pins to LOW to create the 'off' part of the cycle
    digitalWrite(BUZZER_PIN_1, LOW);
    digitalWrite(BUZZER_PIN_2, LOW);
    delayMicroseconds(offTime);
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
  // Test a single note with a variety of duty cycles
  playTone(440, 1000, 10); // A4 at 10% duty
  playTone(440, 1000, 25); // A4 at 25% duty
  playTone(440, 1000, 50); // A4 at 50% duty (square wave)
  playTone(440, 1000, 75); // A4 at 75% duty
  playTone(440, 1000, 90); // A4 at 90% duty

  delay(2000);

  // Play a simple scale with the default 50% duty cycle
  playTone(262, 200); // C4
  playTone(294, 200); // D4
  playTone(330, 200); // E4
  playTone(349, 200); // F4
  playTone(392, 200); // G4
  playTone(440, 200); // A4
  playTone(494, 200); // B4
  playTone(523, 200); // C5
  delay(1000);

  // Turn off the buzzer (set both pins to LOW)
  digitalWrite(BUZZER_PIN_1, LOW);
  digitalWrite(BUZZER_PIN_2, LOW);

  // Wait for 2 seconds before repeating
  delay(2000);
}
