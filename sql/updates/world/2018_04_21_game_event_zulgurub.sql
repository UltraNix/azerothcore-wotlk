UPDATE `game_event` SET `start_time` = '2018-04-16 07:00:00' WHERE `eventEntry` = 30;
UPDATE `game_event` SET `start_time` = '2018-04-30 07:00:00' WHERE `eventEntry` = 29;
UPDATE `game_event` SET `start_time` = '2018-05-14 07:00:00' WHERE `eventEntry` = 28;
UPDATE `game_event` SET `start_time` = '2018-05-28 07:00:00' WHERE `eventEntry` = 27;
UPDATE `game_event` SET `length` = 20160 WHERE `eventEntry` IN (27,28,29,30);
