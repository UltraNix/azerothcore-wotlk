-- [Quest] Princess Must Die! - remove one bodyguard #2610 https://github.com/SunwellTracker/issues/issues/2610
-- [Quest] Children of Ursoc correct reputation reward https://github.com/SunwellTracker/issues/issues/2587
-- [Quest] Shadow of Thel'zan the Duskbringer - add script https://github.com/SunwellTracker/issues/issues/2605
UPDATE `creature_template` SET `lootid` = 0, `flags_extra` = `flags_extra` | 64  WHERE `entry` IN (30957, 30958);
UPDATE `creature` SET `MovementType`=0 WHERE `guid`=131180;
DELETE FROM `creature` WHERE `guid` = 80848;

DELETE FROM `creature_text` WHERE `entry` = 27510;
INSERT INTO `creature_text` VALUES
(27510, 0, 0, 'Soldiers of the frozen wastes, rise and hear the call of your master! Do not let $N escape with the tome!', 14, 0, 100, 0, 0, 0, 0, 'Shadow of Thelzan the Duskbringer'),
(27510, 1, 0, 'Impressive. The master said that you and your people would be a nuisance. No matter, your end draws near. Soon the combined might of Naxxramas will come down upon this place and shatter your meager existence.', 12, 0, 100, 0, 0, 0, 0, 'Shadow of Thelzan the Duskbringer'),
(27510, 2, 0, 'Where do you think you\'re going with that, mortal? Put the tome down and I might spare you an eternity of anguish.', 12, 0, 100, 0, 0, 0, 0, 'Shadow of Thelzan the Duskbringer');

UPDATE `quest_template` SET `RewardFactionId1` = 1050 WHERE `id` = 12247;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 27510;
UPDATE `gameobject_template` SET `AIName` = "SmartGameObjectAI", `ScriptName` = "" WHERE `entry` = 189311;

DELETE FROM `smart_scripts` WHERE `entryorguid` = 189311;
INSERT INTO `smart_scripts` VALUES
(189311, 1, 0, 0, 19, 0, 100, 0, 12312, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 10, 131180, 27510, 0, 0, 0, 0, 0, 'On quest taken - Set Data');


DELETE FROM `smart_scripts` WHERE `entryorguid` = 27510;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 2751000;
INSERT INTO `smart_scripts` VALUES
(27510, 0, 0, 0, 38, 0, 100, 0, 1, 1, 0, 0, 80, 2751000, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On quest taken - start script'),
(2751000, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0 ,0, 0, 0, 0, 0, 'On Script Say Line 0'),
(2751000, 9, 1, 0, 0, 0, 100, 0, 5000, 5000, 5000, 5000, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0 ,0, 0, 0, 0, 0, 'On Script Say Line 0'),
(2751000, 9, 2, 0, 0, 0, 100, 0, 5000, 5000, 5000, 5000, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0 ,0, 0, 0, 0, 0, 'On Script Say Line 0');
