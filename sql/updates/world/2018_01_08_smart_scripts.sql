SET @ENTRY := 29978;
UPDATE `creature_template` SET `AIName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
SET @ENTRY := 29984;
UPDATE `creature_template` SET `AIName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
