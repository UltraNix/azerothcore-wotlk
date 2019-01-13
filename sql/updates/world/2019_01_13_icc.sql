DELETE FROM `spell_script_names` WHERE `spell_id` = 71620;
INSERT INTO `spell_script_names` VALUES
(71620, "spell_putricide_tear_gas_cancel");

DELETE FROM `conditions` WHERE `SourceEntry` = 71620 AND `SourceTypeOrReferenceId` = 13;
