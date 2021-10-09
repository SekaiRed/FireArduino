//BattleHandlerInfo
class BattleHandlerInfo {
  public:
    BattleHandlerInfo(byte attAtk, byte attHit, byte attCrt, byte attMult, byte defAtk, byte defHit, byte defCrt, byte defMult);
    byte attAtk; byte attHit; byte attCrt; byte attMult; byte defAtk; byte defHit; byte defCrt; byte defMult;
};

BattleHandlerInfo::BattleHandlerInfo(byte attAtk, byte attHit, byte attCrt, byte attMult, byte defAtk, byte defHit, byte defCrt, byte defMult)
{
  this->attAtk = attAtk;
  this->attHit = attHit;
  this->attCrt = attCrt;
  this->attMult = attMult;
  this->defAtk = defAtk;
  this->defHit = defHit;
  this->defCrt = defCrt;
  this->defMult = defMult;
}
//////////////////

//BattleHandler
class BattleHandler {
  private:
    Unit uAtt;
    Unit uDef;
  public:
    BattleHandler(Unit &uAtt, Unit &uDef);//only copies
    BattleHandlerInfo matchup();//return a battlehandlerinfo
};

BattleHandler::BattleHandler(Unit &uAtt, Unit &uDef)
{
  this->uAtt = uAtt;
  this->uDef = uDef;
}

BattleHandlerInfo BattleHandler::matchup()
{
  byte attAtk; byte attHit; byte attCrt; byte attMult; byte defAtk; byte defHit; byte defCrt; byte defMult;

  byte dist = getStreetDistance(uAtt.getPos(), uDef.getPos());

  //attacker
  if (uAtt.getHeldItemBase().getWeaponType() != wepTypeTome)
    attAtk = cappedMinus(uAtt.getCompStat(compStatMight), uDef.getCompStat(compStatProtection));
  else
    attAtk = cappedMinus(uAtt.getCompStat(compStatMight), uDef.getCompStat(compStatResilience));

  attHit = cappedMinus(uAtt.getCompStat(compStatHit), uDef.getCompStat(compStatAvoid));

  attCrt = cappedMinus(uAtt.getCompStat(compStatCrit), uDef.getCompStat(compStatCritAvoid));

  if (uAtt.getCompStat(compStatAttackSpeed) > uDef.getCompStat(compStatAttackSpeed) + 5) attMult = 2;
  else attMult = 1;

  if(!checkIfByteWithinBound(dist, uAtt.getHeldItemBase().getRngMin(), uAtt.getHeldItemBase().getRngMax()))
  attMult = 0;

  //defender
  if (uDef.getHeldItemBase().getWeaponType() != wepTypeTome)
    defAtk = cappedMinus(uDef.getCompStat(compStatMight), uAtt.getCompStat(compStatProtection));
  else
    defAtk = cappedMinus(uDef.getCompStat(compStatMight), uAtt.getCompStat(compStatResilience));

  defHit = cappedMinus(uDef.getCompStat(compStatHit), uAtt.getCompStat(compStatAvoid));

  defCrt = cappedMinus(uDef.getCompStat(compStatCrit), uAtt.getCompStat(compStatCritAvoid));

  if (uDef.getCompStat(compStatAttackSpeed) > uAtt.getCompStat(compStatAttackSpeed) + 5) defMult = 2;
  else defMult = 1;

  if(!checkIfByteWithinBound(dist, uDef.getHeldItemBase().getRngMin(), uDef.getHeldItemBase().getRngMax()))
  defMult = 0;

  return BattleHandlerInfo(attAtk, attHit, attCrt, attMult, defAtk, defHit, defCrt, defMult);;
}
//////////////////
