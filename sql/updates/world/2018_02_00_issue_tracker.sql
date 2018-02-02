-- #26
UPDATE `gameobject_loot_template` SET `ChanceOrQuestChance` = '50', `maxcount` = '6' WHERE `gameobject_loot_template`.`entry` = 1502 AND `gameobject_loot_template`.`item` = 2835;
-- #35
UPDATE `creature_template` SET `ScriptName` = 'npc_goldir' WHERE `creature_template`.`entry` = 2316;
-- #41
UPDATE `spell_proc_event` SET `procFlags` = '40' WHERE `spell_proc_event`.`entry` = 67653;
-- #98
UPDATE creature_template SET scriptname = "npc_elwynn_wolf" WHERE entry IN (69,299);