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
SDName: Boss_Volazj 
SD%Complete: 20% 
SDComment: 
SDCategory: Ahn'kahet 
EndScriptData */ 
 
#include "precompiled.h"
#include "ahnkahet.h"

enum 
{ 
    SAY_AGGRO                      = -1619033, 
    SAY_INSANITY                   = -1619034, 
    SAY_SLAY_1                     = -1619035, 
    SAY_SLAY_2                     = -1619036, 
    SAY_SLAY_3                     = -1619037, 
    SAY_DEATH                      = -1619038, 
    WHISPER_AGGRO                  = -1619039, 
    WHISPER_INSANITY               = -1619040, 
    WHISPER_SLAY_1                 = -1619041, 
    WHISPER_SLAY_2                 = -1619042, 
    WHISPER_SLAY_3                 = -1619043, 
    WHISPER_DEATH                  = -1619044, 

    SPELL_INSANITY                  = 57496,
	
	SPELL_INSANITY_PHASE_16			= 57508,
	SPELL_INSANITY_PHASE_32			= 57509,
	SPELL_INSANITY_PHASE_64			= 57510,
	SPELL_INSANITY_PHASE_128		= 57511,
	SPELL_INSANITY_PHASE_256		= 57512,
	
    SPELL_SHIVER                    = 57949, 
    SPELL_SHIVER_H                  = 59978, 
 
    SPELL_SHADOW_BOLT_SALVE        = 57942, 
    SPELL_SHADOW_BOLT_SALVE_H      = 59975, 
 
    SPELL_MIND_FLAY                = 57941, 
    SPELL_MIND_FLAY_H              = 59974,

    // FIXME: these are not the right clone NPCs!
    CLONE                      = 31627,
    CLONE_H                    = 31627,
    FAC_HOSTILE                = 16,
    ACHIEVEMENT_QUICK_DEMISE   = 1862
}; 
 
enum clonehealth
{ 
    CLONE_HEALTH_DRUID        = 16101, 
    CLONE_HEALTH_DRUID_H      = CLONE_HEALTH_DRUID * 3, 
    CLONE_HEALTH_PRIEST        = 16404, 
    CLONE_HEALTH_PRIEST_H      = CLONE_HEALTH_PRIEST * 3, 
    CLONE_HEALTH_PALA          = 17334, 
    CLONE_HEALTH_PALA_H        = CLONE_HEALTH_PALA * 3, 
    CLONE_HEALTH_HUNT          = 15899, 
    CLONE_HEALTH_HUNT_H        = CLONE_HEALTH_HUNT * 3, 
    CLONE_HEALTH_SHAMAN        = 17655, 
    CLONE_HEALTH_SHAMAN_H      = CLONE_HEALTH_SHAMAN * 3, 
    CLONE_HEALTH_ROGUE        = 14530, 
    CLONE_HEALTH_ROGUE_H      = CLONE_HEALTH_ROGUE * 3, 
    CLONE_HEALTH_MAGE          = 12444, 
    CLONE_HEALTH_MAGE_H        = CLONE_HEALTH_MAGE * 3, 
    CLONE_HEALTH_WARRIOR      = 19883, 
    CLONE_HEALTH_WARRIOR_H    = CLONE_HEALTH_WARRIOR * 3, 
    CLONE_HEALTH_WARLOCK      = 16877, 
    CLONE_HEALTH_WARLOCK_H    = CLONE_HEALTH_WARLOCK * 3, 
    CLONE_HEALTH_DK            = 20012, 
    CLONE_HEALTH_DK_H          = CLONE_HEALTH_DK * 3, 
}; 
 
enum 
{ 
    SPELL_DRUID_1          = 69882, 
    SPELL_DRUID_1_H        = 71141, 
    SPELL_DRUID_2          = 69898, 
    SPELL_DRUID_2_H        = 71142, 
    SPELL_DRUID_3          = 38658, 
    SPELL_HUNT              = 59604, 
    SPELL_DK                = 55978, 
    SPELL_MAGE              = 69869, 
    SPELL_MAGE_H            = 71130, 
    SPELL_ROGUE_1          = 37331, 
    SPELL_ROGUE_2          = 1330, 
    SPELL_SHAMAN            = 68113, 
    SPELL_SHAMAN_H          = 64213, 
    SPELL_PRIEST_1          = 71932, 
    SPELL_PRIEST_2          = 30854, 
    SPELL_PRIEST_1_H        = 43575, 
    SPELL_PRIEST_2_H        = 68089, 
    SPELL_WARRIOR          = 46271, 
    SPELL_WARRIOR_H        = 41399, 
    SPELL_WARLOCK          = 37668, 
    SPELL_WARLOCK_H        = 75383, 
    SPELL_PALA              = 46029, 
    SPELL_PALA_H            = 41541 
}; 
 
/*###### 
## boss_volazj 
######*/ 
 
struct MANGOS_DLL_DECL boss_volazjAI : public ScriptedAI 
{ 
    boss_volazjAI(Creature* pCreature) : ScriptedAI(pCreature) 
    { 
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData(); 
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty(); 
        Reset(); 
    } 
 
    ScriptedInstance* m_pInstance; 
    bool m_bIsRegularMode; 
 
    bool isInInsanity; 
    bool phase66; 
    bool phase33; 
	bool clone16;
	bool clone32;
	bool clone64;
	bool clone128;
	bool clone256;
    bool startAchievement;
    bool getsAchievement;
 
    std::list<uint64> cloneGUIDList; 
	std::list<uint64> clone16GUIDList;
	std::list<uint64> clone32GUIDList;
	std::list<uint64> clone64GUIDList;
	std::list<uint64> clone128GUIDList;
	std::list<uint64> clone256GUIDList;
 
    uint32 insanityEndTimer; 
    uint32 insanityTimer; 
    uint32 createMirrorTimer; 
    uint32 shadowBoltSalveTimer; 
    uint32 shiverTimer; 
    uint32 mindFlayTimer; 
    uint32 achievementTimer;
 
    void Reset() 
    { 
        insanityEndTimer = 9999999; 
        createMirrorTimer = 9999999;
        achievementTimer = 120000; // 2minutes
		shadowBoltSalveTimer = 6000;
		shiverTimer = 13000;
		mindFlayTimer = 9000;
		cloneGUIDList.clear();
		clone16GUIDList.clear();
		clone32GUIDList.clear();
		clone64GUIDList.clear();
		clone128GUIDList.clear();
		clone256GUIDList.clear();

		isInInsanity = false;
		phase66 = false;
		phase33 = false;
		clone16 = false;
		clone32 = false;
		clone64 = false;
		clone128 = false;
		clone256 = false;
        startAchievement = false;
        getsAchievement = true;

        // as long as insanity is not working
        m_creature->SetHealth(400000);

		if (m_pInstance)
            m_pInstance->SetData(TYPE_VOLAZJ, NOT_STARTED);
    } 
 
    void Aggro(Unit* pWho) 
    { 
        DoScriptText(SAY_AGGRO, m_creature);

        Map* pMap = m_creature->GetMap();
        Map::PlayerList const &players = pMap->GetPlayers();
	    for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr) 
            if (Unit *target = m_creature->GetMap()->GetUnit(itr->getSource()->GetGUID())) 
                DoScriptText(WHISPER_AGGRO,m_creature,target);
        
        startAchievement = true;

		if (m_pInstance)
            m_pInstance->SetData(TYPE_VOLAZJ, IN_PROGRESS);
    } 
 
    void KilledUnit(Unit* pVictim) 
    { 
        int32 textId = 0;

        switch(urand(0, 2)) 
        { 
            case 0: textId = SAY_SLAY_1; break; 
            case 1: textId = SAY_SLAY_2; break; 
            case 2: textId = SAY_SLAY_3; break; 
        } 

        DoScriptText(textId,m_creature);

        Map* pMap = m_creature->GetMap();
        Map::PlayerList const &players = pMap->GetPlayers();
	    for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr) 
            if (Unit *target = m_creature->GetMap()->GetUnit(itr->getSource()->GetGUID())) 
                DoScriptText(textId-6,m_creature,target);
    } 
 
    void JustDied(Unit* pKiller) 
    { 
        DoScriptText(SAY_DEATH, m_creature); 

        Map* pMap = m_creature->GetMap();
        if (pMap && pMap->IsDungeon())
        {
            Map::PlayerList const &players = pMap->GetPlayers();
            for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
            {
                // as long as insanity is not working
                //if(!m_bIsRegularMode && getsAchievement)
                    //itr->getSource()->CompletedAchievement(ACHIEVEMENT_QUICK_DEMISE);
                DoScriptText(WHISPER_DEATH,m_creature,itr->getSource());
            }
        }

		if (m_pInstance)
            m_pInstance->SetData(TYPE_VOLAZJ, DONE);
    } 

	void setPlayersPhase()
	{
		int i = 1;

        Map* pMap = m_creature->GetMap();
        Map::PlayerList const &players = pMap->GetPlayers();
		for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr) 
            if(Player* target = m_creature->GetMap()->GetPlayer(itr->getSource()->GetGUID())) 
		    {
			    switch(i)
			    {
				    case 1:
					    target->CastSpell(target, SPELL_INSANITY_PHASE_16, true);
					    break;
				    case 2:
					    target->CastSpell(target, SPELL_INSANITY_PHASE_32, true);
					    break;
				    case 3:
					    target->CastSpell(target, SPELL_INSANITY_PHASE_64, true);
					    break;
				    case 4:
					    target->CastSpell(target, SPELL_INSANITY_PHASE_128, true);
					    break;
				    case 5:
					    target->CastSpell(target, SPELL_INSANITY_PHASE_256, true);
					    break;
				    default:
					    break;
                }
					i++;
            }
	}
 
    void createClassMirrors() 
    {
		for (int i = 0; i <= 5; i++)
		{
            Map* pMap = m_creature->GetMap();
            Map::PlayerList const &players = pMap->GetPlayers();
		    for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr) 
			{ 
                if(Unit* target = m_creature->GetMap()->GetUnit(itr->getSource()->GetGUID())) 
				{ 
			        Unit* pClone = m_creature->SummonCreature(m_bIsRegularMode ? CLONE : CLONE_H, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), target->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 15000);
                    if (pClone) 
                    {
                        pClone->RemoveFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_PASSIVE);
                        pClone->RemoveFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NOT_SELECTABLE);
                        pClone->RemoveFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_OOC_NOT_ATTACKABLE);
                        pClone->RemoveFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_UNK_6);
					    pClone->SetDisplayId(target->GetNativeDisplayId());
					    pClone->SetName(target->GetName());
                        pClone->setFaction(FAC_HOSTILE);

					    switch (target->getClass()) 
					    { 
						    case CLASS_PRIEST: pClone->SetMaxHealth(m_bIsRegularMode ? CLONE_HEALTH_PRIEST : CLONE_HEALTH_PRIEST_H); break;
                            case CLASS_PALADIN: pClone->SetMaxHealth(m_bIsRegularMode ? CLONE_HEALTH_PALA : CLONE_HEALTH_PALA_H); break;
    					    case CLASS_WARLOCK: pClone->SetMaxHealth(m_bIsRegularMode ? CLONE_HEALTH_WARLOCK : CLONE_HEALTH_WARLOCK_H); break;
    					    case CLASS_MAGE: pClone->SetMaxHealth(m_bIsRegularMode ? CLONE_HEALTH_MAGE : CLONE_HEALTH_MAGE_H); break;
						    case CLASS_ROGUE: pClone->SetMaxHealth(m_bIsRegularMode ? CLONE_HEALTH_ROGUE : CLONE_HEALTH_ROGUE_H); break;
					        case CLASS_WARRIOR: pClone->SetMaxHealth(m_bIsRegularMode ? CLONE_HEALTH_WARRIOR : CLONE_HEALTH_WARRIOR_H); break;
						    case CLASS_DRUID: pClone->SetMaxHealth(m_bIsRegularMode ? CLONE_HEALTH_DRUID : CLONE_HEALTH_DRUID_H); break;
						    case CLASS_SHAMAN: pClone->SetMaxHealth(m_bIsRegularMode ? CLONE_HEALTH_SHAMAN : CLONE_HEALTH_SHAMAN_H); break;
						    case CLASS_HUNTER: pClone->SetMaxHealth(m_bIsRegularMode ? CLONE_HEALTH_HUNT : CLONE_HEALTH_HUNT_H); break;
						    case CLASS_DEATH_KNIGHT: pClone->SetMaxHealth(m_bIsRegularMode ? CLONE_HEALTH_DK : CLONE_HEALTH_DK_H); break;
                            default: break;
                        }

                        pClone->SetHealth(pClone->GetMaxHealth()); 
					    pClone->Attack(target, true); 
					    pClone->AddThreat(target, 10.0f);
					    cloneGUIDList.push_back(pClone->GetGUID()); 
				    } 

				    switch(i)
				    {
					    case 1:
						    pClone->SetPhaseMask(16, true);
						    clone16GUIDList.push_back(pClone->GetGUID());
						    break;
					    case 2:
						    pClone->SetPhaseMask(32, true);
						    clone32GUIDList.push_back(pClone->GetGUID());
						    break;
					    case 3:
						    pClone->SetPhaseMask(64, true);
						    clone64GUIDList.push_back(pClone->GetGUID());
						    break;
					    case 4:
						    pClone->SetPhaseMask(128, true);
						    clone128GUIDList.push_back(pClone->GetGUID());
						    break;
					    case 5:
						    pClone->SetPhaseMask(256, true);
						    clone256GUIDList.push_back(pClone->GetGUID());
						    break;
					    default:
						    break;
					} 
				} 
			} 
		}
    } 

	bool cloneAlive()
	{
		if (!cloneGUIDList.empty() && m_pInstance)
		{
			for (std::list<uint64>::iterator itr = cloneGUIDList.begin(); itr != cloneGUIDList.end(); ++itr)
			{
				if (Creature* pClone = m_pInstance->instance->GetCreature(*itr))
				{
					if (pClone->isAlive())
						return true;
				}
			}
		}

		return false;
	}

	bool clone16Alive()
	{
		if (!clone16GUIDList.empty() && m_pInstance)
		{
			for (std::list<uint64>::iterator itr = clone16GUIDList.begin(); itr != clone16GUIDList.end(); ++itr)
			{
				if (Creature* pClone = m_pInstance->instance->GetCreature(*itr))
				{
					if (pClone->isAlive())
						return true;
				}
			}
		}

		return false;
	}

	bool clone32Alive()
	{
		if (!clone32GUIDList.empty() && m_pInstance)
		{
			for (std::list<uint64>::iterator itr = clone32GUIDList.begin(); itr != clone32GUIDList.end(); ++itr)
			{
				if (Creature* pClone = m_pInstance->instance->GetCreature(*itr))
				{
					if (pClone->isAlive())
						return true;
				}
			}
		}

		return false;
	}

	bool clone64Alive()
	{
		if (!clone64GUIDList.empty() && m_pInstance)
		{
			for (std::list<uint64>::iterator itr = clone64GUIDList.begin(); itr != clone64GUIDList.end(); ++itr)
			{
				if (Creature* pClone = m_pInstance->instance->GetCreature(*itr))
				{
					if (pClone->isAlive())
						return true;
				}
			}
		}

		return false;
	}

	bool clone128Alive()
	{
		if (!clone128GUIDList.empty() && m_pInstance)
		{
			for (std::list<uint64>::iterator itr = clone128GUIDList.begin(); itr != clone128GUIDList.end(); ++itr)
			{
				if (Creature* pClone = m_pInstance->instance->GetCreature(*itr))
				{
					if (pClone->isAlive())
						return true;
				}
			}
		}

		return false;
	}

	bool clone256Alive()
	{
		if (!clone256GUIDList.empty() && m_pInstance)
		{
			for (std::list<uint64>::iterator itr = clone256GUIDList.begin(); itr != clone256GUIDList.end(); ++itr)
			{
				if (Creature* pClone = m_pInstance->instance->GetCreature(*itr))
				{
					if (pClone->isAlive())
						return true;
				}
			}
		}

		return false;
	}
 
    void UpdateAI(const uint32 uiDiff) 
    {
        if(startAchievement)
            if(achievementTimer < uiDiff)
            {
                startAchievement = false;
                getsAchievement = false;
            } else
                achievementTimer -= uiDiff;

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim()) 
            return; 
 
        if (isInInsanity) 
        { 
            if (insanityEndTimer < uiDiff) 
            { 
				if (!cloneAlive()) 
                {  
                    m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE); 
                    isInInsanity = false; 
                    m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim()); 
                    m_creature->Attack(m_creature->getVictim(), true); 
                    insanityEndTimer = 9999999; 
					clone16 = clone32 = clone64 = clone128 = clone256 = false;
					return;
                }else 
                    insanityEndTimer = 1000; 
            }else insanityEndTimer -= uiDiff;

			if (!clone16Alive() && !clone16)
			{
			    Map* pMap = m_creature->GetMap();
                Map::PlayerList const &players = pMap->GetPlayers();
		        for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr) 
				{ 
                    if (Unit *target = m_creature->GetMap()->GetUnit(itr->getSource()->GetGUID())) 
					{ 
					    if (target->GetPhaseMask() == 16)
					    {
						    target->RemoveAurasDueToSpell(SPELL_INSANITY_PHASE_16);
						    if (!clone32)
							    target->CastSpell(target, SPELL_INSANITY_PHASE_32, true);
						    else if (!clone64)
						        target->CastSpell(target, SPELL_INSANITY_PHASE_64, true);
						    else if (!clone128)
							    target->CastSpell(target, SPELL_INSANITY_PHASE_128, true);
						    else if (!clone256)
						    target->CastSpell(target, SPELL_INSANITY_PHASE_256, true);
						}
					} 
				}

				clone16 = true;
			}

			if (!clone32Alive() && !clone32)
			{
			    Map* pMap = m_creature->GetMap();
                Map::PlayerList const &players = pMap->GetPlayers();
		        for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr) 
				{ 
                    if (Unit *target = m_creature->GetMap()->GetUnit(itr->getSource()->GetGUID())) 
					{ 
					    if (target->GetPhaseMask() == 32)
					    {
					        target->RemoveAurasDueToSpell(SPELL_INSANITY_PHASE_32);
						    if (!clone16)
							    target->CastSpell(target, SPELL_INSANITY_PHASE_16, true);
						    else if (!clone64)
							    target->CastSpell(target, SPELL_INSANITY_PHASE_64, true);
						    else if (!clone128)
							    target->CastSpell(target, SPELL_INSANITY_PHASE_128, true);
						    else if (!clone256)
							    target->CastSpell(target, SPELL_INSANITY_PHASE_256, true);
						}
					} 
				}

				clone32 = true;
			}

			if (!clone64Alive() && !clone64)
			{
			    Map* pMap = m_creature->GetMap();
                Map::PlayerList const &players = pMap->GetPlayers();
		        for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr) 
				{ 
                    if (Unit *target = m_creature->GetMap()->GetUnit(itr->getSource()->GetGUID())) 
					{ 
				        if (target->GetPhaseMask() == 64)
					    {
						    target->RemoveAurasDueToSpell(SPELL_INSANITY_PHASE_64);
						    if (!clone16)
							    target->CastSpell(target, SPELL_INSANITY_PHASE_16, true);
						    else if (!clone32)
							    target->CastSpell(target, SPELL_INSANITY_PHASE_32, true);
						    else if (!clone128)
							    target->CastSpell(target, SPELL_INSANITY_PHASE_128, true);
						    else if (!clone256)
							    target->CastSpell(target, SPELL_INSANITY_PHASE_256, true);
						}
					} 
				}

				clone64 = true;
			}

			if (!clone128Alive() && !clone128)
			{
			    Map* pMap = m_creature->GetMap();
                Map::PlayerList const &players = pMap->GetPlayers();
		        for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr) 
				{ 
                    if (Unit *target = m_creature->GetMap()->GetUnit(itr->getSource()->GetGUID())) 
					{ 
					    if (target->GetPhaseMask() == 128)
					    {
						    target->RemoveAurasDueToSpell(SPELL_INSANITY_PHASE_128);
						    if (!clone16)
							    target->CastSpell(target, SPELL_INSANITY_PHASE_16, true);
						    else if (!clone32)
							    target->CastSpell(target, SPELL_INSANITY_PHASE_32, true);
						    else if (!clone64)
							    target->CastSpell(target, SPELL_INSANITY_PHASE_64, true);
						    else if (!clone256)
							    target->CastSpell(target, SPELL_INSANITY_PHASE_256, true);
						}
					} 
				}

				clone128 = true;
			}

			if (!clone256Alive() && !clone256)
			{
			    Map* pMap = m_creature->GetMap();
                Map::PlayerList const &players = pMap->GetPlayers();
		        for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr) 
				{ 
                    if (Unit *target = m_creature->GetMap()->GetUnit(itr->getSource()->GetGUID())) 
					{ 
					    if (target->GetPhaseMask() == 256)
					    {
						    target->RemoveAurasDueToSpell(SPELL_INSANITY_PHASE_256);
						    if (!clone16)
						        target->CastSpell(target, SPELL_INSANITY_PHASE_16, true);
						    else if (!clone32)
							    target->CastSpell(target, SPELL_INSANITY_PHASE_32, true);
						    else if (!clone64)
							    target->CastSpell(target, SPELL_INSANITY_PHASE_64, true);
						    else if (!clone128)
						    target->CastSpell(target, SPELL_INSANITY_PHASE_128, true);
						}
					} 
				}

				clone256 = true;
			}
        } 
        else 
        { 
            if (m_creature->GetHealth() < m_creature->GetMaxHealth() * 0.66 && !phase66) 
            { 
                DoScriptText(SAY_INSANITY, m_creature);

                Map* pMap = m_creature->GetMap();
                Map::PlayerList const &players = pMap->GetPlayers();
		        for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr) 
                    if (Unit *target = m_creature->GetMap()->GetUnit(itr->getSource()->GetGUID())) 
                        DoScriptText(WHISPER_INSANITY,m_creature,target);

				m_creature->InterruptNonMeleeSpells(true);
                phase66 = true; 
                DoCastSpellIfCan(m_creature, SPELL_INSANITY); 
                createMirrorTimer = 5000; 
                m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE); 
                m_creature->GetMotionMaster()->Clear(); 
                m_creature->GetMotionMaster()->MoveIdle(); 
            } 
 
            if (m_creature->GetHealth() < m_creature->GetMaxHealth() * 0.33 && !phase33) 
            {
                DoScriptText(SAY_INSANITY, m_creature);

                Map* pMap = m_creature->GetMap();
                Map::PlayerList const &players = pMap->GetPlayers();
		        for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr) 
                    if (Unit *target = m_creature->GetMap()->GetUnit(itr->getSource()->GetGUID())) 
                        DoScriptText(WHISPER_INSANITY,m_creature,target);

				m_creature->InterruptNonMeleeSpells(true);
                phase33 = true; 
                DoCastSpellIfCan(m_creature, SPELL_INSANITY); 
                createMirrorTimer = 5000; 
                m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE); 
                m_creature->GetMotionMaster()->Clear(); 
                m_creature->GetMotionMaster()->MoveIdle(); 
            } 
 
            if (createMirrorTimer < uiDiff) 
            { 
                isInInsanity = true; 
                createClassMirrors(); 
                createMirrorTimer = 9999999; 
				insanityEndTimer = 5000;
            }else createMirrorTimer -= uiDiff; 
 
            if (mindFlayTimer < uiDiff) 
            { 
                DoCastSpellIfCan(m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0), m_bIsRegularMode ? SPELL_MIND_FLAY : SPELL_MIND_FLAY_H); 
                // as long as insanity is not working
                //mindFlayTimer = urand(10000, 12000); 
                mindFlayTimer = urand(8000, 10000); 
            }else mindFlayTimer -= uiDiff; 
 
            if (shadowBoltSalveTimer < uiDiff) 
            { 
                DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_SHADOW_BOLT_SALVE : SPELL_SHADOW_BOLT_SALVE_H); 
                // as long as insanity is not working
                //shadowBoltSalveTimer = urand(5000, 10000); 
                shadowBoltSalveTimer = urand(3000, 8000); 
            }else shadowBoltSalveTimer -= uiDiff; 
 
            if (shiverTimer < uiDiff) 
            { 
                DoCastSpellIfCan(m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0), m_bIsRegularMode ? SPELL_SHIVER : SPELL_SHIVER_H); 
                // as long as insanity is not working
                //shiverTimer = urand(13000, 14000); 
                shiverTimer = urand(10000, 11000); 
            }else shiverTimer -= uiDiff;
			
			DoMeleeAttackIfReady();     
        }    
    } 
}; 
 
CreatureAI* GetAI_boss_volazj(Creature* pCreature) 
{ 
    return new boss_volazjAI(pCreature); 
} 
 
struct MANGOS_DLL_DECL mob_volazj_cloneAI : public ScriptedAI 
{ 
    mob_volazj_cloneAI(Creature* pCreature) : ScriptedAI(pCreature) 
    { 
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData(); 
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty(); 
        Reset(); 
    } 
 
    ScriptedInstance* m_pInstance; 
 
    bool m_bIsRegularMode; 
 
    uint32 spellPriestTimer; 
    uint32 spellRogueTimer; 
    uint32 spellMageTimer; 
    uint32 spellDeathKnightTimer; 
    uint32 spellShamanTimer; 
    uint32 spellWarlockTimer; 
    uint32 spellDruidTimer; 
    uint32 spellWarriorTimer; 
    uint32 spellPaladinTimer; 
    uint32 spellHunterTimer; 
        
    void Reset()
	{
		spellPriestTimer = 5000;	
		spellRogueTimer = 5000;
		spellMageTimer = 5000;
		spellDeathKnightTimer = 5000;
		spellShamanTimer = 5000;
		spellWarlockTimer = 5000;
		spellDruidTimer = 5000;
		spellWarriorTimer = 5000;
		spellPaladinTimer = 5000;
		spellHunterTimer = 5000;
	} 
 
    void UpdateAI(const uint32 uiDiff) 
    { 
        if (m_creature->GetMaxHealth() == CLONE_HEALTH_DRUID || m_creature->GetMaxHealth() == CLONE_HEALTH_DRUID_H) 
        { 
            if (spellDruidTimer < uiDiff) 
            { 
                int randomSpell = urand(0, 2); 
                switch (randomSpell) 
                { 
                    case 0: 
                        DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_DRUID_1 : SPELL_DRUID_1_H); 
                        break; 
                    case 1: 
                        DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_DRUID_2 : SPELL_DRUID_2_H); 
                        break; 
                    case 2: 
                        DoCastSpellIfCan(m_creature, SPELL_DRUID_3); 
                        break; 
                } 
                spellDruidTimer = 5000; 
            }else spellDruidTimer -= uiDiff; 
 
        } 
        else if (m_creature->GetMaxHealth() == CLONE_HEALTH_MAGE || m_creature->GetMaxHealth() == CLONE_HEALTH_MAGE_H) 
        { 
            if (spellMageTimer < uiDiff) 
            { 
                DoCastSpellIfCan(m_creature->getVictim(), m_bIsRegularMode ? SPELL_MAGE : SPELL_MAGE_H); 
 
                spellMageTimer = urand(4000, 6000); 
            }else spellMageTimer -= uiDiff; 
        } 
        else if (m_creature->GetMaxHealth() == CLONE_HEALTH_PALA || m_creature->GetMaxHealth() == CLONE_HEALTH_PALA_H) 
        { 
            if (spellPaladinTimer < uiDiff) 
            { 
                if (!m_bIsRegularMode) 
                { 
                    if (!urand(0, 2)) 
                        DoCastSpellIfCan(m_creature, SPELL_PALA_H); 
                    else 
                        DoCastSpellIfCan(m_creature, SPELL_PALA);  
                } 
                else 
                    DoCastSpellIfCan(m_creature, SPELL_PALA);    
 
                spellPaladinTimer = urand(4000, 5000); 
            }else spellPaladinTimer -= uiDiff; 
        } 
        else if (m_creature->GetMaxHealth() == CLONE_HEALTH_HUNT || m_creature->GetMaxHealth() == CLONE_HEALTH_HUNT_H) 
        { 
            if (spellHunterTimer < uiDiff) 
            { 
                DoCastSpellIfCan(m_creature->getVictim(), SPELL_HUNT); 
 
                spellHunterTimer = m_bIsRegularMode ? urand(8000, 9000) : urand(4000, 5000); 
            }else spellHunterTimer -= uiDiff;  
        } 
        else if (m_creature->GetMaxHealth() == CLONE_HEALTH_WARLOCK || m_creature->GetMaxHealth() == CLONE_HEALTH_WARLOCK_H) 
        { 
            if (spellWarlockTimer < uiDiff) 
            { 
                DoCastSpellIfCan(m_creature->getVictim(), m_bIsRegularMode ? SPELL_WARLOCK : SPELL_WARLOCK_H); 
 
                spellWarlockTimer = urand(6000, 10000); 
            }else spellWarlockTimer -= uiDiff; 
        } 
        else if (m_creature->GetMaxHealth() == CLONE_HEALTH_DK || m_creature->GetMaxHealth() == CLONE_HEALTH_DK_H) 
        { 
            if (spellDeathKnightTimer < uiDiff) 
            { 
                DoCastSpellIfCan(m_creature->getVictim(), SPELL_DK); 
 
                spellDeathKnightTimer = m_bIsRegularMode ? urand(9000, 12000) : urand(4000, 5000); 
            }else spellDeathKnightTimer -= uiDiff;  
        } 
        else if (m_creature->GetMaxHealth() == CLONE_HEALTH_WARRIOR || m_creature->GetMaxHealth() == CLONE_HEALTH_WARRIOR_H) 
        { 
            if (spellWarriorTimer < uiDiff) 
            { 
                if (m_bIsRegularMode) 
                { 
                    DoCastSpellIfCan(m_creature->getVictim(), SPELL_WARRIOR); 
                    spellWarriorTimer = urand(4000, 6000); 
                } 
                else 
                { 
                    DoCastSpellIfCan(m_creature->getVictim(), SPELL_WARRIOR_H); 
                    spellWarriorTimer = urand(20000, 25000); 
                } 
            }else spellWarriorTimer -= uiDiff; 
        } 
        else if (m_creature->GetMaxHealth() == CLONE_HEALTH_PRIEST || m_creature->GetMaxHealth() == CLONE_HEALTH_PRIEST_H) 
        { 
            if (spellPriestTimer < uiDiff) 
            { 
                if (m_bIsRegularMode)
				{
					if (urand(0, 1))
						DoCastSpellIfCan(m_creature->getVictim(), SPELL_PRIEST_2);
					else
						DoCastSpellIfCan(m_creature, SPELL_PRIEST_1);
				}
                else 
				{
					if (!urand(0, 3))
						DoCastSpellIfCan(m_creature->getVictim(), SPELL_PRIEST_2_H);
					else
						DoCastSpellIfCan(m_creature, SPELL_PRIEST_1_H);
				}
                  
                spellPriestTimer = urand (5000, 7000);  
            }else spellPriestTimer -= uiDiff; 
        } 
        else if (m_creature->GetMaxHealth() == CLONE_HEALTH_SHAMAN || m_creature->GetMaxHealth() == CLONE_HEALTH_SHAMAN_H) 
        { 
            if (spellShamanTimer < uiDiff) 
            { 
                if (m_bIsRegularMode) 
                { 
					DoCastSpellIfCan(m_creature->getVictim(), SPELL_SHAMAN); 
                    spellShamanTimer = urand(4000, 6000); 
                } 
                else 
                { 
                    DoCastSpellIfCan(m_creature->getVictim(), SPELL_SHAMAN_H); 
                    spellShamanTimer = urand(10000, 11000); 
                } 
            }else spellShamanTimer -= uiDiff;  
        } 
        else if (m_creature->GetMaxHealth() == CLONE_HEALTH_ROGUE || m_creature->GetMaxHealth() == CLONE_HEALTH_ROGUE_H) 
        { 
            if (spellRogueTimer < uiDiff) 
            { 
                if (m_bIsRegularMode) 
                { 
                    DoCastSpellIfCan(m_creature->getVictim(), SPELL_ROGUE_2); 
                    spellRogueTimer = urand(4000, 6000); 
                } 
                else 
                { 
                    DoCastSpellIfCan(m_creature->getVictim(), SPELL_ROGUE_1); 
                    spellRogueTimer = urand(10000, 14000); 
                } 
            }else spellRogueTimer -= uiDiff; 
        } 
 
        DoMeleeAttackIfReady(); 
    } 
}; 
 
CreatureAI* GetAI_mob_volazj_clone(Creature* pCreature) 
{ 
    return new mob_volazj_cloneAI(pCreature); 
} 
 
void AddSC_boss_volazj() 
{ 
    Script *newscript; 
 
    newscript = new Script; 
    newscript->Name = "boss_volazj"; 
    newscript->GetAI = &GetAI_boss_volazj; 
    newscript->RegisterSelf(); 
 
    newscript = new Script; 
    newscript->Name = "mob_volazj_clone"; 
    newscript->GetAI = &GetAI_mob_volazj_clone; 
    newscript->RegisterSelf(); 
}