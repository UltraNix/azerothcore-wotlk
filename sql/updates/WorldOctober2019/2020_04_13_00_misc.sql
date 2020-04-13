-- DB/GO: Dire Maul - limit number of thorium vein spawns
-- DB/Quest: Kurenai reputation correct reputation gain for some quests ( 250 -> 500 ) https://github.com/SunwellTracker/issues/issues/2516
-- DB/Fishing: Raw Summer Bass/Winter Squid - seasonal fishing https://github.com/SunwellTracker/issues/issues/2838
DELETE FROM `pool_template` WHERE `entry` = 50004;
INSERT INTO `pool_template` VALUES
(50004, 1, 'Dire Maul Vein');
DELETE FROM `pool_gameobject` WHERE `entry` = 50004 AND `guid` IN (269112,269111,269110,120704);
INSERT INTO `pool_gameobject` VALUES
(269112, 50004, 0, ''),
(269111, 50004, 0, ''),
(269110, 50004, 0, ''),
(120704, 50004, 0, '');

UPDATE `quest_template` SET `RewardFactionValueId1` = 7 WHERE `id` IN 
(9830,
9833,
9834,
9835,
9839,
9874,
9878,
9902,
9905,
9917,
9921,
9923,
9924,
9936,
9940,
9954,
10115,
10116,
10476,
10477);

DELETE FROM `reference_loot_template` WHERE `entry` IN (11009, 11005) AND `item` = 13755;
INSERT INTO `reference_loot_template` VALUES
(11009,13755, 15, 1, 1, 1, 1),
(11005,13755, 20, 1, 1, 1, 1);
DELETE FROM `conditions` WHERE `SourceGroup` IN (11009, 11005) AND `SourceEntry` IN (13755, 13756) AND `SourceTypeOrReferenceId` = 3;
INSERT INTO `conditions` VALUES 
(3, 11009, 13755, 0, 0, 12, 0, 2, 0, 0, 0, 0, 0, '', 'Winter Squid can be caught only during Winterveil'),
(3, 11009, 13756, 0, 0, 12, 0, 2, 0, 0, 1, 0, 0, '', 'Raw Summer Bass can\'t be caught only during Winterveil'),
(3, 11005, 13755, 0, 0, 12, 0, 2, 0, 0, 0, 0, 0, '', 'Winter Squid can be caught only during Winterveil'),
(3, 11005, 13756, 0, 0, 12, 0, 2, 0, 0, 1, 0, 0, '', 'Raw Summer Bass can\'t be caught only during Winterveil');
