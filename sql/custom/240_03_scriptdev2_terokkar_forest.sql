-- terokkar forest fixes

-- add waypoints and script text for NPC 18760 (Isla Starmane) for quests 10051 & 10052
DELETE FROM `script_waypoint` WHERE `entry` = 18760;
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `waittime`, `point_comment`) VALUES
('18760', '1', '-2287.472900', '3095.203857', '13.826787', '0', NULL),
('18760', '2', '-2311.886719', '3129.350098', '12.144577', '0', NULL),
('18760', '3', '-2349.842041', '3153.418213', '7.341877', '0', NULL),
('18760', '4', '-2371.047363', '3184.919189', '0.961656', '0', NULL),
('18760', '5', '-2372.279053', '3199.797607', '-1.023255', '0', NULL),
('18760', '6', '-2386.342529', '3232.974609', '-1.262486', '0', NULL),
('18760', '7', '-2379.695801', '3254.263428', '-1.253316', '0', NULL),
('18760', '8', '-2348.133789', '3280.836670', '-0.904500', '0', NULL),
('18760', '9', '-2351.991943', '3317.531006', '-1.631526', '0', NULL),
('18760', '10', '-2345.971191', '3369.614014', '-3.451267', '0', NULL),
('18760', '11', '-2317.684082', '3386.684814', '-8.185443', '0', NULL),
('18760', '12', '-2315.380127', '3406.951660', '-11.102516', '0', NULL),
('18760', '13', '-2341.692627', '3433.670898', '-11.345046', '5000', 'quest complete');
-- insert german text as default content because we do not have original text
DELETE FROM `script_texts` WHERE `entry` IN (-1999939,-1999940,-1999941);
INSERT INTO `script_texts` (`entry`, `content_default`, `content_loc3`, `type`, `language`, `emote`, `comment`) VALUES
('-1999939', 'Ihr müsst mir bei meiner Flucht helfen, Fremder. Begleitet und beschützt mich auf meinem Weg in die Freiheit.','Ihr müsst mir bei meiner Flucht helfen, Fremder. Begleitet und beschützt mich auf meinem Weg in die Freiheit.','0','0','0', "Isla Starmane - Say Start"),
('-1999940', 'Kehrt zurück zu Hauptmann Auric Sonnenjäger und berichtet ihm von den Vorkommnissen hier. Ich werde ab jetzt wieder alleine klarkommen.','Kehrt zurück zu Hauptmann Auric Sonnenjäger und berichtet ihm von den Vorkommnissen hier. Ich werde ab jetzt wieder alleine klarkommen.','0','0','0', "Isla Starmane - Say End Alliance"),
('-1999941', 'Kehrt zurück zu Beraterin Faila und berichtet ihr von den Vorkommnissen hier. Ich werde ab jetzt wieder alleine klarkommen.','Kehrt zurück zu Beraterin Faila und berichtet ihr von den Vorkommnissen hier. Ich werde ab jetzt wieder alleine klarkommen.','0','0','0',"Isla Starmane - Say End Horde"); 

# add waypoints for quest 10898 / npc 22424
DELETE FROM `script_waypoint` WHERE `entry` = 22424;
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `waittime`, `point_comment`) VALUES
('22424', '1', '-3609.418213', '4174.385742', '0.292547', '0', NULL),
('22424', '2', '-3621.849121', '4165.044434', '1.867881', '0', NULL),
('22424', '3', '-3627.518555', '4139.603027', '12.183303', '0', NULL),
('22424', '4', '-3630.530079', '4117.277344', '26.992090', '0', NULL),
('22424', '5', '-3628.685547', '4093.361328', '44.641058', '0', NULL),
('22424', '6', '-3624.686279', '4071.981201', '56.582298', '0', NULL),
('22424', '7', '-3611.969727', '4046.911865', '64.971565', '0', NULL),
('22424', '8', '-3605.046631', '4039.909912', '66.346237', '0', NULL),
('22424', '9', '-3600.108887', '4038.006348', '67.400322', '0', NULL),
('22424', '10', '-3597.824217', '4033.054443', '68.703949', '0', NULL),
('22424', '11', '-3602.323975', '4027.261475', '69.453918', '0', NULL),
('22424', '12', '-3611.830811', '4030.003906', '71,630890', '0', NULL),
('22424', '13', '-3613.013672', '4035.715332', '73.557547', '0', NULL),
('22424', '14', '-3610.146973', '4040.600098', '75.268707', '0', NULL),
('22424', '15', '-3602.369873', '4038.461670', '77.909859', '0', NULL),
('22424', '16', '-3601.069580', '4031.963135', '80.170418', '0', NULL),
('22424', '17', '-3607.191406', '4027.922852', '82.690750', '0', NULL),
('22424', '18', '-3612.645508', '4032.183594', '85.084541', '0', NULL),
('22424', '19', '-3610.198486', '4039.599365', '87.944061', '0', NULL),
('22424', '20', '-3603.884277', '4039.553467', '89.977547', '0', NULL),
('22424', '21', '-3601.190674', '4033.166016', '92.492561', '0', NULL),
('22424', '22', '-3606.671387', '4028.856445', '95.203728', '0', NULL),
('22424', '23', '-3611.661377', '4034.167236', '98.391182', '0', NULL),
('22424', '24', '-3609.218750', '4039.462158', '100.782684', '0', NULL),
('22424', '25', '-3602.443604', '4036.136719', '103.950089', '0', NULL),
('22424', '26', '-3605.128418', '4030.214844', '107.112732', '0', NULL),
('22424', '27', '-3610.460938', '4031.000970', '109.639320', '0', NULL),
('22424', '28', '-3606.592041', '4037.254883', '111.068008', '0', NULL),
('22424', '29', '-3599.285400', '4051.003418', '111.942009', '0', NULL),
('22424', '30', '-3611.601318', '4057.063232', '112.011131', '0', NULL),
('22424', '31', '-3618.118908', '4050.774902', '112.005302', '0', NULL),
('22424', '32', '-3623.667725', '4028.894287', '111.998604', '0', NULL),
('22424', '33', '-3614.193105', '4015.226318', '112.001434', '0', NULL),
('22424', '34', '-3599.087646', '4017.573486', '111.996307', '0', NULL),
('22424', '35', '-3584.452881', '4033.303955', '112.005272', '0', NULL),
('22424', '36', '-3560.589600', '4031.330078', '105.505981', '0', NULL),
('22424', '37', '-3526.305176', '4027.950684', '112.275696', '0', NULL),
('22424', '38', '-3523.485840', '4012.846924', '112.667206', '0', NULL),
('22424', '39', '-3533.543701', '4005.476807', '92.509338', '0', NULL),
('22424', '40', '-3535.632812', '4005.219971', '92.687187', '0', NULL),
('22424', '41', '-3528.424561', '4034.352539', '85.691673', '0', NULL),
('22424', '42', '-3522.821777', '4058.942383', '92.931412', '0', NULL),
('22424', '43', '-3508.995805', '4067.622314', '93.024208', '0', "spawn luanga the imprisoner"),
('22424', '44', '-3506.204590', '4078.502441', '92.916435', '30000', "quest complete");
# add script texts for npc 22424 (english texts not available)
DELETE FROM `script_texts` WHERE `entry` IN ('-1999926','-1999927','-1999928'); -- only apply once
DELETE FROM `script_texts` WHERE `entry` IN (-1039980, -1039979, -1039978);
INSERT INTO `script_texts` (`entry`, `content_default`, `content_loc3`,`sound`, `type`, `language`, `emote`, `comment`) VALUES 
('-1039980', 'Endlich wurde ich von diesem schrecklichen Fluch befreit! Vielen Dank! Bitte berichtet Rilak dem Erlösten, dass es mir gut geht. Meine Mission führt nach Skettis. Terokk muss besiegt werden!', 'Endlich wurde ich von diesem schrecklichen Fluch befreit! Vielen Dank! Bitte berichtet Rilak dem Erlösten, dass es mir gut geht. Meine Mission führt nach Skettis. Terokk muss besiegt werden!', '0', '0', '0', '0', "Skywing - SAY_END"),
('-1039979', '%s krächzt und macht sich auf in Richtung Shalasversteck. Beeilt Euch, zu Folgen!', '%s krächzt und macht sich auf in Richtung Shalasversteck. Beeilt Euch, zu Folgen!', '0', '2', '0', '0', "Skywing - SAY_START"),
('-1039978', '%s krächzt laut!', '%s krächzt laut!', '0', '2', '0', '0', "Skywing - SAY_SPAWN");
