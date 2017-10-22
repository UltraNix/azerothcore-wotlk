ALTER TABLE `bazar_auction` 
CHANGE `auction_type` `auction_type` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0', 
CHANGE `owner_name` `owner_name` VARCHAR(20) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL, 
CHANGE `slave_race` `slave_race` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0', 
CHANGE `slave_class` `slave_class` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0', 
CHANGE `slave_gender` `slave_gender` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0', 
CHANGE `slave_level` `slave_level` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0', 
CHANGE `slave_avgitemlevel` `slave_avgitemlevel` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0', 
CHANGE `slave_team` `slave_team` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0', 
CHANGE `create_time` `create_time` INT(10) UNSIGNED NOT NULL DEFAULT '0';