DELETE FROM `spell_script_names` WHERE `spell_id` IN (63317, 64021);
INSERT INTO `spell_script_names` VALUES
(63317, "spell_razorscale_flame_breath"),
(64021, "spell_razorscale_flame_breath");

UPDATE `creature_template` SET `ScriptName` = "npc_razorscale_devouring_flame" WHERE `entry` = 34188;

SET @DARK_RUNE_WATCHER:= 33851;
SET @DARK_RUNE_SENTINEL:= 33852;
SET @DARK_RUNE_GUARDIAN:= 33850;

UPDATE `creature_template` SET `mindmg` = 200, `maxdmg` = 300, `dmg_multiplier` = 20 WHERE `entry` = @DARK_RUNE_WATCHER;
UPDATE `creature_template` SET `dmg_multiplier` = 75 WHERE `entry` = @DARK_RUNE_SENTINEL;
UPDATE `creature_template` SET `dmg_multiplier` = 36 WHERE `entry` = @DARK_RUNE_GUARDIAN;
