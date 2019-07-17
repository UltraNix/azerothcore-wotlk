SET @ENTRY := 18827;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY AND `source_type` = 0;
INSERT INTO `smart_scripts` VALUES 
(@ENTRY,0,0,0,2,0,100,1,0,15,0,0,11,33974,0,0,0,0,0,2,0,0,0,0,0,0,0,'Gan\'arg Sapper - On 15% - Cast Power Burn'),
(@ENTRY,0,1,0,2,0,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Gan\'arg Sapper - On 15% - Say Line 0'),
(@ENTRY,0,2,0,6,0,100,1,0,0,0,0,11,33895,3,0,0,0,0,1,0,0,0,0,0,0,0,'Gan\'arg Sapper - On Just Died - Cast \'Set Charge\' (No Repeat)');

DELETE FROM `creature_text` WHERE `entry` = @ENTRY;
INSERT INTO `creature_text` VALUES (@ENTRY,0,0,'%s\'s eyes glow red as he begins to cackle madly!.',16,7,100,0,0,0,0,'Gan\'arg Sapper');
