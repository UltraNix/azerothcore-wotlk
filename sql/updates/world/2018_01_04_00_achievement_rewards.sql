SET @ALCHEMIST:= 1415;

DELETE FROM `achievement_reward` WHERE `entry` = @ALCHEMIST;
INSERT INTO `achievement_reward` VALUES
(@ALCHEMIST, 96, 96, 0, 0, "", "", 0);

SET @BLACKSMITH:= 1414;

DELETE FROM `achievement_reward` WHERE `entry` = @BLACKSMITH;
INSERT INTO `achievement_reward` VALUES
(@BLACKSMITH, 97, 97, 0, 0, "", "", 0);

SET @COOK:= 1416;

DELETE FROM `achievement_reward` WHERE `entry` = @COOK;
INSERT INTO `achievement_reward` VALUES
(@COOK, 98, 98, 0, 0, "", "", 0);

SET @ENCHANT:= 1417;

DELETE FROM `achievement_reward` WHERE `entry` = @ENCHANT;
INSERT INTO `achievement_reward` VALUES
(@ENCHANT, 99, 99, 0, 0, "", "", 0);

SET @ENGI:= 1418;

DELETE FROM `achievement_reward` WHERE `entry` = @ENGI;
INSERT INTO `achievement_reward` VALUES
(@ENGI, 100, 100, 0, 0, "", "", 0);

SET @FIRSTAID:= 1419;

DELETE FROM `achievement_reward` WHERE `entry` = @FIRSTAID;
INSERT INTO `achievement_reward` VALUES
(@FIRSTAID, 101, 101, 0, 0, "", "", 0);

SET @FISH:= 1420;

DELETE FROM `achievement_reward` WHERE `entry` = @FISH;
INSERT INTO `achievement_reward` VALUES
(@FISH, 102, 102, 0, 0, "", "", 0);

SET @HERB:= 1421;

DELETE FROM `achievement_reward` WHERE `entry` = @HERB;
INSERT INTO `achievement_reward` VALUES
(@HERB, 103, 103, 0, 0, "", "", 0);

SET @SCRIBE:= 1422;

DELETE FROM `achievement_reward` WHERE `entry` = @SCRIBE;
INSERT INTO `achievement_reward` VALUES
(@SCRIBE, 104, 104, 0, 0, "", "", 0);

SET @JEWEL:= 1423;

DELETE FROM `achievement_reward` WHERE `entry` = @JEWEL;
INSERT INTO `achievement_reward` VALUES
(@JEWEL, 105, 105, 0, 0, "", "", 0);

SET @LEATHER:= 1424;

DELETE FROM `achievement_reward` WHERE `entry` = @LEATHER;
INSERT INTO `achievement_reward` VALUES
(@LEATHER, 106, 106, 0, 0, "", "", 0);

SET @MINER:= 1425;

DELETE FROM `achievement_reward` WHERE `entry` = @MINER;
INSERT INTO `achievement_reward` VALUES
(@MINER, 107, 107, 0, 0, "", "", 0);

SET @SKIN:= 1426;

DELETE FROM `achievement_reward` WHERE `entry` = @SKIN;
INSERT INTO `achievement_reward` VALUES
(@SKIN, 108, 108, 0, 0, "", "", 0);

SET @TAILOR:= 1427;

DELETE FROM `achievement_reward` WHERE `entry` = @TAILOR;
INSERT INTO `achievement_reward` VALUES
(@TAILOR, 109, 109, 0, 0, "", "", 0);

-- End of profession realm firsts

-- race realm firsts
SET @GNOME:= 1404;

-- of gnomeregan, taki sam jest z AT
DELETE FROM `achievement_reward` WHERE `entry` = @GNOME;
INSERT INTO `achievement_reward` VALUES
(@GNOME, 113, 0, 0, 0, "", "", 0);

SET @DRAN:= 1406;

DELETE FROM `achievement_reward` WHERE `entry` = @DRAN;
INSERT INTO `achievement_reward` VALUES
(@DRAN, 111, 0, 0, 0, "", "", 0);

SET @DWARF:= 1407;

DELETE FROM `achievement_reward` WHERE `entry` = @DWARF;
INSERT INTO `achievement_reward` VALUES
(@DWARF, 112, 0, 0, 0, "", "", 0);

SET @HUJMAN:= 1408;

DELETE FROM `achievement_reward` WHERE `entry` = @HUJMAN;
INSERT INTO `achievement_reward` VALUES
(@HUJMAN, 114, 0, 0, 0, "", "", 0);

SET @NIGHTELF:= 1409;

DELETE FROM `achievement_reward` WHERE `entry` = @NIGHTELF;
INSERT INTO `achievement_reward` VALUES
(@NIGHTELF, 115, 0, 0, 0, "", "", 0);

SET @ORC:= 1410;

DELETE FROM `achievement_reward` WHERE `entry` = @ORC;
INSERT INTO `achievement_reward` VALUES
(@ORC, 0, 116, 0, 0, "", "", 0);

SET @TAUREN:= 1411;

DELETE FROM `achievement_reward` WHERE `entry` = @TAUREN;
INSERT INTO `achievement_reward` VALUES
(@TAUREN, 0, 117, 0, 0, "", "", 0);

SET @TROLL:= 1412;

DELETE FROM `achievement_reward` WHERE `entry` = @TROLL;
INSERT INTO `achievement_reward` VALUES
(@TROLL, 0, 118, 0, 0, "", "", 0);

SET @FORSAKEN:= 1413;

DELETE FROM `achievement_reward` WHERE `entry` = @FORSAKEN;
INSERT INTO `achievement_reward` VALUES
(@FORSAKEN, 0, 119, 0, 0, "", "", 0);

SET @BLOODELF:= 1405;

DELETE FROM `achievement_reward` WHERE `entry` = @BLOODELF;
INSERT INTO `achievement_reward` VALUES
(@BLOODELF, 0, 110, 0, 0, "", "", 0);

SET @DRUID:= 466;
-- na forum napisane ze niby mial miec Arch druid, ale w dbc jest <name> of the emerald dream
DELETE FROM `achievement_reward` WHERE `entry` = @DRUID;
INSERT INTO `achievement_reward` VALUES
(@DRUID, 87, 87, 0, 0, "", "", 0);

SET @MAGE:= 460;

DELETE FROM `achievement_reward` WHERE `entry` = @MAGE;
INSERT INTO `achievement_reward` VALUES
(@MAGE, 93, 93, 0, 0, "", "", 0);

SET @ROGUE:= 458;

DELETE FROM `achievement_reward` WHERE `entry` = @ROGUE;
INSERT INTO `achievement_reward` VALUES
(@ROGUE, 95, 95, 0, 0, "", "", 0);

SET @PALADIN:= 465;

DELETE FROM `achievement_reward` WHERE `entry` = @PALADIN;
INSERT INTO `achievement_reward` VALUES
(@PALADIN, 156, 156, 0, 0, "", "", 0);

SET @PRIEST:= 464;

DELETE FROM `achievement_reward` WHERE `entry` = @PRIEST;
INSERT INTO `achievement_reward` VALUES
(@PRIEST, 89, 89, 0, 0, "", "", 0);

SET @HUNTER:= 462;

DELETE FROM `achievement_reward` WHERE `entry` = @HUNTER;
INSERT INTO `achievement_reward` VALUES
(@HUNTER, 91, 91, 0, 0, "", "", 0);

SET @WARRIOR:= 459;

DELETE FROM `achievement_reward` WHERE `entry` = @WARRIOR;
INSERT INTO `achievement_reward` VALUES
(@WARRIOR, 94, 94, 0, 0, "", "", 0);

SET @WARLOCK:= 463;

DELETE FROM `achievement_reward` WHERE `entry` = @WARLOCK;
INSERT INTO `achievement_reward` VALUES
(@WARLOCK, 90, 90, 0, 0, "", "", 0);

SET @DK:= 461;

DELETE FROM `achievement_reward` WHERE `entry` = @DK;
INSERT INTO `achievement_reward` VALUES
(@DK, 92, 92, 0, 0, "", "", 0);

SET @SHAMAN:= 467;

DELETE FROM `achievement_reward` WHERE `entry` = @SHAMAN;
INSERT INTO `achievement_reward` VALUES
(@SHAMAN, 86, 86, 0, 0, "", "", 0);

SET @LEVEL80:= 457;

DELETE FROM `achievement_reward` WHERE `entry` = @LEVEL80;
INSERT INTO `achievement_reward` VALUES
(@LEVEL80, 85, 85, 0, 0, "", "", 0);

SET @VANGUARD:= 1463;

DELETE FROM `achievement_reward` WHERE `entry` = @VANGUARD;
INSERT INTO `achievement_reward` VALUES
(@VANGUARD, 123, 123, 0, 0, "", "", 0);

