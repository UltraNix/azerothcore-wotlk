-- Bug: #909 Quest: The Blightcaller Cometh | Author: Shonsu - correct completion text
UPDATE `quest_template` SET `OfferRewardText` = "No. It... NO! How? An agent of the Forsaken? The CHAMPION of the Banshee Queen???$B$B<King Varian Wrynn slumps in defeat.>" WHERE `id` = 6186;

-- Bug: #905 Quest: Healthy Dragon Sclae | Author: Shonsu - poprawka do dropu
DELETE FROM `conditions` WHERE `SourceEntry` = 13920;
INSERT INTO `conditions` VALUES 
(1, 10678, 13920, 0, 0, 8, 0, 5529, 0, 0, 0, 0, 0, '', 'Healthy Dragon Scale will drop only if the player has Plagued Hatchlings');

-- Bug: #723 NPC: City Guards | Author: Shonsu - usuniecie Truesight Vision niektórym NPC
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (68, 1976, 1756, 3296) AND `id` = 0;

-- Bug: #681 Quest: The Master's Terrace | Author: Shonsu - minor corrections
UPDATE `creature_template` SET `flags_extra` = 3 WHERE `entry` = 17651;
UPDATE `creature_template` SET `unit_flags` = 33554432, `flags_extra` = 2, `InhabitType` = 7 WHERE `entry` = 17652;

-- Bug: #863 Quest: Matter of Time | Author: Shonsu - poprawienie spawnu mobow
DELETE FROM `smart_scripts` WHERE `entryorguid` = 10717 AND `id` = 1;
INSERT INTO `smart_scripts` VALUES
(10717, 0, 1, 0, 54, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 18, 10, 0, 0, 0, 0, 0, 0, 'Temporal Parasite - On Just Summond - Attack Start');

-- Bug: #873 NPC: Ghost of the Past | Author: Shonsu - dodanie AI
SET @ENTRY := 176116;
SET @ENTRY2 := 176142;
SET @ENTRY3 := 176143;
UPDATE `gameobject_template` SET `data7` = 0, `AIName` = "SmartGameObjectAI" WHERE `entry` IN (@ENTRY, @ENTRY2, @ENTRY3); -- 176117

DELETE FROM `smart_scripts` WHERE `entryorguid` = 10940 AND `id` = 2;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@ENTRY, @ENTRY2, @ENTRY3);
INSERT INTO `smart_scripts` VALUES
(10940, 0, 2, 0, 54, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 18, 10, 0, 0, 0, 0, 0, 0, 'Ghost of the Past - On Just Summond - Attack Start'),
(@ENTRY, 0, 0, 0, 10, 0, 100, 1, 0, 5, 1000, 1000, 12, 10940, 3, 300000, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Pamela`s Doll - LOS - Summon Ghost of the Past'),
(@ENTRY2, 0, 0, 0, 10, 0, 100, 1, 0, 5, 1000, 1000, 12, 10940, 3, 300000, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Pamela`s Doll - LOS - Summon Ghost of the Past'),
(@ENTRY3, 0, 0, 0, 10, 0, 100, 1, 0, 5, 1000, 1000, 12, 10940, 3, 300000, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Pamela`s Doll - LOS - Summon Ghost of the Past');

-- Bug: #876 NPC: Dormant Infernal | Author: Shonsu - dodanie AI
DELETE FROM `smart_scripts` WHERE `entryorguid` = 21080 AND `id` IN (1,2);
INSERT INTO `smart_scripts` VALUES
(21080, 0, 1, 0, 4, 0, 100, 1, 0, 0, 0, 0, 12, 19759, 3, 300000, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Dormant Infernal - On Aggro - Summon Infernal'),
(21080, 0, 2, 1, 61, 0, 100, 0, 0, 0, 0, 0, 41, 3000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Dormant Infernal - On Link - Despawn Self');

-- Bug: #882 NPC: Forlorn Spirit | Author: Shonsu - poprawa AI
DELETE FROM `smart_scripts` WHERE `entryorguid` = 2044 AND `id` = 3;
INSERT INTO `smart_scripts` VALUES
(2044, 0, 3, 0, 54, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 18, 10, 0, 0, 0, 0, 0, 0, 'Forlorn Spirit - On Just Summond - Attack Start');

-- Bug: #880 NPC: Crimson Courier | Author: Shonsu - Poprawienie formacji 
DELETE FROM `creature_formations` WHERE `leaderGUID` = 92287;
INSERT INTO `creature_formations` VALUES
(92287, 92887, 0, 0, 2, 0, 0),
(92287, 92288, 5, 200, 2, 0, 0),
(92287, 92291, 5, 160, 2, 0, 0), 
(92287, 92290, 5, 290, 2, 0, 0),
(92287, 92289, 5, 110, 2, 0, 0);

-- Bug: #872 NPC: Fallen Hero | Author: Shonsu - poprawka AI
DELETE FROM `smart_scripts` WHERE `entryorguid` = 10996 AND `id` = 4;
INSERT INTO `smart_scripts` VALUES
(10996, 0, 4, 0, 54, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 18, 10, 0, 0, 0, 0, 0, 0, 'Fallen Hero - On Just Summond - Attack Start');

-- Bug: #867  NPC: Rotting Worm | Author: Shonsu - poprawa zachowania
SET @ENTRY := 10925;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 54, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 18, 20, 0, 0, 0, 0, 0, 0, 'Rotting Worm - On Just Summon - Attack Start');

-- Bug: #870 NPC: Scarlet Executioner | Author: Shonsu - dodanie AI
SET @ENTRY := 1841;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 0, 0, 100, 0, 10000, 10000, 10000, 10000, 11, 16856, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Scarlet Executioner - IC - Cast Mortal Strike'),
(@ENTRY, 0, 1, 0, 2, 0, 100, 0, 0, 30, 2000, 2000, 11, 8599, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Scarlet Executioner - IC - Cast Enrage');

-- Bug: #869  NPC: Scarlet High Clerist | Author: Shonsu - dodanie AI
SET @ENTRY := 1839;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @ENTRY;
INSERT INTO `smart_scripts` VALUES
(@ENTRY, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 11, 17139, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Scarlet High Clerist - On Aggro - Cast Power Word Shield');

-- Bug: #858 NPC: Nancy Vishas | Author: Shonsu - przestawienie NPC
UPDATE `creature` SET `position_x` = 889.20, `position_y` = -120.34, `position_z` = 38.40 WHERE `guid` = 17090;

-- Bug #874
UPDATE `smart_scripts` SET `action_param2` = 1000, `action_param3` = 1000 WHERE `entryorguid` = 176307 AND `id` = 1;

-- NPC: Bleeding Hollow Tormentor | Author: Shonsu - poprawienie targetu fear-a
DELETE FROM `conditions` WHERE `SourceEntry` = 33924;

-- Bug: #860  Quest: Royal Gallery tabliczki | Author: Shonsu - Dodanie brakujących, poprawienie pozycji obecnych
SET @GUID := (SELECT MAX(guid) from gameobject) +100; 
UPDATE `gameobject` SET `orientation` = 3.9 WHERE `guid` = 20458;
UPDATE `gameobject` SET `position_x` = -8632.15, `position_y` = 767.33, `position_z` = 98.59, `orientation` = 0.79 WHERE `guid` = 26628;
DELETE FROM `gameobject` WHERE `guid` IN (@OGUID, @OGUID+1, @OGUID+2);
INSERT INTO `gameobject` VALUES
(@OGUID, 177201, 0, 1, 1, -8338.92, 509.51, 122.92, 2.22, 0, 0, 0, 0, 120, 0, 1, 0),
(@OGUID + 1, 25333, 0, 1, 1, -8324.59, 518.42, 122.93, 4.05, 0, 0, 0, 0, 120, 0, 1, 0),
(@OGUID + 2, 25331, 0, 1, 1, -8335.91, 532.45, 122.93, 3.74, 0, 0, 0, 0, 120, 0, 1, 0);

-- Bug: #859  Quest: Argent Dawn Commision | Author: Shonsu - Poprawka Offer Text-u
UPDATE `quest_template` SET `OfferRewardText` = "All who fight evil on behalf of the Argent Dawn must don our commission. Wearing such will earn your right to claim rewards our quartermasters have to offer.$B$BWhile under commission, you'll be able to acquire Scourgestones from slain Scourge; these are marks of insignia that they sometimes possess. Procure these insignia and bring them to me. For each set you turn in, you will receive our marker of heroism - the Argent Dawn Valor Token.$B$BAchieve your destiny, $C - join the fight today!" WHERE `id` = 5405;

-- Bug: #827  Quest: Getting the Bladespire Tanked | Author: Shonsu - poprawka
DELETE FROM `smart_scripts` WHERE `entryorguid` = 21241 AND `id` = 6;
INSERT INTO `smart_scripts` VALUES (19995, 0, 6, 0, 38, 0, 100, 0, 1, 1, 0, 0, 80, 1999501, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Bladespire Brute - On Data Set 1 1 - Run Script 2');

-- Bug: #852  NPC: Anduin Wrynn | Author: Dootz - usunięcie gossipa z blednego patcha
UPDATE `creature_template` SET `npcflag` = 2 WHERE `entry` = 1747;

-- Bug: #838  NPC: Gradok | Author: Shonsu - dodanie formacji
DELETE FROM `creature_formations` WHERE `leaderGUID` = 9203;
INSERT INTO `creature_formations` VALUES
(9203, 9203, 0, 0, 2, 0, 0),
(9203, 9204, 5, 270, 2, 0, 0),
(9203, 9205, 5, 0, 2, 0, 0);

-- Bug: #835 NPC: James Halloran | Author: Shonsu - unieruchomienie NPCa
UPDATE `creature` SET `MovementType` = 0 WHERE `id` = 2094;

-- Bug: #833 NPC: Terl Arakor | Author: Shonsu - usuniecie zbednego gossipa
UPDATE `creature_template` SET `npcflag` = 0 WHERE `entry` = 2153;