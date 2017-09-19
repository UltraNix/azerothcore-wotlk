-- Disabling class mounts for players with not big enough level

DELETE FROM `conditions` WHERE `conditions`.`SourceTypeOrReferenceId` = 17 AND `conditions`.`ConditionTypeOrReference` = 27 AND `conditions`.`SourceEntry` IN (13819, 34769, 5784, 23161, 34767, 23214);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`, `ConditionValue2`, `ErrorType`, `Comment`) VALUES
(17, 13819, 27, 20, 3, 46, "Alliance Warhorse - Level Requirement"),
(17, 34769, 27, 20, 3, 46, "Horde Warhorse - Level Requirement"),
(17, 5784, 27, 20, 3, 46, "Warlock Felstead - Level Requirement"),
(17, 23214, 27, 40, 3, 46, "Alliance Charger - Level Requirement"),
(17, 34767, 27, 40, 3, 46, "Horde Charger - Level Requirement"),
(17, 23161, 27, 40, 3, 46, "Warlock Dreadsteed - Level Requirement");