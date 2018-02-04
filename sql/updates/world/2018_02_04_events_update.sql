ALTER TABLE holiday_dates
ADD `duration` INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Override duration of event from dbc if value is greater than 0. Value in hours';

CREATE FUNCTION packDate (yy TINYINT UNSIGNED, mm TINYINT UNSIGNED, dd TINYINT UNSIGNED, hh TINYINT UNSIGNED)
RETURNS INT UNSIGNED DETERMINISTIC
RETURN (yy << 24) | ((mm - 1) << 20) | ((dd - 1) << 14) | ((hh) << 6);

-- Love in the air 
UPDATE `game_event` SET `start_time`='2018-02-02 10:00:00' WHERE  `eventEntry`=8;
SET @ID = 423;
SET @DURATION = 336;
DELETE FROM holiday_dates WHERE id = @ID;
INSERT INTO `holiday_dates` VALUES
(@ID, 0, packDate(18, 02, 02, 10), @DURATION),
(@ID, 1, packDate(19, 02, 02, 10), @DURATION),
(@ID, 2, packDate(20, 02, 02, 10), @DURATION),
(@ID, 3, packDate(21, 02, 02, 10), @DURATION),
(@ID, 4, packDate(22, 02, 02, 10), @DURATION),
(@ID, 5, packDate(23, 02, 02, 10), @DURATION),
(@ID, 6, packDate(24, 02, 02, 10), @DURATION);

-- Lunar festival
UPDATE `game_event` SET `holidayStage`='0', `length`='20160', `start_time`='2018-02-17 10:00:00' WHERE  `eventEntry`=7;
SET @ID = 327;
SET @DURATION = 336;
DELETE FROM holiday_dates WHERE id = @ID;
INSERT INTO `holiday_dates` VALUES
(@ID, 0, packDate(18, 02, 17, 10), @DURATION),
(@ID, 1, packDate(19, 02, 17, 10), @DURATION),
(@ID, 2, packDate(20, 02, 17, 10), @DURATION),
(@ID, 3, packDate(21, 02, 17, 10), @DURATION),
(@ID, 4, packDate(22, 02, 17, 10), @DURATION),
(@ID, 5, packDate(23, 02, 17, 10), @DURATION),
(@ID, 6, packDate(24, 02, 17, 10), @DURATION);

-- Noblegarden
UPDATE `game_event` SET `start_time`='2018-04-02 10:00:00', `holidayStage`='0', `length`='10080' WHERE  `eventEntry`=9;
SET @ID = 181;
SET @DURATION = 168;
DELETE FROM holiday_dates WHERE id = @ID;
INSERT INTO `holiday_dates` VALUES
(@ID, 0, packDate(18, 04, 02, 10), @DURATION),
(@ID, 1, packDate(19, 04, 02, 10), @DURATION),
(@ID, 2, packDate(20, 04, 02, 10), @DURATION),
(@ID, 3, packDate(21, 04, 02, 10), @DURATION),
(@ID, 4, packDate(22, 04, 02, 10), @DURATION),
(@ID, 5, packDate(23, 04, 02, 10), @DURATION),
(@ID, 6, packDate(24, 04, 02, 10), @DURATION);

-- Children's Week
UPDATE `game_event` SET `start_time`='2018-04-30 10:00:00', `length`='10080', `holidayStage`='0' WHERE  `eventEntry`=10;
SET @ID = 201;
SET @DURATION = 168;
DELETE FROM holiday_dates WHERE id = @ID;
INSERT INTO `holiday_dates` VALUES
(@ID, 0, packDate(18, 04, 30, 10), @DURATION),
(@ID, 1, packDate(19, 04, 30, 10), @DURATION),
(@ID, 2, packDate(20, 04, 30, 10), @DURATION),
(@ID, 3, packDate(21, 04, 30, 10), @DURATION),
(@ID, 4, packDate(22, 04, 30, 10), @DURATION),
(@ID, 5, packDate(23, 04, 30, 10), @DURATION),
(@ID, 6, packDate(24, 04, 30, 10), @DURATION);

DROP FUNCTION packDate;