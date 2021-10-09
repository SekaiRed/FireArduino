#include "Enums.h"
#include "src/Sprites/SpriteHandler.h"
//#include "UtilityClasses.h"

extern TFT_eSPI tft;
extern Vector2 cursorPos;
extern Unit * selectedUnit;
extern byte gameState;
extern byte animationState;
extern ChapterInfo chap;
extern byte actRange [constMaxChapterSize][constMaxChapterSize];

Vector2 getCursorPosition()
{
  return cursorPos;
}

void resetActRange()
{
  for (int i = 0; i < constMaxChapterSize; i++)
  {
    for (int j = 0; j < constMaxChapterSize; j++)
    {
      actRange[i][j] = 0;
    }
  }
}

void homogenizeMovement() {
  for (int i = 0; i < constMaxChapterSize; i++)
  {
    for (int j = 0; j < constMaxChapterSize; j++)
    {
      if (actRange[i][j] != 0)
        actRange[i][j] = 1;
    }
  }
}

void getAttackRange(byte xPos, byte yPos, byte range) {
  byte verticalSize = 2 * range + 1;
  byte k = 1;
  for (int i = 0; i < verticalSize; i++)
  {
    for (int j = 0; j < k; j++)
    {
      byte x, y;

      x = xPos - ((k - 1) / 2) + j;
      y = yPos - range + i;

      if (x < chap.width && y < chap.height)
      {
        if (actRange[x][y] != 1)
          actRange[x][y] = 2;
      }
    }

    if (i < range)
      k += 2;
    else
      k -= 2;
  }
}

void getAllAttackRange(byte range)
{
  for (int i = 0; i < constMaxChapterSize; i++)
  {
    for (int j = 0; j < constMaxChapterSize; j++)
    {
      if (actRange[i][j] == 1)
        getAttackRange(i, j, range);
    }
  }
}

void trickleDownRange(byte xPos, byte yPos, byte step)
{
  actRange[xPos][yPos] = step;
  if (!chap.getIsBlock(Vector2(xPos - 1, yPos)) && step != 0 && xPos != 0) if (actRange[xPos - 1][yPos] < step) trickleDownRange(xPos - 1, yPos, step - 1); //left
  if (!chap.getIsBlock(Vector2(xPos + 1, yPos)) && step != 0 && xPos != chap.width - 1) if (actRange[xPos + 1][yPos] < step) trickleDownRange(xPos + 1, yPos, step - 1); //right
  if (!chap.getIsBlock(Vector2(xPos, yPos - 1)) && step != 0 && yPos != 0) if (actRange[xPos][yPos - 1] < step) trickleDownRange(xPos, yPos - 1, step - 1); //up
  if (!chap.getIsBlock(Vector2(xPos, yPos + 1)) && step != 0 && yPos != chap.height - 1) if (actRange[xPos][yPos + 1] < step) trickleDownRange(xPos, yPos + 1, step - 1); //down
}

void getActRange(byte xPos, byte yPos, byte movRange, byte attRange) {
  //void getMovementRange(int width, int arr[][width]) {
  trickleDownRange(xPos, yPos, movRange);
  homogenizeMovement();
  //getAttackRange(xPos, yPos, 2);
  getAllAttackRange(attRange);
}

void moveUpdate() {
  resetActRange();
  if (chap.checkIfUnitIsAt(cursorPos))
  {
    chap.getUnitPointerAtPos(cursorPos)->computeStats();
    Unit selectUnit = chap.getUnitAtPos(cursorPos);
    getActRange(selectUnit.getPos().x, selectUnit.getPos().y, selectUnit.getCoreStat(coreStatMovement), selectUnit.getHeldMaxRange());
  }
}

void cursorFreeMovement(Input input) {
  if (input.up && cursorPos.y != 0) {
    cursorPos = Vector2(cursorPos.x, cursorPos.y - 1);
    //moveUpdate();
  }
  if (input.left && cursorPos.x != 0) {
    cursorPos = Vector2(cursorPos.x - 1, cursorPos.y);
    //moveUpdate();
  }

  if (input.down && cursorPos.y != chap.height - 1) {
    cursorPos = Vector2(cursorPos.x, cursorPos.y + 1);
    //moveUpdate();
  }
  if (input.right && cursorPos.x != chap.width - 1) {
    cursorPos = Vector2(cursorPos.x + 1, cursorPos.y);
    //moveUpdate();
  }
}

void cursorLimitedMovement(Input input) {
  if (input.up && cursorPos.y != 0 && actRange[cursorPos.x][cursorPos.y - 1] == 1) {
    cursorPos = Vector2(cursorPos.x, cursorPos.y - 1);
    //moveUpdate();
  }
  if (input.left && cursorPos.x != 0 && actRange[cursorPos.x - 1][cursorPos.y] == 1) {
    cursorPos = Vector2(cursorPos.x - 1, cursorPos.y);
    //moveUpdate();
  }

  if (input.down && cursorPos.y != chap.height - 1 && actRange[cursorPos.x][cursorPos.y + 1] == 1) {
    cursorPos = Vector2(cursorPos.x, cursorPos.y + 1);
    //moveUpdate();
  }
  if (input.right && cursorPos.x != chap.width - 1 && actRange[cursorPos.x + 1][cursorPos.y] == 1) {
    cursorPos = Vector2(cursorPos.x + 1, cursorPos.y);
    //moveUpdate();
  }
}

int unitSpriteIdlePerState(byte state) {
  if (state == 0) return unitSpriteIdle0;
  if (state == 1) return unitSpriteIdle1;
  if (state == 2) return unitSpriteIdle2;
  if (state == 3) return unitSpriteIdle2;
  if (state == 4) return unitSpriteIdle1;
  if (state == 5) return unitSpriteIdle0;
  if (state == 6) return unitSpriteIdle0;
  if (state == 7) return unitSpriteIdle1;
  if (state == 8) return unitSpriteIdle2;
  if (state == 9) return unitSpriteIdle2;
  if (state == 10) return unitSpriteIdle1;
  if (state == 11) return unitSpriteIdle0;
}

void gameLogicLoop(Input input)//gameState
{
  if (gameState == GSselectionPhase)
  {
    cursorFreeMovement(input); //let the cursor move anywhere

    if (input.anyDirectionDown()) //if any direction are inputted, update the actrange
      moveUpdate();

    if (input.A && chap.checkIfUnitIsAt(cursorPos))
    {
      Unit * selectUnit = chap.getUnitPointerAtPos(cursorPos);
      if (selectUnit->team == 0 && !selectUnit->alreadyUsed)
      {
        selectedUnit = selectUnit;
        gameState = GSunitSelectedPhase;
        return;
      }
    }

    return; //return to avoid executing code from other GameStates
  }

  if (gameState == GSunitSelectedPhase)
  {
    cursorLimitedMovement(input); //let the cursor move anywhere

    if (input.A && chap.checkIfUnitIsAt(cursorPos))
    {

    }

    if (input.B)
    {
      cursorPos = selectedUnit->getPos();
      gameState = GSselectionPhase;
      return;
    }

    return; //return to avoid executing code from other GameStates
  }
}

void gameGraphicLoop()
{
  for (byte i = 0; i < chap.height; i++)
  {
    for (byte j = 0; j < chap.width; j++)
    {
      byte tileId = chap.getTileId(Vector2(i, j));

      drawSprite(i * tileSprSize, j * tileSprSize, getTileSprite(tileId), tilePalette, tileSprSize, tileSprSize, tft);
      
    }
  }

  for (byte i = 0; i < chap.height; i++)
  {
    for (byte j = 0; j < chap.width; j++)
    {
      if (chap.checkIfUnitIsAt(Vector2(i, j))) {
        Unit selectUnit = chap.getUnitAtPos(Vector2(i, j));
        drawSprite(i * tileSprSize, j * tileSprSize, getUnitSprite(selectUnit.unitClass, unitSpriteIdlePerState(animationState)), getUnitPalette(selectUnit.getPalette()), unitSprSize, unitSprSize, tft);
      }
    }
  }
}
