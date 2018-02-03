UPDATE `game_event` SET `holidayStage`='0' WHERE  `eventEntry` = 8;


CREATE FUNCTION packDate (yy TINYINT UNSIGNED, mm TINYINT UNSIGNED, dd TINYINT UNSIGNED, hh TINYINT UNSIGNED)
RETURNS INT UNSIGNED DETERMINISTIC
RETURN (yy << 24) | ((mm - 1) << 20) | ((dd - 1) << 14) | ((hh) << 6);

DELETE FROM holiday_dates WHERE id = 423;
INSERT INTO `holiday_dates` VALUES
(423, 0, packDate(18, 02, 02, 00)),
(423, 1, packDate(19, 02, 02, 00)),
(423, 2, packDate(20, 02, 02, 00)),
(423, 3, packDate(21, 02, 02, 00)),
(423, 4, packDate(22, 02, 02, 00));

DROP FUNCTION packDate;