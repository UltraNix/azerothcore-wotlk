DROP TABLE IF EXISTS `latency_record`;

CREATE TABLE `latency_record` (
  `latencyId` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `guid` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'Global Unique Identifier',
  `latency` int(10) unsigned NOT NULL COMMENT 'Player Latency',
  `sunwellVPN` tinyint(3) unsigned NOT NULL COMMENT 'Sunwell VPN',
  `date` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`latencyId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Latency Record System';