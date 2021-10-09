//ItemClass
class ItemBase {
  private:
    byte might;
    byte hit;
    byte crit;
    byte dmgType;
    byte rangeMin;
    byte rangeMax;
    byte wepType;
  public:
    ItemBase(byte id, String name, byte sprite, byte might, byte hit, byte crit, byte dmgType, byte rangeMin, byte rangeMax, byte wepType, byte uses);
    ItemBase(byte id, String name, byte sprite, byte heal, byte uses);

    //general variables
    byte id;
    String name;
    byte sprite;
    byte itemType;
    byte uses;

    //weapon variables
    byte getMight();
    byte getHit();
    byte getCrit();
    byte getDmgType();
    byte getRngMin();
    byte getRngMax();
    byte getWeaponType();

    //consumable variables
    byte heal;
    byte getHeal();

    byte const getID();
    String getName();
    byte getSprite();
    byte getItemType();
    byte getUses();

    bool isWeapon();
    bool isConsumable();
};

ItemBase::ItemBase(byte id, String name, byte sprite, byte might, byte hit, byte crit, byte dmgType, byte rangeMin, byte rangeMax, byte wepType, byte uses)
{
  this->id = id;
  this->name = name;
  this->sprite = sprite;
  this->might = might;
  this->hit = hit;
  this->crit = crit;
  this->dmgType = dmgType;
  this->rangeMin = rangeMin;
  this->rangeMax = rangeMax;
  this->wepType = wepType;
  this->uses = uses;
  this->itemType = itemTypeWeapon;
}

ItemBase::ItemBase(byte id, String name, byte sprite, byte heal, byte uses)
{
  this->id = id;
  this->name = name;
  this->sprite = sprite;
  this->heal = heal;
  this->uses = uses;
  this->itemType = itemTypeConsumable;
}

//generic
byte const ItemBase::getID()
{
  return this->id;
}

String ItemBase::getName()
{
  return this->name;
}

byte ItemBase::getSprite()
{
  return this->sprite;
}

byte ItemBase::getItemType()
{
  return this->itemType;
}

byte ItemBase::getUses()
{
  return this->uses;
}

//weapon
byte ItemBase::getMight() {if(this->isWeapon()) return this->might; return 0;}
byte ItemBase::getHit() {if(this->isWeapon()) return this->hit;  return 0;}
byte ItemBase::getCrit() {if(this->isWeapon()) return this->crit;  return 0;}
byte ItemBase::getDmgType() {if(this->isWeapon()) return this->dmgType;  return wepDmgNormal;}
byte ItemBase::getRngMin() {if(this->isWeapon()) return this->rangeMin;  return 0;}
byte ItemBase::getRngMax() {if(this->isWeapon()) return this->rangeMax;  return 0;}
byte ItemBase::getWeaponType() {if(this->isWeapon()) return this->wepType;  return 0;}

//consumables
byte ItemBase::getHeal() {return this->heal;}

bool ItemBase::isWeapon()
{
  if(this->itemType == itemTypeWeapon) return true;
  return false;
}

bool ItemBase::isConsumable()
{
  if(this->itemType == itemTypeConsumable) return true;
  return false;
}
//////////////////

/*WeaponAttributesClass
class Attributes {
  private:
    byte might;
    byte hit;
  public:
    Attributes();
};
//////////////

Attributes::Attributes() {
  
}*/

enum AttributesEnum {
  set_dmg_type,
  add_might
};
