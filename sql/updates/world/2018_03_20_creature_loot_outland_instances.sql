UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 1 WHERE `mincountOrRef` IN (-24023,-24022,-24011,-24003);
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 0.5 WHERE `mincountOrRef` IN (-24023,-24022,-24011,-24003) AND `entry` IN (17259,17370);
