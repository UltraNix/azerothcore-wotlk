-- #704
UPDATE `creature` SET `position_x` = 6529.44, `position_y` = -738.1, `position_z` = 611.05 WHERE `guid` = 106641;
-- #198
DELETE FROM `smart_scripts` WHERE `entryorguid` = 26161 AND `id` = 1;
INSERT INTO `smart_scripts` VALUES
(26161, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 2000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Farshire Grain Credit - On Spellhit `Burn Grain` - Despawn');
UPDATE `smart_scripts` SET `link` = 1 WHERE `entryorguid` = 26161 AND `id` = 0;
-- #713
UPDATE `quest_template` SET `RequiredRaces` = 690, `PrevQuestId` = 0 WHERE `id` = 364;
-- #708
UPDATE `creature_template` SET `mechanic_immune_mask` = `mechanic_immune_mask` | 1073741824 WHERE `entry` = 16441;
-- #716
DELETE FROM `smart_scripts` WHERE `entryorguid` = 2821700;
INSERT INTO `smart_scripts` VALUES

(2821700, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 81, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - Script - Set NPC Flags'),
(2821700, 9, 2, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - Script - Say Line 3'),
(2821700, 9, 3, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 53, 1, 28217, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - Script - Start WP'),
(2821700, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 28, 58806, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - On Script - Remove Aura Feign Death');

DELETE FROM `smart_scripts` WHERE `entryorguid` = 28217 AND `id` = 16;
-- #730
UPDATE `quest_template` SET  `SourceItemId` = 6866 WHERE `id` = 1786;
-- #425
SET @CGUID = 97713;
SET @PATH = @CGUID * 10;
UPDATE `creature` SET `MovementType` = 2 WHERE `guid` = @CGUID;
UPDATE `creature_addon` SET `path_id` = @PATH WHERE `guid` = @CGUID;
DELETE FROM `waypoint_data` WHERE `id` = @PATH;
INSERT INTO `waypoint_data` VALUES
(@PATH, 1, 6178.93, -1053.07, 411.088, 4.24115, 50000, 0, @CGUID*10, 100, 0),
(@PATH, 2, 6172.82, -1055.80, 411.06, 3.99, 0, 0, 0, 100, 0),
(@PATH, 3, 6174.13, -1056.4, 411.11, 5.78, 5000, 0, @CGUID*10 + 1, 100, 0),
(@PATH, 4, 6172.82, -1055.80, 411.06, 3.99, 0, 0, 0, 100, 0),
(@PATH, 5, 6173.18, -1062.39, 411.23, 4.93, 0, 0, 0, 100, 0),
(@PATH, 6, 6177.66, -1061.17, 411.13, 0, 5000, 0, @CGUID*10 + 1, 100, 0),
(@PATH, 7, 6180.65, -1062.06, 410.92, 4.93, 0, 0,  0, 100, 0),
(@PATH, 8, 6178.93, -1053.07, 411.088, 4.24115, 0, 0, 0, 100, 0);
DELETE FROM `waypoint_scripts` WHERE `id` IN (@CGUID*10, @CGUID * 10+1);
INSERT INTO `waypoint_scripts` VALUES
(@CGUID*10, 0, 1, 17, 0, 0, 0, 0, 0, 0, 894),
(@CGUID*10+1, 0, 1, 69, 0, 0, 0, 0, 0, 0, 895);
-- #596
UPDATE `creature_template` SET `MovementType` = 1, `InhabitType` = 3 WHERE `entry` = 16570;
-- #Ulduar 
DELETE FROM `smart_scripts` WHERE `entryorguid` = 34193 AND `id` = 2;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 34223;
INSERT INTO `smart_scripts` VALUES
(34193, 0, 2, 0, 6, 0, 100, 1, 0, 0, 0, 0, 11, 64873, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(34223, 0, 0, 1, 54, 0, 100, 1, 0, 0, 0, 0, 11, 64875, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(34223, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 6500, 0, 0, 0, 0, 0, 1, 0, 0 , 0, 0, 0, 0, 0 ,''); 
UPDATE `creature_template` SET `AIName` = "SmartAI", `flags_extra` = 2 WHERE `entry` = 34223;
-- #183
DELETE FROM `smart_scripts` WHERE `entryorguid` = 19995 AND `id` = 6;
-- #184
UPDATE `smart_scripts` SET `action_param1` = 0 WHERE `entryorguid` = 20058 AND `id` = 1;
-- #321
SET @ILIDAN = 22083;
SET @TOROTH = 22076;
SET @AURALION = 22073;
DELETE FROM `creature_text` WHERE `entry` = @ILIDAN AND `groupid` BETWEEN 7 AND 12;
DELETE FROM `creature_text` WHERE `entry` IN (@TOROTH, @AURALION);
INSERT INTO `creature_text` VALUES
(@ILIDAN, 7, 0, 'What manner of fool dares stand before Illidan Stormrage? Soldiers, destroy these insects!', 14, 0, 100, 0, 0, 0, 0, 'Illidan'),
(@ILIDAN, 8, 0, 'You are no challenge for the Crimson Sigil. Mind breakers, end this nonsense!', 14, 0, 100, 0, 0, 0, 0, 'Illidan'),
(@ILIDAN, 9, 0, 'Run while you still can. The highlords come soon...', 14, 0, 100, 0, 0, 0, 0, 'Illidan'),
(@ILIDAN, 10, 0, 'Torloth, your master calls!', 14, 0, 100, 0, 0, 0, 0, 'Illidan'),
(@ILIDAN, 11, 0, 'So you have defeated the Crimson Sigil. You now seek to challenge my rule? Not even Arthas could defeat me, yet you dare to even harbor such thoughts? Then I say to you, come! Come <name>! The Black Temple awaits...', 14, 0, 100, 0, 0, 0, 0, 'Illidan'),
(@ILIDAN, 12, 0, 'Destroy them, Torloth. Let loose their blood like a river upon this hallowed ground.', 14, 0, 100, 0, 0, 0, 0, 'Illidan'),
(@TOROTH, 0, 0, 'At your command my liege...', 12, 0, 100, 0, 0, 0, 0, 'Toroth'),
(@TOROTH, 1, 0, 'As you desire, Lord Illidan.', 12, 0, 100, 0, 0, 0, 0, 'Toroth'),
(@TOROTH, 2, 0, 'For Lord Illidan, I would sacrifice even this magnificent physique. On this day, you will fall - another victim of Torloth...', 12, 0, 100, 0, 0, 0, 0, 'Toroth'),
(@AURALION, 0, 0, 'Quickly! Get to the middle of the platform! Illidan`s fury is soon to be unleashed!', 12, 0, 100, 0, 0, 0, 0, 'Auralion'),
(@AURALION, 1, 0, 'Return to Shattrath, hero. Seek out the wisdom of A`dal.', 12, 0, 100, 0, 0, 0, 0, 'Auralion');
