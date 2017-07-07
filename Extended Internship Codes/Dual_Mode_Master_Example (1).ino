#include <SimbleeForMobile.h>
#include <SimbleeBLE.h>

uint8_t screenA;
uint8_t textPlant;
uint8_t buttonA;

char valueA[6];

int incomingByte;

void setup() {
  Serial.begin(115200);
  
  SimbleeForMobile.deviceName = "Dual";
  SimbleeForMobile.advertisementData = "Mode";

  SimbleeForMobile.begin();  
}
      
void loop(){   
  SimbleeForMobile.process();
}

void ui()
{  
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

void SimbleeCOM_onReceive(unsigned int esn, const char* payload, int len, int rssi) {
  if (payload[0] == '1'){
  //Serial.println("Payload Received");
  //Serial.print("Temperature Value: ");
  Serial.print(payload[1]);
  Serial.print(payload[2]);
  Serial.print(payload[3]);
  Serial.print(payload[4]);
  Serial.print(payload[5]);
  Serial.println(payload[6]);
  Serial.println();
  valueA[0] = payload[1];
  valueA[1] = payload[2];
  valueA[2] = payload[3];
  valueA[3] = payload[4];
  valueA[4] = payload[5];
  valueA[5] = payload[6];
  Serial.print("Test: ");
  Serial.println(valueA);
  Serial.println();
  }
  
  if (payload[0] == '2'){
  //Serial.println("Payload B Received");
  //Serial.print("Clear Light Value: ");
  //Serial.print(payload[1]);
  //Serial.print(payload[2]);
  //Serial.print(payload[3]);
  //Serial.println(payload[4]);
  //Serial.println();
  }

  if (payload[0] == '3'){
    //Serial.println("Payload C Received");
    //Serial.print("ECO2 Value: ");
    //Serial.print(payload[1]);
    //Serial.print(payload[2]);
    //Serial.print(payload[3]);
    //Serial.println(payload[4]);
    //Serial.println();
  }
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
