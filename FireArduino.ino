#include "Enums.h"
#include "BaseClasses.h"
#include "UtilityClasses.h"
#include "UtilityMethods.h"
#include "UnitClass.h"
#include "ItemDatabase.h"
#include "DebugStuff.h"
#include "BattleHandler.h"
#include "ChapterInfo.h"
#include "SystemBehavior.h"

#include <TFT_eSPI.h>                 // Include the graphics library (this includes the sprite functions)

TFT_eSPI    tft = TFT_eSPI();         // Create object "tft"

//system variables
unsigned long animationTimer = 0;
byte animationState = 0; //which state the animation is in, goes from 0 to 5
byte gameState = GSselectionPhase;//principal gamestate, decides what is happening

//                         str,mag,skl,spd,lck,def,res,mov,maxHp
byte stat1[coreStatAmount] = {16, 2, 8, 13, 2, 5, 1, 7, 24};
byte stat2[coreStatAmount] = {3, 14, 6, 6, 14, 7, 14, 6, 31};
byte stat3[coreStatAmount] = {12, 7, 10, 12, 0, 9, 3, 4, 27};
byte stat4[coreStatAmount] = {15, 3, 16, 7, 1, 12, 1, 5, 38};

bool debugMode = false;

byte colData [constMaxChapterSize][constMaxChapterSize] =
{
  {0, 0, 1, 1, 0, 0, 0, 0},
  {0, 0, 1, 1, 0, 0, 0, 0},
  {0, 0, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};
ChapterInfo chap = ChapterInfo(10, 10, colData);

byte actRange [constMaxChapterSize][constMaxChapterSize];

Vector2 cursorPos = Vector2(1, 1);

Vector2 camera = Vector2(0, 0);

Unit * selectedUnit;

void setup() {

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);

  resetActRange();
  // put your setup code here, to run once:
  //unit = Unit({16,13,2,5,4,8}, 3, 16);
  Serial.begin(38400);

  chap.addUnit(Unit("Chrom", stat1, 0, 1, 4, 1));
  chap.addUnit(Unit("Makoto", stat2, 0, 2, 1, 4));
  chap.addUnit(Unit("sans", stat3, 1, 3, 3, 0));
  chap.addUnit(Unit("Pristis", stat4, 0, 5, 5, 4));
  chap.addUnit(Unit("Albert", stat4, 1, 4, 2, 1));

  //Iron Sword
  chap.getUnitPointerAtSlot(0)->addItem(0x01);
  chap.getUnitPointerAtSlot(0)->setHeld(1);

  //Iron Bow
  chap.getUnitPointerAtSlot(1)->addItem(0x04);
  chap.getUnitPointerAtSlot(1)->setHeld(1);

  //Eigaon (Spell)
  chap.getUnitPointerAtSlot(2)->addItem(0x06);
  chap.getUnitPointerAtSlot(2)->setHeld(1);

  //Maeigaon (Spell)
  chap.getUnitPointerAtSlot(3)->addItem(0x0A);
  chap.getUnitPointerAtSlot(3)->setHeld(1);

  //Iron Axe
  chap.getUnitPointerAtSlot(4)->addItem(0x03);
  chap.getUnitPointerAtSlot(4)->setHeld(1);
}

void loop() {
  unsigned long startTime = millis();

  bool bUp = false;
  bool bDown = false;
  bool bLeft = false;
  bool bRight = false;
  bool bSelect = false;
  bool bBack = false;

  if (!debugMode) {
    String buffer = Serial.readString();

    int uCount = countCharInString(buffer, 'u');
    int dCount = countCharInString(buffer, 'd');
    int lCount = countCharInString(buffer, 'l');
    int rCount = countCharInString(buffer, 'r');
    int sCount = countCharInString(buffer, 's');
    int bCount = countCharInString(buffer, 'b');

    if (countCharInString(buffer, 'o') > 0)
      debugMode = true;

    bUp = uCount;
    bDown = dCount;
    bLeft = lCount;
    bRight = rCount;
    bSelect = sCount;
    bBack = bCount;
  }

  gameLogicLoop(Input(bSelect, bBack, bLeft, bRight, bUp, bDown));
  gameGraphicLoop();

  animationRoutine();

  tft.setCursor(0, tftHeight - 16, 2);

  tft.setTextFont(1);

  int timeT = millis() - startTime;

  tft.print(timeT);

  tft.print("  |  ");

  tft.print(1.0 / (timeT / 1000.0));
  delay(100);
}

void animationRoutine()
{
  unsigned long currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis - animationTimer >= animationDelay)  //test whether the period has elapsed
  {
    if (animationState + 1 == maxAnimationState)
      animationState = 0; else animationState++;
    animationTimer = currentMillis;  //IMPORTANT to save the start time of the current LED state.
  }
}

int unitSpriteDownPerState(byte state) {
  if (state == 0) return unitSpriteDown0;
  if (state == 1) return unitSpriteDown1;
  if (state == 2) return unitSpriteDown2;
  if (state == 3) return unitSpriteDown3;
  if (state == 4) return unitSpriteDown0;
  if (state == 5) return unitSpriteDown1;
  if (state == 6) return unitSpriteDown2;
  if (state == 7) return unitSpriteDown3;
  if (state == 8) return unitSpriteDown0;
  if (state == 9) return unitSpriteDown1;
  if (state == 10) return unitSpriteDown2;
  if (state == 11) return unitSpriteDown3;
}
