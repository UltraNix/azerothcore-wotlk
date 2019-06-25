-- DB/NPC: "Cookie" McWeaksauce - add dialogue with Amiral Odesyus
UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry` IN (17246, 17240);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (17246, 17240, 1724600);
INSERT INTO `smart_scripts` VALUES 
(17246, 0, 0, 0, 1, 0, 100, 0, 0, 30000, 300000, 450000, 80, 1724600, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '"Cookie" McWeaksauce - OOC - Run Script'),
(17246, 0, 1, 0, 40, 0, 100, 0, 3, 17246, 0, 0, 54, 60000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '"Cookie" McWeaksauce - On Reached WP3 - Pause WP'),
(1724600, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 53, 0, 17246, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Cookie" McWeaksauce - Script - Start WP'),
(1724600, 9, 1, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 17240, 0, 0, 0, 0, 0, 0, 'Cookie" McWeaksauce - Script - Set Data 1 1 on Admiral Odesyus'),
(1724600, 9, 2, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 19, 17240, 0, 0, 0, 0, 0, 0, 'Cookie" McWeaksauce - Script - Say Line 1 on Admiral Odesyus'),
(1724600, 9, 3, 0, 0, 0, 100, 0, 9000, 9000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Cookie" McWeaksauce - Script - Say Line 1'),
(1724600, 9, 4, 0, 0, 0, 100, 0, 9000, 9000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Cookie" McWeaksauce - Script - Say Line 2'),
(1724600, 9, 5, 0, 0, 0, 100, 0, 9000, 9000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Cookie" McWeaksauce - Script - Say Line 3'),
(1724600, 9, 6, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 19, 17240, 0, 0, 0, 0, 0, 0, 'Cookie" McWeaksauce - Script - Say Line 2 on Admiral Odesyus'),
(1724600, 9, 7, 0, 0, 0, 100, 0, 9000, 9000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Cookie" McWeaksauce - Script - Say Line 4'),
(1724600, 9, 8, 0, 0, 0, 100, 0, 4000, 4000, 0, 0, 1, 4, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Cookie" McWeaksauce - Script - Say Line 6'),
(1724600, 9, 9, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 11, 30221, 0, 0, 0, 0, 0, 19, 620, 0, 0, 0, 0, 0, 0, 'Cookie" McWeaksauce - Script - Cast Shoot (Target Closest chicken)'),
(1724600, 9, 10, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 19, 17240, 0, 0, 0, 0, 0, 0, 'Cookie" McWeaksauce - Script - Say Line 3 on Admiral Odesyus'),
(1724600, 9, 11, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 45, 2, 2, 0, 0, 0, 0, 19, 17240, 0, 0, 0, 0, 0, 0, 'Cookie" McWeaksauce - Script - Set Data 2 2 on Admiral Odesyus'),
(17240, 0, 0, 0, 38, 0, 100, 0, 1, 1, 0, 0, 66, 0, 0, 0, 0, 0, 0, 19, 17246, 0, 0, 0, 0, 0, 0, 'Admiral Odesyus - On Data Set 1 1- Face "Cookie" McWeaksauce'),
(17240, 0, 1, 0, 38, 0, 100, 0, 2, 2, 0, 0, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 4.38078, 'Admiral Odesyus - On Data Set 2 2- Set Orientation'),
(17240, 0, 2, 0, 64, 0, 100, 0, 0, 0, 0, 0, 33, 17240, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Admiral Odesyus - On Gossip Hello - Quest Credit \'The Kessel Run\'');

DELETE FROM `creature_text` WHERE `entry` IN (17240, 17246);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `TextRange`, `comment`) VALUES 
(17240, 0, 0, 'Hey, Cookie! What\'s for dinner tonight? And don\'t say chicken!', 12, 7, 100, 22, 0, 0, 0, 'Admiral Odesyus'),
(17240, 1, 0, 'Wow! Really?', 12, 7, 100, 5, 0, 0, 0, 'Admiral Odesyus'),
(17240, 2, 0, 'I hate you so much, Cookie.', 12, 7, 100, 1, 0, 0, 0, 'Admiral Odesyus'),
(17246, 0, 0, 'Yarr, Admiral. Let me think about it... Arrr... It be comin\' into focus.', 12, 7, 100, 1, 0, 0, 0, '"Cookie" McWeaksauce'),
(17246, 1, 0, 'It looks like it be succulent pork ribs basted with its own delectable juices and a side o\' Captain Sander\'s Secret Sauce - fer dippin\'.', 12, 7, 100, 1, 0, 0, 0, '"Cookie" McWeaksauce'),
(17246, 2, 0, 'And fer dessert we be havin\' cheesecake, flown in fresh from Stormwind on the wings o\' angels...', 12, 7, 100, 1, 0, 0, 0, '"Cookie" McWeaksauce'),
(17246, 3, 0, 'No. Not really...', 12, 7, 100, 274, 0, 0, 0, '"Cookie" McWeaksauce'),
(17246, 4, 0, 'It be chicken...', 12, 7, 100, 1, 0, 0, 0, '"Cookie" McWeaksauce');
