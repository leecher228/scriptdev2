-- fixes for instance violet hold
UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`='30658';
UPDATE `creature_template` SET `ScriptName`='npc_azure_saboteur' WHERE `entry`='31079';
UPDATE `creature_template` SET `ScriptName`='boss_cyanigosa' WHERE `entry`='31134';
UPDATE `creature_template` SET `ScriptName`='boss_erekem' WHERE `entry`='29315';
UPDATE `creature_template` SET `ScriptName`='mob_erekem_guard' WHERE `entry`='29395';
UPDATE `creature_template` SET `ScriptName`='boss_ichoron' WHERE `entry`='29313';
UPDATE `creature_template` SET `ScriptName`='mob_ichor_globule',`modelid_1`=5492, `modelid_3`=5492 WHERE `entry`='29321';
UPDATE `creature_template` SET `modelid_1`=5492, `modelid_3`=5492 WHERE `entry`='31515'; -- heroic
UPDATE `creature_template` SET `ScriptName`='boss_lavanthor' WHERE `entry`='29312';
UPDATE `creature_template` SET `ScriptName`='boss_moragg' WHERE `entry`='29316';
UPDATE `creature_template` SET `ScriptName`='boss_xevozz' WHERE `entry`='29266';
UPDATE `creature_template` SET `ScriptName`='mob_ethereal_sphere' WHERE `entry`='29271';
UPDATE `creature_template` SET `ScriptName`='boss_zuramat' WHERE `entry`='29314';
UPDATE `creature_template` SET `ScriptName`='mob_zuramat_sentry' WHERE `entry`='29364';

UPDATE `gameobject_template` SET `flags`=`flags`|4 WHERE `entry` IN (191723,191564,191563,191562,191606,191722,191556,191566,191565); -- door untargetable

DELETE FROM `spell_script_target` WHERE `entry` IN (54160,59474);
INSERT INTO `spell_script_target` VALUES (54160, 1, 29266),
(59474, 1, 29266);

UPDATE `creature_template` SET `minhealth` = 500, `maxhealth` = 700, `minlevel` = 77, `maxlevel` = 77, `mindmg` = 220, `maxdmg` = 270, `minrangedmg` = 170, `maxrangedmg` = 260, `attackpower` = 350, `rangedattackpower` = 60 WHERE `entry` = 29364;

-- not known if needed
-- UPDATE `creature_template` SET `unit_flags`=33816580 WHERE `entry`=30896;

-- mechanic immune masks
UPDATE creature_template SET mechanic_immune_mask = '617299803' WHERE entry IN(29315,29316,29313,29266,29312,29314,31134,31506,31507,31508,31509,31510,31511,31512);

-- fix reputation for mobs
DELETE FROM `creature_onkill_reputation` WHERE `creature_id` IN ('31512','31511','31502','31501','31504','31503','31510','31500','31509','31508','31507','31506','31493','31496','31495','31494','31492','31490','32192','31498','31499','31497','31486','31489','31488','31487','31485','31484','31483');
INSERT INTO `creature_onkill_reputation` (`creature_id`, `RewOnKillRepFaction1`, `RewOnKillRepFaction2`, `MaxStanding1`, `IsTeamAward1`, `RewOnKillRepValue1`, `MaxStanding2`, `IsTeamAward2`, `RewOnKillRepValue2`, `TeamDependent`) VALUES
('31483', '1037', '1052', '7', '0', '5', '7', '0', '5', '1'),
('31484', '1037', '1052', '7', '0', '5', '7', '0', '5', '1'),
('31485', '1037', '1052', '7', '0', '5', '7', '0', '5', '1'),
('31487', '1037', '1052', '7', '0', '5', '7', '0', '5', '1'),
('31488', '1037', '1052', '7', '0', '5', '7', '0', '5', '1'),
('31489', '1037', '1052', '7', '0', '5', '7', '0', '5', '1'),
('31486', '1037', '1052', '7', '0', '15', '7', '0', '15', '1'),
('31497', '1037', '1052', '7', '0', '5', '7', '0', '5', '1'),
('31499', '1037', '1052', '7', '0', '5', '7', '0', '5', '1'),
('31498', '1037', '1052', '7', '0', '5', '7', '0', '5', '1'),
('32192', '1037', '1052', '7', '0', '15', '7', '0', '15', '1'),
('31490', '1037', '1052', '7', '0', '15', '7', '0', '15', '1'),
('31492', '1037', '1052', '7', '0', '5', '7', '0', '5', '1'),
('31494', '1037', '1052', '7', '0', '5', '7', '0', '5', '1'),
('31495', '1037', '1052', '7', '0', '5', '7', '0', '5', '1'),
('31496', '1037', '1052', '7', '0', '5', '7', '0', '5', '1'),
('31493', '1037', '1052', '7', '0', '15', '7', '0', '15', '1'),
('31506', '1037', '1052', '7', '0', '250', '7', '0', '250', '1'),
('31507', '1037', '1052', '7', '0', '250', '7', '0', '250', '1'),
('31508', '1037', '1052', '7', '0', '250', '7', '0', '250', '1'),
('31509', '1037', '1052', '7', '0', '250', '7', '0', '250', '1'),
('31500', '1037', '1052', '7', '0', '5', '7', '0', '5', '1'),
('31510', '1037', '1052', '7', '0', '250', '7', '0', '250', '1'),
('31503', '1037', '1052', '7', '0', '30', '7', '0', '30', '1'),
('31504', '1037', '1052', '7', '0', '30', '7', '0', '30', '1'),
('31501', '1037', '1052', '7', '0', '30', '7', '0', '30', '1'),
('31502', '1037', '1052', '7', '0', '30', '7', '0', '30', '1'),
('31511', '1037', '1052', '7', '0', '250', '7', '0', '250', '1'),
('31512', '1037', '1052', '7', '0', '250', '7', '0', '250', '1');
