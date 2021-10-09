#define ItemDBCount 12

extern const unsigned char nullSpr[];
extern const unsigned char ironSwordSpr[];
extern const unsigned char ironAxeSpr[];
extern const unsigned char ironSpearSpr[];
extern const unsigned char ironBowSpr[];
extern const unsigned char fireSpr[];
extern const unsigned char megidolaonSpr[];
extern const unsigned char kougahonSpr[];
extern const unsigned char eigaonSpr[];

//common words
String s_Iron = "Iron";

ItemBase ItemDatabase[ItemDBCount] =
{
  ItemBase(0x01, s_Iron + " Sword", 0x01, 9, 90, 0, wepDmgNormal, 1, 1, wepTypeSword,40),
  ItemBase(0x02, s_Iron + " Spear", 0x03, 7, 100, 0, wepDmgNormal, 1, 1, wepTypeSpear,30),
  ItemBase(0x03, s_Iron + " Axe", 0x02, 11, 80, 0, wepDmgNormal, 1, 1, wepTypeAxe,50),
  ItemBase(0x04, s_Iron + " Bow", 0x04, 7, 75, 0, wepDmgNormal, 1, 2, wepTypeBow,30),
  ItemBase(0x05, "Fire", 0x05, 4, 90, 0, wepDmgSpecial, 1, 2, wepTypeTome,20),
  ItemBase(0x06, "Eigaon", 0x08, 2, 70, 30, wepDmgSpecial, 1, 3, wepTypeTome,15),
  ItemBase(0x07, "Kougahon", 0x07, 6, 80, 10, wepDmgSpecial, 1, 2, wepTypeTome,10),
  ItemBase(0x08, "Megido", 0x06, 22, 100, 0, wepDmgSpecial, 1, 1, wepTypeTome,5),
  ItemBase(0x09, "Megidolaon", 0x06, 54, 200, 0, wepDmgSpecial, 1, 1, wepTypeTome,5),
  ItemBase(0x0A, "Maeigaon", 0x08, 1, 60, 10, wepDmgSpecial, 1, 4, wepTypeTome,25),
  ItemBase(0x0B, "Vorpal Blade", 0x01, 17, 80, 0, wepDmgSpecial, 1, 1, wepTypeSword,10),//does magic damage
  ItemBase(0x10, "Vulnerary", 0x00, 10, 3)
};

ItemBase getItemByID(byte id)
{
  for(int i = 0; i < ItemDBCount; i++)
    if(ItemDatabase[i].getID() == id)
      return ItemDatabase[i];
  return ItemBase(0x00, "null", 0, 1, 1);
}
