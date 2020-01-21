-- DB/Loot: Tears of bitter Anguish - slightly increase drop chance
UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 0.1 WHERE `entry` = 29570 AND `item` = 43573;