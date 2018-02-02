-- #26
UPDATE `gameobject_loot_template` SET `ChanceOrQuestChance` = '50', `maxcount` = '6' WHERE `gameobject_loot_template`.`entry` = 1502 AND `gameobject_loot_template`.`item` = 2835;
-- #35
UPDATE `creature_template` SET `ScriptName` = 'npc_goldir' WHERE `creature_template`.`entry` = 2316;