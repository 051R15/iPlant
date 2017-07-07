#include <SimbleeCOM.h>
#include <Simblee_TMG4903.h>

Simblee_TMG4903 TMG4903; 

char payload[5];

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

  payload[0] = '2';
  payload[1] = clearVal[0];
  payload[2] = clearVal[1];
  payload[3] = clearVal[2];
  payload[4] = clearVal[3];

  Serial.print("Clear Value: ");
  Serial.println(clearVal);
  Serial.println();
  SimbleeCOM.send(payload, sizeof(payload));
  delay(1000);
}
