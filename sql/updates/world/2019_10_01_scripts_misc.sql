-- [Northrend, Quest, NPC] Rescuing Evanor
UPDATE `creature` SET `spawntimesecs` = 20 WHERE `guid` IN (107382,107383,107384,107385);
-- Beryl Mage Hunters deliberately use Frost Cut even when not in Melee Range to attack
DELETE FROM `smart_scripts` WHERE `entryorguid` = 25585;
INSERT INTO `smart_scripts` VALUES
(25585, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 11, 50654, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Beryl Mage Hunter - On Aggro - Cast \'Frost Cut\' (No Repeat)');
-- NPC Enslaved Archaeologist
UPDATE `creature_template` SET `unit_flags` = 0 WHERE `entry` = 8402;
-- npc/mob Death Knight Initiate/adept
UPDATE `creature_template` SET `AIName` = "" WHERE `entry` IN (31042, 30957, 30958);
-- Contagion of Rot can be stacked 
UPDATE `smart_scripts` SET `action_param2` = 32 WHERE `action_param1` IN (56708,56707, 7103,7102);
