DROP TABLE IF EXISTS `hellforge_boss_stats`;
CREATE TABLE IF NOT EXISTS `hellforge_boss_stats` (
	`StatId` INT(10) UNSIGNED NOT NULL,
	`StatValue` INT(10) UNSIGNED NOT NULL,
	`StatVariance` FLOAT,
	`StatComment` VARCHAR(100),
	PRIMARY KEY (`StatId`)
)
COMMENT='Use positive values for stat entry'
COLLATE='utf8_general_ci'
ENGINE=InnoDB;
