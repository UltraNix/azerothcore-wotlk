DELETE FROM `game_tele` WHERE `id` = 1601;
INSERT INTO `game_tele` (`id`, `position_x`, `position_y`, `position_z`, `orientation`, `map`, `name`) VALUES
(1601, 77, -1, 20, 0.0487625, 44, 'OldScarletMonastery');

DELETE FROM `instance_template` WHERE `map` = 44;
INSERT INTO `instance_template` (`map`, `parent`, `script`, `allowMount`) VALUES
(44, 0, 'instance_old_scarlet_monastery', 0);

DELETE FROM `game_event` WHERE `eventEntry` = 88;
INSERT INTO `game_event` (`eventEntry`, `start_time`, `end_time`, `occurence`, `length`, `holiday`, `description`, `world_event`) VALUES
(88, '2017-06-13 00:00:00', '2017-07-13 00:00:00', 5184000, 2592000, 0, 'Old Scarlet Monastery', 0);
