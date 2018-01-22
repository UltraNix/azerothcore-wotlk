UPDATE `creature_template_addon` SET `auras` = "57740" WHERE `entry` IN (30680, 30999);


UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = 30680;

DELETE FROM `smart_scripts` WHERE `entryorguid` = 30680 AND `id` = 2;
INSERT INTO `smart_scripts` VALUES
(30680, 0, 2, 0, 0, 0, 100, 0, 10000, 10000, 0, 0, 11, 57742, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Onyx blood general - In Combat - Cast avenging wrath');

DELETE FROM `spell_script_names` WHERE `spell_id` = 57742;
INSERT INTO `spell_script_names` VALUES
(57742, "spell_onyx_brood_avenging_fury");
