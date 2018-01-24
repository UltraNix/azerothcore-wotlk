DROP TABLE IF EXISTS `account_mute_history`;

CREATE TABLE `account_mute_history` (
  `account_id` int(11) NOT NULL DEFAULT '0' COMMENT 'Account id',
  `characterName` varchar(30) NOT NULL,
  `muteReason` varchar(120) NOT NULL,
  `muteBy` varchar(30) NOT NULL,
  `minutes` int(11) NOT NULL,
  `mute_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`account_id`,`mute_date`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 CHECKSUM=1 DELAY_KEY_WRITE=1 ROW_FORMAT=DYNAMIC COMMENT='Account login history';
