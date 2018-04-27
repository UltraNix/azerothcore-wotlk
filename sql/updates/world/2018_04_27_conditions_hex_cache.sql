DELETE FROM `conditions` WHERE `SourceEntry` = 52644 AND `SourceTypeOrReferenceId` = 13;
INSERT INTO `conditions` VALUES
(13, 2, 52644, 0, 0, 31, 0, 4, 0, 0, 0, 0, 0, '', 'ZolMaz Cache trap Should target player');

DELETE FROM `spell_script_names` WHERE `spell_id` = 52644;
INSERT INTO `spell_script_names` VALUES
(52644, 'spell_q12709_hexed_cache');
