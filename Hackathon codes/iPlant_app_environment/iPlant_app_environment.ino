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
#include <Simblee_CCS811.h>


Simblee_CCS811 CCS811;

#define ams_GRAY rgb(135,135,135)
#define SimbleeBlue rgb(55,122,177)

uint8_t CO2Val_ui, HumidVal_ui;
uint8_t mercury;
uint8_t myRec, myRec2, myiPlant, myEnvMon;
uint8_t myPlant1, myPlant2, myPlant3, myPlant4, myPlant5, myPlant6;
uint8_t CO2Text, ppmText, VOCText, ppbText, clickText;
uint8_t rangeRec, rangeText, rangeText2;
uint8_t aloeVera, Fern, Orchid, Cactus, Tulip, Ficus;

unsigned long lastUpdated = 0;
unsigned long updateRate = 100; // half a second

asm(".global _printf_float");

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  delay(100);

  if (!CCS811.begin()) {
    printf("Failed to intialize Sensor, Halting!\n");
    while (1);
  }

  SimbleeForMobile.deviceName = "iPlant";
  SimbleeForMobile.advertisementData = "CO2 levels";
  SimbleeForMobile.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  // process must be called in the loop for Simblee UI
 
   // put your main code here, to run repeatedly:
  uint16_t eCO2;
  uint16_t TVOC;
  unsigned long loopTime = millis();

  TVOC = CCS811.readTVOC();
  eCO2 = CCS811.readECO2();
  printf("CCS811 CO2: %dppm\tTVOC: %dppb\n", eCO2, TVOC);
  delay(1000);

   if (SimbleeForMobile.updatable && updateRate < (loopTime - lastUpdated))
  {
    lastUpdated = loopTime;
 
    SimbleeForMobile.updateValue(CO2Val_ui, eCO2);
    SimbleeForMobile.updateValue(HumidVal_ui, TVOC);

    // find a way to set updated values as variable so can be set visible and invisible
  }

  // process must be called in the loop for SimbleeForMobile
  

  if (SimbleeForMobile.updatable){
   
    if (eCO2 >= 2000 || eCO2 <= 200) {
     SimbleeForMobile.updateColor(myRec2, RED);
     SimbleeForMobile.updateText(clickText, "Environment is out of ideal range");
     SimbleeForMobile.updateText(clickText, "Appropriate measures being taken.");
    }
     
    else{
     SimbleeForMobile.updateColor(myRec2, GREEN);
     SimbleeForMobile.updateText(clickText, "Environment is in ideal range");
     SimbleeForMobile.updateText(clickText, "");
    }
  }
  
  SimbleeForMobile.process();
  }

void ui() {
    
  SimbleeForMobile.beginScreen();

  myRec = SimbleeForMobile.drawRect(0, 0, SimbleeForMobile.screenWidth,  SimbleeForMobile.screenHeight, WHITE);
  myRec2 = SimbleeForMobile.drawRect(0, 0, SimbleeForMobile.screenWidth,  SimbleeForMobile.screenHeight, GREEN);
  SimbleeForMobile.setVisible(myRec2,false);
  myiPlant = SimbleeForMobile.drawText(120, 150, "iPlant", GREEN, 40);
  myEnvMon = SimbleeForMobile.drawText(80, 200, "Environment Monitor", GREEN, 20);
  

  CO2Text = SimbleeForMobile.drawText(120, 250, "CO2", BLACK, 40);
  SimbleeForMobile.setVisible(CO2Text,false);
  CO2Val_ui = SimbleeForMobile.drawText(110, 300, "", BLUE, 45);
  SimbleeForMobile.setVisible(CO2Val_ui,false);
  ppmText = SimbleeForMobile.drawText(215,325, "ppm", BLUE);
  SimbleeForMobile.setVisible(ppmText,false);
  VOCText = SimbleeForMobile.drawText(45, 350, "Volatile Organic Compounds", BLACK, 20);
  SimbleeForMobile.setVisible(VOCText,false);
  HumidVal_ui = SimbleeForMobile.drawText(110, 400, "", BLUE, 45);
  SimbleeForMobile.setVisible(HumidVal_ui,false);
  ppbText = SimbleeForMobile.drawText(215, 425, "ppb", BLUE);
  SimbleeForMobile.setVisible(ppbText,false);
  clickText = SimbleeForMobile.drawText(80, 250, "", GREEN, 20);
  rangeRec = SimbleeForMobile.drawRect(0, 0, SimbleeForMobile.screenWidth,  SimbleeForMobile.screenHeight, RED);
  SimbleeForMobile.setVisible(rangeRec,false);
  rangeText = SimbleeForMobile.drawText(40, 100, "Environment is not in ideal range.", BLACK, 20);
  SimbleeForMobile.setVisible(rangeText,false);
  rangeText2 = SimbleeForMobile.drawText(40, 150, "Appropriate measures are being taken.", BLACK, 20);
  SimbleeForMobile.setVisible(rangeText2,false);

  myPlant1 = SimbleeForMobile.drawButton(50, 300, 100, "Aloe Vera", GREEN, BOX_TYPE);
  myPlant2 = SimbleeForMobile.drawButton(50, 350, 100, "Orchid", GREEN, BOX_TYPE);
  myPlant3 = SimbleeForMobile.drawButton(50, 400, 100, "Tulip", GREEN, BOX_TYPE);
  myPlant4 = SimbleeForMobile.drawButton(170, 300, 100, "Fern", GREEN, BOX_TYPE);
  myPlant5 = SimbleeForMobile.drawButton(170, 350, 100, "Cactus", GREEN, BOX_TYPE);
  myPlant6 = SimbleeForMobile.drawButton(170, 400, 100, "Ficus", GREEN, BOX_TYPE);

  aloeVera = SimbleeForMobile.drawText(92, 100, "Aloe Vera", BLUE, 35);
  SimbleeForMobile.setVisible(aloeVera, false);
  Fern = SimbleeForMobile.drawText(125, 100, "Fern", BLUE, 35);
  SimbleeForMobile.setVisible(Fern, false);
  Orchid = SimbleeForMobile.drawText(110, 100, "Orchid", BLUE, 35);
  SimbleeForMobile.setVisible(Orchid, false);
  Cactus = SimbleeForMobile.drawText(110, 100, "Cactus", BLUE, 35);
  SimbleeForMobile.setVisible(Cactus, false);
  Tulip = SimbleeForMobile.drawText(120, 100, "Tulip", BLUE, 35);
  SimbleeForMobile.setVisible(Tulip, false);
  Ficus = SimbleeForMobile.drawText(120, 100, "Ficus", BLUE, 35);
  SimbleeForMobile.setVisible(Ficus, false);


  SimbleeForMobile.setEvents(myPlant1, EVENT_PRESS);
  SimbleeForMobile.setEvents(myPlant2, EVENT_PRESS);
  SimbleeForMobile.setEvents(myPlant3, EVENT_PRESS);
  SimbleeForMobile.setEvents(myPlant4, EVENT_PRESS);
  SimbleeForMobile.setEvents(myPlant5, EVENT_PRESS);
  SimbleeForMobile.setEvents(myPlant6, EVENT_PRESS);

  SimbleeForMobile.endScreen();
}

void ui_event(event_t &event)
{
  
  if(event.id == myPlant1) {
    if(SimbleeForMobile.updatable) {
      SimbleeForMobile.setVisible(CO2Text, true);
      SimbleeForMobile.setVisible(CO2Val_ui, true);
      SimbleeForMobile.setVisible(ppmText, true);
      SimbleeForMobile.setVisible(myRec2, true);
      SimbleeForMobile.setVisible(VOCText, true);
      SimbleeForMobile.setVisible(HumidVal_ui, true);
      SimbleeForMobile.setVisible(ppbText, true);
      SimbleeForMobile.setVisible(aloeVera, true);
      SimbleeForMobile.setVisible(myPlant1, false);
      SimbleeForMobile.setVisible(myPlant2, false);
      SimbleeForMobile.setVisible(myPlant3, false);
      SimbleeForMobile.setVisible(myPlant4, false);
      SimbleeForMobile.setVisible(myPlant5, false);
      SimbleeForMobile.setVisible(myPlant6, false);
      SimbleeForMobile.setVisible(myiPlant, false);
      SimbleeForMobile.setVisible(myEnvMon, false);
      SimbleeForMobile.setVisible(clickText, false);
      SimbleeForMobile.setVisible(rangeRec, false);
      SimbleeForMobile.setVisible(rangeText, false);
      SimbleeForMobile.setVisible(rangeText2, false);
      
      
        }
        
  }

  if(event.id == myPlant2) {
    if(SimbleeForMobile.updatable) {
      SimbleeForMobile.setVisible(CO2Text, true);
      SimbleeForMobile.setVisible(CO2Val_ui, true);
      SimbleeForMobile.setVisible(ppmText, true);
      SimbleeForMobile.setVisible(VOCText, true);
      SimbleeForMobile.setVisible(HumidVal_ui, true);
      SimbleeForMobile.setVisible(ppbText, true);
      SimbleeForMobile.setVisible(myRec2, true);
      SimbleeForMobile.setVisible(Fern, true);
      SimbleeForMobile.setVisible(myPlant1, false);
      SimbleeForMobile.setVisible(myPlant2, false);
      SimbleeForMobile.setVisible(myPlant3, false);
      SimbleeForMobile.setVisible(myPlant4, false);
      SimbleeForMobile.setVisible(myPlant5, false);
      SimbleeForMobile.setVisible(myPlant6, false);
      SimbleeForMobile.setVisible(myiPlant, false);
      SimbleeForMobile.setVisible(myEnvMon, false);
      SimbleeForMobile.setVisible(clickText, false);
      SimbleeForMobile.setVisible(rangeRec, false);
      SimbleeForMobile.setVisible(rangeText, false);
      SimbleeForMobile.setVisible(rangeText2, false);
        }
  }

   if(event.id == myPlant3) {
    if(SimbleeForMobile.updatable) {
      SimbleeForMobile.setVisible(CO2Text, true);
      SimbleeForMobile.setVisible(CO2Val_ui, true);
      SimbleeForMobile.setVisible(ppmText, true);
      SimbleeForMobile.setVisible(VOCText, true);
      SimbleeForMobile.setVisible(HumidVal_ui, true);
      SimbleeForMobile.setVisible(ppbText, true);
      SimbleeForMobile.setVisible(myRec2, true);
      SimbleeForMobile.setVisible(Orchid, true);
      SimbleeForMobile.setVisible(myPlant1, false);
      SimbleeForMobile.setVisible(myPlant2, false);
      SimbleeForMobile.setVisible(myPlant3, false);
      SimbleeForMobile.setVisible(myPlant4, false);
      SimbleeForMobile.setVisible(myPlant5, false);
      SimbleeForMobile.setVisible(myPlant6, false);
      SimbleeForMobile.setVisible(myiPlant, false);
      SimbleeForMobile.setVisible(myEnvMon, false);
      SimbleeForMobile.setVisible(clickText, false);
      SimbleeForMobile.setVisible(rangeRec, false);
      SimbleeForMobile.setVisible(rangeText, false);
      SimbleeForMobile.setVisible(rangeText2, false);
        }
  }

   if(event.id == myPlant4) {
    if(SimbleeForMobile.updatable) {
      SimbleeForMobile.setVisible(CO2Text, true);
      SimbleeForMobile.setVisible(CO2Val_ui, true);
      SimbleeForMobile.setVisible(ppmText, true);
      SimbleeForMobile.setVisible(VOCText, true);
      SimbleeForMobile.setVisible(HumidVal_ui, true);
      SimbleeForMobile.setVisible(ppbText, true);
      SimbleeForMobile.setVisible(myRec2, true);
      SimbleeForMobile.setVisible(Cactus, true);
      SimbleeForMobile.setVisible(myPlant1, false);
      SimbleeForMobile.setVisible(myPlant2, false);
      SimbleeForMobile.setVisible(myPlant3, false);
      SimbleeForMobile.setVisible(myPlant4, false);
      SimbleeForMobile.setVisible(myPlant5, false);
      SimbleeForMobile.setVisible(myPlant6, false);
      SimbleeForMobile.setVisible(myiPlant, false);
      SimbleeForMobile.setVisible(myEnvMon, false);
      SimbleeForMobile.setVisible(clickText, false);
      SimbleeForMobile.setVisible(rangeRec, false);
      SimbleeForMobile.setVisible(rangeText, false);
      SimbleeForMobile.setVisible(rangeText2, false);
        }
  }

  if(event.id == myPlant5) {
      SimbleeForMobile.setVisible(CO2Text, true);
      SimbleeForMobile.setVisible(CO2Val_ui, true);
      SimbleeForMobile.setVisible(ppmText, true);
      SimbleeForMobile.setVisible(VOCText, true);
      SimbleeForMobile.setVisible(HumidVal_ui, true);
      SimbleeForMobile.setVisible(ppbText, true);
      SimbleeForMobile.setVisible(myRec2, true);
      SimbleeForMobile.setVisible(Tulip, true);
      SimbleeForMobile.setVisible(myPlant1, false);
      SimbleeForMobile.setVisible(myPlant2, false);
      SimbleeForMobile.setVisible(myPlant3, false);
      SimbleeForMobile.setVisible(myPlant4, false);
      SimbleeForMobile.setVisible(myPlant5, false);
      SimbleeForMobile.setVisible(myPlant6, false);
      SimbleeForMobile.setVisible(myiPlant, false);
      SimbleeForMobile.setVisible(myEnvMon, false);
      SimbleeForMobile.setVisible(clickText, false);
      SimbleeForMobile.setVisible(rangeRec, false);
      SimbleeForMobile.setVisible(rangeText, false);
      SimbleeForMobile.setVisible(rangeText2, false);
        }
 

  if(event.id == myPlant6) {
      SimbleeForMobile.setVisible(CO2Text, true);
      SimbleeForMobile.setVisible(CO2Val_ui, true);
      SimbleeForMobile.setVisible(ppmText, true);
      SimbleeForMobile.setVisible(VOCText, true);
      SimbleeForMobile.setVisible(HumidVal_ui, true);
      SimbleeForMobile.setVisible(ppbText, true);
      SimbleeForMobile.setVisible(myRec2, true);
      SimbleeForMobile.setVisible(Ficus, true);
      SimbleeForMobile.setVisible(myPlant1, false);
      SimbleeForMobile.setVisible(myPlant2, false);
      SimbleeForMobile.setVisible(myPlant3, false);
      SimbleeForMobile.setVisible(myPlant4, false);
      SimbleeForMobile.setVisible(myPlant5, false);
      SimbleeForMobile.setVisible(myPlant6, false);
      SimbleeForMobile.setVisible(myiPlant, false);
      SimbleeForMobile.setVisible(myEnvMon, false);
      SimbleeForMobile.setVisible(clickText, false);
      SimbleeForMobile.setVisible(rangeRec, false);
      SimbleeForMobile.setVisible(rangeText, false);
      SimbleeForMobile.setVisible(rangeText2, false);
        }
  }
  

// home button 
