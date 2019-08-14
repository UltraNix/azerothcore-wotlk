SET @ENTRY := 260000;
DELETE FROM `creature_template` WHERE `entry` BETWEEN @ENTRY AND @ENTRY + 6;
INSERT INTO `creature_template` VALUES 
(@ENTRY,0,0,0,0,0,2147483648,0,0,0,'The Wanderer',NULL,NULL,0,80,80,0,35,3,1,1.14286,1,0,100000,200000,0,136,1,1000,2000,1,0,2048,0,0,0,0,0,0,39,57,14,7,4096,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,3,1,1.15,1,1,0,0,0,0,0,0,0,0,1,0,0,'npc_hellforge_wanderer',12340),
(@ENTRY + 1,0,0,0,0,0,24925,0,0,0,'Cocoon',NULL,NULL,0,80,80,0,14,0,1,1.14286,1,0,56,74,0,136,1,1000,2000,1,0,2048,0,0,0,0,0,0,39,57,14,7,4096,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,3,1,1.15,1,1,0,0,0,0,0,0,0,0,1,0,0,'npc_hellforge_wanderer_champion_cocoon',12340),
(@ENTRY + 2,0,0,0,0,0,5567,0,0,0,'Jonas Dark',NULL,NULL,0,80,80,0,35,3,1,1.14286,1,0,56,74,0,136,1,1000,2000,1,0,2048,0,0,0,0,0,0,39,57,14,7,4096,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,3,1,1.15,1,1,0,0,0,0,0,0,0,0,1,0,0,'npc_hellforge_wanderer_champion',12340),
(@ENTRY + 3,0,0,0,0,0,5567,0,0,0,'Hellforge Q6 Heal Credit',NULL,NULL,0,80,80,0,35,3,1,1.14286,1,0,56,74,0,136,1,1000,2000,1,0,2048,0,0,0,0,0,0,39,57,14,7,4096,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,3,1,1.15,1,1,0,0,0,0,0,0,0,0,1,0,0,'',12340),
(@ENTRY + 4,0,0,0,0,0,22669,0,0,0,'Soul Stone',NULL,NULL,0,80,80,0,35,0,0.1,0.1,0.3,0,56,74,0,136,1,1000,2000,1,0,2048,0,0,0,0,0,0,39,57,14,7,4096,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,4,1,1.15,1,1,0,0,0,0,0,0,0,0,1,0,0,'',12340),
(@ENTRY + 5,0,0,0,0,0,16896,0,0,0,'Burning Worm',NULL,NULL,0,80,80,0,35,0,0.1,0.1,0.3,0,56,74,0,136,1,1000,2000,1,0,2048,0,0,0,0,0,0,39,57,14,7,4096,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,4,1,1.15,1,1,0,0,0,0,0,0,0,0,1,0,0,'',12340),
(@ENTRY + 6,0,0,0,0,0,25900,0,0,0,'Tyrael', 'Archangel of Justice',NULL,0,80,80,0,35,3,1,1.14286,10,0,100000,200000,0,136,1,1000,2000,1,0,2048,0,0,0,0,0,0,39,57,14,7,4096,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,1,1,1.15,1,1,0,0,0,0,0,0,0,0,1,0,0,'npc_hellforge_tyrael',12340);

UPDATE `gameobject` SET `spawnMask`=15 WHERE  `guid`=17906;

SET @QUEST_ENTRY := 31000;
DELETE FROM `quest_template` WHERE `Id` = @QUEST_ENTRY;  
INSERT INTO `quest_template` VALUES 
(@QUEST_ENTRY,2,80,80,0,4395,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,30012,0,0,@QUEST_ENTRY + 1,0,1000000,0,0,0,0,0,0,0,0,0,0,72,2,0,0,0,0,49426,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,'What a Mess','Kill all creatures in first hall','Warriors’ armors ahead of us seems familiar… Is it possible for him to be here…? Nevermind, we have to clear our path through this hall. Return to me once all enemies are dead.
','','It was just a warm up. Time to dive into these catacombs.', 'I smell some foul stench, something around here is certainly still alive..','',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Kill all creatures in first hall','','','',1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,12340);

DELETE FROM `creature_queststarter` WHERE `id` = @ENTRY AND `quest` = @QUEST_ENTRY;
INSERT INTO `creature_queststarter` VALUES(@ENTRY, @QUEST_ENTRY);

DELETE FROM `creature_questender` WHERE `id` = @ENTRY AND `quest` = @QUEST_ENTRY;
INSERT INTO `creature_questender` VALUES(@ENTRY, @QUEST_ENTRY);

SET @QUEST_ENTRY := @QUEST_ENTRY + 1;
DELETE FROM `quest_template` WHERE `Id` = @QUEST_ENTRY;  
INSERT INTO `quest_template` VALUES (@QUEST_ENTRY,2,80,80,0,4395,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,@QUEST_ENTRY - 1,0,0,@QUEST_ENTRY + 1,0,1000000,0,0,0,0,0,0,0,0,0,0,72,0,0,0,0,0,49426,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,'Heat','Slain Phyrrocoris','I have never seen something like this… What a heat… It seems like this hallway belongs to this creature, everything around is burnt to ash. We shall burn too, if we’ll just avoid it and pass by. We have to annihilate it.', '', 'Great job! I hope you have some strength left yet, because something tells me that Hellforge is full of surprises.', 'It’s so hot around here...','',250000,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Phyrrocoris slain','','','',1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,12340);

DELETE FROM `creature_queststarter` WHERE `id` = @ENTRY AND `quest` = @QUEST_ENTRY;
INSERT INTO `creature_queststarter` VALUES(@ENTRY, @QUEST_ENTRY);

DELETE FROM `creature_questender` WHERE `id` = @ENTRY AND `quest` = @QUEST_ENTRY;
INSERT INTO `creature_questender` VALUES(@ENTRY, @QUEST_ENTRY);

SET @QUEST_ENTRY := @QUEST_ENTRY + 1;
DELETE FROM `quest_template` WHERE `Id` = @QUEST_ENTRY;  
INSERT INTO `quest_template` VALUES (@QUEST_ENTRY,2,80,80,0,4395,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,@QUEST_ENTRY - 1,0,0,@QUEST_ENTRY + 1,0,1000000,0,0,0,0,0,0,0,0,0,0,72,2,0,0,0,0,49426,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,'Reunion','Find Jonas Dark','I’ve heard of this place… If I recall it correctly, we should meet my friend somewhere around here. He arrived to Hellforge some time ago. I feel disturbing aura of this place as well… Someone or something… has been summoning ancient creatures here. It’s truly an aberrant place… Finish off remaining enemies and let’s find my companion.', '', 'Thank you..', 'He is somewhere around here, we have to find him!','',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Find Jonas Dark','','','',1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,12340);

DELETE FROM `creature_queststarter` WHERE `id` = @ENTRY AND `quest` = @QUEST_ENTRY;
INSERT INTO `creature_queststarter` VALUES(@ENTRY, @QUEST_ENTRY);

DELETE FROM `creature_questender` WHERE `id` = @ENTRY + 2 AND `quest` = @QUEST_ENTRY;
INSERT INTO `creature_questender` VALUES(@ENTRY + 2, @QUEST_ENTRY);

SET @QUEST_ENTRY := @QUEST_ENTRY + 1;
DELETE FROM `quest_template` WHERE `Id` = @QUEST_ENTRY;  
INSERT INTO `quest_template` VALUES (@QUEST_ENTRY,2,80,80,0,4395,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,@QUEST_ENTRY - 1,0,0,@QUEST_ENTRY + 1,0,1000000,0,0,0,0,0,0,0,0,0,0,72,0,0,0,0,0,49426,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,'Treason','Speak with The Wanderer','Thank you for your help, I thought that they will finally sacrifice me. Deity called Slythe daily offers captives to his god and I was supposed to be next one, so you arrived here just in time… But let’s not talk about that now! The Wanderer, where is he? You have to let him know, that Hephasto betrayed him! It was he, who stole his stone and escaped to Hellforge. I was following him but they caught me in this hall. Hephasto is here for sure, I have seen him several times. It is time to settle the score between us! You can count on my help!', '', 'Hephasto… You’ll regret it...', 'He must know the truth…','',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Speak with The Wanderer','','','',1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,12340);

DELETE FROM `creature_queststarter` WHERE `id` = @ENTRY + 2 AND `quest` = @QUEST_ENTRY;
INSERT INTO `creature_queststarter` VALUES(@ENTRY + 2, @QUEST_ENTRY);

DELETE FROM `creature_questender` WHERE `id` = @ENTRY AND `quest` = @QUEST_ENTRY;
INSERT INTO `creature_questender` VALUES(@ENTRY, @QUEST_ENTRY);

SET @QUEST_ENTRY := @QUEST_ENTRY + 1;
DELETE FROM `quest_template` WHERE `Id` = @QUEST_ENTRY;  
INSERT INTO `quest_template` VALUES (@QUEST_ENTRY,2,80,80,0,4395,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,@QUEST_ENTRY - 1,0,0,@QUEST_ENTRY + 1,0,1000000,0,0,0,0,0,0,0,0,0,0,72,0,0,0,0,0,49426,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,'Hephasto the Armorer','Slain Hephasto the Armorer','How dare he… He has been accompanying me for ages, I can’t believe he actually did betray me! Kill this wretch!', '', 'Black Witch? So he works for her… I’ve heard about her...', 'Damned smith, we have to get him!','',250015,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Hephasto the Armorer Slain','','','',1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,12340);

DELETE FROM `creature_queststarter` WHERE `id` = @ENTRY AND `quest` = @QUEST_ENTRY;
INSERT INTO `creature_queststarter` VALUES(@ENTRY, @QUEST_ENTRY);

DELETE FROM `creature_questender` WHERE `id` = @ENTRY + 2 AND `quest` = @QUEST_ENTRY;
INSERT INTO `creature_questender` VALUES(@ENTRY + 2, @QUEST_ENTRY);

SET @QUEST_ENTRY := @QUEST_ENTRY + 1;
DELETE FROM `quest_template` WHERE `Id` = @QUEST_ENTRY;  
INSERT INTO `quest_template` VALUES (@QUEST_ENTRY,2,80,80,0,4395,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,@QUEST_ENTRY - 1,0,0,@QUEST_ENTRY + 1,0,1000000,0,0,0,0,0,0,0,0,0,0,72,0,0,0,0,0,49426,13584,0,0,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,'Role Reversal','Aid me and discover the truth.','Black Witch… so Hephasto stole the Wanderer’s Stone for her. Winged vampire is dangerous adversary, but she has been living for thousands of years already and got completely blind… Maybe we can use this against her. If she has the Stone we must succeed, prepare yourself for a savage battle. Before we start… Could you heal me, please? Hephasto was an extremely challenging opponent.','','What have you done, mortals?! You let great evil and terror enter your realm. We have to hurry if we want to avoid unimaginable tragedy!','I’m afraid of Black Witch a bit…','',260003,250023,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Heal Jonas to full health','Truth discovered','','',1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,12340);

DELETE FROM `creature_queststarter` WHERE `id` = @ENTRY + 2 AND `quest` = @QUEST_ENTRY;
INSERT INTO `creature_queststarter` VALUES(@ENTRY + 2, @QUEST_ENTRY);

DELETE FROM `creature_questender` WHERE `id` = @ENTRY + 6 AND `quest` = @QUEST_ENTRY;
INSERT INTO `creature_questender` VALUES(@ENTRY + 6, @QUEST_ENTRY);

DELETE FROM `waypoint_data` WHERE `id` in (2600000, 2600001, 2600002, 2600020);
INSERT INTO `waypoint_data` VALUES 
(2600000,1,1378.88,-633.317,-92.0544,0,10000,1,0,100,0),
(2600000,2,1376.12,-631.154,-92.0544,0,0,1,0,100,0),
(2600000,3,1369.98,-623.087,-92.0544,0,0,1,0,100,0),
(2600000,4,1368.76,-619.557,-92.0544,0,0,1,0,100,0),
(2600000,5,1368.77,-615.061,-92.0544,0,0,1,0,100,0),
(2600000,6,1369.73,-597.608,-92.0544,0,0,1,0,100,0),
(2600000,7,1370.12,-576.612,-92.0544,0,0,1,0,100,0),
(2600000,8,1370.55,-554.139,-92.0544,0,0,1,0,100,0),
(2600000,9,1373.76,-544.799,-92.0351,0,0,1,0,100,0),
(2600000,10,1377.67,-538.988,-92.0357,0,0,1,0,100,0),
(2600000,11,1379.94,-528.366,-92.0487,0,0,1,0,100,0),
(2600000,12,1380.24,-502.106,-92.0508,0,0,1,0,100,0),
(2600001,1,1381.73,-383.665,-92.047,0,0,2,0,100,0),
(2600001,2,1376.18,-378.505,-92.028,0,0,2,0,100,0),
(2600001,3,1372.21,-375.996,-92.0235,0,0,2,0,100,0),
(2600001,4,1351.61,-375.347,-92.0013,0,0,2,0,100,0),
(2600001,5,1341.2,-374.562,-92.001,0,0,2,0,100,0),
(2600001,6,1337.56,-373.773,-92.0085,0,0,2,0,100,0),
(2600001,7,1334.38,-372.228,-92.0103,0,0,2,0,100,0),
(2600001,8,1332.52,-370.581,-92.0103,0,0,2,0,100,0),
(2600001,9,1329.45,-364.775,-91.9988,0,0,2,0,100,0),
(2600001,10,1316.79,-346.794,-92.0414,0,0,2,0,100,0),
(2600002,1,1313.69,-345.468,-92.0495,0,0,2,0,100,0),
(2600002,2,1308.77,-340.488,-92.0403,0,0,2,0,100,0),
(2600002,3,1301.4,-333.015,-92.0543,0,0,2,0,100,0),
(2600002,4,1296.48,-328.033,-88.6423,0,0,2,0,100,0),
(2600002,5,1289.1,-320.56,-81.1147,0,0,2,0,100,0),
(2600002,6,1284.81,-316.2,-78.1531,0,0,2,0,100,0),
(2600002,7,1276.28,-306.266,-78.138,0,0,2,0,100,0),
(2600020,1,1118.16,-130.854,-74.3606,0,0,2,0,100,0),
(2600020,2,1084.36,-167.439,-65.3098,0,0,2,0,100,0);

SET @GUID := 600000;

DELETE FROM `creature` WHERE `guid` BETWEEN @GUID AND @GUID + 2;
INSERT INTO `creature` VALUES 
(@GUID,@ENTRY,230,2,1,0,0,1380.31,-824.814,-92.7219,1.65003,300,0,0,6144,0,0,0,0,0),
(@GUID + 1,@ENTRY + 1,230,2,1,0,0,1381.06,-386.57,-92.05,4.68,300,0,0,6144,0,0,0,0,0),
(@GUID + 2,@ENTRY + 2,230,2,300,0,1,1381.06,-386.57,-92.05,4.68,300,0,0,6144,0,0,0,0,0);
-- (@GUID + 2,@ENTRY + 2,230,2,300,0,0,1197.77, -170.88, -74.33,4.68,300,0,0,6144,0,0,0,0,0);

DELETE FROM `gameobject` WHERE `id` = 400504;

SET @GO_ENTRY:= 400600;

DELETE FROM `gameobject_template` WHERE `entry` BETWEEN @GO_ENTRY AND @GO_ENTRY + 1;
INSERT INTO `gameobject_template` VALUES 
(@GO_ENTRY,0,9223,'Cave In','','','',114,16,2,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'','',12340),
(@GO_ENTRY + 1,0,9223,'Cave In','','','',114,16,2,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'','',12340);


SET @GO_GUID := 280000;
DELETE FROM `gameobject` WHERE `id` IN (@GO_ENTRY, @GO_ENTRY + 1);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `VerifiedBuild`) VALUES
(@GO_GUID,     @GO_ENTRY, 230, 2, 1, 1104.65, -145.10, -69.74, 2.36012, -0, -0, -0.924628, -0.38087, 300, 0, 1, 0),
(@GO_GUID + 1, @GO_ENTRY + 1, 230, 2, 1, 1261.90, -317.43, -78.50, 2.36012, -0, -0, -0.924628, -0.38087, 300, 0, 1, 0),
(@GO_GUID + 2, @GO_ENTRY + 1, 230, 2, 1, 960.58, -208.85, -61.78, 2.36012, -0, -0, -0.924628, -0.38087, 300, 0, 1, 0),
(@GO_GUID + 3, @GO_ENTRY + 1, 230, 2, 1, 940.30, -231.38, -50.17, 2.36012, -0, -0, -0.924628, -0.38087, 300, 0, 1, 0);

SET @STAT_ENTRY = 800;

DELETE FROM `hellforge_boss_stats` WHERE `StatId` = @STAT_ENTRY;
INSERT INTO `hellforge_boss_stats` VALUES 
(@STAT_ENTRY, 213000, 1, 'Jonas Dark health');

DELETE FROM `creature_equip_template` WHERE `entry` = @ENTRY + 2;
INSERT INTO `creature_equip_template` VALUES (@ENTRY + 2, 1, 5194, 0, 0, 0);

UPDATE `quest_template` SET `Flags` = `Flags` | 2 WHERE `Id` BETWEEN 31000 AND 31005;

SET @TEXT_ENTRY := 1110010;
DELETE FROM `npc_text` WHERE `Id` BETWEEN @TEXT_ENTRY AND @TEXT_ENTRY + 2;
INSERT INTO `npc_text`(`ID`, `text0_0`) VALUES
(@TEXT_ENTRY, 'Hello $n, what can I do for you?'),
(@TEXT_ENTRY + 1, 'Let\'s move on, the sooner we leave this cursed place the better!'),
(@TEXT_ENTRY + 2, 'Heroes, you must stop him...');

SET @QUEST_ENTRY := 30012;
DELETE FROM `quest_template` WHERE `Id` = @QUEST_ENTRY;
INSERT INTO `quest_template` VALUES (@QUEST_ENTRY,2,80,80,0,4395,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,@QUEST_ENTRY - 1,0,0,31000,0,1000000,0,0,0,0,0,0,0,0,0,0,72,0,0,0,0,0,49426,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,'Meeting in Hellforge','Meet The Wanderer in Hellforge','I made it, friend! I’ve found my enemies’ hideout! They’ll regret stealing my possession. Get ready for the battle hero, I will be waiting for you in Hellforge. You can get there through the portal under Wyrmrest Temple in Dragonblight.', '', 'Good to see you pal, shall we start?', 'Are you ready to join me?','',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Meet The Wanderer in Hellforge','','','',1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,12340);

DELETE FROM `creature_queststarter` WHERE `quest` = @QUEST_ENTRY;
INSERT INTO `creature_queststarter` VALUES(200000, @QUEST_ENTRY);

DELETE FROM `creature_questender` WHERE `quest` = @QUEST_ENTRY;
INSERT INTO `creature_questender` VALUES(@ENTRY, @QUEST_ENTRY);