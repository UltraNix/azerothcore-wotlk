SET @ENTRY := 1100000;

DELETE FROM `npc_text` WHERE ID BETWEEN @ENTRY AND @ENTRY + 2;
INSERT INTO `npc_text` VALUES 
(@ENTRY,'Hey!\nSo you want to spectate some arenas, eh? What kind of bracket are you interested in?',NULL,0,0,0,0,0,0,0,0,NULL,NULL,0,0,0,0,0,0,0,0,NULL,NULL,0,0,0,0,0,0,0,0,NULL,NULL,0,0,0,0,0,0,0,0,NULL,NULL,0,0,0,0,0,0,0,0,NULL,NULL,0,0,0,0,0,0,0,0,NULL,NULL,0,0,0,0,0,0,0,0,NULL,NULL,0,0,0,0,0,0,0,0,1),
(@ENTRY + 1,'Well, there are no fights in this bracket at this moment. Check later or try another bracket.',NULL,0,0,0,0,0,0,0,0,NULL,NULL,0,0,0,0,0,0,0,0,NULL,NULL,0,0,0,0,0,0,0,0,NULL,NULL,0,0,0,0,0,0,0,0,NULL,NULL,0,0,0,0,0,0,0,0,NULL,NULL,0,0,0,0,0,0,0,0,NULL,NULL,0,0,0,0,0,0,0,0,NULL,NULL,0,0,0,0,0,0,0,0,1),
(@ENTRY + 2,'Which fight do you want to see?\n',NULL,0,0,0,0,0,0,0,0,NULL,NULL,0,0,0,0,0,0,0,0,NULL,NULL,0,0,0,0,0,0,0,0,NULL,NULL,0,0,0,0,0,0,0,0,NULL,NULL,0,0,0,0,0,0,0,0,NULL,NULL,0,0,0,0,0,0,0,0,NULL,NULL,0,0,0,0,0,0,0,0,NULL,NULL,0,0,0,0,0,0,0,0,1);

SET @ENTRY := 210000;
DELETE FROM `creature_template` WHERE entry = @ENTRY;
INSERT INTO `creature_template` VALUES (@ENTRY,0,0,0,0,0,7102,0,0,0,'Buzz Gutwrench','Arena Reporter',NULL,0,40,40,0,35,1,1,1.14286,1,0,56,74,0,136,1,1000,2000,1,0,2048,0,0,0,0,0,0,39,57,14,7,4096,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,3,1,1.15,1,1,0,0,0,0,0,0,0,0,1,0,2,'npc_arena_spectator',12340);
