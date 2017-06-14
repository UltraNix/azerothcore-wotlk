SET @DESSEMBRAE:= 400010;
SET @PHYSICALBALL := 400011;
SET @FROSTBALL := 400012;
SET @FIREBALL := 400013;
SET @ARCANEBALL := 400014;
SET @ROOMADD := 400015;
SET @ROOMGHOST := 400016;
SET @CHANNELTRIGGER:= 400017;
SET @PROTECTOR:= 400018;
SET @LILPHEONIX:= 400019;
SET @FLAMETRIGGER:= 400033;
SET @ARCANEORB := 400034;
SET @FORCEFIELDDUMMY := 400035;
SET @BOMB := 400036;
-- ^inne entry bo od 400020 uzywalem na mazinie

-- gameobject
SET @BUFFWELL:= 500016;

SET @DESSEMBRAEGUID := 400004;

DELETE FROM `creature_template` WHERE `entry` = @DESSEMBRAE;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES 
(@DESSEMBRAE, 0, 0, 0, 0, 0, 17279, 0, 0, 0, 'Dessembrae', '<The Risen>', NULL, 65007, 83, 83, 2, 35, 1, 1, 1.14286, 1.2, 3, 417, 582, 0, 608, 100, 2000, 0, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 341, 506, 80, 7, 4, 100007, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2000000, 2500000, '', 0, 3, 1, 2000, 1000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 1, 'boss_dessembrae', 0);

DELETE FROM `creature` WHERE `id` = @DESSEMBRAE;
DELETE FROM `creature` WHERE `id` = @DESSEMBRAE;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@DESSEMBRAEGUID, @DESSEMBRAE, 44, 1, 1, 0, 1, 432.13, -113.14, 32.07, 1.5708, 604800, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM `gossip_menu` WHERE `entry` = 65007;
INSERT INTO `gossip_menu` (`entry`, `text_id`) VALUES
(65007, 40007);

DELETE FROM `npc_text` WHERE `ID` = 40007;
INSERT INTO `npc_text` (`ID`, `text0_0`, `text0_1`, `lang0`, `prob0`, `em0_0`, `em0_1`, `em0_2`, `em0_3`, `em0_4`, `em0_5`, `text1_0`, `text1_1`, `lang1`, `prob1`, `em1_0`, `em1_1`, `em1_2`, `em1_3`, `em1_4`, `em1_5`, `text2_0`, `text2_1`, `lang2`, `prob2`, `em2_0`, `em2_1`, `em2_2`, `em2_3`, `em2_4`, `em2_5`, `text3_0`, `text3_1`, `lang3`, `prob3`, `em3_0`, `em3_1`, `em3_2`, `em3_3`, `em3_4`, `em3_5`, `text4_0`, `text4_1`, `lang4`, `prob4`, `em4_0`, `em4_1`, `em4_2`, `em4_3`, `em4_4`, `em4_5`, `text5_0`, `text5_1`, `lang5`, `prob5`, `em5_0`, `em5_1`, `em5_2`, `em5_3`, `em5_4`, `em5_5`, `text6_0`, `text6_1`, `lang6`, `prob6`, `em6_0`, `em6_1`, `em6_2`, `em6_3`, `em6_4`, `em6_5`, `text7_0`, `text7_1`, `lang7`, `prob7`, `em7_0`, `em7_1`, `em7_2`, `em7_3`, `em7_4`, `em7_5`, `VerifiedBuild`) VALUES
(40007, 'Leave me alone!', 'Leave me alone!', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM `gossip_menu_option` WHERE `menu_id` = 65007;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`,  `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES
(65007, 0, 0, 'Poke', 1, 1, 0, 0, 0, 0, '');

DELETE FROM `creature_text` WHERE `entry` = @DESSEMBRAE;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(@DESSEMBRAE, 0, 0, "I warned you to leave me alone dammit!", 12, 0, 100, 1, 0, 0, 'Dessembrae'),
(@DESSEMBRAE, 1, 0, "Be hole, be dust, be dream, be wind. Be night, be dark, be wish, be mind. Now slip, now slide, now move unseen. Above, beneath, betwixt, between. Every spell is a journey you know?", 12, 0, 100, 1, 0, 0, 'Dessembrae'),
(@DESSEMBRAE, 2, 0, "This is essence of physical mastery.", 12, 0, 100, 1, 0, 0, 'Dessembrae'),
(@DESSEMBRAE, 3, 0, "This one is essence of frost magic.", 12, 0, 100, 1, 0, 0, 'Dessembrae'),
(@DESSEMBRAE, 4, 0, "Essence of fire magic. Can you feel the burning sensation?", 12, 0, 100, 1, 0, 0, 'Dessembrae'),
(@DESSEMBRAE, 5, 0, "And last but not least, essence of arcane magic.", 12, 0, 100, 1, 0, 0, 'Dessembrae'),
(@DESSEMBRAE, 6, 0, "Ahh.. im whole again!", 12, 0, 100, 1, 0, 0, 'Dessembrae'),
(@DESSEMBRAE, 7, 0, "I won't play your game mortals, you will play my instead! $n $n $n", 12, 0, 100, 1, 0, 0, 'Dessembrae'),
(@DESSEMBRAE, 8, 0, "Looks like your friends lost.", 12, 0, 100, 1, 0, 0, 'Dessembrae'),
(@DESSEMBRAE, 9, 0, "Tonitrus meum iram fulgur meum fortitudinem. Adduce meo nubes nigrae quasi noctem.", 12, 0, 100, 1, 0, 0, 'Dessembrae'),
(@DESSEMBRAE, 10, 0, "Aoooowwwwww!", 12, 0, 100, 1, 0, 0, 'Dessembrae'),
(@DESSEMBRAE, 11, 0, "Which came first, the phoenix or the flame?", 12, 0, 100, 1, 0, 0, 'Dessembrae'),
(@DESSEMBRAE, 12, 0, "I walked this land when the first night elves were but children. I have commanded armies a hundred thousand strong. I have spread the fire of my wrath across entire continents, and sat alone upon tall thrones. Do you grasp the meaning of this? Do you truly believe that you can defeat me? NONSENSE!!", 12, 0, 100, 1, 0, 0, 'Dessembrae'),
(@DESSEMBRAE, 13, 0, "Nothing burns like the cold.", 12, 0, 100, 1, 0, 0, 'Dessembrae'),
(@DESSEMBRAE, 14, 0, "Is it wrong to kill something that wants to kill you?", 12, 0, 100, 1, 0, 0, 'Dessembrae'),
(@DESSEMBRAE, 14, 1, "Many have tried to kill me. Another one falls.", 12, 0, 100, 1, 0, 0, 'Dessembrae'),
(@DESSEMBRAE, 15, 0, "Defair le coo reah melth plea, et to belth thoo coupe snow Melthere nada greth planetarie, reah melth plea. Defair le coo et to belth thoo coupe snow.", 12, 0, 100, 1, 0, 0, 'Dessembrae'),
(@DESSEMBRAE, 16, 0, "Dessembrae is looking for target..", 41, 0, 100, 1, 0, 0, 'Dessembrae'),
(@DESSEMBRAE, 17, 0, "Dessembrae is chasing $N", 41, 0, 100, 1, 0, 0, 'Dessembrae'),
(@DESSEMBRAE, 18, 0, "Dessembrae is gaining speed!", 41, 0, 100, 1, 0, 0, 'Dessembrae');

-- ---------------------------- kulki

DELETE FROM `creature_template` WHERE `entry` IN (@PHYSICALBALL, @FROSTBALL, @FIREBALL, @ARCANEBALL);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@PHYSICALBALL, 0, 0, 0, 0, 0, 25144, 0, 0, 0, 'Ball of Physical Power', NULL, NULL, 0, 80, 80, 1, 35, 0, 4, 4, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 33554688, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 4, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 2, 'npc_dessembraes_ball', 0),
(@FROSTBALL, 0, 0, 0, 0, 0, 16480, 0, 0, 0, 'Ball of Frost Power', NULL, NULL, 0, 80, 80, 1, 35, 0, 4, 4, 0.6, 1, 0, 0, 0, 0, 1, 0, 0, 1, 33554688, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 4, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 130, 'npc_dessembraes_ball', 0),
(@FIREBALL, 0, 0, 0, 0, 0, 16480, 0, 0, 0, 'Ball of Fire Power', NULL, NULL, 0, 80, 80, 1, 35, 0, 4, 4, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 33554688, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 4, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 130, 'npc_dessembraes_ball', 0),
(@ARCANEBALL, 0, 0, 0, 0, 0, 16480, 0, 0, 0, 'Ball of Arcane Power', NULL, NULL, 0, 80, 80, 1, 35, 0, 4, 4, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 33554688, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 4, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 130, 'npc_dessembraes_ball', 0);


DELETE FROM `creature_template_addon` WHERE `entry` IN (@PHYSICALBALL, @FROSTBALL, @FIREBALL, @ARCANEBALL, @ARCANEORB);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(@PHYSICALBALL, 0, 0, 0, 4097, 0, NULL),
(@FROSTBALL, 0, 0, 0, 4097, 0, '50579'),
(@FIREBALL, 0, 0, 0, 4097, 0, '71706'),
(@ARCANEBALL, 0, 0, 33554432, 4097, 0, '69017'),
(@ARCANEORB, 0, 0, 33554432, 0, 0, '69017');

-- ---------------------------- pokoj

DELETE FROM `creature_template` WHERE `entry` IN (@ROOMADD, @ROOMGHOST, @CHANNELTRIGGER, @PROTECTOR, @LILPHEONIX, @FLAMETRIGGER, @ARCANEORB, @FORCEFIELDDUMMY, @BOMB);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@ROOMADD, 0, 0, 0, 0, 0, 23226, 0, 0, 0, 'Arcane Channeler', '<The Risen>', NULL, 0, 83, 83, 2, 16, 0, 0.6, 1.14286, 1, 1, 417, 582, 0, 608, 1, 2000, 0, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 341, 506, 80, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 60, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 0, 'npc_arcane_channeler', 0),
(@ROOMGHOST, 0, 0, 0, 0, 0, 25553, 0, 0, 0, 'Shadow of the Past', NULL, NULL, 0, 82, 82, 2, 16, 0, 0.6, 0.6, 0.5, 1, 417, 582, 0, 608, 3, 2000, 0, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 341, 506, 80, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 5, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650875775, 0, 'npc_shadow_of_the_past', 0),
(@CHANNELTRIGGER, 0, 0, 0, 0, 0, 16480, 0, 0, 0, 'channel trigger', NULL, NULL, 0, 83, 83, 2, 16, 0, 0.8, 0.8, 1, 1, 417, 582, 0, 608, 1, 2000, 0, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 341, 506, 80, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 60, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 128, 'npc_channel_trigger_OLDSM', 0),
(@PROTECTOR, 0, 0, 0, 0, 0, 12750, 2429, 12929, 0, 'Protector', NULL, 'Interact', 0, 83, 83, 2, 16, 0, 0.6, 1.14286, 1, 1, 417, 582, 0, 608, 1, 2000, 0, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 341, 506, 80, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 60, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 0, 'npc_protector_OLDSM', 0),
(@LILPHEONIX, 0, 0, 0, 0, 0, 23574, 0, 0, 0, 'Cute little pheonix', 'OF DEATH!', NULL, 0, 83, 83, 2, 16, 0, 0.6, 1.14286, 2, 1, 417, 582, 0, 608, 1, 2000, 0, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 341, 506, 80, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 4, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 256, 'npc_little_phoenix_OLDSM', 0),
(@FLAMETRIGGER, 0, 0, 0, 0, 0, 23574, 0, 0, 0, 'old SM flames', NULL, NULL, 0, 83, 83, 2, 16, 0, 0.6, 1.14286, 0.5, 1, 417, 582, 0, 608, 1, 2000, 0, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 341, 506, 80, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 60, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 128, '', 0),
(@ARCANEORB, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'Arcane Orb', NULL, NULL, 0, 83, 83, 2, 16, 0, 0.35, 0.35, 0.8, 1, 417, 582, 0, 608, 1, 2000, 0, 2, 33554434, 2048, 0, 0, 0, 0, 0, 0, 341, 506, 80, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 0.5, 60, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 128, 'npc_arcane_orb_OLDSM', 0),
(@FORCEFIELDDUMMY, 0, 0, 0, 0, 0, 26753, 0, 0, 0, 'Force Field Dummy', NULL, NULL, 0, 83, 83, 2, 35, 0, 0.35, 0.35, 2, 1, 417, 582, 0, 608, 1, 2000, 0, 2, 33554692, 2048, 0, 0, 0, 0, 0, 0, 341, 506, 80, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 60, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 2, '', 0),
(@BOMB, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'protector bomb', '', '', 0, 83, 83, 2, 16, 0, 0.35,0.35, 0.5, 0, 417, 582, 0, 608, 1, 2000, 0, 2, 33554436, 2048, 8, 0, 0, 0, 0, 0, 341, 506, 80, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 60, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 'npc_protector_bomb_OLDSM', 0);
 

DELETE FROM `gameobject_template` WHERE `entry` = @BUFFWELL;
INSERT INTO `gameobject_template` VALUES 
(@BUFFWELL, 1, 7788, 'Defense Well', '', '', '', 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 'go_energy_well', 0);

DELETE FROM `spell_script_names` WHERE `spell_id` IN (29973, 34190, 3023, 37993);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(29973, 'spell_arcane_explosion_OLDSM'),
(34190 , 'spell_arcane_orb_damage'),
(3023, 'aura_nature_debuff_test_OLDSM'),
(37993, 'spell_frost_breath_OLDSM');

UPDATE `creature_model_info` SET `bounding_radius` = '0.07', `combat_reach` = '0.2' WHERE `modelid` = 23574;
