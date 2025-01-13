#include <ESP8266WiFi.h>                              
#include <FirebaseESP8266.h> 
#include <PubSubClient.h>                            
#include "DHT.h"                                        
#define KITCHEN_LED D1                                     
#define OFFICE_LED D2                                    
#define BEDROOM_LED D5                                     
#define CHILDREN_ROOM_LED D6                                     
#define DHT_PIN D7  

const char* ssid = "Ahmed";                          
const char* password = "123456789";                  

// const char* broker = "192.168.137.1";                 
// const int port = 1883;   

// Firebase Realtime Database URL and secret
const char* FIREBASE_HOST = "iotproject-db999-default-rtdb.firebaseio.com";
const char* FIREBASE_AUTH = "EyNf3B6hzSyupSNr5uWnnfFBxcQVsduOZdJg1dan";

// float h = 0.0;                         
// float t = 0.0;

int photoresistor = 0;                  
float threshold = 250.0;

DHT dht(DHT_PIN, DHT11);

WiFiClient espClient;                                 
PubSubClient client(espClient);  

FirebaseData fbdo; 


void setup() {
  Serial.begin(9600);       
  pinMode(KITCHEN_LED, OUTPUT);                  
  pinMode(OFFICE_LED, OUTPUT);                  
  pinMode(BEDROOM_LED, OUTPUT);                  
  pinMode(CHILDREN_ROOM_LED, OUTPUT);                  
  WiFi.begin(ssid, password);             // Begin WiFi connection using SSID and password

  while(WiFi.status() != WL_CONNECTED){         // Check if the WiFi status is not connected
    delay(1000);                                // Wait 1 second between WiFi connection checks
    Serial.println("Connecting to WiFi...");    // Print message indicating an attempt to connect to WiFi
  }

  Serial.println("Connected to WiFi.");         // Print message when WiFi connection is successful
  Serial.print("IP Address: ");                 // Print the label for the IP address
  Serial.println(WiFi.localIP());               // Print the assigned IP address
  
  dht.begin();                                  // Start DHT sensor
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); // Initialize Firebase connection
  Firebase.reconnectWiFi(true);                 // Automatic reconnection to WiFi if connection is lost
}


void loop()
{    

  LED(KITCHEN_LED, getFirebaseReads("home/kitchen/led"));
  LED(OFFICE_LED, getFirebaseReads("home/office/led"));
  LED(BEDROOM_LED, getFirebaseReads("home/bedroom/led"));
  LED(CHILDREN_ROOM_LED, getFirebaseReads("home/children_room/led"));

  // LDR();

  DHT11Senor();               
  
  delay(1000);    

}







