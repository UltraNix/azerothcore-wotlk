DELETE FROM `spell_linked_spell` WHERE `spell_linked_spell`.`spell_trigger` = 56001;
DELETE FROM `spell_linked_spell` WHERE `spell_linked_spell`.`spell_trigger` = 56002;
DELETE FROM `spell_linked_spell` WHERE `spell_linked_spell`.`spell_trigger` = 56003;

INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
(56001, 59676, 0, 'Ebonweave - Residue of Darkness');

INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
(56002, 59674, 0, 'Moonshroud - Moonshroud Residue');

INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
(56003, 59675, 0, 'Spellweave - Nexus Residue');

