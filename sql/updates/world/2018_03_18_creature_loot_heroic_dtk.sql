SET @ENTRY = 31355;
UPDATE `creature_template` SET `lootid` = @ENTRY WHERE `entry` = @ENTRY;
DELETE FROM `creature_loot_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_loot_template` VALUES
(@ENTRY, 22829, 2.5, 1, 0, 1, 1), 
(@ENTRY, 22832, 1.1, 1, 0, 1, 1), 
(@ENTRY, 26040, 15.8, 1, 0, -26040, 1), 
(@ENTRY, 33444, 3.7, 1, 0, 1, 1), 
(@ENTRY, 33452, 8, 1, 0, 1, 1), 
(@ENTRY, 35639, 1.2, 1, 0, 1, 1), 
(@ENTRY, 35640, 1, 1, 0, 1, 1), 
(@ENTRY, 37799, 0.4, 1, 0, 1, 1), 
(@ENTRY, 37800, 0.4, 1, 0, 1, 1), 
(@ENTRY, 37801, 0.4, 1, 0, 1, 1), 
(@ENTRY, 42108, -33, 1, 0, 1, 1), 
(@ENTRY, 43624, 0.02, 1, 0, 1, 1), 
(@ENTRY, 43852, 9.4, 1, 0, 1, 1), 
(@ENTRY, 45912, 0.1, 1, 0, 1, 1);

SET @BASIC = (SELECT `entry` FROM `creature_template` WHERE `difficulty_entry_1` = @ENTRY);
DELETE FROM `creature_loot_template` WHERE `entry` = @BASIC AND `item` IN (37799,37800,37801);
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 15.8 WHERE `item` = 26040 AND `entry` = @BASIC;

SET @ENTRY = 31354;
UPDATE `creature_template` SET `lootid` = @ENTRY WHERE `entry` = @ENTRY;
DELETE FROM `creature_loot_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_loot_template` VALUES
(@ENTRY, 26000, 6, 1, 1, -26000, 1),
(@ENTRY, 26040, 13.7, 1, 0, -26040, 1),
(@ENTRY, 33372, 1.9, 1, 0, 1, 1),
(@ENTRY, 33396, 1.8, 1, 0, 1, 1),
(@ENTRY, 33444, 4.7, 1, 0, 1, 1),
(@ENTRY, 33452, 7.5, 1, 0, 1, 1),
(@ENTRY, 35639, 1.6, 1, 0, 1, 1),
(@ENTRY, 37799, 0.4, 1, 0, 1, 1),
(@ENTRY, 37800, 0.4, 1, 0, 1, 1),
(@ENTRY, 37801, 0.4, 1, 0, 1, 1),
(@ENTRY, 42108, -33, 1, 0, 1, 1),
(@ENTRY, 43507, 0.2, 1, 0, 1, 1),
(@ENTRY, 43508, 0.2, 1, 0, 1, 1),
(@ENTRY, 43509, 0.2, 1, 0, 1, 1),
(@ENTRY, 43510, 0.2, 1, 0, 1, 1),
(@ENTRY, 43622, 1.3, 1, 0, 1, 1),
(@ENTRY, 43624, 0.02, 1, 0, 1, 1),
(@ENTRY, 43852, 11.1, 1, 0, 1, 1),
(@ENTRY, 45912, 0.1, 1, 0, 1, 1);

SET @BASIC = (SELECT `entry` FROM `creature_template` WHERE `difficulty_entry_1` = @ENTRY);
DELETE FROM `creature_loot_template` WHERE `entry` = @BASIC AND `item` IN (37799,37800,37801);
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 10.6 WHERE `item` = 26040 AND `entry` = @BASIC;

SET @ENTRY = 31359;
UPDATE `creature_template` SET `lootid` = @ENTRY WHERE `entry` = @ENTRY;
DELETE FROM `creature_loot_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_loot_template` VALUES
(@ENTRY, 22832, 3.1, 1, 0, 1, 1),
(@ENTRY, 26009, 2, 1, 1, -26009, 1),
(@ENTRY, 26040, 15.4, 1, 0, -26040, 1),
(@ENTRY, 33444, 3.6, 1, 0, 1, 1),
(@ENTRY, 33452, 6.8, 1, 0, 1, 1),
(@ENTRY, 35639, 1.1, 1, 0, 1, 1),
(@ENTRY, 35640, 1.1, 1, 0, 1, 1),
(@ENTRY, 36409, 2.1, 1, 0, 1, 1),
(@ENTRY, 36675, 2.4, 1, 0, 1, 1),
(@ENTRY, 37799, 1.4, 1, 0, 1, 1),
(@ENTRY, 37800, 1.4, 1, 0, 1, 1),
(@ENTRY, 37801, 1.4, 1, 0, 1, 1),
(@ENTRY, 43622, 1, 1, 0, 1, 1),
(@ENTRY, 43852, 8.6, 1, 0, 1, 1),
(@ENTRY, 45912, 0.1, 1, 0, 1, 1);

SET @BASIC = (SELECT `entry` FROM `creature_template` WHERE `difficulty_entry_1` = @ENTRY);
DELETE FROM `creature_loot_template` WHERE `entry` = @BASIC AND `item` IN (37799,37800,37801);
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 14.2 WHERE `item` = 26040 AND `entry` = @BASIC;

SET @ENTRY = 31363;
UPDATE `creature_template` SET `lootid` = @ENTRY WHERE `entry` = @ENTRY;
DELETE FROM `creature_loot_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_loot_template` VALUES 
(@ENTRY, 26007, 2, 1, 1, -26007, 1),
(@ENTRY, 26009, 2, 1, 1, -26009, 1),
(@ENTRY, 26040, 15.8, 1, 0, -26040, 1),
(@ENTRY, 33444, 4.6, 1, 0, 1, 1),
(@ENTRY, 33452, 6.2, 1, 0, 1, 1),
(@ENTRY, 35639, 2.6, 1, 0, 1, 1),
(@ENTRY, 35640, 1.1, 1, 0, 1, 1),
(@ENTRY, 35641, 1.1, 1, 0, 1, 1),
(@ENTRY, 36003, 1.8, 1, 0, 1, 1),
(@ENTRY, 36421, 1.9, 1, 0, 1, 1),
(@ENTRY, 37799, 0.1, 1, 0, 1, 1),
(@ENTRY, 37800, 0.1, 1, 0, 1, 1),
(@ENTRY, 37801, 0.1, 1, 0, 1, 1),
(@ENTRY, 43852, 7.7, 1, 0, 1, 1),
(@ENTRY, 45912, 0.1, 1, 0, 1, 1);

SET @BASIC = (SELECT `entry` FROM `creature_template` WHERE `difficulty_entry_1` = @ENTRY);
DELETE FROM `creature_loot_template` WHERE `entry` = @BASIC AND `item` IN (37799,37800,37801);
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 14.2 WHERE `item` = 26040 AND `entry` = @BASIC;


SET @ENTRY = 31336;
UPDATE `creature_template` SET `lootid` = @ENTRY WHERE `entry` = @ENTRY;
DELETE FROM `creature_loot_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_loot_template` VALUES
(@ENTRY, 33629, 73.6, 1, 0, 2, 4),
(@ENTRY, 33630, 17.3, 1, 0, 2, 4),
(@ENTRY, 37799, 1.2, 1, 0, 1, 1),
(@ENTRY, 37800, 1.2, 1, 0, 1, 1),
(@ENTRY, 37801, 1.1, 1, 0, 1, 1),
(@ENTRY, 42253, 11, 1, 0, 1, 1),
(@ENTRY, 45912, 0.1, 1, 0, 1, 1);

SET @BASIC = (SELECT `entry` FROM `creature_template` WHERE `difficulty_entry_1` = @ENTRY);
DELETE FROM `creature_loot_template` WHERE `entry` = @BASIC AND `item` IN (37799,37800,37801);

SET @ENTRY = 31351;
UPDATE `creature_template` SET `lootid` = @ENTRY WHERE `entry` = @ENTRY;
DELETE FROM `creature_loot_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_loot_template` VALUES 
(@ENTRY, 26000, 6, 1, 1, -26000, 1),
(@ENTRY, 26010, 2, 1, 1, -26010, 1),
(@ENTRY, 26040, 23, 1, 0, -26040, 1),
(@ENTRY, 33439, 4, 1, 0, 1, 1),
(@ENTRY, 33444, 3.1, 1, 0, 1, 1),
(@ENTRY, 33452, 6.3, 1, 0, 1, 1),
(@ENTRY, 35641, 1.7, 1, 0, 1, 1),
(@ENTRY, 36011, 4.2, 1, 0, 1, 1),
(@ENTRY, 37757, 4, 1, 0, 1, 1),
(@ENTRY, 37799, 0.1, 1, 0, 1, 1),
(@ENTRY, 37800, 0.1, 1, 0, 1, 1),
(@ENTRY, 37801, 0.1, 1, 0, 1, 1),
(@ENTRY, 42108, -33, 1, 0, 1, 1),
(@ENTRY, 43624, 0.02, 1, 0, 1, 1),
(@ENTRY, 43852, 7.9, 1, 0, 1, 1),
(@ENTRY, 45912, 0.1, 1, 0, 1, 1);

SET @BASIC = (SELECT `entry` FROM `creature_template` WHERE `difficulty_entry_1` = @ENTRY);
DELETE FROM `creature_loot_template` WHERE `entry` = @BASIC AND `item` IN (37799,37800,37801);
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 24.2 WHERE `item` = 26040 AND `entry` = @BASIC;

SET @ENTRY = 31337;
UPDATE `creature_template` SET `lootid` = @ENTRY WHERE `entry` = @ENTRY;
DELETE FROM `creature_loot_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_loot_template` VALUES
(@ENTRY, 33569, 74, 1, 0, 1, 1),
(@ENTRY, 33571, 15.6, 1, 0, 1, 1),
(@ENTRY, 37799, 3.1, 1, 0, 1, 1),
(@ENTRY, 37800, 4.1, 1, 0, 1, 1),
(@ENTRY, 37801, 1.1, 1, 0, 1, 1),
(@ENTRY, 43624, 0.02, 1, 0, 1, 1),
(@ENTRY, 45912, 0.1, 1, 0, 1, 1);

SET @BASIC = (SELECT `entry` FROM `creature_template` WHERE `difficulty_entry_1` = @ENTRY);
DELETE FROM `creature_loot_template` WHERE `entry` = @BASIC AND `item` IN (37799,37800,37801);

SET @ENTRY = 31342;
UPDATE `creature_template` SET `lootid` = @ENTRY WHERE `entry` = @ENTRY;
DELETE FROM `creature_loot_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_loot_template` VALUES
(@ENTRY, 26008, 2, 1, 1, -26008, 1),
(@ENTRY, 26009, 2, 1, 1, -26009, 1),
(@ENTRY, 26040, 20.4, 1, 0, -26040, 1),
(@ENTRY, 33444, 5.2, 1, 0, 1, 1),
(@ENTRY, 33452, 7.6, 1, 0, 1, 1),
(@ENTRY, 35640, 1.3, 1, 0, 1, 1),
(@ENTRY, 35641, 1, 1, 0, 1, 1),
(@ENTRY, 36115, 1.7, 1, 0, 1, 1),
(@ENTRY, 36331, 1.4, 1, 0, 1, 1),
(@ENTRY, 37799, 1.1, 1, 0, 1, 1),
(@ENTRY, 37800, 3.1, 1, 0, 1, 1),
(@ENTRY, 37801, 2.1, 1, 0, 1, 1),
(@ENTRY, 42108, -33, 1, 0, 1, 1),
(@ENTRY, 43624, 0.02, 1, 0, 1, 1),
(@ENTRY, 43852, 9.7, 1, 0, 1, 1),
(@ENTRY, 45912, 0.1, 1, 0, 1, 1);

SET @BASIC = (SELECT `entry` FROM `creature_template` WHERE `difficulty_entry_1` = @ENTRY);
DELETE FROM `creature_loot_template` WHERE `entry` = @BASIC AND `item` IN (37799,37800,37801);
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 12.2 WHERE `item` = 26040 AND `entry` = @BASIC;

SET @ENTRY = 31340;
UPDATE `creature_template` SET `lootid` = @ENTRY WHERE `entry` = @ENTRY;
DELETE FROM `creature_loot_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_loot_template` VALUES
(@ENTRY, 26000, 6, 1, 1, -26000, 1),
(@ENTRY, 26040, 28.7, 1, 0, -26040, 1),
(@ENTRY, 33393, 1.4, 1, 0, 1, 1),
(@ENTRY, 33438, 1.2, 1, 0, 1, 1),
(@ENTRY, 33444, 3.6, 1, 0, 1, 1),
(@ENTRY, 33452, 5.7, 1, 0, 1, 1),
(@ENTRY, 35640, 1, 1, 0, 1, 1),
(@ENTRY, 35641, 1.8, 1, 0, 1, 1),
(@ENTRY, 37799, 4.1, 1, 0, 1, 1),
(@ENTRY, 37800, 3.1, 1, 0, 1, 1),
(@ENTRY, 37801, 6.1, 1, 0, 1, 1),
(@ENTRY, 43624, 0.02, 1, 0, 1, 1),
(@ENTRY, 43852, 9.1, 1, 0, 1, 1),
(@ENTRY, 45912, 0.1, 1, 0, 1, 1);

SET @BASIC = (SELECT `entry` FROM `creature_template` WHERE `difficulty_entry_1` = @ENTRY);
DELETE FROM `creature_loot_template` WHERE `entry` = @BASIC AND `item` IN (37799,37800,37801);
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 15.2 WHERE `item` = 26040 AND `entry` = @BASIC;

SET @ENTRY = 31343;
UPDATE `creature_template` SET `lootid` = @ENTRY WHERE `entry` = @ENTRY;
DELETE FROM `creature_loot_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_loot_template` VALUES
(@ENTRY, 29567, 10.7, 1, 0, 1, 1),
(@ENTRY, 29568, 4.4, 1, 0, 1, 1),
(@ENTRY, 37799, 2.1, 1, 0, 1, 1),
(@ENTRY, 37800, 1.1, 1, 0, 1, 1),
(@ENTRY, 37801, 3.1, 1, 0, 1, 1),
(@ENTRY, 43624, 0.02, 1, 0, 1, 1),
(@ENTRY, 44782, 61.1, 1, 0, 3, 5),
(@ENTRY, 44783, 13.7, 1, 0, 2, 4),
(@ENTRY, 45912, 0.1, 1, 0, 1, 1);

SET @BASIC = (SELECT `entry` FROM `creature_template` WHERE `difficulty_entry_1` = @ENTRY);
DELETE FROM `creature_loot_template` WHERE `entry` = @BASIC AND `item` IN (37799,37800,37801);

SET @ENTRY = 31351;
UPDATE `creature_template` SET `lootid` = @ENTRY WHERE `entry` = @ENTRY;
DELETE FROM `creature_loot_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_loot_template` VALUES
(@ENTRY, 26000, 6, 1, 1, -26000, 1),
(@ENTRY, 26010, 2, 1, 1, -26010, 1),
(@ENTRY, 26040, 23, 1, 0, -26040, 1),
(@ENTRY, 33439, 4, 1, 0, 1, 1),
(@ENTRY, 33444, 3.1, 1, 0, 1, 1),
(@ENTRY, 33452, 6.3, 1, 0, 1, 1),
(@ENTRY, 35641, 1.7, 1, 0, 1, 1),
(@ENTRY, 36011, 4.2, 1, 0, 1, 1),
(@ENTRY, 37757, 4, 1, 0, 1, 1),
(@ENTRY, 37799, 5.1, 1, 0, 1, 1),
(@ENTRY, 37800, 5.1, 1, 0, 1, 1),
(@ENTRY, 37801, 5.1, 1, 0, 1, 1),
(@ENTRY, 42108, -33, 1, 0, 1, 1),
(@ENTRY, 43624, 0.02, 1, 0, 1, 1),
(@ENTRY, 43852, 7.9, 1, 0, 1, 1),
(@ENTRY, 45912, 0.1, 1, 0, 1, 1);

SET @BASIC = (SELECT `entry` FROM `creature_template` WHERE `difficulty_entry_1` = @ENTRY);
DELETE FROM `creature_loot_template` WHERE `entry` = @BASIC AND `item` IN (37799,37800,37801);
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 18.2 WHERE `item` = 26040 AND `entry` = @BASIC;

SET @ENTRY = 31357;
UPDATE `creature_template` SET `lootid` = @ENTRY WHERE `entry` = @ENTRY;
DELETE FROM `creature_loot_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_loot_template` VALUES
(@ENTRY, 26002, 6, 1, 1, -26002, 1),
(@ENTRY, 26010, 2, 1, 1, -26010, 1),
(@ENTRY, 26011, 2, 1, 1, -26011, 1),
(@ENTRY, 26040, 22.6, 1, 0, -26040, 1),
(@ENTRY, 33402, 2.8, 1, 0, 1, 1),
(@ENTRY, 33444, 3.8, 1, 0, 1, 1),
(@ENTRY, 33452, 6.1, 1, 0, 1, 1),
(@ENTRY, 35640, 1.3, 1, 0, 1, 1),
(@ENTRY, 36124, 2.4, 1, 0, 1, 1),
(@ENTRY, 36250, 2.4, 1, 0, 1, 1),
(@ENTRY, 37799, 4.1, 1, 0, 1, 1),
(@ENTRY, 37800, 4.1, 1, 0, 1, 1),
(@ENTRY, 37801, 4.1, 1, 0, 1, 1),
(@ENTRY, 42108, -33, 1, 0, 1, 1),
(@ENTRY, 43624, 0.02, 1, 0, 1, 1),
(@ENTRY, 43852, 9.5, 1, 0, 1, 1),
(@ENTRY, 45912, 0.1, 1, 0, 1, 1);

SET @BASIC = (SELECT `entry` FROM `creature_template` WHERE `difficulty_entry_1` = @ENTRY);
DELETE FROM `creature_loot_template` WHERE `entry` = @BASIC AND `item` IN (37799,37800,37801);
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 20.2 WHERE `item` = 26040 AND `entry` = @BASIC;

SET @ENTRY = 31339;
UPDATE `creature_template` SET `lootid` = @ENTRY WHERE `entry` = @ENTRY;
DELETE FROM `creature_loot_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_loot_template` VALUES
(@ENTRY, 26040, 4.1, 1, 0, -26040, 1),
(@ENTRY, 37799, 2.1, 1, 0, 1, 1),
(@ENTRY, 37800, 3.1, 1, 0, 1, 1),
(@ENTRY, 37801, 4.1, 1, 0, 1, 1),
(@ENTRY, 38303, 66, 1, 0, 1, 1),
(@ENTRY, 43624, 0.02, 1, 0, 1, 1),
(@ENTRY, 43852, 1.1, 1, 0, 1, 1),
(@ENTRY, 45912, 0.1, 1, 0, 1, 1);

SET @BASIC = (SELECT `entry` FROM `creature_template` WHERE `difficulty_entry_1` = @ENTRY);
DELETE FROM `creature_loot_template` WHERE `entry` = @BASIC AND `item` IN (37799,37800,37801);

SET @ENTRY = 31352;
UPDATE `creature_template` SET `lootid` = @ENTRY WHERE `entry` = @ENTRY;
DELETE FROM `creature_loot_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_loot_template` VALUES
(@ENTRY, 22829, 2.4, 1, 0, 1, 1),
(@ENTRY, 26001, 6, 1, 1, -26001, 1),
(@ENTRY, 26040, 22.2, 1, 0, -26040, 1),
(@ENTRY, 33427, 1.3, 1, 0, 1, 1),
(@ENTRY, 33431, 1.2, 1, 0, 1, 1),
(@ENTRY, 33444, 3.7, 1, 0, 1, 1),
(@ENTRY, 33452, 8.9, 1, 0, 1, 1),
(@ENTRY, 35639, 1.1, 1, 0, 1, 1),
(@ENTRY, 35640, 2.2, 1, 0, 1, 1),
(@ENTRY, 35641, 1, 1, 0, 1, 1),
(@ENTRY, 37799, 3.1, 1, 0, 1, 1),
(@ENTRY, 37800, 3.1, 1, 0, 1, 1),
(@ENTRY, 37801, 3.1, 1, 0, 1, 1),
(@ENTRY, 42108, -33, 1, 0, 1, 1),
(@ENTRY, 43624, 0.02, 1, 0, 1, 1),
(@ENTRY, 43852, 9, 1, 0, 1, 1),
(@ENTRY, 45912, 0.1, 1, 0, 1, 1);

SET @BASIC = (SELECT `entry` FROM `creature_template` WHERE `difficulty_entry_1` = @ENTRY);
DELETE FROM `creature_loot_template` WHERE `entry` = @BASIC AND `item` IN (37799,37800,37801);
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 22.2 WHERE `item` = 26040 AND `entry` = @BASIC;

SET @ENTRY = 31338;
UPDATE `creature_template` SET `lootid` = @ENTRY WHERE `entry` = @ENTRY;
DELETE FROM `creature_loot_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_loot_template` VALUES
(@ENTRY, 26009, 2, 1, 1, -26009, 1),
(@ENTRY, 26010, 2, 1, 1, -26010, 1),
(@ENTRY, 26040, 17.9, 1, 0, -26040, 1),
(@ENTRY, 33444, 4.6, 1, 0, 1, 1),
(@ENTRY, 33454, 6.4, 1, 0, 1, 1),
(@ENTRY, 35639, 1, 1, 0, 1, 1),
(@ENTRY, 35640, 1.4, 1, 0, 1, 1),
(@ENTRY, 35641, 1.2, 1, 0, 1, 1),
(@ENTRY, 36350, 4.2, 1, 0, 1, 1),
(@ENTRY, 36423, 1, 1, 0, 1, 1),
(@ENTRY, 37799, 4.1, 1, 0, 1, 1),
(@ENTRY, 37800, 4.1, 1, 0, 1, 1),
(@ENTRY, 37801, 4.1, 1, 0, 1, 1),
(@ENTRY, 43624, 0.02, 1, 0, 1, 1),
(@ENTRY, 43852, 10.6, 1, 0, 1, 1),
(@ENTRY, 45912, 0.1, 1, 0, 1, 1);

SET @BASIC = (SELECT `entry` FROM `creature_template` WHERE `difficulty_entry_1` = @ENTRY);
DELETE FROM `creature_loot_template` WHERE `entry` = @BASIC AND `item` IN (37799,37800,37801);
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 17.2 WHERE `item` = 26040 AND `entry` = @BASIC;

SET @ENTRY = 31345;
UPDATE `creature_template` SET `lootid` = @ENTRY WHERE `entry` = @ENTRY;
DELETE FROM `creature_loot_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_loot_template` VALUES
(@ENTRY, 26040, 3.8, 1, 0, -26040, 1),
(@ENTRY, 37799, 3.1, 1, 0, 1, 1),
(@ENTRY, 37800, 3.1, 1, 0, 1, 1),
(@ENTRY, 37801, 3.1, 1, 0, 1, 1),
(@ENTRY, 38303, 67, 1, 0, 1, 1),
(@ENTRY, 43624, 0.02, 1, 0, 1, 1),
(@ENTRY, 43852, 1.2, 1, 0, 1, 1),
(@ENTRY, 45912, 0.1, 1, 0, 1, 1);

SET @BASIC = (SELECT `entry` FROM `creature_template` WHERE `difficulty_entry_1` = @ENTRY);
DELETE FROM `creature_loot_template` WHERE `entry` = @BASIC AND `item` IN (37799,37800,37801);
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 2.2 WHERE `item` = 26040 AND `entry` = @BASIC;


