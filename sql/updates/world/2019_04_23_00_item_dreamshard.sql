-- DB/Item: Dream shard - reduce number of dropped items
UPDATE `disenchant_loot_template` SET `mincountOrRef` = 1, `maxcount` = 2 WHERE `entry` IN (16, 35) AND `item` = 34052;
