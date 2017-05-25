-- #321
UPDATE `creature_template_addon` SET `auras` = '22766' WHERE `entry` = 938;

-- #182
DELETE FROM `waypoints` WHERE `entry` = 19991;
INSERT INTO `waypoints` VALUES
(19991, 0, 1725.96, 6316.71, 5.2, ''),
(19991, 1, 1730.81, 6326.17, 10.12, ''),
(19991, 2, 1718.19, 6330.83, 16.6, ''),
(19991, 3, 1704.28, 6332.57, 23.56, ''),
(19991, 4, 1698.56, 6327.52, 27.20, ''),
(19991, 5, 1692.61, 6321.89, 30.68, ''),
(19991, 6, 1701.61, 6307.23, 33.19, '');

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` IN (19991, 21238, 20116, 28288, 19952, 19956, 21294);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (20116, 28288, 19956, 21294);
DELETE FROM `smart_scripts` WHERE `entryorguid` = 19991 AND `id` = 6;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 21238 AND `id` = 5;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 19952 AND `id` = 5;
INSERT INTO `smart_scripts` VALUES
(19991, 0, 6, 0, 54, 0, 100, 1, 0, 0, 0, 0, 53, 0, 19991, 0, 10518, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(21238, 0, 5, 0, 54, 0, 100, 1, 0, 0, 0, 0, 53, 0, 19991, 0, 10518, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(19952, 0, 5, 0, 54, 0, 100, 1, 0, 0, 0, 0, 53, 0, 19991, 0, 10518, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(20116, 0, 0, 0, 54, 0, 100, 1, 0, 0, 0, 0, 53, 0, 19991, 0, 10518, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(28288, 0, 0, 0, 54, 0, 100, 1, 0, 0, 0, 0, 53, 0, 19991, 0, 10518, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(19956, 0, 0, 0, 54, 0, 100, 1, 0, 0, 0, 0, 53, 0, 19991, 0, 10518, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(21294, 0, 0, 0, 54, 0, 100, 1, 0, 0, 0, 0, 53, 0, 19991, 0, 10518, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');

-- #170
UPDATE `quest_template` SET `PrevQuestId` = 13232 WHERE `id` = 13233; -- No Mercy after Finish Me
UPDATE `quest_template` SET `PrevQuestId` = 13231 WHERE `id` = 13286; -- All the help after Broken Front
UPDATE `quest_template` SET `PrevQuestId` = 13231 WHERE `id` = 13290; -- Your Attention after Broken Front
UPDATE `quest_template` SET `PrevQuestId` = 13334 WHERE `id` = 13314; -- Get the Message after Bloodspattered Banners
UPDATE `quest_template` SET `PrevQuestId` = 13314 WHERE `id` = 13333; -- Capture More dispatches after get the message

-- #170
DELETE FROM `waypoints` WHERE `entry` = 19991;
INSERT INTO `waypoints` VALUES
(19991, 0, 1725.96, 6316.71, 5.2, ''),
(19991, 1, 1730.81, 6326.17, 10.12, ''),
(19991, 2, 1718.19, 6330.83, 16.6, ''),
(19991, 3, 1704.28, 6332.57, 23.56, ''),
(19991, 4, 1698.56, 6327.52, 27.20, ''),
(19991, 5, 1692.61, 6321.89, 30.68, ''),
(19991, 6, 1701.61, 6307.23, 33.19, '');

-- #182
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` IN (19991, 21238, 20116, 28288, 19952, 19956, 21294);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (20116, 28288, 19956, 21294);
DELETE FROM `smart_scripts` WHERE `entryorguid` = 19991 AND `id` = 6;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 21238 AND `id` = 5;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 19952 AND `id` = 5;
INSERT INTO `smart_scripts` VALUES
(19991, 0, 6, 0, 54, 0, 100, 1, 0, 0, 0, 0, 53, 0, 19991, 0, 10518, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Just summoned - start waypoint'),
(21238, 0, 5, 0, 54, 0, 100, 1, 0, 0, 0, 0, 53, 0, 19991, 0, 10518, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Just summoned - start waypoint'),
(19952, 0, 5, 0, 54, 0, 100, 1, 0, 0, 0, 0, 53, 0, 19991, 0, 10518, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Just summoned - start waypoint'),
(20116, 0, 0, 0, 54, 0, 100, 1, 0, 0, 0, 0, 53, 0, 19991, 0, 10518, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Just summoned - start waypoint'),
(28288, 0, 0, 0, 54, 0, 100, 1, 0, 0, 0, 0, 53, 0, 19991, 0, 10518, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Just summoned - start waypoint'),
(19956, 0, 0, 0, 54, 0, 100, 1, 0, 0, 0, 0, 53, 0, 19991, 0, 10518, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Just summoned - start waypoint'),
(21294, 0, 0, 0, 54, 0, 100, 1, 0, 0, 0, 0, 53, 0, 19991, 0, 10518, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Just summoned - start waypoint');

-- #163
DELETE FROM `conditions` WHERE `SourceEntry` = 33836;
INSERT INTO `conditions` VALUES
(13, 1, 33836, 0, 1, 31, 0, 4, 0, 0, 1, 0, 0, '', 'Dropping Heavy Bomb should NOT affect players'),
(13, 2, 33836, 0, 1, 31, 0, 4, 0, 0, 1, 0, 0, '', 'Dropping Heavy Bomb should NOT affect players');

-- #283
DELETE FROM `creature`  WHERE `guid` = 113330;
UPDATE `smart_scripts` SET `target_x` = 2318.15, `target_y` = -5744.10, `target_z` = 155.72, `target_o` = 5.59 WHERE `entryorguid` = 2890700 AND `id` IN ( 3, 10, 14);
UPDATE `creature` SET `position_x` = 2318.15, `position_y` = -5744.10, `position_z` = 155.72, `orientation` = 5.59 WHERE `guid` = 130344;
UPDATE `smart_scripts` SET `target_x` = 2309.61, `target_y` = -5735.08, `target_z` = 155.31, `target_o` = 2.05  WHERE `entryorguid` = 2890700 AND `id` IN ( 1, 6);

UPDATE `creature` SET `spawndist` = 0, `MovementType` = 0 WHERE `guid` = 128578;

-- #319 
UPDATE `creature_template` SET `faction` = 35 WHERE `entry` = 21318;

-- #350
UPDATE `creature` SET `orientation` = 4.24 WHERE `guid` = 117815;

-- #445
DELETE FROM `conditions` WHERE `SourceEntry` = 35480;
INSERT INTO `conditions` VALUES
(17, 0, 35480, 0, 0, 1, 0, 5487, 0, 0, 1, 0, 0, '','Dont apply Human Illusion while in Bear Form'), (17, 0, 35480, 0, 0, 1, 0, 24858, 0, 0, 1, 0, 0, '','Dont apply Human Illusion while in Moonkin Form'),
(17, 0, 35480, 0, 0, 1, 0, 768, 0, 0, 1, 0, 0, '','Dont apply Human Illusion while in Cat Form'), (17, 0, 35480, 0, 0, 1, 0, 33891, 0, 0, 1, 0, 0, '','Dont apply Human Illusion while in Tree of Life Form');

-- #330
DELETE FROM `conditions` WHERE `SourceEntry` IN (74541,54469);
INSERT INTO `conditions` VALUES
(13, 1, 74541, 0, 0, 31, 0, 3, 29333, 0, 0, 0, 0, '', 'Frost Breath should target Gryphon Rider'),
(13, 1, 54469, 0, 1, 31, 0, 3, 29333, 0, 0, 0, 0, '', 'Plague Strike should target Gryphon Rider'),
(13, 2, 54469, 0, 1, 31, 0, 3, 29333, 0, 0, 0, 0, '', 'Plague Strike should target Gryphon Rider'),
(13, 4, 54469, 0, 1, 31, 0, 3, 29333, 0, 0, 0, 0, '', 'Plague Strike should target Gryphon Rider');

-- #602
DELETE FROM `achievement_reward` WHERE `entry` IN(2138,2137);
INSERT INTO `achievement_reward` VALUES
(2138, 0, 0, 44164, 32346, "Glory of the Rider", "Dear $N,$B$BI hope ye're doing well and that ye've had time to recover from our adventures in Naxxramas.$B$BWe've managed to capture hatchling of black drake.  ... We thought perhaps you'd accept him as a gift.$B$BGood luck,$BJaina Proudmoore",0),
(2137, 0, 0, 44175, 4949, "Glory of the Rider", "Dear $N,$B$BI hope ye're doing well and that ye've had time to recover from our adventures in Naxxramas.$B$BWe've managed to capture hatchling of plagued drake.  ... We thought perhaps you'd accept him as a gift.$B$BMay the Elemnts guide you$BThrall, son of Durotan",0);

-- #385
DELETE FROM `creature_addon` WHERE `guid` = 118361;
INSERT INTO `creature_addon` VALUES
(118361, 0, 0, 1, 0, 0, '');