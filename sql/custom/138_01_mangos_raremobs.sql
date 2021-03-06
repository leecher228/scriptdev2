# add missing rare mobs into pool system
# creature guids and pool entrys possibly have bad IDs

# burning crusade mobs
DELETE FROM `creature` WHERE `guid` BETWEEN 300000 AND 300036;
DELETE FROM `pool_template` WHERE `entry` BETWEEN 1850 AND 1861;
DELETE FROM `pool_creature` WHERE `guid` BETWEEN 300000 AND 300035;

INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES (300000, '18695', '530', '1', '1', '0', '0', '-3237.681152', '1018.319702', '61.264862', '2.134655', '86400', '15', '0', '13500', '0', '0', '1'),
(300001, '18695', '530', '1', '1', '0', '0', '-4185.557617', '440.016296', '32.107979', '4.011782', '86400', '15', '0', '13500', '0', '0', '1'),
(300002, '18695', '530', '1', '1', '0', '0', '-3929.701904', '2680.625000', '118.257408', '4.208324', '86400', '15', '0', '13500', '0', '0', '1');
INSERT INTO `pool_template` (`entry`,`max_limit`,`description`) VALUES (1850,1," Outland rare - Ambassador Jerrika (18695)");
INSERT INTO `pool_creature` (`guid`,`pool_entry`,`chance`,`description`) VALUES (300000,1850,0,"Ambassador Jerrika (18695) - Spawn 1"),
(300001,1850,0,"Ambassador Jerrika (18695) - Spawn 2"),
(300002,1850,0,"Ambassador Jerrika (18695) - Spawn 3");

INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES (300003, '18697', '530', '1', '1', '0', '0', '2460.794434', '2891.318604', '128.684021', '2.695679', '86400', '15', '0', '10800', '15400', '0', '1'),
(300004, '18697', '530', '1', '1', '0', '0', '4090.4767074', '3992.803223', '192.818680', '2.777372', '86400', '15', '0', '10800', '15400', '0', '1'),
(300005, '18697', '530', '1', '1', '0', '0', '3045.405273', '2247.408936', '154.906952', '0.741065', '86400', '15', '0', '10800', '15400', '0', '1');
INSERT INTO `pool_template` (`entry`,`max_limit`,`description`) VALUES (1851,1," Outland rare - Chief Engineer Lorthander (18697)");
INSERT INTO `pool_creature` (`guid`,`pool_entry`,`chance`,`description`) VALUES (300003,1851,0,"Chief Engineer Lorthander (18697) - Spawn 1"),
(300004,1851,0,"Chief Engineer Lorthander (18697) - Spawn 2"),
(300005,1851,0,"Chief Engineer Lorthander (18697) - Spawn 3");

INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES (300006, '18686', '530', '1', '1', '0', '0', '-2433.179688', '5097.484375', '8.662614', '3.001749', '86400', '15', '0', '9140', '13500', '0', '1'),
(300007, '18686', '530', '1', '1', '0', '0', '-2547.578857', '3417.656738', '-3.045719', '2.810343', '86400', '15', '0', '9140', '13500', '0', '1'),
(300008, '18686', '530', '1', '1', '0', '0', '-1797.334717', '4283.257812', '25.076462', '3.344168', '86400', '15', '0', '9140', '13500', '0', '1');
INSERT INTO `pool_template` (`entry`,`max_limit`,`description`) VALUES (1852,1," Outland rare - Doomsayer Jurim (18686)");
INSERT INTO `pool_creature` (`guid`,`pool_entry`,`chance`,`description`) VALUES (300006,1851,0,"Doomsayer Jurim (18686) - Spawn 1"),
(300007,1851,0,"Doomsayer Jurim (18686) - Spawn 2"),
(300008,1851,0,"Doomsayer Jurim (18686) - Spawn 3");

INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES (300009, '18678', '530', '1', '1', '0', '0', '-47.339607', '4176.867188', '81.006584', '2.092331', '86400', '15', '0', '10700', '0', '0', '1'),
(300010, '18678', '530', '1', '1', '0', '0', '-1079.063599', '2540.306396', '16.563498', '1.765931', '86400', '15', '0', '10700', '0', '0', '1'),
(300011, '18678', '530', '1', '1', '0', '0', '80.097626', '3899.460205', '87.060349', '2.122477', '86400', '15', '0', '10700', '0', '0', '1');
INSERT INTO `pool_template` (`entry`,`max_limit`,`description`) VALUES (1853,1," Outland rare - Fulgorge (18678)");
INSERT INTO `pool_creature` (`guid`,`pool_entry`,`chance`,`description`) VALUES (300009,1851,0,"Fulgorge (18678) - Spawn 1"),
(300010,1851,0,"Fulgorge (18678) - Spawn 2"),
(300011,1851,0,"Fulgorge (18678) - Spawn 3");

INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES (300012, '18692', '530', '1', '1', '0', '0', '2126.164795', '7259.093262', '364.822968', '3.465213', '86400', '15', '0', '13100', '0', '0', '1'),
(300013, '18692', '530', '1', '1', '0', '0', '2652.212158', '7339.860352', '363.560760', '4.098254', '86400', '15', '0', '13100', '0', '0', '1'),
(300014, '18692', '530', '1', '1', '0', '0', '2212.915771', '7038.781250', '363.949432', '1.123166', '86400', '15', '0', '13100', '0', '0', '1');
INSERT INTO `pool_template` (`entry`,`max_limit`,`description`) VALUES (1854,1," Outland rare - Hemathion (18692)");
INSERT INTO `pool_creature` (`guid`,`pool_entry`,`chance`,`description`) VALUES (300012,1851,0,"Hemathion (18692) - Spawn 1"),
(300013,1851,0,"Hemathion (18692) - Spawn 2"),
(300014,1851,0,"Hemathion (18692) - Spawn 3");

INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES (300015, '18683', '530', '1', '1', '0', '0', '-2784.940186', '8455.953125', '-38.460110', '4.152437', '86400', '15', '0', '10500', '12000', '0', '1'),
(300016, '18683', '530', '1', '1', '0', '0', '-2467.787354', '8415.733398', '-36.310673', '0.838840', '86400', '15', '0', '10500', '12000', '0', '1'),
(300017, '18683', '530', '1', '1', '0', '0', '-2459.008789', '8031.260254', '-47.942081', '4.262394', '86400', '15', '0', '10500', '12000', '0', '1');
INSERT INTO `pool_template` (`entry`,`max_limit`,`description`) VALUES (1855,1," Outland rare - Voidhunter Yar (18683)");
INSERT INTO `pool_creature` (`guid`,`pool_entry`,`chance`,`description`) VALUES (300015,1851,0,"Voidhunter Yar (18683) - Spawn 1"),
(300016,1851,0,"Voidhunter Yar (18683) - Spawn 2"),
(300017,1851,0,"Voidhunter Yar (18683) - Spawn 3");

INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES (300018, '18689', '530', '1', '1', '0', '0', '-2836.140625', '5243.291016', '-9.498530', '4.174833', '86400', '15', '0', '11800', '0', '0', '1'),
(300019, '18689', '530', '1', '1', '0', '0', '-3749.400732', '4819.921387', '-18.763035', '2.045631', '86400', '15', '0', '11800', '0', '0', '1'),
(300020, '18689', '530', '1', '1', '0', '0', '-3586.409180', '5328.696777', '-19.243772', '1.253949', '86400', '15', '0', '11800', '0', '0', '1');
INSERT INTO `pool_template` (`entry`,`max_limit`,`description`) VALUES (1856,1," Outland rare - Crippler (18689)");
INSERT INTO `pool_creature` (`guid`,`pool_entry`,`chance`,`description`) VALUES (300018,1851,0,"Crippler (18689) - Spawn 1"),
(300019,1851,0,"Crippler (18689) - Spawn 2"),
(300020,1851,0,"Crippler (18689) - Spawn 3");

INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES (300021, '18698', '530', '1', '1', '0', '0', '3009.432861', '4189.224121', '160.827698', '1.426700', '86400', '15', '0', '10400', '5970', '0', '1'),
(300022, '18698', '530', '1', '1', '0', '0', '4289.955566', '1942.021118', '129.690918', '1.087917', '86400', '15', '0', '10400', '5970', '0', '1'),
(300023, '18698', '530', '1', '1', '0', '0', '4062.319824', '3790.450928', '116.618645', '3.864343', '86400', '15', '0', '10400', '5970', '0', '1');
INSERT INTO `pool_template` (`entry`,`max_limit`,`description`) VALUES (1857,1," Outland rare - Ever-Core the Punisher (18698)");
INSERT INTO `pool_creature` (`guid`,`pool_entry`,`chance`,`description`) VALUES (300021,1851,0,"Ever-Core the Punisher (18698) - Spawn 1"),
(300022,1851,0,"Ever-Core the Punisher (18698) - Spawn 2"),
(300023,1851,0,"Ever-Core the Punisher (18698) - Spawn 3");

INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES (300024, '17144', '530', '1', '1', '0', '0', '-1525.552734', '8069.183594', '-99.606117', '4.857725', '86400', '15', '0', '11800', '0', '0', '1'),
(300025, '17144', '530', '1', '1', '0', '0', '-1630.942139', '8252.359375', '-31.224432', '2.488175', '86400', '15', '0', '11800', '0', '0', '1'),
(300026, '17144', '530', '1', '1', '0', '0', '-959.301575', '7003.530273', '23.232496', '3.114249', '86400', '15', '0', '11800', '0', '0', '1');
INSERT INTO `pool_template` (`entry`,`max_limit`,`description`) VALUES (1858,1," Outland rare - Goretooth (17144)");
INSERT INTO `pool_creature` (`guid`,`pool_entry`,`chance`,`description`) VALUES (300024,1851,0,"Goretooth (17144) - Spawn 1"),
(300025,1851,0,"Goretooth (17144) - Spawn 2"),
(300026,1851,0,"Goretooth (17144) - Spawn 3");

INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES (300027, '18677', '530', '1', '1', '0', '0', '-223.314697', '2968.788574', '-58.505398', '3.008394', '86400', '15', '0', '10400', '0', '0', '1'),
(300028, '18677', '530', '1', '1', '0', '0', '-1097.265747', '1961.782837', '73.858154', '2.537202', '86400', '15', '0', '10400', '0', '0', '1'),
(300029, '18677', '530', '1', '1', '0', '0', '-63.120411', '3153.531738', '-4.239535', '6.003150', '86400', '15', '0', '10400', '0', '0', '1');
INSERT INTO `pool_template` (`entry`,`max_limit`,`description`) VALUES (1859,1," Outland rare - Mekthorg the Wild (18677)");
INSERT INTO `pool_creature` (`guid`,`pool_entry`,`chance`,`description`) VALUES (300027,1851,0,"Mekthorg the Wild (18677) - Spawn 1"),
(300028,1851,0,"Mekthorg the Wild (18677) - Spawn 2"),
(300029,1851,0,"Mekthorg the Wild (18677) - Spawn 3");

INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES (300030, '18693', '530', '1', '1', '0', '0', '2497.815430', '6629.513184', '0.848387', '3.900326', '86400', '15', '0', '10500', '8970', '0', '1'),
(300031, '18693', '530', '1', '1', '0', '0', '1686.986206', '6255.636230', '2.101650', '0.578088', '86400', '15', '0', '10500', '8970', '0', '1'),
(300032, '18693', '530', '1', '1', '0', '0', '3677.605225', '5232.106445', '-14.994740', '1.833064', '86400', '15', '0', '10500', '8970', '0', '1');
INSERT INTO `pool_template` (`entry`,`max_limit`,`description`) VALUES (1860,1," Outland rare - Speaker Mar'grom (18693)");
INSERT INTO `pool_creature` (`guid`,`pool_entry`,`chance`,`description`) VALUES (300030,1851,0,"Speaker Mar'grom (18693) - Spawn 1"),
(300031,1851,0,"Speaker Mar'grom (18693) - Spawn 2"),
(300032,1851,0,"Speaker Mar'grom (18693) - Spawn 3");

INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES (300033, '18679', '530', '1', '1', '0', '0', '-405.282379', '1741.967041', '54.373188', '0.369346', '86400', '15', '0', '8550', '2570', '0', '1'),
(300034, '18679', '530', '1', '1', '0', '0', '366.772095', '3528.892334', '69.541054', '3.882576', '86400', '15', '0', '8550', '2570', '0', '1'),
(300035, '18679', '530', '1', '1', '0', '0', '465.576996', '2514.848633', '160.153107', '3.387015', '86400', '15', '0', '8550', '2570', '0', '1');
INSERT INTO `pool_template` (`entry`,`max_limit`,`description`) VALUES (1861,1," Outland rare - Vorakem Doomspeaker (18679)");
INSERT INTO `pool_creature` (`guid`,`pool_entry`,`chance`,`description`) VALUES (300033,1851,0,"Vorakem Doomspeaker (18679) - Spawn 1"),
(300034,1851,0,"Vorakem Doomspeaker (18679) - Spawn 2"),
(300035,1851,0,"Vorakem Doomspeaker (18679) - Spawn 3");

# vanilla
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES (300036, '14232', '1', '1', '1', '0', '0', '-2524.266846', '-3489.695801', '42.588753', '2.567490', '86400', '15', '0', '1600', '0', '0', '1');

UPDATE `creature_template` SET `faction_A` = 14,`faction_H` = 14 WHERE `entry` = 18697;
UPDATE `creature_template` SET `unit_flags` = 0 WHERE `entry` = 18692;

/*
wotlk mobs (not complete yet)
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES (NULL, '32517', '571', '1', '1', '0', '0', '5219.234375', '5868.420898', '-72.627205', '3.696030', '86400', '15', '0', '16500', '0', '0', '1'),
(NULL, '32501', '571', '1', '1', '0', '0', '6535.847168', '3430.172852', '598.482666', '5.715408', '86400', '15', '0', '18900', '0', '0', '1'),
(NULL, '32495', '571', '1', '1', '0', '0', '7750.822754', '3439.896484', '658.731445', '4.421801', '86400', '15', '0', '18900', '5990', '0', '1'),
(NULL, '32447', '571', '1', '1', '0', '0', '5868.022949', '-2650.734375', '288.312561', '5.936375', '86400', '15', '0', '45500', '0', '0', '1'),
(NULL, '32471', '571', '1', '1', '0', '0', '5146.212891', '-1656.877075', '233.207687', '3.344372', '86400', '15', '0', '16000', '0', '0', '1'),
(NULL, '32475', '571', '1', '1', '0', '0', '6721.244629', '-4028.423096', '517.719604', '5.139779', '86400', '15', '0', '16500', '0', '0', '1'),
(NULL, '32481', '571', '1', '1', '0', '0', '5273.802246', '5061.300293', '-131.115387', '4.982510', '86400', '15', '0', '16000', '0', '0', '1'),
(NULL, '32485', '571', '1', '1', '0', '0', '4997.216309', '3980.703613', '-14.943896', '1.347680', '86400', '15', '0', '42500', '0', '0', '1'),
(NULL, '32630', '571', '1', '1', '0', '0', '7073.901855', '-604.590210', '731.008362', '3.945914', '86400', '15', '0', '18900', '0', '0', '1'),
(NULL, '32500', '571', '1', '1', '0', '0', '8191.468750', '-942.331848', '929.106628', '5.328724', '86400', '15', '0', '50400', '3990', '0', '1'),
(NULL, '32487', '571', '1', '1', '0', '0', '6569.747070', '1075.940552', '283.997314', '0.843520', '86400', '15', '0', '75600', '0', '0', '1');
*/