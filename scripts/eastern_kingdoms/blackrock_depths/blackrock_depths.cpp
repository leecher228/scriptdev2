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
SDName: Blackrock_Depths
SD%Complete: 50
SDComment: Quest support: 4001, 4342, 7604, 12062. Vendor Lokhtos Darkbargainer.
SDCategory: Blackrock Depths
EndScriptData */

/* ContentData
go_shadowforge_brazier
at_ring_of_law
npc_grimstone
mob_phalanx
npc_kharan_mighthammer
npc_lokhtos_darkbargainer
boss_coren_direbrew
EndContentData */

#include "precompiled.h"
#include "blackrock_depths.h"
#include "escort_ai.h"

/*######
## go_shadowforge_brazier
######*/

bool GOHello_go_shadowforge_brazier(Player* pPlayer, GameObject* pGo)
{
    if (ScriptedInstance* pInstance = (ScriptedInstance*)pGo->GetInstanceData())
    {
        if (pInstance->GetData(TYPE_LYCEUM) == IN_PROGRESS)
            pInstance->SetData(TYPE_LYCEUM, DONE);
        else
            pInstance->SetData(TYPE_LYCEUM, IN_PROGRESS);
    }
    return false;
}

/*######
## npc_grimstone
######*/

enum
{
    SAY_START_1         = -1230004,
    SAY_START_2         = -1230005,
    SAY_OPEN_EAST_GATE  = -1230006,
    SAY_SUMMON_BOSS_1   = -1230007,
    SAY_SUMMON_BOSS_2   = -1230008,
    SAY_OPEN_NORTH_GATE = -1230009,

    NPC_GRIMSTONE       = 10096,
    NPC_THELDREN        = 16059,

    //4 or 6 in total? 1+2+1 / 2+2+2 / 3+3. Depending on this, code should be changed.
    MAX_MOB_AMOUNT      = 4
};

static uint32 RingMob[]=
{
    8925,                                                   // Dredge Worm
    8926,                                                   // Deep Stinger
    8927,                                                   // Dark Screecher
    8928,                                                   // Burrowing Thundersnout
    8933,                                                   // Cave Creeper
    8932,                                                   // Borer Beetle
};

static uint32 RingBoss[]=
{
    9027,                                                   // Gorosh
    9028,                                                   // Grizzle
    9029,                                                   // Eviscerator
    9030,                                                   // Ok'thor
    9031,                                                   // Anub'shiah
    9032,                                                   // Hedrum
};

bool AreaTrigger_at_ring_of_law(Player* pPlayer, AreaTriggerEntry const* pAt)
{
    if (ScriptedInstance* pInstance = (ScriptedInstance*)pPlayer->GetInstanceData())
    {
        if (pInstance->GetData(TYPE_RING_OF_LAW) == IN_PROGRESS || pInstance->GetData(TYPE_RING_OF_LAW) == DONE)
            return false;

        pInstance->SetData(TYPE_RING_OF_LAW, IN_PROGRESS);
        pPlayer->SummonCreature(NPC_GRIMSTONE, 625.559f, -205.618f, -52.735f, 2.609f, TEMPSUMMON_DEAD_DESPAWN, 0);

        return false;
    }
    return false;
}

/*######
## npc_grimstone
######*/

//TODO: implement quest part of event (different end boss)
struct MANGOS_DLL_DECL npc_grimstoneAI : public npc_escortAI
{
    npc_grimstoneAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_uiMobSpawnId = urand(0, 5);
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint8 m_uiEventPhase;
    uint32 m_uiEventTimer;

    uint8 m_uiMobSpawnId;
    uint8 m_uiMobCount;
    uint32 m_uiMobDeathTimer;

    uint64 m_auiRingMobGUID[MAX_MOB_AMOUNT];
    uint64 m_uiRingBossGUID;

    bool m_bCanWalk;

    void Reset()
    {
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        memset(&m_auiRingMobGUID, 0, sizeof(m_auiRingMobGUID));

        m_uiEventTimer    = 1000;
        m_uiEventPhase    = 0;
        m_uiMobCount      = 0;
        m_uiMobDeathTimer = 0;
        m_uiRingBossGUID  = 0;

        m_bCanWalk = false;
    }

    void JustSummoned(Creature* pSummoned)
    {

    }

    void SummonedCreatureJustDied(Creature* pSummoned)
    {

    }
    
    void DoGate(uint32 id, uint32 state)
    {
        if (GameObject* pGo = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(id)))
            pGo->SetGoState(GOState(state));

        debug_log("SD2: npc_grimstone, arena gate update state.");
    }

    //TODO: move them to center
    void SummonRingMob()
    {
        if (Creature* pTmp = m_creature->SummonCreature(RingMob[m_uiMobSpawnId], 608.960f, -235.322f, -53.907f, 1.857f, TEMPSUMMON_DEAD_DESPAWN, 0))
            m_auiRingMobGUID[m_uiMobCount] = pTmp->GetGUID();

        ++m_uiMobCount;

        if (m_uiMobCount == MAX_MOB_AMOUNT)
            m_uiMobDeathTimer = 2500;
    }

    //TODO: move them to center
    void SummonRingBoss()
    {
        if (Creature* pTmp = m_creature->SummonCreature(RingBoss[urand(0, 5)], 644.300f, -175.989f, -53.739f, 3.418f, TEMPSUMMON_DEAD_DESPAWN, 0))
            m_uiRingBossGUID = pTmp->GetGUID();

        m_uiMobDeathTimer = 2500;
    }

    void WaypointReached(uint32 uiPointId)
    {
        switch(uiPointId)
        {
            case 0:                                         // Middle reached first time
                DoScriptText(urand(0, 1) ? SAY_START_1 : SAY_START_2, m_creature);
                m_bCanWalk = false;
                m_uiEventTimer = 5000;
                break;
            case 1:                                         // Reached wall again
                DoScriptText(SAY_OPEN_EAST_GATE, m_creature);
                m_bCanWalk = false;
                m_uiEventTimer = 5000;
                break;
            case 2:                                         // walking along the wall, while door opened
                m_bCanWalk = false;
                break;
            case 3:                                         // Middle reached second time
                DoScriptText(urand(0, 1) ? SAY_SUMMON_BOSS_1 : SAY_SUMMON_BOSS_2, m_creature);
                break;
            case 4:                                         // Reached North Gate
                DoScriptText(SAY_OPEN_NORTH_GATE, m_creature);//6
                m_bCanWalk = false;
                m_uiEventTimer = 5000;
                break;
            case 5:
                if (m_pInstance)
                {
                    m_pInstance->SetData(TYPE_RING_OF_LAW, DONE);
                    debug_log("SD2: npc_grimstone: event reached end and set complete.");
                }
                break;
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance)
            return;

        if (m_uiMobDeathTimer)
        {
            if (m_uiMobDeathTimer <= uiDiff)
            {
                m_uiMobDeathTimer = 2500;

                if (m_uiRingBossGUID)
                {
                    Creature* pBoss = m_creature->GetMap()->GetCreature(m_uiRingBossGUID);
                    if (pBoss && !pBoss->isAlive() && pBoss->isDead())
                    {
                        m_uiRingBossGUID = 0;
                        m_uiEventTimer = 5000;
                        m_uiMobDeathTimer = 0;
                        return;
                    }
                    return;
                }

                for(uint8 i = 0; i < MAX_MOB_AMOUNT; ++i)
                {
                    Creature* pMob = m_creature->GetMap()->GetCreature(m_auiRingMobGUID[i]);
                    if (pMob && !pMob->isAlive() && pMob->isDead())
                    {
                        m_auiRingMobGUID[i] = 0;
                        --m_uiMobCount;

                        //seems all are gone, so set timer to continue and discontinue this
                        if (!m_uiMobCount)
                        {
                            m_uiEventTimer = 5000;
                            m_uiMobDeathTimer = 0;
                        }
                    }
                }
            }
            else
                m_uiMobDeathTimer -= uiDiff;
        }

        if (m_uiEventTimer)
        {
            if (m_uiEventTimer <= uiDiff)
            {
                switch(m_uiEventPhase)
                {
                    case 0:
                        // Shortly after spawn, start walking
                        //DoScriptText(-1000000, m_creature); // no more text on spawn
                        DoGate(DATA_ARENA4, GO_STATE_READY);
                        Start(false);
                        m_bCanWalk = true;
                        m_uiEventTimer = 0;
                        break;
                    case 1:
                        // Start walking towards wall
                        m_bCanWalk = true;
                        m_uiEventTimer = 0;
                        break;
                    case 2:
                        m_uiEventTimer = 2000;
                        break;
                    case 3:
                        // Open East Gate
                        DoGate(DATA_ARENA1, GO_STATE_ACTIVE);
                        m_uiEventTimer = 3000;
                        break;
                    case 4:
                        m_bCanWalk = true;
                        m_creature->SetVisibility(VISIBILITY_OFF);
                        SummonRingMob();
                        m_uiEventTimer = 8000;
                        break;
                    case 5:
                        SummonRingMob();
                        SummonRingMob();
                        m_uiEventTimer = 8000;
                        break;
                    case 6:
                        SummonRingMob();
                        m_uiEventTimer = 0;
                        break;
                    case 7:
                        // Summoned Mobs are dead, continue event
                        m_creature->SetVisibility(VISIBILITY_ON);
                        DoGate(DATA_ARENA1, GO_STATE_READY);
                        //DoScriptText(-1000000, m_creature); // after killed the mobs, no say here
                        m_bCanWalk = true;
                        m_uiEventTimer = 0;
                        break;
                    case 8:
                        // Open North Gate
                        DoGate(DATA_ARENA2, GO_STATE_ACTIVE);
                        m_uiEventTimer = 5000;
                        break;
                    case 9:
                        // Summon Boss
                        m_creature->SetVisibility(VISIBILITY_OFF);
                        SummonRingBoss();
                        m_uiEventTimer = 0;
                        break;
                    case 10:
                        // Boss dead
                        //if quest, complete
                        DoGate(DATA_ARENA2, GO_STATE_READY);
                        DoGate(DATA_ARENA3, GO_STATE_ACTIVE);
                        DoGate(DATA_ARENA4, GO_STATE_ACTIVE);
                        m_bCanWalk = true;
                        m_uiEventTimer = 0;
                        break;
                }
                ++m_uiEventPhase;
            }
            else
                m_uiEventTimer -= uiDiff;
        }

        if (m_bCanWalk)
            npc_escortAI::UpdateAI(uiDiff);
    }
};

CreatureAI* GetAI_npc_grimstone(Creature* pCreature)
{
    return new npc_grimstoneAI(pCreature);
}

/*######
## mob_phalanx
######*/

enum
{
    SPELL_THUNDERCLAP    = 15588,
    SPELL_FIREBALLVOLLEY = 15285,
    SPELL_MIGHTYBLOW     = 14099
};

struct MANGOS_DLL_DECL mob_phalanxAI : public ScriptedAI
{
    mob_phalanxAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    uint32 m_uiThunderClapTimer;
    uint32 m_uiFireballVolleyTimer;
    uint32 m_uiMightyBlowTimer;

    void Reset()
    {
        m_uiThunderClapTimer    = 12000;
        m_uiFireballVolleyTimer = 0;
        m_uiMightyBlowTimer     = 15000;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // ThunderClap
        if (m_uiThunderClapTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_THUNDERCLAP);
            m_uiThunderClapTimer = 10000;
        }
        else
            m_uiThunderClapTimer -= uiDiff;

        // FireballVolley
        if (m_creature->GetHealthPercent() < 51.0f)
        {
            if (m_uiFireballVolleyTimer < uiDiff)
            {
                DoCastSpellIfCan(m_creature->getVictim(), SPELL_FIREBALLVOLLEY);
                m_uiFireballVolleyTimer = 15000;
            }
            else
                m_uiFireballVolleyTimer -= uiDiff;
        }

        // MightyBlow
        if (m_uiMightyBlowTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_MIGHTYBLOW);
            m_uiMightyBlowTimer = 10000;
        }
        else
            m_uiMightyBlowTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_phalanx(Creature* pCreature)
{
    return new mob_phalanxAI(pCreature);
}

/*######
## npc_kharan_mighthammer
######*/
enum
{
    QUEST_WHAT_IS_GOING_ON = 4001,
    QUEST_KHARANS_TALE     = 4342
};

#define GOSSIP_ITEM_KHARAN_1    "I need to know where the princess are, Kharan!"
#define GOSSIP_ITEM_KHARAN_2    "All is not lost, Kharan!"

#define GOSSIP_ITEM_KHARAN_3    "Gor'shak is my friend, you can trust me."
#define GOSSIP_ITEM_KHARAN_4    "Not enough, you need to tell me more."
#define GOSSIP_ITEM_KHARAN_5    "So what happened?"
#define GOSSIP_ITEM_KHARAN_6    "Continue..."
#define GOSSIP_ITEM_KHARAN_7    "So you suspect that someone on the inside was involved? That they were tipped off?"
#define GOSSIP_ITEM_KHARAN_8    "Continue with your story please."
#define GOSSIP_ITEM_KHARAN_9    "Indeed."
#define GOSSIP_ITEM_KHARAN_10   "The door is open, Kharan. You are a free man."

bool GossipHello_npc_kharan_mighthammer(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(QUEST_WHAT_IS_GOING_ON) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KHARAN_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    if (pPlayer->GetQuestStatus(QUEST_KHARANS_TALE) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KHARAN_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);

    if (pPlayer->GetTeam() == HORDE)
        pPlayer->SEND_GOSSIP_MENU(2473, pCreature->GetGUID());
    else
        pPlayer->SEND_GOSSIP_MENU(2474, pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_kharan_mighthammer(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KHARAN_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            pPlayer->SEND_GOSSIP_MENU(2475, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KHARAN_4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
            pPlayer->SEND_GOSSIP_MENU(2476, pCreature->GetGUID());
            break;

        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KHARAN_5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
            pPlayer->SEND_GOSSIP_MENU(2477, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+4:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KHARAN_6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
            pPlayer->SEND_GOSSIP_MENU(2478, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+5:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KHARAN_7, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
            pPlayer->SEND_GOSSIP_MENU(2479, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+6:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KHARAN_8, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+7);
            pPlayer->SEND_GOSSIP_MENU(2480, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+7:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KHARAN_9, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+8);
            pPlayer->SEND_GOSSIP_MENU(2481, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+8:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KHARAN_10, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+9);
            pPlayer->SEND_GOSSIP_MENU(2482, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+9:
            pPlayer->CLOSE_GOSSIP_MENU();
            if (pPlayer->GetTeam() == HORDE)
                pPlayer->AreaExploredOrEventHappens(QUEST_WHAT_IS_GOING_ON);
            else
                pPlayer->AreaExploredOrEventHappens(QUEST_KHARANS_TALE);
            break;
    }
    return true;
}

/*######
## npc_lokhtos_darkbargainer
######*/

enum
{
    FACTION_THORIUM_BROTHERHOOD               = 59,
    
    ITEM_THRORIUM_BROTHERHOOD_CONTRACT        = 18628,
    ITEM_SULFURON_INGOT                       = 17203,
    
    QUEST_A_BINDING_CONTRACT                  = 7604,
    
    SPELL_CREATE_THORIUM_BROTHERHOOD_CONTRACT = 23059
};

#define GOSSIP_ITEM_SHOW_ACCESS     "Show me what I have access to, Lothos."
#define GOSSIP_ITEM_GET_CONTRACT    "Get Thorium Brotherhood Contract"

bool GossipHello_npc_lokhtos_darkbargainer(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pCreature->isVendor() && pPlayer->GetReputationRank(FACTION_THORIUM_BROTHERHOOD) >= REP_FRIENDLY)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_ITEM_SHOW_ACCESS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);

    if (!pPlayer->GetQuestRewardStatus(QUEST_A_BINDING_CONTRACT) &&
        !pPlayer->HasItemCount(ITEM_THRORIUM_BROTHERHOOD_CONTRACT, 1, true) &&
        pPlayer->HasItemCount(ITEM_SULFURON_INGOT, 1))
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GET_CONTRACT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    }

    if (pPlayer->GetReputationRank(FACTION_THORIUM_BROTHERHOOD) < REP_FRIENDLY)
        pPlayer->SEND_GOSSIP_MENU(3673, pCreature->GetGUID());
    else
        pPlayer->SEND_GOSSIP_MENU(3677, pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_lokhtos_darkbargainer(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->CastSpell(pPlayer, SPELL_CREATE_THORIUM_BROTHERHOOD_CONTRACT, false);
    }

    if (uiAction == GOSSIP_ACTION_TRADE)
        pPlayer->SEND_VENDORLIST(pCreature->GetGUID());

    return true;
}

/*######
## npc_rocknot
######*/

enum
{
    SAY_GOT_BEER       = -1230000,

    SPELL_DRUNKEN_RAGE = 14872,

    QUEST_ALE          = 4295
};

struct MANGOS_DLL_DECL npc_rocknotAI : public npc_escortAI
{
    npc_rocknotAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiBreakKegTimer;
    uint32 m_uiBreakDoorTimer;

    void Reset()
    {
        if (HasEscortState(STATE_ESCORT_ESCORTING))
            return;

        m_uiBreakKegTimer  = 0;
        m_uiBreakDoorTimer = 0;
    }

    void DoGo(uint32 id, uint32 state)
    {
        if (GameObject* pGo = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(id)))
            pGo->SetGoState(GOState(state));
    }

    void WaypointReached(uint32 uiPointId)
    {
        if (!m_pInstance)
            return;

        switch(uiPointId)
        {
            case 1:
                m_creature->HandleEmote(EMOTE_ONESHOT_KICK);
                break;
            case 2:
                m_creature->HandleEmote(EMOTE_ONESHOT_ATTACKUNARMED);
                break;
            case 3:
                m_creature->HandleEmote(EMOTE_ONESHOT_ATTACKUNARMED);
                break;
            case 4:
                m_creature->HandleEmote(EMOTE_ONESHOT_KICK);
                break;
            case 5:
                m_creature->HandleEmote(EMOTE_ONESHOT_KICK);
                m_uiBreakKegTimer = 2000;
                break;
        }
    }

    void UpdateEscortAI(const uint32 uiDiff)
    {
        if (!m_pInstance)
            return;

        if (m_uiBreakKegTimer)
        {
            if (m_uiBreakKegTimer <= uiDiff)
            {
                DoGo(DATA_GO_BAR_KEG,0);
                m_uiBreakKegTimer = 0;
                m_uiBreakDoorTimer = 1000;
            }
            else
                m_uiBreakKegTimer -= uiDiff;
        }

        if (m_uiBreakDoorTimer)
        {
            if (m_uiBreakDoorTimer <= uiDiff)
            {
                DoGo(DATA_GO_BAR_DOOR, 2);
                DoGo(DATA_GO_BAR_KEG_TRAP, 0);              //doesn't work very well, leaving code here for future
                                                            //spell by trap has effect61, this indicate the bar go hostile

                if (Creature* pTmp = m_creature->GetMap()->GetCreature(m_pInstance->GetData64(DATA_PHALANX)))
                    pTmp->setFaction(14);

                // for later, this event(s) has alot more to it.
                // optionally, DONE can trigger bar to go hostile.
                m_pInstance->SetData(TYPE_BAR, DONE);

                m_uiBreakDoorTimer = 0;
            }
            else
                m_uiBreakDoorTimer -= uiDiff;
        }
    }
};

CreatureAI* GetAI_npc_rocknot(Creature* pCreature)
{
    return new npc_rocknotAI(pCreature);
}

bool ChooseReward_npc_rocknot(Player* pPlayer, Creature* pCreature, const Quest* pQuest, uint32 item)
{
    ScriptedInstance* pInstance = (ScriptedInstance*)pCreature->GetInstanceData();

    if (!pInstance)
        return true;

    if (pInstance->GetData(TYPE_BAR) == DONE || pInstance->GetData(TYPE_BAR) == SPECIAL)
        return true;

    if (pQuest->GetQuestId() == QUEST_ALE)
    {
        if (pInstance->GetData(TYPE_BAR) != IN_PROGRESS)
            pInstance->SetData(TYPE_BAR,IN_PROGRESS);

        pInstance->SetData(TYPE_BAR,SPECIAL);

        // keep track of amount in instance script, returns SPECIAL if amount ok and event in progress
        if (pInstance->GetData(TYPE_BAR) == SPECIAL)
        {
            DoScriptText(SAY_GOT_BEER, pCreature);
            pCreature->CastSpell(pCreature, SPELL_DRUNKEN_RAGE, false);

            if (npc_rocknotAI* pEscortAI = dynamic_cast<npc_rocknotAI*>(pCreature->AI()))
                pEscortAI->Start(false, 0, NULL, true);
        }
    }

    return true;
}

/*######
## boss_coren_direbrew
######*/

enum
{
        QUEST_INSULT_COREN = 12062,

        SAY_PAY     = -1799998,
        SAY_AGGRO   = -1799997,

        SAY_IDLE1   = -1799996,
        SAY_IDLE2   = -1799995,
        SAY_IDLE3   = -1799994,
        SAY_IDLE4   = -1799993,

        SAY_ANTAGONIST1_1   = -1799992,
        SAY_ANTAGONIST1_2   = -1799991,
        SAY_ANTAGONIST1_3   = -1799990,
        SAY_ANTAGONIST2_1   = -1799989,
        SAY_ANTAGONIST2_2   = -1799988,
        SAY_ANTAGONIST2_3   = -1799987,
        SAY_ANTAGONIST4     = -1799986,

        MOB_ANTAGONIST  = 23795,
        MOB_ILSA        = 26764,
        MOB_URSULA      = 26822,
        MOB_MINION      = 26776,

        SPELL_DISARM    = 47310
};

float Coord[6][4] =
{
    {902.65f,-131.26f,-49.74f,5.94f},// Antagonist1
    {902.85f,-134.45f,-49.74f,0.49f},// Antagonist2
    {904.72f,-137.24f,-49.75f,1.34f},// Antagonist3
    {905.53f,-128.06f,-49.74f,5.04f},// Coren noncombat event movement point1
    {909.47f,-137.38f,-49.74f,1.01f},// Coren noncombat event movement point2
    {898.79f,-140.91f,-49.75f,0.48f} // Ursula and Ilsa spawn point
};

struct MANGOS_DLL_DECL boss_coren_direbrewAI : public npc_escortAI
{
    boss_coren_direbrewAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
       m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
       Reset();
    }

    ScriptedInstance* m_pInstance;

    bool m_bEventStarted;
    bool m_bLastPoint;
    bool m_bAntagonistAttacked;
    bool m_bIlsaSpawned;
    bool m_bUrsulaSpawned;

    // Adds GUIDs
    uint64 m_uiAntagonist1GUID;
    uint64 m_uiAntagonist2GUID;
    uint64 m_uiAntagonist3GUID;

    uint32 m_uiAggroYell_Timer;
    uint32 m_uiWalk_Timer;
    uint32 m_uiSpeach_Timer;
    uint32 m_uiMinion_Timer;
    uint32 m_uiDisarm_Timer;

    uint8 m_uiSpeach;
    uint8 m_uiWalk;
   
    void Reset()
    {
        DespawnAdds();
        // Player cannot turn quest before quest event begins
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        // Coren cannot be attacked before quest rewareded
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        SetEscortPaused(false);
        
        m_bEventStarted = false;
        m_bLastPoint = false;
        m_bAntagonistAttacked = false;
        m_bIlsaSpawned = false;
        m_bUrsulaSpawned = false;
        
        m_uiAggroYell_Timer = 10000;
        m_uiWalk_Timer = 0;
        m_uiSpeach_Timer = 0;
        m_uiSpeach = 0;
        m_uiWalk = 0;
        m_uiMinion_Timer = 10000;
        m_uiDisarm_Timer = 1000;
    }
   
   void NPCSay(uint64 guid, int32 text)
   {
        Creature* pPointer = (Creature*) m_creature->GetMap()->GetUnit(guid);
        if (pPointer && pPointer->isAlive())
            DoScriptText(text,pPointer,NULL);
   }

   void Despawn(uint64 guid)
   {
       if (Creature* pCreature = (Creature*) m_creature->GetMap()->GetUnit(guid))
            pCreature->ForcedDespawn();
   }

   void Assault(uint64 guid, uint32 faction, Unit* pTarget)
   {
       Creature* pCreature = (Creature*) m_creature->GetMap()->GetUnit(guid);
       if (pTarget && pCreature)
       {
           pCreature->setFaction(faction);
           pCreature->AI()->AttackStart(pTarget);
       }
   }

 
    void DespawnAdds()
    {
        Despawn(m_uiAntagonist1GUID);
        Despawn(m_uiAntagonist2GUID);
        Despawn(m_uiAntagonist3GUID);
    }

    void JustDied(Unit* pKiller)
    {
        DespawnAdds();
    }

    void WaypointReached (uint32 i)
    {
        switch(i)
        {
        case 1:
            Creature* pTemp;
            if (pTemp = m_creature->SummonCreature(MOB_ANTAGONIST, Coord[0][0], Coord[0][1], Coord[0][2], Coord[0][3], TEMPSUMMON_DEAD_DESPAWN, 0))
            {
                m_uiAntagonist1GUID = pTemp->GetGUID();
                pTemp = NULL;
            }
            if (pTemp = m_creature->SummonCreature(MOB_ANTAGONIST, Coord[1][0], Coord[1][1], Coord[1][2], Coord[1][3], TEMPSUMMON_DEAD_DESPAWN, 0))
            {
                m_uiAntagonist2GUID = pTemp->GetGUID();
                pTemp = NULL;
            }
            if (pTemp = m_creature->SummonCreature(MOB_ANTAGONIST, Coord[2][0], Coord[2][1], Coord[2][2], Coord[2][3], TEMPSUMMON_DEAD_DESPAWN, 0))
            {
                m_uiAntagonist3GUID = pTemp->GetGUID();
            }
            break;
        case 12:
            // When escort is paused we need to restore questgiver flags
            m_creature->SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            m_creature->SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            m_bLastPoint = true;
            SetEscortPaused(true);
            break;
        }
    }

    void MoveInLineOfSight (Unit* pWho)
    {
        if (!pWho)
            return;

        if (m_bEventStarted)
            return;

        if (pWho->GetTypeId() != TYPEID_PLAYER)
            return;

        Player* pPlayer = (Player*)pWho;
        if (!pPlayer)
            return;

        if (!m_bEventStarted && m_creature->GetDistance(pPlayer) < 10)
        {
            if (pPlayer->GetQuestStatus(QUEST_INSULT_COREN) == QUEST_STATUS_COMPLETE)
            {
                Start(false,pPlayer->GetGUID());
                m_bEventStarted = true;
            }
        }
    }

    void UpdateEscortAI(const uint32 uiDiff)
    {
        if (!m_creature->isInCombat() || !m_creature->SelectHostileTarget() || !m_creature->getVictim())
        {
            // After achieving last point of escort small noncombat event begins
            if (m_bLastPoint)
            {
                void GetAntagonists();
                // Coren Walking in front of Antagonists
                if (m_uiWalk_Timer < uiDiff)
                {
                    m_creature->AddSplineFlag(SPLINEFLAG_WALKMODE);
                    switch(m_uiWalk)
                    {
                        case 0:
                            m_creature->SendMonsterMove(Coord[3][0],Coord[3][1],Coord[3][2],SPLINETYPE_NORMAL,SPLINEFLAG_WALKMODE,6000);
                            m_uiWalk = 1;
                            break;
                        case 1:
                            m_creature->SendMonsterMove(Coord[4][0],Coord[4][1],Coord[4][2],SPLINETYPE_NORMAL,SPLINEFLAG_WALKMODE,6000);
                            m_uiWalk = 0;
                            break;
                    }
                    m_uiWalk_Timer = 6000;
                }
                else m_uiWalk_Timer -= uiDiff;

                // Coren Yell and Antagonists response
                if (m_uiSpeach_Timer < uiDiff)
                {
                    switch(m_uiSpeach)
                    {
                    case 0:
                        DoScriptText(SAY_IDLE1,m_creature);
                        m_uiSpeach = 1;
                        break;
                    case 1:
                        NPCSay(m_uiAntagonist1GUID,SAY_ANTAGONIST2_1);
                        NPCSay(m_uiAntagonist2GUID,SAY_ANTAGONIST2_2);
                        NPCSay(m_uiAntagonist3GUID,SAY_ANTAGONIST2_3);
                        m_uiSpeach = 2;
                        break;
                    case 2:
                        DoScriptText(SAY_IDLE2,m_creature);
                        m_uiSpeach = 3;
                        break;
                    case 3:
                        NPCSay(m_uiAntagonist1GUID,SAY_ANTAGONIST1_2);
                        NPCSay(m_uiAntagonist2GUID,SAY_ANTAGONIST1_3);
                        NPCSay(m_uiAntagonist3GUID,SAY_ANTAGONIST1_1);
                        m_uiSpeach = 4;
                        break;
                    case 4:
                        DoScriptText(SAY_IDLE3,m_creature);
                        m_uiSpeach = 5;
                        break;
                    case 5:
                        NPCSay(m_uiAntagonist1GUID,SAY_ANTAGONIST1_1);
                        NPCSay(m_uiAntagonist2GUID,SAY_ANTAGONIST1_2);
                        NPCSay(m_uiAntagonist3GUID,SAY_ANTAGONIST1_3);
                        m_uiSpeach = 6;
                        break;
                    case 6:
                        DoScriptText(SAY_IDLE4,m_creature);
                        m_uiSpeach = 7;
                        break;
                    case 7:
                        NPCSay(m_uiAntagonist1GUID,SAY_ANTAGONIST4);
                        NPCSay(m_uiAntagonist2GUID,SAY_ANTAGONIST4);
                        NPCSay(m_uiAntagonist3GUID,SAY_ANTAGONIST4);
                        m_uiSpeach = 0;
                        break;
                    }
                    m_uiSpeach_Timer = 5000;
                }else m_uiSpeach_Timer -=uiDiff;
            }
        }
        else 
        {
            //Force Antagonist to assist Coren in combat
            if (m_creature->getVictim() && !m_bAntagonistAttacked)
            {
                Assault(m_uiAntagonist1GUID,m_creature->getFaction(),m_creature->getVictim());
                Assault(m_uiAntagonist2GUID,m_creature->getFaction(),m_creature->getVictim());
                Assault(m_uiAntagonist3GUID,m_creature->getFaction(),m_creature->getVictim());
                m_bAntagonistAttacked = true;
            }

            if (!m_bIlsaSpawned && ((m_creature->GetHealth()*100) / m_creature->GetMaxHealth() <= 66))
            {
                Creature* Ilsa = m_creature->SummonCreature(MOB_ILSA,Coord[5][0],Coord[5][1],Coord[5][2],Coord[5][3],TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,20000);
                if (Ilsa && m_creature->getVictim()) // i know if(victim) was checked at the top but once got crash with multithreaded mangos
                    {
                        Ilsa->AI()->AttackStart(m_creature->getVictim());
                        m_bIlsaSpawned = true;
                    }
            }

            if (!m_bUrsulaSpawned && ((m_creature->GetHealth()*100) / m_creature->GetMaxHealth() <= 33))
            {
                Creature* Ursula = m_creature->SummonCreature(MOB_URSULA,Coord[5][0],Coord[5][1],Coord[5][2],Coord[5][3],TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,20000);
                if (Ursula && m_creature->getVictim())// i know if(victim) was checked at the top but once got crash with multithreaded mangos
                    {
                        Ursula->AI()->AttackStart(m_creature->getVictim());
                        m_bUrsulaSpawned = true;
                    }
            }

        if (m_uiMinion_Timer < uiDiff)
        {
            if (m_pInstance)
                if(Creature* pMinion = m_creature->SummonCreature(MOB_MINION,m_creature->GetPositionX()+rand()%20,m_creature->GetPositionY()+rand()%20,m_creature->GetPositionZ(),0,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,20000))
                {
                    pMinion->AI()->AttackStart(m_creature->getVictim());
                    m_uiMinion_Timer = 23000;
                }
                    
        }else m_uiMinion_Timer -= uiDiff;

        if (m_uiAggroYell_Timer < uiDiff)
        {
            DoScriptText(SAY_AGGRO,m_creature);
            m_uiAggroYell_Timer = 45000 + (rand()%45000);
        }
        else m_uiAggroYell_Timer -= uiDiff;

        if(m_uiDisarm_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_DISARM);
            m_uiDisarm_Timer = 15000;
        }
        else m_uiDisarm_Timer -= uiDiff;

        DoMeleeAttackIfReady();
        }
    }
};

CreatureAI* GetAI_boss_coren_direbrew(Creature* pCreature)
{
    return new boss_coren_direbrewAI(pCreature);
}

bool ChooseReward_boss_coren_direbrew(Player* pPlayer, Creature* pCreature, const Quest* pQuest, uint32 slot)
{

    if (pPlayer && pQuest->GetQuestId() == QUEST_INSULT_COREN)
        if (boss_coren_direbrewAI* pEscortAI = dynamic_cast<boss_coren_direbrewAI*>(pCreature->AI()))
        {
            DoScriptText(SAY_PAY,pCreature,pPlayer);
            pCreature->setFaction(16);
            pEscortAI->AttackStart(pPlayer);
            pCreature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }
    return true;
}

void AddSC_blackrock_depths()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "go_shadowforge_brazier";
    pNewScript->pGOHello = &GOHello_go_shadowforge_brazier;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "at_ring_of_law";
    pNewScript->pAreaTrigger = &AreaTrigger_at_ring_of_law;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_grimstone";
    pNewScript->GetAI = &GetAI_npc_grimstone;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_phalanx";
    pNewScript->GetAI = &GetAI_mob_phalanx;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_kharan_mighthammer";
    pNewScript->pGossipHello =  &GossipHello_npc_kharan_mighthammer;
    pNewScript->pGossipSelect = &GossipSelect_npc_kharan_mighthammer;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_lokhtos_darkbargainer";
    pNewScript->pGossipHello =  &GossipHello_npc_lokhtos_darkbargainer;
    pNewScript->pGossipSelect = &GossipSelect_npc_lokhtos_darkbargainer;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_rocknot";
    pNewScript->GetAI = &GetAI_npc_rocknot;
    pNewScript->pChooseReward = &ChooseReward_npc_rocknot;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_coren_direbrew";
    pNewScript->GetAI = &GetAI_boss_coren_direbrew;
    pNewScript->pChooseReward = &ChooseReward_boss_coren_direbrew;
    pNewScript->RegisterSelf();
}
