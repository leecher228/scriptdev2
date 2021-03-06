
DELETE FROM `script_texts` WHERE entry IN (-1002050,-1002051,-1002052,-1002053,-1002054,-1002055,-1002056,-1002057);
INSERT INTO `script_texts` (`entry`, `content_default`, `sound`, `type`, `language`, `emote`, `comment`) VALUES
('-1002050','What\'s the big idea, Spark? Why\'d you call for this meeting?','0','0','0','0','npc_geezle SAY_GEEZLE1'),
('-1002051','Relax, Spark! I have it all under control. We\'ll strip mine the Exodar right out from under\'em - making both you and I very, very rich in the process.','0','0','0','0','npc_geezle SAY_GEEZLE2\r\n'),
('-1002052','Yes, sir. It won\'t happen again...','0','0','0','0','npc_geezle SAY_GEEZLE3'),
('-1002057','%s picks up the naga flag.','0','2','0','0','npc_engineer_spark_overgrind SAY_SPARK0'),
('-1002053','What\'s the big idea? You nearly blew my cover, idiot! I told you to put the compass and the navigation maps somewhere safe - not out in the open for any fool to discover.','0','0','0','0','npc_engineer_spark_overgrind SAY_SPARK1'),
('-1002054','The Master has gone to great lengths to secure information about the whereabouts of the Exodar. You could have blown the entire operation, including the cover of our spy on the inside.','0','0','0','0','npc_engineer_spark_overgrind SAY_SPARK2'),
('-1002055','Relax? Do you know what Kael\'thas does to those who fail him, Geezle? Eternal suffering and pain... do NOT screw this up, fool.','0','0','0','0','npc_engineer_spark_overgrind SAY_SPARK3'),
('-1002056','Our Bloodmyst scouts have located our contact. The fool, Velen, will soon leave himself open and defenseless -- long enough for us to strike! Now get out of my sight before I vaporize you...','0','0','0','0','npc_engineer_spark_overgrind SAY_SPARK4');

DELETE FROM `script_waypoint` WHERE entry IN (17318,17243);
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `waittime`, `point_comment`) VALUES
('17318','0','-5136.58','-11247.8','5.584','0',''),
('17318','1','-5126.52','-11247.9','1.449','0',''),
('17318','2','-5118.31','-11249.2','0.241','0',''),
('17318','3','-5092.65','-11253.5','0.698','60000','roleplay spot'),
('17318','4','-5118.31','-11249.2','0.241','0',''),
('17318','5','-5126.52','-11247.9','1.449','0',''),
('17318','6','-5136.58','-11247.8','5.584','0',''),
('17318','7','-5144.08','-11248.2','3.455','0',''),
('17243','6','-5033.99','-11288.7','6.702','0',''),
('17243','0','-5049.43','-11258.3','4.105','0',''),
('17243','1','-5054.69','-11257.4','1.031','0',''),
('17243','2','-5081.9','-11253.2','0.574','67000','roleplay spot'),
('17243','3','-5059.86','-11261.1','0.659','0',''),
('17243','4','-5049.83','-11272.6','1.62','0',''),
('17243','5','-5041.76','-11280.2','1.356','0','');