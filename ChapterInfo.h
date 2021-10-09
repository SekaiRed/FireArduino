//ChapterInfo
class ChapterInfo {
  public:
    ChapterInfo();
    ChapterInfo(int width, int height, byte colData[constMaxChapterSize][constMaxChapterSize]);
    //ChapterInfo(int width, int height, byte colData[constMaxChapterSize][constMaxChapterSize], Unit unitList [constMaxUnitPerMap]);
    byte getTileId(Vector2 pos);
    bool getIsBlock(Vector2 pos);
    bool checkIfUnitIsAt(Vector2 pos);
    Unit getUnitAtPos(Vector2 pos);
    Unit * getUnitPointerAtPos(Vector2 pos);
    Unit getUnitAtSlot(byte slot);
    Unit * getUnitPointerAtSlot(byte slot);
    bool addUnit(Unit unit);
    void removeUnit(byte slot);
    byte width;
    byte height;
    byte colData [constMaxChapterSize][constMaxChapterSize];
    Unit unitList [constMaxUnitPerMap]; //list of units
    byte unitCount; //how many units are there
};

ChapterInfo::ChapterInfo(){}

ChapterInfo::ChapterInfo(int width, int height, byte colData[constMaxChapterSize][constMaxChapterSize])
{
  this->width = width;
  this->height = height;
  //this->colData = *colData;
  for (int i = 0; i < width; i++)
  {
    for (int j = 0; j < height; j++)
    {
      this->colData[i][j] = colData[i][j];
    }
  }
}

/*ChapterInfo::ChapterInfo(int width, int height, byte colData[constMaxChapterSize][constMaxChapterSize], Unit unitList [constMaxUnitPerMap])
{
  this->width = width;
  this->height = height;
  //this->colData = *colData;
  for (int i = 0; i < width; i++)
  {
    for (int j = 0; j < height; j++)
    {
      this->colData[i][j] = colData[i][j];
    }
  }
  for (int o = 0; o < unitCount; o++)
  {
    this->unitList[o] = unitList[o];
  }
}*/

byte ChapterInfo::getTileId(Vector2 pos)
{
  if (pos.x >= width || pos.y >= height)
    return 0; //invalid id

  return colData[pos.x][pos.y];
}

bool ChapterInfo::getIsBlock(Vector2 pos)
{
  if (pos.x >= width || pos.y >= height)
    return false; //invalid vector

  byte tileData = colData[pos.x][pos.y];

  if (tileData == 0)
    return false;
  if (tileData == 1)
    return true;

  return false;
}

bool ChapterInfo::checkIfUnitIsAt(Vector2 pos)
{
  for (int i = 0; i < this->unitCount; i++)
    if (pos.x == this->unitList[i].getPos().x && pos.y == this->unitList[i].getPos().y)
      return true;
  return false;
}

Unit ChapterInfo::getUnitAtPos(Vector2 pos)
{
  for (int i = 0; i < this->unitCount; i++)
    if (pos.x == this->unitList[i].getPos().x && pos.y == this->unitList[i].getPos().y)
      return this->unitList[i];
  return Unit();
}

Unit* ChapterInfo::getUnitPointerAtPos(Vector2 pos)
{
  for (int i = 0; i < this->unitCount; i++)
    if (pos.x == this->unitList[i].getPos().x && pos.y == this->unitList[i].getPos().y)
      return &unitList[i];
  //return *Unit();
}

Unit ChapterInfo::getUnitAtSlot(byte slot)
{
  if(slot < unitCount)
  {
    return this->unitList[slot];
  }

  return Unit();
}

Unit* ChapterInfo::getUnitPointerAtSlot(byte slot)
{
  if(slot < unitCount)
  {
    return &unitList[slot];
  }

  //return &Unit();
}

bool ChapterInfo::addUnit(Unit unit)
{
  if(unitCount < constMaxUnitPerMap)
  {
    unitList[unitCount] = unit;
    unitCount++;
    return true;
  }

  return false;
}

void ChapterInfo::removeUnit(byte slot)
{
  if(slot < unitCount)
  {
    for(int i = 0; i < constMaxUnitPerMap; i++)
    {
      if(i >= slot)
      {
        if(i != constMaxUnitPerMap - 1)
        unitList[i] = unitList[i+1];
        else
        unitList[i] = Unit();
      }
    }

    unitCount--;
  }
}
//////////////////
