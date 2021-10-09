//InventoryClass
class InvSlot {
  public:
    InvSlot();
    byte id;
    byte uses;
    bool empty;
    void Add(byte id, byte uses);
    void ClearSlot();
};

InvSlot::InvSlot()
{
  this->id = 0x00;
  this->uses = 0;
  this->empty = true;
}

void InvSlot::Add(byte id, byte uses)
{
  this->id = id;
  this->uses = uses;
  this->empty = false;
}

void InvSlot::ClearSlot()
{
  this->empty = true;
}
//////////////////

extern ItemBase getItemByID(byte id);
extern const unsigned char nullSpr[];

//UnitClass
class Unit {

  public:
    Unit();
    Unit(String name, byte unitStat[coreStatAmount], byte team, byte unitClass, byte X, byte Y);
    byte getCoreStat(byte stat);
    byte getCompStat(byte stat);
    Vector2 getPos();
    String getName();
    void computeStats();
    bool addItem(byte id); //will return false if inventory is full, if uses is 255 then it defaults to the original one
    void removeItem(byte slot); //
    byte inventoryCount();
    byte getHeldItem();
    ItemBase getHeldItemBase();
    byte getItem(byte slot);
    void setHeld(byte slot);
    byte getHeldMaxRange();
    byte getPalette();

    byte coreStat[coreStatAmount]; //str,mag,skl,spd,lck,def,res,mov,maxHp // core stats
    byte compStat[compStatAmount]; //Might,Hit,Crit,Avoid,CritAvoid,AS,prt,rsl // computed stats
    InvSlot inv[constInventorySize]; //inventory
    byte invHold; //current held item, 0 is none, can only be a weapon
    String name; //unit's name
    byte team; //curent team 0 player / 1 enemy / 2 ally / 3 other enemy
    byte unitClass; //class of this unit, only determines it's sprite for now
    byte level; //current level
    byte xp; //xp from 0 to 99
    byte xPos; //X position
    byte yPos; //Y position
    bool alreadyUsed; //wether this unit already moved or not
};

Unit::Unit()
{
}

Unit::Unit(String name, byte unitStat[coreStatAmount], byte team, byte unitClass, byte X, byte Y)
{
  for (int i = 0; i < coreStatAmount; i++)
    this->coreStat[i] = unitStat[i];

  for (int i = 0; i < constInventorySize; i++)
    this->inv[i] = InvSlot();

  //inv[0].Add(0x02, 50);

  this->name = name;
  this->xPos = X;
  this->yPos = Y;
  this->team = team;
  this->unitClass = unitClass;
}

bool Unit::addItem(byte id)
{
  int i = 0;
  while (i < constInventorySize)
  {
    if (inv[i].empty) {
      inv[i].Add(id, 20);
      return true;
    }
    i++;
  }
  return false;
  //inv[0].Add(0x01, 20);
}

void Unit::removeItem(byte slot)//1,2,3,4,5,6
{
  byte invCount = this->inventoryCount();

}

byte Unit::inventoryCount()
{
  byte invCount = 0;
  for (int i = 0; i < constInventorySize; i++)
  {
    if (!inv[i].empty) invCount += 1;
  }
  return invCount;
}

byte Unit::getHeldItem()
{
  if (!inv[invHold - 1].empty) return inv[invHold - 1].id;
  return 0x00;
}

ItemBase Unit::getHeldItemBase()
{
  if (!inv[invHold - 1].empty) return getItemByID(inv[invHold - 1].id);
  return ItemBase(0x00, "null", 0, 1, 1);
}

byte Unit::getItem(byte slot)
{
  if (!inv[slot - 1].empty) return inv[slot].id;
  return 0x00;
}

void Unit::setHeld(byte slot)
{
  if (slot == 0) {
    invHold = 0;
  }
  else
  {
    if (!inv[slot - 1].empty && getItemByID(inv[slot - 1].id).isWeapon() && slot<=inventoryCount()) invHold = slot;
  }
}

byte Unit::getHeldMaxRange()
{
  return getHeldItemBase().getRngMax();
}

byte Unit::getCoreStat(byte myStat)
{
  if(myStat<coreStatAmount)
  return this->coreStat[myStat];
  return 0;
}

byte Unit::getCompStat(byte myStat)
{
  if(myStat<compStatAmount)
  return this->compStat[myStat];
  return 0;
  //return this->compStat[myStat];
}

Vector2 Unit::getPos()
{
  return Vector2(this->xPos, this->yPos);
}

String Unit::getName()
{
  return name;
}

byte Unit::getPalette()
{
  if(alreadyUsed) return 0;
  if(team == 3) return 1;
  return team+1;
}

void Unit::computeStats()
{
  ItemBase wep = this->getHeldItemBase();
  
  if(wep.getDmgType() == wepDmgNormal)
  this->compStat[compStatMight] = this->getCoreStat(coreStatStrength) + wep.getMight();
  if(wep.getDmgType() == wepDmgSpecial)
  this->compStat[compStatMight] = this->getCoreStat(coreStatMagic) + wep.getMight();
  
  this->compStat[compStatHit] = (this->getCoreStat(coreStatSkill) * 3 + this->getCoreStat(coreStatLuck)) / 2 + wep.getHit();
  this->compStat[compStatCrit] = this->getCoreStat(coreStatSkill) / 2 + wep.getCrit();
  this->compStat[compStatAvoid] = (this->getCoreStat(coreStatSpeed) * 3 + this->getCoreStat(coreStatLuck)) / 2;
  this->compStat[compStatCritAvoid] = this->getCoreStat(coreStatLuck);
  this->compStat[compStatAttackSpeed] = this->getCoreStat(coreStatSpeed);
  this->compStat[compStatProtection] = this->getCoreStat(coreStatDefense);
  this->compStat[compStatResilience] = this->getCoreStat(coreStatResistance);

  /*this->compStat[compStatMight] = wep.getMight();
  this->compStat[compStatHit] = wep.getHit();
  this->compStat[compStatCrit] = wep.getCrit();*/

  /*this->compStat[compStatMight] = this->getCoreStat(coreStatStrength);
  this->compStat[compStatHit] = (this->getCoreStat(coreStatSkill) * 3 + this->getCoreStat(coreStatLuck)) / 2;
  this->compStat[compStatCrit] = this->getCoreStat(coreStatSkill) / 2;*/
  //if(bruh) this->compStat[compStatMight] = 144;
}
//////////////////
