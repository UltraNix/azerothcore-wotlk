-- ToDo: equip dla healera i castera, loot
-- Risen Dark Stalker
SET @ROGUE := 400050;
SET @TANK := 400051;
SET @HEAL := 400052;
SET @CASTER := 400053;
SET @CONSTRUCT := 400054;

SET @GUID := 400021; -- 41 guidow

-- -------------------------------- rogue
DELETE FROM `creature_template` WHERE `entry` = @ROGUE;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@ROGUE, 0, 0, 0, 0, 0, 4135, 4136, 0, 0, 'Dark Risen Stalker', '<The Risen>', NULL, 0, 82, 82, 0, 16, 0, 1.05, 1.8286, 1, 1, 300, 500, 0, 100, 100, 500, 0, 1, 32768, 2048, 0, 0, 0, 0, 0, 0, 28, 41, 8, 6, 0, 37023, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10000, 20000, '', 1, 3, 1, 100, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 608935551, 0, 'npc_dark_risen_stalker', 0);


DELETE FROM `creature_template_addon` WHERE `entry` = @ROGUE;
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(@ROGUE, 0, 0, 0, 4097, 0, '');

DELETE FROM `creature_equip_template` WHERE `entry` = @ROGUE;
INSERT INTO `creature_equip_template` (`entry`, `id`, `itemEntry1`, `itemEntry2`, `itemEntry3`, `VerifiedBuild`) VALUES
(@ROGUE, 1, 2147, 2147, 6886, 0);

-- -------------------------------- tank
DELETE FROM `creature_template` WHERE `entry` = @TANK;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@TANK, 0, 0, 0, 0, 0, 30617, 0, 0, 0, 'Dark Risen Commander', '<The Risen>', NULL, 0, 82, 82, 0, 16, 0, 1.05, 1.14286, 0.6, 1, 200, 500, 0, 100, 100, 2000, 0, 1, 32768, 2048, 0, 0, 0, 0, 0, 0, 28, 41, 8, 6, 0, 37023, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10000, 20000, '', 1, 3, 1, 100, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 608932475, 0, 'npc_trash_tank_OLDSM', 0);


DELETE FROM `creature_equip_template` WHERE `entry` = @TANK;
INSERT INTO `creature_equip_template` (`entry`, `id`, `itemEntry1`, `itemEntry2`, `itemEntry3`, `VerifiedBuild`) VALUES
(@TANK, 1, 29924, 51533, 0, 0);

-- -------------------------------- healer
DELETE FROM `creature_template` WHERE `entry` = @HEAL;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
 (@HEAL, 0, 0, 0, 0, 0, 18824, 0, 0, 0, 'Dark Risen Zealot', '<The Risen>', NULL, 0, 82, 82, 0, 16, 0, 1.05, 1.14286, 0.9, 1, 300, 500, 0, 100, 50, 2000, 0, 1, 32768, 2048, 0, 0, 0, 0, 0, 0, 28, 41, 8, 6, 0, 37023, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10000, 20000, '', 1, 3, 1, 100, 40, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 608932475, 0, 'npc_trash_healer_OLDSM', 0);


-- -------------------------------- caster dps
DELETE FROM `creature_template` WHERE `entry` = @CASTER;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@CASTER, 0, 0, 0, 0, 0, 26919, 27705, 27706, 27707, 'Dark Risen Adherent', '<The Risen>', NULL, 0, 82, 82, 0, 16, 0, 1.05, 1.14286, 0.6, 1, 300, 500, 0, 100, 50, 2000, 0, 2, 32768, 2048, 0, 0, 0, 0, 0, 0, 28, 41, 8, 6, 0, 37023, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10000, 20000, '', 1, 3, 1, 100, 40, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 608932475, 0, 'npc_trash_caster_OLDSM', 0);


-- aoe reflect
DELETE FROM `spell_script_names` WHERE `spell_id` = 20619;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(20619, 'spell_aoe_reflect_OLDSM');

-- -------------------------------- Risen Construct
DELETE FROM `creature_template` WHERE `entry` = @CONSTRUCT;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@CONSTRUCT, 0, 0, 0, 0, 0, 17205, 0, 0, 0, 'Risen Construct', '<The Risen>', NULL, 0, 82, 82, 2, 16, 0, 1.05, 1.3286, 0.4, 1, 300, 500, 0, 100, 120, 2000, 0, 1, 32768, 2048, 0, 0, 0, 0, 0, 0, 28, 41, 8, 9, 0, 37023, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 50000, 80000, '', 1, 3, 1, 500, 40, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 653000575, 0, 'npc_risen_construct', 0);


-- --------------------------------

-- dwa rogale na start
DELETE FROM `creature` WHERE `id` IN (@ROGUE, @TANK, @HEAL, @CASTER, @CONSTRUCT);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@GUID, @ROGUE, 44, 1, 1, 0, 1, 66.9502, 6.94791, 18.6773, 1.66915, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+1, @ROGUE, 44, 1, 1, 0, 1, 66.7755, -8.88809, 18.6773, 4.75589, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),

-- 1e formation(glowny pokoj po wejsciu)
(@GUID+2, @TANK, 44, 1, 1, 0, 1, 129.028, -14.2825, 18.6773, 3.08837, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+3, @TANK, 44, 1, 1, 0, 1, 128.775, -10.1971, 18.6773, 3.14728, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+4, @HEAL, 44, 1, 1, 0, 0, 132.906, -10.1739, 18.6773, 3.14728, 604800, 0, 0, 564700, 0, 2, 0, 0, 0),
(@GUID+5, @HEAL, 44, 1, 1, 0, 0, 132.928, -14.1428, 18.6773, 3.14728, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+6, @CASTER, 44, 1, 1, 0, 0, 135.858, -14.1262, 18.6773, 3.14728, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+7, @CASTER, 44, 1, 1, 0, 0, 135.834, -10.0312, 18.6773, 3.14728, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),

-- 1e formation w tunelu do mazina
(@GUID+8, @HEAL, 44, 1, 1, 0, 0, 146.557, -18.5877, 18.007, 1.50645, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+9, @HEAL, 44, 1, 1, 0, 0, 150.762, -18.8587, 18.007, 1.50645, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+10, @TANK, 44, 1, 1, 0, 1, 153.612, -14.6963, 18.007, 1.50645, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+11, @HEAL, 44, 1, 1, 0, 0, 155.086, -19.1373, 18.007, 1.50645, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+12, @TANK, 44, 1, 1, 0, 1, 148.934, -14.623, 18.007, 1.45409, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+13, @CASTER, 44, 1, 1, 0, 0, 153.03, -20.7845, 18.007, 1.5719, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+14, @CASTER, 44, 1, 1, 0, 0, 148.585, -20.7894, 18.007, 1.5719, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),

-- 2ie formation w tunelu do mazina
(@GUID+15, @TANK, 44, 1, 1, 0, 1, 151.683, -50.1562, 18.007, 1.60043, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+16, @CASTER, 44, 1, 1, 0, 0, 148.83, -52.6493, 18.007, 1.60043, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+17, @HEAL, 44, 1, 1, 0, 0, 155.738, -52.7462, 18.007, 1.60043, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),

-- tunel do javiera (2 rogale)
(@GUID+18, @ROGUE, 44, 1, 1, 0, 1, 228.474, -108.981, 18.007, 1.59965, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+19, @ROGUE, 44, 1, 1, 0, 1, 222.621, -108.799, 18.007, 1.59965, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),

-- tunel do javiera(3 tanki 2 healerow)
(@GUID+20, @HEAL, 44, 1, 1, 0, 0, 227.364, -81.868, 18.007, 3.15971, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+21, @TANK, 44, 1, 1, 0, 1, 223.15, -83.3745, 18.007, 3.22188, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+22, @HEAL, 44, 1, 1, 0, 0, 226.878, -85.3412, 18.007, 3.00263, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+23, @TANK, 44, 1, 1, 0, 1, 222.889, -80.1231, 18.007, 3.22188, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+24, @TANK, 44, 1, 1, 0, 1, 222.24, -86.4549, 18.007, 3.17607, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),

-- tunel za javierem(2 tankow,2 castero,healer)
(@GUID+25, @TANK, 44, 1, 1, 0, 1, 297.201, -85.8907, 30.8232, 4.76977, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+26, @TANK, 44, 1, 1, 0, 1, 301.988, -85.6157, 30.8232, 4.76977, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+27, @CASTER, 44, 1, 1, 0, 0, 304.15, -83.1628, 30.8232, 4.7436, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+28, @HEAL, 44, 1, 1, 0, 0, 299.076, -83.3892, 30.8232, 4.73051, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+29, @CASTER, 44, 1, 1, 0, 0, 294.914, -83.4511, 30.8232, 4.7436, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),

-- w pokoju mini bossa
(@GUID+30, @CASTER, 44, 1, 1, 0, 0, 255.513, -52.257, 31.4935, 0.0403752, 604800, 0, 0, 564700, 0, 2, 0, 0, 0),
(@GUID+31, @TANK, 44, 1, 1, 0, 1, 260.744, -55.2052, 31.4935, 0.0992801, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+32, @TANK, 44, 1, 1, 0, 1, 260.621, -52.1627, 31.4935, 0.0403752, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+33, @HEAL, 44, 1, 1, 0, 0, 257.995, -52.2688, 31.4935, 0.0403752, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+34, @HEAL, 44, 1, 1, 0, 0, 258.113, -55.1924, 31.4935, 0.0403752, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+35, @CASTER, 44, 1, 1, 0, 0, 255.635, -55.2925, 31.4935, 0.0403752, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),

-- za pokojem mini bossa,przed muru
(@GUID+36, @ROGUE, 44, 1, 1, 0, 1, 233.257, -21.1296, 30.8232, 4.75238, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+37, @ROGUE, 44, 1, 1, 0, 1, 227.426, -21.5465, 30.8232, 4.76874, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+38, @ROGUE, 44, 1, 1, 0, 1, 227.743, 2.45774, 30.8232, 4.65996, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+39, @ROGUE, 44, 1, 1, 0, 1, 232.645, 2.23269, 30.8232, 4.66651, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+40, @ROGUE, 44, 1, 1, 0, 1, 232.441, 34.2391, 30.8232, 4.66428, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),
(@GUID+41, @ROGUE, 44, 1, 1, 0, 1, 227.678, 34.3874, 30.8232, 4.60211, 604800, 0, 0, 564700, 0, 0, 0, 0, 0),

(@GUID+42, @CONSTRUCT, 44, 1, 1, 0, 0, 342.646, -9.550, 30.8255, 0.000, 604800, 0, 0, 0, 0, 2, 0, 0, 0),
(@GUID+43, @CONSTRUCT, 44, 1, 1, 0, 0, 321.690, -53.064, 30.8282, 1.570, 604800, 0, 0, 0, 0, 2, 0, 0, 0);
-- ------------

DELETE FROM `creature_formations` WHERE `leaderGUID` BETWEEN @GUID AND @GUID+41 OR `memberGUID` BETWEEN @GUID AND @GUID+41;
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(@GUID+4, @GUID+2, 5, 30, 2, 0, 0),
(@GUID+4, @GUID+3, 5, 90, 2, 0, 0),
(@GUID+4, @GUID+4, 0, 0, 2, 0, 0),
(@GUID+4, @GUID+5, 5, 330, 2, 0, 0),
(@GUID+4, @GUID+6, 5, 150, 2, 0, 0),
(@GUID+4, @GUID+7, 5, 210, 2, 0, 0),

(@GUID+8, @GUID+8, 0, 0, 2, 0, 0),
(@GUID+8, @GUID+9, 0, 0, 2, 0, 0),
(@GUID+8, @GUID+10, 0, 0, 2, 0, 0),
(@GUID+8, @GUID+11, 0, 0, 2, 0, 0),
(@GUID+8, @GUID+12, 0, 0, 2, 0, 0),
(@GUID+8, @GUID+13, 0, 0, 2, 0, 0),
(@GUID+8, @GUID+14, 0, 0, 2, 0, 0),

(@GUID+15, @GUID+15, 0, 0, 2, 0, 0),
(@GUID+15, @GUID+16, 0, 0, 2, 0, 0),
(@GUID+15, @GUID+17, 0, 0, 2, 0, 0),

(@GUID+20, @GUID+20, 0, 0, 2, 0, 0),
(@GUID+20, @GUID+21, 0, 0, 2, 0, 0),
(@GUID+20, @GUID+22, 0, 0, 2, 0, 0),
(@GUID+20, @GUID+23, 0, 0, 2, 0, 0),
(@GUID+20, @GUID+24, 0, 0, 2, 0, 0),

(@GUID+25, @GUID+25, 0, 0, 2, 0, 0),
(@GUID+25, @GUID+26, 0, 0, 2, 0, 0),
(@GUID+25, @GUID+27, 0, 0, 2, 0, 0),
(@GUID+25, @GUID+28, 0, 0, 2, 0, 0),
(@GUID+25, @GUID+29, 0, 0, 2, 0, 0),

(@GUID+30, @GUID+30, 0, 0, 2, 0, 0),
(@GUID+30, @GUID+31, 5, 240, 2, 0, 0),
(@GUID+30, @GUID+32, 5, 300, 2, 0, 0),
(@GUID+30, @GUID+33, 5, 60, 2, 0, 0),
(@GUID+30, @GUID+34, 5, 180, 2, 0, 0),
(@GUID+30, @GUID+35, 5, 120, 2, 0, 0);

DELETE FROM `waypoint_data` WHERE `id` IN ((@GUID+4)*10, (@GUID+30)*10, (@GUID+42)*10, (@GUID+43)*10);
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `delay`, `move_type`, `action`, `action_chance`, `wpguid`) VALUES
((@GUID+4)*10, 1, 128.548, -12.532, 18.677, 0, 0, 0, 0, 100, 0),
((@GUID+4)*10, 2, 104.880, -12.532, 18.677, 0, 0, 0, 0, 100, 0),
((@GUID+4)*10, 3, 104.880, 10.362, 18.677, 0, 0, 0, 0, 100, 0),
((@GUID+4)*10, 4, 128.548, 10.362, 18.677, 0, 0, 0, 0, 100, 0),

((@GUID+30)*10, 1, 276.074, -53.979, 31.493, 0, 0, 0, 0, 100, 0),
((@GUID+30)*10, 2, 275.293, -33.592, 31.493, 0, 0, 0, 0, 100, 0),
((@GUID+30)*10, 3, 254.253, -28.4262, 31.493, 0, 0, 0, 0, 100, 0),
((@GUID+30)*10, 4, 254.163, -53.017, 31.493, 0, 0, 0, 0, 100, 0),

((@GUID+42)*10, 1, 342.646, -9.550, 30.8255, 0, 0, 0, 0, 100, 0),
((@GUID+42)*10, 2, 381.212, -10.111, 30.8255, 0, 0, 0, 0, 100, 0),

((@GUID+43)*10, 1, 321.690, -53.064, 30.826, 0, 0, 0, 0, 100, 0),
((@GUID+43)*10, 2, 322.208, -9.2356, 30.828, 0, 0, 0, 0, 100, 0);

DELETE FROM `creature_addon` WHERE `guid` IN (@GUID+4, @GUID+30, @GUID+42, @GUID+43);
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(@GUID+4, (@GUID+4)*10, 0, 0, 4097, 0, NULL),
(@GUID+30, (@GUID+30)*10, 0, 0, 4097, 0, NULL),
(@GUID+42, (@GUID+42)*10, 0, 0, 4097, 0, NULL),
(@GUID+43, (@GUID+43)*10, 0, 0, 4097, 0, NULL);
