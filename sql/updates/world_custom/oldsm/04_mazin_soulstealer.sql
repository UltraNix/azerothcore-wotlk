SET @DEATHORB:= 400020;
SET @MAZIN := 400022;
SET @THRALL := 400023;
SET @SYLVANAS := 400024;
SET @KELTHUZAD := 400025;
SET @AIRELEMENTAL := 400026;
SET @EARTHELEMENTAL := 400027;
SET @FIREELEMENTAL := 400028;
SET @SYLVAGENT := 400029;
SET @KELTHUZADAGENT := 400030;
SET @RAGINGSKELETON := 400031;
SET @PURPLEORB := 400032;

SET @cGUID:= 400020;

DELETE FROM `creature_template` WHERE `entry` IN (@DEATHORB, @MAZIN, @THRALL, @SYLVANAS, @KELTHUZAD, @AIRELEMENTAL, @EARTHELEMENTAL, @FIREELEMENTAL, @SYLVAGENT, @KELTHUZADAGENT, @RAGINGSKELETON, @PURPLEORB);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(@DEATHORB, 0, 0, 0, 0, 0, 25144, 0, 0, 0, 'Death Orb', NULL, NULL, 0, 80, 80, 1, 16, 0, 1.125, 1.14286, 1, 1, 2, 2, 0, 24, 1, 2000, 0, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 1, 1, 100, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 4, 1, 25, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 0, 'npc_death_orb_OLDSM'),
(@MAZIN, 0, 0, 0, 0, 0, 28220, 0, 0, 0, 'Mazin Soulstealer', '<The Risen>', NULL, 0, 83, 83, 2, 16, 0, 0.7, 1.14286, 1.2, 3, 3, 2, 0, 24, 95.8, 2000, 0, 2, 768, 2048, 0, 0, 0, 0, 0, 0, 1, 2, 0, 6, 4, 100007, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2000000, 2500000, '', 0, 3, 1, 1500, 35, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 1, 'boss_mazin_soulstealer'),
(@THRALL, 0, 0, 0, 0, 0, 27656, 0, 0, 0, 'Thrall', '<The Risen>', NULL, 0, 83, 83, 2, 16, 2, 1, 1.14286, 1.5, 3, 2, 2, 0, 24, 95.8, 2000, 0, 2, 768, 2048, 0, 0, 0, 0, 0, 0, 1, 2, 0, 7, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 144, 15, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 0, 'npc_thrall_OLDSM'),
(@SYLVANAS, 0, 0, 0, 0, 0, 28213, 0, 0, 0, 'Lady Sylvanas Windrunner', '<The Risen>', NULL, 0, 83, 83, 2, 16, 0, 1, 1.14286, 1, 3, 0, 0, 0, 0, 1, 1000, 1000, 1, 768, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 145, 20, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 0, 'npc_sylvanas_OLDSM'),
(@KELTHUZAD, 0, 0, 0, 0, 0, 24787, 0, 0, 0, "Kel\'Thuzad", '<The Risen>', NULL, 0, 83, 83, 2, 16, 0, 1, 1.14286, 1, 3, 509, 683, 0, 805, 35, 2000, 0, 8, 768, 2048, 0, 0, 0, 0, 0, 0, 371, 535, 135, 6, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 4, 1, 180, 50, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 0, 'npc_kel_thuzad_OLDSM'),
(@AIRELEMENTAL, 0, 0, 0, 0, 0, 13490, 0, 0, 0, 'Air Elemental', NULL, NULL, 0, 81, 81, 2, 16, 0, 1, 1.14286, 1, 1, 0, 0, 0, 0, 22.5, 0, 0, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 15, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650755903, 0, 'npc_elementals_generic'),
(@EARTHELEMENTAL, 0, 0, 0, 0, 0, 14328, 0, 0, 0, 'Earth Elemental', NULL, NULL, 0, 81, 81, 2, 16, 0, 1, 1.14286, 1, 1, 0, 0, 0, 0, 22.5, 0, 0, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 15, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650755903, 0, 'npc_elementals_generic'),
(@FIREELEMENTAL, 0, 0, 0, 0, 0, 1070, 0, 0, 0, 'Fire Elemental', NULL, NULL, 0, 81, 81, 2, 16, 0, 1, 1.14286, 1, 1, 0, 0, 0, 0, 22.5, 0, 0, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 15, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650755903, 0, 'npc_elementals_generic'),
(@SYLVAGENT, 0, 0, 0, 0, 0, 15294, 0, 0, 0, 'Invisible Sylvanas Agent', '<OLD SM>', NULL, 0, 81, 81, 0, 35, 0, 1, 1.14286, 0.1, 1, 2, 2, 0, 24, 1, 2000, 0, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 1, 1, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 4, 1, 0.2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 668974975, 0, ''),
(@KELTHUZADAGENT, 0, 0, 0, 0, 0, 20570, 0, 0, 0, "Kel\'Thuzad invis agent", '<OLD SM>', NULL, 0, 83, 83, 2, 16, 0, 1, 1.14286, 2, 1, 509, 683, 0, 805, 35, 2000, 0, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 371, 535, 135, 6, 36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 4, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 668974975, 128, 'npc_void_zone_OLDSM'),
(@RAGINGSKELETON, 0, 0, 0, 0, 0, 30363, 0, 0, 0, 'Raging Skeleton', "<Kel\'Thuzad Minion", NULL, 0, 80, 80, 2, 16, 0, 1, 1.14286, 1, 1, 422, 586, 0, 642, 22.5, 2000, 0, 1, 32832, 2048, 0, 0, 0, 0, 0, 0, 345, 509, 103, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650754879, 0, 'npc_raging_skeleton_OLDSM'),
(@PURPLEORB, 0, 0, 0, 0, 0, 17200, 0, 0, 0, 'Purple Light Orb', NULL, NULL, 0, 83, 83, 1, 16, 0, 1, 1.14286, 5, 1, 2, 2, 0, 24, 1, 2000, 0, 1, 33554432, 2048, 0, 0, 0, 0, 0, 0, 1, 1, 100, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 7, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 0, 'npc_purple_lightning_orb_OLDSM');

DELETE FROM `creature` WHERE `id` = @MAZIN;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(@cGUID, @MAZIN, 44, 1, 1, 0, 0, 182.865, -81.0748, 18.02, 5.25027, 604800, 0, 0, 162610, 149030, 0, 0, 0, 0);

DELETE FROM `creature_text` WHERE `entry` = @MAZIN;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(@MAZIN, 0, 0, 'What is that smell!? eww!', 12, 0, 100, 0, 0, 0, 'OLD SM boss 1'),
(@MAZIN, 1, 0, 'uh.. strangers.. I''m Mazin Soulstealer, are you here to fight me?', 12, 0, 100, 11, 0, 0, 'OLD SM boss 1'),
(@MAZIN, 2, 0, 'Fine, we will fight but first let me show you my collection... my collection of souls.', 12, 0, 100, 0, 0, 0, 'OLD SM boss 1'),
(@MAZIN, 3, 0, 'My powers allow me to steal part of someone soul without killing him, they''re not the real deal, but strong enough to kill you!', 12, 0, 100, 11, 0, 0, 'OLD SM boss 1'),
(@MAZIN, 4, 0, 'Go''el also known as Thrall. Warchief of the Orcish Horde!', 12, 0, 100, 0, 0, 0, 'OLD SM boss 1'),
(@MAZIN, 5, 0, 'Dark Ranger, Mistress Sylvanas!', 12, 0, 100, 0, 0, 0, 'OLD SM boss 1'),
(@MAZIN, 6, 0, 'Founder of the Cult of the Damned, Kel''Thuzad!', 12, 0, 100, 0, 0, 0, 'OLD SM boss 1'),
(@MAZIN, 7, 0, 'The end is near!', 12, 0, 100, 0, 0, 0, 'Old SM boss 1'),
(@MAZIN, 8, 0, 'Killing is not so easy as the innocent believe $n', 12, 0, 100, 0, 0, 0, 'Old SM boss1'),
(@MAZIN, 8, 1, 'There will be killing till the score is paid $n', 12, 0, 100, 0, 0, 0, 'Old SM boss 1'),
(@MAZIN, 8, 2, 'Killing makes me feel good $n', 12, 0, 100, 0, 0, 0, 'Old SM boss 1'),
(@MAZIN, 9, 0, 'The death of the soul is more painful than that of the body. Javier.. Matar! MATARLOS A TODOS!', 14, 0, 100, 0, 0, 0, 'Old SM boss 1');

DELETE FROM `creature_equip_template` WHERE `entry` IN (@MAZIN, @THRALL, @RAGINGSKELETON, @SYLVANAS, @KELTHUZAD);
INSERT INTO `creature_equip_template` VALUES
(@MAZIN, 1, 19364, 0, 0, 0),
(@THRALL, 1, 13408, 13408, 0, 0),
(@RAGINGSKELETON, 1, 17104, 0, 0, 0),
(@SYLVANAS, 1, 0, 0, 34529, 0),
(@KELTHUZAD, 1, 880, 0, 0, 0);

DELETE FROM `creature_template_addon` WHERE `entry` IN (@THRALL, @SYLVANAS, @KELTHUZAD, @MAZIN, @PURPLEORB);
INSERT INTO `creature_template_addon` VALUES
(@THRALL, 0, 0, 0, 0, 0, '12898 44816 25039'),
(@SYLVANAS, 0, 0, 0, 2, 0, '12898 44816 25039'),
(@KELTHUZAD, 0, 0, 0, 0, 0, '12898 44816 25039'),
(@MAZIN, 0, 0, 0, 1, 0, '46804'),
(@PURPLEORB, 0, 0, 0, 0, 0, '32566');

DELETE FROM `disables` WHERE `entry` = 61873;
INSERT INTO `disables` (`sourceType`, `entry`, `flags`, `params_0`, `params_1`, `comment`)VALUES
(0, 61873, 64, 0, 0, 'Disable los for copy of throw spear OLD SM');

DELETE FROM `spell_script_names` WHERE `spell_id` IN (30000,30282);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(30000, 'spell_demon_wings_OLDSM'),
(30282, 'spell_fireball_barrage_OLDSM');
