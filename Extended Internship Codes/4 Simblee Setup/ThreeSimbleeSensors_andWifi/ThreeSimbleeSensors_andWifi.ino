#include <SimbleeForMobile.h>
#include <SimbleeBLE.h>
#include <SPI.h>
#include <SimbleeWiFi.h>
#include <SimbleeWiFiSSLClient.h>
#include <SimbleeCloud.h>
#include "plant_jpg.h"

//SimbleeCloud ESNs
unsigned int userId = 0xe42532dd;
unsigned int destESN = 0x60606060;

//Simblee Cloud has to pass through a SimbleeWiFiSSSLClient Client instance
SimbleeWiFiSSLClient client;
SimbleeCloud cloud(&client);

char ssid[] = "HeptagonPublic";
char password[] = "0ptiC3nG";

//Signal sent to the sensors to allow them to send data
char signalBLE[2];
char signal2BLE[2];

//RGB LED Shield
int redLed = 2;
int greenLed = 3;

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
int otherPlant;

//Text
int iPlant, forMobile;
int homeText, loginText;
int welcomeMessage, ESNText;
int enterPlant, enterName;
int lightText, tempText, humText, CO2Text;
int lightVal, tempVal, humVal, CO2Val;
int unitLight, unitTemp, unitHum, unitCO2;
int displayText, nameAloe, nameOrchid, nameTulip, nameFern, nameCactus, nameFicus, unrecognizedText;
int keyText, redText, greenText, contactText;

//Text Fields
int userName;
int plantField;

//'Pointer' Variables
int screenValue = 1;
int whatPlant = 0;

//Plants
String aloeVera = String("Aloe Vera");
String orchid = String("Orchid");
String tulip = String("Tulip");
String fern = String("Fern");
String cactus = String("Cactus");
String ficus = String("Ficus");

//Variables storing character arrays into integers/floats for compare functions
uint16_t lightCheck;
float tempCheck;
float humCheck;
uint16_t CO2Check;

long initialTime = 0;
long resetTime = 2000;

int counter = 0;

void setup() {
  Serial.begin(115200);

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi Shield not present");
    while (1);
  }

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  signalBLE[0] = '6'; //Signal to Light Sensor
  signalBLE[1] = '9'; //Signal to CO2 Sensor
  signal2BLE[0] = '7'; //Signal to Temperature Sensor
  signal2BLE[1] = '8'; //Signal to Humidity Sensor

  valueA[4] = '\0';
  valueB[5] = '\0';
  valueC[5] = '\0';
  valueD[4] = '\0';

  SimbleeForMobile.deviceName = "iPlant";
  SimbleeForMobile.advertisementData = "forMobile";

  Serial.print("The ESN of my Simblee is 0x");
  Serial.println(cloud.myESN, HEX);
  cloud.userID = userId;

  SimbleeForMobile.begin();
  SimbleeBLE.dualModeBegin();
}

void join()
{
  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  WiFi.begin(ssid, password);

  // wait 10 seconds for connection:
  uint8_t timeout = 10;
  while (timeout && (WiFi.status() != WL_CONNECTED))
  {
    timeout--;
    delay(1000);
  }

  if (WiFi.status() != WL_CONNECTED)
    return;

  Serial.println("Connected to wifi");
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);


  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void connect()
{
  if (WiFi.status() == WL_CONNECTED && cloud.connect()){
    printf("cloud active\n");
    }
  else{
    printf("cloud failed\n");
    }
}

void loop() {
  if (WiFi.status() != WL_CONNECTED)
  {
    // reconnect if we lose connection
    join();
    connect();
    return;
  }

  unsigned long currentMillis = millis();
  
  if (currentMillis - initialTime > resetTime){
    initialTime = currentMillis;
    counter = ++ counter;
    Serial.print("Counter: ");
    Serial.println(counter);
    //Simblee_systemReset();
  }

  
  //Send a staggered signal to the sensors
  SimbleeCOM.send(signalBLE, 2);
  delay(100);
  SimbleeCOM.send(signal2BLE, 2);

  //Light Array:
  lightValue[0] = '5';
  lightValue[1] = valueA[0];
  lightValue[2] = valueA[1];
  lightValue[3] = valueA[2];
  lightValue[4] = valueA[3];
  lightValue[5] = valueA[4];
  cloud.send(destESN, lightValue, sizeof(lightValue));
  //counter = ++counter;

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

  lightCheck = atoi(valueA);
  tempCheck = atof(valueB);
  humCheck = atof(valueC);
  CO2Check = atoi(valueD);

  if (SimbleeForMobile.updatable) {
    SimbleeForMobile.updateText(lightVal, valueA);
    SimbleeForMobile.updateText(tempVal, valueB);
    SimbleeForMobile.updateText(humVal, valueC);
    SimbleeForMobile.updateText(CO2Val, valueD);
  }

  if (whatPlant == 0 && screenValue == 2) {
    whatHappens0();
  }
  if (whatPlant == 1 && screenValue == 2) {
    whatHappens1();
  }
  if (whatPlant == 2 && screenValue == 2) {
    whatHappens2();
  }
  if (whatPlant == 3 && screenValue == 2) {
    whatHappens3();
  }
  if (whatPlant == 4 && screenValue == 2) {
    whatHappens4();
  }
  if (whatPlant == 5 && screenValue == 2) {
    whatHappens5();
  }
  if (whatPlant == 6 && screenValue == 2) {
    whatHappens6();
  }
  if (whatPlant == 7 && screenValue == 2) {
    whatHappens7();
  }

  
  if (counter == 15){
    Serial.println("RESET INITIATED");
    Simblee_systemReset();  
  }
  
  SimbleeForMobile.process();
  cloud.process();

  delay(1000);
}

void SimbleeForMobile_onConnect()
{
  Serial.println("Simblee For Mobile Connected");
}

void SimbleeForMobile_onDisconnect () {
  Serial.println("SimbleeForMobile Disconnected");
}

void ui() {
  #define IMAGE1 1
  #define IMAGE2 2
  SimbleeForMobile.beginScreen(WHITE, PORTRAIT);

  //imageSource for image
  SimbleeForMobile.imageSource(IMAGE1, JPG, plant_jpg, plant_jpg_len);
  //draw Image
  SimbleeForMobile.drawImage(IMAGE1, 80, 280);

  //Login Screen
  iPlant = SimbleeForMobile.drawText(105, 30, "iPlant", BLACK, 50);
  forMobile = SimbleeForMobile.drawText(120, 80, "For Mobile", BLACK, 20);
  loginText = SimbleeForMobile.drawText(145, 510, "Login", BLACK, 10);
  welcomeMessage = SimbleeForMobile.drawText(100, 250, "Welcome back!", BLACK, 20);
  enterName = SimbleeForMobile.drawText(60, 180, "Enter your username here: ", BLACK, 15);
  userName = SimbleeForMobile.drawTextField(60, 200, 200, "", "Username: ", BLACK, WHITE);
  AtoB = SimbleeForMobile.drawButton(200, 500, 100, "NEXT", BOX_TYPE);
  SimbleeForMobile.setVisible(AtoB, false);
  SimbleeForMobile.setVisible(welcomeMessage, false);

  //Home-Data Screen
  homeText = SimbleeForMobile.drawText(140, 40, "Home", BLACK, 20);
  BtoA = SimbleeForMobile.drawButton(20, 500, 100, "Logout", BOX_TYPE);
  enterPlant = SimbleeForMobile.drawText(60, 120, "Enter your plant name here: ", BLACK, 15);
  plantField = SimbleeForMobile.drawTextField(60, 140, 200, "", "Plant: ", BLACK, WHITE);
  lightText = SimbleeForMobile.drawText(50, 220, "Light: ", BLACK, 20);
  tempText = SimbleeForMobile.drawText(50, 270, "Temperature: ", BLACK, 20);
  humText = SimbleeForMobile.drawText(50, 320, "Humidity: ", BLACK, 20);
  CO2Text = SimbleeForMobile.drawText(50, 370, "CO2: ", BLACK, 20);
  lightVal = SimbleeForMobile.drawText(190, 220, "", BLACK, 20);
  tempVal = SimbleeForMobile.drawText(190, 270, "", BLACK, 20);
  humVal = SimbleeForMobile.drawText(190, 320, "", BLACK, 20);
  CO2Val = SimbleeForMobile.drawText(190, 370, "", BLACK, 20);
  unitLight = SimbleeForMobile.drawText(240, 220, "cd", BLACK, 20);
  unitTemp = SimbleeForMobile.drawText(240, 270, "\xb0" "C", BLACK, 20);
  unitHum = SimbleeForMobile.drawText(240, 320, "%", BLACK, 20);
  unitCO2 = SimbleeForMobile.drawText(240, 370, "ppm", BLACK, 20);
  displayText = SimbleeForMobile.drawText(90, 120, "Displaying: ", BLACK, 15);
  nameAloe = SimbleeForMobile.drawText(170, 120, "Aloe Vera", BLACK, 15);
  nameOrchid = SimbleeForMobile.drawText(170, 120, "Orchid", BLACK, 15);
  nameTulip = SimbleeForMobile.drawText(170, 120, "Tulip", BLACK, 15);
  nameFern = SimbleeForMobile.drawText(170, 120, "Fern", BLACK, 15);
  nameCactus = SimbleeForMobile.drawText(170, 120, "Cactus", BLACK, 15);
  nameFicus = SimbleeForMobile.drawText(170, 120, "Ficus", BLACK, 15);
  unrecognizedText = SimbleeForMobile.drawText(75, 120, "Unrecognized Plant Selected", BLACK, 15);
  otherPlant = SimbleeForMobile.drawButton(85, 160, 150, "Select another plant", BLUE, TEXT_TYPE);
  keyText = SimbleeForMobile.drawText(80, 430, "Key:", BLACK, 10);
  greenText = SimbleeForMobile.drawText(110, 420, "Green: Desirable Conditions", GREEN, 10);
  redText = SimbleeForMobile.drawText(110, 440, "Red: Undesirable Conditions", RED, 10);
  contactText = SimbleeForMobile.drawText(10, 450, "Would you like to iPlant to recognize your Plant? Contact us on our website.", BLACK, 10);

  //Initialise Home-Data Screen Modules to invisible
  SimbleeForMobile.setVisible(homeText, false);
  SimbleeForMobile.setVisible(BtoA, false);
  SimbleeForMobile.setVisible(enterPlant, false);
  SimbleeForMobile.setVisible(plantField, false);
  SimbleeForMobile.setVisible(lightText, false);
  SimbleeForMobile.setVisible(tempText, false);
  SimbleeForMobile.setVisible(humText, false);
  SimbleeForMobile.setVisible(CO2Text, false);
  SimbleeForMobile.setVisible(lightVal, false);
  SimbleeForMobile.setVisible(tempVal, false);
  SimbleeForMobile.setVisible(humVal, false);
  SimbleeForMobile.setVisible(CO2Val, false);
  SimbleeForMobile.setVisible(unitLight, false);
  SimbleeForMobile.setVisible(unitTemp, false);
  SimbleeForMobile.setVisible(unitHum, false);
  SimbleeForMobile.setVisible(unitCO2, false);
  SimbleeForMobile.setVisible(displayText, false);
  SimbleeForMobile.setVisible(nameAloe, false);
  SimbleeForMobile.setVisible(nameOrchid, false);
  SimbleeForMobile.setVisible(nameTulip, false);
  SimbleeForMobile.setVisible(nameFern, false);
  SimbleeForMobile.setVisible(nameCactus, false);
  SimbleeForMobile.setVisible(nameFicus, false);
  SimbleeForMobile.setVisible(otherPlant, false);
  SimbleeForMobile.setVisible(unrecognizedText, false);
  SimbleeForMobile.setVisible(keyText, false);
  SimbleeForMobile.setVisible(greenText, false);
  SimbleeForMobile.setVisible(redText, false);
  SimbleeForMobile.setVisible(contactText, false);

  //Set Button Press Events
  SimbleeForMobile.setEvents(AtoB, EVENT_PRESS);
  SimbleeForMobile.setEvents(BtoA, EVENT_PRESS);
  SimbleeForMobile.setEvents(otherPlant, EVENT_PRESS);

  SimbleeForMobile.endScreen();
}

void ui_event(event_t &event) {
  //If Button AtoB is pressed, show Home Screen. If Button BtoA is pressed, show Login Screen.
  if (event.id == AtoB) {
    showScreenB();
  }
  else if (event.id == BtoA) {
    showScreenA();
  }

  //Code to set Next Button and Welcome Message visible or not
  if (event.id == userName) {
    if (event.text != NULL) {
      SimbleeForMobile.setVisible(AtoB, true);
      SimbleeForMobile.setVisible(welcomeMessage, true);
    }
  } else if (screenValue == 2 || event.text == NULL || event.text == "") {
    if (SimbleeForMobile.updatable) {
      SimbleeForMobile.setVisible(AtoB, false);
      SimbleeForMobile.setVisible(welcomeMessage, false);
      SimbleeForMobile.updateText(userName, "");
    }
  }

  //Code to set Plant Text Field visible/invisible + set Plant name visible/invisible
  if (event.id == plantField) {
    String userPlant(event.text);

    if (userPlant.equals(aloeVera)) {
      whatPlant = 2;
      SimbleeForMobile.updateText(plantField, "");
      SimbleeForMobile.setVisible(plantField, false);
      SimbleeForMobile.setVisible(enterPlant, false);
      SimbleeForMobile.setVisible(displayText, true);
      SimbleeForMobile.setVisible(nameAloe, true);
      SimbleeForMobile.setVisible(otherPlant, true);
    }
    if (userPlant.equals(orchid)) {
      whatPlant = 3;
      SimbleeForMobile.updateText(plantField, "");
      SimbleeForMobile.setVisible(plantField, false);
      SimbleeForMobile.setVisible(enterPlant, false);
      SimbleeForMobile.setVisible(displayText, true);
      SimbleeForMobile.setVisible(nameOrchid, true);
      SimbleeForMobile.setVisible(otherPlant, true);

    }
    if (userPlant.equals(tulip)) {
      whatPlant = 4;
      SimbleeForMobile.updateText(plantField, "");
      SimbleeForMobile.setVisible(plantField, false);
      SimbleeForMobile.setVisible(enterPlant, false);
      SimbleeForMobile.setVisible(displayText, true);
      SimbleeForMobile.setVisible(nameTulip, true);
      SimbleeForMobile.setVisible(otherPlant, true);
    }
    if (userPlant.equals(fern)) {
      whatPlant = 5;
      SimbleeForMobile.updateText(plantField, "");
      SimbleeForMobile.setVisible(plantField, false);
      SimbleeForMobile.setVisible(enterPlant, false);
      SimbleeForMobile.setVisible(displayText, true);
      SimbleeForMobile.setVisible(nameFern, true);
      SimbleeForMobile.setVisible(otherPlant, true);
    }
    if (userPlant.equals(cactus)) {
      whatPlant = 6;
      SimbleeForMobile.updateText(plantField, "");
      SimbleeForMobile.setVisible(plantField, false);
      SimbleeForMobile.setVisible(enterPlant, false);
      SimbleeForMobile.setVisible(displayText, true);
      SimbleeForMobile.setVisible(nameCactus, true);
      SimbleeForMobile.setVisible(otherPlant, true);
    }
    if (userPlant.equals(ficus)) {
      whatPlant = 7;
      SimbleeForMobile.updateText(plantField, "");
      SimbleeForMobile.setVisible(plantField, false);
      SimbleeForMobile.setVisible(enterPlant, false);
      SimbleeForMobile.setVisible(displayText, true);
      SimbleeForMobile.setVisible(nameFicus, true);
      SimbleeForMobile.setVisible(otherPlant, true);
    }
    if (userPlant != NULL && whatPlant == 0) {
      whatPlant = 1;
      SimbleeForMobile.updateText(plantField, "");
      SimbleeForMobile.setVisible(plantField, false);
      SimbleeForMobile.setVisible(enterPlant, false);
      SimbleeForMobile.setVisible(unrecognizedText, true);
      SimbleeForMobile.setVisible(otherPlant, true);
      SimbleeForMobile.setVisible(contactText, true);
    }
  }

  if (event.id == otherPlant) {
    whatPlant = 0;
    if (SimbleeForMobile.updatable) {
      SimbleeForMobile.setVisible(plantField, true);
      SimbleeForMobile.setVisible(enterPlant, true);
      SimbleeForMobile.setVisible(displayText, false);
      SimbleeForMobile.setVisible(nameAloe, false);
      SimbleeForMobile.setVisible(nameOrchid, false);
      SimbleeForMobile.setVisible(nameTulip, false);
      SimbleeForMobile.setVisible(nameFern, false);
      SimbleeForMobile.setVisible(nameCactus, false);
      SimbleeForMobile.setVisible(nameFicus, false);
      SimbleeForMobile.setVisible(unrecognizedText, false);
      SimbleeForMobile.setVisible(contactText, false);
      SimbleeForMobile.setVisible(otherPlant, false);
    }
  }
}

void showScreenB() {
  screenValue = 2;
  if (SimbleeForMobile.updatable) {
    SimbleeForMobile.setVisible(homeText, true);
    SimbleeForMobile.setVisible(BtoA, true);
    SimbleeForMobile.setVisible(enterPlant, true);
    SimbleeForMobile.setVisible(plantField, true);
    SimbleeForMobile.setVisible(lightText, true);
    SimbleeForMobile.setVisible(tempText, true);
    SimbleeForMobile.setVisible(humText, true);
    SimbleeForMobile.setVisible(CO2Text, true);
    SimbleeForMobile.setVisible(lightVal, true);
    SimbleeForMobile.setVisible(tempVal, true);
    SimbleeForMobile.setVisible(humVal, true);
    SimbleeForMobile.setVisible(CO2Val, true);
    SimbleeForMobile.setVisible(unitLight, true);
    SimbleeForMobile.setVisible(unitTemp, true);
    SimbleeForMobile.setVisible(unitHum, true);
    SimbleeForMobile.setVisible(unitCO2, true);
    SimbleeForMobile.setVisible(iPlant, false);
    SimbleeForMobile.setVisible(forMobile, false);
    SimbleeForMobile.setVisible(loginText, false);
    SimbleeForMobile.setVisible(welcomeMessage, false);
    SimbleeForMobile.setVisible(enterName, false);
    SimbleeForMobile.setVisible(userName, false);
    SimbleeForMobile.setVisible(AtoB, false);
    SimbleeForMobile.setVisible(IMAGE1, false);
  }
}

void showScreenA() {
  screenValue = 1;
  whatPlant = 0;
  if (SimbleeForMobile.updatable) {
    SimbleeForMobile.setVisible(homeText, false);
    SimbleeForMobile.setVisible(BtoA, false);
    SimbleeForMobile.setVisible(enterPlant, false);
    SimbleeForMobile.setVisible(plantField, false);
    SimbleeForMobile.setVisible(lightText, false);
    SimbleeForMobile.setVisible(tempText, false);
    SimbleeForMobile.setVisible(humText, false);
    SimbleeForMobile.setVisible(CO2Text, false);
    SimbleeForMobile.setVisible(lightVal, false);
    SimbleeForMobile.setVisible(tempVal, false);
    SimbleeForMobile.setVisible(humVal, false);
    SimbleeForMobile.setVisible(CO2Val, false);
    SimbleeForMobile.setVisible(unitLight, false);
    SimbleeForMobile.setVisible(unitTemp, false);
    SimbleeForMobile.setVisible(unitHum, false);
    SimbleeForMobile.setVisible(unitCO2, false);
    SimbleeForMobile.setVisible(iPlant, true);
    SimbleeForMobile.setVisible(forMobile, true);
    SimbleeForMobile.setVisible(loginText, true);
    SimbleeForMobile.setVisible(enterName, true);
    SimbleeForMobile.setVisible(userName, true);
    SimbleeForMobile.setVisible(nameAloe, false);
    SimbleeForMobile.setVisible(nameOrchid, false);
    SimbleeForMobile.setVisible(nameFern, false);
    SimbleeForMobile.setVisible(nameCactus, false);
    SimbleeForMobile.setVisible(nameFicus, false);
    SimbleeForMobile.setVisible(nameTulip, false);
    SimbleeForMobile.setVisible(plantField, false);
    SimbleeForMobile.setVisible(displayText, false);
    SimbleeForMobile.setVisible(unrecognizedText, false);
    SimbleeForMobile.setVisible(otherPlant, false);
    SimbleeForMobile.setVisible(keyText, false);
    SimbleeForMobile.setVisible(greenText, false);
    SimbleeForMobile.setVisible(redText, false);
    SimbleeForMobile.setVisible(contactText, false);
    SimbleeForMobile.setVisible(IMAGE1, true);
    SimbleeForMobile.setVisible(IMAGE2, true);
  }
}

void whatHappens0(){
  if (SimbleeForMobile.updatable){
    SimbleeForMobile.setVisible(keyText, false);
    SimbleeForMobile.setVisible(greenText, false);
    SimbleeForMobile.setVisible(redText, false);
    SimbleeForMobile.updateColor(lightVal, BLACK);
    SimbleeForMobile.updateColor(tempVal, BLACK);
    SimbleeForMobile.updateColor(humVal, BLACK);
    SimbleeForMobile.updateColor(CO2Val, BLACK);
  }  
}

void whatHappens1(){
  if (SimbleeForMobile.updatable){
    SimbleeForMobile.setVisible(keyText, false);
    SimbleeForMobile.setVisible(greenText, false);
    SimbleeForMobile.setVisible(redText, false);
    SimbleeForMobile.updateColor(lightVal, BLACK);
    SimbleeForMobile.updateColor(tempVal, BLACK);
    SimbleeForMobile.updateColor(humVal, BLACK);
    SimbleeForMobile.updateColor(CO2Val, BLACK);    
  }  
}

void whatHappens2(){
  if (SimbleeForMobile.updatable){
    SimbleeForMobile.setVisible(keyText, true);
    SimbleeForMobile.setVisible(greenText, true);
    SimbleeForMobile.setVisible(redText, true);

    if (lightCheck <= 5000){
      SimbleeForMobile.updateColor(lightVal, RED);
    }
    else if (lightCheck > 5000){
      SimbleeForMobile.updateColor(lightVal, GREEN);
    }

    if (tempCheck <= 10 || tempCheck >= 40){
      SimbleeForMobile.updateColor(tempVal, RED);
    }
    else if (tempCheck > 10 || tempCheck < 40){
      SimbleeForMobile.updateColor(tempVal, GREEN);
    }

    if (humCheck <= 10 || humCheck >= 70){
      SimbleeForMobile.updateColor(humVal, RED);
    }
    else if (humCheck > 10 || humCheck < 70){
      SimbleeForMobile.updateColor(humVal, GREEN);
    }

    if (CO2Check <= 400 || CO2Check >= 1500){
      SimbleeForMobile.updateColor(CO2Val, RED);
    }
    else if (CO2Check > 400 || CO2Check < 1500){
      SimbleeForMobile.updateColor(CO2Val, GREEN);
    }
  }
}

void whatHappens3(){
  if (SimbleeForMobile.updatable){
    SimbleeForMobile.setVisible(keyText, true);
    SimbleeForMobile.setVisible(greenText, true);
    SimbleeForMobile.setVisible(redText, true);

    if (lightCheck >= 3000){
      SimbleeForMobile.updateColor(lightVal, RED);
    }
    else if (lightCheck < 3000){
      SimbleeForMobile.updateColor(lightVal, GREEN);
    }
    
    if (tempCheck <= 7 || tempCheck >= 30){
      SimbleeForMobile.updateColor(tempVal, RED);
    }
    else if (tempCheck > 7 || tempCheck < 30){
      SimbleeForMobile.updateColor(tempVal, GREEN);
    }

    if (humCheck <= 50 || humCheck >= 70){
      SimbleeForMobile.updateColor(humVal, RED);
    }
    else if (humCheck > 50 || humCheck < 70){
      SimbleeForMobile.updateColor(humVal, GREEN);
    }

    if (CO2Check <= 200 || CO2Check >= 1200){
      SimbleeForMobile.updateColor(CO2Val, RED);
    }
    else if (CO2Check > 200 || CO2Check < 1200){
      SimbleeForMobile.updateColor(CO2Val, GREEN);
    }        
  }  
}

void whatHappens4(){
  if (SimbleeForMobile.updatable){
    SimbleeForMobile.setVisible(keyText, true);
    SimbleeForMobile.setVisible(greenText, true);
    SimbleeForMobile.setVisible(redText, true);

    if (lightCheck <= 5000){
      SimbleeForMobile.updateColor(lightVal, RED);
    }
    else if (lightCheck > 5000){
      SimbleeForMobile.updateColor(lightVal, GREEN);
    }

    if (tempCheck <= 13 || tempCheck >= 18){
      SimbleeForMobile.updateColor(tempVal, RED);
    }
    else if (tempCheck > 13 || tempCheck < 18){
      SimbleeForMobile.updateColor(tempVal, GREEN);
    }

    if (humCheck <= 65 || humCheck >= 90){
      SimbleeForMobile.updateColor(humVal, RED);
    }
    else if (humCheck > 65 || humCheck < 90){
      SimbleeForMobile.updateColor(humVal, GREEN);
    }

    if (CO2Check <= 300 || CO2Check >= 1750){
      SimbleeForMobile.updateColor(CO2Val, RED);
    }
    else if (CO2Check > 300 || CO2Check < 1750){
      SimbleeForMobile.updateColor(CO2Val, GREEN);
    }        
  }  
}

void whatHappens5(){
  if (SimbleeForMobile.updatable){
    SimbleeForMobile.setVisible(keyText, true);
    SimbleeForMobile.setVisible(greenText, true);
    SimbleeForMobile.setVisible(redText, true);

    if (lightCheck >= 3000){
      SimbleeForMobile.updateColor(lightVal, RED);
    }
    else if (lightCheck < 3000){
      SimbleeForMobile.updateColor(lightVal, GREEN);
    }

    if (tempCheck <= 20 || tempCheck >= 27){
      SimbleeForMobile.updateColor(tempVal, RED);
    }
    else if (tempCheck > 20 || tempCheck < 27){
      SimbleeForMobile.updateColor(tempVal, GREEN);
    }

    if (humCheck <= 70 || humCheck >= 90){
      SimbleeForMobile.updateColor(humVal, RED);
    }
    else if (humCheck > 70 || humCheck < 90){
      SimbleeForMobile.updateColor(humVal, GREEN);
    }

    if (CO2Check <= 400 || CO2Check >= 1500){
      SimbleeForMobile.updateColor(CO2Val, RED);
    }
    else if (CO2Check > 400 || CO2Check < 1500){
      SimbleeForMobile.updateColor(CO2Val, GREEN);
    }            
  }  
}

void whatHappens6(){
  if (SimbleeForMobile.updatable){
    SimbleeForMobile.setVisible(keyText, true);
    SimbleeForMobile.setVisible(greenText, true);
    SimbleeForMobile.setVisible(redText, true);

    if (lightCheck <= 5500){
      SimbleeForMobile.updateColor(lightVal, RED);
    }
    else if (lightCheck > 5500){
      SimbleeForMobile.updateColor(lightVal, GREEN);
    }

    if (tempCheck <= 7 || tempCheck >= 30){
      SimbleeForMobile.updateColor(tempVal, RED);
    }
    else if (tempCheck > 7 || tempCheck < 30){
      SimbleeForMobile.updateColor(tempVal, GREEN);
    }

    if (humCheck <= 10 || humCheck >= 60){
      SimbleeForMobile.updateColor(humVal, RED);
    }
    else if (humCheck > 10 || humCheck < 60){
      SimbleeForMobile.updateColor(humVal, GREEN);
    }

    if (CO2Check <= 400 || CO2Check >= 1500){
      SimbleeForMobile.updateColor(CO2Val, RED);
    }
    else if (CO2Check > 400 || CO2Check < 1500){
      SimbleeForMobile.updateColor(CO2Val, GREEN);
    }            
  }  
}

void whatHappens7(){
  if (SimbleeForMobile.updatable){
    SimbleeForMobile.setVisible(keyText, true);
    SimbleeForMobile.setVisible(greenText, true);
    SimbleeForMobile.setVisible(redText, true);

    if (lightCheck >= 3500 || lightCheck <= 2500){
      SimbleeForMobile.updateColor(lightVal, RED);
    }
    else if (lightCheck < 3500 || lightCheck > 2500){
      SimbleeForMobile.updateColor(lightVal, GREEN);
    }

    if (tempCheck <= 21 || tempCheck >= 29){
      SimbleeForMobile.updateColor(tempVal, RED);
    }
    else if (tempCheck > 21 || tempCheck < 29){
      SimbleeForMobile.updateColor(tempVal, GREEN);
    }

    if (humCheck <= 70 || humCheck >= 90){
      SimbleeForMobile.updateColor(humVal, RED);
    }
    else if (humCheck > 70 || humCheck < 90){
      SimbleeForMobile.updateColor(humVal, GREEN);
    }

    if (CO2Check <= 400 || CO2Check >= 1500){
      SimbleeForMobile.updateColor(CO2Val, RED);
    }
    else if (CO2Check > 400 || CO2Check < 1500){
      SimbleeForMobile.updateColor(CO2Val, GREEN);
    }        
  }  
}

void SimbleeCloud_onReceive(unsigned int originESN, const unsigned char *payload, int len){
  if (payload[0] == '2'){
    //Serial.println("TWO RECEIVED!");
    //counter = 0;
  }
}

void SimbleeCOM_onReceive(unsigned int esn, const char* payload, int len, int rssi) {
  //First read Light pointer '1' before storing sensor values into valueA
  if (payload[0] == '1') {
    valueA[0] = payload[1];
    valueA[1] = payload[2];
    valueA[2] = payload[3];
    valueA[3] = payload[4];
    //Serial.print("Light: ");
    //Serial.println(valueA);
    //Serial.println();
  }

  //First read Humidity pointer '3' before storing sensor values into valueC
  else if (payload[0] == '3') {
    valueC[0] = payload[1];
    valueC[1] = payload[2];
    valueC[2] = payload[3];
    valueC[3] = payload[4];
    valueC[4] = payload[5];
    //Serial.print("Humidity: ");
    //Serial.println(valueC);
    //Serial.println();
  }

  //First read ECO2 pointer '4' before storing sensor values into valueD
  if (payload[0] == '4') {
    valueD[0] = payload[1];
    valueD[1] = payload[2];
    valueD[2] = payload[3];
    valueD[3] = payload[4];
    //Serial.print("ECO2: ");
    //Serial.println(valueD);
    //Serial.println();
  }

  //First read Temperature pointer '2' before storing sensor values into valueB
  else if (payload[0] == '2') {
    valueB[0] = payload[1];
    valueB[1] = payload[2];
    valueB[2] = payload[3];
    valueB[3] = payload[4];
    valueB[4] = payload[5];
    //Serial.print("Temperature: ");
    //Serial.println(valueB);
    //Serial.println();
  }
/*
  counter = counter + 1;
  Serial.print("Counter: ");
  Serial.println(counter);
  Serial.println();
  */
}

void SimbleeBLE_onDualModeStart () {
}

void SimbleeBLE_onDualModeEnd () {
}

void SimbleeCloud_onDisconnect(){
  Simblee_systemReset();
}

