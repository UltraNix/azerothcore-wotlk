DELETE FROM `command` WHERE `command`.`name` = 'instance unbindme';
INSERT INTO `command` (`name` , `security` , `help`) VALUES 
('instance unbindme', '1', 'Syntax: .instance unbind <mapid|all> [difficulty] Clear all/some binds');