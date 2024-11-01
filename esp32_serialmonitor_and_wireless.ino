//code to glow light either from serial monitor or wirelessly along with a standby light mode when no any inputs are received

#include <WiFi.h>
#include <Adafruit_NeoPixel.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "acm_AP";
const char* password = "Csc1Student!";

// NeoPixel setup
#define DATA_PIN 18   // Pin connected to the NeoPixel data line
#define NUMPIXELS 50  // Number of LEDs in the strip
#define BRIGHTNESS 100 // Set brightness to 100%
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, DATA_PIN, NEO_GRB + NEO_KHZ800); 

// Web server on port 80
WebServer server(80);

// Function to map letters to specific LEDs and light them up
void switchLights(char letter) {
  int index = -1; // Default invalid index
  uint32_t color = strip.Color(255, 255, 255);  // Default white color

  // Convert the letter to uppercase to make it case-insensitive
  letter = toupper(letter);

  switch (letter) {
    case 'A': index = 34; color = strip.Color(255, 255, 255); break;  // White
    case 'B': index = 33; color = strip.Color(0, 0, 255); break;      // Blue
    case 'C': index = 32; color = strip.Color(255, 0, 255); break;    // Magenta
    case 'D': index = 31; color = strip.Color(0, 255, 255); break;    // Cyan
    case 'E': index = 30; color = strip.Color(0, 0, 255); break;      // Blue
    case 'F': index = 29; color = strip.Color(255, 255, 0); break;    // Yellow
    case 'G': index = 28; color = strip.Color(255, 0, 0); break;      // Red
    case 'H': index = 20; color = strip.Color(50, 50, 255); break;    // Light Blue
    case 'I': index = 21; color = strip.Color(255, 0, 255); break;    // Magenta
    case 'J': index = 22; color = strip.Color(50, 50, 255); break;    // Light Blue
    case 'K': index = 23; color = strip.Color(0, 0, 255); break;      // Blue
    case 'L': index = 24; color = strip.Color(255, 255, 255); break;  // White
    case 'M': index = 25; color = strip.Color(255, 255, 0); break;    // Yellow
    case 'N': index = 17; color = strip.Color(255, 0, 0); break;      // Red
    case 'O': index = 16; color = strip.Color(255, 0, 255); break;    // Magenta
    case 'P': index = 15; color = strip.Color(255, 255, 255); break;  // White
    case 'Q': index = 14; color = strip.Color(255, 0, 255); break;    // Magenta
    case 'R': index = 13; color = strip.Color(100, 100, 255); break;  // Light Blue
    case 'S': index = 12; color = strip.Color(255, 255, 250); break;  // Light White
    case 'T': index = 11; color = strip.Color(255, 255, 0); break;    // Yellow
    case 'U': index = 2; color = strip.Color(0, 0, 255); break;       // Blue
    case 'V': index = 3; color = strip.Color(255, 0, 255); break;     // Magenta
    case 'W': index = 4; color = strip.Color(0, 0, 255); break;       // Blue
    case 'X': index = 6; color = strip.Color(255, 255, 0); break;     // Yellow
    case 'Y': index = 7; color = strip.Color(255, 0, 0); break;       // Red
    case 'Z': index = 8; color = strip.Color(255, 0, 255); break;     // Magenta
    default: break;  // Non-alphabet characters won't light up any LEDs
  }

  if (index >= 0 && index < NUMPIXELS) {
    strip.setPixelColor(index, color);  // Set the color of the LED
    strip.show();
    delay(500);  // Delay to allow the light to be visible
    strip.setPixelColor(index, 0); // Turn off the LED
    strip.show();
    delay(200);  // Small delay before lighting the next LED
  }
}

// Function to light up LEDs based on the word entered
void lightUpWord(String word) {
  strip.clear();
  for (int i = 0; i < word.length(); i++) {
    switchLights(word[i]);
  }
  strip.show();
}

// Webpage HTML
String webpage = "<html>\
  <body>\
  <h1>McNeese ACM Internet of Stranger Things</h1>\
  <form action=\"/setword\" method=\"GET\">\
  Enter a word: <input type=\"text\" name=\"word\">\
  <input type=\"submit\" value=\"Display\">\
  </form>\
  </body>\
  </html>";

void handleRoot() {
  server.send(200, "text/html", webpage);
}

void handleSetWord() {
  if (server.hasArg("word")) {
    String word = server.arg("word");
    word.trim(); // Remove any trailing newline or spaces
    for (int i = 0; i < word.length(); i++) {
        word[i] = toupper(word[i]);
    }
    lightUpWord(word);
    server.send(200, "text/html", "Word set: " + word + "<br><a href=\"/\">Go back</a>");
  } else {
    server.send(200, "text/html", "No word provided.<br><a href=\"/\">Go back</a>");
  }
}

void standbyMode() {
  static int pixel = 0;
  strip.clear();
  strip.setPixelColor(pixel, strip.Color(0, 0, 255)); // Set current pixel to blue
  strip.show();
  pixel = (pixel + 1) % NUMPIXELS; // Move to the next pixel
}

// Timer variable for standby mode
unsigned long lastStandbyTime = 0;
const unsigned long standbyInterval = 50;

void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.setBrightness(BRIGHTNESS);  // Set brightness to 100%
  strip.show(); // Initialize all pixels to 'off'

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Start the web server
  server.on("/", handleRoot);
  server.on("/setword", handleSetWord);
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  // Handle web server clients
  server.handleClient();

  // Check for serial input
  if (Serial.available() > 0) {
    String word = Serial.readStringUntil('\n'); // Read the word from the Serial Monitor
    word.trim(); // Remove any trailing newline or spaces
    word.toUpperCase(); // Convert the entire word to uppercase to ensure case insensitivity
    lightUpWord(word);
    Serial.print("Word set: ");
    Serial.println(word);
    Serial.println("Enter another word:");
  } 
  else {
    // Run standby mode only if enough time has passed
    unsigned long currentMillis = millis();
    if (currentMillis - lastStandbyTime >= standbyInterval) {
      standbyMode();
      lastStandbyTime = currentMillis;
    }
  }
}
