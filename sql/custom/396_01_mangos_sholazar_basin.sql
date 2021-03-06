-- sholazar basin fixes

-- fix quest 12688
UPDATE `creature_template` SET `ScriptName` = 'npc_engineer_helice' WHERE entry = 28787;

-- fix quest 12532
DELETE FROM `creature` WHERE `id` = 28161;
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES
(28161, 571, 1, 1, 0, 0, 5190.4, 4571.54, -102.378, 3.80362, 25, 5, 0, 1, 0, 0, 1),
(28161, 571, 1, 1, 0, 0, 5174.2, 4558.92, -102.739, 3.80362, 25, 5, 0, 1, 0, 0, 1),
(28161, 571, 1, 1, 0, 0, 5179.45, 4557.77, -100.218, 0.808116, 25, 5, 0, 1, 0, 0, 1),
(28161, 571, 1, 1, 0, 0, 5174.86, 4546.15, -98.9565, 4.32278, 25, 5, 0, 1, 0, 0, 1),
(28161, 571, 1, 1, 0, 0, 5168.98, 4534.39, -97.3293, 4.00077, 25, 5, 0, 1, 0, 0, 1),
(28161, 571, 1, 1, 0, 0, 5156.71, 4540.77, -97.5804, 1.07594, 25, 5, 0, 1, 0, 0, 1),
(28161, 571, 1, 1, 0, 0, 5212.14, 4553.01, -95.3657, 0.939282, 25, 5, 0, 1, 0, 0, 1),
(28161, 571, 1, 1, 0, 0, 5246.05, 4561.46, -91.9413, 0.413066, 25, 5, 0, 1, 0, 0, 1),
(28161, 571, 1, 1, 0, 0, 5239.75, 4562.96, -91.0187, 3.21223, 25, 5, 0, 1, 0, 0, 1),
(28161, 571, 1, 1, 0, 0, 5263.64, 4564.33, -89.5545, 0.565433, 25, 5, 0, 1, 0, 0, 1),
(28161, 571, 1, 1, 0, 0, 5274.27, 4559.52, -86.6077, 5.81975, 25, 5, 0, 1, 0, 0, 1),
(28161, 571, 1, 1, 0, 0, 5317.8, 4536.26, -97.4372, 1.60373, 25, 5, 0, 1, 0, 0, 1),
(28161, 571, 1, 1, 0, 0, 5317.58, 4543.02, -96.4277, 1.60373, 25, 5, 0, 1, 0, 0, 1),
(28161, 571, 1, 1, 0, 0, 5313.79, 4522.64, -97.9109, 4.19476, 25, 5, 0, 1, 0, 0, 1),
(28161, 571, 1, 1, 0, 0, 5324.13, 4508.97, -97.858, 1.26758, 25, 5, 0, 1, 0, 0, 1),
(28161, 571, 1, 1, 0, 0, 5282.61, 4409.38, -96.2805, 4.88277, 25, 5, 0, 1, 0, 0, 1),
(28161, 571, 1, 1, 0, 0, 5273.41, 4390.85, -96.2771, 3.83426, 25, 5, 0, 1, 0, 0, 1),
(28161, 571, 1, 1, 0, 0, 5260.79, 4388.52, -95.2331, 3.29627, 25, 5, 0, 1, 0, 0, 1),
(28161, 571, 1, 1, 0, 0, 5246.28, 4399.47, -95.2409, 2.49516, 25, 5, 0, 1, 0, 0, 1),
(28161, 571, 1, 1, 0, 0, 5264.74, 4401.47, -94.8276, 0.107547, 25, 5, 0, 1, 0, 0, 1),
(28161, 571, 1, 1, 0, 0, 5239.8, 4432.74, -92.6718, 1.87941, 25, 5, 0, 1, 0, 0, 1),
(28161, 571, 1, 1, 0, 0, 5193.29, 4451.03, -90.1913, 2.52343, 25, 5, 0, 1, 0, 0, 1),
(28161, 571, 1, 1, 0, 0, 5206.27, 4452.23, -90.7965, 0.0965526, 25, 5, 0, 1, 0, 0, 1);

-- fix quest 12544
INSERT INTO `event_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `datalong3`, `datalong4`, `data_flags`, `dataint`, `x`, `y`, `z`, `o`) VALUES
('18481','0','10','28256','120000','0','0','0','0','5218.2485','5776.6992','-71.2309','2.462964');
UPDATE `creature_template` SET `ScriptName` = 'mob_voiceofnozronn' WHERE `entry` = 28256;

-- fix quest 12531
-- not the best way, but EventAI of this mob is corrupted somehow, so disable this part
-- TODO: fix EventAI instead of removing this
UPDATE `creature_ai_scripts` SET `creature_id` = 0 WHERE `id` IN (2808301,2808306,2808309);
UPDATE creature_template SET unit_flags=0 WHERE entry=28083;

-- fix quest 12621 
UPDATE `creature_template` SET `gossip_menu_id` = '27800' WHERE `entry` =27801;
UPDATE `quest_template` SET `SpecialFlags` = 0 WHERE `entry` = 12621;
DELETE FROM `gossip_menu` WHERE `entry` IN (27800, 27801, 27802, 27803);
INSERT INTO `gossip_menu` (`entry`,`text_id`, `cond_1`, `cond_1_val_1` ) VALUES 
('27800', '13303', '9', '12621'),
('27801', '13304', '9', '12621'),
('27802', '13305', '9', '12621'),
('27803', '1', '9', '12621');
DELETE FROM `gossip_menu_option` WHERE `menu_id` IN (27800, 27801, 27802, 27803);
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_script_id` ,`cond_1`, `cond_1_val_1`, `cond_1_val_2`) VALUES 
('27800', '0', '0', 'I want to stop the Scourge as much as you do. How can I help?', '1', '1', '27801' , '0', '9', '12621', '0'),
('27800', '1', '0', 'GOSSIP_OPTION_QUESTGIVER', '2', '2', '0', '0', '0', '0', '0'),
('27801', '0', '0', 'You can trust me. I am no friend of the Lich King.', '1', '1', '27802' , '0', '9', '12621', '0'),
('27802', '0', '0', 'I will not fail.', '1', '1', '27803' , '126211', '9', '12621', '0'),
('27803', '0', '0', 'GOSSIP_OPTION_QUESTGIVER', '2', '2', '0', '0', '0', '0', '0');
DELETE FROM `gossip_scripts` WHERE `id`= 126211;
INSERT INTO `gossip_scripts` (`id`,`delay`,`command`,`datalong`,`datalong2`,`comments`)  VALUES 
('126211', '0', '15', '52045', '0', 'Quest 12621 Credit Spell');

-- set item 44117 not lootable
DELETE FROM `reference_loot_template` WHERE `item` = 44117; 

-- items for quests 12533, 12536
UPDATE `quest_template` SET `SrcItemId` = '38621', `SrcItemCount` = '1' WHERE `entry` = '12533';
UPDATE `quest_template` SET `SrcItemId` = '38512', `SrcItemCount` = '1' WHERE `entry` = '12536';
UPDATE `creature_template` SET `gossip_menu_id` = '28138' WHERE `entry` = '28138';
DELETE FROM `npc_text` WHERE `ID` = '28138';
INSERT INTO `npc_text` (`ID`, `text0_0`) VALUES 
('28138', 'Stay a while and listen.');
DELETE FROM `locales_npc_text` WHERE `entry` = '28138';
INSERT INTO `locales_npc_text` (`entry`, `Text0_0_loc3`) VALUES 
('28138', 'Bleib eine Weile und höre zu.');
DELETE FROM `gossip_menu` WHERE `entry` = '28138';
INSERT INTO `gossip_menu` (`entry`,`text_id`, `cond_1`, `cond_1_val_1` ) VALUES 
('28138', '28138', '0', '0');
DELETE FROM `gossip_menu_option` WHERE `menu_id` = '28138';
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_script_id` ,`cond_1`, `cond_1_val_1`, `cond_1_val_2`, `cond_2`, `cond_2_val_1`, `cond_2_val_2`, `cond_3`, `cond_3_val_1`, `cond_3_val_2`) VALUES 
('28138', '0', '0', 'GOSSIP_OPTION_QUESTGIVER', '2', '2', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'),
-- todo update gossiptext (not blizzlike)
('28138', '1', '0', 'I have lost Goregek\'s Shackles', '1', '1', '28138', '52542', '8', '12528', '0', '16', '38619', '1', '22', '12530', '0'),
('28138', '2', '0', 'I have lost Dajik\'s Worn Chalk', '1', '1', '28138', '52544', '8', '12530', '0', '16', '38621', '1', '22', '12536', '0'),
('28138', '3', '0', 'I have lost Zepik\'s Hunting Horn', '1', '1', '28138', '52545', '8', '12531', '0', '16', '38512', '1', '22', '12539', '0');
DELETE FROM `gossip_scripts` WHERE `id` IN ( '52542', '52544','52545') ;
INSERT INTO `gossip_scripts` (`id`,`delay`,`command`,`datalong`,`datalong2`,`comments`)  VALUES 
('52542', '0', '15', '52542', '0', 'add Item 38619 Goregek\'s Shackles'),
('52544', '0', '15', '52544', '0', 'add Item 38621 Dajik\'s Worn Chalk'),
('52545', '0', '15', '52545', '0', 'add Item 38512 Zepik\'s Hunting Horn');

-- fix quest 12548
DELETE FROM areatrigger_teleport WHERE id ='5046';
INSERT INTO areatrigger_teleport (id, NAME, required_level, required_item, required_item2, heroic_key, heroic_key2, required_quest_done, required_quest_done_heroic, required_failed_text, target_map, target_position_x, target_position_y, target_position_z, target_orientation)VALUES
('5046', 'The_Waygate_Sholazar', '1', '0', '0', '0', '0', '12559', '0', '0', '1', '-6161.8', '-1332.13', '-168.965', '2.35776');
DELETE FROM areatrigger_teleport WHERE id ='5047';
INSERT INTO areatrigger_teleport (id, NAME, required_level, required_item, required_item2, heroic_key, heroic_key2, required_quest_done, required_quest_done_heroic, required_failed_text, target_map, target_position_x, target_position_y, target_position_z, target_orientation)VALUES
('5047', 'The_Waygate_Ungoro', '1', '0', '0', '0', '0', '12559', '0', '0', '571', '4885.993', '5175.694', '-84.863', '0.450570');
