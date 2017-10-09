DELETE FROM `spell_ranks` WHERE `first_spell_id`=57514 AND `rank`=2;
INSERT INTO `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) VALUES (57514, 57516, 2);
DELETE FROM `spell_ranks` WHERE `first_spell_id`=57514 AND `rank`=1;
INSERT INTO `spell_ranks` (`first_spell_id`, `spell_id`, `rank`) VALUES (57514, 57514, 1);

DELETE FROM `spell_group` WHERE `id`=1031 AND `spell_id`=57514;
INSERT INTO `spell_group` (`id`, `spell_id`, `special_flag`) VALUES (1031, 57514, 16);

UPDATE `spell_group` SET `special_flag` = 16 WHERE `spell_id` = 12880;