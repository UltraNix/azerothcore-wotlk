ALTER TABLE `spell_proc_event`
ADD COLUMN `procPhase` INT(10) UNSIGNED DEFAULT '2' NOT NULL AFTER `procEx`;
