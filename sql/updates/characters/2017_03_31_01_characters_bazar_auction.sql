DROP TABLE IF EXISTS `bazar_auction`;

CREATE TABLE `bazar_auction` (
  `auctionId` int(10) unsigned NOT NULL DEFAULT '0',
  `account_id` int(10) unsigned NOT NULL DEFAULT '0',
  `char_guid` int(10) unsigned NOT NULL DEFAULT '0',
  `mo_amount` int(10) unsigned NOT NULL DEFAULT '0',
  `dp_amount` int(10) unsigned NOT NULL DEFAULT '0',
  `auction_type` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `owner_name` varchar(30) NOT NULL DEFAULT '',
  `slave_race` int(10) unsigned NOT NULL DEFAULT '0',
  `slave_class` int(10) unsigned NOT NULL DEFAULT '0',
  `slave_gender` int(10) unsigned NOT NULL DEFAULT '0',
  `slave_level` int(10) unsigned NOT NULL DEFAULT '0',
  `slave_money` int(10) unsigned NOT NULL DEFAULT '0',
  `slave_arena` int(10) unsigned NOT NULL DEFAULT '0',
  `slave_honor` int(10) unsigned NOT NULL DEFAULT '0',
  `slave_riding` int(10) unsigned NOT NULL DEFAULT '0',
  `slave_mainspec` varchar(30) NOT NULL DEFAULT '',
  `slave_offspec` varchar(30) NOT NULL DEFAULT '',
  `slave_gearscore` int(10) unsigned NOT NULL DEFAULT '0',
  `slave_description` varchar(130) NOT NULL DEFAULT '',
  `create_time` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`auctionId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;