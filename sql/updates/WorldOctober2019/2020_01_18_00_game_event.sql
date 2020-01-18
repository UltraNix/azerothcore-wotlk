DELETE FROM `holiday_dates` WHERE `id` = 423 AND `date_id` = 0;
INSERT INTO `holiday_dates` VALUES (423, 0, 336708352, 20160); -- Add event to calendar
UPDATE `game_event` SET `start_time`='2018-02-08 12:00:00' WHERE `eventEntry`=8; -- Change game_event date
DELETE FROM `item_loot_template` WHERE  `entry`=54537 AND `item`=40753 AND `lootmode`=1; -- Delete Emblems from Heart-Shaped Box
DELETE FROM `reference_loot_template` WHERE `item` IN ( 51804, 51805, 51806, 51807, 51808); -- Delete 226 necks from event boss