DELETE FROM `trinity_string` WHERE `trinity_string`.`entry` = 1025;

DELETE FROM `reserved_name` WHERE `reserved_name`.`name` = 'Default';
INSERT INTO `reserved_name` (`name`) VALUES ('Default');