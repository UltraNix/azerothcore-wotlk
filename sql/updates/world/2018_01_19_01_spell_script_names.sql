DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = -28169;
DELETE FROM `spell_script_names` WHERE `spell_id` = 28169;
INSERT INTO `spell_script_names` VALUES
(28169, "spell_grobbulus_mutating_injection");
