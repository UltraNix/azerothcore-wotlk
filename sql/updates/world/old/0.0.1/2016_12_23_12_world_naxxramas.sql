UPDATE `creature_template` SET `mechanic_immune_mask` = mechanic_immune_mask | 2048 | 524288 WHERE `entry` IN (16428, 16441);

DELETE FROM `creature_text` WHERE `entry` = 16980;
INSERT INTO `creature_text` VALUES
(16980, 0, 0, 'Soon we will eradicate the Alliance and Horde. Then the rest of Azeroth will fall before the might of my army.', 14, 0, 100, 0, 0, 14768, 3, '(SAY_SAPP_DIALOG2_LICH'),
(16980, 1, 0, 'Invaders... here?! DESTROY them, Kel\'Thuzad! Naxxramas must not fall!', 14, 0, 100, 0, 0, 14769, 3, '(SAY_SAPP_DIALOG4_LICH');

-- INSERT INTO `creature_text` VALUES (16980, 0, 0, 'It is good that you serve me so faithfully. Soon, all will serve the Lich King and in the end, you shall be rewarded...so long as you do not falter.', 14, 0, 100, 0, 0, 8881, 0, 'kelthuzad SAY_SAPP_DIALOG2_LICH');
-- INSERT INTO `creature_text` VALUES (16980, 1, 0, 'Your security measures have failed! See to this interruption immediately!', 14, 0, 100, 0, 0, 8882, 0, 'kelthuzad SAY_SAPP_DIALOG4_LICH');