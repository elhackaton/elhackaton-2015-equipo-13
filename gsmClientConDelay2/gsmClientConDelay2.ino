/*
  Web client
 
 This sketch connects to a website through a GSM shield. Specifically,
 this example downloads the URL "http://arduino.cc/asciilogo.txt" and 
 prints it to the Serial monitor.
 
 Circuit:
 * GSM shield attached to an Arduino
 * SIM card with a data plan
 
 created 8 Mar 2012
 by Tom Igoe
 
 http://arduino.cc/en/Tutorial/GSMExamplesWebClient
 
 */

// libraries
#include <GSM.h>

// PIN Number
#define PINNUMBER "3450"

// APN data
#define GPRS_APN       "ac.vodafone.es" // replace your GPRS APN
#define GPRS_LOGIN     "vodafone"    // replace with your GPRS login
#define GPRS_PASSWORD  "vodafone" // replace with your GPRS password

// initialize the library instance
GSMClient client;
GPRS gprs;
GSM gsmAccess; 

// URL, path & port (for example: arduino.cc)
char server[] = "diccionarioeconomicsek.esy.es";
char path[] = "/family-Bot/subida.php";
int port = 80; // port 80 is the default for HTTP

unsigned long lastConnectionTime = 0;          // last time you connected to the server, in milliseconds
boolean lastConnected = false;                 // state of the connection last time through the main loop
const unsigned long postingInterval = 60*1000;  // delay between updates, in milliseconds

const byte dhtPin = 5;
byte errorCode; // código de error
byte dhtData[5]; //bytes leídos
String dhtDataOne = "";
String dhtDataTwo = "";
String data = "";

void setup()
{
    pinMode(dhtPin,OUTPUT);
  digitalWrite(dhtPin,HIGH);
  // initialize serial communications and wait for port to open:
  Serial.begin(9600);

  Serial.println("Starting Arduino web client.");
  // connection state
  boolean notConnected = true;

  // After starting the modem with GSM.begin()
  // attach the shield to the GPRS network with the APN, login and password
  while(notConnected){
    if((gsmAccess.begin(PINNUMBER)==GSM_READY) &
      (gprs.attachGPRS(GPRS_APN, GPRS_LOGIN, GPRS_PASSWORD)==GPRS_READY))
      notConnected = false;
    else
    {
      Serial.println("Not connected");
      delay(1000);
    }
  }
  
  
}

void loop() {
    delay(5000);
     Serial.println("conectando");

    // if there are incoming bytes available 
    // from the server, read them and print them:
    if (client.available()){
      char c = client.read();
      Serial.print(c);
    }

    // if there's no net connection, but there was one last time
  // through the loop, then stop the client:
  if (!client.connected() && lastConnected) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }

  
  
    // if you're not connected, and ten seconds have passed since
    // your last connection, then connect again and send data:
    if(!client.connected()) {
      readDHT(); // comenzamos la lectura
      dhtDataOne = String(dhtData[2]);
      dhtDataTwo = String(dhtData[3]);
      data = "value=" + String(dhtDataOne);
      methodPost();
    }
    // store the state of the connection for next time through
    // the loop:
    lastConnected = client.connected();
  
 
  
}


void methodPost (){
  
 if (client.connect(server, port)){
    Serial.println("connected");
    // Make a HTTP request:
    client.println("POST /family-Bot/subida.php HTTP/1.1"); //download text
    client.println("From: Arduino1");
    client.println("Host: diccionarioeconomicsek.esy.es");  // Will be needed if apache is configured for VHOSTS
    client.println("User-Agent: HTTPTool/1.1");
    client.println("Connection: close");
    client.println("Cache-Control : no-cache");
    client.println("Pragma: no-cache");
    client.println("Expires: -1");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.println(data);
    client.println();
      lastConnectionTime = millis();
  }
 
  else{
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
    client.stop();
  }
  
    
  
}



/*****************************************************
* Inicia la secuencia de envío de datos y recibe los
* 40 bits de información con temperatura y humedad
* Se encarga de generar los tres códigos posibles de error
*****************************************************/
void readDHT(){
  errorCode=0;//limpiamos último error
  byte dhtIn;
  byte i;
  
  digitalWrite(dhtPin,LOW); //handshake de comienzo
  delay(20);
  digitalWrite(dhtPin,HIGH);
  delayMicroseconds(40);
  pinMode(dhtPin,INPUT);

  dhtIn=digitalRead(dhtPin); // Lectura posible error
  //Condición 1 de comienzo
  if(dhtIn){// si se lee HIGH => error
    errorCode=1;
    return;
  }

  delayMicroseconds(80);// espera transición LOW HIGH

  dhtIn=digitalRead(dhtPin); // Lectura posible error
  //Condición 2 de comienzo
  if(!dhtIn){// si se lee LOW => error
    errorCode=2;
    return;
  }

  delayMicroseconds(80);

  //lectura byte a byte
  for (i=0; i<5; i++){
    dhtData[i] = readDHTByte();
  }
  
  // se pasa a high para la siguiente lectura
  pinMode(dhtPin,OUTPUT);
  digitalWrite(dhtPin,HIGH);

  //comprobación de checksum
  byte dht_check_sum =
    dhtData[0]+dhtData[1]+dhtData[2]+dhtData[3];
  if(dhtData[4]!= dht_check_sum){
    errorCode=3;
  }

};

/*****************************************************
* Lee un byte teniendo en cuenta los tiempos de HIGH
******************************************************/
byte readDHTByte(){
  byte i = 0;
  byte result=0;
  
  for(i=0; i< 8; i++){
    while(digitalRead(dhtPin)==LOW);
    delayMicroseconds(30);   
    if (digitalRead(dhtPin)==HIGH){
      result |=(1<<(7-i));
    }
    while (digitalRead(dhtPin)==HIGH);
  }

  return result;
}

