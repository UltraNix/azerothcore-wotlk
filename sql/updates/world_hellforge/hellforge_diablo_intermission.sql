SET @ENTRY := 261000;
DELETE FROM `creature_template` WHERE `entry` BETWEEN @ENTRY AND @ENTRY + 23;
INSERT INTO `creature_template` VALUES 
(@ENTRY,0,0,0,0,0,15945,0,0,0,'Soul of Kel\'Thuzad','',NULL,0,83,83,2,21,0,1.1,1.14286,1,3,496,674,0,783,35,2000,0,2,0,2048,8,0,0,0,0,0,365,529,98,6,76,15990,0,0,0,0,0,200,100,0,0,0,0,0,0,0,0,0,0,0,1002755,1457838,'',0,3,1,375,600,1,0,0,0,0,0,0,0,0,1,617299839,2097153,'boss_hellforge_diablo_kelthuzad',12340),
(@ENTRY + 1,0,0,0,0,0,30890,0,0,0,'Ice Tomb','',NULL,0,83,83,2,21,0,1.1,1.14286,1,3,496,674,0,783,35,2000,0,2,0,2048,8,0,0,0,0,0,365,529,98,6,76,15990,0,0,0,0,0,200,100,0,0,0,0,0,0,0,0,0,0,0,1002755,1457838,'',0,3,1,375,600,1,0,0,0,0,0,0,0,0,1,617299839,2097153,'npc_hellforge_ice_tomb',12340),
(@ENTRY + 2,0,0,0,0,0,16586,0,0,0,'Soul of Guardian of Icecrown',NULL,NULL,0,80,80,2,21,0,1.25,1.42858,1,1,422,586,0,642,7.5,1250,1650,1,0,2048,8,0,0,0,0,0,345,509,103,6,72,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,3,1,200,1,1,0,0,0,0,0,0,0,174,1,617299839,0,'boss_hellforge_diablo_kelthuzad_minion',12340),
(@ENTRY + 3,0,0,0,0,0,8570,0,0,0,'Soul of Onyxia','','',0,83,83,2,103,0,1,1.29,1,3,375,507,0,805,70,1500,1800,1,64,2048,8,0,0,0,0,0,371,535,135,2,108,10184,0,10184,0,0,100,0,0,0,0,0,0,0,0,0,0,0,0,0,93755,122438,'',1,3,1,350,1,0.996334,0,18705,0,0,0,0,0,0,1,650854271,2097409,'boss_hellforge_diablo_onyxia',11723),
(@ENTRY + 4,0,0,0,0,0,30346,0,0,0,'Soul of Onyxian Drake','',NULL,0,83,83,0,103,0,1.2,1.14286,1,1,2,2,0,24,7.5,2000,2000,1,0,2048,0,0,0,0,0,0,1,1,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,3,1,30,1,1,0,0,0,0,0,0,0,0,1,0,0,'npc_hellforge_diablo_onyxian_drake',12340),
(@ENTRY + 5,0,35615,35616,0,0,29268,0,0,0,'Soul of Anub\'arak','','',0,83,83,2,14,0,1,1.3,1,3,1200,1300,0,805,50,0,0,1,0,2048,8,0,0,0,0,0,371,535,135,6,108,34564,0,70214,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,569703,569703,'',0,3,1,300,1,1,0,0,0,0,0,0,0,191,1,650854271,2097161,'boss_hellforge_diablo_anubarak',12340),
(@ENTRY + 6,0,0,0,0,0,11686,0,0,0,'Permafrost trigger','','',0,79,80,2,1925,0,1,1.14286,1,0,422,586,0,0,1,0,0,1,0,2048,8,0,0,0,0,0,345,509,103,8,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,5,1,0.238095,1,1,0,0,0,0,0,0,0,721,0,0,0,'boss_hellforge_diablo_anubarak_permafrost',12340),
(@ENTRY + 7,0,0,0,0,0,169,11686,0,0,'Impale Target','','',0,70,70,2,114,0,1,1.14286,1,0,252,357,0,304,1,2000,2000,1,33685508,2048,0,0,0,0,0,0,215,320,44,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,3,1,1.35,1,1,0,0,0,0,0,0,0,0,1,0,130,'boss_hellforge_diablo_anubarak_impale_target',12340),
(@ENTRY + 8,0,0,0,0,0,30721,0,0,0,'Soul of The Lich King','','',0,83,83,2,974,0,2,1.71429,1,3,9000,10000,0,300,6,1500,0,1,512,2048,0,0,0,0,0,0,1,1,0,6,268435564,36597,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1300000,1500000,'',0,3,1,1250,500,1,0,0,0,0,0,0,0,169,1,650854271,2097161,'boss_hellforge_diablo_lichking',12340),
(@ENTRY + 9,0,0,0,0,0,25452,0,0,0,'Soul of Val\'kyr Shadowguard','','',0,80,80,2,14,0,1,0.7,1,3,0,0,0,0,1,2000,2000,1,514,2048,0,0,0,0,0,0,0,0,0,6,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,532,0,0,'',0,4,0,35.7143,500,1,0,0,0,0,0,0,0,741,1,583742335,2097152,'npc_hellforge_diablo_valkyr_shadowguard',12340),
(@ENTRY + 10,0,0,0,0,0,11686,0,0,0,'Frostmourne','','',0,83,83,2,974,0,2,1.71429,1,3,9000,10000,0,300,6,1500,0,1,512,2048,0,0,0,0,0,0,1,1,0,6,268435564,36597,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1300000,1500000,'',0,3,1,1250,500,1,0,0,0,0,0,0,0,169,1,650854271,2097161,'npc_hellforge_diablo_frostmourne',12340),
(@ENTRY + 11,0,0,0,0,0,17519,11686,0,0,'Soul of Yogg-Saron',NULL,NULL,0,80,80,0,114,0,1,1.14286,1,0,104,138,0,252,1,2000,2000,1,33587968,2048,0,0,0,0,0,0,72,106,26,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,4,1,1.35,1,1,0,0,0,0,0,0,0,0,1,0,130,'boss_hellforge_diablo_yogg',12340),
(@ENTRY + 12,0,0,0,0,0,28815,0,0,0,'Constrictor Tentacle','','',0,82,82,2,16,0,1,1.14286,1,1,488,642,0,782,7.5,2000,2000,1,0,2048,0,0,0,0,0,0,363,521,121,10,72,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,385,0,0,'',0,3,1,1.48357,1,1,0,0,0,0,0,0,0,401,1,650854271,2097152,'boss_hellforge_diablo_yogg_constrictor_tentacle',12340),
(@ENTRY + 13,0,0,0,0,0,17519,11686,0,0,'Yogg Saron Shadowcrash caster',NULL,NULL,0,80,80,0,114,0,1,1.14286,1,0,104,138,0,252,1,2000,2000,1,33587968,2048,0,0,0,0,0,0,72,106,26,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,4,1,1.35,1,1,0,0,0,0,0,0,0,0,1,0,130,'boss_hellforge_diablo_yogg_shadowcrash_caster',12340),
(@ENTRY + 14,0,0,0,0,0,17519,11686,0,0,'Yogg Saron Shadowcrash target',NULL,NULL,0,80,80,0,114,0,1,1.14286,1,0,104,138,0,252,1,2000,2000,1,33587968,2048,0,0,0,0,0,0,72,106,26,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,4,1,1.35,1,1,0,0,0,0,0,0,0,0,1,0,130,'boss_hellforge_diablo_yogg_shadowcrash_target',12340),
(@ENTRY + 15,0,0,0,0,0,28465,0,0,0,'Children of Yogg-Saron','','',0,82,82,2,16,0,1.6,1.71429,1,1,2745,3743,0,805,6,2000,2000,1,32768,2048,0,0,0,0,0,0,324,480,88,10,104,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,3,1,16.3193,1,1,0,0,0,0,0,0,0,167,1,617299839,2097152,'boss_hellforge_diablo_yogg_children',12340),
(@ENTRY + 16,0,0,0,0,0,28814,0,0,0,'Crusher Tentacle','','',0,82,82,2,16,0,1,1.14286,1,1,3000,3500,0,1,10,2000,2000,1,0,2048,0,0,0,0,0,0,353,512,112,10,72,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,3,1,29.6714,1,1,0,0,0,0,0,0,0,0,1,650854271,2097152,'boss_hellforge_diablo_yogg_crusher_tentacle',12340),
(@ENTRY + 17,0,0,0,0,0,28813,0,0,0,'Corruptor Tentacle','','',0,82,82,2,16,0,1,1.14286,1,1,488,642,0,782,7.5,2000,2000,1,0,2048,0,0,0,0,0,0,363,521,121,10,72,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,3,1,8.90142,1,1,0,0,0,0,0,0,0,0,1,617299839,2097152,'boss_hellforge_diablo_yogg_corruptor_tentacle',12340),
(@ENTRY + 18,0,0,0,0,0,28951,0,0,0,'Brain of Yogg-Saron','','',0,83,83,2,16,0,1.6,1.42857,0.3,3,509,683,0,805,35,2000,2000,1,0,2048,0,0,0,0,0,0,371,535,135,10,108,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,4,1,98.3455,1,1,0,0,0,0,0,0,0,150,1,650854271,2097152,'boss_hellforge_diablo_yogg_brain',12340),
(@ENTRY + 19,34215,0,0,0,0,28988,0,0,0,'Yogg-Saron\'s Brain Cell','','',0,80,80,2,14,0,1,1,1,1,422,586,6,642,7.5,2000,2000,1,0,2048,0,0,0,0,0,0,345,509,103,4,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,3,1,7,1,1,0,0,0,0,0,0,0,0,0,650854271,2097152,'boss_hellforge_diablo_yogg_brain_cell',12340),
(@ENTRY + 20,0,0,0,0,0,15294,0,0,0,'Shadow Fissure',NULL,NULL,0,1,1,0,35,0,1,1.14286,1,0,2,2,0,24,1,5500,0,1,0,2048,8,0,0,0,0,0,1,1,0,10,0,0,0,0,0,0,0,0,0,0,27812,0,0,0,0,0,0,0,0,0,0,0,'',0,7,1,1,1,1,0,0,0,0,0,0,0,100,1,0,128,'boss_hellforge_diablo_kelthuzad_fissure',12340),
(@ENTRY + 21,0,0,0,0,0,17519,11686,0,0,'Coldflame summoner',NULL,NULL,0,80,80,0,114,0,1,1.14286,1,0,104,138,0,252,1,2000,2000,1,33587968,2048,0,0,0,0,0,0,72,106,26,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,4,1,1.35,1,1,0,0,0,0,0,0,0,0,1,0,130,'boss_hellforge_diablo_lk_coldflame_summoner',12340),
(@ENTRY + 22,0,0,0,0,0,17519,11686,0,0,'Coldflame',NULL,NULL,0,80,80,0,114,0,1,1.14286,1,0,104,138,0,252,1,2000,2000,1,33587968,2048,0,0,0,0,0,0,72,106,26,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,4,1,1.35,1,1,0,0,0,0,0,0,0,0,1,0,130,'boss_hellforge_diablo_lk_coldflame',12340),
(@ENTRY + 23,0,0,0,0,0,17519,11686,0,0,'Defile',NULL,NULL,0,80,80,0,114,0,1,1.14286,1,0,104,138,0,252,1,2000,2000,1,33587968,2048,0,0,0,0,0,0,72,106,26,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,4,1,1.35,1,1,0,0,0,0,0,0,0,0,1,0,130,'boss_hellforge_diablo_lk_defile',12340);

UPDATE `creature_template` SET `dmg_multiplier` = 1, `lootid` = 0, `flags_extra` = `flags_extra` | 0x40000000 WHERE `entry` BETWEEN @ENTRY AND @ENTRY + 23;

DELETE FROM `spell_script_names` WHERE `spell_id` IN (66013, 69273);
INSERT INTO `spell_script_names` VALUES (66013, 'spell_anubarak_penetraing_cold'), (69273, "spell_hellforge_diablo_kelthuzad_volley"); 

DELETE FROM `hellforge_boss_stats` WHERE `StatId` BETWEEN 900 AND 1000;
INSERT INTO `hellforge_boss_stats` (`StatId`, `StatValue`, `StatVariance`, `StatComment`) VALUES
-- Kelthuzad stats
(900, 7999000, 1.0, "Diablo Kelthuzad health"),
(901, 72000, 0.88, "Diablo Kelthuzad meele dmg"),
(902, 12000, 0.5, "Diablo Kelthuzad Icy Touch timer"), -- pierwszy po 6 sekundach
(903, 25000, 1.0, "Diablo Kelthuzad Icy Touch damage"),
(904, 35000, 0.42, "Diablo Kelthuzad Frost Tomb timer"), -- pierwszy po 15 sekundach
(905, 2, 1.0, "Diablo Kelthuzad Frost Tomb count"),
(906, 10000, 1.0, "Diablo Kelthuzad Frost Volley timer after tombs"), -- pierwszy po 25 sekundach (10s po pierwszych tombach)
(907, 500000, 1.0, "Diablo Kelthuzad Frost Volley damage"), -- Frostbolt Volley ma lecieć w każdego gracza w raidzie za wyjątkiem tanka, może niech to zawsze blockuje, parruje czy coś ;o
(908, 20000, 0.75, "Diablo Kelthuzad Detonate mana timer"), -- pierwszy po 15 sekundach
(909, 25000, 0.4, "Diablo Kelthuzad Shadow Fissure timer"), -- pierwszy po 10s, 2 targety
(910, 25000, 0.8, "Diablo Kelthuzad Shadow Word Pain timer"), -- undispellable, pierwszy po 20s
(911, 12000, 1.0, "Diablo Kelthuzad Shadow Word Pain damage"), -- chodzi mi o 12k/tick
(912, 1000000, 1.0, "Diablo Kelthuzad Minion health"),
(913, 62000, 0.88, "Diablo Kelthuzad Minion meele dmg"),
(914, 13000, 1.0, "Diablo Kelthuzad Blood tap timer"),
(915, 100000, 1.0, "Diablo Kelthuzad Frost Tomb timer"),
(916, 10000, 1.0, "Diablo Kelthuzad Frost Tomb asphyxiation timer"),

(987, 80000, 1.0, "Diablo Kelthuzad Detonate damage"),
(988, 2, 1.0, "Diablo Kelthuzad fissure count"),
 
-- Yogg-Saron stats
(917, 18000, 0.4, "Diablo Yogg-Saron Constrictor Tentacle timer"), -- pierwszy po 6 sekundach
(918, 35000, 0.23, "Diablo Yogg-Saron Corruptor Tentacle timer"), -- pierwszy po 8 sekundach
(919, 89000, 1.0, "Diablo Yogg-Saron Constrictor Tentacle health"),
(920, 10000, 1.0, "Diablo Yogg-Saron Constrictor Tentacle kill timer"),
(921, 20000, 1.0, "Diablo Yogg-Saron Shadow Crash timer"),
(922, 10, 1.0, "Diablo Yogg-Saron Shadow Crash count"),
(923, 550000, 1.0, "Diablo Yogg-Saron Children health"),
(924, 70000, 0.88, "Diablo Yogg-Saron Children meele dmg"),
(925, 10000, 0.6, "Diablo Yogg-Saron Children volley timer"), -- pierwszy po 6 sekundach
(926, 25000, 1.0, "Diablo Yogg-Saron Children volley dmg"),
(927, 4999999, 1.0, "Diablo Yogg-Saron Crusher Tentacle health"),
(928, 88000, 0.88, "Diablo Yogg-Saron Crusher Tentacle meele dmg"),
(929, 249000, 1.0, "Diablo Yogg-Saron Corruptor Tentacle health"),
(930, 5000, 1.0, "Diablo Yogg-Saron Corruptor debuff timer"),
(931, 5000000, 1.0, "Diablo Yogg-Saron Brain Health"),
(932, 10000, 1.0, "Diablo Yogg-Saron Brain Summon Cell Timer"),
(933, 2, 1.0, "Diablo Yogg-Saron Brain Summon Cell Count"),
(934, 30000, 0.76, "Diablo Yogg-Saron Brain Cell Health"), -- losowe hp od 22.8k do 30k
(935, 20000, 0.88, "Diablo Yogg-Saron Brain Cell Meele Dmg"), -- arcane melee damage
(936, 5000, 1.0, "Diablo Yogg-Saron Brain Cell Explosion Timer"),
(937, 90, 1.0, "Diablo Yogg-Saron Brain Wipe Timer"),

(992, 6000, 1.0, "Diablo Yogg-Saron Brain Cell bubble DMG"),
(993, 300, 1.0, "Diablo Yogg-Saron Shadowcrash increase % dmg (base dmg is 5654 to 6345)"),
 
-- Anubarak stats
(955, 7999000, 1.0, "Diablo Anubarak health"),
(956, 92000, 0.77, "Diablo Anubarak meele dmg"),
(957, 15000, 0.4, "Diablo Anubarak freezing slash timer"), -- pierwszy po 6 sekundach
(958, 25, 1.0, "Diablo Anubarak freezing slash DMG (weapon % dmg)"),
(959, 20000, 0.5, "Diablo Anubarak penetrating cold timer"), -- pierwszy po 10 sekundach
(960, 2, 1.0, "Diablo Anubarak penetrating cold count"), -- selector ma wykluczyć main tanka
(961, 25000, 0.48, "Diablo Anubarak pound timer"), -- pierwszy po 12 skundach
(962, 128000, 1.0, "Diablo Anubarak submerge timer"),
(963, 38000, 1.0, "Diablo Anubarak merge timer"),
(964, 5000, 1.0, "Diablo Anubarak impale timer"),
(965, 5, 1.0, "Diablo Anubarak impale count"),
(966, 1000, 4, "Diablo Anubarak penetrating cold frost pulse timer"),
(967, 8000, 1.0, "Diablo Anubarak penetrating cold frost pulse dmg"),
(968, 45000, 1.0, "Diablo Anubarak permafrost despawn time"),
(969, 2500, 1.0, "Diablo Anubarak imaple activate timer"),
(970, 5000000, 1.0, "Diablo Anubarak imaple dmg"),
 
-- Onyxia stats
(938, 7949000, 1.0, "Diablo Onyxia health"),
(939, 100000, 0.88, "Diablo Onyxia meele dmg"),
(940, 12000, 0.5, "Diablo Onyxia flamebreath timer"), -- pierwszy po 6 sekundach
(941, 45000, 1.0, "Diablo Onyxia flamebreath dmg"),
(942, 10000, 1.0, "Diablo Onyxia tailsweep timer"),
(943, 30000, 1.0, "Diablo Onyxia tailsweep dmg"),
(944, 4000, 1.0, "Diablo Onyxia cleave timer"),
(945, 12000, 1.0, "Diablo Onyxia fireball volley timer"), -- pierwszy po 12 skundach
(946, 25000, 0.136, "Diablo Onyxia fireball volley dmg"),
(947, 45000, 1.0, "Diablo Onyxia spawn drake timer"),
(948, 449000, 1.0, "Diablo Onyxian Drake health"),
(949, 68000, 0.88, "Diablo Onyxian Drake meele dmg"),
(950, 8000, 1.0, "Diablo Onyxian Drake growth timer"),
(951, 10000, 1.0, "Diablo Onyxian Drake breath timer"),
(952, 30000, 1.0, "Diablo Onyxian Drake breath dmg"),
(953, 12000, 1.0, "Diablo Onyxian Drake fissure timer"), -- pierwszy po 6 sekundach, unlimited range
(954, 300000, 1.0, "Diablo Onyxian Drake fissure dmg"),

(989, 15000, 1.0, "Diablo Onyxia fear timer"),
(990, 2, 1.0, "Diablo Onyxia fear count"),
(991, 3000, 1.0, "Diablo Onyxia fear duration"),
 
-- Lichking stats
(971, 8100000, 1.0, "Diablo Lichking health"),
(972, 100000, 0.71, "Diablo Lichking meele dmg"),
(973, 22500, 0.26, "Diablo Lichking infest timer"), -- pierwszy po 6 sekundach
(974, 30000, 0.36, "Diablo Lichking soul reaper timer"), -- pierwszy po 11 sekundach
(975, 45000, 0.48, "Diablo Lichking raging spirit timer"), -- pierwszy po 22 sekundach
(976, 30000, 1.0, "Diablo Lichking spawn valkyr timer"), -- pierwsza po 30 sekundach
(977, 30000, 1.5, "Diablo Lichking defile timer"), -- na p2 z mieczem cd ma wynosić 45s, pierwszy defile 16s po pullu.
(978, 16000, 1.0, "Diablo Lichking defile first timer"),
(979, 700000, 1.0, "Diablo Lichking valkyr health"),
(980, 103000000, 1.0, "Diablo Lichking Frostmourne health"),
(981, 99000, 0.72, "Diablo Lichking Frostmourne meele"),
(982, 10000, 1.0, "Diablo Lichking Frostmourne coldflame timer"),
(983, 30000, 1.0, "Diablo Lichking Frostmourne bladestorm timer"),
(984, 3000, 1.0, "Diablo Lichking Frostmourne cleave timer"),
(985, 399000, 1.0, "Diablo Lichking Raging Spirit Health"),
(986, 70000, 0.88, "Diablo Lichking Raging Spirit Meele DMG");

