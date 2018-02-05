DELETE FROM `spell_script_names` WHERE `spell_id` IN (52694, 53349);
INSERT INTO `spell_script_names` VALUES
(52694, "spell_acherus_recall_52694"),
(53349, "spell_arrow_assault_crusader");

UPDATE `gameobject_template` SET `data3` = 30000 WHERE `entry` = 187655;
