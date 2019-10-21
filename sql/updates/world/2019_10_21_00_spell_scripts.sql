UPDATE `item_template` SET ScriptName = '' WHERE `entry` = 31742;
DELETE FROM `spell_script_names` WHERE `spell_id` = 39105;
INSERT INTO `spell_script_names` VALUES (39105, 'spell_nether_wraith_beacon');
