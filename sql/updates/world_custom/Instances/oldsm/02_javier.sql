SET @JAVIERID := 400000;
SET @VOID := 400001;
SET @JAVIERCLONE := 400002;
SET @DEFENDER := 400003;
SET @BUFFER := 400004;
SET @HEALER := 400005;
SET @SOLDIER := 400006;

SET @JAVIERGUID := 400000;

DELETE FROM `creature_template` WHERE `entry` IN (@JAVIERID, @VOID, @JAVIERCLONE, @HEALER, @BUFFER, @DEFENDER, @SOLDIER);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(@JAVIERID, 0, 0, 0, 0, 0, 27611, 0, 0, 0, 'Javier Voidbringer', '<The Risen>', NULL, 0, 83, 83, 2, 16, 0, 1.4, 1.8, 1, 3, 250, 350, 0, 300, 115, 1500, 0, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 260, 387, 37, 6, 4, 100007, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2000000, 2500000, '', 0, 7, 1, 1300, 300, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 257, 'boss_javier_voidbringer'),
(@VOID, 0, 0, 0, 0, 0, 31196, 0, 0, 0, 'Void', NULL, NULL, 0, 83, 83, 2, 16, 0, 3, 3, 0.5, 1, 250, 350, 0, 0, 1, 2000, 0, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 260, 387, 37, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 4, 1, 8, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 256, 'npc_void'),
(@JAVIERCLONE, 0, 0, 0, 0, 0, 27611, 0, 0, 0, 'Javier Voidbringer', '<The Risen>', NULL, 0, 83, 83, 2, 16, 0, 1.4, 1.8, 1, 3, 250, 350, 5, 300, 25, 1500, 0, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 260, 387, 37, 6, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 300, 200, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 617332607, 0, 'npc_javier_clone'),
(@DEFENDER, 0, 0, 0, 0, 0, 22773, 0, 0, 0, 'Risen Defender', '<The Risen>', NULL, 0, 83, 83, 2, 16, 0, 1, 1.14286, 0.5, 1, 250, 350, 0, 0, 1, 2000, 0, 2, 4, 2048, 0, 0, 0, 0, 0, 0, 365, 529, 98, 6, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 11, 20, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 256, 'npc_javier_helper'),
(@BUFFER, 0, 0, 0, 0, 0, 22773, 0, 0, 0, 'Risen Sorcerer', '<The Risen>', NULL, 0, 83, 83, 2, 16, 0, 1, 1.14286, 0.5, 1, 250, 350, 0, 0, 1, 2000, 0, 2, 4, 2048, 0, 0, 0, 0, 0, 0, 365, 529, 98, 6, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 15, 20, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 256, 'npc_javier_helper'),
(@HEALER, 0, 0, 0, 0, 0, 22773, 0, 0, 0, 'Risen Healer', '<The Risen>', NULL, 0, 83, 83, 2, 16, 0, 1, 1.14286, 0.5, 1, 250, 350, 0, 0, 1, 2000, 0, 2, 4, 2048, 0, 0, 0, 0, 0, 0, 365, 529, 98, 6, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 30, 20, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 256, 'npc_javier_helper'),
(@SOLDIER, 0, 0, 0, 0, 0, 30616, 30617, 0, 0, 'Risen Soldier', '<The Risen>', NULL, 0, 83, 83, 2, 16, 0, 1, 1.14286, 0.8, 1, 250, 350, 0, 500, 40, 2000, 0, 1, 32832, 2048, 0, 0, 0, 0, 0, 0, 345, 509, 103, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 15, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650884991, 0, 'npc_javier_soldier');

DELETE FROM `creature_equip_template` WHERE `entry` IN (@JAVIERID, @JAVIERCLONE, @SOLDIER);
INSERT INTO `creature_equip_template` (`entry`, `id`, `itemEntry1`, `itemEntry2`, `itemEntry3`, `VerifiedBuild`) VALUES
(@JAVIERID, 1, 18874, 0, 0, 0),
(@JAVIERCLONE, 1, 18874, 0, 0, 0),
(@SOLDIER, 1, 49637, 49777, 0, 0);

DELETE FROM `creature` WHERE `id` = @JAVIERID;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@JAVIERGUID, @JAVIERID, 44, 1, 1, 0, 1, 272.603, -99.817, 28.870, 3.146, 604800, 0, 0, 8785350, 300000, 0, 0, 0, 0);

DELETE FROM `creature_text` WHERE `entry` = @JAVIERID;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(@JAVIERID, 0, 0, "It is a long time since someone as courageous as you came into my domain. You managed to defeat a Risen on top of that! Impressive!", 12, 0, 100, 1, 0, 0, 'Javier Voidbringer'),
(@JAVIERID, 1, 0, "I'll avenge you Mazin. Wait just a little bit longer.", 12, 0, 100, 0, 0, 0, 'Javier Voidbringer'),
(@JAVIERID, 2, 0, "The shadow escapes from the body like an animal we had been sheltering. Look above you.", 12, 0, 100, 1, 0, 0, 'Javier Voidbringer'),
(@JAVIERID, 3, 0, "The only real battle in life is between hanging on and letting go.", 12, 0, 100, 0, 0, 0, 'Javier Voidbringer'),
(@JAVIERID, 4, 0, "And what will you do? Hang on or let go?", 14, 0, 100, 25, 0, 0, 'Javier Voidbringer'),
(@JAVIERID, 5, 0, "Your end has come.", 14, 0, 100, 0, 0, 0, 'Javier Voidbringer'),
(@JAVIERID, 6, 0, "You'll witness the true power of The Risen!", 12, 0, 100, 25, 0, 0, 'Javier Voidbringer'),
(@JAVIERID, 7, 0, "I love those who can smile in battle.. ;)", 12, 0, 100, 0, 0, 0, 'Javier Voidbringer'),
(@JAVIERID, 8, 0, "Argh! You're strong mortals!", 12, 0, 100, 0, 0, 0, 'Javier Voidbringer'),
(@JAVIERID, 9, 0, "COME FORTH INTO LIGHT OF THINGS!", 12, 0, 100, 0, 0, 0, 'Javier Voidbringer'),
(@JAVIERID, 10, 0, "It's not over yet!", 12, 0, 100, 0, 0, 0, 'Javier Voidbringer'),
(@JAVIERID, 11, 0, "Who would have thought that i'll have to let go.", 12, 0, 100, 0, 0, 0, 'Javier Voidbringer'),
(@JAVIERID, 12, 0, "If I'm going to die, I will take you with me!", 14, 0, 100, 0, 0, 0, 'Javier Voidbringer'),
(@JAVIERID, 13, 0, "My power... is gone... You... have won.", 12, 0, 100, 0, 0, 0, 'Javier Voidbringer');
