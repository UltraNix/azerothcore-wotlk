SET @GO = 1728;
SET @DRINKEMOTE = 418;
SET @FARMER1 = 15893;
SET @FARMER2 = 15891;
SET @FARMER3 = 15892;
UPDATE `gameobject_template` SET `AIName` = "SmartGameObjectAI" WHERE `entry` = 1728;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 2284;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@GO, -@FARMER1, -@FARMER2, -@FARMER3, 228400);
INSERT INTO `smart_scripts` VALUES
(@GO, 1, 0, 0, 20, 0, 100, 0, 524, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 9, 2284, 0, 10, 0, 0, 0, 0, 'Dusty Rug - On Quest Rewarded - Set Data On Farmers'),
(-@FARMER1, 0, 0, 1, 38, 0, 100, 0, 1, 1, 0, 0, 69, 1, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0.4533, -941.80, 61.93, 4.59, 'Farmer - On data Set - Move to Pos'),
(-@FARMER1, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 80, 228400, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Farmer - On Data Set - Start Script'),
(-@FARMER2, 0, 0, 1, 38, 0, 100, 0, 1, 1, 0, 0, 69, 1, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0.56, -943.62, 61.93, 1.60, 'Farmer - On data Set - Move to Pos'),
(-@FARMER2, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 80, 228400, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Farmer - On Data Set - Start Script'),
(-@FARMER3, 0, 0, 1, 38, 0, 100, 0, 1, 1, 0, 0, 69, 1, 0, 0, 0, 0, 0, 8, 0, 0, 0, -0.93, -942.94, 61.93, 0.10, 'Farmer - On data Set - Move to Pos'),
(-@FARMER3, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 80, 228400, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Farmer - On Data Set - Start Script'),
(228400, 9, 0, 0, 0, 0, 100, 0, 5000, 5000, 5000, 5000, 5, @DRINKEMOTE, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Farmer - Script - Play Emote Drink'),
(228400, 9, 1, 0, 0, 0, 100, 0, 3000, 3000, 3000, 3000, 37, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Farmer - Script - Die');
