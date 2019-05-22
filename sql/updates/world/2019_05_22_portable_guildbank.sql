SET @ENTRY := 211000;

DELETE FROM `creature_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_template` VALUES (@ENTRY,0,0,0,0,0,7993,0,0,0,'Cagy Littlefinger',NULL,NULL,0,80,80,0,35,0,1,1.14286,1,0,56,74,0,136,1,1000,2000,1,0,2048,0,0,0,0,0,0,39,57,14,7,4096,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,3,1,1.15,1,1,0,0,0,0,0,0,0,0,1,0,2,'npc_custom_guild_bank_companion',12340);

SET @ENTRY := 32618;
DELETE FROM `item_template` WHERE `entry` = @ENTRY;
INSERT INTO `item_template` VALUES (@ENTRY,15,0,-1,'Portable Guild Bank',37541,5,64,0,1,0,0,0,-1,-1,70,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,53374,0,0,0,-1,0,-1,0,0,0,0,-1,0,-1,0,0,0,0,-1,0,-1,0,0,0,0,-1,0,-1,0,0,0,0,-1,0,-1,1,'Summons guild bank vendor',0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,'item_portable_guildbank',0,0,0,0,0,1);