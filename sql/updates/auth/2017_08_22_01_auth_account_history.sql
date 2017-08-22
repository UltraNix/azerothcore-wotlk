ALTER TABLE `account` ADD COLUMN `last_local_ip` varchar(30) NOT NULL DEFAULT '0.0.0.0' AFTER `os`;

DROP TABLE IF EXISTS `account_history`;
CREATE TABLE `account_history` (
  `account_id` int(11) NOT NULL DEFAULT '0' COMMENT 'Account id',
  `hostname` varchar(120) NOT NULL,
  `ip` varchar(30) NOT NULL,
  `local_ip` varchar(30) NOT NULL,
  `login_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`account_id`,`login_date`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 CHECKSUM=1 DELAY_KEY_WRITE=1 ROW_FORMAT=DYNAMIC COMMENT='Account login history';
