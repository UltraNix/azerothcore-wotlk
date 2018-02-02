SET @RETHILGORE = 3914;
SET @LEVER1 = 18900;
SET @LEVER2 = 18901;

UPDATE `gameobject_template` SET `flags` = 4 WHERE `entry` IN (@LEVER1, @LEVER2);
UPDATE `smart_scripts` SET `link` = 3 WHERE `entryorguid` = 3914 AND `id` = 2;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @RETHILGORE AND `id` IN (3,4);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@LEVER1, @LEVER2) AND `id` = 1;
INSERT INTO `smart_scripts` VALUES
(@RETHILGORE, 0, 3, 4, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 20, @LEVER1, 30, 0, 0, 0, 0, 0, 'Rethilgore - On Just Died - Set Data'),
(@RETHILGORE, 0, 4, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 20, @LEVER2, 30, 0, 0, 0, 0, 0, 'Rethilgore - On Just Died - Set Data'),
(@LEVER1, 1, 1, 0, 38, 0, 100, 0, 1, 1, 0, 0, 106, 4, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Lever - On Data Set - Remove Flag'),
(@LEVER2, 1, 1, 0, 38, 0, 100, 0, 1, 1, 0, 0, 106, 4, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Lever - On Data Set - Remove Flag');