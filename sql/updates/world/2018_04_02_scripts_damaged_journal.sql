SET @QUEST = 12026;
SET @QUEST2 = 12054;
SET @NPC = 26584;
SET @SCOUT = 26666;

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @NPC;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@NPC, @NPC*100, @NPC*100+1);
INSERT INTO `smart_scripts` VALUES
(@NPC, 0, 0, 0, 20, 0, 100, 0, @QUEST, 0, 0, 0, 80, @NPC*100, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sage Paluna - on quest rewarded - start script'),
(@NPC*100, 9, 0, 0, 0, 0, 100, 0, 1000, 1000, 1000, 1000, 83, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sage Paluna - Script - Remove npc flag'),
(@NPC*100, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 83, 2, 0, 0, 0, 0, 0, 19, @SCOUT, 30, 0, 0, 0, 0, 0, 'Scout Vor\'takh - Script - Remove npc flag'),
(@NPC*100, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sage Paluna - Script - Say Line 0'),
(@NPC*100, 9, 3, 0, 0, 0, 100, 0, 3000, 3000, 3000, 3000, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sage Paluna - Script - Say Line 1'),
(@NPC*100, 9, 4, 0, 0, 0, 100, 0, 3000, 3000, 3000, 3000, 1, 4, 0, 0, 0, 0, 0, 19, @SCOUT, 30, 0, 0, 0, 0, 0, 'Scout Vor\'takh - Script - Say line 4'),
(@NPC*100, 9, 5, 0, 0, 0, 100, 0, 3000, 3000, 3000, 3000, 1, 5, 0, 0, 0, 0, 0, 19, @SCOUT, 30, 0, 0, 0, 0, 0, 'Scout Vor\'takh - Script - Say line 5'),
(@NPC*100, 9, 6, 0, 0, 0, 100, 0, 5000, 5000, 5000, 5000, 1, 6, 0, 0, 0, 0, 0, 19, @SCOUT, 30, 0, 0, 0, 0, 0, 'Scout Vor\'takh - Script - Say line 6'),
(@NPC*100, 9, 7, 0, 0, 0, 100, 0, 5000, 5000, 5000, 5000, 1, 7, 0, 0, 0, 0, 0, 19, @SCOUT, 30, 0, 0, 0, 0, 0, 'Scout Vor\'takh - Script - Say line 7'),
(@NPC*100, 9, 8, 0, 0, 0, 100, 0, 3000, 3000, 3000, 3000, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sage Paluna - Script - Say Line 2'),
(@NPC*100, 9, 9, 0, 0, 0, 100, 0, 3000, 3000, 3000, 3000, 1, 8, 0, 0, 0, 0, 0, 19, @SCOUT, 30, 0, 0, 0, 0, 0, 'Scout Vor\'takh - Script - Say line 8'),
(@NPC*100, 9, 10, 0, 0, 0, 100, 0, 5000, 5000, 5000, 5000, 1, 9, 0, 0, 0, 0, 0, 19, @SCOUT, 30, 0, 0, 0, 0, 0, 'Scout Vor\'takh - Script - Say line 9'),
(@NPC*100, 9, 11, 0, 0, 0, 100, 0, 3000, 3000, 3000, 3000, 82, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sage Paluna - Script - Add npc flag'),
(@NPC*100, 9, 12, 0, 0, 0, 100, 0, 0, 0, 0, 0, 82, 2, 0, 0, 0, 0, 0, 19, @SCOUT, 30, 0, 0, 0, 0, 0, 'Scout Vor\'takh - Script - Add npc flag'),

(@NPC, 0, 1, 0, 20, 0, 100, 0, @QUEST2, 0, 0, 0, 80, @NPC*100+1, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sage Paluna - On Quest rewarded - Start Script'),
(@NPC*100+1, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 83, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sage Paluna - Script - remove npc flag'),
(@NPC*100+1, 9, 1, 0, 0, 0, 100, 0, 3000, 3000, 3000, 3000, 5, 16, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sage Paluna - Script - emote'),
(@NPC*100+1, 9, 2, 0, 0, 0, 100, 0, 5000, 5000, 5000, 5000, 1, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sage Paluna - Script - Say Line 3'),
(@NPC*100+1, 9, 3, 0, 0, 0, 100, 0, 5000, 5000, 5000, 5000, 1, 4, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sage Paluna - Script - Say Line 4'),
(@NPC*100+1, 9, 4, 0, 0, 0, 100, 0, 5000, 5000, 5000, 5000, 1, 5, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sage Paluna - Script - Say Line 5'),
(@NPC*100+1, 9, 5, 0, 0, 0, 100, 0, 5000, 5000, 5000, 5000, 1, 6, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sage Paluna - Script - Say Line 6'),
(@NPC*100+1, 9, 6, 0, 0, 0, 100, 0, 5000, 5000, 5000, 5000, 1, 7, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sage Paluna - Script - Say Line 7'),
(@NPC*100+1, 9, 7, 0, 0, 0, 100, 0, 0, 0, 0, 0, 82, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sage Paluna - Script - Add npc flag');

DELETE FROM `creature_text` WHERE `entry` = @NPC;
DELETE FROM `creature_text` WHERE `entry` = @SCOUT AND `groupid` IN (4,5,6,7,8,9);
INSERT INTO `creature_text` VALUES
(@NPC, 0, 0, 'This is an intriguing find, $n, but I don\'t know what to make of it.', 12, 0, 100, 0, 0, 0, 0, 'Sage Paluna'),
(@NPC, 1, 0, 'The language is unfamiliar and for all we know, it\'s just some soldier\'s journal.', 12, 0, 100, 0, 0, 0, 0, 'Sage Paluna'),
(@NPC, 2, 0, 'What do you mean?', 12, 0, 100, 0, 0, 0, 0, 'Sage Paluna'),
(@NPC, 3, 0, 'Let us see what this journal reveals.', 12, 0, 100, 0, 0, 0, 0, 'Sage Paluna'),
(@NPC, 4, 0, 'Scout Vor\'takh\'s hunch was correct. Brann Bronzebeard visited Thor Modan recently and this journal records his findings.', 12, 0, 100, 0, 0, 0, 0, 'Sage Paluna'),
(@NPC, 5, 0, 'He managed to explore the ruins before the battle began, discovering three runic plates inscribed with prophecies.', 12, 0, 100, 0, 0, 0, 0, 'Sage Paluna'),
(@NPC, 6, 0, 'Brann doesn\'t record the translations, but it says he committed them to memory before fleeing the battle.', 12, 0, 100, 0, 0, 0, 0, 'Sage Paluna'),
(@NPC, 7, 0, 'If you can translate those plates, we can find and capture Brann.', 12, 0, 100, 0, 0, 0, 0, 'Sage Paluna'),

(@SCOUT, 4, 0, 'Let me take a look at that.', 12, 0, 100, 0, 0, 0, 0, 'Scout Vor\'takh'),
(@SCOUT, 5, 0, 'Hmm...', 12, 0, 100, 0, 0, 0, 0, 'Scout Vor\'takh'),
(@SCOUT, 6, 0, 'This journal is written in dwarven. I can\'t read this scrawl, but I can make out one thing.', 12, 0, 100, 0, 0, 0, 0, 'Scout Vor\'takh'),
(@SCOUT, 7, 0, '\'Brann Bronzebeard.\' The brother of Ironforge\'s king? You may have spoken too soon, Paluna.', 12, 0, 100, 0, 0, 0, 0, 'Scout Vor\'takh'),
(@SCOUT, 8, 0, 'Think about how valuable a member of the dwarven royal family would be as a hostage.', 12, 0, 100, 0, 0, 0, 0, 'Scout Vor\'takh'),
(@SCOUT, 9, 0, 'If he\'s in the area, we must find him. First, though, we\'ll need a way to decipher this journal.', 12, 0, 100, 0, 0, 0, 0, 'Scout Vor\'takh');

UPDATE `quest_template` SET `NextQuestIdChain` = 0 WHERE `id` = 12026;
