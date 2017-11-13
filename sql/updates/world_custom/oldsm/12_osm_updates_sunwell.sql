DELETE FROM `spell_script_names` WHERE `spell_id` IN (43657, 56897, 26659, 39028);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(43657, "spell_electrical_storm_damage"),
(56897, "spell_storm_call_old_scarlet"),
(26659, "spell_sam_test_aura"),
(39028, "spell_lightning_discharge_osm");


UPDATE `creature_template` SET `ScriptName` = "npc_storm_call_trigger_OSM", `name` = "storm call trigger", `modelid1` = 11686, `flags_extra` = 128 WHERE `entry` = 400045;
