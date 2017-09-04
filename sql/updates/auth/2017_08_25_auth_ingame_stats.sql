DROP TABLE IF EXISTS ingame_stats; 
CREATE TABLE ingame_stats ( 
  `connectedPlayers` int(11) unsigned NOT NULL DEFAULT '0', 
  `playersCount` int(11) unsigned NOT NULL DEFAULT '0', 
  `diff` smallint(3) unsigned NOT NULL DEFAULT '0',
  `avgDiff` smallint(3) unsigned NOT NULL DEFAULT '0',
  `currentTime` varchar(30) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;