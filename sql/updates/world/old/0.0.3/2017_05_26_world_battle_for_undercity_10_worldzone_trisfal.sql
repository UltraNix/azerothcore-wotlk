DROP TABLE IF EXISTS `world_zone_scripts`;
CREATE TABLE `world_zone_scripts` (
`zone_entry` INT(11) NOT NULL DEFAULT '0',
`ScriptName` CHAR(64) NOT NULL DEFAULT '',
UNIQUE KEY `zone_entry` (`zone_entry`,`ScriptName`)
) ENGINE=INNODB DEFAULT CHARSET=utf8;

DELETE FROM `world_zone_scripts` WHERE `zone_entry`=85;
INSERT INTO `world_zone_scripts` VALUES 
(85,'worldzone_trisfal_glades');