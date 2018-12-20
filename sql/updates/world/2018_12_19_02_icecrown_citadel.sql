DELETE FROM `spell_script_names` WHERE `spell_id` = 71363;
INSERT INTO `spell_script_names` VALUES
(71363, "spell_deathwhisper_summon_spirit");

UPDATE `creature_template` SET `ScriptName` = "npc_king_wrynn_saurfang_icc" WHERE `entry` = 37879;

DELETE FROM `creature_text` WHERE `entry` = 37188;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `TextRange`, `comment`) VALUES
(37188, 0, 0, '%s cries.', 16, 0, 0, 18, 0, 16651, 0, 'Lady Jaina Proudmoore - SAY_OUTRO_ALLIANCE_17'),
(37188, 1, 0, 'It was nothing, your majesty. Just... I\'m proud of my king.', 12, 0, 0, 0, 0, 16652, 0, 'Lady Jaina Proudmoore - SAY_OUTRO_ALLIANCE_19'),
(37188, 2, 0, '%s wipes her tears away and smiles at King Varian Wrynn.', 16, 0, 0, 0, 0, 0, 0, 'Lady Jaina Proudmoore');

DELETE FROM `spell_area` WHERE `spell` IN (73818, 73824, 73822, 73828) AND `area` = 4812;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(73818, 4812, 0, 0, 0, 690, 2, 1, 64, 11),
(73824, 4812, 0, 0, 0, 1101, 2, 1, 64, 11);

UPDATE creature_template SET ScriptName = "npc_saurfang_peon" WHERE entry IN (37930, 37902);
UPDATE creature_template SET ScriptName = "npc_saurfang_vendor" WHERE entry IN (37904, 37903, 37935, 37936);

DELETE FROM `creature` WHERE `guid` = 202600;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(202600, 38433, 624, 3, 1, 0, 1, -43.3316, -288.708, 91.2511, 1.58825, 604800, 0, 0, 1, 0, 0, 0, 0, 0);
