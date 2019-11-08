SET @QUESTGIVER_ENTRY = 200000;

-- Kel'Thuzad quest
SET @ITEM_ENTRY := 13602;
DELETE FROM `item_template` WHERE `entry` = @ITEM_ENTRY;
INSERT INTO `item_template` VALUES (@ITEM_ENTRY,12,0,-1,'Phylactery of Kel\'Thuzad',21610,5,2048,8192,1,0,0,0,-1,-1,1,0,0,0,0,0,0,0,0,0,20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,-1,0,0,0,0,-1,0,-1,0,0,0,0,-1,0,-1,0,0,0,0,-1,0,-1,0,0,0,0,-1,0,-1,4,'',0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,'',0,0,0,0,0,12340);

SET @QUEST_ENTRY := 30007;
DELETE FROM `quest_template` WHERE `Id` = @QUEST_ENTRY;
INSERT INTO `quest_template` VALUES (@QUEST_ENTRY,2,80,80,0,4395,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,@QUEST_ENTRY + 1,0,1000000,0,0,0,0,0,0,0,0,0,0,72,0,0,0,0,0,49426,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,'The Forgotten Phylactery','Defeat Kel’Thuzad in Naxxramas (any difficulty) and bring Phylactery of Kel’Thuzad to the Wanderer.','Some of them just return, doesn’t matter how many times have you killed them… Oh, the irony… I’m sorry, what was I...? Ah, yes. A few years ago, one of Lich King lieutenants was slain. However, he has returned. Kel’Thuzad, the powerful lich, is bound to his phylactery. After his first defeat, it was used to bring him back. I need the phylactery. You have to defeat him and bring me the phylactery, only then we can make sure he’s finished. And I’d like to keep this… souvenir.','','This is good… for the first step. Now, Kel’Thuzad will never return and I could use this… gift of yours to restore at least some of my long lost power. But it’s not over yet. There are more threats… and more trinkets.',' Do you have it? Do you have the Phylactery of Kel’Thuzad?','',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,@ITEM_ENTRY,0,0,0,0,0,1,0,0,0,0,0,0,'Defeat Kel’Thuzad in Naxxramas (any difficulty) and bring Phylactery of Kel’Thuzad to the Wanderer.','','','',1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,12340);

DELETE FROM `creature_loot_template` WHERE item = @ITEM_ENTRY;
INSERT INTO `creature_loot_template` VALUES (15990, @ITEM_ENTRY, -100, 1, 0, 1, 1); -- 10 man
INSERT INTO `creature_loot_template` VALUES (30061, @ITEM_ENTRY, -100, 1, 0, 1, 1); -- 25 man

DELETE FROM `creature_queststarter` WHERE `id` = @QUESTGIVER_ENTRY AND `quest` = @QUEST_ENTRY;
INSERT INTO `creature_queststarter` VALUES(@QUESTGIVER_ENTRY, @QUEST_ENTRY);

DELETE FROM `creature_questender` WHERE `id` = @QUESTGIVER_ENTRY AND `quest` = @QUEST_ENTRY;
INSERT INTO `creature_questender` VALUES(@QUESTGIVER_ENTRY, @QUEST_ENTRY);


-- Yogg-Saron quest
SET @ITEM_ENTRY := 1254;
DELETE FROM `item_template` WHERE `entry` = @ITEM_ENTRY;
INSERT INTO `item_template` VALUES (@ITEM_ENTRY,12,0,-1,'Blood of the Old God',24380,5,2048,8192,1,0,0,0,-1,-1,1,0,0,0,0,0,0,0,0,0,20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,-1,0,0,0,0,-1,0,-1,0,0,0,0,-1,0,-1,0,0,0,0,-1,0,-1,0,0,0,0,-1,0,-1,4,'',0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,'',0,0,0,0,0,12340);

SET @QUEST_ENTRY := 30008;
DELETE FROM `quest_template` WHERE `Id` = @QUEST_ENTRY;
INSERT INTO `quest_template` VALUES (@QUEST_ENTRY,2,80,80,0,4395,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,@QUEST_ENTRY - 1,0,0,@QUEST_ENTRY + 1,0,1000000,0,0,0,0,0,0,0,0,0,0,72,0,0,0,0,0,49426,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,'Blood of the Old God','Defeat Yogg-Saron in Ulduar (any difficulty) and bring Blood of the Old God to the Wanderer.','You know what Saronite is? It’s also called “black blood of Yogg-Saron”. I need it, but the ore doesn’t meet any of my requirements. It doesn’t really work. I think I need… fresh blood. I need you to venture to Ulduar and lay siege to its defendants. Find Yogg-Saron and defeat him. You won’t be able to kill him, of course. You can’t kill and Old God, you can merely… push him back. Especially when he’s as weakened as Yogg-Saron, whose body stretches beneath all of Northrend. Bring me his blood.','','You’ve made it. When Yogg-Saron rises again, he won’t be happy. But I hope we will be long gone by then. Now, there’s more to do.', 'I hope you have a fresh vial of Yogg-Saron’s blood','',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,@ITEM_ENTRY,0,0,0,0,0,1,0,0,0,0,0,0,'Defeat Yogg-Saron in Ulduar (any difficulty) and bring Blood of the Old God to the Wanderer.','','','',1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,12340);

DELETE FROM `creature_loot_template` WHERE item = @ITEM_ENTRY;
DELETE FROM `creature_loot_template` WHERE item = @ITEM_ENTRY;
INSERT INTO `creature_loot_template` VALUES (33288, @ITEM_ENTRY, -100, 1, 0, 1, 1); -- 10 man
INSERT INTO `creature_loot_template` VALUES (33955, @ITEM_ENTRY, -100, 1, 0, 1, 1); -- 25 man

DELETE FROM `creature_queststarter` WHERE `id` = @QUESTGIVER_ENTRY AND `quest` = @QUEST_ENTRY;
INSERT INTO `creature_queststarter` VALUES(@QUESTGIVER_ENTRY, @QUEST_ENTRY);

DELETE FROM `creature_questender` WHERE `id` = @QUESTGIVER_ENTRY AND `quest` = @QUEST_ENTRY;
INSERT INTO `creature_questender` VALUES(@QUESTGIVER_ENTRY, @QUEST_ENTRY);

-- Anub'Arak quest
SET @ITEM_ENTRY := 41605;
DELETE FROM `item_template` WHERE `entry` = @ITEM_ENTRY;
INSERT INTO `item_template` VALUES (@ITEM_ENTRY,12,0,-1,'Carapace of the Nerubian King',42717,5,2048,8192,1,0,0,0,-1,-1,1,0,0,0,0,0,0,0,0,0,20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,-1,0,0,0,0,-1,0,-1,0,0,0,0,-1,0,-1,0,0,0,0,-1,0,-1,0,0,0,0,-1,0,-1,4,'',0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,'',0,0,0,0,0,12340);

SET @QUEST_ENTRY := 30009;
DELETE FROM `quest_template` WHERE `Id` = @QUEST_ENTRY;
INSERT INTO `quest_template` VALUES (@QUEST_ENTRY,2,80,80,0,4395,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,@QUEST_ENTRY - 1,0,0,@QUEST_ENTRY + 1,0,1000000,0,0,0,0,0,0,0,0,0,0,72,0,0,0,0,0,49426,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,'Hard as a Nerubian','Defeat Anub’arak in Trial of the Crusader (any difficulty) and bring Carapace of the Nerubian King to the Wanderer.','I’ve heard many tales of the fallen king and I don’t mean Arthas. Anub’arak was slain in the War of the Spider and only then he was raised in undeath to serve the Lich King. He has betrayed his own kin, but as powerful as he was, he served as one of the highest ranked lieutenants of Ner’zhul. He serves no purpose for me, but as unbreakable in life as he was… I need his carapace. At least a part of it. Do you have enough strength to break him for me? My agents say that he might show up during Trial of the Crusader.', '', 'It’s even harder than I thought. Good, good. It’s almost finished.', 'Say, you couldn’t take it off from him?','',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,@ITEM_ENTRY,0,0,0,0,0,1,0,0,0,0,0,0,'Defeat Anub’arak in Trial of the Crusader (any difficulty) and bring Carapace of the Nerubian King to the Wanderer.','','','',1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,12340);

DELETE FROM `creature_loot_template` WHERE item = @ITEM_ENTRY;
DELETE FROM `creature_loot_template` WHERE item = @ITEM_ENTRY;
INSERT INTO `creature_loot_template` VALUES (34564, @ITEM_ENTRY, -100, 1, 0, 1, 1); -- 10 man (normal)
INSERT INTO `creature_loot_template` VALUES (34566, @ITEM_ENTRY, -100, 1, 0, 1, 1); -- 25 man (normal)
INSERT INTO `creature_loot_template` VALUES (35615, @ITEM_ENTRY, -100, 1, 0, 1, 1); -- 10 man (heroic)
INSERT INTO `creature_loot_template` VALUES (35616, @ITEM_ENTRY, -100, 1, 0, 1, 1); -- 25 man (heroic)

DELETE FROM `creature_queststarter` WHERE `id` = @QUESTGIVER_ENTRY AND `quest` = @QUEST_ENTRY;
INSERT INTO `creature_queststarter` VALUES(@QUESTGIVER_ENTRY, @QUEST_ENTRY);

DELETE FROM `creature_questender` WHERE `id` = @QUESTGIVER_ENTRY AND `quest` = @QUEST_ENTRY;
INSERT INTO `creature_questender` VALUES(@QUESTGIVER_ENTRY, @QUEST_ENTRY);

-- Onyxia quest
SET @ITEM_ENTRY := 18566;
DELETE FROM `item_template` WHERE `entry` = @ITEM_ENTRY;
INSERT INTO `item_template` VALUES (@ITEM_ENTRY,12,0,-1,'Eye of Onyxia',30913,5,2048,8192,1,0,0,0,-1,-1,1,0,0,0,0,0,0,0,0,0,20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,-1,0,0,0,0,-1,0,-1,0,0,0,0,-1,0,-1,0,0,0,0,-1,0,-1,0,0,0,0,-1,0,-1,4,'',0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,'',0,0,0,0,0,12340);

SET @QUEST_ENTRY := 30010;
DELETE FROM `quest_template` WHERE `Id` = @QUEST_ENTRY;
INSERT INTO `quest_template` VALUES (@QUEST_ENTRY,2,80,80,0,4395,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,@QUEST_ENTRY - 1,0,0,@QUEST_ENTRY + 1,0,1000000,0,0,0,0,0,0,0,0,0,0,72,0,0,0,0,0,49426,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,'The Broodmother','Defeat Onyxia in Onyxia’s Lair (any difficulty) and bring Eye of Onyxia to the Wanderer.','Now, something easier and quicker. In Dustwallow Marsh, a black, mature dragon has its lair. She’s called Onyxia. Sister to Nefarian and daughter to Neltharion, she keeps breeding these black dragons… I don’t really mind, but I wouldn’t be mad if the Black Dragonflight took a painful hit. There’s something else… I need her eye. Only one. Bring it to me. We’re getting closer to the finish.','', 'Now I have almost everything I need. Thank you, <name>. Now, for the harder part…', 'It shouldn’t be hard. Do you have the eye?','',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,@ITEM_ENTRY,0,0,0,0,0,1,0,0,0,0,0,0,'Defeat Onyxia in Onyxia’s Lair (any difficulty) and bring Eye of Onyxia to the Wanderer.','','','',1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,12340);

DELETE FROM `creature_loot_template` WHERE item = @ITEM_ENTRY;
DELETE FROM `creature_loot_template` WHERE item = @ITEM_ENTRY;
INSERT INTO `creature_loot_template` VALUES (10184, @ITEM_ENTRY, -100, 1, 0, 1, 1); -- 10 man
INSERT INTO `creature_loot_template` VALUES (36538, @ITEM_ENTRY, -100, 1, 0, 1, 1); -- 25 man  

DELETE FROM `creature_queststarter` WHERE `id` = @QUESTGIVER_ENTRY AND `quest` = @QUEST_ENTRY;
INSERT INTO `creature_queststarter` VALUES(@QUESTGIVER_ENTRY, @QUEST_ENTRY);

DELETE FROM `creature_questender` WHERE `id` = @QUESTGIVER_ENTRY AND `quest` = @QUEST_ENTRY;
INSERT INTO `creature_questender` VALUES(@QUESTGIVER_ENTRY, @QUEST_ENTRY);

-- Lich King quest
SET @ITEM_ENTRY := 23364;
DELETE FROM `item_template` WHERE `entry` = @ITEM_ENTRY;
INSERT INTO `item_template` VALUES (@ITEM_ENTRY,12,0,-1,'Frozen Tear',12310,5,2048,8192,1,0,0,0,-1,-1,1,0,0,0,0,0,0,0,0,0,20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,-1,0,0,0,0,-1,0,-1,0,0,0,0,-1,0,-1,0,0,0,0,-1,0,-1,0,0,0,0,-1,0,-1,4,'',0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,'',0,0,0,0,0,12340);

SET @QUEST_ENTRY := 30011;
DELETE FROM `quest_template` WHERE `Id` = @QUEST_ENTRY;
INSERT INTO `quest_template` VALUES (@QUEST_ENTRY,2,80,80,0,4395,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,@QUEST_ENTRY - 1,0,0,0,0,1000000,0,0,0,0,0,0,0,0,0,0,72,0,0,0,0,0,49426,0,0,0,2,0,0,0,46376,46377,46378,0,0,0,5,5,5,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,'Tear of the Fallen Prince','Defeat the Lich King in Icecrown Citadel (any difficulty) and bring Frozen Tear to the Wanderer.', 'Nobody knows pain better than Arthas. Nobody knows rejection, disappointment, loss, betrayal, better than him. He tore his own heart out. Despite being the Lich King, despite controlling the Scourge… We’re still alive. And we shouldn’t be alive. He obviously keeps the dead at bay. Inside, he’s still the young boy he once was, despite everything. That makes me wonder… Will he shed even one tear after all he has done? Make sure of it. Kill the Lich King and bring me his frozen tear.','', 'It is done. I have everything I need… for now. I could restore some of my power using these artifacts… You’ve shown a lot of strength and iron will, too. I’m glad. It seems like I’ve chosen the right person.', 'Any tears? Any remorse? Any pain?','',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,@ITEM_ENTRY,0,0,0,0,0,1,0,0,0,0,0,0,'Defeat the Lich King in Icecrown Citadel (any difficulty) and bring Frozen Tear to the Wanderer.','','','',1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,12340);

DELETE FROM `creature_loot_template` WHERE item = @ITEM_ENTRY;
INSERT INTO `creature_loot_template` VALUES (36597, @ITEM_ENTRY, -100, 1, 0, 1, 1); -- 10 man (normal)
INSERT INTO `creature_loot_template` VALUES (39166, @ITEM_ENTRY, -100, 1, 0, 1, 1); -- 25 man (normal)
INSERT INTO `creature_loot_template` VALUES (39167, @ITEM_ENTRY, -100, 1, 0, 1, 1); -- 10 man (heroic)
INSERT INTO `creature_loot_template` VALUES (39168, @ITEM_ENTRY, -100, 1, 0, 1, 1); -- 25 man (heroic)

DELETE FROM `creature_queststarter` WHERE `id` = @QUESTGIVER_ENTRY AND `quest` = @QUEST_ENTRY;
INSERT INTO `creature_queststarter` VALUES(@QUESTGIVER_ENTRY, @QUEST_ENTRY);

DELETE FROM `creature_questender` WHERE `id` = @QUESTGIVER_ENTRY AND `quest` = @QUEST_ENTRY;
INSERT INTO `creature_questender` VALUES(@QUESTGIVER_ENTRY, @QUEST_ENTRY);