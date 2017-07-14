#include <SimbleeCOM.h>
#include <Simblee_TMG4903.h>

Simblee_TMG4903 TMG4903;

char payloadA[5];

void setup() {
  Serial.begin(115200);
  delay(100);
  
  printf("\nRFDigital TMG4903 sensor initialized\n\n");
  if (!TMG4903.begin()) {
    printf("Failed to intialize Sensor, Halting!\n");
    while (1);
  }

  SimbleeCOM.mode = LOW_LATENCY;
  SimbleeCOM.begin();
}

void loop() {
  float clearLight;
  clearLight = TMG4903.readClear();

  String stringVal = "";

  stringVal+=String(int(clearLight));

  char clearVal[stringVal.length()+1];
  stringVal.toCharArray(clearVal,stringVal.length()+1); 

  payloadA[0] = '1';
  payloadA[1] = clearVal[0];
  payloadA[2] = clearVal[1];
  payloadA[3] = clearVal[2];
  payloadA[4] = clearVal[3];

  Serial.print("Clear Value: ");
  Serial.println(clearVal);
  Serial.println();
  SimbleeCOM.send(payloadA, sizeof(payloadA));
  delay(100);
}

void SimbleeCOM_onReceive(unsigned int esn, const char *payload, int len, int rssi){
}

