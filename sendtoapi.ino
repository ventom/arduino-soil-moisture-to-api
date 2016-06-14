#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:

char server[] = "ventsi.dev.ventom-solutions.com";    // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192,168,0,177);

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;


int numRetries = 0;
void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
 connectToServer();
}

void loop()
{
   numRetries++;
  // if there are incoming bytes available 
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
  
  
  sendtoserver();

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    //while(true);
    delay(2000);
  }
  
  if(numRetries%10==0)
    connectToServer();
}

void sendtoserver()
{
   
  
    int sensorValue = analogRead(A1);
    String sensorValueString = String(sensorValue);
    
    Serial.println(sensorValue);

    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /arduino/api/?moisture="+sensorValueString+" HTTP/1.1");
    client.println("Host: ventsi.dev.ventom-solutions.com");
   // client.println("Connection: close");
    client.println();
  
  delay(1000);
}

void connectToServer()
{
   
      Serial.println("Starting");
      // start the Ethernet connection:
      if (Ethernet.begin(mac) == 0) {
        Serial.println("Failed to configure Ethernet using DHCP");
        // no point in carrying on, so do nothing forevermore:
        // try to congifure using IP address instead of DHCP:
        Ethernet.begin(mac, ip);
      }
      Serial.println("After start");
      // give the Ethernet shield a second to initialize:
      delay(1000);
      Serial.println("connecting...");
      // if you get a connection, report back via serial:
      if (client.connect(server, 80)) {
        Serial.println("connected to host");
      } 
      else {
        // kf you didn't get a connection to the server:
        Serial.println("connection failed");
      }
  
}
