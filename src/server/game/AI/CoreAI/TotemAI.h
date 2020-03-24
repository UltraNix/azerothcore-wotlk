
#ifndef TRINITY_TOTEMAI_H
#define TRINITY_TOTEMAI_H

#include "CreatureAI.h"
#include "Timer.h"

class Creature;
class Totem;

class TotemAI : public CreatureAI
{
    public:

        explicit TotemAI(Creature* c);

        void MoveInLineOfSight(Unit* who);
        void AttackStart(Unit* victim);
        void EnterEvadeMode();
        void SpellHit(Unit* /*caster*/, const SpellInfo* /*spellInfo*/);
        void DoAction(int32 param);

        void UpdateAI(uint32 diff);
        static int Permissible(Creature const* creature);

    private:
        uint64 i_victimGuid;
};

class KillMagnetEvent : public BasicEvent
{
    public:
        KillMagnetEvent(Unit& self) : _self(self) { }
        bool Execute(uint64 e_time, uint32 p_time)
        {
            _self.setDeathState(JUST_DIED);
            return true;
        }

    protected:
        Unit& _self;
};

#endif

