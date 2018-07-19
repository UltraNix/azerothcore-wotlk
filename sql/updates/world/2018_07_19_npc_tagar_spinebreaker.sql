SET @NPC = 19443;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @NPC;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @NPC;
INSERT INTO `smart_scripts` VALUES
(@NPC, 0, 0, 0, 0, 0, 100, 0, 20000, 25000, 15000, 20000, 11, 34108, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Tagar Spinebreaker - In Combat - Cast Spine Break'),
(@NPC, 0, 1, 0, 0, 0, 100, 0, 10000, 15000, 10000, 15000, 11, 34109, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Tagar Spinebreaker - In Combat - Cast Whirlwind Knockback');
