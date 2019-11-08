SET @CGUID = 1980060;
SET @CRUSADER = 38493;
SET @KNIGHT = 38505;
SET @EVENTTRIGGER_ENTRY = 21987;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` IN (@EVENTTRIGGER_ENTRY, @CRUSADER, @KNIGHT);
DELETE FROM `creature` WHERE `guid` = @CGUID;
INSERT INTO `creature` VALUES
(@CGUID, @EVENTTRIGGER_ENTRY, 571, 1, 1, 0, 0, 5868.20, 2107.88, 636.01, 3.67, 0, 0, 0, 1, 0, 0, 0, 0, 0);

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (-@CGUID,@CGUID*100,@CGUID*100+1, 38493, @KNIGHT);
INSERT INTO `smart_scripts` VALUES
(-@CGUID, 0, 0, 0, 1, 0, 100, 0, 10000, 20000, 20000, 40000, 87, @CGUID*100, (@CGUID*100)+1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'ICC Opening Event Trigger - OOC - start script'),
(@CGUID*100, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, @CRUSADER, 3, 14000, 0, 0, 0, 8, 0, 0, 0, 5875.41, 2089.95, 636.04, 2.03, 'ICC Opening Event Trigger - on script - summon argent crusader'),
(@CGUID*100, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 4, 4, 0, 0, 0, 0, 9, @CRUSADER, 0, 30, 0, 0, 0, 0, 'ICC Opening Event Trigger - on script - set data 4 4'),
(@CGUID*100, 9, 2, 0, 0, 0, 100, 0, 10000, 15000, 0, 0, 12, @KNIGHT, 3, 14000, 0, 0, 0, 8, 0, 0, 0, 5861.41, 2126.66, 636.03, 5.16, 'ICC Opening Event Trigger - on script - summon knight of the ebon blade'),
(@CGUID*100, 9, 3, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 4, 4, 0, 0, 0, 0, 9, @KNIGHT, 0, 30, 0, 0, 0, 0, 'ICC Opening Event Trigger - on script - set data 5 5'),
(@CGUID*100+1, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, @KNIGHT, 3, 14000, 0, 0, 0, 8, 0, 0, 0, 5875.41, 2089.95, 636.04, 2.03, 'ICC Opening Event Trigger - on script - summon knight of the ebon blade'),
(@CGUID*100+1, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 5, 5, 0, 0, 0, 0, 9, @KNIGHT, 0, 30, 0, 0, 0, 0, 'ICC Opening Event Trigger - on script - set data 5 5'),
(@CGUID*100+1, 9, 2, 0, 0, 0, 100, 0, 10000, 15000, 0, 0, 12, @CRUSADER, 3, 14000, 0, 0, 0, 8, 0, 0, 0, 5861.41, 2126.66, 636.03, 5.16, 'ICC Opening Event Trigger - on script - summon argent crusader'),
(@CGUID*100+1, 9, 3, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 5, 5, 0, 0, 0, 0, 9, @CRUSADER, 0, 30, 0, 0, 0, 0, 'ICC Opening Event Trigger - on script - set data 5 5'),
(@CRUSADER, 0, 0, 0, 38, 0, 100, 0, 4, 4, 0, 0, 53, 1, @CRUSADER, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Argent Crusader - on data set 4 4 - start wp'),
(@KNIGHT, 0, 0, 0, 38, 0, 100, 0, 4, 4, 0, 0, 53, 1, @KNIGHT, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Knight of the ebon blade - on data set 4 4 - start wp'),
(@CRUSADER, 0, 1, 0, 38, 0, 100, 0, 5, 5, 0, 0, 53, 1, @KNIGHT, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Argent Crusader - on data set 5 5 - start wp'),
(@KNIGHT, 0, 1, 0, 38, 0, 100, 0, 5, 5, 0, 0, 53, 1, @CRUSADER, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Knight of the ebon blade - on data set 5 5 - start wp');

DELETE FROM `waypoints` WHERE `entry` IN( @KNIGHT, @CRUSADER);
INSERT INTO `waypoints` VALUES
(@KNIGHT, 1, 5866.60, 2112.65, 635.99, ''),
(@KNIGHT, 2, 5849.31, 2100.13, 636.06, ''),
(@KNIGHT, 3, 5783.03, 2068.56, 636.06, ''),
(@CRUSADER, 1, 5869.06, 2102.54, 636.04, ''),
(@CRUSADER, 2, 5849.31, 2100.13, 636.06, ''),
(@CRUSADER, 3, 5783.03, 2068.56, 636.06, '');

UPDATE `creature_template` SET `flags_extra` = 130 WHERE `entry` = @EVENTTRIGGER_ENTRY;
