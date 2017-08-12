SET @NPC_CAVE := 91000;
DELETE FROM creature_template WHERE entry = @NPC_CAVE;
DELETE FROM creature_template WHERE entry = @NPC_CAVE + 1;
DELETE FROM creature_template WHERE entry = @NPC_CAVE + 2;
DELETE FROM creature_template WHERE entry = @NPC_CAVE + 3;
DELETE FROM creature_template WHERE entry = @NPC_CAVE + 4;
DELETE FROM creature_template WHERE entry = @NPC_CAVE + 5;
DELETE FROM creature_template WHERE entry = @NPC_CAVE + 6;
DELETE FROM creature_template WHERE entry = @NPC_CAVE + 7;
DELETE FROM creature_template WHERE entry = @NPC_CAVE + 8;
DELETE FROM creature_template WHERE entry = @NPC_CAVE + 9;
DELETE FROM creature_template WHERE entry = @NPC_CAVE + 10;
DELETE FROM creature_template WHERE entry = @NPC_CAVE + 11;
DELETE FROM creature_template WHERE entry = @NPC_CAVE + 18;
DELETE FROM creature_template WHERE entry = @NPC_CAVE + 19;
DELETE FROM creature_template WHERE entry = @NPC_CAVE + 20;
DELETE FROM creature_template WHERE entry = @NPC_CAVE + 21;
DELETE FROM creature_template WHERE entry = @NPC_CAVE + 22;
DELETE FROM creature_template WHERE entry = @NPC_CAVE + 23;
DELETE FROM creature_template WHERE entry = @NPC_CAVE + 24;
DELETE FROM creature_template WHERE entry = @NPC_CAVE + 25;
DELETE FROM creature_template WHERE entry = @NPC_CAVE + 26;
DELETE FROM creature_template WHERE entry = @NPC_CAVE + 27;
DELETE FROM creature_template WHERE entry = @NPC_CAVE + 28;
DELETE FROM creature_template WHERE entry = @NPC_CAVE + 29;
DELETE FROM creature_template WHERE entry = @NPC_CAVE + 30;
DELETE FROM creature_template WHERE entry = @NPC_CAVE + 31;
DELETE FROM creature_template WHERE entry = @NPC_CAVE + 32;
DELETE FROM creature_template WHERE entry = @NPC_CAVE + 33;
SET @NPC_GUEST := 92000;
DELETE FROM creature_template WHERE entry = @NPC_GUEST;
DELETE FROM creature_template WHERE entry = @NPC_GUEST + 1;
DELETE FROM creature_template WHERE entry = @NPC_GUEST + 2;
DELETE FROM creature_template WHERE entry = @NPC_GUEST + 3;
DELETE FROM creature_template WHERE entry = @NPC_GUEST + 4;
DELETE FROM creature_template WHERE entry = @NPC_GUEST + 5;
DELETE FROM creature_template WHERE entry = @NPC_GUEST + 6;
 
DELETE FROM creature_template WHERE entry = 32568;
DELETE FROM creature_template WHERE entry = 40165;
DELETE FROM creature_template WHERE entry = 32321;
DELETE FROM creature_template WHERE entry = 32322;
 
INSERT INTO creature_template (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VerifiedBuild`) VALUES
(@NPC_CAVE, 0, 0, 0, 0, 0, 18668, 18668, 18668, 18668, 'Edar', 'Ghost from the Well', '', 0, 70, 70, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 5, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_lotery_teleporter', 12340),
(@NPC_CAVE + 1, 0, 0, 0, 0, 0, 18668, 18668, 18668, 18668, 'Edar', 'Ghost from the Well', '', 0, 70, 70, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 5, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_lotery_teleporter', 12340),
(@NPC_CAVE + 2, 0, 0, 0, 0, 0, 18668, 18668, 18668, 18668, 'Edar', 'Ghost from the Well', '', 0, 70, 70, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 5, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_lotery_teleporter', 12340),
(@NPC_CAVE + 3, 0, 0, 0, 0, 0, 14756, 14756, 14756, 14756, 'Peter the Fisheye', 'Gold Lottery', '', 0, 70, 70, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 5, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_lotery_number', 12340),
(@NPC_CAVE + 4, 0, 0, 0, 0, 0, 6840, 6840, 6840, 6840, 'Peg Gundee', 'Sunwell Coin Lottery', '', 0, 70, 70, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 5, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_lotery_number', 12340),
(@NPC_CAVE + 5, 0, 0, 0, 0, 0, 21697, 21697, 21697, 21697, 'Morgan Moscat', 'Mount Lottery', '', 0, 70, 70, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 5, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_lotery_maker', 12340),
(@NPC_CAVE + 6, 0, 0, 0, 0, 0, 18459, 18459, 18459, 18459, 'Mork', 'Mount Lottery', '', 0, 70, 70, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 5, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_lotery_maker', 12340),
(@NPC_CAVE + 7, 0, 0, 0, 0, 0, 29397, 29397, 29397, 29397, 'Thuna Rivers', 'Mount Lottery', '', 0, 70, 70, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 5, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_lotery_maker', 12340),
(@NPC_CAVE + 8, 0, 0, 0, 0, 0, 16797, 16797, 16797, 16797, 'Lira Summerbreeze', 'Mount Lottery', '', 0, 70, 70, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 5, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_lotery_maker', 12340),
(@NPC_CAVE + 9, 0, 0, 0, 0, 0, 18691, 18691, 18691, 18691, 'Stephen Sparks', 'Mount Lottery', '', 0, 70, 70, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 5, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_lotery_maker', 12340),
(@NPC_CAVE + 10, 0, 0, 0, 0, 0, 5910, 5910, 5910, 5910, 'Shelly Mayers', 'Pet Lottery', '', 0, 70, 70, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 5, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_lotery_maker', 12340),
(@NPC_CAVE + 11, 0, 0, 0, 0, 0, 21505, 21505, 21505, 21505, 'Menos Arc', 'Guard', '', 0, 70, 70, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 5, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_wypierdalator', 12340),
(@NPC_GUEST, 0, 0, 0, 0, 0, 5205, 5205, 5205, 5205, 'Narak Longhorn', '', '', 60000, 80, 80, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 5, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, '', 12340),
(@NPC_GUEST + 1, 0, 0, 0, 0, 0, 3608, 3608, 3608, 3608, 'M\'khan', '', '', 60001, 80, 80, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 5, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, '', 12340),
(@NPC_GUEST + 2, 0, 0, 0, 0, 0, 2662, 2662, 2662, 2662, 'Martha Edwards', '', '', 60002, 80, 80, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 5, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, '', 12340),
(@NPC_GUEST + 3, 0, 0, 0, 0, 0, 5567, 5567, 5567, 5567, 'Zork the Slave Master', '', '', 60003, 80, 80, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 5, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, '', 12340),
(@NPC_GUEST + 4, 0, 0, 0, 0, 0, 17645, 17645, 17645, 17645, 'Derek', '', '', 60004, 80, 80, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 5, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, '', 12340),
(@NPC_GUEST + 5, 0, 0, 0, 0, 0, 18689, 18689, 18689, 18689, 'Karl Saggan', '', '', 60005, 80, 80, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 5, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, '', 12340),
(@NPC_CAVE + 19,0,0,0,0,0,3307,0,0,0,'Karn Rockwell','Food & Drink',NULL,0,38,38,0,35,640,1,1.14286,1,0,53,70,0,128,1,2000,2000,1,512,2048,0,0,0,0,0,0,36,53,13,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'SmartAI',0,3,1,1.15,1,1,0,0,0,0,0,0,0,0,1,0,2,'',12340),
(@NPC_CAVE + 20,0,0,0,0,0,28456,0,0,0,'Frosty','','',0,1,1,0,35,0,1,1.14286,1,0,2,2,0,24,1,2000,2000,1,0,2048,0,0,0,0,0,0,1,1,0,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,3,1,1,1,1,0,0,0,0,0,0,0,121,1,0,0,'',12340),
(@NPC_CAVE + 21,0,0,0,0,0,10992,0,0,0,'Mini Diablo','Lord of Terror',NULL,0,1,1,0,35,0,1,1.14286,1,0,2,2,0,24,1,2000,2200,1,0,2048,0,0,0,0,0,0,1,1,100,12,0,0,0,100008,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,3,1,1,1,1,0,0,0,0,0,0,0,121,1,0,2,'',12340),
(@NPC_CAVE + 22,0,0,0,0,0,30507,0,0,0,'Lil\' K.T.','','',0,1,1,0,35,0,1,1.14286,1,0,2,2,0,24,1,2000,2000,1,33536,2048,0,0,0,0,0,0,1,1,0,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'SmartAI',0,3,1,1,1,1,0,0,0,0,0,0,0,121,1,0,0,'',12340),
(@NPC_CAVE + 23,0,0,0,0,0,32031,0,0,0,'Lil\' XT','','',0,1,1,0,35,0,0.8,1.14286,1,0,0,0,0,0,1,2000,2000,1,0,2048,0,0,0,0,0,0,0,0,0,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'SmartAI',0,3,1,1,1,1,0,0,0,0,0,0,0,121,1,0,0,'',12340),
(@NPC_CAVE + 24,0,0,0,0,0,30409,0,0,0,'Spectral Tiger Cub','','',0,1,1,0,35,0,1,1.14286,1,0,2,2,0,24,1,2000,2000,1,0,2048,0,0,0,0,0,0,1,1,0,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'SmartAI',0,3,1,1,1,1,0,0,0,0,0,0,0,121,1,0,0,'',12340),
(32568,0,0,0,0,0,18724,0,0,0,'Flying Black Qiraji Battle Tank','','',0,62,62,1,35,0,1,1.14286,0.75,0,2,2,0,24,1,2000,2000,1,0,2048,0,44,0,0,0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,4,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,'',12340),
(@NPC_CAVE + 25, 0, 0, 0, 0, 0, 18785, 0, 0, 0, 'Panienka', '', '', 0, 69, 69, 0, 35, 1, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_female_emote', 12340),
(@NPC_CAVE + 26, 0, 0, 0, 0, 0, 18794, 0, 0, 0, 'Panienka', '', '', 0, 69, 69, 0, 35, 1, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_female_emote', 12340),
(@NPC_CAVE + 27, 0, 0, 0, 0, 0, 18802, 0, 0, 0, 'Panienka', '', '', 0, 69, 69, 0, 35, 1, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_female_emote', 12340),
(@NPC_CAVE + 28, 0, 0, 0, 0, 0, 14413, 0, 0, 0, 'Piromancer Maz’grum', '', '', 0, 80, 80, 0, 35, 1, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_burn_flag_horde', 12340),
(@NPC_CAVE + 29, 0, 0, 0, 0, 0, 1505, 0, 0, 0, 'Piromancer Wakarc\n', '', '', 0, 80, 80, 0, 35, 1, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_burn_flag_alliance', 12340),
(@NPC_CAVE + 30, 0, 0, 0, 0, 0, 20388, 0, 0, 0, 'Krokuun', '', '', 0, 80, 80, 0, 35, 1, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_gambler', 12340),
(@NPC_CAVE + 31, 0, 0, 0, 0, 0, 18668, 0, 0, 0, 'Edar', 'Ghost from the Well', '', 0, 80, 80, 0, 35, 1, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_wpierdalator', 12340),
(@NPC_CAVE + 32, 0, 0, 0, 0, 0, 28934, 0, 0, 0, 'Crypt Mage', '', '', 0, 80, 80, 0, 35, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, '', 12340),
(@NPC_CAVE + 33, 0, 0, 0, 0, 0, 25624, 0, 0, 0, 'Cyrulik Jack', 'Fryzjer', '', 60006, 80, 80, 0, 35, 1, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, '', 12340),
(40165,0,0,0,0,0,31803,31803,0,0,'Blazing Hippogryph','','',0,80,80,2,35,0,1,1.14286,0.85,0,0,0,0,0,1,2000,2000,1,0,2048,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,4,1,1,1,1,0,0,0,0,0,0,0,140,1,0,0,'',12340),
(@NPC_CAVE + 34, 0, 0, 0, 0, 0, 26068, 0, 0, 0, 'Seet', 'The Crypt Stalker', '', 0, 80, 80, 0, 35, 1, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_crypt_tele', 12340),
(@NPC_GUEST + 6, 0, 0, 0, 0, 0, 18217, 18217, 18217, 18217, 'Menora', 'Lottery Coins Seller', '', 0, 70, 70, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 5, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_lottery_coins', 12340);
 

SET @NPC_GUID := (SELECT MAX(guid) from creature) +100;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@NPC_GUID, @NPC_CAVE, 0, 1, 1, 0, 0, -11136.219727, -2033.110962, 47.075542, 5.395273, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 1, @NPC_CAVE + 1, 0, 1, 1, 0, 0, -11230.036133, -1775.875977, 4.251500 , 5.734866, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 4, @NPC_CAVE + 3  , 0, 1, 1, 0, 0, -11197.725586, -1806.849854, 4.252917, 1.568324, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 5, @NPC_CAVE + 4  , 0, 1, 1, 0, 0, -11210.725586, -1806.817749, 4.252917, 1.568324, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 6, @NPC_CAVE + 5  , 0, 1, 1, 0, 0, -11183.183594, -1796.786133, 4.252190, 3.201950, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 7, @NPC_CAVE + 6  , 0, 1, 1, 0, 0, -11182.701172, -1804.771484, 4.318017, 3.201950, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 8, @NPC_CAVE + 7  , 0, 1, 1, 0, 0, -11238.137695, -1817.581909, 4.252227, 0.028939, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 9, @NPC_CAVE + 8  , 0, 1, 1, 0, 0, -11238.687500, -1798.589844, 4.252227, 0.028939, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 10, @NPC_CAVE + 9  , 0, 1, 1, 0, 0, -11239.208008, -1780.597412, 4.252227, 0.028939, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 11, @NPC_CAVE + 10 , 0, 1, 1, 0, 0, -11183.787109, -1786.804321, 4.341176, 3.201950, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 12, @NPC_CAVE + 11 , 0, 1, 1, 0, 0, -11230.000000, -1775.880005, 4.351553, 5.734870, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 13, @NPC_GUEST , 0, 1, 1, 0, 0, -11203.4,-1758.07,4.25195,3.25578, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 14, @NPC_GUEST + 1, 0, 1, 1, 0, 0, -11210.9,-1803.89,4.253,4.73348, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 15, @NPC_GUEST + 2, 0, 1, 1, 0, 0, -11205.5,-1758.17,4.25217,0.170245, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 16, @NPC_GUEST + 3, 0, 1, 1, 0, 0, -11186.1, -1777.3, 4.33218, 0.929793, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 17, @NPC_GUEST + 4, 0, 1, 1, 0, 0, -11234.694336, -1781.235718, 4.252714, 3.181539, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 18, @NPC_GUEST + 5, 0, 1, 1, 0, 0, -11234.242188, -1815.247437, 4.252110, 2.467611, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 19, @NPC_CAVE + 20, 0,1,1,0,0,-11182.9,-1784.11,4.34743,3.7111,300,0,0,42,0,0,0,0,0),
(@NPC_GUID + 20, @NPC_CAVE + 21, 0,1,1,0,0,-11183.8,-1785.53,4.33802,3.65634,300,0,0,42,0,0,0,0,0),
(@NPC_GUID + 21, @NPC_CAVE + 22, 0,1,1,0,0,-11183.5,-1787.74,4.34092,2.88194,300,0,0,42,0,0,0,0,0),
(@NPC_GUID + 22, @NPC_CAVE + 23,0,1,1,0,0,-11184.9,-1787.77,4.33316,0.906663,300,0,0,42,0,0,0,0,0),
(@NPC_GUID + 23, @NPC_CAVE + 24,0,1,1,0,0,-11185,-1791.5,4.29666,0.134614,300,0,0,42,0,0,0,0,0),
(@NPC_GUID + 24, 24004,0,1,1,0,0,-11182,-1791.23,4.30199,3.12076,300,0,0,55,0,0,0,0,0),
(@NPC_GUID + 25, 32568,0,1,1,0,0,-11242.2,-1817.78,9.58043,0.0855407,300,0,0,5341,0,0,0,0,0),
(@NPC_GUID + 26, 40165,0,1,1,0,0,-11242.5,-1804.93,10.2991,0.0910375,300,0,0,12600,0,0,0,0,0),
(@NPC_GUID + 27, 40625,0,1,1,0,0,-11242.5,-1784.9,4.30238,6.28197,300,0,0,5342,0,0,0,0,0),
(@NPC_GUID + 28, @NPC_CAVE + 19,0,1,1,0,0,-11228.8,-1810.6,4.27607,-0.518407,300,0,0,2500,0,2,0,0,0),
(@NPC_GUID + 31, 31146,0,1,1,0,0,-11102.1,-1545.49,27.5323,4.71855,300,0,0,24009944,0,0,0,0,0),
(@NPC_GUID + 37, @NPC_GUEST + 6, 0, 1, 1, 0, 0, -11192.917969, -1776.687744, 4.295313, 4.751176, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 38, @NPC_CAVE + 30, 0, 1, 1, 0, 0, -11215.3, -1776.68, 4.25121, 4.7594, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
(@NPC_GUID + 39, @NPC_CAVE + 34, 0, 1, 1, 0, 0, -11221.3, -1772.01, 4.25276, 0.514327, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
(@NPC_GUID + 40, @NPC_CAVE + 32, 0, 1, 1, 28934, 1, -11229.9, -1770.6, 4.25166, 1.56429, 300, 0, 0, 55890, 31550, 0, 0, 0, 0),
(@NPC_GUID + 41, @NPC_CAVE + 32, 0, 1, 1, 0, 1, -11201.9, -1768.93, 4.25274, 1.76614, 300, 0, 0, 55890, 31550, 0, 0, 0, 0),
(@NPC_GUID + 42, @NPC_CAVE + 32, 0, 1, 1, 0, 1, -11193.7, -1810.63, 7.94713, 4.74671, 300, 0, 0, 55890, 31550, 0, 0, 0, 0),
(@NPC_GUID + 43, @NPC_CAVE + 32, 0, 1, 1, 0, 1, -11193.7, -1816.05, 7.95973, 1.58391, 300, 0, 0, 55890, 31550, 0, 0, 0, 0),
(@NPC_GUID + 44, @NPC_CAVE + 28, 0, 1, 1, 0, 0, -11202, -1760.23, 4.25244, 4.09511, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
(@NPC_GUID + 45, @NPC_CAVE + 29, 0, 1, 1, 0, 0, -11228.1, -1762.05, 4.25188, 5.9422, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
(@NPC_GUID + 46, @NPC_CAVE + 26, 0, 1, 1, 0, 0, -11232.4, -1823.26, 4.2525, 1.53535, 300, 0, 0, 3942, 0, 0, 0, 0, 0),
(@NPC_GUID + 47, @NPC_CAVE + 25, 0, 1, 1, 0, 0, -11223.2, -1809.94, 4.26617, 2.01051, 300, 0, 0, 3942, 0, 0, 0, 0, 0),
(@NPC_GUID + 48, @NPC_CAVE + 27, 0, 1, 1, 0, 0, -11184.9, -1775.92, 4.32018, 3.88053, 300, 0, 0, 3942, 0, 0, 0, 0, 0),
(@NPC_GUID + 49, 29534, 0, 1, 1, 0, 0, -11211.8, -1817.46, 7.96921, 1.58482, 300, 0, 0, 10635, 0, 0, 0, 0, 0),
(@NPC_GUID + 50, 29533, 0, 1, 1, 0, 0, -11207.8, -1817.41, 7.96921, 1.58482, 300, 0, 0, 10635, 0, 0, 0, 0, 0),
(@NPC_GUID + 51, @NPC_CAVE + 31, 0, 1, 1, 0, 0, -11060.7, -1801.65, 52.6571, 3.83049, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
(@NPC_GUID + 52, @NPC_CAVE + 33, 0, 1, 1, 0, 0, -11207.6, -1822.09, 4.25196, 3.15137, 300, 0, 0, 5342, 0, 0, 0, 0, 0),
(@NPC_GUID + 53, 31144, 0, 1, 1, 0, 0, -11226.3, -1757.58, 4.35155, 4.77746, 300, 0, 0, 3, 0, 0, 0, 393216, 0),
(@NPC_GUID + 54, @NPC_CAVE, 571, 1, 1, 0, 0, 5777.167, 572.331, 613.737, 1.4789, 180, 0, 0, 1, 0, 0, 0, 0, 0);


SET @TEXT_ID := 1000000;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 1;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 2;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 3;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 4;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 5;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 6;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 7;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 8;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 9;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 10;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 11;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 12;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 13;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 14;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 15;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 16;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 17;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 18;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 19;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 20;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 21;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 22;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 23;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 24;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 25;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 26;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 27;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 28;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 29;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 30;
DELETE FROM `npc_text` WHERE `npc_text`.`ID` = @TEXT_ID + 31;

INSERT INTO `npc_text` (`ID`, `text0_0`, `text0_1`, `lang0`, `prob0`, `em0_0`, `em0_1`, `em0_2`, `em0_3`, `em0_4`, `em0_5`, `text1_0`, `text1_1`, `lang1`, `prob1`, `em1_0`, `em1_1`, `em1_2`, `em1_3`, `em1_4`, `em1_5`, `text2_0`, `text2_1`, `lang2`, `prob2`, `em2_0`, `em2_1`, `em2_2`, `em2_3`, `em2_4`, `em2_5`, `text3_0`, `text3_1`, `lang3`, `prob3`, `em3_0`, `em3_1`, `em3_2`, `em3_3`, `em3_4`, `em3_5`, `text4_0`, `text4_1`, `lang4`, `prob4`, `em4_0`, `em4_1`, `em4_2`, `em4_3`, `em4_4`, `em4_5`, `text5_0`, `text5_1`, `lang5`, `prob5`, `em5_0`, `em5_1`, `em5_2`, `em5_3`, `em5_4`, `em5_5`, `text6_0`, `text6_1`, `lang6`, `prob6`, `em6_0`, `em6_1`, `em6_2`, `em6_3`, `em6_4`, `em6_5`, `text7_0`, `text7_1`, `lang7`, `prob7`, `em7_0`, `em7_1`, `em7_2`, `em7_3`, `em7_4`, `em7_5`, `VerifiedBuild`) VALUES
(@TEXT_ID, 'Juz dawno nie mialem goscia. Jestem Edar i, jak zdazyles zauwazyc, jestem duchem. Razem z moimi druhami szedlem do Karazhanu i… Niewazne. Naprawde doceniam to, ze tu jestes. Jesli chcesz, to zabiore cie w pewne sekretne miejsce. Tak, jestem martwy, ale martwi tez moga grac!', 'Juz dawno nie mialem goscia. Jestem Edar i, jak zdazyles zauwazyc, jestem duchem. Razem z moimi druhami szedlem do Karazhanu i… Niewazne. Naprawde doceniam to, ze tu jestes. Jesli chcesz, to zabiore cie w pewne sekretne miejsce. Tak, jestem martwy, ale martwi tez moga grac!', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+1, 'Milej zabawy! Tylko pamietaj… znaj umiar. Jesli bedziesz chcial, to pokaze ci, gdzie mozna sprawdzic sie w walce z innymi, albo zabiore cie z powrotem przed Karazhan.', 'Milej zabawy! Tylko pamietaj… znaj umiar. Jesli bedziesz chcial, to pokaze ci, gdzie mozna sprawdzic sie w walce z innymi, albo zabiore cie z powrotem przed Karazhan.', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+2, 'Mordownia zostala zalozona dosc niedawno. Peter byl pierwszy, a potem dolaczyli do niego kolejni - wyrzutki z Azeroth. To miejsce jest trudno dostepne, ale mimo wszystko cieszy sie popularnoscia. Mozesz tu wygrac zloto, Sunwell Coiny, wierzchowce, zwierzaki… albo przegrac wszystko. Ja gram od czasu do czasu, glownie dla przyjemnosci.', 'Mordownia zostala zalozona dosc niedawno. Peter byl pierwszy, a potem dolaczyli do niego kolejni - wyrzutki z Azeroth. To miejsce jest trudno dostepne, ale mimo wszystko cieszy sie popularnoscia. Mozesz tu wygrac zloto, Sunwell Coiny, wierzchowce, zwierzaki… albo przegrac wszystko. Ja gram od czasu do czasu, glownie dla przyjemnosci.', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+3, 'Nie przesadzaj z gra!', 'Nie przesadzaj z gra!', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+4, 'Niezla faza, stary.', 'Niezla faza, stary.', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+5, 'O co ci chodzi?', 'Niezla faza, stary.', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+6, 'Nic tutaj nie widziales.', 'Nic tutaj nie widziales.', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+7, 'Wygrales juz cos?', 'Wygrales juz cos?', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+8, 'Gwiazdy mowia, ze bede mial dzis szczescie.', 'Gwiazdy mowia, ze bede mial dzis szczescie.', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+9, 'Grasz, czy gadasz?', 'Grasz, czy gadasz?', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+10, 'Jestes pewny, ze chcesz sie w to bawic?', 'Jestes pewny, ze chcesz sie w to bawic?', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+11, 'Jesli ci sie uda to odjedziesz na grzbiecie tego tygrysa.', 'Jesli ci sie uda to odjedziesz na grzbiecie tego tygrysa.', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+12, 'To ryzykowna gra...', 'To ryzykowna gra...', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+13, 'Spojrz na ten wspanialy okaz! Mozesz sprobowac go wygrac.', 'Spojrz na ten wspanialy okaz! Mozesz sprobowac go wygrac.', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+14, 'Masz odwage, by dosiasc hipogryfa?', 'Masz odwage, by dosiasc hipogryfa?', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+15, 'Podniebny wierzchowiec… Biega, lata, czego chciec wiecej?', 'Podniebny wierzchowiec… Biega, lata, czego chciec wiecej?', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+16, 'Czasami trzeba czytac miedzy wierszami. Chcesz sprobowac szczescia i wygrac jednego z tych rzadkich zwierzakow?', 'Czasami trzeba czytac miedzy wierszami. Chcesz sprobowac szczescia i wygrac jednego z tych rzadkich zwierzakow?', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+17, 'Sprobuj szczescia nastepnym razem.', 'Sprobuj szczescia nastepnym razem.', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+18, 'Gratulacje! Wygrales. Oto twoja nagroda.', 'Gratulacje! Wygrales. Oto twoja nagroda.', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+19, 'Witaj! Jestem odpowiedzialna za dystrybucje Lottery Coinsow potrzebnych do grania o mounty, pety, zloto oraz Sunwell Coinsy. Chcesz je kupic?', 'Witaj! Jestem odpowiedzialna za dystrybucje Lottery Coinsow potrzebnych do grania o mounty, pety, zloto oraz Sunwell Coinsy. Chcesz je kupic?', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+20, 'Cos jeszcze?', 'Cos jeszcze?', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+21, 'Ile chcesz kupic?', 'Ile chcesz kupic?', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+22, 'Witaj, przystojniaku... Swieta przyszly o wiele wczesniej! Co chcialbys pod choinke?', 'Witaj,slicznotko... Swieta przyszly o wiele wczesniej! Co chcialabys pod choinke?', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+23, 'To dosc stare krypty… Dlugo je eksplorowalem, poznawalem ich tajemnice, ale wciaz nie znam definitywnej odpowiedzi. Jezeli chcesz, to mozesz je zwiedzic na wlasna reke, ale to moze byc dosc niebezpieczne i… szokujace. Oczywiscie pamietasz, gdzie sie znajdujemy? Wiesz, ze nie zrobie tego za darmo?', 'To dosc stare krypty… Dlugo je eksplorowalem, poznawalem ich tajemnice, ale wciaz nie znam definitywnej odpowiedzi. Jezeli chcesz, to mozesz je zwiedzic na wlasna reke, ale to moze byc dosc niebezpieczne i… szokujace. Oczywiscie pamietasz, gdzie sie znajdujemy? Wiesz, ze nie zrobie tego za darmo?', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+24, 'Jesli lubisz sie bic i chcesz zarobic, to dobrze trafiles. Mozesz walczyc za pieniadze, jesli chcesz. Jaka jest twoja stawka?', 'Jesli lubisz sie bic i chcesz zarobic, to dobrze trafiles. Mozesz walczyc za pieniadze, jesli chcesz. Jaka jest twoja stawka?', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+25, 'Jesli ustalisz stawke i wyzwiesz kogos na pojedynek, bedziecie walczyc o twoja stawke. Jezeli przegrasz, to pieniadze trafia do przeciwnika. Zawsze gra sie o stawke tego, kto wyzwie na pojedynek. Jezeli zostaniesz wyzwany przez kogos, ktorego stawka jest 500 gold, bedziecie walczyc wlasnie o tyle. Nie boj sie - bedziesz wiedzial, ze walczysz o pieniadze.', 'Jesli ustalisz stawke i wyzwiesz kogos na pojedynek, bedziecie walczyc o twoja stawke. Jezeli przegrasz, to pieniadze trafia do przeciwnika. Zawsze gra sie o stawke tego, kto wyzwie na pojedynek. Jezeli zostaniesz wyzwany przez kogos, ktorego stawka jest 500 gold, bedziecie walczyc wlasnie o tyle. Nie boj sie - bedziesz wiedzial, ze walczysz o pieniadze.', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+26, 'Witaj,slicznotko... Swieta przyszly o wiele wczesniej! Co chcialabys pod choinke?', 'Witaj,slicznotko... Swieta przyszly o wiele wczesniej! Co chcialabys pod choinke?', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+27, 'Witaj, przystojniaku... Swieta przyszly o wiele wczesniej! Co chcialbys pod choinke?', 'Witaj, przystojniaku... Swieta przyszly o wiele wczesniej! Co chcialbys pod choinke?', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+28, 'To scierwo powinno miec kolory teczy, a nie lwa! Trzeba to spalic!', 'To scierwo powinno miec kolory teczy, a nie lwa! Trzeba to spalic!', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+29, 'Ten niewyobrazalny smrod… ta flaga. Chyba tylko ogien potrafi sie z tym uporac!\r\n', 'Ten niewyobrazalny smrod… ta flaga. Chyba tylko ogien potrafi sie z tym uporac!\r\n', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+30, 'Nazywam sie cyrulik Jack - medyk zlodziei i zloczyncow brat.', 'Nazywam sie cyrulik Jack - medyk zlodziei i zloczyncow brat.', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+31, 'Zgubiles sie?', 'Zgubiles sie?', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340);


SET @GOBJECT_LOCK := 1000000;
DELETE FROM `gossip_menu` WHERE `entry` = 60000;
DELETE FROM `gossip_menu` WHERE `entry` = 60001;
DELETE FROM `gossip_menu` WHERE `entry` = 60002;
DELETE FROM `gossip_menu` WHERE `entry` = 60003;
DELETE FROM `gossip_menu` WHERE `entry` = 60004;
DELETE FROM `gossip_menu` WHERE `entry` = 60005;
DELETE FROM `gossip_menu` WHERE `entry` = 60006;
INSERT INTO `gossip_menu` (`entry`, `text_id`) VALUES (60000, @GOBJECT_LOCK + 3);
INSERT INTO `gossip_menu` (`entry`, `text_id`) VALUES (60001, @GOBJECT_LOCK + 4);
INSERT INTO `gossip_menu` (`entry`, `text_id`) VALUES (60002, @GOBJECT_LOCK + 5);
INSERT INTO `gossip_menu` (`entry`, `text_id`) VALUES (60003, @GOBJECT_LOCK + 6);
INSERT INTO `gossip_menu` (`entry`, `text_id`) VALUES (60004, @GOBJECT_LOCK + 7);
INSERT INTO `gossip_menu` (`entry`, `text_id`) VALUES (60005, 1000008);
INSERT INTO `gossip_menu` (`entry`, `text_id`) VALUES (60006, @GOBJECT_LOCK + 30);

 
UPDATE `gameobject_template` SET `type` = 5 WHERE `entry` IN (176901, 177047, 177048, 177049);

DELETE FROM `gameobject_template` WHERE `entry` = @GOBJECT_LOCK;
DELETE FROM `gameobject_template` WHERE `entry` = @GOBJECT_LOCK + 1;
DELETE FROM `gameobject_template` WHERE `entry` = @GOBJECT_LOCK + 2;
DELETE FROM `gameobject_template` WHERE `entry` = @GOBJECT_LOCK + 3;
DELETE FROM `gameobject_template` WHERE `entry` = @GOBJECT_LOCK + 4;
DELETE FROM `gameobject_template` WHERE `entry` = @GOBJECT_LOCK + 5;
DELETE FROM `gameobject_template` WHERE `entry` = @GOBJECT_LOCK + 5;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `AIName`, `ScriptName`, `VerifiedBuild`) VALUES
(@GOBJECT_LOCK, 5, 411, 'Doodad_PortcullisActive08', '', '', '', 0, 32, 6, 0, 0, 0, 0, 0, 0, 0, 0, 3000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 'go_closed_door', 12340),
(@GOBJECT_LOCK + 1, 5, 411, 'Doodad_PortcullisActive09', '', '', '', 0, 32, 2.97, 0, 0, 0, 0, 0, 0, 0, 0, 3000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 'go_closed_door', 12340),
(@GOBJECT_LOCK + 2,5,7982,'Apothecary Cage','','','',0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'','',1),
(@GOBJECT_LOCK + 3,5,7469,'Gjalerbron Cage','','','',0,32,1.05,0,0,0,0,0,0,0,0,3000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'','',12340),
(@GOBJECT_LOCK + 4,5,2614,'Gold Coins','','','',0,0,0.5,0,0,0,0,0,0,0,300,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'','',11723),
(@GOBJECT_LOCK + 5,5,2614,'Gold Coins','','','',0,0,1,0,0,0,0,0,0,0,300,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'','',11723),
(@GOBJECT_LOCK + 6, 7, 603, 'Wooden Bench', '', '', '', 0, 4, 0.63, 0, 0, 0, 0, 0, 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 12340);


SET @GOBJECT_GUID := (SELECT MAX(guid) from gameobject) +100;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `VerifiedBuild`) VALUES
(@GOBJECT_GUID + 2,@GOBJECT_LOCK + 5,0,1,1,-11197.8,-1807.93,4.25231,4.3557,0,0,-0.821331,0.570451,300,0,1,0),
(@GOBJECT_GUID + 3,@GOBJECT_LOCK + 2,0,1,1,-11241.8,-1817.69,8.55792,3.19101,0,0,-0.999695,0.0247046,300,0,1,0),
(@GOBJECT_GUID + 4,@GOBJECT_LOCK + 2,0,1,1,-11242.4,-1804.71,8.55792,3.19101,0,0,-0.999695,0.0247046,300,0,1,0),
(@GOBJECT_GUID + 5,@GOBJECT_LOCK + 5,0,1,1,-11200.9,-1819.08,4.2518,0.0116606,0,0,-0.00583241,-0.999983,300,0,1,0),
(@GOBJECT_GUID + 6,@GOBJECT_LOCK + 5,0,1,1,-11199.9,-1819.85,4.25892,0.423994,0,0,-0.210413,-0.977613,300,0,1,0),
(@GOBJECT_GUID + 7,@GOBJECT_LOCK + 3,0,1,1,-11181.2,-1791.17,4.30292,0.0797004,0,0,-0.03984,-0.999206,300,0,1,0),
(@GOBJECT_GUID + 8,@GOBJECT_LOCK + 3,0,1,1,-11242.3,-1785.04,4.29741,3.10977,0,0,-0.999873,-0.0159128,300,0,1,0),
(@GOBJECT_GUID + 9,@GOBJECT_LOCK + 3,0,1,1,-11187.4,-1809.18,4.25168,1.6183,0,0,-0.723701,-0.690114,300,0,1,0),
(@GOBJECT_GUID + 10,@GOBJECT_LOCK + 4,0,1,1,-11200.2,-1819.94,4.25221,5.40578,0,0,-0.424767,0.905303,300,0,1,0),
(@GOBJECT_GUID + 11,@GOBJECT_LOCK + 5,0,1,1,-11198.9,-1819.41,4.25191,3.09121,0,0,-0.999683,-0.0251898,300,0,1,0),
(@GOBJECT_GUID + 12,@GOBJECT_LOCK + 5,0,1,1,-11199.4,-1807.7,4.25267,3.20509,0,0,-0.999496,0.0317435,300,0,1,0),
(@GOBJECT_GUID + 13,@GOBJECT_LOCK + 5,0,1,1,-11198.6,-1808.23,4.25656,5.02329,0,0,-0.589101,0.808059,300,0,1,0),
(@GOBJECT_GUID + 14,@GOBJECT_LOCK + 4,0,1,1,-11197.9,-1819.21,4.25296,3.44621,0,0,-0.988424,0.151719,300,0,1,0),
(@GOBJECT_GUID + 15,@GOBJECT_LOCK + 4,0,1,1,-11199.1,-1820.6,4.2523,0.230789,0,0,-0.115138,-0.99335,300,0,1,0),
(@GOBJECT_GUID + 16,@GOBJECT_LOCK + 5,0,1,1,-11200,-1808.19,4.25283,6.13462,0,0,-0.074212,0.997243,300,0,1,0),
(@GOBJECT_GUID + 17,@GOBJECT_LOCK + 5,0,1,1,-11196.6,-1807.78,4.25195,4.72484,0,0,-0.70269,0.711496,300,0,1,0),
(@GOBJECT_GUID + 18,@GOBJECT_LOCK + 5,0,1,1,-11195.1,-1807.76,4.25195,4.72484,0,0,-0.70269,0.711496,300,0,1,0),
(@GOBJECT_GUID + 19,@GOBJECT_LOCK + 5,0,1,1,-11196.1,-1806.94,4.25184,2.14088,0,0,-0.877412,-0.479737,300,0,1,0),
(@GOBJECT_GUID + 20,@GOBJECT_LOCK + 5,0,1,1,-11195.9,-1808.24,4.29816,4.24182,0,0,-0.852464,0.522785,300,0,1,0),
(@GOBJECT_GUID + 21,@GOBJECT_LOCK + 4,0,1,1,-11245.3,-1781.44,4.33813,4.8596,0,0,-0.653193,0.757192,300,0,1,0),
(@GOBJECT_GUID + 22,@GOBJECT_LOCK + 4,0,1,1,-11245.8,-1780.98,4.32178,1.4117,0,0,-0.64868,-0.761061,300,0,1,0),
(@GOBJECT_GUID + 23,@GOBJECT_LOCK + 5,0,1,1,-11211.1,-1807.62,4.25233,4.17035,0,0,-0.870599,0.491993,300,0,1,0),
(@GOBJECT_GUID + 24,@GOBJECT_LOCK + 4,0,1,1,-11213.6,-1807.28,4.25218,1.59817,0,0,-0.716717,-0.697364,300,0,1,0),
(@GOBJECT_GUID + 25,@GOBJECT_LOCK + 5,0,1,1,-11213.7,-1808.16,4.2517,0.141248,0,0,-0.0705652,-0.997507,300,0,1,0),
(@GOBJECT_GUID + 26,@GOBJECT_LOCK + 5,0,1,1,-11244.9,-1805.2,4.32955,1.71801,0,0,-0.757193,-0.653192,300,0,1,0),
(@GOBJECT_GUID + 27,@GOBJECT_LOCK + 4,0,1,1,-11213.7,-1808.66,4.25238,0.121613,0,0,-0.0607693,-0.998152,300,0,1,0),
(@GOBJECT_GUID + 28,@GOBJECT_LOCK + 4,0,1,1,-11210.9,-1808.6,4.34506,3.40851,0,0,-0.991108,0.133064,300,0,1,0),
(@GOBJECT_GUID + 29,@GOBJECT_LOCK + 5,0,1,1,-11212.4,-1807.11,4.25175,5.749,0,0,-0.26393,0.964542,300,0,1,0),
(@GOBJECT_GUID + 30,@GOBJECT_LOCK + 5,0,1,1,-11245.2,-1799.84,4.32839,1.43526,0,0,-0.657601,-0.753366,300,0,1,0),
(@GOBJECT_GUID + 31,@GOBJECT_LOCK + 5,0,1,1,-11244.9,-1817.23,4.25486,1.04257,0,0,-0.497993,-0.867181,300,0,1,0),
(@GOBJECT_GUID + 32,@GOBJECT_LOCK + 5,0,1,1,-11246,-1781.79,4.30307,0.960094,0,0,-0.461821,-0.886973,300,0,1,0),
(@GOBJECT_GUID + 33,@GOBJECT_LOCK + 4,0,1,1,-11245,-1818.51,4.25262,5.98665,0,0,-0.147726,0.989028,300,0,1,0),
(@GOBJECT_GUID + 34,@GOBJECT_LOCK + 4,0,1,1,-11244.6,-1804.57,4.33561,6.15551,0,0,-0.0637952,0.997963,300,0,1,0),
(@GOBJECT_GUID + 35,@GOBJECT_LOCK + 5,0,1,1,-11178.1,-1786.57,4.31763,4.97505,0,0,-0.608418,0.793617,300,0,1,0),
(@GOBJECT_GUID + 36,@GOBJECT_LOCK + 4,0,1,1,-11178.2,-1785.87,4.3295,1.71565,0,0,-0.756423,-0.654083,300,0,1,0),
(@GOBJECT_GUID + 37,@GOBJECT_LOCK + 5,0,1,1,-11178.5,-1787.6,4.33518,4.55879,0,0,-0.759274,0.650771,300,0,1,0),
(@GOBJECT_GUID + 38,@GOBJECT_LOCK + 5,0,1,1,-11177.6,-1795.34,4.25228,4.78656,0,0,-0.680404,0.732837,300,0,1,0),
(@GOBJECT_GUID + 39,@GOBJECT_LOCK + 5,0,1,1,-11178,-1796.33,4.26114,4.33495,0,0,-0.827205,0.5619,300,0,1,0),
(@GOBJECT_GUID + 40,@GOBJECT_LOCK + 4,0,1,1,-11177.1,-1796.19,4.25252,1.00094,0,0,-0.479837,-0.877358,300,0,1,0),
(@GOBJECT_GUID + 41,@GOBJECT_LOCK + 5,0,1,1,-11178,-1805.37,4.33204,1.77063,0,0,-0.774116,-0.633044,300,0,1,0),
(@GOBJECT_GUID + 42,@GOBJECT_LOCK + 5,0,1,1,-11177.6,-1804.51,4.31591,1.91593,0,0,-0.818024,-0.575184,300,0,1,0),
(@GOBJECT_GUID + 43,@GOBJECT_LOCK + 5,0,1,1,-11206.1,-1819.71,4.25219,3.16472,0,0,-0.999933,0.011562,300,0,1,0),
(@GOBJECT_GUID + 44,@GOBJECT_LOCK + 5,0,1,1,-11207.2,-1819.65,4.25255,3.04298,0,0,-0.998785,-0.0492861,300,0,1,0),
(@GOBJECT_GUID + 45,@GOBJECT_LOCK + 5,0,1,1,-11206.7,-1819.23,4.32268,1.44862,0,0,-0.662619,-0.748956,300,0,1,0),
(@GOBJECT_GUID + 46,@GOBJECT_LOCK + 5,0,1,1,-11208,-1820.45,4.25241,2.98015,0,0,-0.996744,-0.0806347,300,0,1,0),
(@GOBJECT_GUID + 47,@GOBJECT_LOCK + 5,0,1,1,-11209,-1820.15,4.25208,2.50891,0,0,-0.95038,-0.311092,300,0,1,0),
(@GOBJECT_GUID + 48,@GOBJECT_LOCK + 4,0,1,1,-11208.3,-1819.2,4.25201,0.203765,0,0,-0.101706,-0.994815,300,0,1,0),
(@GOBJECT_GUID + 49,@GOBJECT_LOCK + 5,0,1,1,-11208.3,-1819.46,4.39414,1.82954,0,0,-0.792422,-0.609973,300,0,1,0),
(@GOBJECT_GUID + 50,181959,0,1,1,-11209.8,-1757.58,4.25257,2.08561,0,0,-0.86382,-0.5038,300,0,1,0),
(@GOBJECT_GUID + 51,181959,0,1,1,-11181.7,-1807.51,4.2813,3.19615,0,0,-0.999628,0.0272735,300,0,1,0),
(@GOBJECT_GUID + 52,181959,0,1,1,-11203.9,-1809.44,4.25135,4.59415,0,0,-0.74765,0.664093,300,0,1,0),
(@GOBJECT_GUID + 53,181959,0,1,1,-11229.5,-1774.29,4.25217,3.12153,0,0,-0.99995,-0.0100295,300,0,1,0),
(@GOBJECT_GUID + 54,181959,0,1,1,-11231.8,-1776.66,4.25295,1.68426,0,0,-0.746063,-0.665876,300,0,1,0),
(@GOBJECT_GUID + 55,181959,0,1,1,-11202.2,-1757.44,4.25195,3.12619,0,0,-0.99997,-0.0077014,300,0,1,0),
(@GOBJECT_GUID + 56,181959,0,1,1,-11222.2,-1758.36,4.25195,1.0064,0,0,-0.482231,-0.876044,300,0,1,0),
(@GOBJECT_GUID + 57,181959,0,1,1,-11230.6,-1758.52,4.25214,0.044287,0,0,-0.0221414,-0.999755,300,0,1,0),
(@GOBJECT_GUID + 58,181959,0,1,1,-11239.5,-1814.41,4.26083,3.11598,0,0,-0.999918,-0.0128044,300,0,1,0),
(@GOBJECT_GUID + 59,181959,0,1,1,-11239.2,-1800.99,4.34243,3.11598,0,0,-0.999918,-0.0128044,300,0,1,0),
(@GOBJECT_GUID + 60,181959,0,1,1,-11239.6,-1778.33,4.29893,3.11598,0,0,-0.999918,-0.0128044,300,0,1,0),
(@GOBJECT_GUID + 61,181959,0,1,1,-11183.6,-1799.38,4.27158,0.00187922,0,0,-0.000951535,-1,300,0,1,0),
(@GOBJECT_GUID + 62,181959,0,1,1,-11183.3,-1784.96,4.34472,3.06493,0,0,-0.999266,-0.0383205,300,0,1,0),
(@GOBJECT_GUID + 63,181959,0,1,1,-11192.5,-1808.45,4.25362,4.76218,0,0,-0.689284,0.724491,300,0,1,0),
(@GOBJECT_GUID + 64,181959,0,1,1,-11215.5,-1809.21,4.25294,4.7347,0,0,-0.699176,0.714949,300,0,1,0),
(@GOBJECT_GUID + 65,188225,0,1,1,-11212.2,-1808.12,4.25196,1.68299,0,0,-0.74564,-0.666349,300,0,1,0),
(@GOBJECT_GUID + 66,21680,0,1,1,-11071.8,-1561.28,27.218,5.35581,0,0,-0.447249,0.89441,300,0,1,0),
(@GOBJECT_GUID + 67, 192289, 0, 1, 1, -11229.9, -1764.1, 4.25198, 0.0445609, -0, -0, -0.0222782, -0.999752, 300, 0, 1, 0),
(@GOBJECT_GUID + 68, 192423, 0, 1, 1, -11201.8, -1762.96, 4.25153, 3.19163, -0, -0, -0.999687, 0.0250146, 300, 0, 1, 0),
(@GOBJECT_GUID + 69, 190960, 0, 1, 1, -11202, -1764.98, 4.25249, 3.27959, -0, -0, -0.997621, 0.0689426, 300, 0, 1, 0),
(@GOBJECT_GUID + 70, 191009, 0, 1, 1, -11229.7, -1767.21, 4.25203, 0.213408, -0, -0, -0.106502, -0.994313, 300, 0, 1, 0),
(@GOBJECT_GUID + 71, 195682, 0, 1, 1, -11193.6, -1813.65, 7.95612, 3.18151, -0, -0, -0.999801, 0.0199591, 300, 0, 1, 0),
(@GOBJECT_GUID + 72, @GOBJECT_LOCK + 6, 0, 1, 1, -11202.6, -1813.52, 7.10302, 4.76874, -0, -0, -0.686905, 0.726747, 300, 0, 1, 0),
(@GOBJECT_GUID + 73, @GOBJECT_LOCK + 6, 0, 1, 1, -11204.6, -1813.63, 7.10302, 4.76874, -0, -0, -0.686905, 0.726747, 300, 0, 1, 0),
(@GOBJECT_GUID + 74, @GOBJECT_LOCK + 6, 0, 1, 1, -11202.6, -1814.52, 7.10302, 4.76874, -0, -0, -0.686905, 0.726747, 300, 0, 1, 0),
(@GOBJECT_GUID + 75, @GOBJECT_LOCK + 6, 0, 1, 1, -11204.6, -1814.63, 7.10302, 4.76874, -0, -0, -0.686905, 0.726747, 300, 0, 1, 0),
(@GOBJECT_GUID + 76, 24388, 0, 1, 1, -11234.7, -1823.66, 4.25296, 1.56206, -0, -0, -0.704013, -0.710187, 300, 0, 1, 0),
(@GOBJECT_GUID + 77, 24388, 0, 1, 1, -11229.7, -1823.7, 4.25296, 1.56206, -0, -0, -0.704013, -0.710187, 300, 0, 1, 0),
(@GOBJECT_GUID + 78, 24388, 0, 1, 1, -11218.9, -1776.48, 4.25277, 4.7429, -0, -0, -0.696236, 0.717813, 300, 0, 1, 0),
(@GOBJECT_GUID + 79, 24388, 0, 1, 1, -11211.9, -1776.26, 4.25277, 4.74291, -0, -0, -0.696236, 0.717813, 300, 0, 1, 0),
(@GOBJECT_GUID + 80, 24388, 0, 1, 1, -11210.6, -1810.28, 7.97058, 1.60996, -0, -0, -0.720817, -0.693126, 300, 0, 1, 0),
(@GOBJECT_GUID + 81, 191030, 0, 1, 1, -11209.6, -1822.11, 4.25183, 0.0111008, -0, -0, -0.00555201, -0.999985, 300, 0, 1, 0),
(@GOBJECT_GUID + 82, 185436, 0, 1, 1, -11213.7, -1810.45, 7.9625, 5.47566, -0, -0, -0.392882, 0.919589, 300, 0, 1, 0),
(@GOBJECT_GUID + 83, 185436, 0, 1, 1, -11215.7, -1808.16, 4.25377, 2.69295, -0, -0, -0.974946, -0.222442, 300, 0, 1, 0),
(@GOBJECT_GUID + 84, 190897, 0, 1, 1, -11218.4, -1814.28, 4.25246, 1.58551, -0, -0, -0.712288, -0.701887, 300, 0, 1, 0);


-- Makhan
SET @ENTRY := @NPC_GUID + 14;
DELETE FROM `waypoints` WHERE entry = @ENTRY;
INSERT INTO `waypoints` VALUES
(@ENTRY,2,-11186,-1796.95,4.2519,NULL),
(@ENTRY,1,-11210.8,-1805,4.25227,NULL),
(@ENTRY,3,-11209.5,-1776.13,4.2527,NULL),
(@ENTRY,4,-11210.3,-1792.21,4.25,NULL);
 
-- Ma’khan SAI
SET @ENTRY := @NPC_GUEST + 1;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,11,0,100,0,0,0,0,0,53,0,@NPC_GUID + 14,1,0,0,0,0,0,0,0,0,0,0,0,"Ma’khan - On Respawn - Start Waypoint"),
(@ENTRY,0,1,0,40,0,100,0,1,@NPC_GUID + 14,0,0,54,300000,0,0,0,0,0,0,0,0,0,0,0,0,0,"Ma’khan - On Waypoint 1 Reached - Pause Waypoint"),
(@ENTRY,0,2,0,40,0,100,0,1,@NPC_GUID + 14,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Ma’khan - On Waypoint 1 Reached - Say Line 0"),
(@ENTRY,0,3,0,40,0,100,0,2,@NPC_GUID + 14,0,0,54,300000,0,0,0,0,0,0,0,0,0,0,0,0,0,"Ma’khan - On Waypoint 2 Reached - Pause Waypoint"),
(@ENTRY,0,4,0,40,0,100,0,2,@NPC_GUID + 14,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,"Ma’khan - On Waypoint 2 Reached - Say Line 1"),
(@ENTRY,0,5,0,40,0,100,0,3,@NPC_GUID + 14,0,0,54,300000,0,0,0,0,0,0,0,0,0,0,0,0,0,"Ma’khan - On Waypoint 3 Reached - Pause Waypoint"),
(@ENTRY,0,6,0,40,0,100,0,3,@NPC_GUID + 14,0,0,5,18,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ma’khan - On Waypoint 3 Reached - Play Emote 18"),
(@ENTRY,0,11,0,40,0,100,0,1,@NPC_GUID + 14,0,0,5,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ma’khan - On Waypoint 1 Reached - Play Emote 1"),
(@ENTRY,0,12,0,40,0,100,0,2,@NPC_GUID + 14,0,0,5,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ma’khan - On Waypoint 2 Reached - Play Emote 1"),
(@ENTRY,0,13,0,11,0,100,0,0,0,0,0,54,300000,0,0,0,0,0,0,0,0,0,0,0,0,0,"Ma’khan - On Respawn - Pause Waypoint");
 
DELETE FROM `creature_text` WHERE entry = @ENTRY;
INSERT INTO `creature_text` VALUES
(@ENTRY,0,0,'Dzis mi sie uda, stary!',12,0,0,0,0,0,0,''),
(@ENTRY,1,0,'To moj szczeliwy dzien, ziom.',12,0,0,0,0,0,0,'');
 
-- Karl Saggan
SET @ENTRY := @NPC_GUID + 18;
DELETE FROM waypoints WHERE entry = @ENTRY;
INSERT INTO waypoints(entry, pointid, position_x, position_y, position_z) VALUES  
(@ENTRY,1,-11197.7,-1804.97,4.25195),
(@ENTRY,2,-11197.7,-1805.8,4.25195),
(@ENTRY,3,-11185.8,-1789.93,4.31922),
(@ENTRY,4,-11202,-1776.18,4.25149),
(@ENTRY,5,-11204.8,-1759.65,4.25149),
(@ENTRY,6,-11206.79,-1775.71,4.251744);

-- Karl Saggan SAI
SET @ENTRY := @NPC_GUEST + 5;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,11,0,100,0,0,0,0,0,53,0,@NPC_GUID + 18,1,0,0,0,0,0,0,0,0,0,0,0,"Karl Saggan - On Respawn - Start Waypoint"),
(@ENTRY,0,1,0,40,0,100,0,2,@NPC_GUID + 18,0,0,54,300000,0,0,0,0,0,0,0,0,0,0,0,0,0,"Karl Saggan - On Waypoint 2 Reached - Pause Waypoint"),
(@ENTRY,0,2,0,40,0,100,0,3,@NPC_GUID + 18,0,0,54,300000,0,0,0,0,0,0,0,0,0,0,0,0,0,"Karl Saggan - On Waypoint 3 Reached - Pause Waypoint"),
(@ENTRY,0,3,0,40,0,100,0,5,@NPC_GUID + 18,0,0,54,300000,0,0,0,0,0,0,0,0,0,0,0,0,0,"Karl Saggan - On Waypoint 5 Reached - Pause Waypoint"),
(@ENTRY,0,4,0,40,0,100,0,2,@NPC_GUID + 18,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Karl Saggan - On Waypoint 2 Reached - Say Line 0"),
(@ENTRY,0,5,0,40,0,100,0,3,@NPC_GUID + 18,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,"Karl Saggan - On Waypoint 3 Reached - Say Line 1"),
(@ENTRY,0,6,0,40,0,100,0,5,@NPC_GUID + 18,0,0,5,11,0,0,0,0,0,1,0,0,0,0,0,0,0,"Karl Saggan - On Waypoint 5 Reached - Play Emote 11"),
(@ENTRY,0,7,0,40,0,100,0,2,@NPC_GUID + 18,0,0,5,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Karl Saggan - On Waypoint 2 Reached - Play Emote 1"),
(@ENTRY,0,8,0,40,0,100,0,3,@NPC_GUID + 18,0,0,5,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Karl Saggan - On Waypoint 3 Reached - Play Emote 1"),
(@ENTRY,0,9,0,11,0,100,0,0,0,0,0,54,900000,0,0,0,0,0,0,0,0,0,0,0,0,0,"");
 
DELETE FROM `creature_text` WHERE entry = @ENTRY;
INSERT INTO `creature_text` VALUES
(@ENTRY,0,0,'Czas zmienic swoje zycie!',12,0,0,0,0,0,0,''),
(@ENTRY,1,0,'Piekne stworzonka.',12,0,0,0,0,0,0,'');
 
-- Derek
SET @ENTRY := @NPC_GUID + 17;
DELETE FROM waypoints WHERE entry = @ENTRY;
INSERT INTO waypoints(entry, pointid, position_x, position_y, position_z) VALUES
(@ENTRY,1,-11238.8,-1785.15,4.25169),
(@ENTRY,2,-11235.2,-1798.26,4.32745),
(@ENTRY,3,-11237.1,-1798.56,4.33498),
(@ENTRY,4,-11233.4,-1816.7,4.25275),
(@ENTRY,5,-11236,-1817.48,4.25275),
(@ENTRY,6,-11233.5,-1784.71,4.25139);
 
-- Derek SAI
SET @ENTRY := @NPC_GUEST + 4;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,11,0,100,0,0,0,0,0,53,0,@NPC_GUID + 17,1,0,0,0,0,0,0,0,0,0,0,0,"Derek - On Respawn - Start Waypoint"),
(@ENTRY,0,1,0,40,0,100,0,1,@NPC_GUID + 17,0,0,54,300000,0,0,0,0,0,0,0,0,0,0,0,0,0,"Derek - On Waypoint 1 Reached - Pause Waypoint"),
(@ENTRY,0,2,0,40,0,100,0,3,@NPC_GUID + 17,0,0,54,300000,0,0,0,0,0,0,0,0,0,0,0,0,0,"Derek - On Waypoint 3 Reached - Pause Waypoint"),
(@ENTRY,0,3,0,40,0,100,0,5,@NPC_GUID + 17,0,0,54,300000,0,0,0,0,0,0,0,0,0,0,0,0,0,"Derek - On Waypoint 5 Reached - Pause Waypoint"),
(@ENTRY,0,4,0,40,0,100,0,1,@NPC_GUID + 17,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Derek - On Waypoint 1 Reached - Say Line 0"),
(@ENTRY,0,5,0,40,0,100,0,3,@NPC_GUID + 17,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,"Derek - On Waypoint 3 Reached - Say Line 1"),
(@ENTRY,0,6,0,40,0,100,0,5,@NPC_GUID + 17,0,0,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,"Derek - On Waypoint 5 Reached - Say Line 2"),
(@ENTRY,0,7,0,40,0,100,0,1,@NPC_GUID + 17,0,0,5,1,0,0,0,0,0,0,0,0,0,0,0,0,0,"Derek - On Waypoint 1 Reached - Play Emote 1"),
(@ENTRY,0,8,0,40,0,100,0,3,@NPC_GUID + 17,0,0,5,1,0,0,0,0,0,0,0,0,0,0,0,0,0,"Derek - On Waypoint 3 Reached - Play Emote 1"),
(@ENTRY,0,9,0,40,0,100,0,5,@NPC_GUID + 17,0,0,5,1,0,0,0,0,0,0,0,0,0,0,0,0,0,"Derek - On Waypoint 5 Reached - Play Emote 1"),
(@ENTRY,0,10,0,11,0,100,0,0,0,0,0,54,600000,0,0,0,0,0,0,0,0,0,0,0,0,0,"Derek - On Respawn - Pause Waypoint");
 
DELETE FROM `creature_text` WHERE entry = @ENTRY;
INSERT INTO `creature_text` VALUES
(@ENTRY,0,0,'Piekny wierzchowiec. Moze kiedys mi sie uda?',12,0,0,0,0,0,0,''),
(@ENTRY,1,0,'Wspanialy okaz! Pewnie trudno bylo go zlapac.',12,0,0,0,0,0,0,''),
(@ENTRY,2,0,'Czyli jednak cos z Ahn\'Qiraj przetrwalo.',12,0,0,0,0,0,0,'');
 
-- Martha Edwards SAI
SET @ENTRY := @NPC_GUEST + 2;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,0,4000,4000,8000,8000,5,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Martha Edwards - Out of Combat - Play Emote 1");
 
-- Narak Longhorn SAI
SET @ENTRY := @NPC_GUEST;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,0,0,0,8000,8000,5,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Narak Longhorn - Out of Combat - Play Emote 1");
 
-- Karn Rockwell SAI
SET @ENTRY := @NPC_CAVE + 19;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,0,0,0,420000,420000,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Karn Rockwell - Out of Combat - Say Line 0");
 
DELETE from npc_vendor WHERE entry = @ENTRY;
INSERT INTO `npc_vendor` VALUES (@ENTRY,0,33443,0,0,0),(@ENTRY,0,33444,0,0,0),(@ENTRY,0,33445,0,0,0),(@ENTRY,0,33449,0,0,0),(@ENTRY,0,33454,0,0,0),(@ENTRY,0,35950,0,0,0),(@ENTRY,0,35952,0,0,0),(@ENTRY,0,35953,0,0,0),(@ENTRY,0,35954,0,0,0),(@ENTRY,0,40035,0,0,0),(@ENTRY,0,40036,0,0,0),(@ENTRY,0,40042,0,0,0);
 
DELETE FROM `creature_addon` WHERE guid = @NPC_GUID + 28;
INSERT INTO `creature_addon` VALUES (@NPC_GUID + 28,@NPC_GUID + 28,0,0,0,0,NULL);
 
DELETE FROM `waypoint_data` WHERE id = @NPC_GUID + 28;
INSERT INTO `waypoint_data` VALUES
(@NPC_GUID + 28,1,-11226.4,-1765.23,4.2514,0,0,0,0,100,0),
(@NPC_GUID + 28,2,-11226,-1777.57,4.2514,0,0,0,0,100,0),
(@NPC_GUID + 28,3,-11229.7,-1784.92,4.2514,0,0,0,0,100,0),
(@NPC_GUID + 28,4,-11231.3,-1809.64,4.28996,0,0,0,0,100,0),
(@NPC_GUID + 28,5,-11224.2,-1813.21,4.25179,0,0,0,0,100,0),
(@NPC_GUID + 28,6,-11219.8,-1796.03,4.26302,0,0,0,0,100,0),
(@NPC_GUID + 28,7,-11198.7,-1793.83,4.25261,0,0,0,0,100,0),
(@NPC_GUID + 28,8,-11192,-1782.45,4.29129,0,0,0,0,100,0),
(@NPC_GUID + 28,9,-11214,-1779.73,4.25181,0,0,0,0,100,0),
(@NPC_GUID + 28,10,-11226.6,-1776.64,4.25181,0,0,0,0,100,0);
 
DELETE FROM `creature_text` WHERE entry = @ENTRY;
INSERT INTO `creature_text` VALUES
(@ENTRY,0,1,'Zimne napoje!',12,0,0,0,0,0,0,''),
(@ENTRY,0,2,'Przekaski w dobrych cenach!',12,0,0,0,0,0,0,''),
(@ENTRY,0,3,'Granie o suchym pysku przynosi pecha!',12,0,0,0,0,0,0,''),
(@ENTRY,0,4,'Zapraszam na dobre napoje i wspaniale przekaski!',12,0,0,0,0,0,0,''),
(@ENTRY,0,5,'Uwazajcie na dziure! Niby magowie to zabezpieczyli, ze sie nie zabijesz, ale ja magom nie ufam.',12,0,0,0,0,0,0,'');
 
-- Spectral Tiger Cub SAI
SET @ENTRY := @NPC_CAVE + 24;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,0,0,0,900000,900000,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Npc - Event - Action (phase) (dungeon difficulty)");
 
-- Crypt Mage SAI
SET @ENTRY := @NPC_CAVE + 32;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY, 0, 0, 0, 25, 0, 100, 1, 0, 0, 0, 0, 11, 32783, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Crypt Mage - On Reset - Cast Arcane Channeling'),
(@ENTRY, 0, 1, 0, 11, 0, 100, 0, 0, 0, 0, 0, 48, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Crypt Mage - On Spawn - Set Active'),
(@ENTRY, 0, 2, 3, 11, 0, 100, 257, 0, 0, 0, 0, 150, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, -276.43, 1529.1, 0, 0, 'Crypt Mage - On Spawn - Load Grid'),
(@ENTRY, 0, 3, 4, 61, 0, 100, 0, 0, 0, 0, 0, 150, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, -172.35, 1513.68, 0, 0, 'Crypt Mage - On Spawn - Load Grid'),
(@ENTRY, 0, 4, 5, 61, 0, 100, 0, 0, 0, 0, 0, 150, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, -99.78, 1892.91, 0, 0, 'Crypt Mage - On Spawn - Load Grid'),
(@ENTRY, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 150, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, -418.51, 1828.48, 0, 0, 'Crypt Mage - On Spawn - Load Grid');

DELETE FROM `creature_text` WHERE entry = @ENTRY;
INSERT INTO `creature_text` VALUES (@ENTRY,0,0,'Spectral Tiger Cub cries to his mommy.',16,0,0,0,0,0,0,'');

DELETE FROM `trinity_string` where `entry` IN ('11010', '11011', '11012', '11013');
INSERT INTO `trinity_string` (`entry`, `content_default`) VALUES ('11010', '|cffff0000[Loteria]: Losowanie zakonczone! Lacznie losow bylo: %u. Zwycieskie liczby sa nastepujace: %s. Pula nagrod wynosila %u %s i nikt nie wygral glownej wygranej.|r');
INSERT INTO `trinity_string` (`entry`, `content_default`) VALUES ('11011', '|cffff0000[Loteria]: Losowanie zakonczone! Lacznie losow bylo: %u. Zwycieskie liczby sa nastepujace: %s.  %s trafil na szczesliwe liczby i wygral %u %s! Gratulacje!|r');
INSERT INTO `trinity_string` (`entry`, `content_default`) VALUES ('11012', '|cffff0000[Loteria]: Losowanie zakonczone! Lacznie losow bylo: %u. Zwycieskie liczby sa nastepujace: %s.  %u graczy trafilo na szczesliwe liczby i wygrywaja %u %s. Gratulacje!|r');
INSERT INTO `trinity_string` (`entry`, `content_default`) VALUES ('11013', '|cffff0000[Loteria]: Rozpoczynam losowanie %s|r');

REPLACE INTO `game_event` (`eventEntry`, `start_time`, `end_time`, `occurence`, `length`, `holiday`, `description`, `world_event`) VALUES 
(132, '2017-08-17 20:00:00', '2030-12-31 06:00:00', 1440, 1, 0, 'Lottery Gold', 0);
REPLACE INTO `game_event` (`eventEntry`, `start_time`, `end_time`, `occurence`, `length`, `holiday`, `description`, `world_event`) VALUES 
(133, '2017-08-17 20:05:00', '2020-12-31 06:00:00', 1440, 1, 0, 'Lottery Sunwell Coins', 0);