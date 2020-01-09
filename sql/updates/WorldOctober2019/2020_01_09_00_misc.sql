 -- DB/NPC: Ghost Howl should be tameable - https://github.com/SunwellTracker/issues/issues/2793
-- DB/Quest: Blessing of Zim'Torga should be a repeatable quest - https://github.com/SunwellTracker/issues/issues/2794
-- DB/Quest: Bringing Down Heb'Jin - despawn bat after Heb Jin is defeated https://github.com/SunwellTracker/issues/issues/2773
UPDATE `creature_template` SET `type_flags` = 1, `family` = 1 WHERE `entry` = 3056;
UPDATE `quest_template` SET `SpecialFlags` = 1 WHERE `id` = 12618;
UPDATE `smart_scripts` SET `link` = 0 WHERE `entryorguid` = 28636 AND `id` = 10;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 28636 AND `id` = 11;
INSERT INTO `smart_scripts` VALUES
(28636, 0, 11, 0, 6, 0, 100, 0, 0, 0, 0, 0, 41, 500, 0, 0, 0, 0, 0, 19, 28639, 5, 0, 0, 0, 0, 0, 'Heb Jin - On Link(Landed) - Remove Bat\'s Immune to PC flag'); 