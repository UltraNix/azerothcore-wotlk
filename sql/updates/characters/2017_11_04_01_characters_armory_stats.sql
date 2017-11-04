DROP TABLE IF EXISTS `characters_armory_stats`;

CREATE TABLE `characters_armory_stats` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT 'Identifier',
  `guid` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'Global Unique Identifier',
  `guildId` int(10) unsigned NOT NULL DEFAULT '0',
  `creatureEntry` int(10) unsigned NOT NULL DEFAULT '0',
  `mapId` int(10) unsigned NOT NULL DEFAULT '0',
  `difficulity` int(10) unsigned NOT NULL DEFAULT '0',
  `groupCount` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `fightLength` varchar(30) NOT NULL DEFAULT '',
  `fightDate` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;