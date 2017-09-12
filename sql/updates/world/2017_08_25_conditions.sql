DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 19 AND `ConditionTypeOrReference` = 28 AND `SourceEntry` = 13593;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 19 AND `ConditionTypeOrReference` = 28 AND `SourceEntry` = 13703;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 19 AND `ConditionTypeOrReference` = 28 AND `SourceEntry` = 13704;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 19 AND `ConditionTypeOrReference` = 28 AND `SourceEntry` = 13705;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 19 AND `ConditionTypeOrReference` = 28 AND `SourceEntry` = 13706;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 19 AND `ConditionTypeOrReference` = 28 AND `SourceEntry` = 13707;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 19 AND `ConditionTypeOrReference` = 28 AND `SourceEntry` = 13708;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 19 AND `ConditionTypeOrReference` = 28 AND `SourceEntry` = 13709;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 19 AND `ConditionTypeOrReference` = 28 AND `SourceEntry` = 13710;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 19 AND `ConditionTypeOrReference` = 28 AND `SourceEntry` = 13711;

INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`, `NegativeCondition`, `Comment`) VALUES 
(19, 13593, 28, 13703, 1, "Valiant of Stormwind - cant take if on quest Valiant of Ironforge"),
(19, 13593, 28, 13704, 1, "Valiant of Stormwind - cant take if on quest Valiant of Gnomeregan"),
(19, 13593, 28, 13705, 1, "Valiant of Stormwind - cant take if on quest Valiant of The Exodar"),
(19, 13593, 28, 13706, 1, "Valiant of Stormwind - cant take if on quest Valiant of Darnassus"),

(19, 13703, 28, 13593, 1, "Valiant of Ironforge - cant take if on quest Valiant of Stormwind"),
(19, 13703, 28, 13704, 1, "Valiant of Ironforge - cant take if on quest Valiant of Gnomeregan"),
(19, 13703, 28, 13705, 1, "Valiant of Ironforge - cant take if on quest Valiant of The Exodar"),
(19, 13703, 28, 13706, 1, "Valiant of Ironforge - cant take if on quest Valiant of Darnassus"),

(19, 13704, 28, 13593, 1, "Valiant of Gnomeregan - cant take if on quest Valiant of Stormwind"),
(19, 13704, 28, 13703, 1, "Valiant of Gnomeregan - cant take if on quest Valiant of Ironforge"),
(19, 13704, 28, 13705, 1, "Valiant of Gnomeregan - cant take if on quest Valiant of The Exodar"),
(19, 13704, 28, 13706, 1, "Valiant of Gnomeregan - cant take if on quest Valiant of Darnassus"),

(19, 13705, 28, 13593, 1, "Valiant of The Exodar - cant take if on quest Valiant of Stormwind"),
(19, 13705, 28, 13703, 1, "Valiant of The Exodar - cant take if on quest Valiant of Ironforge"),
(19, 13705, 28, 13704, 1, "Valiant of The Exodar - cant take if on quest Valiant of Gnomeregan"),
(19, 13705, 28, 13706, 1, "Valiant of The Exodar - cant take if on quest Valiant of Darnassus"),

(19, 13706, 28, 13593, 1, "Valiant of Darnassus - cant take if on quest Valiant of Stormwind"),
(19, 13706, 28, 13703, 1, "Valiant of Darnassus - cant take if on quest Valiant of Ironforge"),
(19, 13706, 28, 13704, 1, "Valiant of Darnassus - cant take if on quest Valiant of Gnomeregan"),
(19, 13706, 28, 13705, 1, "Valiant of Darnassus - cant take if on quest Valiant of The Exodar"),

(19, 13707, 28, 13708, 1, "Valiant of Orgrimmar - cant take if on quest Valiant of Sel'jin"),
(19, 13707, 28, 13709, 1, "Valiant of Orgrimmar - cant take if on quest Valiant of Thunder Bluff"),
(19, 13707, 28, 13710, 1, "Valiant of Orgrimmar - cant take if on quest Valiant of Undercity"),
(19, 13707, 28, 13711, 1, "Valiant of Orgrimmar - cant take if on quest Valiant of Silvermoon"),

(19, 13708, 28, 13707, 1, "Valiant of Sel'jin - cant take if on quest Valiant of Orgrimmar"),
(19, 13708, 28, 13709, 1, "Valiant of Sel'jin - cant take if on quest Valiant of Thunder Bluff"),
(19, 13708, 28, 13710, 1, "Valiant of Sel'jin - cant take if on quest Valiant of Undercity"),
(19, 13708, 28, 13711, 1, "Valiant of Sel'jin - cant take if on quest Valiant of Silvermoon"),

(19, 13709, 28, 13707, 1, "Valiant of Thunder Bluff - cant take if on quest Valiant of Orgrimmar"),
(19, 13709, 28, 13708, 1, "Valiant of Thunder Bluff - cant take if on quest Valiant of Sel'jin"),
(19, 13709, 28, 13710, 1, "Valiant of Thunder Bluff - cant take if on quest Valiant of Undercity"),
(19, 13709, 28, 13711, 1, "Valiant of Thunder Bluff - cant take if on quest Valiant of Silvermoon"),

(19, 13710, 28, 13707, 1, "Valiant of Undercity - cant take if on quest Valiant of Orgrimmar"),
(19, 13710, 28, 13708, 1, "Valiant of Undercity - cant take if on quest Valiant of Sel'jin"),
(19, 13710, 28, 13709, 1, "Valiant of Undercity - cant take if on quest Valiant of Thunder Bluff"),
(19, 13710, 28, 13711, 1, "Valiant of Undercity - cant take if on quest Valiant of Silvermoon"),

(19, 13711, 28, 13707, 1, "Valiant of Silvermoon - cant take if on quest Valiant of Orgrimmar"),
(19, 13711, 28, 13708, 1, "Valiant of Silvermoon - cant take if on quest Valiant of Sel'jin"),
(19, 13711, 28, 13709, 1, "Valiant of Silvermoon - cant take if on quest Valiant of Thunder Bluff"),
(19, 13711, 28, 13710, 1, "Valiant of Silvermoon - cant take if on quest Valiant of Undercity");