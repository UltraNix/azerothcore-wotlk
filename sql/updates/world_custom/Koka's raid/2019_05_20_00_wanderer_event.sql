SET @ENTRY := 200000;
SET @OUTFIT_ENTRY = 2147483648;
DELETE FROM `creature_template` WHERE entry BETWEEN @ENTRY AND @ENTRY + 2;
INSERT INTO `creature_template` VALUES 
(@ENTRY,0,0,0,0,0,@OUTFIT_ENTRY,0,0,0,'The Wanderer',NULL,NULL,0,80,80,0,35,3,1,1.14286,1,0,56,74,0,136,1,1000,2000,1,0,2048,0,0,0,0,0,0,39,57,14,7,4096,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,3,1,1.15,1,1,0,0,0,0,0,0,0,0,1,0,2,'npc_wanderer',12340),
(@ENTRY + 1,0,0,0,0,0,9784,9787,9786,9788,'Skeleton of Doom','','',0,80,80,2,21,0,0.8,0.99206,1,0,5000,8000,0,642,1,2000,2000,1,32768,2048,0,0,0,0,0,0,345,509,103,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,3,1,40,1,1,0,0,0,0,0,0,0,0,1,8388624,0,'npc_wanderer_skeleton',12340),
(@ENTRY + 2,0,0,0,0,0,@OUTFIT_ENTRY,0,0,0,'The Wanderer',NULL,NULL,0,80,80,0,35,3,1,1.14286,1,0,56,74,0,136,1,1000,2000,1,0,2048,0,0,0,0,0,0,39,57,14,7,4096,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,3,1,1.15,1,1,0,0,0,0,0,0,0,0,1,0,2,'',12340);

DELETE FROM `creature_template_outfits` WHERE `entry` = @OUTFIT_ENTRY;
INSERT INTO `creature_template_outfits` VALUES (@OUTFIT_ENTRY,0,1,1,0,3,10,0,8,8,0,0,0,6144,0,0,0,0,0,0,0,0,'Wanderer');

DELETE FROM `creature_equip_template` WHERE `entry` = @ENTRY + 1;
INSERT INTO `creature_equip_template` VALUES (@ENTRY + 1,1,1905,0,0,18019);

DELETE FROM `creature_template_addon` WHERE `entry` = @ENTRY + 1;
INSERT INTO `creature_template_addon` VALUES (@ENTRY + 1,0,0,0,0,0,'36725');

DELETE FROM `creature_text` WHERE `entry` = @ENTRY;
INSERT INTO `creature_text` VALUES
(@ENTRY, 0, 0, 'I have lost something.', 12, 0, 100, 0, 0, 0, 0, 'The Wanderer'),
(@ENTRY, 1, 0, 'Those who help me regain my treasure will be justly… rewarded.', 12, 0, 100, 0, 0, 0, 0, 'The Wanderer'),
(@ENTRY, 2, 0, 'This is a strange realm indeed.', 12, 0, 100, 0, 0, 0, 0, 'The Wanderer'),
(@ENTRY, 3, 0, 'I have never liked winter.', 12, 0, 100, 0, 0, 0, 0, 'The Wanderer'),
(@ENTRY, 4, 0, 'The stench of sulfur fills the air.', 16, 0, 100, 0, 0, 0, 0, 'The Wanderer'),
(@ENTRY, 5, 0, 'Something very odd is happening.', 16, 0, 100, 0, 0, 0, 0, 'The Wanderer'),
(@ENTRY, 6, 0, 'Smell of burning skin and hair suffocates the air.', 16, 0, 100, 0, 0, 0, 0, 'The Wanderer'),
(@ENTRY, 7, 0, 'Why is everybody screaming?', 16, 0, 100, 0, 0, 0, 0, 'The Wanderer');

SET @TEXT_ENTRY := 1110000;
DELETE FROM `npc_text` WHERE `Id` BETWEEN @TEXT_ENTRY AND @TEXT_ENTRY + 3;
INSERT INTO `npc_text`(`ID`, `text0_0`) VALUES
(@TEXT_ENTRY, 'Hello stranger, what can I do for you?'),
(@TEXT_ENTRY + 1, 'People used to call me the Wanderer. In my world… I was once a great warrior, just like you. I\'ve faced many enemies and fought many wars. Now, I carry a terrible secret and I\'ve lost the only thing I could care about.'),
(@TEXT_ENTRY + 2, 'Many years have I spent searching for the lost treasure of mine. I am looking for the heroes fit for helping me - and I shall reward them greatly. But are you a hero indeed?'),
(@TEXT_ENTRY + 3, 'I don\'t know. I shouldn\'t ask, but I\'m not hiding that I\'m not from here and it\'s hard for me to get along. It\'s nothing certain, but I think I know who has my property and where he is. If the gossip turns out to be true, I will ask you, my friend, to come with me.');

SET @EVENT_ENTRY := 74;
SET @GUID = 500002;
DELETE FROM `game_event` WHERE `eventEntry` = @EVENT_ENTRY;
INSERT INTO `game_event` VALUES (@EVENT_ENTRY,'2019-05-13 07:00:00','2020-12-31 05:00:00',1440,840,0,0,'Wanderer Dalaran Event',0);
DELETE FROM `game_event_creature` WHERE `eventEntry` = @EVENT_ENTRY;
INSERT INTO `game_event_creature` VALUES(@EVENT_ENTRY, @GUID);

SET @QUEST_ENTRY := 30000;
DELETE FROM `quest_template` WHERE `Id` BETWEEN @QUEST_ENTRY AND @QUEST_ENTRY + 6;
INSERT INTO `quest_template` VALUES 
(@QUEST_ENTRY,2,80,80,0,4395,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,30000,0,0,500000,0,0,0,0,0,0,0,0,0,0,32968,1,0,0,0,0,52006,49426,0,0,1,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,'The Wanderer\'s Call: A Song of Ice and Fire','Slay Sindragosa in Icecrown Citadel (any difficulty)\r\nSlay Ignis the Furnace Master in Ulduar (any difficulty).\r\n','She was reborn in ice and he wields fire. Sindragosa waits for you in her icy lair. Turn her bones into ash. As the song of ice comes to its end, you will have to find Ignis the Furnace Master in Ulduar. Burn him with the very fire he commands.','','You\'ve proven that you\'re a glorious fighter, $n. But it\'s not enough. Return to me soon, so I can continue… testing you.','You\'re still here? I think you wanted to prove yourself. Return to me once you do what I asked for.','',33118,36853,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Ignis the Furnace Master slain','Sindragosa slain','','',1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,12340),
(@QUEST_ENTRY + 1,2,80,80,0,4395,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,30000,0,0,500000,0,0,0,0,0,0,0,0,0,0,32968,1,0,0,0,0,52006,49426,0,0,1,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,'The Wanderer\'s Call: Beauty and the Beast','Slay The Twin Val\'kyr in Trial of the Crusader (any difficulty)\r\nSlay Rotface in Icecrown Citadel (any difficulty).\r\n','Two Val\'kyr sisters share the worst fate. They are bound to each other, as they were in life, they are in death. Break their bonds and break their spirits. Once you do that, head to Icecrown Citadel. Find Rotface, an amalgamation with a mind of a child. Break his body and break his mind','','And now, they are both… dead. It pleases me. Thank you, $n. Return to me soon and I will have something new for you.','You\'re still here? I think you wanted to prove yourself. Return to me once you do what I asked for.','',34496,36627,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Twin Val\'kyr slain','Rotface slain',NULL,NULL,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,12340),
(@QUEST_ENTRY + 2,2,80,80,0,4395,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,30000,0,0,500000,0,0,0,0,0,0,0,0,0,0,32968,1,0,0,0,0,52006,49426,0,0,1,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,'The Wanderer\'s Call: Master of Puppets','Slay The Lich King in Icecrown Citadel (any difficulty)\r\nSlay Sapphiron in Naxxramas (any difficulty).\r\n','He was just a boy. A boy who razed his own kingdom to the ground, who did unspeakable things to his own people. In any other circumstances… oh, where was I? Ah, yes, the Lich King. Destroy him. After you deal with him, pay Sapphiron a visit. This frostwyrm is a creation of the Lich King, a memory of him. Kill this memory.',NULL,'And now, they are both… dead. It pleases me. Thank you, $n. Return to me soon and I will have something new for you.','You\'re still here? I think you wanted to prove yourself. Return to me once you do what I asked for.',NULL,36597,15989,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Lich King slain','Sapphirion slain',NULL,NULL,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,12340),
(@QUEST_ENTRY + 3,2,80,80,0,4395,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,30000,0,0,500000,0,0,0,0,0,0,0,0,0,0,32968,1,0,0,0,0,52006,49426,0,0,1,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,'The Wanderer\'s Call: Hour of Twilight','Slay Halion in Ruby Sanctum (any difficulty).','I can hear the whispers of the Old Gods. They are in turmoil, down in the deeps they are waking up. Halion is one of their harbingers. Let the sun set on his pitiful, enthralled existence.',NULL,'The Twilight Harbinger is no more! Good, good. Come back to me soon, I will have another great task for you.','You\'re still here? I think you wanted to prove yourself. Return to me once you do what I asked for.',NULL,39863,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Halion slain','',NULL,NULL,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,12340),
(@QUEST_ENTRY + 4,2,80,80,0,4395,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,30000,0,0,500000,0,0,0,0,0,0,0,0,0,0,32968,1,0,0,0,0,52006,49426,0,0,1,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,'The Wanderer\'s Call: Icy Winds','Slay Lady Deathwhisper in Icecrown Citadel (any difficulty)\r\nSlay Icehowl in Trial of the Crusader (any difficulty).\r\n','I am not used to the icy winds of Northrend. There are creatures and beings with ice inside their veins. And these creatures… are powerful. Lady Deathwhisper, a lich residing inside of Icecrown Citadel, supposedly wields the power to freeze anyone from within. Burn her. After you do that, do me a little favor… There\'s Icehowl, a giant creature held in Argent Tournament Grounds. End it.',NULL,'It\'s done! You\'ve proven yourself, $n. But it\'s not over. Soon, I will have another great task for you.','You\'re still here? I think you wanted to prove yourself. Return to me once you do what I asked for.',NULL,36855,34797,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Lady Deathwhisper slain','Icehowl slain',NULL,NULL,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,12340),
(@QUEST_ENTRY + 5,2,80,19,0,4395,41,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,30001,0,0,0,0,0,0,9928,0,0,0,0,0,0,32968,1,0,0,0,100,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,'The Wanderer\'s Call: Fight for Glory','Win 5 Battlegrounds.','Have you ever done anything glorious, $n? Are there a songs about your feats? Did you hear the wail of the widows of those who you have slaughtered? You don\'t have to say anything. I have never heard of you and things you would say could be lies. I am not someone to lie to.',NULL,'You\'ve proven that you\'re a glorious fighter, $n. But it\'s not enough. Return to me soon, so I can continue… testing you.\r\n','You\'re still here? I think you wanted to prove yourself. Return to me once you do what I asked for.',NULL,200000,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Battlegrounds won','',NULL,NULL,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,12340),
(@QUEST_ENTRY + 6,2,80,19,0,4395,41,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,30001,0,0,0,0,0,0,9928,0,0,0,0,0,0,32968,1,0,0,0,100,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,'The Wanderer\'s Call: Blood and Sand','Win 3 Rated Arenas (2v2, 3v3 or 5v5).','It might be hard to fight your enemies head on, but if you want to prove yourself to me, you\'ll have to do that. You must enter the fighting pits and… get out of them alive. Destroy your enemies and then return to me.',NULL,'Great. That\'s what I thought. There are more tasks for you to do, so return to me once you are ready.\r\n','You\'re still here? I think you wanted to prove yourself. Return to me once you do what I asked for.',NULL,200002,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Arenas won',NULL,NULL,NULL,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,12340);

DELETE FROM `creature_queststarter` WHERE `Id` = @ENTRY;
INSERT INTO `creature_queststarter` VALUES
(@ENTRY, @QUEST_ENTRY),
(@ENTRY, @QUEST_ENTRY + 1),
(@ENTRY, @QUEST_ENTRY + 2),
(@ENTRY, @QUEST_ENTRY + 3),
(@ENTRY, @QUEST_ENTRY + 4),
(@ENTRY, @QUEST_ENTRY + 5),
(@ENTRY, @QUEST_ENTRY + 6);
DELETE FROM `creature_questender` WHERE `Id` = @ENTRY;
INSERT INTO `creature_questender` VALUES
(@ENTRY, @QUEST_ENTRY),
(@ENTRY, @QUEST_ENTRY + 1),
(@ENTRY, @QUEST_ENTRY + 2),
(@ENTRY, @QUEST_ENTRY + 3),
(@ENTRY, @QUEST_ENTRY + 4),
(@ENTRY, @QUEST_ENTRY + 5),
(@ENTRY, @QUEST_ENTRY + 6);

SET @POOL_ENTRY := 70000;
SET @QUEST_ENTRY := 30000;
DELETE FROM `pool_template` WHERE `entry` BETWEEN @POOL_ENTRY AND @POOL_ENTRY + 1;
INSERT INTO `pool_template` VALUES (@POOL_ENTRY,1,'Wanderer Dalaran Weekly PvE'),(@POOL_ENTRY + 1,1,'Wanderer Dalaran Weekly PvP');

DELETE FROM `pool_quest` WHERE `pool_entry` BETWEEN @POOL_ENTRY AND @POOL_ENTRY + 1;
INSERT INTO `pool_quest` VALUES (@QUEST_ENTRY,@POOL_ENTRY,'The Wanderer\'s Call'),(@QUEST_ENTRY + 1,@POOL_ENTRY,'The Wanderer\'s Call'),(@QUEST_ENTRY + 2,@POOL_ENTRY,'The Wanderer\'s Call'),(@QUEST_ENTRY + 3,@POOL_ENTRY,'The Wanderer\'s Call'),(@QUEST_ENTRY + 4,@POOL_ENTRY,'The Wanderer\'s Call'),(@QUEST_ENTRY + 5,@POOL_ENTRY + 1,'The Wanderer\'s Call'),(@QUEST_ENTRY + 6,@POOL_ENTRY + 1,'The Wanderer\'s Call');

UPDATE `creature_template` SET `ScriptName` = 'npc_wanderer_dalaranNPC' WHERE `entry` IN
(SELECT `Id` FROM `creature` WHERE `guid` IN (133649, 28686, 105660, 115281, 114331, 111719, 97932, 99201, 112965, 111461, 98866, 101811, 102325, 98070, 102048, 96496, 111374, 102530, 102606, 98178, 98421, 102500, 98346, 99029, 114781, 111858, 112329, 105534, 114292, 102700, 102397, 102387, 101236, 112052, 112385, 12402, 102070, 103296, 102399, 97989, 97931, 101356, 100940, 111283, 112852, 112639, 112686, 102033, 116617, 112609, 111691, 102417, 102427, 102428, 207871, 207873, 85214, 102430, 102420, 102323, 111306, 137702, 100897, 120324, 119625, 102418, 102419, 107612, 104358, 104242, 113397, 117830, 85210, 85208, 102693, 249559, 249558, 102673, 102516));

DELETE FROM `creature` WHERE `guid` = @GUID;
INSERT INTO `creature` VALUES (@GUID,200000,571,1,1,0,0,5839.03,589.837,650.596,5.67249,300,0,0,1753,0,2,0,0,0);
DELETE FROM `waypoint_data` WHERE `Id` = @GUID;
INSERT INTO `waypoint_data` VALUES (@GUID,1,5839.05,589.501,650.615,0,0,0,0,100,0),(@GUID,2,5843.8,595.616,650.633,0,0,0,0,100,0),(@GUID,3,5851.54,605.729,650.742,0,0,0,0,100,0),(@GUID,4,5863.83,622.755,648.921,0,0,0,0,100,0),(@GUID,5,5871.54,637.582,647.078,0,0,0,0,100,0),(@GUID,6,5874.01,655.602,645.192,0,0,0,0,100,0),(@GUID,7,5869.37,673.091,643.662,0,0,0,0,100,0),(@GUID,8,5880.82,681.124,643,0,0,0,0,100,0),(@GUID,9,5894.11,691.315,642.007,0,0,0,0,100,0),(@GUID,10,5903.85,705.153,641.098,0,0,0,0,100,0),(@GUID,11,5903.3,716.962,640.849,0,0,0,0,100,0),(@GUID,12,5895.99,729.712,639.547,0,0,0,0,100,0),(@GUID,13,5884.06,733.773,638.893,0,0,0,0,100,0),(@GUID,14,5870.9,732.403,638.205,0,0,0,0,100,0),(@GUID,15,5860.97,725.57,639.018,0,0,0,0,100,0),(@GUID,16,5851.85,714.957,640.449,0,0,0,0,100,0),(@GUID,17,5837.8,704.574,641.347,0,0,0,0,100,0),(@GUID,18,5829.52,705.148,641.436,0,0,0,0,100,0),(@GUID,19,5816.76,710.891,641.255,0,0,0,0,100,0),(@GUID,20,5801.64,714.939,641.004,0,0,0,0,100,0),(@GUID,21,5786.44,711.592,641.177,0,0,0,0,100,0),(@GUID,22,5777,702.7,641.723,0,0,0,0,100,0),(@GUID,23,5763.09,686.969,642.371,0,0,0,0,100,0),(@GUID,24,5753.82,676.48,642.682,0,0,0,0,100,0),(@GUID,25,5744.55,665.992,644.198,0,0,0,0,100,0),(@GUID,26,5734.57,653.284,645.983,0,0,0,0,100,0),(@GUID,27,5727.8,642.462,646.507,0,0,0,0,100,0),(@GUID,28,5726.28,634.276,646.736,0,0,0,0,100,0),(@GUID,29,5728.55,624.19,647.25,0,0,0,0,100,0),(@GUID,30,5735.46,615.95,647.643,0,0,0,0,100,0),(@GUID,31,5751.7,602.637,648.87,0,0,0,0,100,0),(@GUID,32,5762.42,593.633,649.653,0,0,0,0,100,0),(@GUID,33,5773.61,584.556,649.927,0,0,0,0,100,0),(@GUID,34,5784.66,575.96,649.936,0,0,0,0,100,0),(@GUID,35,5795.71,567.364,650.111,0,0,0,0,100,0),(@GUID,36,5801.11,562.912,650.255,0,0,0,0,100,0),(@GUID,37,5802.87,552.068,649.641,0,0,0,0,100,0),(@GUID,38,5784.56,531.381,641.56,0,0,0,0,100,0),(@GUID,39,5779.14,535.619,641.56,0,0,0,0,100,0),(@GUID,40,5786.6,544.313,637.828,0,0,0,0,100,0),(@GUID,41,5799.34,561.01,630.588,0,0,0,0,100,0),(@GUID,42,5800.12,562.335,629.784,0,0,0,0,100,0),(@GUID,43,5803.5,571.573,628.899,0,0,0,0,100,0),(@GUID,44,5811,580.018,627.473,0,0,0,0,100,0),(@GUID,45,5820.57,590.219,625.368,0,0,0,0,100,0),(@GUID,46,5829.79,600.751,623.54,0,0,0,0,100,0),(@GUID,47,5835.46,609.819,621.302,0,0,0,0,100,0),(@GUID,48,5835.86,615.712,620.363,0,0,0,0,100,0),(@GUID,49,5830.07,625.31,615.83,0,0,0,0,100,0),(@GUID,50,5827.47,629.182,614.569,0,0,0,0,100,0),(@GUID,51,5826.14,632.66,612.918,0,0,0,0,100,0),(@GUID,52,5825.81,642.579,609.384,0,0,0,0,100,0),(@GUID,53,5822.99,645.882,609.383,0,0,0,0,100,0),(@GUID,54,5818.19,649.55,609.887,0,0,0,0,100,0),(@GUID,55,5805,654.528,609.887,0,0,0,0,100,0),(@GUID,56,5796.1,650.957,609.887,0,0,0,0,100,0),(@GUID,57,5790.72,645.201,609.887,0,0,0,0,100,0),(@GUID,58,5789.19,639.614,609.887,0,0,0,0,100,0),(@GUID,59,5787.48,625.723,609.158,0,0,0,0,100,0),(@GUID,60,5787.12,622.566,609.158,0,0,0,0,100,0),(@GUID,61,5781.87,612.395,609.886,0,0,0,0,100,0),(@GUID,62,5774.79,616.073,609.886,0,0,0,0,100,0),(@GUID,63,5764.96,624.857,612.511,0,0,0,0,100,0),(@GUID,64,5760.14,628.451,615.232,0,0,0,0,100,0),(@GUID,65,5754.66,632.815,617.127,0,0,0,0,100,0),(@GUID,66,5748.06,640.994,618.598,0,0,0,0,100,0),(@GUID,67,5750.97,643.631,618.598,0,0,0,0,100,0),(@GUID,68,5759.94,654.372,618.501,0,0,0,0,100,0),(@GUID,69,5771.46,666.544,618.599,0,0,0,0,100,0),(@GUID,70,5778.25,672.616,618.599,0,0,0,0,100,0),(@GUID,71,5786.96,683.575,618.599,0,0,0,0,100,0),(@GUID,72,5800.04,700,618.599,0,0,0,0,100,0),(@GUID,73,5804.49,707.627,618.918,0,0,0,0,100,0),(@GUID,74,5807.36,714.905,619.03,0,0,0,0,100,0),(@GUID,75,5815,726.631,624.057,0,0,0,0,100,0),(@GUID,76,5820.93,738.917,623.357,0,0,0,0,100,0),(@GUID,77,5824.16,753.26,624.261,0,0,0,0,100,0),(@GUID,78,5822.46,767.758,625.429,0,0,0,0,100,0),(@GUID,79,5821.24,776.346,627.254,0,0,0,0,100,0),(@GUID,80,5813.66,789.519,632.588,0,0,0,0,100,0),(@GUID,81,5811.66,788.985,632.588,0,0,0,0,100,0),(@GUID,82,5812.11,782.023,633.087,0,0,0,0,100,0),(@GUID,83,5814.19,768.181,639.241,0,0,0,0,100,0),(@GUID,84,5816.22,753.203,640.404,0,0,0,0,100,0),(@GUID,85,5816.81,746.228,640.762,0,0,0,0,100,0),(@GUID,86,5818.74,725.317,641.26,0,0,0,0,100,0),(@GUID,87,5820.21,717.329,641.299,0,0,0,0,100,0),(@GUID,88,5829.11,706.538,641.263,0,0,0,0,100,0),(@GUID,89,5843.74,691.472,642.624,0,0,0,0,100,0),(@GUID,90,5857.96,678.211,643.643,0,0,0,0,100,0),(@GUID,91,5867.43,667.93,644.202,0,0,0,0,100,0),(@GUID,92,5875.39,656.724,645.136,0,0,0,0,100,0),(@GUID,93,5876.91,641.116,646.386,0,0,0,0,100,0),(@GUID,94,5868.97,626.827,648.2,0,0,0,0,100,0),(@GUID,95,5860.06,616.04,650.092,0,0,0,0,100,0),(@GUID,96,5855.46,610.764,650.575,0,0,0,0,100,0),(@GUID,97,5846.65,599.892,650.909,0,0,0,0,100,0),(@GUID,98,5839.2,590.048,650.591,0,0,0,0,100,0);

DELETE FROM `creature_addon` WHERE `guid` = @GUID;
INSERT INTO `creature_addon` VALUES (@GUID, @GUID, 0, 0, 0, 0, NULL)
