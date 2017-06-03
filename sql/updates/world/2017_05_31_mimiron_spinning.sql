DELETE FROM `conditions` WHERE `sourceEntry` IN (63414,63274,64042,63297);
INSERT INTO `conditions` VALUES 
(13, 1, 63414, 0, 0, 31, 0, 3, 33576, 0, 0, 0, 0, '', 'Spinning Up EFFECT_0 can only hit Mimiron DB Targe'),
(13, 1, 63274, 0, 0, 31, 0, 3, 33576, 0, 0, 0, 0, '', 'P3Wx2 Laser Barrage EFFECT_0 can only hit Mimiron DB Target'),
(13, 2, 64042, 0, 0, 31, 0, 3, 33576, 0, 0, 0, 0, '', 'P3Wx2 Laser Barrage EFFECT_0 can only hit Mimiron DB Target'),
(13, 2, 63297, 0, 0, 31, 0, 3, 33576, 0, 0, 0, 0, '', 'P3Wx2 Laser Barrage EFFECT_0 can only hit Mimiron DB Target');

UPDATE `creature_template` SET `InhabitType` = 4, `flags_extra` = 130, `AiName`="", `ScriptName` = "npc_db_target_mimiron" WHERE `entry` = 33576;

SET @GUID := 137631;
DELETE FROM `creature` WHERE `id`=33576;
INSERT INTO `creature` VALUES
(@GUID,33576,603,3,1,16925,0,2785.42,2673.12,373.361,2.9363,180,0,0,4120,0,0,0,0,0);

DELETE FROM `spell_script_names` WHERE `spell_id`IN (63414, 63274);
INSERT INTO `spell_script_names` VALUES
(63414, "spell_spinning_up_mimiron"),
(63274, "spell_lasser_barrage_rotating");