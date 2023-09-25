
#include <ESP8266WiFi.h>

WiFiClient client;
WiFiServer server(80);

/* WIFI settings */
const char* ssid = "385!";
const char* password = "chaynhutthuduc";

/* data received from application */
String  data =""; 

/* define L298N or L293D motor control pins */
int relay1 = 4;     /* GPIO4(D2) -> IN3   */
int relay2 = 2;   /* GPIO2(D4) -> IN1  */


void setup()
{
  /* initialize motor control pins as output */
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT); 
  Serial.begin(115200);
  connectWiFi();

  server.begin();
}

void loop()
{
    /* If the server available, run the "checkClient" function */  
    client = server.available();
    if (!client) return; 
    data = checkClient ();
  

    if (data == "r1on") turnonrelay(relay1);
    
    else if (data == "r1off") turnoffrelay(relay1);
   
    else if (data == "r2on") turnonrelay(relay2);
   
    else if (data == "r2off") turnoffrelay(relay2);
} 

/********************************************* TURN ON RELAY *****************************************************/
void turnonrelay(int relay)
{
  digitalWrite(relay,HIGH);
  }
  
void turnoffrelay(int relay)
{
  digitalWrite(relay,LOW);
  }
/********************************** RECEIVE DATA FROM the APP ******************************************/
String checkClient (void)
{
  while(!client.available()) delay(1); 
  String request = client.readStringUntil('\r');
  Serial.println(request);
  request.remove(0, 5);
  Serial.println(request);
  request.remove(request.length()-9,9);
  Serial.println(request);
  return request;
}
void connectWiFi()
{
  Serial.println("Connecting to WIFI");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(300);
    Serial.print("..");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("NodeMCU Local IP is : ");
  Serial.print((WiFi.localIP()));
}
