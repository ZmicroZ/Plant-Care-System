#include <WiFi.h>
#include <WiFiClient.h>

const char *ssid = "Plant Status Monitor";
const char *password = "ee366micro";
static String webisteout= "";
WiFiServer server(80);

// Define the RX and TX pins for the ESP32
#define RXD2 16 // Replace with your RX pin number
#define TXD2 17 // Replace with your TX pin number

void setup() {
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  if (!WiFi.softAP(ssid, password)) {
    Serial.println("Soft AP creation failed.");
    while(1);
  }
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
}

void loop() {
  static String receivedData = ""; // Buffer to hold incoming data

  // Check if there is data available from Serial2
  while (Serial2.available()) {
    char incomingByte = Serial2.read(); // Read the incoming byte

    // Check if the end of line is detected
    if (incomingByte == '\n') {
      // Print the entire line
      Serial.print("Received from Serial2: ");
      Serial.println(receivedData);
      int startIndex = receivedData.indexOf("Moisture Sensor Levels: ") + 23;
      int endIndex = receivedData.indexOf('%', startIndex);
      
      // Extract the percentage as a string
      String percentageStr = receivedData.substring(startIndex, endIndex);
      
      // Store the percentage for the website output
      webisteout = percentageStr;

      // Clear the receivedData string for the next line
      receivedData = "";
    } else {
      // Add the incoming byte to the receivedData string
      receivedData += incomingByte;
    }
  }

  // Check if a client has connected
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
     // Set the response to the client
                client.println("HTTP/1.1 200 OK");
                client.println("Content-type:text/html");
                client.println("Refresh: 3"); // Refresh every 3 seconds
                client.println();
                
                // HTML content with styling
                client.println("<!DOCTYPE html><html>");
                client.println("<head><meta http-equiv=\"refresh\" content=\"3\">");
                client.println("<style>");
                client.println("body { font-family: Arial, sans-serif; margin: 0; padding: 0; background-color: #000000; color: #ffffff; }");
                client.println(".container { text-align: center; padding: 50px; }");
                client.println(".status { padding: 20px; font-size: 24px; }"); // Increased font size
                client.println(".low { color: #ff0000; }");
                client.println(".medium { color: #ffa500; }");
                client.println(".high { color: #008000; }");
                client.println("</style>");
                client.println("</head>");
                client.println("<body>");
                client.println("<div class=\"container\">");
                client.println("<h1>Soil Moisture Level</h1>");
                
                // Convert the percentage string to a float
                float moistureLevel = webisteout.toFloat();
                
                // Determine the status based on moisture level
                String statusClass;
                if (moistureLevel < 20) {
                  statusClass = "low";
                } else if (moistureLevel < 40) {
                  statusClass = "medium";
                } else {
                  statusClass = "high";
                }
                
                // Display the moisture level with appropriate color based on the status
                client.println("<p class=\"status " + statusClass + "\">" + webisteout + "%</p>");
                
                client.println("</div>");
                client.println("</body></html>");

   
   
                  break;

             } else {
                currentLine = "";
              }
            } else if (c != '\r') {
              currentLine += c;
            }
          } else {
            break;
          }
        }
        client.stop();
        Serial.println("Client Disconnected.");
      }
}
