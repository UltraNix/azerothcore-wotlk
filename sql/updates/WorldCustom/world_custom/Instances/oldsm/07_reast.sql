SET @REAST := 400040;
SET @REAST2 := 400041;
SET @ORB := 400042;

SET @REASTGUID := 400001;

DELETE FROM `creature_template` WHERE `entry` IN (@REAST, @REAST2, @ORB);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@REAST, 0, 0, 0, 0, 0, 18998, 0, 0, 0, 'Reast', '<The Risen>', NULL, 0, 83, 83, 2, 16, 0, 1.4, 1.8, 0.5, 3, 250, 350, 0, 300, 115, 1500, 0, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 260, 387, 37, 6, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1300, 300, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 257, 'boss_reast', 0),
(@REAST2, 0, 0, 0, 0, 0, 23428, 0, 0, 0, 'Reast', '<The Risen>', NULL, 0, 83, 83, 2, 16, 0, 1.4, 1.8, 0.35, 3, 250, 350, 0, 300, 150, 1200, 0, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 260, 387, 37, 6, 4, 100007, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2000000, 2500000, '', 0, 1, 1, 800, 300, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 257, '', 0),
(@ORB, 0, 0, 0, 0, 0, 26753, 0, 0, 0, 'Orb', NULL, NULL, 0, 83, 83, 2, 35, 0, 1, 1, 0.7, 1, 250, 350, 0, 0, 1, 2000, 0, 1, 33554946, 2048, 0, 0, 0, 0, 0, 0, 260, 387, 37, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 4, 1, 8, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 256, 'npc_reast_orb', 0);

DELETE FROM `creature` WHERE `id` = @REAST;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@REASTGUID, @REAST, 44, 1, 1, 0, 1, 188.838, 25.807, 30.839, 0.000, 604800, 0, 0, 1, 1, 0, 0, 0, 0);
