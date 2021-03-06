-- netherspite
/* Portale: not attackable, not selectable, NullAI zur Sicherheit */
UPDATE `creature_template` SET `unit_flags` = 0x02000002, `AIName` = 'NullAI' WHERE `entry` IN(17367,17368,17369);
/* Voidzone: not attackable, not selectable, pacified, NullAI */
UPDATE `creature_template` SET `unit_flags` = 0x02020002, `type_flags` = '1026', `AIName` = 'NullAI' WHERE `entry` =16697;
/*Voidzone: aoe dmg aura*/
DELETE FROM `creature_template_addon` WHERE `entry` = 16697;
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `bytes2`, `emote`, `moveflags`, `auras`) VALUES
('16697', '0', '0', '0', '0', '0', '30497 0');
/* Netherspite: Scriptname und boundig radius (auch wenn man das eigentlich nicht ändern soll)*/
UPDATE `creature_model_info` SET `bounding_radius` = '10' WHERE `creature_model_info`.`modelid` =15363;
UPDATE `creature_template` SET `ScriptName`='boss_netherspite' WHERE `entry`='15689';

-- trash
UPDATE creature_template SET minhealth=55439, maxhealth=55439 WHERE entry=17229;
UPDATE creature SET curhealth=55439 WHERE id=17229;
