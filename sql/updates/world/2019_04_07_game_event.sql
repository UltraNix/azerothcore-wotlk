-- DB/Event: Kalu'ak Fishing Derby - correct start hour (should start at 14:00)
UPDATE `game_event` SET `start_time` = "2019-04-13 14:00:00" WHERE `eventEntry` IN (63,64);