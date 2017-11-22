-- those quests are not pick up type of quests, they require player to get those items and go to npc (blue mark above their head)
-- which means we cannot set loot to be picked up only with quest in questLog
UPDATE `gameobject_loot_template` SET `ChanceOrQuestChance` = 100, `ChanceOrQuestChance` = 45, `groupid` = 1 WHERE `entry` = 11103 AND `item` IN (11753, 11752, 11751);
