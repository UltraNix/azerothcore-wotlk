ALTER TABLE `creature_template` CHANGE COLUMN `modelid1` `modelid1` INT(10) UNSIGNED NOT NULL DEFAULT '0';
ALTER TABLE `creature_template` CHANGE COLUMN `modelid2` `modelid2` INT(10) UNSIGNED NOT NULL DEFAULT '0';
ALTER TABLE `creature_template` CHANGE COLUMN `modelid3` `modelid3` INT(10) UNSIGNED NOT NULL DEFAULT '0';
ALTER TABLE `creature_template` CHANGE COLUMN `modelid4` `modelid4` INT(10) UNSIGNED NOT NULL DEFAULT '0';

ALTER TABLE `creature_template_outfits` DROP PRIMARY KEY;
ALTER TABLE `creature_template_outfits` ADD PRIMARY KEY (`entry`);

ALTER TABLE `creature` CHANGE COLUMN `modelid` `modelid` INT(10) UNSIGNED NOT NULL DEFAULT '0';
ALTER TABLE `game_event_model_equip` CHANGE COLUMN `modelid` `modelid` INT(10) UNSIGNED NOT NULL DEFAULT '0';
ALTER TABLE `creature_model_info` CHANGE COLUMN `modelid` `modelid` INT(10) UNSIGNED NOT NULL DEFAULT '0';
