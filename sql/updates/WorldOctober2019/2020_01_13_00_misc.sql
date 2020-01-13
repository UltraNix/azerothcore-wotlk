-- DB/Quest: Iron Pommel - should drop from chest not slimes, fix issue with chest being not interactable https://github.com/SunwellTracker/issues/issues/2799
DELETE FROM `creature_loot_template` WHERE `item` = 5519;
UPDATE `gameobject_loot_template` SET `ChanceOrQuestChance` = -100 WHERE `item` = 5519 AND `entry` = 2971;
UPDATE `smart_scripts` SET `action_type` = 86, `action_param3` = 7 WHERE `entryorguid` = 3928 AND `id` = 1;
