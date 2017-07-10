// Doesn't work

#include <SimbleeForMobile.h>

int fromS1toS2ButtonID, fromS1toS3ButtonID, fromS1toS4ButtonID;
int fromS2toS1ButtonID, fromS2toS3ButtonID, fromS2toS4ButtonID;
int fromS3toS1ButtonID, fromS3toS2ButtonID, fromS3toS4ButtonID;
int fromS4toS1ButtonID, fromS4toS2ButtonID, fromS4toS3ButtonID;

int currentScreen;

uint8_t myScreen1, myText1;
uint8_t myScreen2, myText2;
uint8_t myScreen3, myText3;
uint8_t myScreen4, myText4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Setup beginning");
  
  SimbleeForMobile.deviceName = "iPlant";
  SimbleeForMobile.advertisementData = "DS Trial";

  SimbleeForMobile.domain = "twoscreens.simblee.com";
 
  SimbleeForMobile.begin();
  
  Serial.println("Setup completed");
}

void loop() {
 
  SimbleeForMobile.process();  
}

void SimbleeForMobile_onConnect()
{
  currentScreen = -1;
}

void SimbleeForMobile_onDisconnect()
{
}

// SCREEN 1
void createScreen1()
{
  SimbleeForMobile.beginScreen(WHITE, PORTRAIT);
  
  myScreen1 = SimbleeForMobile.drawRect(0, 0, SimbleeForMobile.screenWidth,  SimbleeForMobile.screenHeight, WHITE);
  myText1 = SimbleeForMobile.drawText(120, 300, "I am on screen 1", BLACK);

  int textID = SimbleeForMobile.drawText(80, 60, "Screen 1", BLACK, 40);
  fromS1toS2ButtonID = SimbleeForMobile.drawButton(50, 200, 100, "Screen 2");
  fromS1toS3ButtonID = SimbleeForMobile.drawButton(200, 200, 100, "Screen 3");
  fromS1toS4ButtonID = SimbleeForMobile.drawButton(200, 300, 100, "Screen 4");

  SimbleeForMobile.setEvents(fromS1toS2ButtonID, EVENT_PRESS);
  SimbleeForMobile.setEvents(fromS1toS3ButtonID, EVENT_PRESS);
  SimbleeForMobile.setEvents(fromS1toS4ButtonID, EVENT_PRESS);
  
  SimbleeForMobile.endScreen();
}

// SCREEN 2
void createScreen2()
{
  SimbleeForMobile.beginScreen(WHITE, PORTRAIT);
  myScreen2 = SimbleeForMobile.drawRect(0, 0, SimbleeForMobile.screenWidth,  SimbleeForMobile.screenHeight, BLUE);
  myText2 = SimbleeForMobile.drawText(120, 300, "I am on screen 2", WHITE);

  int textID = SimbleeForMobile.drawText(80, 60, "Screen 2", BLACK, 40);
  fromS2toS1ButtonID = SimbleeForMobile.drawButton(50, 200, 100, "Screen 1");
  fromS2toS3ButtonID = SimbleeForMobile.drawButton(200, 200, 100, "Screen 3");
  fromS2toS4ButtonID = SimbleeForMobile.drawButton(200, 300, 100, "Screen 4");
  
  SimbleeForMobile.setEvents(fromS2toS1ButtonID, EVENT_PRESS);
  SimbleeForMobile.setEvents(fromS2toS3ButtonID, EVENT_PRESS);
  SimbleeForMobile.setEvents(fromS2toS4ButtonID, EVENT_PRESS);

  SimbleeForMobile.endScreen();
}

// SCREEN 3
void createScreen3()
{
  SimbleeForMobile.beginScreen(GREEN, PORTRAIT);
  myScreen3 = SimbleeForMobile.drawRect(0, 0, SimbleeForMobile.screenWidth,  SimbleeForMobile.screenHeight, GREEN);
  myText3 = SimbleeForMobile.drawText(120, 300, "I am on screen 3", WHITE);

  int textID = SimbleeForMobile.drawText(80, 60, "Screen 3", BLACK, 40);
  fromS3toS1ButtonID = SimbleeForMobile.drawButton(50, 200, 100, "Screen 1");
  fromS3toS2ButtonID = SimbleeForMobile.drawButton(200, 200, 100, "Screen 2");
  fromS3toS4ButtonID = SimbleeForMobile.drawButton(200, 300, 100, "Screen 4");

  SimbleeForMobile.setEvents(fromS3toS1ButtonID, EVENT_PRESS);
  SimbleeForMobile.setEvents(fromS3toS2ButtonID, EVENT_PRESS);
  SimbleeForMobile.setEvents(fromS3toS4ButtonID, EVENT_PRESS);

  SimbleeForMobile.endScreen();
}

// SCREEN 4
void createScreen4()
{
  SimbleeForMobile.beginScreen(YELLOW, PORTRAIT);
  myScreen4 = SimbleeForMobile.drawRect(0, 0, SimbleeForMobile.screenWidth,  SimbleeForMobile.screenHeight, GREEN);
  myText4 = SimbleeForMobile.drawText(120, 300, "I am on screen 4", BLACK);

  int textID = SimbleeForMobile.drawText(80, 60, "Screen 3", BLACK, 40);
  fromS4toS1ButtonID = SimbleeForMobile.drawButton(50, 200, 100, "Screen 1");
  fromS4toS2ButtonID = SimbleeForMobile.drawButton(200, 200, 100, "Screen 2");
  fromS4toS3ButtonID = SimbleeForMobile.drawButton(200, 300, 100, "Screen 4");

  SimbleeForMobile.setEvents(fromS4toS1ButtonID, EVENT_PRESS);
  SimbleeForMobile.setEvents(fromS4toS2ButtonID, EVENT_PRESS);
  SimbleeForMobile.setEvents(fromS4toS3ButtonID, EVENT_PRESS);

  SimbleeForMobile.endScreen();
}

void ui()
{  
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

    case 3:
      createScreen3();
      break;

    case 4:
      createScreen4();
      break;
             
   default:
      Serial.print("ui: Unknown screen requested: ");
      Serial.println(SimbleeForMobile.screen);
  }
}

void ui_event(event_t &event)
{
  
// Add statement for if both buttons are pressed -- return screens 

//TO SCREEN 1

  if(event.id == fromS2toS1ButtonID && event.type == EVENT_PRESS && (currentScreen == 2))
  {
    SimbleeForMobile.showScreen(1);
  }
  else if(event.id == fromS3toS1ButtonID && event.type == EVENT_PRESS && (currentScreen == 3))
  {
    SimbleeForMobile.showScreen(1);
  }

  else if(event.id == fromS4toS1ButtonID && event.type == EVENT_PRESS && (currentScreen == 4))
  {
    SimbleeForMobile.showScreen(1);
  }


//TO SCREEN 2

 if(event.id == fromS1toS2ButtonID && event.type == EVENT_PRESS && (currentScreen == 1))
  {
    SimbleeForMobile.showScreen(2);
  }
  else if(event.id == fromS3toS2ButtonID && event.type == EVENT_PRESS && (currentScreen == 3))
  {
    SimbleeForMobile.showScreen(2);
  }
   else if(event.id == fromS4toS2ButtonID && event.type == EVENT_PRESS && (currentScreen == 4))
  {
    SimbleeForMobile.showScreen(2);
  }
 

//TO SCREEN 3

 if(event.id == fromS1toS3ButtonID && event.type == EVENT_PRESS && (currentScreen == 1))
  {
    SimbleeForMobile.showScreen(3);
  }
  else if(event.id == fromS2toS3ButtonID && event.type == EVENT_PRESS && (currentScreen == 2))
  {
    SimbleeForMobile.showScreen(3);
  }
   else if(event.id == fromS4toS3ButtonID && event.type == EVENT_PRESS && (currentScreen == 4))
  {
    SimbleeForMobile.showScreen(3);
  }

//TO SCREEN 4

 if(event.id == fromS1toS4ButtonID && event.type == EVENT_PRESS && (currentScreen == 1))
  {
    SimbleeForMobile.showScreen(4);
  }
  else if(event.id == fromS2toS4ButtonID && event.type == EVENT_PRESS && (currentScreen == 42))
  {
    SimbleeForMobile.showScreen(4);
  }
  else if(event.id == fromS3toS4ButtonID && event.type == EVENT_PRESS && (currentScreen == 3))
  {
    SimbleeForMobile.showScreen(4);
  }
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


