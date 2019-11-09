-- [NPC]Reanimated Crusader - Hammer of Injustice should not bypass cooldown
-- [NPC]Rampaging Ghoul - correct movement speed
-- [NPC]Pustulent Horror - add spells
-- [NPC] Reanimated Abomination from "Thats Abominable" quest should despawn after exploding
-- [Spell] Burst at the Seams - should knockback players
UPDATE `smart_scripts` SET `event_param3` = 65000, `event_param4` = 70000 WHERE `entryorguid` = 30202 AND `id` = 3;
UPDATE `creature_template` SET `speed_run` = 2 WHERE `entry` = 32178;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 31139 AND `id` IN (2,3);
INSERT INTO `smart_scripts` VALUES
(31139, 0, 2, 0, 0, 0, 100, 0, 3000, 5000, 3000, 7000, 11, 28405, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Pustulent Horror - IC - Cast Knock Back'),
(31139, 0, 3, 0, 0, 0, 100, 0, 4000, 6000, 5000, 9000, 11, 63546, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Pustulent Horror - IC - Cast Stomp');
UPDATE `smart_scripts` SET `target_type` = 7 WHERE `entryorguid` = 31692 AND `id` = 4;
UPDATE `smart_scripts` SET `link` = 7 WHERE `entryorguid` = 31692 AND `id` = 6;

DELETE FROM `smart_scripts` WHERE `entryorguid` = 31692 AND `id` = 7;
INSERT INTO `smart_scripts` VALUES 
(31692, 0, 7, 0, 61, 0, 100, 0, 0, 0, 0, 0, 41, 500, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Reanimated Abomination - Linked - Despawn self');

DELETE FROM `conditions` WHERE `SourceEntry` = 59576 AND `ElseGroup` = 3;
INSERT INTO `conditions` VALUES
(13, 2, 59576, 0, 3, 31, 0, 4, 0, 0, 0, 0, 0, '', '');
