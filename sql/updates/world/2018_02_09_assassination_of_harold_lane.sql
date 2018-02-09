DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry` IN (46385);
INSERT INTO `conditions` VALUES
(13, 1, 46385, 0, 0, 31, 0, 3, 25804, 0, 0, 0, 0, '', 'Stampede targets Harold Lane');

DELETE FROM `spell_script_names` WHERE `spell_id`=46368;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(46368, 'spell_blow_cenarion_horn');

UPDATE `creature_template`SET `unit_flags`=0, `faction`=7, `ScriptName`='npc_stamped_creature' WHERE `entry` IN (25988,25989,25990);

DELETE FROM `smart_scripts` WHERE `entryorguid` = 25804 AND `id` = 3;
INSERT INTO `smart_scripts` VALUES
(25804, 0, 3, 0, 6, 0, 100, 0, 0, 0, 0, 0, 33, 25804, 0, 0, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 'Harold Lane - On Death - Give Kill Credit');