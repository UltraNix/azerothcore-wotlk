-- DB/Quest: Across Transborea - only one guardian can be summoned
UPDATE `quest_template` SET `SourceSpellId` = 0 WHERE `id` = 11930;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 26158;
INSERT INTO `smart_scripts` VALUES
(26158, 0, 0, 0, 19, 0, 100, 0, 11930, 0, 0, 0, 85, 46657, 32, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Mother Tauranook - On Quest Accept (Across Transborea) - Invoker Cast Taunka\'le Evacuee');
