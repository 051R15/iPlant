/*
 * Copyright (c) 2015 RF Digital Corp. All Rights Reserved.
 *
 * The source code contained in this file and all intellectual property embodied in
 * or covering the source code is the property of RF Digital Corp. or its licensors.
 * Your right to use this source code and intellectual property is non-transferable,
 * non-sub licensable, revocable, and subject to terms and conditions of the
 * SIMBLEE SOFTWARE LICENSE AGREEMENT.
 * http://www.simblee.com/licenses/SimbleeSoftwareLicenseAgreement.txt
 *
 * THE SOURCE CODE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND.
 *
 * This heading must NOT be removed from this file.
 */
  
#include <SimbleeForMobile.h>
#include <Simblee_ENS210.h>

Simblee_ENS210 ENS210;

asm(".global _printf_float");

uint8_t Back;
uint8_t Rect1, Text1, Text2, But1, But2, But3, But4, But5, But6;
uint8_t Rect11, Rect12, Rect13, Rect14, Text11, Text12, Text13, Text14, apptemp, apphumi;
uint8_t Rect21, Rect23, Text21, Text22, Text23, Text24;
uint8_t Rect31, Rect33, Text31, Text32, Text33, Text34;
uint8_t Rect41, Rect43, Text41, Text42, Text43, Text44;
uint8_t Rect51, Rect53, Text51, Text52, Text53, Text54;
uint8_t Rect61, Rect63, Text61, Text62, Text63, Text64;

color_t darkgreen = rgb(65,139,0);
color_t lightgreen1 = rgb(173,255,47);
color_t lightgreen = rgb(0,190,0);
color_t red11 = rgb(238,64,0);


float temp;
float humi;

int tempswitch;

/*
 * Traditional Arduino setup routine
 * 
 * Initialize the SimbleeForMobile environment.
 */
void setup() {
  // put your setup code here, to run once:
  override_uart_limit = true;

  Serial.begin(115200);

  SimbleeForMobile.deviceName = "iPlant";
  SimbleeForMobile.advertisementData = "Tempra";
  SimbleeForMobile.domain = "template.simblee.com";
  // Begin Simblee UI
  SimbleeForMobile.begin();
  delay(100);
  if (!ENS210.begin()) {
    printf("Failed to intialize Sensor, Halting!\n");
    while (1);
  }
}





/*
 * The traditional Arduino loop method
 * 
 * Enable SimbleeForMobile functionality by calling the process method
 * each time through the loop. This method must be called regularly for
 * functionality to work.
 */
void loop() {
  // put your main code here, to run repeatedly:
  // process must be called in the loop for Simblee UI
  SimbleeForMobile.process();
  

   

  if (SimbleeForMobile.updatable) {
    temp = ENS210.readTemp();
    humi = ENS210.readHumidity();
    SimbleeForMobile.updateValue(apptemp, temp);
    SimbleeForMobile.updateValue(apphumi, humi);
    if (temp >= 10 && temp <= 40) {
      SimbleeForMobile.updateColor(Rect11,  lightgreen);
    } else {
      SimbleeForMobile.updateColor(Rect11, red11);
    }
    if (humi >= 10 && humi <= 70) {
      SimbleeForMobile.updateColor(Rect13,  lightgreen);
    } else {
      SimbleeForMobile.updateColor(Rect13, red11);
    }
    if (temp >= 7 && temp <= 30) {
      SimbleeForMobile.updateColor(Rect21,  lightgreen);
    } else {
      SimbleeForMobile.updateColor(Rect21, red11);
    }
    if (humi >= 50 && humi <=70) {
      SimbleeForMobile.updateColor(Rect23,  lightgreen);
    } else {
      SimbleeForMobile.updateColor(Rect23, red11);
    }
    if (temp >= 13 && temp <= 18) {
      SimbleeForMobile.updateColor(Rect31,  lightgreen);
    } else {
      SimbleeForMobile.updateColor(Rect31, red11);
    }
    if (humi >= 65 && humi <= 90) {
      SimbleeForMobile.updateColor(Rect33,  lightgreen);
    } else {
      SimbleeForMobile.updateColor(Rect33, red11);
    }
    if (temp >= 20 && temp <=27) {
      SimbleeForMobile.updateColor(Rect41,  lightgreen);
    } else {
      SimbleeForMobile.updateColor(Rect41, red11);
    }
    if (humi >= 70 && humi <= 90) {
      SimbleeForMobile.updateColor(Rect43,  lightgreen);
    } else {
      SimbleeForMobile.updateColor(Rect43, red11);
    }
    if (temp >= 7 && temp <=30) {
      SimbleeForMobile.updateColor(Rect51,  lightgreen);
    } else {
      SimbleeForMobile.updateColor(Rect51, red11);
    }
    if (humi >= 10 && humi <=60) {
      SimbleeForMobile.updateColor(Rect53,  lightgreen);
    } else {
      SimbleeForMobile.updateColor(Rect53, red11);
    }
    if (temp >= 21 && temp <=29) {
      SimbleeForMobile.updateColor(Rect61,  lightgreen);
    } else {
      SimbleeForMobile.updateColor(Rect61, red11);
    }
    if (humi >= 70 && humi <=90) {
      SimbleeForMobile.updateColor(Rect63,  lightgreen);
    } else {
      SimbleeForMobile.updateColor(Rect63, red11);
    }
  }
  

      
}





/*
 * SimbleeForMobile UI callback requesting the user interface
 */
void ui()
{  
  SimbleeForMobile.beginScreen();
  
  

  Rect11 = SimbleeForMobile.drawRect(0, 0, 350,  284,   lightgreen);
  Rect13 = SimbleeForMobile.drawRect(0, 284, 350,  284,   lightgreen);
  Text11 = SimbleeForMobile.drawText(10, 50, "Optimal Temprature Range: 10""\xb0""C-40""\xb0""C", BLACK, 20);
  Text12 = SimbleeForMobile.drawText(20, 120, "Temprature:     ""\xb0""C", BLACK, 40);
  Text13 = SimbleeForMobile.drawText(20, (334), "Optimal Humidity Range: 10%-70%", BLACK, 20);
  Text14 = SimbleeForMobile.drawText(50, (404), "Humidity:     %", BLACK, 40);
  SimbleeForMobile.setVisible(Back, false);
  SimbleeForMobile.setVisible(Rect11, false);
  SimbleeForMobile.setVisible(Rect13, false);
  SimbleeForMobile.setVisible(Text11, false);
  SimbleeForMobile.setVisible(Text12, false);
  SimbleeForMobile.setVisible(apptemp, false);
  SimbleeForMobile.setVisible(Text13, false);
  SimbleeForMobile.setVisible(Text14, false);
  SimbleeForMobile.setVisible(apphumi, false);

  Rect21 = SimbleeForMobile.drawRect(0, 0, 350,  284,   lightgreen);
  Rect23 = SimbleeForMobile.drawRect(0, 284, 350,  284,   lightgreen);
  Text21 = SimbleeForMobile.drawText(10, 50, "Optimal Temprature Range: 7""\xb0""C-30""\xb0""C", BLACK, 20);
  Text22 = SimbleeForMobile.drawText(20, 120, "Temprature:     ""\xb0""C", BLACK, 40);
  Text23 = SimbleeForMobile.drawText(20, (334), "Optimal Humidity Range: 50%-70%", BLACK, 20);
  Text24 = SimbleeForMobile.drawText(50, (404), "Humidity:     %", BLACK, 40);
  SimbleeForMobile.setVisible(Rect21, false);
  SimbleeForMobile.setVisible(Rect23, false);
  SimbleeForMobile.setVisible(Text21, false);
  SimbleeForMobile.setVisible(Text22, false);
  SimbleeForMobile.setVisible(Text23, false);
  SimbleeForMobile.setVisible(Text24, false);

  Rect31 = SimbleeForMobile.drawRect(0, 0, 350,  284,   lightgreen);
  Rect33 = SimbleeForMobile.drawRect(0, 284, 350,  284,   lightgreen);
  Text31 = SimbleeForMobile.drawText(10, 50, "Optimal Temprature Range: 13""\xb0""C-18""\xb0""C", BLACK, 20);
  Text32 = SimbleeForMobile.drawText(20, 120, "Temprature:     ""\xb0""C", BLACK, 40);
  Text33 = SimbleeForMobile.drawText(20, (334), "Optimal Humidity Range: 65%-90%", BLACK, 20);
  Text34 = SimbleeForMobile.drawText(50, (404), "Humidity:     %", BLACK, 40);
  SimbleeForMobile.setVisible(Rect31, false);
  SimbleeForMobile.setVisible(Rect33, false);
  SimbleeForMobile.setVisible(Text31, false);
  SimbleeForMobile.setVisible(Text32, false);
  SimbleeForMobile.setVisible(Text33, false);
  SimbleeForMobile.setVisible(Text34, false);

  Rect41 = SimbleeForMobile.drawRect(0, 0, 350,  284,   lightgreen);
  Rect43 = SimbleeForMobile.drawRect(0, 284, 350,  284,   lightgreen);
  Text41 = SimbleeForMobile.drawText(10, 50, "Optimal Temprature Range: 20""\xb0""C-27""\xb0""C", BLACK, 20);
  Text42 = SimbleeForMobile.drawText(20, 120, "Temprature:     ""\xb0""C", BLACK, 40);
  Text43 = SimbleeForMobile.drawText(20, (334), "Optimal Humidity Range: 70%-90%", BLACK, 20);
  Text44 = SimbleeForMobile.drawText(50, (404), "Humidity:     %", BLACK, 40);
  SimbleeForMobile.setVisible(Rect41, false);
  SimbleeForMobile.setVisible(Rect43, false);
  SimbleeForMobile.setVisible(Text41, false);
  SimbleeForMobile.setVisible(Text42, false);
  SimbleeForMobile.setVisible(Text43, false);
  SimbleeForMobile.setVisible(Text44, false);

  Rect51 = SimbleeForMobile.drawRect(0, 0, 350,  284,   lightgreen);
  Rect53 = SimbleeForMobile.drawRect(0, 284, 350,  284,   lightgreen);
  Text51 = SimbleeForMobile.drawText(10, 50, "Optimal Temprature Range: 7""\xb0""C-30""\xb0""C", BLACK, 20);
  Text52 = SimbleeForMobile.drawText(20, 120, "Temprature:     ""\xb0""C", BLACK, 40);
  Text53 = SimbleeForMobile.drawText(20, (334), "Optimal Humidity Range: 10%-60%", BLACK, 20);
  Text54 = SimbleeForMobile.drawText(50, (404), "Humidity:     %", BLACK, 40);
  SimbleeForMobile.setVisible(Rect51, false);
  SimbleeForMobile.setVisible(Rect53, false);
  SimbleeForMobile.setVisible(Text51, false);
  SimbleeForMobile.setVisible(Text52, false);
  SimbleeForMobile.setVisible(Text53, false);
  SimbleeForMobile.setVisible(Text54, false);

  Rect61 = SimbleeForMobile.drawRect(0, 0, 350,  284,   lightgreen);
  Rect63 = SimbleeForMobile.drawRect(0, 284, 350,  284,   lightgreen);
  Text61 = SimbleeForMobile.drawText(10, 50, "Optimal Temprature Range: 21""\xb0""C-29""\xb0""C", BLACK, 20);
  Text62 = SimbleeForMobile.drawText(20, 120, "Temprature:     ""\xb0""C", BLACK, 40);
  Text63 = SimbleeForMobile.drawText(20, (334), "Optimal Humidity Range: 70%-90%", BLACK, 20);
  Text64 = SimbleeForMobile.drawText(50, (404), "Humidity:     %", BLACK, 40);
  SimbleeForMobile.setVisible(Rect61, false);
  SimbleeForMobile.setVisible(Rect63, false);
  SimbleeForMobile.setVisible(Text61, false);
  SimbleeForMobile.setVisible(Text62, false);
  SimbleeForMobile.setVisible(Text63, false);
  SimbleeForMobile.setVisible(Text64, false);

  apphumi = SimbleeForMobile.drawText(210, (404), "", BLACK, 40);
  Back = SimbleeForMobile.drawButton(110, 240, 100, "Back", BLACK, BOX_TYPE);
  apptemp = SimbleeForMobile.drawText(215, 120, "", BLACK, 40);

  Rect1 = SimbleeForMobile.drawRect(0, 0, 350,  575,  darkgreen);
  Text1 = SimbleeForMobile.drawText(10, 80, "iPlant Temprature \n" "and Humidity",  lightgreen1, 40);
  Text2 = SimbleeForMobile.drawText(10, 250, "Select Plant:",  lightgreen1, 30);
  But1 = SimbleeForMobile.drawButton(10, 285, 150, "Aloe Vera",  lightgreen1, BOX_TYPE);
  But2 = SimbleeForMobile.drawButton(162, 285, 150, "Orchid",  lightgreen1, BOX_TYPE);
  But3 = SimbleeForMobile.drawButton(10, 325, 150, "Tulip",  lightgreen1, BOX_TYPE);
  But4 = SimbleeForMobile.drawButton(162, 325, 150, "Fern",  lightgreen1, BOX_TYPE);
  But5 = SimbleeForMobile.drawButton(10, 365, 150, "Cactus",  lightgreen1, BOX_TYPE);
  But6 = SimbleeForMobile.drawButton(162, 365, 150, "Ficus",  lightgreen1, BOX_TYPE);



  




  

  
  
  
  SimbleeForMobile.endScreen();
}





/*
 * SimbleeForMobile event callback method
 */
void ui_event(event_t &event)
{
  if (event.id == Back)
  {
    if (SimbleeForMobile.updatable)
    {     
      SimbleeForMobile.setVisible(Rect1, true);
      SimbleeForMobile.setVisible(But1, true);
      SimbleeForMobile.setVisible(Text1, true);
      SimbleeForMobile.setVisible(Text2, true);
      SimbleeForMobile.setVisible(But2, true);
      SimbleeForMobile.setVisible(But3, true);
      SimbleeForMobile.setVisible(But4, true);
      SimbleeForMobile.setVisible(But5, true);
      SimbleeForMobile.setVisible(But6, true);
      SimbleeForMobile.setVisible(Back, false);
      SimbleeForMobile.setVisible(Rect11, false);
      SimbleeForMobile.setVisible(Rect13, false);
      SimbleeForMobile.setVisible(Text11, false);
      SimbleeForMobile.setVisible(Text12, false);
      SimbleeForMobile.setVisible(apptemp, false);
      SimbleeForMobile.setVisible(Text13, false);
      SimbleeForMobile.setVisible(Text14, false);
      SimbleeForMobile.setVisible(apphumi, false);
      SimbleeForMobile.setVisible(Rect21, false);
  SimbleeForMobile.setVisible(Rect23, false);
  SimbleeForMobile.setVisible(Text21, false);
  SimbleeForMobile.setVisible(Text22, false);
  SimbleeForMobile.setVisible(Text23, false);
  SimbleeForMobile.setVisible(Text24, false);
      SimbleeForMobile.setVisible(Rect31, false);
  SimbleeForMobile.setVisible(Rect33, false);
  SimbleeForMobile.setVisible(Text31, false);
  SimbleeForMobile.setVisible(Text32, false);
  SimbleeForMobile.setVisible(Text33, false);
  SimbleeForMobile.setVisible(Text34, false);
  SimbleeForMobile.setVisible(Rect41, false);
  SimbleeForMobile.setVisible(Rect43, false);
  SimbleeForMobile.setVisible(Text41, false);
  SimbleeForMobile.setVisible(Text42, false);
  SimbleeForMobile.setVisible(Text43, false);
  SimbleeForMobile.setVisible(Text44, false);
  SimbleeForMobile.setVisible(Rect51, false);
  SimbleeForMobile.setVisible(Rect53, false);
  SimbleeForMobile.setVisible(Text51, false);
  SimbleeForMobile.setVisible(Text52, false);
  SimbleeForMobile.setVisible(Text53, false);
  SimbleeForMobile.setVisible(Text54, false);
  SimbleeForMobile.setVisible(Rect61, false);
  SimbleeForMobile.setVisible(Rect63, false);
  SimbleeForMobile.setVisible(Text61, false);
  SimbleeForMobile.setVisible(Text62, false);
  SimbleeForMobile.setVisible(Text63, false);
  SimbleeForMobile.setVisible(Text64, false);
    }
  }
    if (event.id == But1)
  {
    if (SimbleeForMobile.updatable)
    {     
      SimbleeForMobile.setVisible(Rect1, false);
      SimbleeForMobile.setVisible(But1, false);
      SimbleeForMobile.setVisible(Text1, false);
      SimbleeForMobile.setVisible(Text2, false);
      SimbleeForMobile.setVisible(But2, false);
      SimbleeForMobile.setVisible(But3, false);
      SimbleeForMobile.setVisible(But4, false);
      SimbleeForMobile.setVisible(But5, false);
      SimbleeForMobile.setVisible(But6, false);
      SimbleeForMobile.setVisible(Back, true);
      SimbleeForMobile.setVisible(Rect11, true);
      SimbleeForMobile.setVisible(Rect13, true);
      SimbleeForMobile.setVisible(Text11, true);
      SimbleeForMobile.setVisible(Text12, true);
      SimbleeForMobile.setVisible(apptemp, true);
      SimbleeForMobile.setVisible(Text13, true);
      SimbleeForMobile.setVisible(Text14, true);
      SimbleeForMobile.setVisible(apphumi, true);
      SimbleeForMobile.setVisible(Rect21, false);
  SimbleeForMobile.setVisible(Rect23, false);
  SimbleeForMobile.setVisible(Text21, false);
  SimbleeForMobile.setVisible(Text22, false);
  SimbleeForMobile.setVisible(Text23, false);
  SimbleeForMobile.setVisible(Text24, false);
      SimbleeForMobile.setVisible(Rect31, false);
  SimbleeForMobile.setVisible(Rect33, false);
  SimbleeForMobile.setVisible(Text31, false);
  SimbleeForMobile.setVisible(Text32, false);
  SimbleeForMobile.setVisible(Text33, false);
  SimbleeForMobile.setVisible(Text34, false);
  SimbleeForMobile.setVisible(Rect41, false);
  SimbleeForMobile.setVisible(Rect43, false);
  SimbleeForMobile.setVisible(Text41, false);
  SimbleeForMobile.setVisible(Text42, false);
  SimbleeForMobile.setVisible(Text43, false);
  SimbleeForMobile.setVisible(Text44, false);
  SimbleeForMobile.setVisible(Rect51, false);
  SimbleeForMobile.setVisible(Rect53, false);
  SimbleeForMobile.setVisible(Text51, false);
  SimbleeForMobile.setVisible(Text52, false);
  SimbleeForMobile.setVisible(Text53, false);
  SimbleeForMobile.setVisible(Text54, false);
  SimbleeForMobile.setVisible(Rect61, false);
  SimbleeForMobile.setVisible(Rect63, false);
  SimbleeForMobile.setVisible(Text61, false);
  SimbleeForMobile.setVisible(Text62, false);
  SimbleeForMobile.setVisible(Text63, false);
  SimbleeForMobile.setVisible(Text64, false);
    }
  }
    if (event.id == But2)
  {
    if (SimbleeForMobile.updatable)
    {     
      SimbleeForMobile.setVisible(Rect1, false);
      SimbleeForMobile.setVisible(But1, false);
      SimbleeForMobile.setVisible(Text1, false);
      SimbleeForMobile.setVisible(Text2, false);
      SimbleeForMobile.setVisible(But2, false);
      SimbleeForMobile.setVisible(But3, false);
      SimbleeForMobile.setVisible(But4, false);
      SimbleeForMobile.setVisible(But5, false);
      SimbleeForMobile.setVisible(But6, false);
      SimbleeForMobile.setVisible(Back, true);
      SimbleeForMobile.setVisible(Rect11, false);
      SimbleeForMobile.setVisible(Rect13, false);
      SimbleeForMobile.setVisible(Text11, false);
      SimbleeForMobile.setVisible(Text12, false);
      SimbleeForMobile.setVisible(apptemp, true);
      SimbleeForMobile.setVisible(Text13, false);
      SimbleeForMobile.setVisible(Text14, false);
      SimbleeForMobile.setVisible(apphumi, true);
      SimbleeForMobile.setVisible(Rect21, true);
  SimbleeForMobile.setVisible(Rect23, true);
  SimbleeForMobile.setVisible(Text21, true);
  SimbleeForMobile.setVisible(Text22, true);
  SimbleeForMobile.setVisible(Text23, true);
  SimbleeForMobile.setVisible(Text24, true);
      SimbleeForMobile.setVisible(Rect31, false);
  SimbleeForMobile.setVisible(Rect33, false);
  SimbleeForMobile.setVisible(Text31, false);
  SimbleeForMobile.setVisible(Text32, false);
  SimbleeForMobile.setVisible(Text33, false);
  SimbleeForMobile.setVisible(Text34, false);
  SimbleeForMobile.setVisible(Rect41, false);
  SimbleeForMobile.setVisible(Rect43, false);
  SimbleeForMobile.setVisible(Text41, false);
  SimbleeForMobile.setVisible(Text42, false);
  SimbleeForMobile.setVisible(Text43, false);
  SimbleeForMobile.setVisible(Text44, false);
  SimbleeForMobile.setVisible(Rect51, false);
  SimbleeForMobile.setVisible(Rect53, false);
  SimbleeForMobile.setVisible(Text51, false);
  SimbleeForMobile.setVisible(Text52, false);
  SimbleeForMobile.setVisible(Text53, false);
  SimbleeForMobile.setVisible(Text54, false);
  SimbleeForMobile.setVisible(Rect61, false);
  SimbleeForMobile.setVisible(Rect63, false);
  SimbleeForMobile.setVisible(Text61, false);
  SimbleeForMobile.setVisible(Text62, false);
  SimbleeForMobile.setVisible(Text63, false);
  SimbleeForMobile.setVisible(Text64, false);
    }
  }
    if (event.id == But3)
  {
    if (SimbleeForMobile.updatable)
    {     
      SimbleeForMobile.setVisible(Rect1, false);
      SimbleeForMobile.setVisible(But1, false);
      SimbleeForMobile.setVisible(Text1, false);
      SimbleeForMobile.setVisible(Text2, false);
      SimbleeForMobile.setVisible(But2, false);
      SimbleeForMobile.setVisible(But3, false);
      SimbleeForMobile.setVisible(But4, false);
      SimbleeForMobile.setVisible(But5, false);
      SimbleeForMobile.setVisible(But6, false);
      SimbleeForMobile.setVisible(Back, true);
      SimbleeForMobile.setVisible(Rect11, false);
      SimbleeForMobile.setVisible(Rect13, false);
      SimbleeForMobile.setVisible(Text11, false);
      SimbleeForMobile.setVisible(Text12, false);
      SimbleeForMobile.setVisible(apptemp, true);
      SimbleeForMobile.setVisible(Text13, false);
      SimbleeForMobile.setVisible(Text14, false);
      SimbleeForMobile.setVisible(apphumi, true);
      SimbleeForMobile.setVisible(Rect21, false);
  SimbleeForMobile.setVisible(Rect23, false);
  SimbleeForMobile.setVisible(Text21, false);
  SimbleeForMobile.setVisible(Text22, false);
  SimbleeForMobile.setVisible(Text23, false);
  SimbleeForMobile.setVisible(Text24, false);
      SimbleeForMobile.setVisible(Rect31, true);
  SimbleeForMobile.setVisible(Rect33, true);
  SimbleeForMobile.setVisible(Text31, true);
  SimbleeForMobile.setVisible(Text32, true);
  SimbleeForMobile.setVisible(Text33, true);
  SimbleeForMobile.setVisible(Text34, true);
  SimbleeForMobile.setVisible(Rect41, false);
  SimbleeForMobile.setVisible(Rect43, false);
  SimbleeForMobile.setVisible(Text41, false);
  SimbleeForMobile.setVisible(Text42, false);
  SimbleeForMobile.setVisible(Text43, false);
  SimbleeForMobile.setVisible(Text44, false);
  SimbleeForMobile.setVisible(Rect51, false);
  SimbleeForMobile.setVisible(Rect53, false);
  SimbleeForMobile.setVisible(Text51, false);
  SimbleeForMobile.setVisible(Text52, false);
  SimbleeForMobile.setVisible(Text53, false);
  SimbleeForMobile.setVisible(Text54, false);
  SimbleeForMobile.setVisible(Rect61, false);
  SimbleeForMobile.setVisible(Rect63, false);
  SimbleeForMobile.setVisible(Text61, false);
  SimbleeForMobile.setVisible(Text62, false);
  SimbleeForMobile.setVisible(Text63, false);
  SimbleeForMobile.setVisible(Text64, false);
    }
  }
    if (event.id == But4)
  {
    if (SimbleeForMobile.updatable)
    {     
      SimbleeForMobile.setVisible(Rect1, false);
      SimbleeForMobile.setVisible(But1, false);
      SimbleeForMobile.setVisible(Text1, false);
      SimbleeForMobile.setVisible(Text2, false);
      SimbleeForMobile.setVisible(But2, false);
      SimbleeForMobile.setVisible(But3, false);
      SimbleeForMobile.setVisible(But4, false);
      SimbleeForMobile.setVisible(But5, false);
      SimbleeForMobile.setVisible(But6, false);
      SimbleeForMobile.setVisible(Back, true);
      SimbleeForMobile.setVisible(Rect11, false);
      SimbleeForMobile.setVisible(Rect13, false);
      SimbleeForMobile.setVisible(Text11, false);
      SimbleeForMobile.setVisible(Text12, false);
      SimbleeForMobile.setVisible(apptemp, true);
      SimbleeForMobile.setVisible(Text13, false);
      SimbleeForMobile.setVisible(Text14, false);
      SimbleeForMobile.setVisible(apphumi, true);
      SimbleeForMobile.setVisible(Rect21, false);
  SimbleeForMobile.setVisible(Rect23, false);
  SimbleeForMobile.setVisible(Text21, false);
  SimbleeForMobile.setVisible(Text22, false);
  SimbleeForMobile.setVisible(Text23, false);
  SimbleeForMobile.setVisible(Text24, false);
      SimbleeForMobile.setVisible(Rect31, false);
  SimbleeForMobile.setVisible(Rect33, false);
  SimbleeForMobile.setVisible(Text31, false);
  SimbleeForMobile.setVisible(Text32, false);
  SimbleeForMobile.setVisible(Text33, false);
  SimbleeForMobile.setVisible(Text34, false);
  SimbleeForMobile.setVisible(Rect41, true);
  SimbleeForMobile.setVisible(Rect43, true);
  SimbleeForMobile.setVisible(Text41, true);
  SimbleeForMobile.setVisible(Text42, true);
  SimbleeForMobile.setVisible(Text43, true);
  SimbleeForMobile.setVisible(Text44, true);
  SimbleeForMobile.setVisible(Rect51, false);
  SimbleeForMobile.setVisible(Rect53, false);
  SimbleeForMobile.setVisible(Text51, false);
  SimbleeForMobile.setVisible(Text52, false);
  SimbleeForMobile.setVisible(Text53, false);
  SimbleeForMobile.setVisible(Text54, false);
  SimbleeForMobile.setVisible(Rect61, false);
  SimbleeForMobile.setVisible(Rect63, false);
  SimbleeForMobile.setVisible(Text61, false);
  SimbleeForMobile.setVisible(Text62, false);
  SimbleeForMobile.setVisible(Text63, false);
  SimbleeForMobile.setVisible(Text64, false);
    }
  }
    if (event.id == But5)
  {
    if (SimbleeForMobile.updatable)
    {     
      SimbleeForMobile.setVisible(Rect1, false);
      SimbleeForMobile.setVisible(But1, false);
      SimbleeForMobile.setVisible(Text1, false);
      SimbleeForMobile.setVisible(Text2, false);
      SimbleeForMobile.setVisible(But2, false);
      SimbleeForMobile.setVisible(But3, false);
      SimbleeForMobile.setVisible(But4, false);
      SimbleeForMobile.setVisible(But5, false);
      SimbleeForMobile.setVisible(But6, false);
      SimbleeForMobile.setVisible(Back, true);
      SimbleeForMobile.setVisible(Rect11, false);
      SimbleeForMobile.setVisible(Rect13, false);
      SimbleeForMobile.setVisible(Text11, false);
      SimbleeForMobile.setVisible(Text12, false);
      SimbleeForMobile.setVisible(apptemp, true);
      SimbleeForMobile.setVisible(Text13, false);
      SimbleeForMobile.setVisible(Text14, false);
      SimbleeForMobile.setVisible(apphumi, true);
      SimbleeForMobile.setVisible(Rect21, false);
  SimbleeForMobile.setVisible(Rect23, false);
  SimbleeForMobile.setVisible(Text21, false);
  SimbleeForMobile.setVisible(Text22, false);
  SimbleeForMobile.setVisible(Text23, false);
  SimbleeForMobile.setVisible(Text24, false);
      SimbleeForMobile.setVisible(Rect31, false);
  SimbleeForMobile.setVisible(Rect33, false);
  SimbleeForMobile.setVisible(Text31, false);
  SimbleeForMobile.setVisible(Text32, false);
  SimbleeForMobile.setVisible(Text33, false);
  SimbleeForMobile.setVisible(Text34, false);
  SimbleeForMobile.setVisible(Rect41, false);
  SimbleeForMobile.setVisible(Rect43, false);
  SimbleeForMobile.setVisible(Text41, false);
  SimbleeForMobile.setVisible(Text42, false);
  SimbleeForMobile.setVisible(Text43, false);
  SimbleeForMobile.setVisible(Text44, false);
  SimbleeForMobile.setVisible(Rect51, true);
  SimbleeForMobile.setVisible(Rect53, true);
  SimbleeForMobile.setVisible(Text51, true);
  SimbleeForMobile.setVisible(Text52, true);
  SimbleeForMobile.setVisible(Text53, true);
  SimbleeForMobile.setVisible(Text54, true);
  SimbleeForMobile.setVisible(Rect61, false);
  SimbleeForMobile.setVisible(Rect63, false);
  SimbleeForMobile.setVisible(Text61, false);
  SimbleeForMobile.setVisible(Text62, false);
  SimbleeForMobile.setVisible(Text63, false);
  SimbleeForMobile.setVisible(Text64, false);
    }
  }
    if (event.id == But6)
  {
    if (SimbleeForMobile.updatable)
    {     
      SimbleeForMobile.setVisible(Rect1, false);
      SimbleeForMobile.setVisible(But1, false);
      SimbleeForMobile.setVisible(Text1, false);
      SimbleeForMobile.setVisible(Text2, false);
      SimbleeForMobile.setVisible(But2, false);
      SimbleeForMobile.setVisible(But3, false);
      SimbleeForMobile.setVisible(But4, false);
      SimbleeForMobile.setVisible(But5, false);
      SimbleeForMobile.setVisible(But6, false);
      SimbleeForMobile.setVisible(Back, true);
      SimbleeForMobile.setVisible(Rect11, false);
      SimbleeForMobile.setVisible(Rect13, false);
      SimbleeForMobile.setVisible(Text11, false);
      SimbleeForMobile.setVisible(Text12, false);
      SimbleeForMobile.setVisible(apptemp, true);
      SimbleeForMobile.setVisible(Text13, false);
      SimbleeForMobile.setVisible(Text14, false);
      SimbleeForMobile.setVisible(apphumi, true);
      SimbleeForMobile.setVisible(Rect21, false);
  SimbleeForMobile.setVisible(Rect23, false);
  SimbleeForMobile.setVisible(Text21, false);
  SimbleeForMobile.setVisible(Text22, false);
  SimbleeForMobile.setVisible(Text23, false);
  SimbleeForMobile.setVisible(Text24, false);
      SimbleeForMobile.setVisible(Rect31, false);
  SimbleeForMobile.setVisible(Rect33, false);
  SimbleeForMobile.setVisible(Text31, false);
  SimbleeForMobile.setVisible(Text32, false);
  SimbleeForMobile.setVisible(Text33, false);
  SimbleeForMobile.setVisible(Text34, false);
  SimbleeForMobile.setVisible(Rect41, false);
  SimbleeForMobile.setVisible(Rect43, false);
  SimbleeForMobile.setVisible(Text41, false);
  SimbleeForMobile.setVisible(Text42, false);
  SimbleeForMobile.setVisible(Text43, false);
  SimbleeForMobile.setVisible(Text44, false);
  SimbleeForMobile.setVisible(Rect51, false);
  SimbleeForMobile.setVisible(Rect53, false);
  SimbleeForMobile.setVisible(Text51, false);
  SimbleeForMobile.setVisible(Text52, false);
  SimbleeForMobile.setVisible(Text53, false);
  SimbleeForMobile.setVisible(Text54, false);
  SimbleeForMobile.setVisible(Rect61, true);
  SimbleeForMobile.setVisible(Rect63, true);
  SimbleeForMobile.setVisible(Text61, true);
  SimbleeForMobile.setVisible(Text62, true);
  SimbleeForMobile.setVisible(Text63, true);
  SimbleeForMobile.setVisible(Text64, true);
    }
  }
}
