SET @ENTRY:= 250000;
SET @GO_ENTRY:= 400500;

-- do zmiany
SET @OGUID:= 550000;
SET @CGUID:= 2073700;

DELETE FROM `creature_template` WHERE `entry` BETWEEN @ENTRY + 0 AND @ENTRY + 35;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
-- boss one stuff
(@ENTRY, 0, 0, 0, 0, 0, 16896, 0, 0, 0, 'Phyrrocoris', '', '', 0, 80, 80, 2, 14, 0, 1, 1.14286, 4, 0, 0, 0, 0, 0, 1, 2000, 2000, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 12340),
(@ENTRY + 1, 0, 0, 0, 0, 0, 16896, 0, 0, 0, 'Flaming Larva', '', '', 0, 80, 80, 2, 14, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 12340),
(@ENTRY + 2, 0, 0, 0, 0, 0, 16896, 0, 0, 0, 'Attachable worm', '', '', 0, 80, 80, 2, 14, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 12340),
-- boss two stuff
(@ENTRY + 3, 0, 0, 0, 0, 0, 1206, 0, 0, 0, 'Prophet of Slythe', '', '', 0, 80, 80, 2, 14, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 12340),
(@ENTRY + 4, 0, 0, 0, 0, 0, 1206, 0, 0, 0, 'Snake soaker', '', '', 0, 80, 80, 2, 14, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 12340),
(@ENTRY + 5, 0, 0, 0, 0, 0, 21174, 0, 0, 0, "Slythe's Guardian", '', '', 0, 80, 80, 2, 14, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 12340),
(@ENTRY + 6, 0, 0, 0, 0, 0, 21174, 0, 0, 0, 'Snake boss add two', '', '', 0, 80, 80, 2, 14, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 12340),
(@ENTRY + 7, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'CrossFire Trigger', '', '', 0, 80, 80, 2, 14, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 12340),
(@ENTRY + 8, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'BossTwo Spawn Triggers', '', '', 0, 80, 80, 2, 14, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 12340),
-- unsued afterall (@ENTRY + 9, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'Snake boss floating blob', '', '', 0, 80, 80, 2, 14, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 128, '', 12340),
(@ENTRY + 10, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'Snake boss delayed explosion', '', '', 0, 80, 80, 2, 14, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 128, '', 12340),
(@ENTRY + 11, 0, 0, 0, 0, 0, 1206, 0, 0, 0, "Slythe's Slave", '', '', 0, 80, 80, 2, 35, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 'npc_add_poison_spreader', 12340),
(@ENTRY + 12, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'Flame spreader hit target', '', '', 0, 80, 80, 2, 35, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 12340),
(@ENTRY + 13, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'Toxic Waste Caster', '', '', 0, 80, 80, 2, 14, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 12340),

-- boss three stuff
(@ENTRY + 14, 0, 0, 0, 0, 0, 21028, 0, 0, 0, 'Simon', '', '', 0, 80, 80, 2, 14, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 12340),

-- boss four stuff
(@ENTRY + 15, 0, 0, 0, 0, 0, 2147483649, 0, 0, 0, 'Hephasto the Armorer', 'The Greatest Blacksmith', '', 0, 83, 83, 2, 14, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 12340),

-- boss three adds
(@ENTRY + 16, 0, 0, 0, 0, 0, 20211, 0, 0, 0, 'Boss Three Tornado', '', '', 0, 80, 80, 2, 14, 0, 1, 0.5, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 12340),

-- boss four adds
(@ENTRY + 17, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'Boss four lightning target', '', '', 0, 80, 80, 2, 14, 0, 1, 0.5, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 128, '', 12340),
(@ENTRY + 18, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'Boss four blizzard target', '', '', 0, 80, 80, 2, 14, 0, 1, 0.5, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 128, '', 12340),

-- gauntlet trigger & gauntlet adds
(@ENTRY + 19, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'Gauntlet controller', '', '', 0, 80, 80, 2, 14, 0, 1, 0.5, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 2, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 128, '', 12340),
(@ENTRY + 20, 0, 0, 0, 0, 0, 30403, 0, 0, 0, 'Bloody Gargoyle', '', '', 0, 80, 80, 2, 2068, 0, 1, 1.14286, 1, 0, 383, 539, 0, 500, 1, 2000, 2000, 2, 32768, 2048, 0, 0, 0, 0, 0, 0, 321, 477, 68, 6, 0, 31040, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 4, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 8388624, 0, '', 12340),
(@ENTRY + 21, 0, 0, 0, 0, 0, 31812, 31752, 0, 0, 'Risen Madman', '', '', 0, 80, 80, 2, 35, 0, 0.777776, 1.14286, 1, 0, 0, 0, 0, 0, 1, 1000, 2000, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 15, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 8388624, 0, '', 12340),
(@ENTRY + 22, 0, 0, 0, 0, 0, 24993, 24994, 24992, 24995, 'Risen Madman', '', '', 0, 80, 80, 2, 21, 0, 1, 1.14286, 1, 0, 2, 2, 0, 24, 1, 2000, 2000, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 1, 1, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 8388624, 0, '', 12340),

(@ENTRY + 23, 0, 0, 0, 0, 0, 31165, 0, 0, 0, 'The Black Witch', '', '', 0, 83, 83, 2, 21, 0, 1, 1.14286, 1, 0, 2, 2, 0, 24, 1, 2000, 2000, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 1, 1, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 8388624, 0, '', 12340),
(@ENTRY + 24, 0, 0, 0, 0, 0, 11398, 0, 0, 0, 'Bloody Warlock', '', '', 0, 83, 83, 2, 21, 0, 1, 1.14286, 1.5, 0, 2, 2, 0, 24, 1, 2000, 2000, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 1, 1, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 8388624, 0, '', 12340),
(@ENTRY + 25, 0, 0, 0, 0, 0, 985, 0, 0, 0, 'Bloody Mindmaster', '', '', 0, 83, 83, 2, 21, 0, 1, 1.14286, 1.5, 0, 2, 2, 0, 24, 1, 2000, 2000, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 1, 1, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 8388624, 0, '', 12340),
(@ENTRY + 26, 0, 0, 0, 0, 0, 30300, 0, 0, 0, 'Bloody Slaughter', '', '', 0, 83, 83, 2, 21, 0, 1, 1.14286, 1, 0, 2, 2, 0, 24, 1, 2000, 2000, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 1, 1, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 8388624, 0, '', 12340),
(@ENTRY + 27, 0, 0, 0, 0, 0, 16053, 0, 0, 0, 'Bloody Bat', '', '', 0, 83, 83, 2, 190, 0, 1, 1.14286, 1, 0, 356, 503, 0, 432, 1, 2000, 2000, 1, 32768, 2048, 0, 24, 0, 0, 0, 0, 305, 452, 74, 1, 1, 28233, 0, 70211, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 12340),
(@ENTRY + 28, 0, 0, 0, 0, 0, 18996, 0, 0, 0, 'Bloody Crystal', '', '', 0, 83, 83, 2, 190, 0, 1, 1.14286, 1, 0, 356, 503, 0, 432, 1, 2000, 2000, 1, 32768, 2048, 0, 24, 0, 0, 0, 0, 305, 452, 74, 1, 1, 28233, 0, 70211, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 128, 'npc_boss_five_flame_spreader', 12340),
(@ENTRY + 29, 0, 0, 0, 0, 0, 26789, 0, 0, 0, 'Paradoxical Worgen', '', '', 0, 83, 83, 2, 190, 0, 1, 1.14286, 1, 0, 356, 503, 0, 432, 1, 2000, 2000, 1, 32768, 2048, 0, 24, 0, 0, 0, 0, 305, 452, 74, 1, 1, 28233, 0, 70211, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 12340),
(@ENTRY + 30, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'Frosty Worgen melee explosion', '', '', 0, 83, 83, 2, 190, 0, 1, 1.14286, 1, 0, 356, 503, 0, 432, 1, 2000, 2000, 1, 32768, 2048, 0, 24, 0, 0, 0, 0, 305, 452, 74, 1, 1, 28233, 0, 70211, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 12340),

-- misc
(@ENTRY + 31, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'Boss one flame patch', '', '', 0, 83, 83, 2, 190, 0, 1, 1.14286, 1, 0, 356, 503, 0, 432, 1, 2000, 2000, 1, 32768, 2048, 0, 24, 0, 0, 0, 0, 305, 452, 74, 1, 1, 28233, 0, 70211, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 128, '', 12340),

-- boss four add
(@ENTRY + 32, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'Fiery Orb', '', '', 0, 83, 83, 2, 190, 0, 1, 1.14286, 1, 0, 356, 503, 0, 432, 1, 2000, 2000, 1, 32768, 2048, 0, 24, 0, 0, 0, 0, 305, 452, 74, 1, 1, 28233, 0, 70211, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 12340),


-- teleport to hellforge
(@ENTRY + 33, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'Hellforge teleport', '', '', 0, 80, 80, 2, 35, 0, 1, 1.14286, 1, 0, 356, 503, 0, 432, 1, 2000, 2000, 1, 32768, 2048, 0, 24, 0, 0, 0, 0, 305, 452, 74, 1, 1, 28233, 0, 70211, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 12340),
(@ENTRY + 34, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'Boss four pillar protection', '', '', 0, 83, 83, 2, 35, 0, 1, 1.14286, 1, 0, 356, 503, 0, 432, 1, 2000, 2000, 1, 32768, 2048, 0, 24, 0, 0, 0, 0, 305, 452, 74, 1, 1, 28233, 0, 70211, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, '', 12340),
(@ENTRY + 35, 0, 0, 0, 0, 0, 11686, 0, 0, 0, 'Boss four hammer hit trigger', '', '', 0, 83, 83, 2, 35, 0, 1, 1.14286, 5, 0, 356, 503, 0, 432, 1, 2000, 2000, 1, 32768, 2048, 0, 24, 0, 0, 0, 0, 305, 452, 74, 1, 1, 28233, 0, 70211, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 'npc_boss_four_hammer_hit_pool', 12340);

DELETE FROM `creature_equip_template` WHERE `entry` IN (@ENTRY + 24, @ENTRY + 26, 250005);
INSERT INTO `creature_equip_template` VALUES 
(@ENTRY + 24, 1, 1907, 0, 0, 0), -- Bloody Warlock
(@ENTRY + 26, 1, 52007, 52008, 0, 0), -- Bloody Slaughter
(250005, 1, 31062, 0, 0, 0);

-- update every creature
UPDATE `creature_template` SET `lootid` = 0, `baseattacktime` = 2000, `mingold` = 0, `maxgold` = 0, `minlevel` = 83, `maxlevel` = 83, `exp` = 2, `rank` = 1 WHERE `entry` BETWEEN @ENTRY + 0 AND @ENTRY + 32;
-- and now set boss specific fields
UPDATE `creature_template` SET `speed_run` = 1.71429, `mechanic_immune_mask` = 650854271, `rank` = 3, `type_flags` = `type_flags` | 4, `flags_extra` = 2097153/*instance bind and knockback immunity*/ WHERE `entry` IN (@ENTRY + 0, @ENTRY + 3, @ENTRY + 5, @ENTRY + 14, @ENTRY + 15, @ENTRY + 23, @ENTRY + 29);
-- 2097409
UPDATE `creature_template` SET `flags_extra` = `flags_extra` | 256 WHERE `entry` IN (@ENTRY + 0, @ENTRY + 3, @ENTRY + 5, @ENTRY + 11, @ENTRY + 14, @ENTRY + 20, @ENTRY + 21, @ENTRY + 22, @ENTRY + 27, @ENTRY + 28, @ENTRY + 25, @ENTRY + 24);
DELETE FROM `creature_template_addon` WHERE `entry` = @ENTRY + 31;
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(@ENTRY + 31, "64561");

-- dodac bind flagi
UPDATE `creature_template` SET `unit_flags` = `unit_flags` | 33554432, `flags_extra` = 128 WHERE `entry` IN (@ENTRY + 12, @ENTRY + 13);
UPDATE `creature_template` SET `ScriptName` = "boss_hellforge_one", `unit_flags2` = `unit_flags2` | 32768 WHERE `entry` = @ENTRY;
UPDATE `creature_template` SET `scale` = 0.65, `ScriptName` = "npc_little_worm_boss_one", `family` = 42 WHERE `entry` = @ENTRY + 1;
UPDATE `creature_template` SET `scale` = 0.40, `ScriptName` = "npc_exploding_worm" WHERE `entry` = @ENTRY + 2;
UPDATE `creature_template` SET `scale` = 10, `ScriptName` = "boss_hellforge_boss_two", `speed_run` = 3 WHERE `entry` = @ENTRY + 3;
UPDATE `creature_template` SET `scale` = 0.15, `flags_extra` = 0, `ScriptName` = "npc_boss_two_soaker", `speed_run` = 1, `unit_flags` = 33554944 WHERE `entry` = @ENTRY + 4;
UPDATE `creature_template` SET `ScriptName` = "npc_hellforge_boss_two_add", `unit_flags2` = 0 WHERE `entry` = @ENTRY + 5;
UPDATE `creature_template` SET `flags_extra` = 128, `InhabitType` = 4 WHERE `entry` = @ENTRY + 8;
UPDATE `creature_template` SET `scale` = 0.5, `ScriptName` = "npc_boss_two_crossfire_trigger" WHERE `entry` = @ENTRY + 7;
UPDATE `creature_template` SET `InhabitType` = 4, `ScriptName` = "npc_boss_two_floating_blob" WHERE `entry` = @ENTRY + 9;
UPDATE `creature_template` SET `InhabitType` = 4, `flags_extra` = 128 WHERE `entry` = @ENTRY + 13;
UPDATE `creature_template` SET `ScriptName` = "boss_hellforge_boss_three", `scale` = 5 WHERE `entry` = @ENTRY + 14;
UPDATE `creature_template` SET `ScriptName` = "boss_dwarf_boss_four", `scale` = 4 WHERE `entry` = @ENTRY + 15;
UPDATE `creature_template` SET `ScriptName` = "npc_boss_three_tornado", `flags_extra` = 0, `unit_flags` = 33554432 WHERE `entry` = @ENTRY + 16;
UPDATE `creature_template` SET `ScriptName` = "npc_boss_four_lightning_target" WHERE `entry` = @ENTRY + 17;
UPDATE `creature_template` SET `ScriptName` = "npc_boss_four_blizzard_target", `flags_extra` = 128, `speed_run` = 1, `speed_walk` = 1 WHERE `entry` = @ENTRY + 18;
UPDATE `creature_template` SET `ScriptName` = "npc_gauntlet_controller_hellforge" WHERE `entry` = @ENTRY + 19;
UPDATE `creature_template` SET `faction` = 14 WHERE `entry` IN (@ENTRY + 20, @ENTRY + 21, @ENTRY + 22);
UPDATE `creature_template` SET `faction` = 14, `ScriptName` = "boss_hellforge_five" WHERE `entry` = @ENTRY + 23;
UPDATE `creature_template` SET `flags_extra` = 0, `minlevel` = 80, `maxlevel` = 80, `scale` = 1.3/*, `ScriptName` = "npc_boss_five_flame_spreader"*/ WHERE `entry` = @ENTRY + 28;
UPDATE `creature_template` SET `ScriptName` = "npc_boss_five_frosty_worgen", `dmgschool` = 4/*frost*/ WHERE `entry` = @ENTRY + 29;
UPDATE `creature_template` SET `ScriptName` = "npc_boss_five_melee_explosion", `flags_extra` = 128 WHERE `entry` = @ENTRY + 30;
UPDATE `creature_template` SET `ScriptName` = "npc_boss_five_burner" WHERE `entry` = @ENTRY + 24;
UPDATE `creature_template` SET `ScriptName` = "npc_boss_five_fearer" WHERE `entry` = @ENTRY + 25;
UPDATE `creature_template` SET `ScriptName` = "npc_boss_five_big_add" WHERE `entry` = @ENTRY + 26;
-- hide nameplates for fiery orb trigger
UPDATE `creature_template` SET `faction` = 35, `npcflag` = 16777216, `ScriptName` = "npc_boss_fiery_orb", `type_flags` = 1048576 WHERE `entry` = @ENTRY + 32;
UPDATE `creature_template` SET `ScriptName` = "npc_boss_five_bat", `InhabitType` = 4 WHERE `entry` = @ENTRY + 27;
UPDATE `creature_template` SET `ScriptName` = "npc_bloody_gargoyle_hellforge", `VehicleId` = 562 WHERE `entry` = @ENTRY + 20;
UPDATE `creature_template` SET `ScriptName` = "npc_hellforge_teleporter" WHERE `entry` = @ENTRY + 33;
UPDATE `creature_template` SET `ScriptName` = "npc_boss_four_pillar_protection" WHERE `entry` = @ENTRY + 34;
UPDATE `creature_template` SET `mechanic_immune_mask` = 650854271 WHERE `entry` IN (@ENTRY + 21, @ENTRY + 22, @ENTRY + 27, @ENTRY + 28, @ENTRY + 26, @ENTRY + 29);
UPDATE `creature_template` SET `scale` = 1.5 WHERE `entry` IN (@ENTRY + 25,  @ENTRY + 24);
UPDATE `creature_template` SET `unit_flags` = `unit_flags` | 33554432, `type` = 0 WHERE `entry` IN (@ENTRY + 13, @ENTRY + 19, @ENTRY + 30);


DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = @ENTRY + 32;
INSERT INTO `npc_spellclick_spells` VALUES
(@ENTRY + 32, 13567, 2, 1);

DELETE FROM `gameobject_template` WHERE `entry` BETWEEN @GO_ENTRY + 0 AND @GO_ENTRY + 16;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `AIName`, `ScriptName`, `VerifiedBuild`) VALUES
(@GO_ENTRY + 0, 10, 4291, 'Sacrifice Altar', '', 'Using', '', 0, 0, 1.3, 0, 0, 0, 0, 0, 0, 1690, 0, 0, 1000000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19700, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0),
(@GO_ENTRY + 1, 5, 230, 'Frostblade Shrine Aura', '', '', '', 0, 0, 0.95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0),
(@GO_ENTRY + 2, 5, 1, 'Comestic Chest 02 (2.00)', '', '', '', 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', -18019),
(@GO_ENTRY + 3, 8, 273, 'Anvil', '', '', '', 0, 0, 2.5, 0, 0, 0, 0, 0, 0, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 12340),
(@GO_ENTRY + 4, 10, 6383, 'Gong', '', '', '', 0, 0, 1.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 'go_gong_of_boss_two', 12340),
(@GO_ENTRY + 5, 0, 8266, 'Doodad_org_arena_red_fence01', '', '', '', 114, 32, 4.3, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 12340),
(@GO_ENTRY + 6, 0, 3614, 'Gate gauntlet exit', '', '', '', 0, 20, 1.3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 12340),
(@GO_ENTRY + 7, 0, 3614, 'Gate gauntlet entrance', '', '', '', 0, 20, 1.3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 12340),
(@GO_ENTRY + 8, 0, 3614, 'Gate exit boss four', '', '', '', 0, 20, 1.3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 12340),
(@GO_ENTRY + 9, 0, 3614, 'Gate boss five entrance', '', '', '', 0, 20, 1.3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 12340),
(@GO_ENTRY + 10, 0, 3614, 'Gate boss four entrance', '', '', '', 0, 20, 1.3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 12340),
(@GO_ENTRY + 11, 0, 2750, 'Simon says exit', '', '', '', 114, 34, 1.25, 0, 0, 0, 0, 0, 0, 1, 85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 12340),
(@GO_ENTRY + 12, 0, 2750, 'Simon says entrance', '', '', '', 114, 34, 1.25, 0, 0, 0, 0, 0, 0, 0, 85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 12340),
(@GO_ENTRY + 13, 0, 2752, 'first boss entrance', '', '', '', 114, 34, 1.51, 0, 0, 0, 0, 0, 0, 0, 85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 12340),
(@GO_ENTRY + 14, 0, 2752, 'Golem Room North', '', '', '', 114, 34, 1.5, 0, 0, 0, 0, 0, 0, 0, 85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 12340),
(@GO_ENTRY + 15, 0, 2752, 'Golem Room South', '', '', '', 114, 34, 1.5, 0, 0, 0, 0, 0, 0, 0, 85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 12340),
(@GO_ENTRY + 16, 0, 3614, 'Gate boss five exit', '', '', '', 0, 20, 1.3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 12340);


DELETE FROM `gameobject` WHERE `id` BETWEEN @GO_ENTRY + 0 AND @GO_ENTRY + 16;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `VerifiedBuild`) VALUES
(@OGUID + 0, 400502, 230, 2, 1, 1171, -201.93, -65.3086, 2.36012, -0, -0, -0.924628, -0.38087, 300, 0, 1, 0),
(@OGUID + 1, 400503, 230, 2, 1, 1175.13, -187.021, -65.4539, 4.32834, -0, -0, -0.829059, 0.559161, 300, 0, 1, 0),
(@OGUID + 2, 400505, 230, 2, 1, 1380.94, -425.717, -94.6745, 3.14542, 0, 0, -0.999998, 0.00191538, 300, 0, 0, 0),
-- (@OGUID + 3, 400504, 230, 2, 1, 1381.06, -386.575, -92.0517, 4.67615, -0, -0, -0.719801, 0.69418, 300, 0, 1, 0), 
(@OGUID + 4, 400506, 230, 2, 1, 1042.22, -210.546, -61.7851, 0.736717, -0, -0, -0.360084, -0.93292, 300, 0, 1, 0),
(@OGUID + 5, 400507, 230, 2, 1, 1080.03, -171.287, -65.3025, 0.823112, -0, -0, -0.400036, -0.916499, 300, 0, 0, 0),
(@OGUID + 6, 400508, 230, 2, 1, 1080.03, -171.287, -65.3025, 0.823112, -0, -0, -0.400036, -0.916499, 300, 0, 1, 0),
(@OGUID + 7, 400509, 230, 2, 1, 1042.22, -210.546, -61.7851, 0.736717, -0, -0, -0.360084, -0.93292, 300, 0, 1, 0),
(@OGUID + 8, 400510, 230, 2, 1, 1203.78, -179.075, -74.33, 5.50086, -0, -0, -0.381265, 0.924466, 300, 0, 1, 0),
(@OGUID + 9, @GO_ENTRY + 11, 230, 2, 1, 1230.33, -205.21, -85.6843, -0.767945, 0, 0, -0.374607, 0.927184, 600, 100, 0, 0),
(@OGUID + 10, @GO_ENTRY + 12, 230, 2, 1, 1262.85, -293.797, -78.1676, -0.785397, 0, 0, -0.382683, 0.92388, 600, 100, 0, 0),
(@OGUID + 11, @GO_ENTRY + 13, 230, 2, 1, 1380.12, -710.482, -92.0093, -1.5708, 0, 0, -0.707107, 0.707107, 600, 100, 1, 0),
(@OGUID + 12, @GO_ENTRY + 14, 230, 2, 1, 1389.55, -555.851, -92.0093, -1.5708, 0, 0, -0.707107, 0.707107, 600, 100, 1, 0),
(@OGUID + 13, @GO_ENTRY + 15, 230, 2, 1, 1370.65, -555.846, -92.0093, -1.5708, 0, 0, -0.707107, 0.707107, 600, 100, 1, 0),
(@OGUID + 14, 400516, 230, 2, 1, 983.187, -212.345, -61.7892, 2.31873, -0, -0, -0.916549, -0.399923, 300, 0, 1, 0);

UPDATE `gameobject_template` SET `ScriptName` = "go_altar_of_sacrifice_hellforge", `flags` = 0 WHERE `entry` = @GO_ENTRY + 0;

-- change respawn times for bosses
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID + 0 AND @CGUID + 52;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID + 0, @ENTRY + 0, 230, 2, 1, 0, 0, 1379.19, -623.617, -92.0543, 4.61492, 300, 0, 0, 12600, 3994, 0, 0, 0, 0),
(@CGUID + 1, @ENTRY + 3, 230, 2, 1, 0, 0, 1329.794, -432.588, -92.00099, 1.524, 300, 0, 0, 12600, 3994, 0, 0, 0, 0),
(@CGUID + 2, @ENTRY + 14, 230, 2, 1, 0, 0, 1266.94, -249.684, -78.219, 2.30436, 300, 0, 0, 12600, 3994, 0, 0, 0, 0),
(@CGUID + 3, @ENTRY + 15, 230, 2, 1, 0, 0, 1173.13, -191.129, -65.4475, 1.20244, 300, 0, 0, 12600, 3994, 0, 0, 0, 0),
(@CGUID + 4, @ENTRY + 19, 230, 2, 1, 0, 0, 1065.72, -192.736, -63.5526, 3.67176, 300, 0, 0, 12600, 3994, 0, 0, 33554432, 0),

-- fire triggers at first boss
(@CGUID + 5 , 250031, 230, 2, 1, 0, 0, 1402.94, -673.901, -92.0544, 2.93809, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 6 , 250031, 230, 2, 1, 0, 0, 1408.74, -676.061, -92.0544, 5.94224, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 7 , 250031, 230, 2, 1, 0, 0, 1404.3, -678.177, -92.0544, 5.94224, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 8 , 250031, 230, 2, 1, 0, 0, 1403.36, -683.986, -92.0544, 5.94224, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 9 , 250031, 230, 2, 1, 0, 0, 1409.96, -684.192, -92.0544, 5.94224, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 10, 250031, 230, 2, 1, 0, 0, 1412.54, -676.928, -92.0544, 0.237107, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 11, 250031, 230, 2, 1, 0, 0, 1410.2, -671.725, -92.0544, 0.237107, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 12, 250031, 230, 2, 1, 0, 0, 1403.71, -670.054, -92.0544, 0.237107, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 13, 250031, 230, 2, 1, 0, 0, 1407.89, -632.218, -92.0544, 0.102018, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 14, 250031, 230, 2, 1, 0, 0, 1402.31, -631.397, -92.0544, 0.102018, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 15, 250031, 230, 2, 1, 0, 0, 1402.59, -634.196, -92.0544, 0.102018, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 16, 250031, 230, 2, 1, 0, 0, 1403.2, -640.129, -92.0544, 0.102018, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 17, 250031, 230, 2, 1, 0, 0, 1406.19, -639.824, -92.0544, 0.102018, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 18, 250031, 230, 2, 1, 0, 0, 1410.97, -637.891, -92.0544, 0.102018, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 19, 250031, 230, 2, 1, 0, 0, 1412.22, -631.281, -92.0544, 0.102018, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 20, 250031, 230, 2, 1, 0, 0, 1410.58, -625.813, -92.0544, 0.102018, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 21, 250031, 230, 2, 1, 0, 0, 1403.5, -625.482, -92.0544, 0.102018, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 22, 250031, 230, 2, 1, 0, 0, 1402.1, -581.88, -92.0544, 6.18807, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 23, 250031, 230, 2, 1, 0, 0, 1402.51, -590.195, -92.0544, 6.18807, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 24, 250031, 230, 2, 1, 0, 0, 1404.45, -588.53, -92.0544, 6.18807, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 25, 250031, 230, 2, 1, 0, 0, 1407.76, -586.367, -92.0544, 6.18807, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 26, 250031, 230, 2, 1, 0, 0, 1403.07, -595.054, -92.0544, 6.18807, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 27, 250031, 230, 2, 1, 0, 0, 1407.52, -594.197, -92.0544, 6.18807, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 28, 250031, 230, 2, 1, 0, 0, 1411.69, -589.256, -92.0544, 6.18807, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 29, 250031, 230, 2, 1, 0, 0, 1411.57, -583.253, -92.0544, 6.18807, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 30, 250031, 230, 2, 1, 0, 0, 1405.81, -580.311, -92.0544, 0.0619659, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 31, 250031, 230, 2, 1, 0, 0, 1357.95, -590.941, -92.0544, 3.16037, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 32, 250031, 230, 2, 1, 0, 0, 1353.6, -589.34, -92.0544, 3.16037, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 33, 250031, 230, 2, 1, 0, 0, 1358.14, -586.769, -92.0544, 3.16037, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 34, 250031, 230, 2, 1, 0, 0, 1358.02, -580.827, -92.0544, 3.16037, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 35, 250031, 230, 2, 1, 0, 0, 1350.81, -581.971, -92.0544, 3.16037, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 36, 250031, 230, 2, 1, 0, 0, 1351.29, -594.475, -92.0544, 3.16037, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 37, 250031, 230, 2, 1, 0, 0, 1347.98, -588.186, -92.0544, 3.16037, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 38, 250031, 230, 2, 1, 0, 0, 1356.92, -595.419, -92.0544, 3.16037, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 39, 250031, 230, 2, 1, 0, 0, 1355.66, -629.299, -92.0543, 3.22713, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 40, 250031, 230, 2, 1, 0, 0, 1356.15, -634.344, -92.0543, 3.22713, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 41, 250031, 230, 2, 1, 0, 0, 1358.86, -625.005, -92.0543, 3.22713, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 42, 250031, 230, 2, 1, 0, 0, 1353.85, -625.435, -92.0543, 3.22713, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 43, 250031, 230, 2, 1, 0, 0, 1348.96, -629.764, -92.0543, 3.22713, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 44, 250031, 230, 2, 1, 0, 0, 1349.14, -636.839, -92.0543, 3.22713, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 45, 250031, 230, 2, 1, 0, 0, 1356.97, -639.864, -92.0543, 3.22713, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 46, 250031, 230, 2, 1, 0, 0, 1359.65, -670.824, -92.0543, 0.984031, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 47, 250031, 230, 2, 1, 0, 0, 1356.88, -678.043, -92.0543, 3.24205, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 48, 250031, 230, 2, 1, 0, 0, 1353.8, -672.226, -92.0543, 3.24205, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 49, 250031, 230, 2, 1, 0, 0, 1349.95, -678.838, -92.0543, 3.24205, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),
(@CGUID + 50, 250031, 230, 2, 1, 0, 0, 1356.99, -684.799, -92.0543, 3.24205, 300, 0, 0, 12600, 0, 0, 0, 33587200, 0),

-- vampire boss
(@CGUID + 51, 250023, 230, 2, 1, 0, 0, 1012.39, -240.434, -61.3871, 3.95, 300, 0, 0, 12600, 0, 0, 0, 0, 0),

-- teleporter
(@CGUID + 52, 250033, 571, 1, 1, 0, 0, 3589.09, 366.315, -109.695, 1.16454, 300, 0, 0, 12600, 0, 0, 0, 0, 0);

UPDATE `creature` SET `spawntimesecs` = 604800 WHERE `guid` BETWEEN @CGUID + 0 AND @CGUID + 52;

DELETE FROM `spell_script_names` WHERE `spell_id` IN (56505, 32361, 31256, 23272, 22662, 11350, 61186, 29973, 29849, 54115, 19099, 62470, 42171, 25656, 39067, 72635);
INSERT INTO `spell_script_names` VALUES
(56505, "spell_surge_of_power_periodic"),
(32361, "spell_boss_two_crystal_prison"),
(31256, "spell_boss_four_frost_armor"),
(11350, "spell_boss_one_fire_shield"),
(61186, "spell_boss_four_frozen_bites_triggered"),
(29973, "spell_boss_four_arcane_explosion"),
(29849, "spell_boss_four_frost_nova"),
(54115, "spell_boss_two_blight_crystal_damage"),
(19099, "spell_boss_four_blizzard_damage"),
(62470, "spell_defeaning_thunder_boss_four"),
(42171, "spell_evidence_marker_hellforge"),
(25656, "spell_hellforge_sandtrap"),
(39067, "spell_boss_four_lightning_shield"),
(72635, "spell_hellforge_boss_five_flame");

UPDATE `gameobject_template` SET `data2` = 1, `data7` = 4 WHERE `entry` = 180647;

DELETE FROM `waypoint_data` WHERE `id` = (@ENTRY + 15) * 10;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `move_type`) VALUES
((@ENTRY + 15) * 10, 0, 1167.261, -196.994, -65.44095, 3.827, 1),
((@ENTRY + 15) * 10, 1, 1159.211, -202.483, -65.44674, 3.804, 1),
((@ENTRY + 15) * 10, 2, 1150.095, -204.451, -65.43459, 3.434, 1),
((@ENTRY + 15) * 10, 3, 1142.168, -205.722, -65.42977, 3.085, 1),
((@ENTRY + 15) * 10, 4, 1131.706, -204.848, -65.42977, 2.221, 1),
((@ENTRY + 15) * 10, 5, 1115.622, -186.523, -65.46320, 2.394, 1);

-- fix frost nova for unholy weapon
UPDATE smart_scripts SET action_param2 = 2 WHERE entryorguid = 16215 AND id = 2;

DELETE FROM `creature_template_outfits` WHERE `entry` = 2147483649;
INSERT INTO creature_template_outfits VALUES
(2147483649,0,3,1,0,7,5,5,4,4,0,47781,0,45429,0,47057,0,0,45430,0,0,0,'Hellforge Dwarf');

UPDATE `creature_template` SET `mechanic_immune_mask` =
 1              -- MECHANIC_CHARM  
 | 2            -- MECHANIC_DISORIENTED    
 | 4            -- MECHANIC_DISARM         
 | 8            -- MECHANIC_DISTRACT       
 | 16           -- MECHANIC_FEAR  
 | 32           -- MECHANIC_GRIP
-- | 64           -- MECHANIC_ROOT  
 | 128          -- MECHANIC_PACIFY
 | 256          -- MECHANIC_SILENCE      
 | 512          -- MECHANIC_SLEEP        
 | 1024         -- MECHANIC_SNARE       
-- | 2048         -- MECHANIC_STUN        
 | 4096         -- MECHANIC_FREEZE      
 | 8192         -- MECHANIC_KNOCKOUT
 | 16384        -- MECHANIC_BLEED    
 | 32768        -- MECHANIC_BANDAGE
 | 65536        -- MECHANIC_POLYMORPH  
 | 131072       -- MECHANIC_BANISH    
 | 262144       -- MECHANIC_SHIELD  
-- | 524288       -- MECHANIC_SHACKLE
-- | 1048576      -- MECHANIC_MOUNT
-- | 2097152      -- MECHANIC_INFECTED
 | 4194304      -- MECHANIC_TURN
 | 8388608      -- MECHANIC_HORROR
 | 16777216     -- MECHANIC_INVULNERABILITY
-- | 33554432     -- MECHANIC_INTERRUPT       
-- | 67108864     -- MECHANIC_DAZE    
 | 134217728    -- MECHANIC_DISCOVERY
 | 268435456    -- MECHANIC_IMMUNE_SHIELD
 | 536870912    -- MECHANIC_SAPPED         
-- | 1073741824   -- MECHANIC_ENRAGED 
WHERE `entry` IN (@ENTRY + 20);

UPDATE `creature_template` SET `mechanic_immune_mask` =
 1              -- MECHANIC_CHARM  
 | 2            -- MECHANIC_DISORIENTED    
 | 4            -- MECHANIC_DISARM         
 | 8            -- MECHANIC_DISTRACT       
 | 16           -- MECHANIC_FEAR  
 | 32           -- MECHANIC_GRIP
-- | 64           -- MECHANIC_ROOT  
 | 128          -- MECHANIC_PACIFY
 | 256          -- MECHANIC_SILENCE      
 | 512          -- MECHANIC_SLEEP        
 | 1024         -- MECHANIC_SNARE       
 | 2048         -- MECHANIC_STUN        
 | 4096         -- MECHANIC_FREEZE      
 | 8192         -- MECHANIC_KNOCKOUT
 | 16384        -- MECHANIC_BLEED    
 | 32768        -- MECHANIC_BANDAGE
 | 65536        -- MECHANIC_POLYMORPH  
 | 131072       -- MECHANIC_BANISH    
 | 262144       -- MECHANIC_SHIELD  
-- | 524288       -- MECHANIC_SHACKLE
-- | 1048576      -- MECHANIC_MOUNT
-- | 2097152      -- MECHANIC_INFECTED
 | 4194304      -- MECHANIC_TURN
 | 8388608      -- MECHANIC_HORROR
 | 16777216     -- MECHANIC_INVULNERABILITY
-- | 33554432     -- MECHANIC_INTERRUPT       
 | 67108864     -- MECHANIC_DAZE    
 | 134217728    -- MECHANIC_DISCOVERY
 | 268435456    -- MECHANIC_IMMUNE_SHIELD
 | 536870912    -- MECHANIC_SAPPED         
-- | 1073741824   -- MECHANIC_ENRAGED 
WHERE `entry` IN (@ENTRY + 25, @ENTRY + 24);

-- 
UPDATE `creature_template` SET `mechanic_immune_mask` =
 1              -- MECHANIC_CHARM  
 | 2            -- MECHANIC_DISORIENTED    
 | 4            -- MECHANIC_DISARM         
 | 8            -- MECHANIC_DISTRACT       
 | 16           -- MECHANIC_FEAR  
 | 32           -- MECHANIC_GRIP
 | 64           -- MECHANIC_ROOT  
 | 128          -- MECHANIC_PACIFY
 | 256          -- MECHANIC_SILENCE      
 | 512          -- MECHANIC_SLEEP        
 -- | 1024         -- MECHANIC_SNARE       
 | 2048         -- MECHANIC_STUN        
 | 4096         -- MECHANIC_FREEZE      
 | 8192         -- MECHANIC_KNOCKOUT
 | 16384        -- MECHANIC_BLEED    
 | 32768        -- MECHANIC_BANDAGE
 | 65536        -- MECHANIC_POLYMORPH  
 | 131072       -- MECHANIC_BANISH    
 | 262144       -- MECHANIC_SHIELD  
-- | 524288       -- MECHANIC_SHACKLE
-- | 1048576      -- MECHANIC_MOUNT
-- | 2097152      -- MECHANIC_INFECTED
 | 4194304      -- MECHANIC_TURN
 | 8388608      -- MECHANIC_HORROR
 | 16777216     -- MECHANIC_INVULNERABILITY
| 33554432     -- MECHANIC_INTERRUPT       
-- | 67108864     -- MECHANIC_DAZE    
 | 134217728    -- MECHANIC_DISCOVERY
 | 268435456    -- MECHANIC_IMMUNE_SHIELD
 | 536870912    -- MECHANIC_SAPPED         
-- | 1073741824   -- MECHANIC_ENRAGED 
WHERE `entry` IN (@ENTRY + 1);

DELETE FROM `access_requirement` WHERE `mapId` = 230;
INSERT INTO `access_requirement` VALUES
(230, 0, 40, 0, 0, 0, 0, 0, 0, 0, NULL, 'Blackrock Mountain - Searing Gorge Instance?'),
(230, 1, 90, 0, 0, 0, 0, 0, 0, 0, NULL, 'Hellforge');

UPDATE `gameobject` SET `SpawnMask` = 3 WHERE `guid` IN (35862, 335812, 17122, 15620, 15302, 17124, 15642, 15629, 15577, 15552, 15550, 15547);

DELETE FROM `spell_proc_event` WHERE `entry` = 61185;
INSERT INTO `spell_proc_event` (`entry`, `procFlags`, `procEx`) VALUES
(61185, 4, 9343); 
