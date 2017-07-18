SET @ENTRY := 34069;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
SET @ITEM := 200000;
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM, 3, 1, 0, -34155, 1);

SET @ENTRY := 34086;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 1, 3, 1, 0, -34155, 1);

SET @ENTRY := 34085;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 2, 3, 1, 0, -34155, 1);

SET @ENTRY := 34273;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 3, 3, 1, 0, -34155, 1);

SET @ENTRY := 34267;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 4, 3, 1, 0, -34155, 1);

SET @ENTRY := 34271;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 5, 3, 1, 0, -34155, 1);

SET @ENTRY := 34269;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 6, 3, 1, 0, -34155, 1);

SET @ENTRY := 34199;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 7, 3, 1, 0, -34155, 1);

SET @ENTRY := 34198;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 8, 3, 1, 0, -34155, 1);

SET @ENTRY := 34190;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 9, 3, 1, 0, -34155, 1);

SET @ENTRY := 34196;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 10, 3, 1, 0, -34155, 1);

SET @ENTRY := 34197;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 11, 3, 1, 0, -34155, 1);

SET @ENTRY := 33722;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 12, 3, 1, 0, -34155, 1);

SET @ENTRY := 34133;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 13, 3, 1, 0, -34155, 1);

SET @ENTRY := 34137;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 14, 3, 1, 0, -34155, 1);

SET @ENTRY := 34135;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 15, 3, 1, 0, -34155, 1);

SET @ENTRY := 34134;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 16, 3, 1, 0, -34155, 1);

SET @ENTRY := 33722;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 17, 3, 1, 0, -34155, 1);

SET @ENTRY := 33754;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 18, 3, 1, 0, -34155, 1);

SET @ENTRY := 33755;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 19, 3, 1, 0, -34155, 1);

SET @ENTRY := 33431;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 20, 3, 1, 0, -34155, 1);

SET @ENTRY := 33430;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 21, 3, 1, 0, -34155, 1);

SET @ENTRY := 33528;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 22, 3, 1, 0, -34155, 1);

SET @ENTRY := 33527;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 23, 3, 1, 0, -34155, 1);

SET @ENTRY := 33525;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 24, 3, 1, 0, -34155, 1);

SET @ENTRY := 33526;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 25, 3, 1, 0, -34155, 1);

SET @ENTRY := 33354;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 26, 3, 1, 0, -34155, 1);

SET @ENTRY := 33355;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 27, 3, 1, 0, -34155, 1);

SET @ENTRY := 34191;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 28, 3, 1, 0, -34155, 1);

SET @ENTRY := 34183;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 29, 3, 1, 0, -34155, 1);

SET @ENTRY := 34184;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 30, 3, 1, 0, -34155, 1);

SET @ENTRY := 34193;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 31, 3, 1, 0, -34155, 1);

SET @ENTRY := 33822;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 32, 3, 1, 0, -34155, 1);

SET @ENTRY := 33818;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 33, 3, 1, 0, -34155, 1);

SET @ENTRY := 33823;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 34, 3, 1, 0, -34155, 1);

SET @ENTRY := 33824;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 35, 3, 1, 0, -34155, 1);

SET @ENTRY := 33772;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 36, 3, 1, 0, -34155, 1);

SET @ENTRY := 33820;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 37, 3, 1, 0, -34155, 1);

SET @ENTRY := 33819;
SET @DIFFENTRY := (SELECT `difficulty_entry_1` FROM `creature_template` WHERE `entry`=@ENTRY);
SET @LOOTID := (SELECT `lootid` FROM `creature_template` WHERE `entry`=@DIFFENTRY);
DELETE FROM `creature_loot_template` WHERE `mincountOrRef`=-34155 AND `entry`=@LOOTID;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(@LOOTID, @ITEM + 38, 3, 1, 0, -34155, 1);