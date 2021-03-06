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
SDName: Boss_Anomalus
SD%Complete: 50%
SDComment: TODO: remove hacks, add support for rift charging
SDCategory: Nexus
EndScriptData */

#include "precompiled.h"
#include "nexus.h"

enum
{
    SAY_AGGRO                          = -1576006,
    SAY_RIFT                           = -1576007,
    SAY_SHIELD                         = -1576008,
    SAY_KILL                           = -1576009,
    SAY_DEATH                          = -1576010,
    EMOTE_OPEN_RIFT                    = -1576021,
    EMOTE_SHIELD                       = -1576022,

    // Anomalus
    SPELL_CREATE_RIFT                  = 47743,
    SPELL_CHARGE_RIFT                  = 47747,
    SPELL_RIFT_SHIELD                  = 47748,

    SPELL_SPARK                        = 47751,
    SPELL_SPARK_H                      = 57062,

    SPELL_ARCANE_FORM                  = 48019,

	SPELL_BERSERK			           = 26662,
    // Chaotic Rift
    SPELL_RIFT_AURA                    = 47687,
    SPELL_RIFT_SUMMON_AURA             = 47732,

    // Charged Chaotic Rift
    SPELL_CHARGED_RIFT_AURA            = 47733,
    SPELL_CHARGED_RIFT_SUMMON_AURA     = 47742,

    SPELL_SUMMON_CRAZED_MANA_WRAITH    = 47692,
    NPC_CHAOTIC_RIFT                   = 26918,
    NPC_CRAZED_MANA_WRAITH             = 26746,

    ACHIEVEMENT_CHAOS_THEORY           = 2037
};

const float spawnRiftPos[6][4] =
{
    {651.117859f, -297.122864f, -9.365547f, 2.490881f},
	{639.771423f, -313.002563f, -9.475847f, 1.706268f},
    {626.450684f, -305.178284f, -9.443430f, 0.944431f},
    {620.875549f, -281.674042f, -9.030414f, 5.905006f},
	{634.398743f, -266.216400f, -8.448195f, 4.909906f},
    {652.564819f, -273.689362f, -8.751000f, 3.887317f}
};

#define BERSERK_Z_POS		    -12.0f

/*######
## boss_anomalus
######*/

struct MANGOS_DLL_DECL boss_anomalusAI : public ScriptedAI
{
    boss_anomalusAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    bool   m_bChaoticRift;
    bool   m_briftActive;
	bool   m_bisInBerserk;
    uint32 m_uiSparkTimer;
    uint32 m_uiCreateRiftTimer;
    uint64 m_uiChaoticRiftGUID;
	uint32 m_uiBerserkCheckTimer;
    bool   m_bRiftKilled;

    std::list<uint64> m_uiRiftGUIDList;

    void Reset()
    {
        m_bChaoticRift = false;
        m_briftActive = false;
		m_bisInBerserk = false;
        m_uiSparkTimer = 5000;
        m_uiCreateRiftTimer = 25000;
        m_uiChaoticRiftGUID = 0;
		m_uiBerserkCheckTimer = 6000;
        m_bRiftKilled = false;

        DespawnRifts();
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);
    }

    void JustDied(Unit* pKiller)
    {  
        DoScriptText(SAY_DEATH, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_ANOMALUS, DONE);

        if(m_bRiftKilled || m_bIsRegularMode)
            return;

        Map* pMap = m_creature->GetMap();
        if (pMap)
        {
            Map::PlayerList const &players = pMap->GetPlayers();
            for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                itr->getSource()->CompletedAchievement(ACHIEVEMENT_CHAOS_THEORY);
        }

		DespawnRifts();
    }

    void KilledUnit(Unit* pVictim)
    {
        if (urand(0, 1))
            DoScriptText(SAY_KILL, m_creature);
    }

    void JustSummoned(Creature* pSummoned)
    {
        if (pSummoned->GetEntry() == NPC_CHAOTIC_RIFT)
        {
            DoScriptText(SAY_RIFT, m_creature);

            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                pSummoned->AI()->AttackStart(pTarget);
        }
    }

    void SummonedCreatureDespawn(Creature* pSummoned)
    {
        if (pSummoned->GetEntry() == NPC_CHAOTIC_RIFT)
        {
            if (m_creature->HasAura(SPELL_RIFT_SHIELD))
                m_creature->RemoveAurasDueToSpell(SPELL_RIFT_SHIELD);

            m_uiChaoticRiftGUID = 0;
            m_briftActive = false;
        }
    }

    uint64 CreateRiftAtRandomPoint()
    {
        int randPos = urand(0, 5);

        Creature* pRift = NULL;

        if (pRift = m_creature->SummonCreature(NPC_CHAOTIC_RIFT, spawnRiftPos[randPos][0], spawnRiftPos[randPos][1], spawnRiftPos[randPos][2], spawnRiftPos[randPos][3], TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 1000))
        {
            DoScriptText(EMOTE_OPEN_RIFT, m_creature);
            m_uiRiftGUIDList.push_back(pRift->GetGUID());
        }

        return pRift?pRift->GetGUID():0;
    }

    void DespawnRifts()
    {
        if (!m_uiRiftGUIDList.empty() && m_pInstance)
        {
            for(std::list<uint64>::iterator itr = m_uiRiftGUIDList.begin(); itr != m_uiRiftGUIDList.end(); ++itr)
            {
                if (Creature* pRift = m_pInstance->instance->GetCreature(*itr))
                {
                    if (pRift->isAlive())
                        pRift->ForcedDespawn();
                }
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim() || m_creature->HasAura(SPELL_RIFT_SHIELD))
             return;
		
		if (!m_bisInBerserk)
		{
			if (m_uiBerserkCheckTimer < uiDiff)
			{
				if (m_creature->GetPositionZ() < BERSERK_Z_POS)
					DoCastSpellIfCan(m_creature, SPELL_BERSERK);

				m_bisInBerserk = true;
				m_uiBerserkCheckTimer = 2000;
			}else m_uiBerserkCheckTimer -= uiDiff;
		}

        // Create additional Chaotic Rift at 50% HP
        if (!m_bChaoticRift && m_creature->GetHealthPercent() < 50.0f)
        {
            DoScriptText(EMOTE_SHIELD, m_creature);
            m_uiChaoticRiftGUID = CreateRiftAtRandomPoint();

            DoScriptText(SAY_SHIELD, m_creature);
            DoCastSpellIfCan(m_creature, SPELL_RIFT_SHIELD);
            m_bChaoticRift = true;
            return;
        }
        
        if (!m_briftActive)
        {
            if (m_uiCreateRiftTimer < uiDiff)
            {
                CreateRiftAtRandomPoint();
                if (!urand(0, 1))
                    DoScriptText(SAY_SHIELD, m_creature);

                DoScriptText(EMOTE_SHIELD, m_creature);
                DoCastSpellIfCan(m_creature, SPELL_RIFT_SHIELD);
                m_briftActive = true;
                m_uiCreateRiftTimer = 25000;
            }else m_uiCreateRiftTimer -= uiDiff;
        }

        if (m_uiSparkTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCastSpellIfCan(pTarget, m_bIsRegularMode ? SPELL_SPARK : SPELL_SPARK_H);

            m_uiSparkTimer = 5000;
        }else m_uiSparkTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_anomalus(Creature* pCreature)
{
    return new boss_anomalusAI(pCreature);
}

struct MANGOS_DLL_DECL mob_chaotic_riftAI : public Scripted_NoMovementAI
{
    mob_chaotic_riftAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    uint32 m_uiSummonTimer;

    void Reset()
    {
        m_uiSummonTimer = 4000;
        DoCastSpellIfCan(m_creature, SPELL_RIFT_AURA);
        //DoCastSpellIfCan(m_creature, SPELL_RIFT_SUMMON_AURA);
    }

    void JustSummoned(Creature* pSummoned)
    {
        if (pSummoned->GetEntry() == NPC_CRAZED_MANA_WRAITH)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                pSummoned->AI()->AttackStart(pTarget);
        }
    }

    void JustDied(Unit* pKiller)
    {
        if(pKiller->GetCharmerOrOwnerOrSelf()->GetTypeId() == TYPEID_PLAYER && m_pInstance)
            if(Creature* pAnomalus = (Creature*) m_creature->GetMap()->GetUnit(m_pInstance->GetData64(NPC_ANOMALUS)))
            ((boss_anomalusAI*)pAnomalus->AI())->m_bRiftKilled = true;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (!m_creature->HasAura(SPELL_ARCANE_FORM))
            DoCastSpellIfCan(m_creature, SPELL_ARCANE_FORM);

        if (m_uiSummonTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_SUMMON_CRAZED_MANA_WRAITH);
            m_uiSummonTimer = urand(4000, 7000);
        }
        else
            m_uiSummonTimer -= uiDiff;
    }
};

CreatureAI* GetAI_mob_chaotic_rift(Creature* pCreature)
{
    return new mob_chaotic_riftAI(pCreature);
}

void AddSC_boss_anomalus()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "boss_anomalus";
    newscript->GetAI = &GetAI_boss_anomalus;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_chaotic_rift";
    newscript->GetAI = &GetAI_mob_chaotic_rift;
    newscript->RegisterSelf();
}
