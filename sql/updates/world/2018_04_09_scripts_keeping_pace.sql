SET @EXPLOSION = 50775;
SET @RIZZLE = 4720;
SET @ZAMEK = 4709;
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` = @RIZZLE;
DELETE FROM `creature_questender` WHERE `id` = 4709 AND `quest` = 1191;
UPDATE `creature` SET `npcflag` = 1 WHERE `guid` = 21572;
UPDATE `creature_template` SET `gossip_menu_id` = 56004 WHERE `entry` = @ZAMEK;

DELETE FROM `gossip_menu_option` WHERE `menu_id` = 56004;
INSERT INTO `gossip_menu_option` VALUES
(56004, 0, 0, 'I\'m ready, create some diversion', 1, 1, 0, 0, 0, 0, '');
UPDATE `smart_scripts` SET `event_type` = 62, `event_param1` = 56004, `comment` = "Zamek - On Gossip Option Selected - Run Script" WHERE `entryorguid` = @ZAMEK AND `id` = 0;

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@ZAMEK*100, @RIZZLE, @RIZZLE*100);
INSERT INTO `smart_scripts` VALUES
(@ZAMEK*100, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 69, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, -6273.41, -3841.7, -58.75, 1.9, 'Zamek - On Script - Move To Position'),
(@ZAMEK*100, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 83, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Zamek - On Script - Remove gossip flag'),
(@ZAMEK*100, 9, 2, 0, 0, 0, 100, 0, 18000, 18000, 0, 0, 70, 600, 0, 0, 0, 0, 0, 14, 13621, 20805, 0, 0, 0, 0, 0, 'Zamek - On Script - Respawn Closest Gameobject \'Rizzle\'s Unguarded Plans\''),
(@ZAMEK*100, 9, 3, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 9, @RIZZLE, 0, 100, 0, 0, 0, 0, 'Zamek - On Script - Set Data'),
(@ZAMEK*100, 9, 4, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Zamek - On Script - Set Data'),
(@ZAMEK*100, 9, 5, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 11, @EXPLOSION, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Zamek - On Script - Cast Explosion'),
(@ZAMEK*100, 9, 6, 0, 0, 0, 100, 0, 0, 0, 0, 0, 69, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, -6224, -3945, -58.75, 0.75, 'Zamek - On Script - Move To Position'),
(@ZAMEK*100, 9, 7, 0, 0, 0, 100, 0, 0, 0, 0, 0, 81, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Zamek - On Script - Restor Gossip falg'),
(@RIZZLE, 0, 0, 0, 38, 0, 100, 0, 1, 1, 0, 0, 80, @RIZZLE*100, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Rizzle - data set - start script'),
(@RIZZLE*100, 9, 0, 0, 0, 0, 100, 0, 10000, 10000, 0, 0, 69, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, -6259.36, -3853.21, -58.76, 2.41, 'Rizzle - Script - Move to pos'),
(@RIZZLE*100, 9, 1, 0, 0, 0, 100, 0, 15000, 15000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Rizzle - Script - Say line 0'),
(@RIZZLE*100, 9, 2, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 24, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Rizzle - Script - Return to home pos');

DELETE FROM `creature_text` WHERE `entry` IN (@ZAMEK, @RIZZLE);
INSERT INTO `creature_text` VALUES
(@ZAMEK, 0, 0, 'Hehehe! Things go boom!', 12, 0, 100, 0, 0, 0, 0, 'Zamek'),
(@RIZZLE, 0, 0, 'Guess there\'s nothing more to be done. Blast!', 12, 0, 100, 0, 0, 0, 0, 'Rizzle');

DELETE FROM `conditions` WHERE `SourceGroup` = 56004 AND `ConditionValue1` = 1190;
INSERT INTO `conditions` VALUES
(15, 56004, 0, 0, 0, 28, 0, 1190, 0, 0, 0, 0, 0, 0, 'Zamek show gossip if quest Keeping pace completed');
