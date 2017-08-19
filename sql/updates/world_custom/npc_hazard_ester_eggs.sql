SET @NPC_ID := 91035;
 
DELETE FROM `creature_template` WHERE entry = @NPC_ID;
DELETE FROM `creature_template` WHERE entry = @NPC_ID + 1;
DELETE FROM `creature_template` WHERE entry = @NPC_ID + 2;
DELETE FROM `creature_template` WHERE entry = @NPC_ID + 3;
DELETE FROM `creature_template` WHERE entry = @NPC_ID + 4;
DELETE FROM `creature_template` WHERE entry = @NPC_ID + 5;
DELETE FROM `creature_template` WHERE entry = @NPC_ID + 6;
DELETE FROM `creature_template` WHERE entry = @NPC_ID + 7;
DELETE FROM `creature_template` WHERE entry = @NPC_ID + 8;
 
INSERT INTO `creature_template` VALUES
(@NPC_ID,0,0,0,0,0,6922,0,0,0,'Masuka','Retired Gold Seller','',0,80,80,0,35,3,1,1.14286,1,0,0,0,0,0,1,2000,2000,1,2,2048,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,5,1,1,1,1,0,0,0,0,0,0,0,0,1,0,2,'npc_hazard_masuka',12340),
(@NPC_ID + 1,0,0,0,0,0,2106,0,0,0,'Piootrek','','',0,80,80,0,35,3,1,1.14286,1,0,0,0,0,0,1,2000,2000,1,2,2048,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,5,1,1,1,1,0,0,0,0,0,0,0,0,1,0,2,'npc_hazard_pioorade',12340),
(@NPC_ID + 2,0,0,0,0,0,18668,0,0,0,'Radeghost','','',0,80,80,0,35,3,1,1.14286,1,0,0,0,0,0,1,2000,2000,1,2,2048,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,5,1,1,1,1,0,0,0,0,0,0,0,0,1,0,2,'npc_hazard_pioorade',12340),
(@NPC_ID + 3,0,0,0,0,0,21959,0,0,0,'Fenix','Professional Bug Fixer','',0,80,80,0,35,3,1,1.14286,1,0,0,0,0,0,1,2000,2000,1,2,2048,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,5,1,1,1,1,0,0,0,0,0,0,0,0,1,0,2,'npc_hazard_pswzrdxinef',12340),
(@NPC_ID + 4,0,0,0,0,0,21959,0,0,0,'Wizard','Professional Bug Fixer','',0,80,80,0,35,3,1,1.14286,1,0,0,0,0,0,1,2000,2000,1,0,2048,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,5,1,1,1,1,0,0,0,0,0,0,0,0,1,0,2,'npc_hazard_pswzrdxinef',12340),
(@NPC_ID + 5,0,0,0,0,0,27900,0,0,0,'Sensimilek','','',0,80,80,0,1770,0,1,1.14286,1,0,0,0,0,1000,1,2000,2000,1,526592,2048,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,5,1,1,1,1,0,0,0,0,0,0,0,0,1,0,8388608,'npc_hazard_senpen',12340),
(@NPC_ID + 6,0,0,0,0,0,23019,0,0,0,'Pendu','','',0,80,80,0,2101,0,1,1.14286,1,0,0,0,0,0,1,2000,2000,1,256,2048,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'SmartAI',0,5,1,1,1,0,0,0,0,0,0,0,0,0,1,0,2,'',12340),
(@NPC_ID + 7,0,0,0,0,0,11686,0,0,0,'Pussywizard','','',0,80,80,0,35,3,1,1.14286,1,0,0,0,0,0,1,2000,2000,1,2,2048,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,5,1,1,1,1,0,0,0,0,0,0,0,0,1,0,130,'',12340),
(@NPC_ID + 8,0,0,0,0,0,24099,0,0,0,'Kaleb the Warmane','','',0,80,80,0,35,0,1,1.14286,1,0,0,0,0,0,1,2000,2000,1,2,2048,32,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,5,1,1,1,1,0,0,0,0,0,0,0,0,1,0,2,'npc_hazard_warmane',12340);
 
DELETE FROM `creature` WHERE id = @NPC_ID;
DELETE FROM `creature` WHERE id = @NPC_ID + 1;
DELETE FROM `creature` WHERE id = @NPC_ID + 2;
DELETE FROM `creature` WHERE id = @NPC_ID + 3;
DELETE FROM `creature` WHERE id = @NPC_ID + 4;
DELETE FROM `creature` WHERE id = @NPC_ID + 5;
DELETE FROM `creature` WHERE id = @NPC_ID + 6;
DELETE FROM `creature` WHERE id = @NPC_ID + 7;
DELETE FROM `creature` WHERE id = @NPC_ID + 8;
 
SET @NPC_GUID := 1980110;
INSERT INTO `creature` VALUES
(@NPC_GUID,@NPC_ID,0,1,1,6921,0,-11063.4,-1525.96,28.6826,4.63292,300,0,0,5342,0,0,0,0,0),
(@NPC_GUID + 1,@NPC_ID+1,0,1,1,0,0,-11165.3,-1811.92,-28.5048,2.55533,300,0,0,5342,0,0,0,0,0),
(@NPC_GUID + 2,@NPC_ID+2,0,1,1,0,0,-11167.8,-1810.06,-28.5048,5.56969,300,0,0,5342,0,0,0,0,0),
(@NPC_GUID + 3,@NPC_ID+3,0,1,1,0,0,-11028.1,-1609.92,28.1618,3.20036,300,0,0,5342,0,0,0,0,0),
(@NPC_GUID + 4,@NPC_ID+4,0,1,1,0,0,-11032.8,-1609.83,28.1922,0.0234253,300,0,0,5342,0,0,0,0,0),
(@NPC_GUID + 5,@NPC_ID+5,0,1,1,0,1,-11253.3,-1755.31,-15.6989,0.0151219,300,0,0,5342,0,0,0,2304,0),
(@NPC_GUID + 6,@NPC_ID+6,0,1,1,0,0,-11251.1,-1755.06,-15.6989,0.021405,300,0,0,5342,0,0,0,0,0),
(@NPC_GUID + 7,@NPC_ID+7,0,1,1,0,0,-11257.3,-1763.9,-15.7011,0.564904,300,0,0,5342,0,0,0,33554434,0),
(@NPC_GUID + 8,@NPC_ID+8,0,1,1,0,0,-11223.6,-1402.55,-14.7903,4.62015,300,0,0,5342,0,0,0,0,0);
 
DELETE FROM `creature_equip_template` WHERE `entry` = @NPC_ID + 5;
INSERT INTO `world`.`creature_equip_template` (`entry`, `id`, `itemEntry1`, `itemEntry2`) VALUES (@NPC_ID + 5, 1, 51521, 51533);
 
DELETE FROM `creature_template_addon` WHERE `entry` = @NPC_ID;
DELETE FROM `creature_template_addon` WHERE `entry` = @NPC_ID + 1;
DELETE FROM `creature_template_addon` WHERE `entry` = @NPC_ID + 2;
DELETE FROM `creature_template_addon` WHERE `entry` = @NPC_ID + 6;
DELETE FROM `creature_template_addon` WHERE `entry` = @NPC_ID + 8;
INSERT INTO `world`.`creature_template_addon` (`entry`, `bytes1`, `emote`, `auras`) VALUES
(@NPC_ID + 6, 1, 13, NULL),(@NPC_ID + 1, 0, 1, NULL), (@NPC_ID + 2, 0, 1, NULL), (@NPC_ID + 8, 7, 0, NULL), (@NPC_ID, 3, 0, '55701'), (@NPC_ID + 7, 0, 0, '16380');
 
UPDATE `world`.`gameobject_template` SET `data2`=30000 WHERE  `entry`=177248 OR `entry`=177250;
 
-- Pendu SAI
SET @ENTRY := @NPC_ID + 6;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,6,0,100,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Pendu - On Just Died - Say Line 0");
DELETE FROM `creature_text` WHERE entry = @NPC_ID + 6;
INSERT INTO `world`.`creature_text` (`entry`, `text`, `type`) VALUES (@NPC_ID + 6, 'Widze przed soba... blizzlike.', 12);