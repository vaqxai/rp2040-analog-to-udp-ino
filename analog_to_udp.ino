#include <SPI.h>
#include <WiFiNINA.h>

char ssid[] = "arduwifi";
char pass[] = "somepassword";
IPAddress client_addr;
uint16_t client_port;
bool client_defined = false;

short a0 = 0;
short a1 = 0;
short a2 = 0;
short a3 = 0;

WiFiUDP server;

void setup() {
  server.begin(4000);

  WiFi.beginAP(ssid, pass);

  pinMode(LEDB, OUTPUT);
}

void loop() {
  if (WiFi.status() != WL_AP_CONNECTED) {
    return; // skip loop if no device connected
  }

  a0 = analogRead(A0);
  a1 = analogRead(A1);
  a2 = analogRead(A2);
  a3 = analogRead(A3);

  if (server.parsePacket() > 0 && !client_defined) {
    client_addr = server.remoteIP();
    client_port = server.remotePort();
    client_defined = true;
    // TODO: Multiple clients?
  }

  digitalWrite(LEDB, HIGH);
  server.beginPacket(client_addr, client_port);
    // 2 bytes per number * 4 = 8 bytes
    // 2 bytes per separator * 3 = 6 bytes
    // total = 14 bytes, 22 chars with the terminator
    char buf[22];
    sprintf(buf, "%04d:%04d:%04d:%04d\r\n", a0, a1, a2, a3);
    server.write(buf, 22);
  server.endPacket();
  digitalWrite(LEDB, LOW);
}
