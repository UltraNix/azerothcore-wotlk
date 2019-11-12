-- DB/Skinning: Correct number of borean leather dropped by some creatures
-- DB/NPC: Dying Soldier/Dying Berserker - should not follow players in combat
-- DB/NPC: Dying Soldier/Dying Berserker  - correct amount of hp
-- DB/Quest: The Will of the Naaru - add script for Rhydian to summon portal
UPDATE `skinning_loot_template` SET `maxcount` = 3 WHERE `entry` IN (70215,70203,70216);
UPDATE `creature_template_addon` SET `auras` = '65985' WHERE `entry` IN (31304, 31273);
UPDATE `creature` SET `curhealth` = 37 WHERE `id` IN (31304, 31273);
UPDATE `creature_template` SET `AIName` = "SmartAI", `ScriptName` = '' WHERE `entry` IN (31044, 30656);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (31044,30656, 3065600);
INSERT INTO `smart_scripts` VALUES
(31044, 0, 0, 0, 19, 0, 100, 0, 13081, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 10, 124114, 30656, 0, 0, 0, 0, 0, "Tirion on quest set data on Rhydian"),
(30656, 0, 0, 0, 38, 0, 100, 0, 1, 1, 0, 0, 80, 3065600, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Rhydian on data set - run script"),
(3065600, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 46, 15, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,  "Rhydian on script move forward"),
(3065600, 9, 1, 0, 0, 0, 100, 0, 3400, 3400, 0, 0, 11, 57676, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Rhydian on script cast portal"),
(3065600, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Rhydian on script say line 0"),
(3065600, 9, 3, 0, 0, 0, 100, 0, 10000, 10000, 0, 0, 69, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 6409.120117, 422.381989, 511.347992, 0.628319, "Rhydian on script return to home pos"),
(3065600, 9, 4, 0, 0, 0, 100, 0, 2600, 2600, 0, 0, 66, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0.628319, "Rhydian on script set orientation");
DELETE FROM `creature_text` WHERE `entry`=30656;
INSERT INTO `creature_text` VALUES
(30656, 0, 0, "Hail. I could not help but overhear your conversation. Please allow me to lend some assistance.", 12, 0, 100, 0, 0, 0, 0, "Rhydian");

