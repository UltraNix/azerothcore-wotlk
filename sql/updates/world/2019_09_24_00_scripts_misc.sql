-- DB/NPC: Deadwood Shaman - update AI, fix someissues with spellcasting
UPDATE `smart_scripts` SET `action_param2` = 0 WHERE `entryorguid` = 7158 AND `id` IN (1,2);
