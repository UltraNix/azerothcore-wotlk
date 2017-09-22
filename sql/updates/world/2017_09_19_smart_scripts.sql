SET @ENTRY := 17233;

DELETE FROM `smart_scripts` WHERE (`smart_scripts`.`entryorguid` IN (17253, @ENTRY) AND `smart_scripts`.`source_type` = 0) OR (`smart_scripts`.`entryorguid` IN (1723300, 1723301) AND `smart_scripts`.`source_type` = 9);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,54,0,100,0,0,0,0,0,1,4,5000,0,0,0,0,1,0,0,0,0,0,0,0,"Ghost of Uther Lightbringer - On Just Summoned (Quest - Tomb of the Lightbringer) - Say Line 4"),
(@ENTRY,0,1,0,52,0,100,0,4,17233,0,0,1,5,5000,0,0,0,0,1,0,0,0,0,0,0,0,"Ghost of Uther Lightbringer - On Text Over 4 - Say Line 5"),
(@ENTRY,0,2,0,52,0,100,0,5,17233,0,0,41,5000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ghost of Uther Lightbringer - On Text Over 5 - Despawn in 5s"),
(@ENTRY,0,3,0,54,0,100,0,0,0,0,0,1,0,8000,0,0,0,0,1,0,0,0,0,0,0,0,"Ghost of Uther Lightbringer - On Just Summoned (Quest - Defiling Uther's Tomb) - Say Line 0"),
(@ENTRY,0,4,0,52,0,100,0,0,17233,0,0,1,1,8000,0,0,0,0,1,0,0,0,0,0,0,0,"Ghost of Uther Lightbringer - On Text Over 0 - Say Line 1"),
(@ENTRY,0,5,0,52,0,100,0,1,17233,0,0,1,2,8000,0,0,0,0,1,0,0,0,0,0,0,0,"Ghost of Uther Lightbringer - On Text Over 1 - Say Line 2"),
(@ENTRY,0,6,0,52,0,100,0,2,17233,0,0,1,3,8000,0,0,0,0,1,0,0,0,0,0,0,0,"Ghost of Uther Lightbringer - On Text Over 2  - Say Line 3"),
(@ENTRY,0,7,0,52,0,100,0,5,17233,0,0,41,5000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ghost of Uther Lightbringer - On Text Over 3 - Despawn in 5s");

DELETE FROM `conditions` WHERE `conditions`.`SourceTypeOrReferenceId` = 22 AND `conditions`.`SourceEntry` = 17233;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `ConditionValue1`, `Comment`) VALUES
(22, 1, 17233, 469, 'Ghost of Uther Lightbringer - says on Alliance character'),
(22, 1, 17233, 67, 'Ghost of Uther Lightbringer - says on Horde character');