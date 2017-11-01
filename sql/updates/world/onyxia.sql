DELETE FROM `achievement_criteria_data` WHERE `criteria_id` IN (12566,12569)  AND `type` IN (11, 12, 18);
INSERT INTO `achievement_criteria_data` (`criteria_id`,`type`,`value1`,`value2`,`ScriptName`) VALUES
(12566,11,0,0,"achievement_onyxia_deep_breath"),
(12566,12,0,0,"achievement_onyxia_deep_breath"),
(12569,11,1,0,"achievement_onyxia_deep_breath"),
(12569,12,1,0,"achievement_onyxia_deep_breath");
DELETE FROM `achievement_criteria_data` WHERE `criteria_id` IN (12565,12568)  AND `type` IN (11, 12, 18);
INSERT INTO `achievement_criteria_data` (`criteria_id`,`type`,`value1`,`value2`,`ScriptName`) VALUES
(12565,11,0,0,"achievement_onyxia_many_whelps"),
(12565,12,0,0,"achievement_onyxia_many_whelps"),
(12568,11,1,0,"achievement_onyxia_many_whelps"),
(12568,12,1,0,"achievement_onyxia_many_whelps");
