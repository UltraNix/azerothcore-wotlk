SET @DEVALETH := 400008;
SET @EAGLE := 400009;

SET @DEVALETHGUID := 400003;

DELETE FROM `creature_template` WHERE `entry` IN (@DEVALETH, @EAGLE);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@DEVALETH, 0, 0, 0, 0, 0, 30198, 0, 0, 0, 'Devaleth', '<The Risen>', NULL, 0, 83, 83, 2, 16, 0, 1.4, 1.8, 2, 3, 250, 350, 0, 300, 115, 1500, 0, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 260, 387, 37, 6, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1500000, 2000000, '', 0, 1, 1, 700, 300, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650887039, 257, 'npc_devaleth', 0),
(@EAGLE, 0, 0, 0, 0, 0, 25630, 0, 0, 0, 'Risen Eagle', NULL, NULL, 0, 82, 82, 0, 16, 0, 1.65, 2.286, 0.5, 1, 200, 500, 0, 100, 15, 1000, 0, 1, 32768, 2048, 0, 0, 0, 0, 0, 0, 28, 41, 8, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 100, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 650875775, 0, 'npc_risen_eagle', 0);

DELETE FROM `creature_equip_template` WHERE `entry` = @DEVALETH;
INSERT INTO `creature_equip_template` (`entry`, `id`, `itemEntry1`, `itemEntry2`, `itemEntry3`, `VerifiedBuild`) VALUES
(@DEVALETH, 1, 19854, 0, 0, 0);

DELETE FROM `creature_text` WHERE `entry` = @DEVALETH;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(@DEVALETH, 0, 0, "Eagles, attack!", 12, 0, 100, 0, 0, 0, 'Devaleth'),
(@DEVALETH, 1, 0, "I will crush you!", 12, 0, 100, 0, 0, 0, 'Devaleth');

DELETE FROM `creature` WHERE `id` = @DEVALETH;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `VerifiedBuild`) VALUES
(@DEVALETHGUID, @DEVALETH, 44, 1, 1, 0, 1, 244.153, -30.326, 31.494, 0.000, 604800, 0, 0, 0, 0, 0, 0, 0, 0, 0);
