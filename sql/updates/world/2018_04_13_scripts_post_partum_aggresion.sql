SET @DORIAN = 28376;
SET @HEMET = 28451;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @HEMET AND `id` = 2;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @DORIAN*100 AND `id` = 2;
INSERT INTO `smart_scripts` VALUES
(@HEMET, 0, 2, 0, 38, 0, 100, 1, 1, 1, 0, 0, 80, @HEMET*100, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Hemet - On Data Set - Start Script'),
(@DORIAN*100, 9, 2, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 28451, 20, 0, 0, 0, 0, 0, 'Dorian - ActionList - Set Data');
