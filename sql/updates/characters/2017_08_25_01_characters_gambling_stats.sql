DROP TABLE IF EXISTS `character_gambling_stats`;
CREATE TABLE IF NOT EXISTS `character_gambling_stats` (
  `guid` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'Global Unique Identifier',
  `lost_money` int(10) unsigned NOT NULL DEFAULT '0',
  `win_money` int(10) unsigned NOT NULL DEFAULT '0',
  `duel_count` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`guid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;