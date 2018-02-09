SET @TELATHION = 17359;
SET @ELEMENTAL = 6748;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` IN (@TELATHION, @ELEMENTAL);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@TELATHION, @ELEMENTAL);
INSERT INTO `smart_scripts` VALUES
(@TELATHION, 0, 0, 0, 0, 0, 100, 0, 5000, 15000, 10000, 15000, 11, 15736, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Telathion - In Combat - Cast Arcane Missiles'),
(@TELATHION, 0, 1, 0, 0, 0, 100, 0, 20000, 30000, 30000, 35000, 11, 13339, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Telathion - In Combat - Cast Fire Blast'),
(@TELATHION, 0, 2, 0, 0, 0, 100, 0, 2000, 12000, 20000, 30000, 11, 11831, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Telathion - In Combat - Cast Frost Nova'),
(@TELATHION, 0, 3, 0, 0, 0, 100, 0, 10000, 25000, 50000, 60000, 11, 9672, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Telathion - In Combat - Cast Frostbolt'),
(@ELEMENTAL, 0, 0, 0, 54, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 19, @TELATHION, 50, 0, 0, 0, 0, 0, 'Water Spirit - On Just Summoned - attack Telathion');

UPDATE `gameobject_template` SET `data3` = 10000 WHERE `entry` = 181699;
UPDATE `creature_template` SET `faction` = 84 WHERE `entry` = @ELEMENTAL;