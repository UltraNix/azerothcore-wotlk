DELETE FROM `smart_scripts` WHERE `entryorguid` = 30562;
INSERT INTO `smart_scripts` VALUES 
(30562, 0, 0, 1, 20, 0, 100, 0, 13082, 0, 0, 0, 11, 57786, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Crusader Bridenbrad - On Quest \'The Boon of A\'dal\' Finished - Cast \'Summon K\'uri\''),
(30562, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 11, 57782, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Crusader Bridenbrad - On Quest \'The Boon of A\'dal\' Finished - Cast \'Summon M\'ori\''),
(30562, 0, 2, 3, 61, 0, 100, 0, 0, 0, 0, 0, 11, 57746, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Crusader Bridenbrad - On Quest \'The Boon of A\'dal\' Finished - Cast \'Summon A\'dal\''),
(30562, 0, 3, 4, 61, 0, 100, 0, 0, 0, 0, 0, 11, 57747, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Crusader Bridenbrad - On Quest \'The Boon of A\'dal\' Finished - Cast \'Summon Spirit of Bridenbrad\''),
(30562, 0, 4, 0, 61, 0, 100, 0, 0, 0, 0, 0, 11, 57773, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Crusader Bridenbrad - On Quest \'The Boon of A\'dal\' Finished - Cast \'Summon Light Bunny\'');

SET @EVENT_LENGTH = 20000;

UPDATE `smart_scripts` SET `action_param1` = @EVENT_LENGTH  WHERE `entryorguid` = 30712 AND `id` = 1;
UPDATE `smart_scripts` SET `action_param1` = @EVENT_LENGTH WHERE `entryorguid` = 30693 AND `id` = 0;
UPDATE `smart_scripts` SET `action_param1` = @EVENT_LENGTH WHERE `entryorguid` = 30692 AND `id` = 0;
UPDATE `smart_scripts` SET `action_param1` = @EVENT_LENGTH WHERE `entryorguid` = 30691 AND `id` = 0;
UPDATE `smart_scripts` SET `event_param1` = @EVENT_LENGTH, `event_param2` = @EVENT_LENGTH, `event_param3` = @EVENT_LENGTH, `event_param4` = @EVENT_LENGTH, `action_param1` = 0  WHERE `entryorguid` = 30694 AND `id` = 2;
UPDATE `smart_scripts` SET `event_flags` = 1, `event_param3` = 0, `event_param4` = 0 WHERE `entryorguid` = 30694 AND `id` = 0;

UPDATE `smart_scripts` SET `link` = 2 WHERE `entryorguid` = 30712 AND `id` = 0;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 30712 AND `id` = 2;
INSERT INTO `smart_scripts` VALUES
(30712, 0, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 11, 25824, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Bridenbrad Light Bunny - On Respawn - Cast Spotlight');

UPDATE `creature_template` SET `speed_walk` = 0.5, `InhabitType` = 4, `unit_flags` = `unit_flags` | 33555200 WHERE `entry` = 30694;

UPDATE `smart_scripts` SET `link` = 3 WHERE `entryorguid` = 30694 AND `id` = 0;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 30694 AND `id` = 1;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 30694 AND `id` IN (3,4,5,6);
DELETE FROM `smart_scripts` WHERE `entryorguid` = 30691 AND `id` IN (1,2,3);
INSERT INTO `smart_scripts` VALUES
(30694, 0, 3, 4, 61, 0, 100, 0, 0, 0, 0, 0, 90, 33554432, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(30694, 0, 1, 0, 54, 0, 100, 0, 0, 0, 0, 0, 11, 64462, 7, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(30694, 0, 4, 5, 61, 0, 100, 0, 0, 0, 0, 0, 59, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Bridenbrad Spirit - disable run'),
(30694, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 114, 20, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Bridenbrad Spirit - Move offset'),
(30691, 0, 1, 0, 1, 0, 100, 1, 4000, 4000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(30691, 0, 2, 0, 1, 0, 100, 1, 10000, 10000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(30691, 0, 3, 0, 1, 0, 100, 1, 15000, 15000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');
DELETE FROM `creature_text` WHERE `entry` = 30691;
INSERT INTO `creature_text` VALUES
(30691, 0, 0, 'Fear not, young one, for this crusader shall not taste death.', 12, 0, 100, 0, 0, 0, 0, ''),
(30691, 1, 0, 'In life, Bridenbrad was the bearer of great deeds. Now, in passing, he shall taste only paradise.', 12, 0, 100, 0, 0, 0, 0, ''),
(30691, 2, 0, 'The light does not abandon its champions.', 12, 0, 100, 0, 0, 0, 0, '');
