ALTER TABLE `characters` CHANGE COLUMN `blizzlikeMode` `xpRate` INT UNSIGNED NOT NULL DEFAULT '5' AFTER `grantableLevels`;
UPDATE `characters` SET `xpRate` = 5;