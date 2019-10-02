DELETE FROM `smart_scripts` WHERE `entryorguid` = 4781 AND `source_type` = 0;
INSERT INTO `smart_scripts` VALUES 
(4781,0,0,1,54,0,100,0,0,0,0,0,1,0,0,0,0,0,0,23,0,0,0,0,0,0,0,'Snufflenose Gopher - On Just Summoned - Say Line 0'),
(4781,0,1,8,61,0,100,0,0,0,0,0,29,1,0,0,0,0,0,23,0,0,0,0,0,0,0,'Snufflenose Gopher - On Just Summoned - Follow Summoner'),
(4781,0,2,3,38,0,100,0,1,1,10000,10000,29,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Snufflenose Gopher - On Data Set - Stop Following Invoker'),
(4781,0,3,4,61,0,100,0,0,0,0,0,69,0,0,0,0,0,0,20,20920,0,0,0,0,0,0,'Snufflenose Gopher - On Data Set - Move to Blueleaf Tuber'),
(4781,0,4,5,61,0,100,0,0,0,0,0,80,478100,2,0,0,0,0,1,0,0,0,0,0,0,0,'Snufflenose Gopher - On Data Set - Run Script'),
(4781,0,5,6,61,0,100,0,0,0,0,0,1,1,0,0,0,0,0,23,0,0,0,0,0,0,0,'Snufflenose Gopher - On Data Set - Say Line 1'),
(4781,0,6,0,61,0,100,0,0,0,0,0,8,0,0,0,0,0,0,23,0,0,0,0,0,0,0,'Snufflenose Gopher - On Data Set - Set Passive'),
(4781,0,7,0,8,0,100,0,8283,0,0,0,45,1,1,0,0,0,0,20,20920,20,0,0,0,0,0,'Snufflenose Gopher - On Spellhit (Snufflenose Command) - Set Data Blueleaf Tuber'),
(4781,0,8,9,61,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Snufflenose Gopher - On Just Summoned - Set Passive'),
(4781,0,9,0,61,0,100,0,0,0,0,0,44,3,0,0,0,0,0,1,0,0,0,0,0,0,0,'Snufflenose Gopher - On Just Summoned - Set Phasemask 3');

DELETE FROM `smart_scripts` WHERE `entryorguid` = 20920 AND `source_type` = 1;
INSERT INTO `smart_scripts` VALUES 
(20920,1,0,0,11,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Blueleaf Tuber - On Spawn - Set Phase 1'),
(20920,1,1,2,38,1,100,0,1,1,0,0,45,1,1,0,0,0,0,19,4781,0,0,0,0,0,0,'Blueleaf Tuber - On Data Set (Phase 1) - Set Data Snufflenose Gopher'),
(20920,1,2,0,61,0,100,0,0,0,0,0,22,2,0,0,0,0,0,1,0,0,0,0,0,0,0,'Blueleaf Tuber - On Data Set (Phase 1) - Set Phase 2'),
(20920,1,3,0,1,0,100,0,300000,300000,300000,300000,22,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Blueleaf Tuber - OOC (Phase 2) - Set Phase 1'),
(20920,1,4,0,38,1,100,0,2,2,0,0,44,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Blueleaf Tuber - On Data Set (Phase 1) - Set Phase 2');

DELETE FROM `smart_scripts` WHERE `entryorguid` = 478100 AND `source_type` = 9;
INSERT INTO `smart_scripts` VALUES 
(478100,9,0,0,0,0,100,0,5000,5000,0,0,1,2,0,0,0,0,0,23,0,0,0,0,0,0,0,'Snufflenose Gopher - Script - Say Line 2'),
(478100,9,1,0,0,0,100,0,0,0,0,0,44,1,0,0,0,0,0,20,20920,0,0,0,0,0,0,'Snufflenose Gopher - Script - Set Phasemask 1 on Blueleaf Tubers'),
(478100,9,3,0,0,0,100,0,5000,5000,0,0,29,1,0,0,0,0,0,23,0,0,0,0,0,0,0,'Snufflenose Gopher - Script - Follow Summoner'),
(478100,9,4,0,0,0,100,0,0,0,0,0,8,2,0,0,0,0,0,1,0,0,0,0,0,0,0,'Snufflenose Gopher - Script - Set Hostile');

UPDATE gameobject g SET g.spawntimesecs = 43200, g.phaseMask = 2 WHERE g.id = 20920;