DELETE FROM `smart_scripts` WHERE `entryorguid` = 14304 AND `source_type` = 0;
INSERT INTO `smart_scripts` VALUES 
(14304,0,0,0,10,0,100,512,1,10,10000,10000,87,6800,6801,6802,6803,0,0,1,0,0,0,0,0,0,0,'Kor\'\'kron Elite - Within 1-10 Range Out of Combat LoS - Run Random Script'),
(14304,0,1,0,0,0,100,0,0,0,2000,4000,11,6660,64,0,0,0,0,2,0,0,0,0,0,0,0,'Kor\'kron Elite - In Combat - Cast \'Shoot\''),
(14304,0,2,0,0,0,100,0,5000,9000,8000,13000,11,40505,0,0,0,0,0,2,0,0,0,0,0,0,0,'Kor\'kron Elite - In Combat - Cast \'Cleave\''),
(14304,0,3,0,2,0,100,0,0,30,120000,120000,11,8599,0,0,0,0,0,1,0,0,0,0,0,0,0,'Kor\'kron Elite - Between 0-30% Health - Cast \'Enrage\''),
(14304,0,4,0,2,0,100,1,0,30,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Kor\'kron Elite - Between 0-30% Health - Say Line 1 (No Repeat)'),
(14304,0,5,0,22,0,100,0,101,5000,5000,0,80,6800,0,0,0,0,0,1,0,0,0,0,0,0,0,'Kor\'kron Elite - On Received Emote \'Wave\' - Run Script'),
(14304,0,6,0,22,0,100,0,78,5000,5000,0,80,6801,0,0,0,0,0,1,0,0,0,0,0,0,0,'Kor\'kron Elite - On Received Emote \'Salute\' - Run Script'),
(14304,0,7,0,22,0,100,0,58,5000,5000,0,80,6802,0,0,0,0,0,1,0,0,0,0,0,0,0,'Kor\'kron Elite - On Received Emote \'Kiss\' - Run Script'),
(14304,0,8,0,22,0,100,0,84,5000,5000,0,80,6803,0,0,0,0,0,1,0,0,0,0,0,0,0,'Kor\'kron Elite - On Received Emote \'Shy\' - Run Script'),
(14304,0,9,0,22,0,100,0,77,5000,5000,0,80,6804,0,0,0,0,0,1,0,0,0,0,0,0,0,'Kor\'kron Elite - On Received Emote \'Rude\' - Run Script'),
(14304,0,10,0,22,0,100,0,22,5000,5000,0,80,6804,0,0,0,0,0,1,0,0,0,0,0,0,0,'Kor\'kron Elite - On Received Emote \'Chicken\' - Run Script'),
(14304,0,11,0,22,0,100,0,17,5000,5000,0,80,6802,0,0,0,0,0,1,0,0,0,0,0,0,0,'Kor\'kron Elite - On Received Emote \'Bow\' - Run Script');

UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 14304;
