SET @GAHZRANKAPATHID:= 15114 * 10;
DELETE FROM `waypoint_data` WHERE `id` = @GAHZRANKAPATHID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`) VALUES
(@GAHZRANKAPATHID, 1, -11679.807, -1696.884, -4.940),
(@GAHZRANKAPATHID, 2, -11678.780, -1713.134, 8.3364),
(@GAHZRANKAPATHID, 3, -11710.557, -1758.050, 8.3364);

UPDATE `spell_target_position` SET `target_position_x` = -11676.006, `target_position_y` = -1698.0500, `target_position_z` = 8.409842 WHERE id IN (24325, 24593);
DELETE FROM `spell_script_names` WHERE `spell_id` = 24325;
INSERT INTO `spell_script_names` VALUES
(24325, "spell_pagle_point_spawn_ghaz");
