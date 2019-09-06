SET @ENTRY:= 250200;

DELETE FROM `creature_template` WHERE `entry` BETWEEN @ENTRY + 0 AND @ENTRY + 23;
INSERT INTO `creature_template` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 10992, 0, 0, 0, 'Diablo', '', '', 0, 83, 83, 2, 14, 0, 1, 1.14286, 1, 0, 1000, 1000, 0, 1, 1, 2000, 2000, 2, 0, 34816, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 617297919, 0, "npc_boss_six_diablo", 12340),
(@ENTRY + 1, 0, 0, 0, 0, 0, 30039, 0, 0, 0, 'Diablo nether portal', '', '', 0, 83, 83, 2, 14, 0, 1, 1.14286, 1, 0, 1000, 1000, 0, 1, 1, 2000, 2000, 2, 0, 34816, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 617297919, 0, "", 12340),
(@ENTRY + 2, 0, 0, 0, 0, 0, 19503, 0, 0, 0, 'Abyss Knight', '', '', 0, 83, 83, 2, 14, 0, 1, 1.14286, 1, 0, 1000, 1000, 0, 1, 1, 2000, 2000, 2, 0, 34816, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 617297919, 0, "", 12340),
(@ENTRY + 3, 0, 0, 0, 0, 0, 18237, 0, 0, 0, 'Kazzak copy', '', '', 0, 83, 83, 2, 14, 0, 1, 1.14286, 1, 0, 1000, 1000, 0, 1, 1, 2000, 2000, 2, 0, 34816, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 617297919, 0, "", 12340),
(@ENTRY + 4, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'Diablo beam target', '', '', 0, 83, 83, 2, 14, 0, 1, 1.14286, 1, 0, 1000, 1000, 0, 1, 1, 2000, 2000, 2, 0, 34816, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 617297919, 0, "npc_boss_six_beam_trigger", 12340),
(@ENTRY + 5, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'Diablo', 'Beam target explosion trigger', '', 0, 83, 83, 2, 14, 0, 1, 1.14286, 1, 0, 1000, 1000, 0, 1, 1, 2000, 2000, 2, 0, 34816, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 617297855, 0, "npc_boss_six_beam_trigger_explosion", 12340),
(@ENTRY + 6, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'Diablo', 'Heart beam target', '', 0, 83, 83, 2, 14, 0, 1, 1.14286, 1, 0, 1000, 1000, 0, 1, 1, 2000, 2000, 2, 0, 34816, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, "npc_boss_diablo_playerclone", 12340),
(@ENTRY + 7, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'Diablo', 'fiery comet trigger', '', 0, 83, 83, 2, 14, 0, 1, 1.14286, 1, 0, 1000, 1000, 0, 1, 1, 2000, 2000, 2, 0, 34816, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 617297919, 0, "npc_boss_diablo_comet_trigger", 12340),

(@ENTRY + 8, 0, 0, 0, 0, 0,  1060, 0, 0, 0, 'Pentagon trigger 1', '', '', 0, 83, 83, 2, 14, 0, 1, 1.14286, 1, 0, 1000, 1000, 0, 1, 1, 2000, 2000, 2, 0, 34816, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 617297919, 128, "", 12340),
(@ENTRY + 9, 0, 0, 0, 0, 0,  1060, 0, 0, 0, 'Pentagon trigger 2', '', '', 0, 83, 83, 2, 14, 0, 1, 1.14286, 1, 0, 1000, 1000, 0, 1, 1, 2000, 2000, 2, 0, 34816, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 617297919, 128, "", 12340),
(@ENTRY + 10, 0, 0, 0, 0, 0, 1060, 0, 0, 0, 'Pentagon trigger 3', '', '', 0, 83, 83, 2, 14, 0, 1, 1.14286, 1, 0, 1000, 1000, 0, 1, 1, 2000, 2000, 2, 0, 34816, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 617297919, 128, "", 12340),
(@ENTRY + 11, 0, 0, 0, 0, 0, 1060, 0, 0, 0, 'Pentagon trigger 4', '', '', 0, 83, 83, 2, 14, 0, 1, 1.14286, 1, 0, 1000, 1000, 0, 1, 1, 2000, 2000, 2, 0, 34816, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 617297919, 128, "", 12340),
(@ENTRY + 12, 0, 0, 0, 0, 0, 1060, 0, 0, 0, 'Pentagon trigger 5', '', '', 0, 83, 83, 2, 14, 0, 1, 1.14286, 1, 0, 1000, 1000, 0, 1, 1, 2000, 2000, 2, 0, 34816, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 617297919, 128, "", 12340),

(@ENTRY + 13, 0, 0, 0, 0, 0, 18036, 0, 0, 0, 'Diabolic Infernal', '', '', 0, 83, 83, 2, 14, 0, 1, 1.14286, 0.45, 0, 1000, 1000, 0, 1, 1, 2000, 2000, 2, 0, 34816, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 617297919, 0, "npc_boss_six_diabolic_infernal", 12340),
(@ENTRY + 14, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'Diablo', 'Damage increase trigger', '', 0, 83, 83, 2, 14, 0, 1, 1.14286, 1, 0, 1000, 1000, 0, 1, 1, 2000, 2000, 2, 0, 34816, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 617297919, 128, "npc_boss_six_increased_damage_trigger", 12340),
(@ENTRY + 15, 0, 0, 0, 0, 0, 25680, 0, 0, 0, 'Unstable Fire Elemental', '', '', 0, 80, 80, 1, 16, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 212, 1, 0, 0, 'npc_boss_diablo_fire_elementals', 12340),
(@ENTRY + 16, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'Diablo', 'Ball of flames player', '', 0, 80, 80, 1, 16, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'NullCreatureAI', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 212, 1, 0, 0, 'npc_boss_player_flame_sphere', 12340),
(@ENTRY + 17, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'Diablo', 'Ball of flames boss', '', 0, 80, 80, 1, 16, 0, 1, 1.14286, 3, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'NullCreatureAI', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 212, 1, 0, 0, '', 12340),

(@ENTRY + 18, 0, 0, 0, 0, 0, 17890, 0, 0, 0, 'Ashes of alar copy', '', '', 0, 80, 80, 1, 35, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'NullCreatureAI', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 140, 1, 0, 0, '', 12340),
(@ENTRY + 19, 0, 0, 0, 0, 0, 19135, 0, 0, 0, 'Onyx netherwing drake copy', '', '', 0, 80, 80, 1, 16, 0, 1, 1.14286, 2, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'NullCreatureAI', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 212, 1, 0, 0, 'npc_boss_diablo_shadow_drake', 12340),
(@ENTRY + 20, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'Diablo', 'napalam shell trigger', '', 0, 83, 83, 1, 16, 0, 1, 1.14286, 2, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'NullCreatureAI', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 212, 1, 0, 0, 'npc_diablo_napalm_shell_trigger', 12340),
(@ENTRY + 21, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'Diablo', 'meteor caster', '', 0, 83, 83, 1, 16, 0, 1, 1.14286, 2, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'NullCreatureAI', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 212, 1, 0, 128, '', 12340),
(@ENTRY + 22, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'Fire elemental spawn in portal trigger', '', '', 0, 83, 83, 1, 16, 0, 1, 1.14286, 2, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'NullCreatureAI', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 212, 1, 0, 128, '', 12340),
(@ENTRY + 23, 0, 0, 0, 0, 0, 22506, 0, 0, 0, 'Shadow Crystal', '', '', 0, 83, 83, 1, 16, 0, 1, 1.14286, 2, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'NullCreatureAI', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 212, 1, 0, 0, '', 12340);

UPDATE `creature_template` SET `npcflag` = `npcflag` | 16777216, `VehicleId` = 25, `InhabitType` = 7 WHERE `entry` = @ENTRY + 18;
UPDATE `creature_template` SET `InhabitType` = 7 WHERE `entry` IN (@ENTRY + 16, @ENTRY + 17);
UPDATE `creature_template` SET `scale` = 10 WHERE `entry` = @ENTRY + 0;
UPDATE `creature_template` SET `AIName` = "NullCreatureAI", `ScriptName` = "" WHERE `entry` = @ENTRY + 1;
UPDATE `creature_template` SET `AIName` = "", `ScriptName` = "npc_boss_six_flying_demon", `InhabitType` = 7 WHERE `entry` = @ENTRY + 3;
UPDATE `creature_template` SET `family` = 0, `unit_flags` = `unit_flags` | 33554432 WHERE `entry` IN (@ENTRY + 4, @ENTRY + 5);
UPDATE `creature_template` SET `AIName` = "NullCreatureAI" WHERE `entry` = @ENTRY + 6;
UPDATE `creature_template` SET `AIName` = "NullCreatureAI" WHERE `entry` = @ENTRY + 7;
UPDATE `creature_template` SET `type_flags` = `type_flags` = 1048576 WHERE `entry` >= @ENTRY AND flags_extra & 128;
UPDATE `creature_template` SET `spell1` = 56091, `spell2` = 56092, `unit_class` = 4 WHERE `entry` = @ENTRY + 18;
UPDATE `creature_template` SET `mechanic_immune_mask` = 650854271 WHERE `entry` BETWEEN @ENTRY + 0 AND @ENTRY + 23;
UPDATE `creature_template` SET `mechanic_immune_mask` = `mechanic_immune_mask` &~ 64 WHERE `entry` = @ENTRY + 6;
UPDATE `creature_template` SET `type` = 3, `flags_extra` = `flags_extra` | 1 WHERE `entry` = @ENTRY + 0;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = @ENTRY + 18;
INSERT INTO `npc_spellclick_spells` VALUES
(@ENTRY + 18, 43671, 1, 0);

SET @CGUID:= 2074700;

DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID + 0 AND @CGUID + 1;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID + 0, 250200, 249, 8, 1, 0, 0, -10.9161, -213.238, -87.7776, 3.137, 300, 0, 0, 13945, 4258, 0, 0, 0, 0);

DELETE FROM `spell_script_names` WHERE `spell_id` IN (67105, 36837, 27673, 20478, 32474, 65979, 43501, 64529, 61585, 68832, 64734, 69856);
INSERT INTO `spell_script_names` VALUES
(67105, "spell_boss_diablo_nether_portal"),
(36837, "spell_boss_six_diablo_meteor"),
(27673, "spell_five_finger_death_punch"),
(20478, "spell_boss_diablo_armageddon"),
(32474, "spell_buffeting_winds_diablo"),
(65979, "spell_boss_diablo_flametongue_weapon"),
(43501, "spell_diablo_siphon_soul"),
(64529, "spell_boss_diablo_plasma_blast"),
(61585, "spell_lightning_marker_visual"),
(68832, "spell_boss_diablo_napalm_shell_damage"),
(64734, "spell_devouring_flame_diablo_hellforge"),
(69856, "spell_diablo_conversion_beam");

-- pozmieniac GUIDy potem
DELETE FROM `creature` WHERE `id` = 250200;
INSERT INTO `creature` VALUES
(2074700, 250200, 249, 8, 1, 0, 0, -10.9161, -213.238, -87.7776, 3.137, 300, 0, 0, 13945, 4258, 0, 0, 0, 0);

