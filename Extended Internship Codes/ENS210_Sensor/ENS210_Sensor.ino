#include <SimbleeCOM.h>
#include <Simblee_ENS210.h>

Simblee_ENS210 ENS210;

char payloadA[6];
char payloadB[6];

void setup() {
  Serial.begin(115200);
  delay(100);

  printf("\nRFDigital ENS210 Temperature & Humidity sensor simple example\n\n");
  if (!ENS210.begin()) {
    printf("Failed to intialize Sensor, Halting!\n");
    while (1);
  }

  SimbleeCOM.mode = LOW_LATENCY;
  SimbleeCOM.begin();
}

void loop() {
  float temperature;
  temperature = ENS210.readTemp();

  String stringVal = "";

  stringVal+=String(int(temperature))+ "."+String(getDecimal(temperature));

  char tempVal[stringVal.length()+1];
  stringVal.toCharArray(tempVal,stringVal.length()+1); 

  payloadA[0] = '2';
  payloadA[1] = tempVal[0];
  payloadA[2] = tempVal[1];
  payloadA[3] = tempVal[2];
  payloadA[4] = tempVal[3];
  payloadA[5] = tempVal[4];

  float humidity;
  humidity = ENS210.readHumidity();

  String stringVal2 = "";

  stringVal2+=String(int(humidity))+ "."+String(getDecimal(humidity));

  char humVal[stringVal2.length()+1];
  stringVal2.toCharArray(humVal,stringVal2.length()+1);

  payloadB[0] = '3';
  payloadB[1] = humVal[0];
  payloadB[2] = humVal[1];
  payloadB[3] = humVal[2];
  payloadB[4] = humVal[3];
  payloadB[5] = humVal[4];

  Serial.print("Temperature: ");
  Serial.println(tempVal);
  Serial.println();
  Serial.print("Humidity: ");
  Serial.println(humVal);
  Serial.println();
  SimbleeCOM.send(payloadA, sizeof(payloadA));
  SimbleeCOM.send(payloadB, sizeof(payloadB));
  delay(1000);

}

long getDecimal(float val){
  int intPart = int(val);
  long decPart = 100*(val-intPart);

   if(decPart>0)return(decPart);
   else if(decPart<0)return((-1)*decPart);
   else if(decPart=0)return(00);
}
