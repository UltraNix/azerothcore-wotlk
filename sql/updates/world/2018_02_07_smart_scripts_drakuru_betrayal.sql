SET @DRAKURU_SCRIPT = 2899801;
SET @TROLL = 28931;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @DRAKURU_SCRIPT AND `id` =11;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @TROLL AND `id` = 8;
INSERT INTO `smart_scripts` VALUES
(@DRAKURU_SCRIPT, 9, 11, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 4, 4, 0, 0, 0, 0, 9, 28931, 0, 100, 0, 0, 0, 0, 'Overlord Drakuru - Script 2 - Set Data'),
(@TROLL, 0, 8, 0, 38, 0, 100, 0, 4, 4, 0, 0, 41, 10000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Blightblood Troll - On Data Set 4 4 - Despawn');