ALTER TABLE `autobroadcast` ADD `country` VARCHAR( 20 ) NOT NULL AFTER `weight` ;
ALTER TABLE `autobroadcast` ADD `exceptCountry` VARCHAR( 20 ) NOT NULL AFTER `country` ;