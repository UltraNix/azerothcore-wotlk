DELETE FROM `smart_scripts` WHERE `entryorguid` =27725  AND `source_type`=0 AND `id`=1;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN(27564,27749)  AND `source_type`=0 AND `id`=15;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(27564, 0, 15, 0, 1, 0, 100, 0, 10000, 50000, 20000, 30000, 11, 49329, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Alliance Conscript - OOC - Cast Summon Frigid Ghoul Attacker'),
(27749, 0, 15, 0, 1, 0, 100, 0, 10000, 50000, 20000, 30000, 11, 49329, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Horde Conscript - OOC - Cast Summon Frigid Ghoul Attacker'),
(27725, 0, 1, 0, 1, 0, 100, 0, 10000, 50000, 20000, 30000, 11, 49068, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Ruby Guardian - OOC - Cast Summon Frigid Ghoul');

SET @SUMMONER = 27589;
SET @SUMMONER_GUID = 114498;
SET @SUMMONER_2_GUID = 114481;
SET @ENTRY = 27686;

DELETE FROM `creature_summon_groups` WHERE `summonerId` = @SUMMONER;
INSERT INTO `creature_summon_groups` VALUES
(@SUMMONER, 0, 1, @ENTRY, 3635.08, 1129.83, 92.17, 1.82, 4, 100000),
(@SUMMONER, 0, 1, @ENTRY, 3635.28, 1129.43, 92.17, 1.82, 4, 100000),
(@SUMMONER, 0, 1, @ENTRY, 3635.38, 1129.23, 92.17, 1.82, 4, 100000),
(@SUMMONER, 0, 1, @ENTRY, 3635.78, 1129.13, 92.17, 1.82, 4, 100000),
(@SUMMONER, 0, 1, @ENTRY, 3635.68, 1129.93, 92.17, 1.82, 4, 100000),
(@SUMMONER, 0, 1, @ENTRY, 3635.45, 1129.85, 92.17, 1.82, 4, 100000),
(@SUMMONER, 0, 1, @ENTRY, 3635.49, 1129.80, 92.17, 1.82, 4, 100000),
(@SUMMONER, 0, 1, @ENTRY, 3635.42, 1129.89, 92.17, 1.82, 4, 100000),
(@SUMMONER, 0, 1, @ENTRY, 3634.41, 1128.33, 92.17, 1.82, 4, 100000),
(@SUMMONER, 0, 1, @ENTRY, 3635.40, 1129.83, 92.17, 1.82, 4, 100000),
(@SUMMONER, 0, 1, @ENTRY, 3635.28, 1129.83, 92.17, 1.82, 4, 100000),
(@SUMMONER, 0, 1, @ENTRY, 3635.88, 1129.83, 92.17, 1.82, 4, 100000),

(@SUMMONER, 0, 2, @ENTRY, 3790.01, 732.75, 61.30, 5.49, 4, 100000),
(@SUMMONER, 0, 2, @ENTRY, 3790.01, 733.55, 60.05, 5.49, 4, 100000),
(@SUMMONER, 0, 2, @ENTRY, 3790.01, 733.45, 60.80, 5.49, 4, 100000),
(@SUMMONER, 0, 2, @ENTRY, 3790.01, 733.38, 60.60, 5.49, 4, 100000),
(@SUMMONER, 0, 2, @ENTRY, 3790.01, 733.70, 60.50, 5.49, 4, 100000),
(@SUMMONER, 0, 2, @ENTRY, 3790.01, 731.25, 61.30, 5.49, 4, 100000),
(@SUMMONER, 0, 2, @ENTRY, 3790.01, 734.75, 62.05, 5.49, 4, 100000),
(@SUMMONER, 0, 2, @ENTRY, 3790.01, 733.45, 60.00, 5.49, 4, 100000),
(@SUMMONER, 0, 2, @ENTRY, 3790.01, 733.35, 59.20, 5.49, 4, 100000),
(@SUMMONER, 0, 2, @ENTRY, 3790.01, 733.05, 61.30, 5.49, 4, 100000),
(@SUMMONER, 0, 2, @ENTRY, 3790.01, 730.75, 62.30, 5.49, 4, 100000),
(@SUMMONER, 0, 2, @ENTRY, 3790.01, 733.75, 60.30, 5.49, 4, 100000);

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` IN (@SUMMONER,@ENTRY);
DELETE FROM `creature` WHERE `id` = 27685;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (-@SUMMONER_GUID, -@SUMMONER_2_GUID);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@ENTRY, @ENTRY*100, @ENTRY*100+1);
INSERT INTO `smart_scripts` VALUES
(-@SUMMONER_GUID, 0, 0, 1, 1, 0, 100, 0, 5000, 10000, 600000, 60000, 107, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ruby Strafe Bunny - OOC - Summon Group 1'),
(-@SUMMONER_GUID, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 4, 4, 0, 0, 0, 0, 9, @ENTRY, 0, 10, 0, 0, 0, 0, 'Ruby Strafe Bunny - OOC - Set Data 4 4 On Summoned'),
(-@SUMMONER_2_GUID, 0, 0, 1, 1, 0, 100, 0, 5000, 10000, 60000, 60000, 107, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ruby Strafe Bunny - OCC - Summon Group 2'),
(-@SUMMONER_2_GUID, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 5, 5, 0, 0, 0, 0, 9, @ENTRY, 0, 10, 0, 0, 0, 0, 'Ruby Strafe Bunny - OCC - Set Data 5 5 On Summoned'),
(@ENTRY, 0, 0, 0, 38, 0, 100, 0, 4, 4, 0, 0, 80, @ENTRY*100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Frigid Attacker - On Data Set - Run Script'),
(@ENTRY*100, 9, 0, 0, 0, 0, 100, 0, 10000, 10000, 10000, 10000, 69, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 3641.4, 1223.64, 134.41, 1.6, 'Frigid Attacker - On Script - Move to Pos'),
(@ENTRY*100, 9, 1, 0, 0, 0, 100, 0, 10000, 10000, 10000, 10000, 101, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 3641.4, 1223.64, 134.41, 1.6, 'Frigid Attacker - On Script - Set Home Pos'),
(@ENTRY*100, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 9, 0, 30, 0, 0, 0, 0, 0, 'Frigid Attacker - On Script - Attack Start'),
(@ENTRY, 0, 1, 0, 38, 0, 100, 0, 5, 5, 0, 0, 80, @ENTRY*100+1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Frigid Attacker - On Data Set - Run Script'),
(@ENTRY*100+1, 9, 0, 0, 0, 0, 100, 0, 10000, 10000, 10000, 10000, 69, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 3849.70, 667.54, 58.60, 0, 'Frigid Attacker - On Script - Move to Pos'),
(@ENTRY*100+1, 9, 1, 0, 0, 0, 100, 0, 10000, 10000, 10000, 10000, 101, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 3849.70, 667.54, 58.60, 0, 'Frigid Attacker - On Script - Set Home Pos'),
(@ENTRY*100+1, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 9, 0, 30, 0, 0, 0, 0, 0, 'Frigid Attacker - On Script - Attack Start');
