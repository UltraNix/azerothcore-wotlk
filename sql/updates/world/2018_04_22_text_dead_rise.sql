DELETE FROM `creature_text` WHERE `entry` IN (24874,24875,24876,24877) AND `groupid` = 1;
INSERT INTO `creature_text` VALUES
(24874, 1, 0, 'From sundered ground the sacrament was stolen. The Shield of Aesirites is lost. Unrest will be eternal.', 12, 0, 100, 0, 0, 0, 0, 'Fengir the Disgraced'),
(24876, 1, 0, 'The Staff of Storm\'s Fury pilfered. A curse upon this land! The storms will never cease!', 12, 0, 100, 0, 0, 0, 0, 'Fengir the Disgraced'),
(24877, 1, 0, 'The Frozen Heart of Isuldof will consume this land until it is returned. Woe unto those that hold the heart as the curse of frozen blood besets them...', 12, 0, 100, 0, 0, 0, 0, 'Fengir the Disgraced'),
(24875, 1, 0, 'The anguish of ten-thousand years awaits any foolish enough to don the Ancient Armor of the Kvaldir. Beware the mist and fog, mortals; for with them comes your end.', 12, 0, 100, 0, 0, 0, 0, 'Fengir the Disgraced');

UPDATE `gameobject_template` SET `ScriptName` = 'go_dead_rise_clue' WHERE `entry` IN (187022, 187023,187026,187027);
UPDATE `gameobject` SET `position_z` = 297.1 WHERE `guid` = 59521;
