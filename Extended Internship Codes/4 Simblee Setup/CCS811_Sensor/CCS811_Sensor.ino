#include <SimbleeCOM.h>
#include <Simblee_CCS811.h>

Simblee_CCS811 CCS811; 

char payload[5];

long initialTime = 0;
long resetTime = 300000;

void setup() {
  Serial.begin(115200);
  delay(100);
  
  printf("\nRFDigital TMG4903 sensor initialized\n\n");
  if (!CCS811.begin()) {
    printf("Failed to intialize Sensor, Halting!\n");
    while (1);
  }
  
  SimbleeCOM.mode = LOW_LATENCY;
  SimbleeCOM.begin();
}

void loop() {

  unsigned long currentMillis = millis();
  
  if (currentMillis - initialTime > resetTime){
    initialTime = currentMillis;
    Serial.println("Simblee System Reset!");
    Simblee_systemReset();
  }

  float ECO2;
  ECO2 = CCS811.readECO2();

  String stringVal = "";

  stringVal+=String(int(ECO2));

  char ECO2Val[stringVal.length()+1];
  stringVal.toCharArray(ECO2Val,stringVal.length()+1);

  payload[0] = '4';
  payload[1] = ECO2Val[0];
  payload[2] = ECO2Val[1];
  payload[3] = ECO2Val[2];
  payload[4] = ECO2Val[3];

  Serial.print("ECO2 Value: ");
  Serial.println(ECO2Val);
  Serial.println();
  SimbleeCOM.send(payload, sizeof(payload));
  delay(500);
}

void SimbleeCOM_onReceive(unsigned int esn, const char *payload, int len, int rssi){
}

