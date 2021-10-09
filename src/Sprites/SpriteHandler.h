#define itemSprSize 16
#define tileSprSize 16
#define unitSprSize 32

#include "Unit/ErikaOverworld.h"
#include "Unit/ArcherOverworld.h"
#include "Unit/MageOverworld.h"
#include "Unit/LumberOverworld.h"
#include "Unit/ClericOverworld.h"

#include "Tile/Grass.h"
#include "Tile/Trees.h"

#include "Item/IronSword.h"
#include "Item/IronAxe.h"
#include "Item/IronSpear.h"
#include "Item/IronBow.h"
#include "Item/Fire.h"
#include "Item/Megidolaon.h"
#include "Item/Kougahon.h"
#include "Item/Eigaon.h"
#include "Item/Empty.h"

#include "HUD/Cursor.h"

const unsigned int playerUnitPallet[] = {
  0xF81F,
  0x5A4F,
  0x95DD,
  0xDF5E,
  0x730C,
  0xB48B,
  0xFFDA,
  0x39D2,
  0x3A9C,
  0x2D1F,
  0x1F9F,
  0xE883,
  0xFFC8,
  0x844E,
  0xFFDF,
  0x41C7
};

const unsigned int enemyUnitPallet[] = {
  0xF81F,
  0x6A4C,
  0xC557,
  0xE71C,
  0x730C,
  0xB48B,
  0xFFDA,
  0x6144,
  0xA985,
  0xE082,
  0xFA89,
  0x3E86,
  0xFFC8,
  0x844E,
  0xFFDF,
  0x41C7
};

const unsigned int allyUnitPallet[] = {
  0xF81F,
  0x3A87,
  0x9E50,
  0xDFD7,
  0x5ACA,
  0xA448,
  0xFFD8,
  0x2282,
  0x0C80,
  0x1E82,
  0x57C7,
  0x03D9,
  0xE7C5,
  0x844E,
  0xFFDF,
  0x3A07
};

const unsigned int usedUnitPallet[] = {
  0xF81F,
  0x4208,
  0x7BCF,
  0xBDD7,
  0x528A,
  0x8410,
  0xCE59,
  0x4A49,
  0x5ACB,
  0x9CD3,
  0xBDD7,
  0x738E,
  0xCE59,
  0x844E,
  0xD69A,
  0x41C7
};

const unsigned int tilePalette[] = {
  0x9F4C,
  0xAFD7,
  0x9F0C,
  0xBFCC,
  0xDFD8,
  0xD7CF,
  0x7FD0,
  0x87D6,
  0xB7CD,
  0x9E4F,
  0x6E13,
  0x6F5D,
  0x8C5A,
  0x74CB,
  0xFFFF,
  0xFFFF
};

const unsigned int itemPalette[] = {
  0xF81F,
  0x7286,
  0x51C8,
  0x6E57,
  0x29C4,
  0x2C0C,
  0xB59A,
  0xFFDF,
  0xCE17,
  0x9C0E,
  0xC300,
  0xA041,
  0xDE84,
  0x9490,
  0x73D2,
  0x3A9E
};

enum UnitFrame {
	Idle0,
	Idle1,
	Idle2
};

//Units
const unsigned int * getUnitPalette(byte paletteState)
{
	if (paletteState == 0) return &usedUnitPallet[0];
	if (paletteState == 1) return &playerUnitPallet[0];
	if (paletteState == 2) return &enemyUnitPallet[0];
	if (paletteState == 3) return &allyUnitPallet[0];
}

const unsigned char * getUnitSprite(byte id, byte frame)
{
	if (id == 0x01) {
		if (frame == unitSpriteIdle0) return &erikaIdle0Spr[0];
		if (frame == unitSpriteIdle1) return &erikaIdle1Spr[0];
		if (frame == unitSpriteIdle2) return &erikaIdle2Spr[0];
		if (frame == unitSpriteDown0) return &erikaDown0Spr[0];
		if (frame == unitSpriteDown1) return &erikaDown1Spr[0];
		if (frame == unitSpriteDown2) return &erikaDown2Spr[0];
		if (frame == unitSpriteDown3) return &erikaDown3Spr[0];
	}
	if (id == 0x02) {
		if (frame == unitSpriteIdle0) return &archerIdle0Spr[0];
		if (frame == unitSpriteIdle1) return &archerIdle1Spr[0];
		if (frame == unitSpriteIdle2) return &archerIdle2Spr[0];
		if (frame == unitSpriteDown0) return &archerDown0Spr[0];
		if (frame == unitSpriteDown1) return &archerDown1Spr[0];
		if (frame == unitSpriteDown2) return &archerDown2Spr[0];
		if (frame == unitSpriteDown3) return &archerDown3Spr[0];
	}
	if (id == 0x03) {
		if (frame == unitSpriteIdle0) return &mageIdle0Spr[0];
		if (frame == unitSpriteIdle1) return &mageIdle1Spr[0];
		if (frame == unitSpriteIdle2) return &mageIdle2Spr[0];
	}
	if (id == 0x04) {
		if (frame == unitSpriteIdle0) return &lumberIdle0Spr[0];
		if (frame == unitSpriteIdle1) return &lumberIdle1Spr[0];
		if (frame == unitSpriteIdle2) return &lumberIdle2Spr[0];
	}
	if (id == 0x05) {
		if (frame == unitSpriteIdle0) return &clericIdle0Spr[0];
		if (frame == unitSpriteIdle1) return &clericIdle1Spr[0];
		if (frame == unitSpriteIdle2) return &clericIdle2Spr[0];
		if (frame == unitSpriteDown0) return &clericDown0Spr[0];
		if (frame == unitSpriteDown1) return &clericDown1Spr[0];
		if (frame == unitSpriteDown2) return &clericDown2Spr[0];
		if (frame == unitSpriteDown3) return &clericDown3Spr[0];
	}
	return &erikaIdle0Spr[0];
}

//Tiles
const unsigned char * getTileSprite(byte id)
{
	if (id == 0x00) return &tileGrass[0];
	if (id == 0x01) return &tileTrees[0];
	return &tileGrass[0];
}

//Items
const unsigned char * getItemSprite(byte id)
{
	if (id == 0x00) return &nullSpr[0];
	if (id == 0x01) return &ironSwordSpr[0];
	if (id == 0x02) return &ironAxeSpr[0];
	if (id == 0x03) return &ironSpearSpr[0];
	if (id == 0x04) return &ironBowSpr[0];
	if (id == 0x05) return &fireSpr[0];
	if (id == 0x06) return &megidolaonSpr[0];
	if (id == 0x07) return &kougahonSpr[0];
	if (id == 0x08) return &eigaonSpr[0];
	return &nullSpr[0];
}

//HUD
const unsigned char * getCursorSprite(byte frame)
{
	/*if (frame == 0) return &cursor0Spr[0];
	if (frame == 1) return &cursor1Spr[0];
	if (frame == 2) return &cursor2Spr[0];
	if (frame == 3) return &cursor2Spr[0];
	if (frame == 4) return &cursor1Spr[0];
	if (frame == 5) return &cursor0Spr[0];*/
	if (frame == 0) return &cursorBlue0Spr[0];
	if (frame == 1) return &cursorBlue0Spr[0];
	if (frame == 2) return &cursorBlue0Spr[0];
	if (frame == 3) return &cursorBlue1Spr[0];
	if (frame == 4) return &cursorBlue1Spr[0];
	if (frame == 5) return &cursorBlue1Spr[0];
	if (frame == 6) return &cursorBlue0Spr[0];
	if (frame == 7) return &cursorBlue0Spr[0];
	if (frame == 8) return &cursorBlue0Spr[0];
	if (frame == 9) return &cursorBlue1Spr[0];
	if (frame == 10) return &cursorBlue1Spr[0];
	if (frame == 11) return &cursorBlue1Spr[0];
	return &cursorBlue0Spr[0];
}