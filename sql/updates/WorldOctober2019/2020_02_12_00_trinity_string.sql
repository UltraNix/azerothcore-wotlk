SET @TRINITY_STRING_ID:= 10513;

DELETE FROM `trinity_string` WHERE `entry` = @TRINITY_STRING_ID;
INSERT INTO `trinity_string` (`entry`, `content_default`) VALUES
(@TRINITY_STRING_ID, "Player (%s) has send multiple (%u) invites in a very short period of time!");
