-- DB/NPC: Mjordin Combatant - frostweave cloth drop 
-- DB/Go: Increase number of thorium spawns https://github.com/SunwellTracker/issues/issues/1636 https://github.com/SunwellTracker/issues/issues/2603
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 35 WHERE `entry` = 30037 AND `item` = 26040;
UPDATE `reference_loot_template` SET `maxcount` = 4 WHERE `entry` = 26040 AND `item` = 33470;

UPDATE `pool_template` SET `max_limit` = 35 WHERE `entry` = 1708;
UPDATE `pool_template` SET `max_limit` = 55 WHERE `entry` = 1709;
UPDATE `pool_template` SET `max_limit` = 43 WHERE `entry` = 1722;
UPDATE `pool_template` SET `max_limit` = 25 WHERE `entry` = 1723;
UPDATE `pool_template` SET `max_limit` = 30 WHERE `entry` = 1726;
UPDATE `pool_template` SET `max_limit` = 40 WHERE `entry` = 9916;
