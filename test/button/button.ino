#include "HardwareSerial.h"

// Define the hardware serial port for Nextion
#define NEXTION_RX 16  // Connect to Nextion TX
#define NEXTION_TX 17  // Connect to Nextion RX

// Create a serial instance for the Nextion display
HardwareSerial nextionSerial(1);

void setup() {
  // Start the serial communication for debugging
  Serial.begin(115200);

  // Start the Nextion serial communication
  nextionSerial.begin(9600, SERIAL_8N1, NEXTION_RX, NEXTION_TX);

  Serial.println("Nextion Button Press Example with ESP32");

  delay(1000);
  sendToNextion("loading.txt=\"Hello!\"");
  delay(1000);
  sendToNextion("loading.txt=\" World !\"");
}

void loop() {
  // Check if data is available from Nextion
  if (nextionSerial.available()) {
    String message = nextionSerial.readString();  // Read the message from Nextion

    // Check if the message corresponds to the button press
    if (message.indexOf("VENT_ON") != -1) {
      Serial.println("VENT_ON");
      // Add additional code here to handle the button press
    }
    if (message.indexOf("VENT_OFF") != -1) {
      Serial.println("VENT_OFF");
      // Add additional code here to handle the button press
    }
  }
}

// Function to send a command to the Nextion display
void sendToNextion(String command) {
  // Send the command
  nextionSerial.print(command);
  
  // Send the three terminating bytes
  nextionSerial.write(0xFF);
  nextionSerial.write(0xFF);
  nextionSerial.write(0xFF);
}