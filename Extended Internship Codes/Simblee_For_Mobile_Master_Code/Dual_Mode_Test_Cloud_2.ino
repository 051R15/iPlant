#include <SimbleeForMobile.h>
#include <SimbleeBLE.h>
#include <SimbleeForMobileClient.h>
#include <SimbleeCloud.h>

//SimbleeCloud ESNs
unsigned int userId = 0xe42532dd;
unsigned int destESN = 0x60606060;

SimbleeForMobileClient client;
SimbleeCloud cloud(&client);

uint8_t screenA;
uint8_t textPlant;
uint8_t buttonA;

char valueA[7];
char valueB[5];
char valueC[5];

char dataArray[3]; //Data sent to cloud.

float dataValA; // Temperature
int dataValB; //Light

void setup() {
  Serial.begin(115200);

  valueA[6] = '\0';
  valueB[4] = '\0';
  valueC[4] = '\0';
  
  SimbleeForMobile.deviceName = "Dual";
  SimbleeForMobile.advertisementData = "Mode";

  Serial.print("The ESN of my Simblee is 0x");
  Serial.println(cloud.myESN, HEX);
  cloud.userID = userId;

  SimbleeForMobile.begin();  
}
      
void loop(){   
  //cloud.send(destESN, valueA, 7);
  //Serial.println(valueA);
  //Serial.println();
  //delay(1000);

  dataValA = atof(valueA);
  //Serial.print("TEST: ");
  //Serial.println(dataValA);
  //delay(1000);

  dataValB = atoi(valueB);
  //Serial.print("TESTB: ");
  //Serial.println(dataValB);
  //delay(1000);

  dataArray[0] = '9';
  dataArray[1] = dataValA;
  dataArray[2] = dataValB;

  cloud.send(destESN, dataArray, 3);
  
  SimbleeForMobile.process();
  cloud.process();
}

void ui()
{  
  if (cloud.connect()){
    Serial.println("Cloud Connected");
  }else{
    Serial.println("Cloud Disconnected");
  }
  SimbleeForMobile.beginScreen();

  screenA = SimbleeForMobile.drawRect(0, 0, SimbleeForMobile.screenWidth, SimbleeForMobile.screenHeight, BLUE);

  textPlant = SimbleeForMobile.drawText(100, 100, "iPlant", YELLOW, 30);

  buttonA = SimbleeForMobile.drawButton(50, 200, 100, "Click", BOX_TYPE);

  SimbleeForMobile.setEvents(buttonA, EVENT_PRESS);
  
  SimbleeForMobile.endScreen();
}

void ui_event(event_t &event)
{
}

void SimbleeCloud_onReceive(unsigned int originESN, const unsigned char *payload, int len){
  
}

void SimbleeCOM_onReceive(unsigned int esn, const char* payload, int len, int rssi) {
  if (payload[0] == '1'){
  //Serial.println("Payload Received");
  //Serial.print("Temperature Value: ");
  //Serial.print(payload[1]);
  //Serial.print(payload[2]);
  //Serial.print(payload[3]);
  //Serial.print(payload[4]);
  //Serial.print(payload[5]);
  //Serial.println(payload[6]);
  //Serial.println();
  valueA[0] = payload[1];
  valueA[1] = payload[2];
  valueA[2] = payload[3];
  valueA[3] = payload[4];
  valueA[4] = payload[5];
  valueA[5] = payload[6];
  //Serial.print("Test: ");
  //Serial.println(valueA);
  //Serial.println();
  }
  
  else if (payload[0] == '2'){
  //Serial.println("Payload B Received");
  //Serial.print("Clear Light Value: ");
  //Serial.print(payload[1]);
  //Serial.print(payload[2]);
  //Serial.print(payload[3]);
  //Serial.println(payload[4]);
  //Serial.println();
  valueB[0] = payload[1];
  valueB[1] = payload[2];
  valueB[2] = payload[3];
  valueB[3] = payload[4];
  //Serial.print("Test B: ");
  //Serial.println(valueB);
  //Serial.println();
  }

  //if (payload[0] == '3') {
    //Serial.println("Payload C Received");
    //Serial.print("ECO2 Value: ");
    //Serial.print(payload[1]);
    //Serial.print(payload[2]);
    //Serial.print(payload[3]);
    //Serial.println(payload[4]);
    //Serial.println();
    //valueC[0] = payload[1];
    //valueC[1] = payload[2];
    //valueC[2] = payload[3];
    //valueC[3] = payload[4];
    //Serial.print("Test C: ");
    //Serial.println(valueC);
    //Serial.println();
  //}
}

void SimbleeBLE_onDualModeStart () {
}

void SimbleeBLE_onDualModeEnd () {}

void SimbleeForMobile_onConnect () {
    SimbleeBLE.dualModeBegin();
    Serial.println("Simblee For Mobile Connected");
}

void SimbleeForMobile_onDisconnect () {
  SimbleeBLE.dualModeEnd();
  Serial.println("SimbleeForMobile Disconnected");
}
