DELETE FROM `reserved_name` WHERE `reserved_name`.`name` = 'Default';
INSERT INTO `reserved_name` (`name`) VALUES ('Default');