-- old npc's
DELETE FROM `creature` WHERE `creature`.`id` =80000;
DELETE FROM `creature` WHERE `creature`.`id` =80001;
DELETE FROM `creature` WHERE `creature`.`id` =80002;

DELETE FROM `creature_template` WHERE `creature_template`.`entry` = 80000;
DELETE FROM `creature_template` WHERE `creature_template`.`entry` = 80001;
DELETE FROM `creature_template` WHERE `creature_template`.`entry` = 80002;

DELETE FROM `gameobject` WHERE `gameobject`.`guid` = 165000;
DELETE FROM `gameobject` WHERE `gameobject`.`guid` = 165001;
DELETE FROM `gameobject` WHERE `gameobject`.`guid` = 165002;
DELETE FROM `gameobject` WHERE `gameobject`.`guid` = 165003;
DELETE FROM `gameobject` WHERE `gameobject`.`guid` = 165004;
DELETE FROM `gameobject` WHERE `gameobject`.`guid` = 165005;
DELETE FROM `gameobject` WHERE `gameobject`.`guid` = 165006;
DELETE FROM `gameobject` WHERE `gameobject`.`guid` = 165007;
DELETE FROM `gameobject` WHERE `gameobject`.`guid` = 165008;
DELETE FROM `gameobject` WHERE `gameobject`.`guid` = 165009;
DELETE FROM `gameobject` WHERE `gameobject`.`guid` = 165010;
DELETE FROM `gameobject` WHERE `gameobject`.`guid` = 165011;
DELETE FROM `gameobject` WHERE `gameobject`.`guid` = 165012;
DELETE FROM `gameobject` WHERE `gameobject`.`guid` = 165013;
DELETE FROM `gameobject` WHERE `gameobject`.`guid` = 165014;
DELETE FROM `gameobject` WHERE `gameobject`.`guid` = 165015;
DELETE FROM `gameobject` WHERE `gameobject`.`guid` = 165016;
DELETE FROM `gameobject` WHERE `gameobject`.`guid` = 165017;
DELETE FROM `gameobject` WHERE `gameobject`.`guid` = 165018;
DELETE FROM `gameobject` WHERE `gameobject`.`guid` = 165019;
DELETE FROM `gameobject` WHERE `gameobject`.`guid` = 165020;

INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `VerifiedBuild`) VALUES
(165000, 190816, 1, 1, 1, 1548.69, -4366.61, 0.747391, 0.962879, -0, -0, -0.463056, -0.886329, 300, 0, 1, 0),
(165001, 181379, 1, 1, 1, 1543.22, -4373.54, 0.655381, 5.86534, -0, -0, -0.207408, 0.978255, 300, 0, 1, 0),
(165002, 181379, 1, 1, 1, 1542.49, -4376.9, 0.663382, 0.210469, -0, -0, -0.105041, -0.994468, 300, 0, 1, 0),
(165003, 181379, 1, 1, 1, 1543.83, -4379.7, 0.856642, 0.636938, -0, -0, -0.313113, -0.949716, 300, 0, 1, 0),
(165004, 181379, 1, 1, 1, 1547.24, -4378.68, 1.25755, 6.20873, -0, -0, -0.0372199, 0.999307, 300, 0, 1, 0),
(165005, 181379, 1, 1, 1, 1548.14, -4375, 0.952243, 0.249717, -0, -0, -0.124534, -0.992215, 300, 0, 1, 0),
(165006, 193216, 1, 1, 1, 1547.69, -4365.48, 0.700518, 4.20184, -0, -0, -0.862746, 0.505638, 300, 0, 1, 0),
(165007, 180660, 1, 1, 1, 1563.29, -4356.94, 1.37167, 6.11506, -0, -0, -0.0839632, 0.996469, 300, 0, 1, 0),
(165008, 180660, 1, 1, 1, 1561.3, -4358, 1.1885, 4.92518, -0, -0, -0.628018, 0.778199, 300, 0, 1, 0),
(165009, 180660, 1, 1, 1, 1558.68, -4359.85, 0.970552, 3.22165, -0, -0, -0.999199, 0.0400171, 300, 0, 1, 0),
(165010, 180660, 1, 1, 1, 1560.14, -4359.06, 1.0913, 4.84585, -0, -0, -0.658382, 0.752684, 300, 0, 1, 0),
(165011, 190816, 0, 1, 1, -8817.35, 832.463, 98.8061, 4.50125, -0, -0, -0.77768, 0.628661, 300, 0, 1, 0),
(165012, 181379, 0, 1, 1, -8811.76, 841.024, 99.0113, 3.07802, -0, -0, -0.999495, -0.0317799, 300, 0, 1, 0),
(165013, 181379, 0, 1, 1, -8812.29, 846.747, 99.0311, 3.76212, -0, -0, -0.952253, 0.305309, 300, 0, 1, 0),
(165014, 181379, 0, 1, 1, -8815.21, 842.324, 98.7935, 3.12202, -0, -0, -0.999952, -0.009787, 300, 0, 1, 0),
(165015, 181379, 0, 1, 1, -8816.13, 845.668, 98.8504, 3.5158, -0, -0, -0.982547, 0.186013, 300, 0, 1, 0),
(165016, 180660, 0, 1, 1, -8831.53, 815.978, 98.6473, 1.38264, -0, -0, -0.637554, -0.770405, 300, 0, 1, 0),
(165017, 180660, 0, 1, 1, -8835.21, 820.861, 98.8159, 0.011336, -0, -0, -0.00566817, -0.999984, 300, 0, 1, 0),
(165018, 180660, 571, 1, 1, 5793.49, 660.787, 609.158, 6.21442, -0, -0, -0.0343772, 0.999409, 300, 0, 1, 0),
(165019, 180660, 571, 1, 1, 5792.46, 659.535, 609.158, 5.00176, -0, -0, -0.597766, 0.801671, 300, 0, 1, 0),
(165020, 181379, 0, 1, 1, -8811.52, 843.837, 99.0153, 3.02069, -0, -0, -0.952253, 0.305309, 300, 0, 1, 0);

DELETE FROM `creature` WHERE `creature`.`guid` = 250000;
DELETE FROM `creature` WHERE `creature`.`guid` = 250001;
DELETE FROM `creature` WHERE `creature`.`guid` = 250002;
DELETE FROM `creature` WHERE `creature`.`guid` = 250003;
DELETE FROM `creature` WHERE `creature`.`guid` = 250004;
DELETE FROM `creature` WHERE `creature`.`guid` = 250005;
DELETE FROM `creature` WHERE `creature`.`guid` = 250006;
DELETE FROM `creature` WHERE `creature`.`guid` = 250007;
DELETE FROM `creature` WHERE `creature`.`guid` = 250008;
DELETE FROM `creature` WHERE `creature`.`guid` = 250009;
DELETE FROM `creature` WHERE `creature`.`guid` = 250010;
DELETE FROM `creature` WHERE `creature`.`guid` = 250011;
DELETE FROM `creature` WHERE `creature`.`guid` = 250012;
DELETE FROM `creature` WHERE `creature`.`guid` = 250013;
DELETE FROM `creature` WHERE `creature`.`guid` = 250014;
DELETE FROM `creature` WHERE `creature`.`guid` = 250015;
DELETE FROM `creature` WHERE `creature`.`guid` = 250016;
DELETE FROM `creature` WHERE `creature`.`guid` = 250017;
DELETE FROM `creature` WHERE `creature`.`guid` = 250018;
DELETE FROM `creature` WHERE `creature`.`guid` = 250019;
DELETE FROM `creature` WHERE `creature`.`guid` = 250020;
DELETE FROM `creature` WHERE `creature`.`guid` = 250021;
DELETE FROM `creature` WHERE `creature`.`guid` = 250022;
DELETE FROM `creature` WHERE `creature`.`guid` = 250023;
DELETE FROM `creature` WHERE `creature`.`guid` = 250024;
DELETE FROM `creature` WHERE `creature`.`guid` = 250025;
DELETE FROM `creature` WHERE `creature`.`guid` = 250026;
DELETE FROM `creature` WHERE `creature`.`guid` = 250027;
DELETE FROM `creature` WHERE `creature`.`guid` = 250028;

-- Delete Some original guards 

DELETE FROM `creature` WHERE `creature`.`guid` = 7417;
DELETE FROM `creature` WHERE `creature`.`guid` = 8528;
DELETE FROM `creature` WHERE `creature`.`guid` = 1979097;
DELETE FROM `creature` WHERE `creature`.`guid` = 1979099;

INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(250000, 80012, 1, 1, 1, 0, 1, 1543.22, -4373.54, 0.655381, 5.86534, 300, 0, 0, 15953, 0, 0, 0, 0, 0),
(250001, 80013, 1, 1, 1, 0, 1, 1542.49, -4376.9, 0.663382, 0.210469, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(250002, 80014, 1, 1, 1, 0, 1, 1543.83, -4379.7, 0.856642, 0.636938, 300, 0, 0, 15953, 0, 0, 0, 0, 0),
(250003, 80011, 1, 1, 1, 0, 1, 1547.24, -4378.68, 1.25755, 6.20873, 300, 0, 0, 15953, 0, 0, 0, 0, 0),
(250004, 80010, 1, 1, 1, 0, 0, 1548.14, -4375, 0.952243, 0.249717, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(250005, 3296, 1, 1, 1, 0, 1, 1546.18, -4365.09, 3.03034, 5.69881, 300, 0, 0, 21270, 0, 2, 0, 0, 0),
(250006, 80015, 1, 1, 1, 0, 1, 1549.99, -4367.34, 3.03034, 5.75692, 300, 0, 0, 21270, 0, 0, 0, 0, 0),
(250007, 80017, 1, 1, 1, 0, 1, 1560.55, -4360.38, 1.18713, 5.58491, 300, 0, 0, 21270, 0, 0, 0, 0, 0),
(250008, 80016, 1, 1, 1, 0, 1, 1559.44, -4363, 1.24274, 5.99176, 300, 0, 0, 951, 0, 0, 0, 0, 0),
(250009, 80016, 1, 1, 1, 0, 1, 1562.25, -4359.04, 1.33629, 5.2904, 300, 0, 0, 1003, 0, 0, 0, 0, 0),
(250010, 80023, 0, 1, 1, 0, 1, -8819.01, 832.668, 101.088, 3.02313, 300, 0, 0, 15953, 0, 0, 0, 0, 0),
(250011, 68, 0, 1, 1, 0, 1, -8818.14, 829.847, 101.088, 5.62508, 300, 0, 0, 15953, 0, 2, 0, 0, 0),
(250012, 80020, 0, 1, 1, 0, 1, -8811.76, 841.024, 99.0113, 3.07802, 300, 0, 0, 15953, 0, 0, 0, 0, 0),
(250013, 80021, 0, 1, 1, 0, 1, -8811.52, 843.837, 99.0153, 3.02069, 300, 0, 0, 15953, 0, 0, 0, 0, 0),
(250014, 80022, 0, 1, 1, 0, 1, -8812.29, 846.747, 99.0311, 3.76212, 300, 0, 0, 405, 1202, 0, 0, 0, 0),
(250015, 80018, 0, 1, 1, 0, 0, -8815.21, 842.324, 98.7935, 3.12202, 300, 0, 0, 15953, 0, 0, 0, 0, 0),
(250016, 80019, 0, 1, 1, 0, 1, -8816.13, 845.668, 98.8504, 3.5158, 300, 0, 0, 1398, 0, 0, 0, 0, 0),
(250017, 80025, 0, 1, 1, 0, 1, -8833.1, 818.478, 98.7035, 0.869779, 300, 0, 0, 15953, 0, 0, 0, 0, 0),
(250018, 80024, 0, 1, 1, 0, 1, -8834.92, 819.435, 98.7438, 0.557968, 300, 0, 0, 1003, 0, 0, 0, 0, 0),
(250019, 80024, 0, 1, 1, 0, 1, -8833.02, 816.531, 98.615, 0.733903, 300, 0, 0, 951, 0, 0, 0, 0, 0),
(250020, 80026, 571, 1, 1, 0, 0, 5791.109863, 661.011719, 610.476013, 6.179554, 6300, 0, 0, 0, 0, 0, 0, 0, 0),
(250021, 80028, 0, 1, 1, 0, 0, -8926.624023, -142.887482, 81.648903, 2.054602, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(250022, 80028, 0, 1, 1, 0, 0, -6212.995117, 329.762573, 383.787018, 3.141596, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(250023, 80028, 1, 1, 1, 0, 0, 10326.232422, 821.765564, 1326.427002, 2.134544, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(250024, 80028, 530, 1, 1, 0, 0, -3962.321045 , -13935.514648, 100.472412 , 1.584915, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(250025, 80027, 1, 1, 1, 0, 0, -638.452393, -4241.515625, 38.134140, 6.224284, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(250026, 80027, 0, 1, 1, 0, 0, 1656.823120, 1673.707031, 120.718857, 0.046686, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(250027, 80027, 1, 1, 1, 0, 0, -2912.982666, -253.127716, 52.940941, 3.487168, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(250028, 80027, 530, 1, 1, 0, 0, 10352.305664, -6362.232910, 34.534962, 3.116935, 0, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM `creature_addon` WHERE `creature_addon`.`guid` = 250005;
DELETE FROM `creature_addon` WHERE `creature_addon`.`guid` = 250011;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(250005, 250005, 0, 0, 0, 0, NULL),
(250011, 250011, 0, 0, 0, 0, NULL);

DELETE FROM `waypoint_data` WHERE `waypoint_data`.`id` = 250005;
DELETE FROM `waypoint_data` WHERE `waypoint_data`.`id` = 250011;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `delay`, `move_type`, `action`, `action_chance`, `wpguid`) VALUES
(250005, 1, 1545.8, -4361.37, 3.02987, 0, 0, 0, 0, 100, 0),
(250005, 2, 1550.23, -4365, 3.02987, 0, 0, 0, 0, 100, 0),
(250005, 3, 1547.34, -4369.64, 3.02987, 0, 0, 0, 0, 100, 0),
(250005, 4, 1542.84, -4366.54, 3.02987, 0, 0, 0, 0, 100, 0),
(250011, 1, -8813.58, 828.195, 101.089, 0, 0, 0, 0, 100, 0),
(250011, 2, -8811.88, 834.555, 101.089, 0, 0, 0, 0, 100, 0),
(250011, 3, -8817.49, 835.633, 101.089, 0, 0, 0, 0, 100, 0),
(250011, 4, -8817.89, 829.95, 101.089, 0, 0, 0, 0, 100, 0);

DELETE FROM `creature_template` WHERE `creature_template`.`entry` = 80010;
DELETE FROM `creature_template` WHERE `creature_template`.`entry` = 80011;
DELETE FROM `creature_template` WHERE `creature_template`.`entry` = 80012;
DELETE FROM `creature_template` WHERE `creature_template`.`entry` = 80013;
DELETE FROM `creature_template` WHERE `creature_template`.`entry` = 80014;
DELETE FROM `creature_template` WHERE `creature_template`.`entry` = 80015;
DELETE FROM `creature_template` WHERE `creature_template`.`entry` = 80016;
DELETE FROM `creature_template` WHERE `creature_template`.`entry` = 80017;
DELETE FROM `creature_template` WHERE `creature_template`.`entry` = 80018;
DELETE FROM `creature_template` WHERE `creature_template`.`entry` = 80019;
DELETE FROM `creature_template` WHERE `creature_template`.`entry` = 80020;
DELETE FROM `creature_template` WHERE `creature_template`.`entry` = 80021;
DELETE FROM `creature_template` WHERE `creature_template`.`entry` = 80022;
DELETE FROM `creature_template` WHERE `creature_template`.`entry` = 80023;
DELETE FROM `creature_template` WHERE `creature_template`.`entry` = 80024;
DELETE FROM `creature_template` WHERE `creature_template`.`entry` = 80025;
DELETE FROM `creature_template` WHERE `creature_template`.`entry` = 80026;
DELETE FROM `creature_template` WHERE `creature_template`.`entry` = 80027;
DELETE FROM `creature_template` WHERE `creature_template`.`entry` = 80028;

INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(80010, 0, 0, 0, 0, 0, 2581, 0, 0, 0, 'Alliance Slave', '', '', 0, 1, 1, 0, 1078, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, '', 12340),
(80011, 0, 0, 0, 0, 0, 3524, 3525, 3526, 3527, 'Alliance Slave', '', '', 0, 1, 1, 0, 1078, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, '', 12340),
(80012, 0, 0, 0, 0, 0, 3167, 5446, 0, 0, 'Alliance Slave', '', '', 0, 1, 1, 0, 1078, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, '', 12340),
(80013, 0, 0, 0, 0, 0, 19171, 19172, 0, 0, 'Alliance Slave', '', '', 0, 1, 1, 0, 1078, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, '', 12340),
(80014, 0, 0, 0, 0, 0, 2306, 14613, 14614, 14615, 'Alliance Slave', '', '', 0, 1, 1, 0, 1078, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, '', 12340),
(80015, 0, 0, 0, 0, 0, 14429, 0, 0, 0, 'Valak The Slave Trader', 'Slave Market', NULL, 0, 80, 80, 0, 29, 3, 1, 1.14286, 1, 1, 29, 39, 0, 80, 1, 1500, 2000, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 20, 30, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 3, 1, 1000, 1, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 'npc_slave', 12340),
(80016, 0, 0, 0, 0, 0, 415, 0, 0, 0, 'Bazaar Guard', '', NULL, 0, 83, 83, 0, 29, 0, 1.2, 1.14286, 1, 0, 2, 2, 0, 24, 1, 2000, 2000, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 1, 1, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1.05, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 12340),
(80017, 0, 0, 0, 0, 0, 7108, 0, 0, 0, 'Kenno Goldbringer', 'The Bazaar Trader', NULL, 0, 80, 80, 0, 29, 3, 1, 1.14286, 1, 1, 29, 39, 0, 80, 1, 1500, 2000, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 20, 30, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 500, 1, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 'npc_bazaar', 12340),
(80018, 0, 0, 0, 0, 0, 15511, 0, 0, 0, 'Horde Slave', '', '', 0, 1, 1, 0, 29, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, '', 12340),
(80019, 0, 0, 0, 0, 0, 4083, 4084, 0, 0, 'Horde Slave', '', '', 0, 1, 1, 0, 29, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, '', 12340),
(80020, 0, 0, 0, 0, 0, 4259, 4260, 4601, 4602, 'Horde Slave', '', '', 0, 1, 1, 0, 29, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, '', 12340),
(80021, 0, 0, 0, 0, 0, 2141, 8572, 9391, 9392, 'Horde Slave', '', '', 0, 1, 1, 0, 29, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, '', 12340),
(80022, 0, 0, 0, 0, 0, 4123, 0, 0, 0, 'Horde Slave', '', '', 0, 1, 1, 0, 29, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, '', 12340),
(80023, 0, 0, 0, 0, 0, 5567, 0, 0, 0, 'Zork The Slave Trader', 'Slave Market', NULL, 0, 80, 80, 0, 11, 3, 1, 1.14286, 1, 1, 29, 39, 0, 80, 1, 1500, 2000, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 20, 30, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 3, 1, 1000, 1, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 'npc_slave', 12340),
(80024, 0, 0, 0, 0, 0, 415, 0, 0, 0, 'Bazaar Guard', '', NULL, 0, 83, 83, 0, 11, 0, 1.2, 1.14286, 1, 0, 2, 2, 0, 24, 1, 2000, 2000, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 1, 1, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1.05, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 12340),
(80025, 0, 0, 0, 0, 0, 7108, 0, 0, 0, 'Zenno Goldbringer', 'The Bazaar Trader', NULL, 0, 80, 80, 0, 11, 3, 1, 1.14286, 1, 1, 29, 39, 0, 80, 1, 1500, 2000, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 20, 30, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 500, 1, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 'npc_bazaar', 12340),
(80026, 0, 0, 0, 0, 0, 7108, 0, 0, 0, 'Senno Goldbringer', 'The Bazaar Trader', NULL, 0, 80, 80, 0, 35, 3, 1, 1.14286, 1, 1, 29, 39, 0, 80, 1, 1500, 2000, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 20, 30, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 500, 1, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 'npc_bazaar', 12340),
(80027, 0, 0, 0, 0, 0, 7107, 0, 0, 0, 'Valak Assistant', 'Slave Market', NULL, 0, 80, 80, 0, 29, 3, 1, 1.14286, 1, 1, 29, 39, 0, 80, 1, 1500, 2000, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 20, 30, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 200, 1, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 'npc_slave', 12340),
(80028, 0, 0, 0, 0, 0, 7107, 0, 0, 0, 'Zork Assistant', 'Slave Market', NULL, 0, 80, 80, 0, 11, 3, 1, 1.14286, 1, 1, 29, 39, 0, 80, 1, 1500, 2000, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 20, 30, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 200, 1, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 'npc_slave', 12340);

DELETE FROM `smart_scripts` WHERE `smart_scripts`.`entryorguid` = 80015;
DELETE FROM `smart_scripts` WHERE `smart_scripts`.`entryorguid` = 80023;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(80015, 0, 0, 0, 60, 0, 100, 0, 1000, 15000, 120000, 180000, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On Update - Yell'),
(80023, 0, 0, 0, 60, 0, 100, 0, 1000, 15000, 120000, 180000, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'On Update - Yell');

DELETE FROM `creature_text` WHERE `creature_text`.`entry` = 80015;
DELETE FROM `creature_text` WHERE `creature_text`.`entry` = 80023;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `TextRange`, `comment`) VALUES
(80015, 0, 0, 'Freedom? They don\'t deserve...!', 14, 0, 100, 0, 0, 0, 0, 'Valak The Slave Trader'),
(80015, 0, 1, 'Buy those weak creatures, they are perfect tools!', 14, 0, 100, 0, 0, 0, 0, 'Valak The Slave Trader'),
(80015, 0, 2, 'Gul\'dan would know what to do with them...', 14, 0, 100, 0, 0, 0, 0, 'Valak The Slave Trader'),
(80023, 0, 0, 'Buy them, or we\'ll kill them.', 14, 0, 100, 0, 0, 0, 0, 'Zork The Slave Trader'),
(80023, 0, 1, 'Horde slaves, what could be worse?', 14, 0, 100, 0, 0, 0, 0, 'Zork The Slave Trader'),
(80023, 0, 2, 'Proud residents of Stormwind! We are owners of those animals!', 14, 0, 100, 0, 0, 0, 0, 'Zork The Slave Trader');