SET @BASE_ENTRY:= 37007;
SET @HERIOC_ENTRY:= 38031;

UPDATE `creature_template` SET `mechanic_immune_mask` = 617299839, `flags_extra` = 2097152 WHERE `entry` IN (@BASE_ENTRY, @HERIOC_ENTRY);
