DROP TABLE IF EXISTS `lottery_gold_bets`;
CREATE TABLE IF NOT EXISTS `lottery_gold_bets` (
  `id` int(10) unsigned NOT NULL DEFAULT '1',
  `name` varchar(12) NOT NULL,
  `guid` int(10) unsigned NOT NULL DEFAULT '0',
  `bet` longtext NOT NULL,
  `time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `lottery_sunwell_coins_bets`;
CREATE TABLE IF NOT EXISTS `lottery_sunwell_coins_bets` (
  `id` int(10) unsigned NOT NULL DEFAULT '1',
  `name` varchar(12) NOT NULL,
  `guid` int(10) unsigned NOT NULL DEFAULT '0',
  `bet` longtext NOT NULL,
  `time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `lottery_gold`;
CREATE TABLE `lottery_gold` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `numbers` longtext NOT NULL,
  `jackpot` int(10) unsigned NOT NULL DEFAULT '0',
  `time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `lottery_sunwell_coins`;
CREATE TABLE `lottery_sunwell_coins` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `numbers` longtext NOT NULL,
  `jackpot` int(10) unsigned NOT NULL DEFAULT '0',
  `time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `lottery_winners`;
CREATE TABLE `lottery_winners` (
  `id` int(10) unsigned NOT NULL,
  `name` varchar(12) NOT NULL,
  `guid` int(10) unsigned NOT NULL DEFAULT '0',
  `bet` longtext NOT NULL,
  `betPoints` int(10) unsigned NOT NULL DEFAULT '0',
  `betType` int(10) unsigned NOT NULL DEFAULT '0',
  `time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8;