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
DELETE FROM creature_template WHERE entry = @NPC_CAVE + 34;
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
(@NPC_CAVE + 25, 0, 0, 0, 0, 0, 18785, 0, 0, 0, 'Babe', '', '', 0, 69, 69, 0, 35, 1, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_female_emote', 12340),
(@NPC_CAVE + 26, 0, 0, 0, 0, 0, 18794, 0, 0, 0, 'Babe', '', '', 0, 69, 69, 0, 35, 1, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_female_emote', 12340),
(@NPC_CAVE + 27, 0, 0, 0, 0, 0, 18802, 0, 0, 0, 'Babe', '', '', 0, 69, 69, 0, 35, 1, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_female_emote', 12340),
(@NPC_CAVE + 28, 0, 0, 0, 0, 0, 14413, 0, 0, 0, 'Piromancer Maz’grum', '', '', 0, 80, 80, 0, 35, 1, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_burn_flag_horde', 12340),
(@NPC_CAVE + 29, 0, 0, 0, 0, 0, 1505, 0, 0, 0, 'Piromancer Wakarc\n', '', '', 0, 80, 80, 0, 35, 1, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_burn_flag_alliance', 12340),
(@NPC_CAVE + 30, 0, 0, 0, 0, 0, 20388, 0, 0, 0, 'Krokuun', '', '', 0, 80, 80, 0, 35, 1, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_gambler', 12340),
(@NPC_CAVE + 31, 0, 0, 0, 0, 0, 18668, 0, 0, 0, 'Edar', 'Ghost from the Well', '', 0, 80, 80, 0, 35, 1, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_wpierdalator', 12340),
(@NPC_CAVE + 32, 0, 0, 0, 0, 0, 28934, 0, 0, 0, 'Crypt Mage', '', '', 0, 80, 80, 0, 35, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, '', 12340),
(@NPC_CAVE + 33, 0, 0, 0, 0, 0, 25624, 0, 0, 0, 'Cyrulik Jack', 'Fryzjer', '', 60006, 80, 80, 0, 35, 1, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, '', 12340),
(40165,0,0,0,0,0,31803,31803,0,0,'Blazing Hippogryph','','',0,80,80,2,35,0,1,1.14286,0.85,0,0,0,0,0,1,2000,2000,1,0,2048,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,4,1,1,1,1,0,0,0,0,0,0,0,140,1,0,0,'',12340),
(@NPC_CAVE + 34, 0, 0, 0, 0, 0, 26068, 0, 0, 0, 'Seet', 'The Crypt Stalker', '', 0, 80, 80, 0, 35, 1, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_crypt_tele', 12340),
(@NPC_GUEST + 6, 0, 0, 0, 0, 0, 18217, 18217, 18217, 18217, 'Menora', 'Lottery Coins Seller', '', 0, 70, 70, 0, 35, 3, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 2000, 2000, 1, 2, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 5, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 'npc_lottery_coins', 12340);
 
DELETE FROM `creature` WHERE `id` = @NPC_CAVE + 1;
DELETE FROM `creature` WHERE `id` = @NPC_CAVE + 2;
DELETE FROM `creature` WHERE `id` = @NPC_CAVE + 3;
DELETE FROM `creature` WHERE `id` = @NPC_CAVE + 4;
DELETE FROM `creature` WHERE `id` = @NPC_CAVE + 5;
DELETE FROM `creature` WHERE `id` = @NPC_CAVE + 6;
DELETE FROM `creature` WHERE `id` = @NPC_CAVE + 7;
DELETE FROM `creature` WHERE `id` = @NPC_CAVE + 8;
DELETE FROM `creature` WHERE `id` = @NPC_CAVE + 9;
DELETE FROM `creature` WHERE `id` = @NPC_CAVE + 10;
DELETE FROM `creature` WHERE `id` = @NPC_CAVE + 26;
DELETE FROM `creature` WHERE `id` = @NPC_CAVE + 30;
DELETE FROM `creature` WHERE `id` = @NPC_GUEST + 6;
SET @NPC_GUID := (SELECT MAX(guid) from creature) +100;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
-- (@NPC_GUID + 2, @NPC_CAVE + 3  , 1, 1, 1, 0, 0, 1271.075562, -4350.240234, 33.095955, 0.406819, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
-- (@NPC_GUID + 3, @NPC_CAVE + 4  , 1, 1, 1, 0, 0, 1269.409302, -4341.032715, 33.095955, 0.146067, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 4, @NPC_CAVE + 5  , 1, 1, 1, 0, 0, 1282.338379, -4356.874023, 33.095955, 1.077550, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 5, @NPC_CAVE + 6  , 1, 1, 1, 0, 0, 1292.581787, -4358.854004, 33.098709, 1.707439, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 6, @NPC_CAVE + 7  , 1, 1, 1, 0, 0, 1299.019531, -4354.079102, 33.098709, 2.089143, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 7, @NPC_CAVE + 8  , 1, 1, 1, 0, 0, 1269.673828, -4333.294922, 33.097439, 6.101744, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 8, @NPC_CAVE + 9  , 1, 1, 1, 0, 0, 1274.287720, -4323.011230, 33.097618, 5.347761, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 9, @NPC_GUEST + 6, 1, 1, 1, 0, 0, 1313.885864, -4327.262207, 32.360111, 4.713160, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 11, @NPC_CAVE + 26, 1, 1, 1, 0, 0, 1296.231079, -4326.210938, 33.096249, 4.194011, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 12, @NPC_CAVE + 30, 1, 1, 1, 0, 0, 1319.505493,-4369.537109,27.801524,5.59, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
-- (@NPC_GUID + 14, @NPC_CAVE + 3  , 0, 1, 1, 0, 0, -9060.568359,380.749146,93.531425,4.09, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
-- (@NPC_GUID + 15, @NPC_CAVE + 4  , 0, 1, 1, 0, 0, -9048.838867,367.262146,93.026871,4.12, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 16, @NPC_CAVE + 5  , 0, 1, 1, 0, 0, -9081.796875,371.080536,92.597969,4.975849, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 17, @NPC_CAVE + 6  , 0, 1, 1, 0, 0, -9072.165039,387.027924,92.702354,4.474762, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 18, @NPC_CAVE + 7  , 0, 1, 1, 0, 0, -9085.712891,356.640594,93.513451,0.53, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 19, @NPC_CAVE + 8  , 0, 1, 1, 0, 0, -9070.969727,333.637756,93.708603,1.01, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 20, @NPC_CAVE + 9  , 0, 1, 1, 0, 0, 1274.287720, -4323.011230, 33.097618, 5.347761, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 21, @NPC_GUEST + 6, 0, 1, 1, 0, 0, -9047.546875, 346.003296, 94.308990, 2.995360, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 23, @NPC_CAVE + 26, 0, 1, 1, 0, 0, -9082.175781, 342.077118, 93.139084, 0.642309, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 24, @NPC_CAVE + 30, 0, 1, 1, 0, 0, -9053.829102, 336.000305, 94.319519, 2.004975, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 25, @NPC_CAVE + 30, 571, 1, 1, 0, 0, 5779.993652, 584.738647, 609.157898, 1.196243, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 26, @NPC_CAVE + 9, 0, 1, 1, 0, 0, -9045.083008, 355.165070, 94.293762, 2.945132, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 27, @NPC_CAVE + 10, 1, 1, 1, 0, 0, 1290.501343,-4318.093750,33.097664,4.234, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 28, @NPC_CAVE + 10, 0, 1, 1, 0, 0, -9091.496094,366.945160,92.440399,6.09, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 29, 91021, 1, 1, 1, 0, 0, 1291.234375,-4319.007324,33.097664,2.678045, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 30, 91021, 0, 1, 1, 0, 0, -9091.426758,368.214874,92.359634,4.85, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 31, 91020, 1, 1, 1, 0, 0, 1290.149658,-4318.773438,33.097664,4.321, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 32, 91020, 0, 1, 1, 0, 0, -9091.538086,365.572479,92.603073,2.78, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 33, 91023, 1, 1, 1, 0, 0, 1289.103882,-4317.983887,33.097664,4.467966, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 34, 91023, 0, 1, 1, 0, 0, -9092.047852,364.835663,92.661385,1.105007, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 35, 91022, 1, 1, 1, 0, 0, 1289.198608,-4320.331055,33.097664,0.959, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 36, 91022, 0, 1, 1, 0, 0, -9090.348633,369.422455,92.305275,4.05, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 37, 91024, 1, 1, 1, 0, 0, 1281.943848,-4353.754395,33.097664,4.99, 300, 10, 0, 21760, 0, 0, 0, 0, 0),
(@NPC_GUID + 38, 91024, 0, 1, 1, 0, 0, -9083.075195,369.661316,92.584457,0.731157, 300, 10, 0, 21760, 0, 0, 0, 0, 0);



DELETE FROM `creature_template_addon` WHERE `entry` = @NPC_CAVE + 5;
DELETE FROM `creature_template_addon` WHERE `entry` = @NPC_CAVE + 6;
DELETE FROM `creature_template_addon` WHERE `entry` = @NPC_CAVE + 7;
DELETE FROM `creature_template_addon` WHERE `entry` = @NPC_CAVE + 8;
DELETE FROM `creature_template_addon` WHERE `entry` = @NPC_CAVE + 9;

INSERT INTO `creature_template_addon`(`entry`, `auras`) VALUES
(@NPC_CAVE + 5, "42777"),
(@NPC_CAVE + 6, "25863"),
(@NPC_CAVE + 7, "31700"),
(@NPC_CAVE + 8, "74854"),
(@NPC_CAVE + 9, "75617");

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
(@TEXT_ID, 'Nobody visited me for so long... I am Edar and I am a ghost.  I was going to Karazhan with my friends and then... Nevermind. Do you want to see a secret place? Yes, I am dead, but the dead can gamble too!', 'Nobody visited me for so long... I am Edar and I am a ghost.  I was going to Karazhan with my friends and then... Nevermind. Do you want to see a secret place? Yes, I am dead, but the dead can gamble too!', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+1, 'Enjoy! But... don\'t go too far. If you want I can take you under Karazhan.', 'Enjoy! But... don\'t go too far. If you want I can take you under Karazhan.', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+2, 'Tha Gambler\'s Den was established not so long ago. Peter was the first one and other outcasts joined him. It\'s hard to find this place, but it\'s still popular. You can win a lot of things here! Or lose everything. I play from time to time, just for fun.', 'Tha Gambler\'s Den was established not so long ago. Peter was the first one and other outcasts joined him. It\'s hard to find this place, but it\'s still popular. You can win a lot of things here! Or lose everything. I play from time to time, just for fun.', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+3, 'Don\'t bet too much!', 'Don\'t bet too much!', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+4, 'Dat a nice place, mon. Winnin da mounts... I be makin it, mon! Da mojo be strong wit me!', 'Dat a nice place, mon. Winnin da mounts... I be makin it, mon! Da mojo be strong wit me!', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+5, 'What do you want?', 'What do you want?', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+6, 'Leave me alone.', 'Leave me alone.', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+7, 'Did you win anything yet?', 'Did you win anything yet?', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+8, 'The stars say that I will have luck today.', 'The stars say that I will have luck today.', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+9, 'Playing or talking?', 'Playing or talking?', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+10, 'Are you sure you want to do that?', 'Are you sure you want to do that?', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+11, 'If you make it, you will leave this place on the back of this tiger.', 'If you make it, you will leave this place on the back of this tiger.', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+12, 'This is quite risky...', 'This is quite risky...', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+13, 'Look at this! Beautiful.', 'Look at this! Beautiful.', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+14, 'Are you brave enough to ride a hippogryph?', 'Are you brave enough to ride a hippogryph?', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+15, 'A truly celestial steed!', 'A truly celestial steed!', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+16, 'Sometimes you need to read between the verses. Do you want to try your luck and win these rare pets?', 'Sometimes you need to read between the verses. Do you want to try your luck and win these rare pets?', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+17, 'Try again.', 'Try again.', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+18, 'Congratulations! You have won.', 'Congratulations! You have won.', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+19, 'Hello! I am responsible for selling Lottery Coins necessary for playing for mounts, pets, gold and Sunwell Coins. Want to buy them?', 'Hello! I am responsible for selling Lottery Coins necessary for playing for mounts, pets, gold and Sunwell Coins. Want to buy them?', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+20, 'Anything else?', 'Anything else?', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+21, 'How much do you want to buy?', 'How much do you want to buy?', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+22, 'Hello, handsome... Christmas came earlier... What do you need?', 'Hello, handsome... Christmas came earlier... What do you need?', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+23, 'I am exploring these crypts. It is not safe, but I can show them to you. For a price.', 'I am exploring these crypts. It is not safe, but I can show them to you. For a price.', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+24, 'If you want to fight and to earn some money, I am the right guy. For how much do you want to fight?', 'If you want to fight and to earn some money, I am the right guy. For how much do you want to fight?', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+25, 'If you set up the bid and challenge somebody to duel, you will fight for your stake. If your enemy challenges you, you will fight for his stake.', 'If you set up the bid and challenge somebody to duel, you will fight for your stake. If your enemy challenges you, you will fight for his stake.', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+26, 'Hello, beautiful... Christmas came earlier... What do you need?', 'Hello, beautiful... Christmas came earlier... What do you need?', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+27, 'Hello, handsome... Christmas came earlier... What do you need?', 'Hello, handsome... Christmas came earlier... What do you need?', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+28, 'This filth should have rainbow colors! We should burn it!', 'This filth should have rainbow colors! We should burn it!', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+29, 'This smell... This flag... Only fire can deal with that!!\r\n', 'This smell... This flag... Only fire can deal with that!!\r\n', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+30, 'I am barber Jack.', 'I am barber Jack.', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340),
(@TEXT_ID+31, 'Are you lost?', 'Are you lost?', 0, 1, 0, 1, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, 12340);


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




DELETE FROM `trinity_string` where `entry` IN ('11010', '11011', '11012', '11013');
INSERT INTO `trinity_string` (`entry`, `content_default`) VALUES ('11010', '|cffff0000[Loteria]: Losowanie zakonczone! Lacznie losow bylo: %u. Zwycieskie liczby sa nastepujace: %s. Pula nagrod wynosila %u %s i nikt nie wygral glownej wygranej.|r');
INSERT INTO `trinity_string` (`entry`, `content_default`) VALUES ('11011', '|cffff0000[Loteria]: Losowanie zakonczone! Lacznie losow bylo: %u. Zwycieskie liczby sa nastepujace: %s.  %s trafil na szczesliwe liczby i wygral %u %s! Gratulacje!|r');
INSERT INTO `trinity_string` (`entry`, `content_default`) VALUES ('11012', '|cffff0000[Loteria]: Losowanie zakonczone! Lacznie losow bylo: %u. Zwycieskie liczby sa nastepujace: %s.  %u graczy trafilo na szczesliwe liczby i wygrywaja %u %s. Gratulacje!|r');
INSERT INTO `trinity_string` (`entry`, `content_default`) VALUES ('11013', '|cffff0000[Loteria]: Rozpoczynam losowanie %s|r');


REPLACE INTO `game_event` (`eventEntry`, `start_time`, `end_time`, `occurence`, `length`, `holiday`, `description`, `world_event`) VALUES 
(132, '2017-08-13 20:00:00', '2017-08-13 20:00:00', 10080, 1, 0, 'Lottery Gold', 0);
REPLACE INTO `game_event` (`eventEntry`, `start_time`, `end_time`, `occurence`, `length`, `holiday`, `description`, `world_event`) VALUES 
(133, '2017-08-13 20:00:00', '2017-08-13 20:00:00', 10080, 1, 0, 'Lottery Sunwell Coins', 0);