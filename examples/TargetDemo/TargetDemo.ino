/*
 * IRtag: TargetDemo - Simple target for "laser tag" style IR shooters
 * An IR detector/demodulator (38 kHz) must be connected to the input RECV_PIN.
 * If an IR signal is received, an LED at pin 13 is flashed and the received data
 * value is sent to the serial port as a hexadecimal 32-bit number.
 */

#include <IRtag.h>

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  irrecv.blink13(1);
  Serial.println("Receiver started.");
  
}

void loop()
{
  if (irrecv.decode(&results))
  {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
}

