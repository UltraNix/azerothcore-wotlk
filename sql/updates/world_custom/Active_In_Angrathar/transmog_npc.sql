DELETE FROM `creature_template` WHERE `entry` = 80003;
INSERT INTO `creature_template` VALUES
(80003, 0, 0, 0, 0, 0, 1489, 0, 0, 0, "La'ganog", 'Transmogrification Tokens', '', 0, 81, 81, 2, 35, 128, 1, 1.14286, 1, 0, 289, 421, 0, 175, 1, 2000, 2000, 8, 33536, 2048, 0, 0, 0, 0, 0, 0, 271, 403, 45, 7, 4096, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, '', 12340);

DELETE FROM `npc_vendor` WHERE `entry` = 80003;
INSERT INTO `npc_vendor` VALUES
(80003, 0, 37711, 0, 0, 2604), 
(80003, 0, 37711, 0, 0, 2570),
(80003, 0, 37742, 0, 0, 2607),
(80003, 0, 37742, 0, 0, 2431);

UPDATE `item_template` SET `name` = "Armor Transmog Token" WHERE `entry` = 37711;
DELETE FROM `creature_template` WHERE `entry` = 190010;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(190010, 0, 0, 0, 0, 0, 19646, 0, 0, 0, 'Avrenim', 'Transmogrification', NULL, 0, 80, 80, 2, 35, 1, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 138936390, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 'npc_transmogrifier', 1);

DELETE FROM `creature` WHERE `guid` IN (249558, 249559,249560, 249561, 249562, 249563);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(249558, 190010, 571, 1, 1, 0, 0, 5850.49, 690.44, 610.71, 3.90, 300, 5, 0, 11770, 0, 0, 0, 0, 0),
(249559, 80003, 571, 1, 1, 0, 0, 5848.54, 692.06, 610.71, 3.90, 300, 5, 0, 11770, 0, 0, 0, 0, 0),
(249560, 190010, 0, 1, 1, 0, 0, -8820.12, 651.40, 94.90, 5.25, 300, 5, 0, 11770, 0, 0, 0, 0, 0),
(249561, 80003, 0, 1, 1, 0, 0, -8822.83, 650.55, 94.90, 4.95, 300, 5, 0, 11770, 0, 0, 0, 0, 0),
(249562, 190010, 1, 1, 1, 0, 0, 1654.96, -4433.03, 17.53, 1.85, 300, 5, 0, 11770, 0, 0, 0, 0, 0),
(249563, 80003, 1, 1, 1, 0, 0, 1652.07, -4433.84, 17.53, 1.85, 300, 5, 0, 11770, 0, 0, 0, 0, 0);