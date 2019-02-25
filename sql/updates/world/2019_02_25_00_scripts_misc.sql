-- [Q] Dream Dust in the Swamp - http://www.wowhead.com/quest=1116/dream-dust-in-the-swamp
-- [Q] Return to Thunder Bluff
-- DB/Quest: Forsaken Aid -- http://www.wowhead.com/quest=1064/deprecated-forsaken-aid
-- [Q] Identifying the Brood - http://www.wowhead.com/quest=1169/deprecated-identifying-the-brood
-- [Q] Load Lightening - http://www.wowhead.com/quest=1176/load-lightening
-- [Q] Nothing But The Truth - http://www.wowhead.com/quest=1383/nothing-but-the-truth
-- [Q] It's a Secret to Everybody - http://www.wowhead.com/quest=3908/its-a-secret-to-everybody
-- [Q] Barov Family Fortune - http://www.wowhead.com/quest=5341/barov-family-fortune


-- [Q] Dream Dust in the Swamp - http://www.wowhead.com/quest=1116/dream-dust-in-the-swamp
-- Krazek SAI
SET @ENTRY := 773;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,20,0,100,0,1116,0,0,0,80,@ENTRY*100+00,0,0,0,0,0,1,0,0,0,0,0,0,0,"Krazek - On Quest 'Dream Dust in the Swamp' Finished - Run Script");

-- Actionlist SAI
SET @ENTRY := 77300;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Say Line 0"),
(@ENTRY,9,1,0,0,0,100,0,1000,1000,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Say Line 1"),
(@ENTRY,9,2,0,0,0,100,0,0,0,0,0,11,6903,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Cast 'Krazek's Drug'"),
(@ENTRY,9,3,0,0,0,100,0,3000,3000,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Say Line 2"),
(@ENTRY,9,4,0,0,0,100,0,2000,2000,0,0,1,3,0,0,0,0,0,21,50,0,0,0,0,0,0,"On Script - Say Line 3");

DELETE FROM `creature_text` WHERE `entry`=773;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES 
(773, 0, 0, '%s snorts a speck of dream dust up his nose...', 16, 0, 100, 0, 0, 0, 'Krazek'),
(773, 1, 0, '%s is dazed...', 16, 0, 100, 0, 0, 0, 'Krazek'),
(773, 2, 0, 'ACHOO!', 12, 0, 100, 0, 0, 0, 'Krazek'),
(773, 3, 0, 'Wow! $N, that dream dust is powerful stuff!', 12, 0, 100, 0, 0, 0, 'Krazek');


-- Apothecary Zamah SAI
SET @ENTRY := 3419;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,20,0,100,0,1067,0,0,0,80,@ENTRY*100+00,0,0,0,0,0,1,0,0,0,0,0,0,0,"Apothecary Zamah - On Quest 'Return to Thunder Bluff' Finished - Run Script");

-- Actionlist SAI
SET @ENTRY := 341900;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Say Line 0"),
(@ENTRY,9,1,0,0,0,100,0,4000,4000,0,0,1,1,0,0,0,0,0,21,50,0,0,0,0,0,0,"On Script - Say Line 1");

DELETE FROM `creature_text` WHERE `entry`=3419;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES 
(3419, 0, 0, '%s fills a container with the toxin.', 16, 0, 100, 0, 0, 0, 'Apothecary Zamah'),
(3419, 1, 0, 'The toxin is ready, $N.', 12, 0, 100, 0, 0, 0, 'Apothecary Zamah');


-- DB/Quest: Forsaken Aid -- http://www.wowhead.com/quest=1064/deprecated-forsaken-aid
-- Magatha Grimtotem SAI
SET @ENTRY := 4046;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,20,0,100,0,1063,0,0,0,80,@ENTRY*100+00,0,0,0,0,0,1,0,0,0,0,0,0,0,"Magatha Grimtotem - On Quest 'The Elder Crone' Finished - Run Script"),
(@ENTRY,0,1,0,19,0,100,0,1064,0,0,0,80,@ENTRY*100+01,0,0,0,0,0,1,0,0,0,0,0,0,0,"Magatha Grimtotem - On Quest 'Forsaken Aid' Taken - Run Script");

-- Actionlist SAI
SET @ENTRY := 404601;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,0,2000,2000,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Say Line 2"),
(@ENTRY,9,1,0,0,0,100,0,1000,1000,0,0,11,6657,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Cast 'Summon Serpent Messenger'"),
(@ENTRY,9,2,0,0,0,100,0,1000,1000,0,0,12,4068,3,433000,0,0,0,8,0,0,0,-1067.22,-213.737,160.473,5.25037,"On Script - Summon Creature 'Serpent Messenger'"),
(@ENTRY,9,3,0,0,0,100,0,4000,4000,0,0,1,3,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Say Line 3"),
(@ENTRY,9,4,0,0,0,100,0,0,0,0,0,5,25,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Play Emote 25");

DELETE FROM `creature_text` WHERE `entry`=4046 AND `groupid`>=2;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES 
(4046, 2, 0, '%s summons a messenger...', 16, 0, 100, 0, 0, 0, 'Magatha Grimtotem'), 
(4046, 3, 0, 'Go, my servant. Send word of Stonetalon to Apothecary Zamah.', 12, 0, 100, 0, 0, 0, 'Magatha Grimtotem'); 

DELETE FROM `creature_text` WHERE `entry`=4068;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES 
(4068, 0, 0, '%s gives message to Apothecary Zamah.', 16, 0, 100, 0, 0, 0, 'Serpent Messenger'); 

DELETE FROM `creature_text` WHERE `entry`=3419 AND `groupid`=2;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES 
(3419, 2, 0, '%s gives message to Apothecary Zamah.', 16, 0, 100, 0, 0, 0, 'Apothecary Zamah'); 

-- Serpent Messenger SAI
SET @ENTRY := 4068;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,3,54,0,100,0,0,0,0,0,53,1,4068,0,0,0,0,1,0,0,0,0,0,0,0,"Serpent Messenger - On Just Summoned - Start Waypoint"),
(@ENTRY,0,1,0,40,0,100,0,1,4068,0,0,54,5000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Serpent Messenger - On Waypoint 1 Reached - Pause Waypoint"),
(@ENTRY,0,2,0,40,0,100,0,36,4068,0,0,80,@ENTRY*100+00,0,0,0,0,0,1,0,0,0,0,0,0,0,"Serpent Messenger - On Waypoint 36 Reached - Run Script"),
(@ENTRY,0,3,0,61,0,100,0,0,0,0,0,48,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Serpent Messenger - On Just Summoned - Set Active On");
UPDATE `creature_template` SET `InhabitType`=4 WHERE  `entry`=4068;

-- Actionlist SAI
SET @ENTRY := 406800;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,0,0,0,0,0,54,20000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Serpent Messenger - On Script - Pause Waypoint"),
(@ENTRY,9,1,0,0,0,100,0,2000,2000,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Serpent Messenger - On Script - Say Line 0"),
(@ENTRY,9,2,0,0,0,100,0,6000,6000,0,0,1,2,0,0,0,0,0,19,3419,2,0,0,0,0,0,"Serpent Messenger - On Script - Say Line 2"),
(@ENTRY,9,3,0,0,0,100,0,3000,3000,0,0,41,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Serpent Messenger - On Script - Despawn Instant");

DELETE FROM `waypoints` WHERE `entry`=4068;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`) VALUES 
(4068, 1, -1067.22, -213.737, 160.473),
(4068, 2, -1062.56, -221.981, 160.294),
(4068, 3, -1054.61, -221.248, 161.894),
(4068, 4, -1054.61, -221.248, 161.894),
(4068, 5, -1037.05, -191.12, 158.949),
(4068, 6, -1053.12, -173.969, 163.214),
(4068, 7, -1064.46, -140.953, 161.368),
(4068, 8, -1079.25, -97.1617, 156.371),
(4068, 9, -1085.39, -64.6974, 164.416),
(4068, 10, -1083.91, -26.7695, 159.369),
(4068, 11, -1084.44, -9.29896, 158.034),
(4068, 12, -1109.66, 7.02863, 154.732),
(4068, 13, -1132.07, 31.5715, 158.157),
(4068, 14, -1129.02, 47.1316, 154.19),
(4068, 15, -1095.17, 63.5461, 150.752),
(4068, 16, -1086.83, 113.827, 144.557),
(4068, 17, -1113.2, 129.364, 140.268),
(4068, 18, -1146.35, 119.028, 141.776),
(4068, 19, -1169.85, 118.638, 141.101),
(4068, 20, -1206.75, 117.618, 139.861),
(4068, 21, -1211.53, 129.623, 135.559),
(4068, 22, -1192.52, 144.921, 136.995),
(4068, 23, -1175.37, 157.22, 146.484),
(4068, 24, -1155.67, 169.875, 146.074),
(4068, 25, -1127.05, 179.696, 131.79),
(4068, 26, -1096.04, 189.663, 118.055),
(4068, 27, -1061.46, 191.502, 109.917),
(4068, 28, -1056.64, 215.227, 113.473),
(4068, 29, -1046.91, 223.356, 114.831),
(4068, 30, -1035.35, 218.46, 112.371),
(4068, 31, -1027.93, 217.483, 114.236),
(4068, 32, -1023.41, 229.152, 108.92),
(4068, 33, -1016.34, 236.136, 109.243),
(4068, 34, -1013.08, 246.142, 108.77),
(4068, 35, -1006.87, 255.833, 113.284),
(4068, 36, -997.047, 275.161, 112.343);

-- [Q] Identifying the Brood - http://www.wowhead.com/quest=1169/deprecated-identifying-the-brood
-- Draz'Zilb SAI
SET @ENTRY := 4501;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,20,0,100,0,1169,0,0,0,80,@ENTRY*100+00,0,0,0,0,0,1,0,0,0,0,0,0,0,"Draz'Zilb - On Quest 'Identifying the Brood' Finished - Run Script");

-- Actionlist SAI
SET @ENTRY := 450100;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Say Line 0"),
(@ENTRY,9,1,0,0,0,100,0,1000,1000,0,0,11,6741,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Cast 'Identify Brood'"),
(@ENTRY,9,2,0,0,0,100,0,10000,10000,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Say Line 1");

DELETE FROM `creature_text` WHERE `entry`=4501;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES 
(4501, 0, 0, '%s begins to cast a spell over the hearts and tongues.', 16, 0, 100, 0, 0, 0, 'Draz\'Zilb'),
(4501, 1, 0, 'The brood of Onyxia!', 14, 0, 100, 0, 0, 0, 'Draz\'Zilb');

-- [Q] Load Lightening - http://www.wowhead.com/quest=1176/load-lightening
-- Pozzik SAI
SET @ENTRY := 4630;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,20,0,100,0,1176,0,0,0,80,@ENTRY*100+00,0,0,0,0,0,1,0,0,0,0,0,0,0,"Pozzik - On Quest 'Load Lightening' Finished - Run Script");

-- Actionlist SAI
SET @ENTRY := 463000;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,0,2000,2000,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Say Line 0");

DELETE FROM `creature_text` WHERE `entry`=4630;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES 
(4630, 0, 0, 'Okay, crew. Get to work on getting these bones installed.', 12, 0, 100, 0, 0, 0, 'Pozzik');


-- [Q] Nothing But The Truth - http://www.wowhead.com/quest=1383/nothing-but-the-truth
-- Apothecary Faustin SAI
SET @ENTRY := 5414;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,20,0,100,0,1383,0,0,0,80,@ENTRY*100+00,0,0,0,0,0,1,0,0,0,0,0,0,0,"Apothecary Faustin - On Quest 'Nothing But The Truth' Finished - Run Script");

-- Actionlist SAI
SET @ENTRY := 541400;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,0,0,0,0,0,12,5088,0,180000,0,0,0,8,0,0,0,-3837.25,-4548.3,9.29486,0.786911,"On Script - Summon Creature 'Falgran Hastil'"),
(@ENTRY,9,1,0,0,0,100,0,0,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Set Npc Flag "),
(@ENTRY,9,2,0,0,0,100,0,1000,1000,0,0,1,0,0,0,0,0,0,21,50,0,0,0,0,0,0,"On Script - Say Line 0"),
(@ENTRY,9,3,0,0,0,100,0,3000,3000,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,6.23291,"On Script - Set Orientation 6,23291"),
(@ENTRY,9,4,0,0,0,100,0,2000,2000,0,0,5,69,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Play Emote 69"),
(@ENTRY,9,5,0,0,0,100,0,4000,4000,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Say Line 1"),
(@ENTRY,9,6,0,0,0,100,0,0,0,0,0,5,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Play Emote 0"),
(@ENTRY,9,7,0,0,0,100,0,5000,5000,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,3.14159,"On Script - Set Orientation 3,14159"),
(@ENTRY,9,8,0,0,0,100,0,1000,1000,0,0,1,2,0,0,0,0,0,21,50,0,0,0,0,0,0,"On Script - Say Line 2"),
(@ENTRY,9,9,0,0,0,100,0,0,0,0,0,81,2,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Set Npc Flag Questgiver");

DELETE FROM `creature_text` WHERE `entry`=5414;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES 
(5414, 0, 0, 'The serum will only take a few seconds to prepare, $N.', 12, 0, 100, 0, 0, 0, 'Apothecary Faustin'),
(5414, 1, 0, 'Almost done...', 12, 0, 100, 0, 0, 0, 'Apothecary Faustin'),
(5414, 2, 0, 'At last, the serum is complete, $N. Now, come closer. We must talk.', 12, 0, 100, 0, 0, 0, 'Apothecary Faustin');

-- [Q] It's a Secret to Everybody - http://www.wowhead.com/quest=3908/its-a-secret-to-everybody
-- Donova Snowden SAI
SET @ENTRY := 9298;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,20,0,100,0,3908,0,0,0,80,@ENTRY*100+00,0,0,0,0,0,1,0,0,0,0,0,0,0,"Donova Snowden - On Quest 'It's a Secret to Everybody' Finished - Run Script"),
(@ENTRY,0,1,0,61,0,100,0,3908,0,0,0,48,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Donova Snowden - On Quest 'It's a Secret to Everybody' Finished - Set Active On");

-- Actionlist SAI
SET @ENTRY := 929800;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,0,1000,1000,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Say Line 0"),
(@ENTRY,9,1,0,0,0,100,0,0,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Set Npc Flag "),
(@ENTRY,9,2,0,0,0,100,0,1000,1000,0,0,69,0,0,0,0,0,0,8,0,0,0,6384.54,-2527.25,538.736,2.52438,"On Script - Move To Position"),
(@ENTRY,9,3,0,0,0,100,0,6000,6000,0,0,69,0,0,0,0,0,0,8,0,0,0,6370.12,-2525.52,532.268,2.82283,"On Script - Move To Position"),
(@ENTRY,9,4,0,0,0,100,0,7000,7000,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Say Line 1"),
(@ENTRY,9,5,0,0,0,100,0,5000,5000,0,0,5,61,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Play Emote 61"),
(@ENTRY,9,6,0,0,0,100,0,1000,1000,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Say Line 2"),
(@ENTRY,9,7,0,0,0,100,0,2000,2000,0,0,69,0,0,0,0,0,0,8,0,0,0,6364.25,-2524,527.058,2.9265,"On Script - Move To Position"),
(@ENTRY,9,8,0,0,0,100,0,3000,3000,0,0,1,3,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Say Line 3"),
(@ENTRY,9,9,0,0,0,100,0,1000,1000,0,0,5,16,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Play Emote 16"),
(@ENTRY,9,10,0,0,0,100,0,3000,3000,0,0,1,4,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Say Line 4"),
(@ENTRY,9,11,0,0,0,100,0,1000,1000,0,0,69,0,0,0,0,0,0,8,0,0,0,6370.3,-2524.19,532.27,6.26836,"On Script - Move To Position"),
(@ENTRY,9,12,0,0,0,100,0,3000,3000,0,0,69,0,0,0,0,0,0,8,0,0,0,6385.99,-2529.26,539.03,5.66753,"On Script - Move To Position"),
(@ENTRY,9,13,0,0,0,100,0,8000,8000,0,0,69,0,0,0,0,0,0,8,0,0,0,6395.57,-2536.75,541.548,5.66753,"On Script - Move To Position"),
(@ENTRY,9,14,0,0,0,100,0,5000,5000,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,2.86475,"On Script - Set Orientation 2,86475"),
(@ENTRY,9,15,0,0,0,100,0,1000,1000,0,0,1,5,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Say Line 5"),
(@ENTRY,9,16,0,0,0,100,0,1000,1000,0,0,81,3,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Set Npc Flags Gossip & Questgiver");

DELETE FROM `creature_text` WHERE `entry`=9298;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES 
(9298, 0, 0, 'Please, follow me.', 12, 0, 100, 0, 0, 0, 'Donova Snowden'),
(9298, 1, 0, 'I haven\'t really figured out what it is, but there\'s something strange about the hot springs...', 12, 0, 100, 0, 0, 0, 'Donova Snowden'),
(9298, 2, 0, '%s tosses the sword into the shallow pool.', 16, 0, 100, 0, 0, 0, 'Donova Snowden'),
(9298, 3, 0, 'I\'ve found that when I throw something into this water, it has improved incredibly when I retrieve it.', 12, 0, 100, 0, 0, 0, 'Donova Snowden'),
(9298, 4, 0, 'Well, whatever it is, it works quite well!', 12, 0, 100, 0, 0, 0, 'Donova Snowden'),
(9298, 5, 0, 'And I am determined to find out more... So if you need my help again, you know where I\'ll be.', 12, 0, 100, 0, 0, 0, 'Donova Snowden');

-- [Q] Barov Family Fortune - http://www.wowhead.com/quest=5341/barov-family-fortune
-- Alexi Barov SAI
SET @ENTRY := 11022;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,20,0,100,0,5341,0,0,0,80,@ENTRY*100+00,0,0,0,0,0,1,0,0,0,0,0,0,0,"Alexi Barov - On Quest 'Barov Family Fortune' Finished - Run Script");

-- Actionlist SAI
SET @ENTRY := 1102200;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,0,1000,1000,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Say Line 0"),
(@ENTRY,9,1,0,0,0,100,0,0,0,0,0,5,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"On Script - Play Emote 1");

DELETE FROM `creature_text` WHERE `entry`=11022;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES 
(11022, 0, 0, 'The deeds are mine, brother! Soon you shall be out of my way for good!', 12, 0, 100, 0, 0, 0, 'Alexi Barov');
