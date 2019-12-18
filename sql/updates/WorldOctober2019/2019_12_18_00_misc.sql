-- DB/Loot: Howling Wind - fix ( increase ) drop chance https://github.com/SunwellTracker/issues/issues/2690
-- DB/GO: fix spawn position of some herbs in Western Plaguelands ( Azathoth's report )
-- DB/Loot: Smokywood Pastures Gift Pack should always drop something ( Tide's report )
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 20 WHERE `item` = 24504;
UPDATE `gameobject` SET `position_z` = 55.42 WHERE `guid` = 16022;
UPDATE `item_loot_template` SET `ChanceOrQuestChance` = 0, `groupid` = 1 WHERE `entry` = 17727;