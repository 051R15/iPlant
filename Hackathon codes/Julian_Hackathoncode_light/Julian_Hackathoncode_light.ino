#include <SimbleeForMobile.h>
#include <Simblee_TMG4903.h>

Simblee_TMG4903 TMG4903;

color_t darkgreen = rgb(65,139,0);
color_t lightgreen = rgb(173,255,47);

uint8_t textA, textB, textC;
uint8_t button1, button2, button3, button4, button5, button6, buttonHome;
uint8_t aloeVera, Fern, Orchid, Cactus, Tulip, Ficus;
uint8_t textYes, textNo;
uint8_t textClear, textRed, textGreen, textBlue;
uint8_t valueClear, valueRed, valueGreen, valueBlue;
uint8_t mercury;
unsigned long lastUpdated = 0;
unsigned long updateRate = 100;
asm(".global _printf_float");

int visibleState1 = 0;
int visibleState2 = 0;
int visibleState3 = 0;
int visibleState4 = 0;
int visibleState5 = 0;
int visibleState6 = 0;

void setup() {
  Serial.begin(115200);
  delay(100);

  if (!TMG4903.begin()) {
    printf("Failed to intialize Sensor, Halting!\n");
    while (1);
  }

  SimbleeForMobile.deviceName = "iPlant";
  SimbleeForMobile.advertisementData = "lightSensor";
  SimbleeForMobile.begin();
}

void loop() {
  unsigned long loopTime = millis();
  
  uint16_t clearT = TMG4903.readClear();
  uint16_t red = TMG4903.readRed();
  uint16_t green = TMG4903.readGreen();
  uint16_t blue = TMG4903.readBlue();

  printf("Clear: %d\tRed: %d\tGreen: %d\tBlue: %d\n", clearT, red, green, blue);

  delay(50);

  if (SimbleeForMobile.updatable && updateRate < (loopTime - lastUpdated))
  {
    lastUpdated = loopTime;

    SimbleeForMobile.updateValue(valueClear, clearT);
    SimbleeForMobile.updateValue(valueRed, red);
    SimbleeForMobile.updateValue(valueGreen, green);
    SimbleeForMobile.updateValue(valueBlue, blue);
  }

  if (SimbleeForMobile.updatable){
    
    //Aloe Vera Light Configurations
    if (visibleState1 == 1 && clearT <= 5000){
      SimbleeForMobile.setVisible(textNo, true);
      SimbleeForMobile.setVisible(textYes, false);
    }
    else if (visibleState1 == 1 && clearT > 5000){
       SimbleeForMobile.setVisible(textNo, false);
       SimbleeForMobile.setVisible(textYes, true);
    }
    
    //Orchid Light Configurations
    if (visibleState2 == 1 && clearT >= 3000){
      SimbleeForMobile.setVisible(textNo, true);
      SimbleeForMobile.setVisible(textYes, false);
    }
    else if (visibleState2 == 1 && clearT < 3000){
       SimbleeForMobile.setVisible(textNo, false);
       SimbleeForMobile.setVisible(textYes, true);
    }
    
    //Tulip Light Configurations
    if (visibleState3 == 1 && clearT <= 5000){
      SimbleeForMobile.setVisible(textNo, true);
      SimbleeForMobile.setVisible(textYes, false);
    }
    else if (visibleState3 == 1 && clearT > 5000){
       SimbleeForMobile.setVisible(textNo, false);
       SimbleeForMobile.setVisible(textYes, true);
    }
    
    //Fern Light Configurations
    if (visibleState4 == 1 && clearT >= 3000){
      SimbleeForMobile.setVisible(textNo, true);
      SimbleeForMobile.setVisible(textYes, false);
    }
    else if (visibleState4 == 1 && clearT < 3000){
       SimbleeForMobile.setVisible(textNo, false);
       SimbleeForMobile.setVisible(textYes, true);
    }
    
    //Cactus Light Configurations
    if (visibleState5 == 1 && clearT <= 5500){
      SimbleeForMobile.setVisible(textNo, true);
      SimbleeForMobile.setVisible(textYes, false);
    }
    else if (visibleState5 == 1 && clearT > 5500){
       SimbleeForMobile.setVisible(textNo, false);
       SimbleeForMobile.setVisible(textYes, true);
    }
    
    //Ficus Light Configurations
    if (visibleState6 == 1 && clearT >= 3500 || visibleState6 == 1 && clearT <= 2500){
      SimbleeForMobile.setVisible(textNo, true);
      SimbleeForMobile.setVisible(textYes, false);
    }
    else if (visibleState6 == 1){
       SimbleeForMobile.setVisible(textNo, false);
       SimbleeForMobile.setVisible(textYes, true);
    }
  }

  SimbleeForMobile.process();
}

void ui(){
  SimbleeForMobile.beginScreen(darkgreen);

  textA = SimbleeForMobile.drawText(100, 100, "iPlant", lightgreen, 50);
  textB = SimbleeForMobile.drawText(65, 150, "Light Sensor Information", lightgreen, 20);
  textC = SimbleeForMobile.drawText(80, 250, "Select which plant:", lightgreen, 20);

  textYes = SimbleeForMobile.drawText(30, 310, "Desirable Conditions :)", GREEN, 30);
  SimbleeForMobile.setVisible(textYes, false);
  textNo = SimbleeForMobile.drawText(10, 310, "Undesirable Conditions :(", RED, 30);
  SimbleeForMobile.setVisible(textNo, false);

  aloeVera = SimbleeForMobile.drawText(92, 400, "Aloe Vera", BLUE, 35);
  SimbleeForMobile.setVisible(aloeVera, false);
  Fern = SimbleeForMobile.drawText(125, 400, "Fern", BLUE, 35);
  SimbleeForMobile.setVisible(Fern, false);
  Orchid = SimbleeForMobile.drawText(110, 400, "Orchid", BLUE, 35);
  SimbleeForMobile.setVisible(Orchid, false);
  Cactus = SimbleeForMobile.drawText(110, 400, "Cactus", BLUE, 35);
  SimbleeForMobile.setVisible(Cactus, false);
  Tulip = SimbleeForMobile.drawText(120, 400, "Tulip", BLUE, 35);
  SimbleeForMobile.setVisible(Tulip, false);
  Ficus = SimbleeForMobile.drawText(120, 400, "Ficus", BLUE, 35);
  SimbleeForMobile.setVisible(Ficus, false);

  textClear = SimbleeForMobile.drawText(65, 200, "Clear", lightgreen, 30);
  valueClear = SimbleeForMobile.drawText(220, 200, "", lightgreen, 30);
  textRed = SimbleeForMobile.drawText(90, 250, "R:", BLACK, 10);
  valueRed = SimbleeForMobile.drawText(105, 250, "", BLACK, 10);
  textGreen = SimbleeForMobile.drawText(140, 250, "G:", BLACK, 10);
  valueGreen = SimbleeForMobile.drawText(155, 250, "", BLACK, 10);
  textBlue = SimbleeForMobile.drawText(190, 250, "B:", BLACK, 10);
  valueBlue = SimbleeForMobile.drawText(205, 250, "", BLACK, 10);

  button1 = SimbleeForMobile.drawButton(50, 300, 100, "Aloe Vera", lightgreen, BOX_TYPE);
  button2 = SimbleeForMobile.drawButton(50, 350, 100, "Orchid", lightgreen, BOX_TYPE);
  button3 = SimbleeForMobile.drawButton(50, 400, 100, "Tulip", lightgreen, BOX_TYPE);
  button4 = SimbleeForMobile.drawButton(170, 300, 100, "Fern", lightgreen, BOX_TYPE);
  button5 = SimbleeForMobile.drawButton(170, 350, 100, "Cactus", lightgreen, BOX_TYPE);
  button6 = SimbleeForMobile.drawButton(170, 400, 100, "Ficus", lightgreen, BOX_TYPE);
  buttonHome = SimbleeForMobile.drawButton(108, 500, 100, "HOME", lightgreen, BOX_TYPE);
  SimbleeForMobile.setVisible(buttonHome, false);
  SimbleeForMobile.setEvents(button1, EVENT_PRESS);
  SimbleeForMobile.setEvents(button2, EVENT_PRESS);
  SimbleeForMobile.setEvents(button3, EVENT_PRESS);
  SimbleeForMobile.setEvents(button4, EVENT_PRESS);
  SimbleeForMobile.setEvents(button5, EVENT_PRESS);
  SimbleeForMobile.setEvents(button6, EVENT_PRESS);
  SimbleeForMobile.setEvents(buttonHome, EVENT_PRESS);
  
  SimbleeForMobile.setVisible(textClear, false);
  SimbleeForMobile.setVisible(valueClear, false);
  SimbleeForMobile.setVisible(textRed, false);
  SimbleeForMobile.setVisible(valueRed, false);
  SimbleeForMobile.setVisible(textGreen, false);
  SimbleeForMobile.setVisible(valueGreen, false);
  SimbleeForMobile.setVisible(textBlue, false);
  SimbleeForMobile.setVisible(valueBlue, false);


  SimbleeForMobile.endScreen();
}

void ui_event(event_t &event){
  
  //When Aloe Vera Button is pressed
  if (event.id == button1){
    if (SimbleeForMobile.updatable){
      SimbleeForMobile.setVisible(textClear, true);
      SimbleeForMobile.setVisible(valueClear, true);
      SimbleeForMobile.setVisible(textRed, true);
      SimbleeForMobile.setVisible(valueRed, true);
      SimbleeForMobile.setVisible(textGreen, true);
      SimbleeForMobile.setVisible(valueGreen, true);
      SimbleeForMobile.setVisible(textBlue, true);
      SimbleeForMobile.setVisible(valueBlue, true);
      SimbleeForMobile.setVisible(button1, false);
      SimbleeForMobile.setVisible(button2, false);
      SimbleeForMobile.setVisible(button3, false);
      SimbleeForMobile.setVisible(button4, false);
      SimbleeForMobile.setVisible(button5, false);
      SimbleeForMobile.setVisible(button6, false);
      SimbleeForMobile.setVisible(textC, false);
      SimbleeForMobile.setVisible(buttonHome, true);
      SimbleeForMobile.setVisible(aloeVera, true);
      visibleState1 = 1;
    }
  }

  //When Orchid Button is pressed
  if (event.id == button2){
    SimbleeForMobile.setVisible(textClear, true);
      SimbleeForMobile.setVisible(valueClear, true);
      SimbleeForMobile.setVisible(textRed, true);
      SimbleeForMobile.setVisible(valueRed, true);
      SimbleeForMobile.setVisible(textGreen, true);
      SimbleeForMobile.setVisible(valueGreen, true);
      SimbleeForMobile.setVisible(textBlue, true);
      SimbleeForMobile.setVisible(valueBlue, true);
      SimbleeForMobile.setVisible(button1, false);
      SimbleeForMobile.setVisible(button2, false);
      SimbleeForMobile.setVisible(button3, false);
      SimbleeForMobile.setVisible(button4, false);
      SimbleeForMobile.setVisible(button5, false);
      SimbleeForMobile.setVisible(button6, false);
      SimbleeForMobile.setVisible(textC, false);
      SimbleeForMobile.setVisible(buttonHome, true);
      SimbleeForMobile.setVisible(Orchid, true);
      visibleState2 = 1;
  }

  
  //When Tulip Button is pressed
  if (event.id == button3){
    SimbleeForMobile.setVisible(textClear, true);
      SimbleeForMobile.setVisible(valueClear, true);
      SimbleeForMobile.setVisible(textRed, true);
      SimbleeForMobile.setVisible(valueRed, true);
      SimbleeForMobile.setVisible(textGreen, true);
      SimbleeForMobile.setVisible(valueGreen, true);
      SimbleeForMobile.setVisible(textBlue, true);
      SimbleeForMobile.setVisible(valueBlue, true);
      SimbleeForMobile.setVisible(button1, false);
      SimbleeForMobile.setVisible(button2, false);
      SimbleeForMobile.setVisible(button3, false);
      SimbleeForMobile.setVisible(button4, false);
      SimbleeForMobile.setVisible(button5, false);
      SimbleeForMobile.setVisible(button6, false);
      SimbleeForMobile.setVisible(textC, false);
      SimbleeForMobile.setVisible(buttonHome, true);
      SimbleeForMobile.setVisible(Tulip, true);
      visibleState3 = 1;
  }

  
  //When Fern Button is pressed
  if (event.id == button4){
    SimbleeForMobile.setVisible(textClear, true);
      SimbleeForMobile.setVisible(valueClear, true);
      SimbleeForMobile.setVisible(textRed, true);
      SimbleeForMobile.setVisible(valueRed, true);
      SimbleeForMobile.setVisible(textGreen, true);
      SimbleeForMobile.setVisible(valueGreen, true);
      SimbleeForMobile.setVisible(textBlue, true);
      SimbleeForMobile.setVisible(valueBlue, true);
      SimbleeForMobile.setVisible(button1, false);
      SimbleeForMobile.setVisible(button2, false);
      SimbleeForMobile.setVisible(button3, false);
      SimbleeForMobile.setVisible(button4, false);
      SimbleeForMobile.setVisible(button5, false);
      SimbleeForMobile.setVisible(button6, false);
      SimbleeForMobile.setVisible(textC, false);
      SimbleeForMobile.setVisible(buttonHome, true);
      SimbleeForMobile.setVisible(Fern, true);
      visibleState4 = 1;
  }

  
  //When Cactus Button is pressed
  if (event.id == button5){
    SimbleeForMobile.setVisible(textClear, true);
      SimbleeForMobile.setVisible(valueClear, true);
      SimbleeForMobile.setVisible(textRed, true);
      SimbleeForMobile.setVisible(valueRed, true);
      SimbleeForMobile.setVisible(textGreen, true);
      SimbleeForMobile.setVisible(valueGreen, true);
      SimbleeForMobile.setVisible(textBlue, true);
      SimbleeForMobile.setVisible(valueBlue, true);
      SimbleeForMobile.setVisible(button1, false);
      SimbleeForMobile.setVisible(button2, false);
      SimbleeForMobile.setVisible(button3, false);
      SimbleeForMobile.setVisible(button4, false);
      SimbleeForMobile.setVisible(button5, false);
      SimbleeForMobile.setVisible(button6, false);
      SimbleeForMobile.setVisible(textC, false);
      SimbleeForMobile.setVisible(buttonHome, true);
      SimbleeForMobile.setVisible(Cactus, true);
      visibleState5 = 1;
  }

  
  //When Ficus Button is pressed
  if (event.id == button6){
    SimbleeForMobile.setVisible(textClear, true);
      SimbleeForMobile.setVisible(valueClear, true);
      SimbleeForMobile.setVisible(textRed, true);
      SimbleeForMobile.setVisible(valueRed, true);
      SimbleeForMobile.setVisible(textGreen, true);
      SimbleeForMobile.setVisible(valueGreen, true);
      SimbleeForMobile.setVisible(textBlue, true);
      SimbleeForMobile.setVisible(valueBlue, true);
      SimbleeForMobile.setVisible(button1, false);
      SimbleeForMobile.setVisible(button2, false);
      SimbleeForMobile.setVisible(button3, false);
      SimbleeForMobile.setVisible(button4, false);
      SimbleeForMobile.setVisible(button5, false);
      SimbleeForMobile.setVisible(button6, false);
      SimbleeForMobile.setVisible(textC, false);
      SimbleeForMobile.setVisible(buttonHome, true);
      SimbleeForMobile.setVisible(Ficus, true);
      visibleState6 = 1;
  }

  //When Home Button is pressed
  if (event.id == buttonHome){
    SimbleeForMobile.setVisible(button1, true);
    SimbleeForMobile.setVisible(button2, true);
    SimbleeForMobile.setVisible(button3, true);
    SimbleeForMobile.setVisible(button4, true);
    SimbleeForMobile.setVisible(button5, true);
    SimbleeForMobile.setVisible(button6, true);
    SimbleeForMobile.setVisible(textClear, false);
    SimbleeForMobile.setVisible(valueClear, false);
    SimbleeForMobile.setVisible(textRed, false);
    SimbleeForMobile.setVisible(valueRed, false);
    SimbleeForMobile.setVisible(textGreen, false);
    SimbleeForMobile.setVisible(valueGreen, false);
    SimbleeForMobile.setVisible(textBlue, false);
    SimbleeForMobile.setVisible(valueBlue, false);
    SimbleeForMobile.setVisible(textC, true);
    SimbleeForMobile.setVisible(aloeVera, false);
    SimbleeForMobile.setVisible(Orchid, false);
    SimbleeForMobile.setVisible(Tulip, false);
    SimbleeForMobile.setVisible(Fern, false);
    SimbleeForMobile.setVisible(Cactus, false);
    SimbleeForMobile.setVisible(Ficus, false);
    SimbleeForMobile.setVisible(buttonHome, false);
    SimbleeForMobile.setVisible(textYes, false);
    SimbleeForMobile.setVisible(textNo, false);
    visibleState1 = 0;
    visibleState2 = 0;
    visibleState3 = 0;
    visibleState4 = 0;
    visibleState5 = 0;
    visibleState6 = 0;
  }
}
