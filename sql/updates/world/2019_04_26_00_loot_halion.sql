UPDATE `creature_loot_template` SET `item` = 49426 WHERE `item` = 47241 AND `entry` IN (
SELECT lootid FROM creature_template WHERE entry IN 
(39751, 39899, 39920, 39922, 39747, 39823, 39746, 39805,
39863, 39864, 39944, 39945, 40142, 40143, 40144, 40145));
