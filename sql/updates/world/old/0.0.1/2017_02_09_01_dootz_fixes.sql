UPDATE `quest_template` SET `PrevQuestId` = 13315 WHERE `id` = 13318;
UPDATE `quest_template` SET `PrevQuestId` = 13318 WHERE `id` = 13323;
UPDATE `quest_template` SET `PrevQuestId` = 13315 WHERE `id` = 13319;
UPDATE `quest_template` SET `PrevQuestId` = 13315 WHERE `id` = 13320;
UPDATE `quest_template` SET `PrevQuestId` = 13320 WHERE `id` = 13321;
UPDATE `quest_template` SET `PrevQuestId` = 13321 WHERE `id` = 13322;
UPDATE `quest_template` SET `PrevQuestId` = 13318 WHERE `id` = 13342;
UPDATE `quest_template` SET `PrevQuestId` = 13342 WHERE `id` = 13344;
UPDATE `quest_template` SET `PrevQuestId` = 13318 WHERE `id` = 13345;
UPDATE `quest_template` SET `PrevQuestId` = 13345 WHERE `id` = 13346;
UPDATE `quest_template` SET `PrevQuestId` = 13346 WHERE `id` = 13350;
UPDATE `quest_template` SET `PrevQuestId` = 13346 WHERE `id` = 13337;
UPDATE `quest_template` SET `PrevQuestId` = 13337 WHERE `id` = 13335;
UPDATE `quest_template` SET `PrevQuestId` = 13335 WHERE `id` = 13338;
UPDATE `quest_template` SET `PrevQuestId` = 13335 WHERE `id` = 13339;
UPDATE `quest_template` SET `PrevQuestId` = 13237 WHERE `id` = 13288;
UPDATE `quest_template` SET `PrevQuestId` = 13288 WHERE `id` = 13289;
UPDATE `quest_template` SET `PrevQuestId` = 13237 WHERE `id` = 13294;
UPDATE `quest_template` SET `PrevQuestId` = 13294 WHERE `id` = 13298;
UPDATE `quest_template` SET `PrevQuestId` = 13345 WHERE `id` = 13332;
UPDATE `quest_template` SET `PrevQuestId` = 12898 WHERE `id` = 13386;
UPDATE `quest_template` SET `PrevQuestId` = 13295 WHERE `id` = 13297;

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (369200, 369201);
INSERT INTO `smart_scripts` VALUES 
(369200, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Volcor - On Script - Say Line 0'),
(369200, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 19, 512, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Volcor - On Script - Remove Flag Immune To NPC'), 
(369200, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 53, 0, 3692, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 'Volcor - On Script - Start Waypoint'),
(369200, 9, 3, 0, 0, 0, 100, 0, 110000, 110000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Volcor - On Script - Say Line 2'),
(369200, 9, 4, 0, 0, 0, 100, 0, 0, 0, 0, 0, 15, 994, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Volcor - On Script - Quest Credit \'Escape Through Force\''),
(369201, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 'Volcor - On Script - Say Line 0'),
(369201, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 19, 512, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Volcor - On Script - Remove Flag Immune To NPC'),
(369201, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 53, 0, 3692, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 'Volcor - On Script - Start Waypoint'),
(369201, 9, 3, 0, 0, 0, 100, 0, 110000, 110000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Volcor - On Script - Say Line 3'),
(369201, 9, 4, 0, 0, 0, 100, 0, 0, 0, 0, 0, 15, 995, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Volcor - On Script - Quest Credit \'Escape Through Stealth\'');

UPDATE `event_scripts` SET `datalong2` = 30000 WHERE `id` = 12307;

UPDATE `smart_scripts` SET `event_param1` = 30000, `event_param2` = 30000 WHERE `entryorguid` = 261000 AND `id` = 6;
UPDATE `smart_scripts` SET `event_param1` = 30000, `event_param2` = 30000 WHERE `entryorguid` = 261000 AND `id` = 10;

DELETE FROM `creature` WHERE `guid` = 104161;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 26459;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 26459;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 26673 AND `id` = 2;
INSERT INTO `smart_scripts` VALUES
(26673, 0, 2, 0, 1, 0, 100, 0, 8000, 9000, 8000, 9000, 5, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Image of Archmage Modera - OOC - Play Emote'),
(26459, 0, 0, 0, 1, 0, 100, 0, 10000, 11000, 10000, 11000, 5, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Commander Saia Azuresteel - OOC - Play Emote');

DELETE FROM `conditions` WHERE `SourceEntry` = 49838;
INSERT INTO `conditions` VALUES
(13, 1, 49838, 0, 0, 24, 0, 2, 0, 0, 0, 0, 0, '','Stop Time should target only Dragons'),
(13, 2, 49838, 0, 0, 24, 0, 2, 0, 0, 0, 0, 0, '','Stop Time should target only Dragons'),
(13, 4, 49838, 0, 0, 24, 0, 2, 0, 0, 0, 0, 0, '','Stop Time should target only Dragons');


UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 25623;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 25623;
INSERT INTO `smart_scripts` VALUES
(25623, 0, 0, 0, 8, 0, 100, 0, 47166, 0, 0, 0, 41, 1000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');
