-- sartharion boost
SET @SARTHARION_BASE:= 550;
SET @DRAGONS_BASE:= 160;

UPDATE `creature_template` SET `health_mod` = @SARTHARION_BASE + (@SARTHARION_BASE * 0.5997) WHERE `entry` = 31311;
UPDATE `creature_template` SET `health_mod` = @DRAGONS_BASE + (@DRAGONS_BASE * 0.6009) WHERE `entry` IN (31520, 31535, 31534);
