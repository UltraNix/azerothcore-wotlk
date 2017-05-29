UPDATE `creature_template` SET `dmg_multiplier` = '2.5', `Health_mod` = '3' WHERE `creature_template`.`entry` = 33089;
UPDATE `creature_template` SET `dmg_multiplier` = '3', `Health_mod` = '10' WHERE `creature_template`.`entry` = 34221;

UPDATE `item_template` SET `stat_value1` = '587',
`stat_value2` = '52',
`stat_value3` = '54',
`stat_value4` = '47',
`stat_value5` = '46' WHERE `item_template`.`entry` = 46017;