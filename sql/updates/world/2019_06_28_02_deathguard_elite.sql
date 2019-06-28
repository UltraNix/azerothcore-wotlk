DELETE FROM `smart_scripts` WHERE `entryorguid` = 7980 AND `source_type` = 0;
INSERT INTO `smart_scripts` VALUES 
(7980,0,0,0,0,0,100,0,0,0,2000,4000,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,'Deathguard Elite - In Combat - Cast \'Shoot\''),
(7980,0,1,0,25,0,100,0,0,0,0,0,11,18950,0,0,0,0,0,1,0,0,0,0,0,0,0,'Deathguard Elite - On Reset - Cast \'Invisibility and Stealth Detection\''),
(7980,0,2,0,0,0,100,0,5000,7000,7000,10000,11,14516,0,0,0,0,0,2,0,0,0,0,0,0,0,'Deathguard Elite - In Combat - Cast \'Strike\''),
(7980,0,3,0,9,0,100,0,0,5,12000,16000,11,9080,0,0,0,0,0,2,0,0,0,0,0,0,0,'Deathguard Elite - Within 0-5 Range - Cast \'Hamstring\''),
(7980,0,4,0,22,0,100,0,101,5000,5000,0,80,6800,0,0,0,0,0,1,0,0,0,0,0,0,0,'Deathguard Elite - On Received Emote \'Wave\' - Run Script'),
(7980,0,5,0,22,0,100,0,78,5000,5000,0,80,6801,0,0,0,0,0,1,0,0,0,0,0,0,0,'Deathguard Elite - On Received Emote \'Salute\' - Run Script'),
(7980,0,6,0,22,0,100,0,58,5000,5000,0,80,6802,0,0,0,0,0,1,0,0,0,0,0,0,0,'Deathguard Elite - On Received Emote \'Kiss\' - Run Script'),
(7980,0,7,0,22,0,100,0,84,5000,5000,0,80,6803,0,0,0,0,0,1,0,0,0,0,0,0,0,'Deathguard Elite - On Received Emote \'Shy\' - Run Script'),
(7980,0,8,0,22,0,100,0,77,5000,5000,0,80,6804,0,0,0,0,0,1,0,0,0,0,0,0,0,'Deathguard Elite - On Received Emote \'Rude\' - Run Script'),
(7980,0,9,0,22,0,100,0,22,5000,5000,0,80,6804,0,0,0,0,0,1,0,0,0,0,0,0,0,'Deathguard Elite - On Received Emote \'Chicken\' - Run Script'),
(7980,0,10,0,22,0,100,0,17,5000,5000,0,80,6802,0,0,0,0,0,1,0,0,0,0,0,0,0,'Deathguard Elite - On Received Emote \'Bow\' - Run Script');

UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 7980;
