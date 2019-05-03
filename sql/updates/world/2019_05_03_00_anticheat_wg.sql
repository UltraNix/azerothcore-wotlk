DELETE FROM `trinity_string` WHERE `entry` = 10508;
INSERT INTO `trinity_string` VALUES (10508,'Wintergrasp possible cheater! Attacking Fortress Door from %s. Nick: |cffff0000%s|r (guid: %u)',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
UPDATE `gameobject_template` SET `ScriptName` = 'go_wg_fortress_door' WHERE `entry` = 191810;