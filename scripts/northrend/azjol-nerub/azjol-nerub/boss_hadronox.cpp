/* Copyright (C) 2006 - 2010 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: Boss_Hadronox
SD%Complete: 60%
SDComment: Just spells implementet; cosmetic mistakes  
SDCategory: Azjol'Nerub
EndScriptData */

#include "precompiled.h"
#include "azjol-nerub.h"

enum
{
    SPELL_LEECH_POISON              = 53030,
    SPELL_LEECH_POISON_H            = 59417,
    SPELL_ARMOR_PENETRATION         = 53418,
    SPELL_ACID_CLOUD                = 53400,
    SPELL_ACID_CLOUD_H              = 59419,
};

/*######
## boss_hadronox
######*/

struct MANGOS_DLL_DECL boss_hadronoxAI : public ScriptedAI
{
    boss_hadronoxAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 LeechPoisonTimer;
    uint32 ArmorPenetrationTimer;
    uint32 AcidCloudTimer;

    void Reset()
    {
        LeechPoisonTimer = 2000;
        ArmorPenetrationTimer = 4000;
        AcidCloudTimer = 6000;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (LeechPoisonTimer < uiDiff)
        {
            if (Unit* pVictim = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCastSpellIfCan(pVictim, m_bIsRegularMode ? SPELL_LEECH_POISON : SPELL_LEECH_POISON_H);

            LeechPoisonTimer = urand(12000, 13000);
        }else LeechPoisonTimer -= uiDiff;

        if (ArmorPenetrationTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_ARMOR_PENETRATION);
            ArmorPenetrationTimer = urand(12000, 22000);
        }else ArmorPenetrationTimer -= uiDiff;

        if (AcidCloudTimer < uiDiff)
        {
            if (Unit* pVictim = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCastSpellIfCan(pVictim, m_bIsRegularMode ? SPELL_ACID_CLOUD : SPELL_ACID_CLOUD_H);
            
            AcidCloudTimer = urand(11000, 12000);
        }else AcidCloudTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_hadronox(Creature* pCreature)
{
    return new boss_hadronoxAI(pCreature);
}

void AddSC_boss_hadronox()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_hadronox";
    newscript->GetAI = &GetAI_boss_hadronox;
    newscript->RegisterSelf();
}
