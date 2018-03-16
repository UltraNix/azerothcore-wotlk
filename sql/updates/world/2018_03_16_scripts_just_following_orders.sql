DELETE FROM `smart_scripts` WHERE `entryorguid` = 28325 AND `id` = 4;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 28217 AND `id` IN (16, 17);
INSERT INTO `smart_scripts` VALUES
(28325, 0, 4, 0, 1, 0, 100, 0, 60000, 60000, 60000, 60000, 45, 4, 4, 0, 0, 0, 0, 9, 28217, 0, 20, 0, 0, 0, 0, 'Ravenous Mangal Crocolisk - OOC - Set Data 4 4'),
(28217, 0, 16, 61, 38, 0, 100, 0, 4, 4, 0, 0, 11, 51329, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - On Data Set 4 4 - Add Feign Death Aura'),
(28217, 0, 17, 0, 61, 0, 100, 0, 0, 0, 0, 0, 75, 58806, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Injured Rainspeaker Oracle - On Data Set 4 4 - Add Feign Death Aura');
UPDATE `smart_scripts` SET `action_type` = 75 WHERE `entryorguid` = 28217 AND `id` = 14;

DELETE FROM `conditions` WHERE `SourceGroup` = 9677 AND `ConditionValue1` = 51329 AND `SourceTypeOrReferenceId` = 15;
DELETE FROM `conditions` WHERE `SourceGroup` = 9677 AND `ConditionValue1` = 28325;
INSERT INTO `conditions` VALUES
(15, 9677, 0, 0, 0, 29, 0, 28325, 20, 0, 1, 0, 0, '', 'Injured Rainspeaker Oracle only display gossip if Crocolisk not summoned');
