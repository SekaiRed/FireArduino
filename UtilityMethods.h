#include <TFT_eSPI.h>

unsigned int getColor(byte id, const unsigned int palette[]) {
  if (id >= 16) return 0x0000;
  return palette[id];
}

void drawSprite(int x, int y, const unsigned char sprite[], const unsigned int palette[], int sprWidth, int sprHeight, TFT_eSPI tft) {
  for (int j = 0; j < sprHeight; j++)
  {
    for (int i = 0; i < sprWidth; i++)
    {
      if ((i & 0x01) == 0)
      {
        if(getColor((sprite[i / 2 + (j * sprWidth) / 2] & 0xF0) >> 4, palette) != 0xF81F)
        tft.drawPixel(i + x, j + y, getColor((sprite[i / 2 + (j * sprWidth) / 2] & 0xF0) >> 4, palette)); //even
      }
      else
      {
        if(getColor(sprite[i / 2 + (j * sprWidth) / 2] & 0x0F, palette) != 0xF81F)
        tft.drawPixel(i + x, j + y, getColor(sprite[i / 2 + (j * sprWidth) / 2] & 0x0F, palette)); //odd
      }
    }
  }
}

int getStreetDistance(Vector2 pos1, Vector2 pos2)
{
  byte aX = pos1.x; byte aY = pos1.y; byte bX = pos2.x; byte bY = pos2.y;
  byte xCount = 0;
  byte yCount = 0;

  while(aX!=bX)
  {
    if(aX < bX) bX--;
    if(aX > bX) bX++;
    xCount+=1;
  }

  while(aY!=bY)
  {
    if(aY < bY) bY--;
    if(aY > bY) bY++;
    yCount+=1;
  }

  return xCount + yCount;
}

bool checkIfByteWithinBound(byte val, byte min, byte max)
{
  if(val>=min && val<=max) return true;
  return false;
}

byte cappedMinus(byte a, byte b)//a - b
{
  if(b>a)
  return 0;
  return a-b;
}

int countCharInString(String str, char ch)
{
  int count = 0;
  int i;
  
  int length = str.length();

    for (i = 0; i < length; i++)
    {
        if (str[i] == ch)
        {
            count++;
        }
    }

    return count;
}
