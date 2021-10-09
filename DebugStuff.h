//#include "ChapterInfo.h"

/*void debugDrawGrid(ChapterInfo chap)
{
  for (int i = 0; i < chap.height; i++)
  {
    for (int j = 0; j < chap.width; j++)
    {
      //if (getCursorPosition().equals(Vector2(j, i)))
      {
        if (checkIfUnitIsAt(Vector2(j, i))) Serial.print("X"); else Serial.print("O");
      }
      else
      {
        if (checkIfUnitIsAt(Vector2(j, i))) Serial.print("x"); else Serial.print("o");
      }
    }
    Serial.println("");
  }
}

void debugDrawCell()
{
  
}*/

/*bool simulatedButtonPress(String button)
  {
  while(Serial.available())
  }*/

/*void printBattleHandlerInfo(Unit unit1, Unit unit2)
  {
  BattleHandler btlHdl = BattleHandler(unit1, unit2);
  BattleHandlerInfo info = btlHdl.matchup();

  Serial.println("==================================");
  Serial.print("uAtt Atk "); Serial.println(info.attAtk);
  Serial.print("uAtt Hit "); Serial.println(info.attHit);
  Serial.print("uAtt Crt "); Serial.println(info.attCrt);
  Serial.print("uAtt Mult "); Serial.println(info.attMult);
  Serial.print("uAtt Wep "); Serial.println(unit1.getHeldItemBase().getName());
  Serial.println("");
  Serial.print("uDef Atk "); Serial.println(info.defAtk);
  Serial.print("uDef Hit "); Serial.println(info.defHit);
  Serial.print("uDef Crt "); Serial.println(info.defCrt);
  Serial.print("uDef Mult "); Serial.println(info.defMult);
  Serial.print("uDef Wep "); Serial.println(unit2.getHeldItemBase().getName());
  Serial.println("");
  }*/

/*void debugStuff(Unit &unit1)
{
  if (Serial.available() > 0) {
    // read the incoming byte:
    int incomingByte = Serial.read();

    if (incomingByte == 105) //i
    {
      String command = "";
      while (Serial.available() > 0)
      {
        command += (char)Serial.read();
      }
      byte val = command.toInt();
      if (val >= constInventorySize) val = constInventorySize;
      unit1.setHeld(val);
      Serial.print("Changed val for "); Serial.println(val);
    }
  }

  unit1.computeStats();

  Serial.print("Held ");
  Serial.println(unit1.invHold);
  Serial.print("Heldname ");
  Serial.println(unit1.getHeldItemBase().name);
  Serial.print("Might ");
  Serial.println(unit1.getCompStat(compStatMight));
  Serial.print("Hit ");
  Serial.println(unit1.getCompStat(compStatHit));
  Serial.print("Crit ");
  Serial.println(unit1.getCompStat(compStatCrit));
  delay(2000);
  //Serial.println(unit1.compStat[compStatHit]);
  //Serial.println(getItemByID(0x01).name);
  //Serial.println(getItemByID(unit1.getHeldItem()).name);
  //Serial.println(unit1.getHeldItemBase().name);
}*/
