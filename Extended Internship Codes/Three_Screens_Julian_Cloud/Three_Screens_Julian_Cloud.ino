#include <SimbleeForMobile.h>
#include <SimbleeBLE.h>
#include <SimbleeForMobileClient.h>
#include <SimbleeCloud.h>

//SimbleeCloud ESNs
unsigned int userId = 0xe42532dd;
unsigned int destESN = 0x60606060;

SimbleeForMobileClient client;
SimbleeCloud cloud(&client);

//Signal sent to the sensors to allow them to send data
char signalBLE[2];
char signal2BLE[2];

//Arrays sent to Cloud
char lightValue[6];
char temperatureValue[7];
char humidityValue[7];
char CO2Value[6];

//Character Arrays storing values received from the sensors
char valueA[5]; //Light Values
char valueB[6]; //Temperature Values
char valueC[6]; //Humidity Values
char valueD[5]; //ECO2 Values

//Buttons
int AtoB;
int BtoA;

int currentScreen;
int screenTest;

int lightVal, tempVal, humVal, CO2Val;

void setup() {
  Serial.begin(115200);

  signalBLE[0] = '6'; //Signal to Light Sensor
  signalBLE[1] = '9'; //Signal to CO2 Sensor
  signal2BLE[0] = '7'; //Signal to Temperature Sensor
  signal2BLE[1] = '8'; //Signal to Humidity Sensor

  valueA[4] = '\0';
  valueB[5] = '\0';
  valueC[5] = '\0';
  valueD[4] = '\0';
  
  SimbleeForMobile.deviceName = "Julian";
  SimbleeForMobile.advertisementData = "Test";

  SimbleeForMobile.domain = "twoscreens.simblee.com";

  Serial.print("The ESN of my Simblee is 0x");
  Serial.println(cloud.myESN, HEX);
  cloud.userID = userId;

  SimbleeForMobile.begin();
}

void loop() {
  //Send a staggered signal to the sensors
  SimbleeCOM.send(signalBLE, 2);
  delay(100);
  SimbleeCOM.send(signal2BLE, 2);

  if (screenTest == 0){
    SimbleeForMobile.showScreen(1);
    screenTest = 2;
  }
  else if (screenTest == 1){
    SimbleeForMobile.showScreen(2);
    screenTest = 2;
  }

  if (SimbleeForMobile.updatable){
    if (currentScreen == 2){
    SimbleeForMobile.updateText(lightVal, valueA);
    SimbleeForMobile.updateText(tempVal, valueB);
    SimbleeForMobile.updateText(humVal, valueC);
    SimbleeForMobile.updateText(CO2Val, valueD);
    }
  }

  //Light Array:
  lightValue[0] = '5';
  lightValue[1] = valueA[0];
  lightValue[2] = valueA[1];
  lightValue[3] = valueA[2];
  lightValue[4] = valueA[3];
  lightValue[5] = valueA[4];
  cloud.send(destESN, lightValue, sizeof(lightValue));

  //Temperature Array:
  temperatureValue[0] = '6';
  temperatureValue[1] = valueB[0];
  temperatureValue[2] = valueB[1];
  temperatureValue[3] = valueB[2];
  temperatureValue[4] = valueB[3];
  temperatureValue[5] = valueB[4];
  temperatureValue[6] = valueB[5];
  cloud.send(destESN, temperatureValue, sizeof(temperatureValue));

  //Humidity Array:
  humidityValue[0] = '7';
  humidityValue[1] = valueC[0];
  humidityValue[2] = valueC[1];
  humidityValue[3] = valueC[2];
  humidityValue[4] = valueC[3];
  humidityValue[5] = valueC[4];
  humidityValue[6] = valueC[5];
  cloud.send(destESN, humidityValue, sizeof(humidityValue));

  //CO2 Array:
  CO2Value[0] = '8';
  CO2Value[1] = valueD[0];
  CO2Value[2] = valueD[1];
  CO2Value[3] = valueD[2];
  CO2Value[4] = valueD[3];
  CO2Value[5] = valueD[4];
  cloud.send(destESN, CO2Value, sizeof(CO2Value));
  
  SimbleeForMobile.process(); 
  cloud.process(); 
}

void SimbleeForMobile_onConnect()
{
  currentScreen = -1;
  screenTest = 0;
  SimbleeBLE.dualModeBegin();
  Serial.println("Simblee For Mobile Connected");
}

void SimbleeForMobile_onDisconnect () {
  SimbleeBLE.dualModeEnd();
  Serial.println("SimbleeForMobile Disconnected");
}

void ui(){
  if (cloud.connect()){
    Serial.println("Cloud Connected");
  }else{
    Serial.println("Cloud Disconnected");
  }
  
  if(SimbleeForMobile.screen == currentScreen) return;
  
  currentScreen = SimbleeForMobile.screen;
  switch(SimbleeForMobile.screen)
  {
    case 1:
      createScreen1();
      break;
       
    case 2:
      createScreen2();
      break;            
  }
}

void ui_event(event_t &event){
  if(event.id == BtoA && event.type == EVENT_RELEASE && currentScreen == 2)
  {
    screenTest = 0;
  } else if(event.id == AtoB && event.type == EVENT_RELEASE && currentScreen == 1) 
  {
    screenTest = 1;
  }
}

void createScreen1()
{
  SimbleeForMobile.beginScreen(WHITE);

  int iPlant = SimbleeForMobile.drawText(105, 30, "iPlant", BLACK, 50);
  int forMobile = SimbleeForMobile.drawText(120, 80, "For Mobile", BLACK, 20);
  int screenA = SimbleeForMobile.drawText(145, 510, "Login", BLACK, 10);

  //"Welcome Back" message
  int welcomeMessage = SimbleeForMobile.drawText(100, 350, "Welcome back!", BLACK, 20);

  //"Enter Username" modules
  int enterName = SimbleeForMobile.drawText(60, 180, "Enter your username here: ", BLACK, 15);
  int userName = SimbleeForMobile.drawTextField(60, 200, 200, "", "Username: ", BLACK, WHITE);

  AtoB = SimbleeForMobile.drawButton(200, 500, 100, "NEXT", BOX_TYPE);
  
  SimbleeForMobile.setEvents(AtoB, EVENT_RELEASE);
  SimbleeForMobile.endScreen();
}

void createScreen2()
{
  SimbleeForMobile.beginScreen(WHITE);

  int textID = SimbleeForMobile.drawText(140, 40, "Home", BLACK, 20);
  BtoA = SimbleeForMobile.drawButton(20, 500, 100, "Logout", BOX_TYPE);

  //"Enter Plant Name" modules
  int enterPlant = SimbleeForMobile.drawText(60, 120, "Enter your plant name here: ", BLACK, 15);
  int plantField = SimbleeForMobile.drawTextField(60, 140, 200, "", "Plant: ", BLACK, WHITE);

  //"Title" for each value
  int lightText = SimbleeForMobile.drawText(50, 220, "Light: ", BLACK, 20);
  int tempText = SimbleeForMobile.drawText(50, 270, "Temperature: ", BLACK, 20);
  int humText = SimbleeForMobile.drawText(50, 320, "Humidity: ", BLACK, 20);
  int CO2Text = SimbleeForMobile.drawText(50, 370, "CO2: ", BLACK, 20);

  //Updating Values on the UI
  lightVal = SimbleeForMobile.drawText(190, 220, "", BLACK, 20);
  tempVal = SimbleeForMobile.drawText(190, 270, "", BLACK, 20);
  humVal = SimbleeForMobile.drawText(190, 320, "", BLACK, 20);
  CO2Val = SimbleeForMobile.drawText(190, 370, "", BLACK, 20);

  //Units
  int unitLight = SimbleeForMobile.drawText(240, 220, "cd", BLACK, 20);
  int unitTemp = SimbleeForMobile.drawText(240, 270, "\xb0" "C", BLACK, 20);
  int unitHum = SimbleeForMobile.drawText(240, 320, "%", BLACK, 20);
  int unitCO2 = SimbleeForMobile.drawText(240, 370, "ppm", BLACK, 20);

  SimbleeForMobile.setEvents(BtoA, EVENT_RELEASE);
  SimbleeForMobile.endScreen();
}

void printEvent(event_t &event)
{
  Serial.println("Event:");
  Serial.print("  ID: ");
  Serial.println(event.id);
  
  Serial.print("   Type: ");
  Serial.println(event.type);  

  Serial.print("   Value: ");
  Serial.println(event.value);
  
  Serial.print("   Text: ");
  Serial.println(event.text);  
  
  Serial.print("   Coords: ");
  Serial.print(event.x);  
  Serial.print(",");  
  Serial.println(event.y);  
}

void SimbleeCloud_onReceive(unsigned int originESN, const unsigned char *payload, int len){ 
}

void SimbleeCOM_onReceive(unsigned int esn, const char* payload, int len, int rssi) {
  //First read Light pointer '1' before storing sensor values into valueA
  if (payload[0] == '1'){
  valueA[0] = payload[1];
  valueA[1] = payload[2];
  valueA[2] = payload[3];
  valueA[3] = payload[4];
  Serial.print("Light: ");
  Serial.println(valueA);
  Serial.println();
  }
  
  //First read Humidity pointer '3' before storing sensor values into valueC
  else if (payload[0] == '3'){
    valueC[0] = payload[1];
    valueC[1] = payload[2];
    valueC[2] = payload[3];
    valueC[3] = payload[4];
    valueC[4] = payload[5];
    Serial.print("Humidity: ");
    Serial.println(valueC);
    Serial.println();
  }

  //First read ECO2 pointer '4' before storing sensor values into valueD
  if (payload[0] == '4'){
    valueD[0] = payload[1];
    valueD[1] = payload[2];
    valueD[2] = payload[3];
    valueD[3] = payload[4];
    Serial.print("ECO2: ");
    Serial.println(valueD);
    Serial.println();
  }

  //First read Temperature pointer '2' before storing sensor values into valueB
  else if (payload[0] == '2'){
    valueB[0] = payload[1];
    valueB[1] = payload[2];
    valueB[2] = payload[3];
    valueB[3] = payload[4];
    valueB[4] = payload[5];
    Serial.print("Temperature: ");
    Serial.println(valueB);
    Serial.println();
  }
}

void SimbleeBLE_onDualModeStart () {
}

void SimbleeBLE_onDualModeEnd () {
}
