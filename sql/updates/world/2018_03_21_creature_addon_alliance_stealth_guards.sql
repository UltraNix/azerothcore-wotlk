SET @AURA = 18950;
UPDATE `creature_addon` SET `auras` = @AURA WHERE `guid` IN (1814,79818,10527,10528,46216);
UPDATE `creature_template_addon` SET `auras` = @AURA WHERE `entry` IN (20674,1756);
