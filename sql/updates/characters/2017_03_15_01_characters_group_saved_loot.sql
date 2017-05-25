ALTER TABLE `group_saved_loot` ADD `mapId` INT( 11 ) NOT NULL DEFAULT '0' AFTER `instanceId` ;
ALTER TABLE `group_saved_loot` ADD `difficultyId` INT( 11 ) NOT NULL DEFAULT '0' AFTER `mapId` ;