-- Dehydration
DELETE FROM `achievement_criteria_data` WHERE `criteria_id`=7320;
INSERT INTO `achievement_criteria_data` (`criteria_id`, `type`, `ScriptName`) VALUES
(7320, 11, "achievement_dehydration");
