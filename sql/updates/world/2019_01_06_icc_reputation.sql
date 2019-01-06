DELETE FROM `creature_onkill_reputation` WHERE `creature_id` IN (37038, 10404, 37098, 37023, 37025, 37217, 37534, 37533);
INSERT INTO `creature_onkill_reputation` (`creature_id`, `RewOnKillRepFaction1`, `RewOnKillRepFaction2`, `MaxStanding1`, `IsTeamAward1`, `RewOnKillRepValue1`, `MaxStanding2`, `IsTeamAward2`, `RewOnKillRepValue2`, `TeamDependent`) VALUES
(10404, 1156, 0, 7, 0, 30, 0, 0, 0, 0),
(37023, 1156, 0, 7, 0, 15, 0, 0, 0, 0),
(37025, 1156, 0, 7, 0, 150, 0, 0, 0, 0),
(37038, 1156, 0, 7, 0, 15, 0, 0, 0, 0),
(37098, 1156, 0, 7, 0, 45, 0, 0, 0, 0),
(37217, 1156, 0, 7, 0, 150, 0, 0, 0, 0),
(37534, 1156, 0, 7, 0, 150, 0, 0, 0, 0),
(37533, 1156, 0, 7, 0, 150, 0, 0, 0, 0);
