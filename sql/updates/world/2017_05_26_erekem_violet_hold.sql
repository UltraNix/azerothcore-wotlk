DELETE FROM `spelldifficulty_dbc` WHERE `id` IN (54481, 54479);
INSERT INTO `spelldifficulty_dbc`(`id`,`spellid0`,`spellid1`) VALUES
(54481, 54481, 59473),
(54479, 54479, 59471);
UPDATE `creature_template` SET `speed_walk`=4.0/2.5, `speed_run`=10.0/7.0, `unit_flags`=33600 WHERE `entry` = 29315; 
UPDATE `creature_template` SET `speed_walk`=4.0/2.5, `speed_run`=10.0/7.0, `unit_flags`=33600 WHERE `entry` = 29395; 
