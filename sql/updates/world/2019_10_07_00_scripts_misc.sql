UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entryorguid` = 26158;
DELETE FROM smart_scripts WHERE entryorguid = 26158;
