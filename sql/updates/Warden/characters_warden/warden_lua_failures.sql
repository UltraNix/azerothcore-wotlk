DROP TABLE IF EXISTS `warden_lua_failures`;
CREATE TABLE `warden_lua_failures`
(
	FailureId MEDIUMINT unsigned auto_increment primary key,
	AccountId MEDIUMINT unsigned NOT NULL DEFAULT 0,
	CharacterGuid BIGINT unsigned NOT NULL DEFAULT 0,
	CharacterName varchar(20) NOT NULL DEFAULT "Unknown player name",
	FailedCheck varchar(60) NOT NULL DEFAULT "UNKNOWN",
	FailureDate BIGINT unsigned NOT NULL DEFAULT 0 COMMENT "Unix timestamp"
) ENGINE=InnoDB;
