DROP TABLE IF EXISTS `characters_ninja`;
CREATE TABLE `characters_ninja` (
  `guid` int(11) unsigned NOT NULL default '0' COMMENT 'Global Unique Identifier',
  `name` varchar(30),
  `postId` int(11),
  PRIMARY KEY  (`guid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Player Ninja System';