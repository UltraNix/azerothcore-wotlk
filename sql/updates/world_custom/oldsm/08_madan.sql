SET @MADANTHUL := 400043;
SET @OVERLORD := 400044;
SET @DERATIN := 400045;
SET @BEAMCHANNELER := 400046;
SET @KAMIKAZE := 400047;
SET @ARROWMARKER := 400048;
SET @DARKNESSTARGET := 400049;

SET @cGUID := 400002;

DELETE FROM `creature_template` WHERE `entry` IN (@MADANTHUL, @OVERLORD, @DERATIN, @BEAMCHANNELER, @KAMIKAZE, @ARROWMARKER, @DARKNESSTARGET);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES 
(@MADANTHUL, 0, 0, 0, 0, 0, 30168, 0, 0, 0, "Madan\'tul Rada", '<The Risen>', NULL, 0, 83, 83, 2, 16, 0, 1, 1.14286, 1.5, 3, 417, 582, 0, 608, 70.8, 2000, 0, 1, 64, 0, 0, 0, 0, 0, 0, 0, 341, 506, 80, 7, 4, 100007, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2000000, 2500000, '', 0, 3, 1, 1500, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 257, 'boss_madantul_rada'),
(@OVERLORD, 0, 0, 0, 0, 0, 21021, 0, 0, 0, 'Risen Overlord', '<The Risen>', NULL, 0, 83, 83, 2, 16, 0, 1, 1.14286, 1, 1, 234, 331, 0, 286, 5.9, 2000, 0, 2, 64, 2048, 0, 0, 0, 0, 0, 0, 198, 295, 33, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 20, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650755903, 0, 'npc_drops_channeler'),
(@DERATIN, 0, 0, 0, 0, 0, 19679, 0, 0, 0, 'Dera\'tin\'jeragoth', NULL, NULL, 0, 83, 83, 2, 16, 0, 1, 1.14286, 1, 1, 200, 281, 0, 278, 80.8, 2000, 0, 1, 0, 2048, 0, 1, 0, 0, 0, 0, 166, 246, 35, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 150, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650755903, 0, 'npc_deragoth_hound'),
(@BEAMCHANNELER, 0, 0, 0, 0, 0, 19916, 0, 0, 0, 'beam channeler', '<memory of ice>', NULL, 0, 80, 80, 2, 16, 0, 1, 1.14286, 1, 1, 2, 2, 0, 24, 1, 2000, 0, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 1, 1, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 4, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650755903, 0, 'npc_memory_of_ice_OLDSM'),
(@KAMIKAZE, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'Kamikaze', NULL, NULL, 0, 80, 80, 2, 16, 0, 1, 1.14286, 1.1, 1, 2, 2, 0, 24, 1, 2000, 0, 1, 33554432, 2048, 0, 0, 0, 0, 0, 0, 1, 1, 0, 10, 1024, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 4, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 128, 'npc_kamikaze_OLDSM'),
(@ARROWMARKER, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'Arrow Marker', NULL, NULL, 0, 80, 80, 2, 35, 0, 1.2, 0.6, 1.1, 1, 2, 2, 0, 24, 1, 2000, 0, 1, 33554432, 2048, 0, 0, 0, 0, 0, 0, 1, 1, 0, 10, 1024, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 4, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 128, 'npc_arrow_marker_OLDSM'),
(@DARKNESSTARGET, 0, 0, 0, 0, 0, 11686, 0, 0, 0, "Madan\'tul Rada", '<darkness caster>', NULL, 0, 80, 80, 2, 16, 0, 0.6, 0.6, 1.1, 1, 2, 2, 0, 24, 1, 2000, 0, 1, 33554432, 2048, 0, 0, 0, 0, 0, 0, 1, 1, 0, 10, 1024, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 4, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 0, 'npc_darkness_caster_OLDSM');

DELETE FROM `creature_equip_template` WHERE `entry` = @MADANTHUL;
INSERT INTO `creature_equip_template` (`entry`, `id`, `itemEntry1`, `itemEntry2`, `itemEntry3`, `VerifiedBuild`) VALUES
(@MADANTHUL, 1, 17182, 0, 0, 0);

DELETE FROM `creature` WHERE `id` = @MADANTHUL;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@cGUID, @MADANTHUL, 44, 1, 1, 0, 0, 374.201, -101.18, 33.0511, 1.60589, 604800, 0, 0, 90643, 17032, 0, 0, 0, 0);

DELETE FROM `spell_script_names` WHERE `spell_id` IN (51787, 23278, 26659);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(51787, 'spell_mystical_bolt'),
(26659, 'aura_sam_test_aura_OLDSM'),
(23278, 'spell_shadow_scythe');

DELETE FROM `creature_text` WHERE `entry` = @MADANTHUL;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(@MADANTHUL, 0, 0, "I am Madantul Rada, the strongest warrior among risens. And who might you be?", 12, 0, 100, 1, 0, 0, 'Madantul Rada enter combat'),
(@MADANTHUL, 1, 0, "Come forth Overlords, Let's finish this.", 12, 0, 100, 1, 0, 0, 'Madantul Rada 1a faza 100 energy'),
(@MADANTHUL, 2, 0, "Have you seen my puppy? Oh there it is. It's feeding time Dera'tin'jeragoth", 12, 0, 100, 1, 0, 0, 'Madantul Rada skonczenie transition'),
(@MADANTHUL, 3, 0, "I haven't used this magic in years. Please survive for a little longer, let me enjoy this moment!", 12, 0, 100, 1, 0, 0, 'Madantul Rada 2a faza 100 energy'),
(@MADANTHUL, 4, 0, "Brr.. it's getting cold in here.", 12, 0, 100, 1, 0, 0, 'Madantul Rada 3a faza 100 energy'),
(@MADANTHUL, 5, 0, "The joy of killing! the joy of seeing killing done - this is what drives me!", 12, 0, 100, 1, 0, 0, 'Madantul Rada kill quote'),
(@MADANTHUL, 5, 1, "Killing is indeed a pleasure unmatched in this world. Perhaps it’s a pleasure we could share", 12, 0, 100, 1, 0, 0, 'Madantul Rada kill quote'),
(@MADANTHUL, 6, 0, "I have failed des..", 12, 0, 100, 1, 0, 0, 'Madantul rada death');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 13 AND `SourceEntry` = 56319;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13, 1, 56319, 0, 0, 31, 0, 3, 400043, 0, 1, 0, 0, '', ' Ball Lightning doesnt target Madanthul Rada');
