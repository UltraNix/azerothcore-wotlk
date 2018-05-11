DELETE FROM `creature_text` WHERE `entry` in(25317,25220,25222);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(25317, 0, 0, 'What''s the matter, $c?  Think you''re too good to stand in line with the rest of us?', 12, 0, 100, 0, 0, 0, 'Civilian Recruit to Player'),
(25220, 0, 0, 'Miner.', 12, 7, 100, 66, 0, 0, 'Civilian Recruit to Generic Quest Trigger - LAB'),
(25220, 0, 1, 'Farmhand, sir.', 12, 7, 100, 66, 0, 0,  'Civilian Recruit to Generic Quest Trigger - LAB'),
(25220, 0, 2, 'Tailor.', 12, 7, 100, 66, 0, 0,  'Civilian Recruit to Generic Quest Trigger - LAB'),
(25220, 0, 3, 'Blacksmith.', 12, 7, 100, 66, 0, 0,  'Civilian Recruit to Generic Quest Trigger - LAB'),
(25220, 0, 4, 'Carpenter.', 12, 7, 100, 66, 0, 0,  'Civilian Recruit to Generic Quest Trigger - LAB'),
(25220, 0, 5, 'Shipwright.', 12, 7, 100, 66, 0, 0, 'Civilian Recruit to Generic Quest Trigger - LAB'),
(25220, 0, 6, 'Mason, sir.', 12, 7, 100, 66, 0, 0,  'Civilian Recruit to Generic Quest Trigger - LAB'),
(25220, 0, 7, 'Cook.', 12, 7, 100, 66, 0, 0,  'Civilian Recruit to Generic Quest Trigger - LAB'),
(25222, 0, 0, 'What did you do before you came to Northrend, then?', 12, 7, 100, 0, 0, 0, 'Recruitment Officer Carven to Generic Quest Trigger - LAB'),
(25222, 0, 1, 'State your profession.', 12, 7, 100, 0, 0, 0,  'Recruitment Officer Carven to Generic Quest Trigger - LAB'),
(25222, 0, 2, 'Yes, then.  What is your trade?', 12, 7, 100, 0, 0, 0,  'Recruitment Officer Carven to Generic Quest Trigger - LAB'),
(25222, 0, 3, 'Your previous line of work, recruit?', 12, 7, 100, 0, 0, 0,  'Recruitment Officer Carven to Generic Quest Trigger - LAB'),
(25222, 0, 4, 'Your profession?', 12, 7, 100, 0, 0, 0,  'Recruitment Officer Carven to Generic Quest Trigger - LAB'),
(25222, 1, 0, 'Yes, you''re well seasoned in your field of work.  Report to the civilian liaison at once, we need more like you!', 12, 7, 100, 273, 0, 0, 'Recruitment Officer Carven to Generic Quest Trigger - LAB'),
(25222, 1, 1, 'I thought we had enough in your line of work, but it looks like we have some openings.  Report to the civilian liaison.', 12, 7, 100, 273, 0, 0,  'Recruitment Officer Carven to Generic Quest Trigger - LAB'),
(25222, 1, 2, 'I do have some openings in your line of work.  Report to the civilian liaison.', 12, 7, 100, 273, 0, 0,  'Recruitment Officer Carven to Generic Quest Trigger - LAB'),
(25222, 1, 3, 'Yeah.  We could use some more of you.  Report to the civilian liaison for work assignment.', 12, 7, 100, 273, 0, 0,  'Recruitment Officer Carven to Generic Quest Trigger - LAB'),
(25222, 2, 0, 'Not anymore!  Here''s your sword.  Report to the barracks for duty!', 12, 7, 100, 397, 0, 0,  'Recruitment Officer Carven to Generic Quest Trigger - LAB'),
(25222, 2, 1, 'Afraid not, friend.  Here''s your sword and shield.  Report to the barracks for duty.', 12, 7, 100, 397, 0, 0, 'Recruitment Officer Carven to Generic Quest Trigger - LAB'),
(25222, 2, 2, 'You''re breaking my heart - I''ve quotas to fill, you know?  Can you wield a sword?  Off to the barracks.', 12, 7, 100, 397, 0, 0,  'Recruitment Officer Carven to Generic Quest Trigger - LAB'),
(25222, 2, 3, 'With a sword arm like that?  I''m afraid we need you in the front lines, my friend.  Report to the barracks.', 12, 7, 100, 397, 0, 0,  'Recruitment Officer Carven to Generic Quest Trigger - LAB'),
(25222, 2, 4, 'Looks like we have room for one more... no, my mistake.  That''s a seven not a one.  Hope you''re good with a sword - report to the barracks.', 12, 7, 100, 397, 0, 0,  'Recruitment Officer Carven to Generic Quest Trigger - LAB'),
(25222, 3, 0, 'Next, please!', 12, 7, 100, 22, 0, 0,  'Recruitment Officer Carven to Generic Quest Trigger - LAB'),
(25222, 3, 1, 'Keep it moving, people.', 12, 7, 100, 22, 0, 0,  'Recruitment Officer Carven to Generic Quest Trigger - LAB'),
(25222, 3, 2, 'Next!', 12, 7, 100, 22, 0, 0,  'Recruitment Officer Carven to Generic Quest Trigger - LAB');

DELETE FROM `waypoints` WHERE `entry`=25220;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(25220, 1, 2253.644, 5195.469, 11.40062, 'Civilian Recruit'),
(25220, 2, 2254.098, 5196.36, 11.40062, 'Civilian Recruit'),
(25220, 3, 2277.823, 5238.724, 11.45096, 'Civilian Recruit'),
(25220, 4, 2279.217, 5241.407, 11.45096, 'Civilian Recruit'),
(25220, 5, 2280.84, 5244.218, 11.45719, 'Civilian Recruit'),
(25220, 6, 2282.603, 5245.736, 11.36353, 'Civilian Recruit'),
(25220, 7, 2284.867, 5246.299, 11.45096, 'Civilian Recruit'),
(25220, 8, 2287.469, 5245.929, 11.45096, 'Civilian Recruit'),
(25220, 9, 2289.469, 5244.898, 11.45096, 'Civilian Recruit'),
(25220, 10, 2291.772, 5243.933, 11.45096, 'Civilian Recruit'),
(25220, 11, 2294.129, 5242.708, 11.45096, 'Civilian Recruit'),
(25220, 12, 2296.873, 5241.782, 11.3919, 'Civilian Recruit'),
(25220, 13, 2303.019, 5253.306, 11.50584, 'Civilian Recruit'),
(25220, 14, 2308.73, 5256.926, 11.50584, 'Civilian Recruit'),
(25220, 15, 2320.826, 5259.258, 11.25584, 'Civilian Recruit');

DELETE FROM  `creature` WHERE `guid` IN(108008,108007,108006,108005,108004,108003,108002,108001,108000);

UPDATE `creature_template` SET `AIName`='SmartAI' WHERE  `entry`IN(24959,25220,25307);
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`IN(-107575,-107574);
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`IN(25220,25307);
DELETE FROM `smart_scripts` WHERE `source_type`=9 AND `entryorguid`IN(2522000,2522001);

INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(-107575, 0, 0, 0, 11, 0, 100, 0, 0, 0, 0, 0, 48, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Generic Quest Trigger - LAB - On Spawn - Set Active'),
(-107575, 0, 1, 0, 1, 0, 100, 0, 0, 0, 22000, 23000, 12, 25220, 8, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Generic Quest Trigger - LAB - OOC - Cast Borean Tundra - Valiance Keep Flavor - Summon Recruit'),
(-107574, 0, 1, 0, 1, 0, 100, 0, 0, 0, 22000, 23000, 11, 45307, 8, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Generic Quest Trigger - LAB - OOC - Cast Borean Tundra - Valiance Keep Flavor - Queue Global Ping'),
(25307, 0, 0, 0, 19, 0, 100, 0, 11672, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 19, 25317, 0, 0, 0, 0, 0, 0, 'Recruitment Officer Blythe - On Quest Accepted (Enlistment Day) - Say'),
(25220, 0, 0, 1, 54, 0, 100, 0, 0, 0, 0, 0, 48, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Civilian Recruit - On Just Summoned - Set Active'),
(25220, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 53, 0, 25220, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Civilian Recruit - On Just Summoned - Start WP'),
(25220, 0, 2, 0, 8, 0, 100, 0, 45313, 0, 0, 0, 54, 22000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Civilian Recruit - On Spellhit - Anchor Here - Pause WP'),
(25220, 0, 3, 0, 8, 0, 100, 0, 45307, 0, 0, 0, 65, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Civilian Recruit - On Spellhit - Borean Tundra - Valiance Keep Flavor - Queue Global Ping - Resume WP'),
(25220, 0, 4, 0, 40, 0, 100, 0, 3, 25220, 0, 0, 11, 45313, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Civilian Recruit - On Reached WP3 - Cast Anchor Here'),
(25220, 0, 5, 0, 40, 0, 100, 0, 4, 25220, 0, 0, 11, 45313, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Civilian Recruit - On Reached WP4 - Cast Anchor Here'),
(25220, 0, 6, 0, 40, 0, 100, 0, 5, 25220, 0, 0, 11, 45313, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Civilian Recruit - On Reached WP5 - Cast Anchor Here'),
(25220, 0, 7, 0, 40, 0, 100, 0, 6, 25220, 0, 0, 11, 45313, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Civilian Recruit - On Reached WP6 - Cast Anchor Here'),
(25220, 0, 8, 0, 40, 0, 100, 0, 7, 25220, 0, 0, 11, 45313, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Civilian Recruit - On Reached WP7 - Cast Anchor Here'),
(25220, 0, 9, 0, 40, 0, 100, 0, 8, 25220, 0, 0, 11, 45313, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Civilian Recruit - On Reached WP8 - Cast Anchor Here'),
(25220, 0, 10, 0, 40, 0, 100, 0, 9, 25220, 0, 0, 11, 45313, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Civilian Recruit - On Reached WP9 - Cast Anchor Here'),
(25220, 0, 11, 0, 40, 0, 100, 0, 10, 25220, 0, 0, 11, 45313, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Civilian Recruit - On Reached WP10 - Cast Anchor Here'),
(25220, 0, 12, 0, 40, 0, 100, 0, 11, 25220, 0, 0, 11, 45313, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Civilian Recruit - On Reached WP11 - Cast Anchor Here'),
(25220, 0, 13, 14, 40, 0, 100, 0, 12, 25220, 0, 0, 54, 18000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Civilian Recruit - On Reached WP11 - Cast Anchor Here'),
(25220, 0, 14, 0, 61, 0, 100, 0, 0, 0, 0, 0, 87, 2522000, 2522001, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Civilian Recruit - On Reached WP11 - Run Script'), 
(25220, 0, 15, 0, 40, 0, 100, 0, 15, 25220, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Civilian Recruit - On Reached WP15 - Despawn'),
(2522000, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 19, 25222, 0, 0, 0, 0, 0, 0, 'Civilian Recruit - Script 1 - Say'),
(2522000, 9, 1, 0, 0, 0, 100, 0, 7000, 7000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Civilian Recruit - Scrip 2 - Say'),
(2522000, 9, 2, 0, 0, 0, 100, 0, 6000, 7000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 19, 25222, 0, 0, 0, 0, 0, 0, 'Civilian Recruit - Script 2 - Say'),
(2522000, 9, 3, 0, 0, 0, 100, 0, 0, 0, 0, 0, 71, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Civilian Recruit - Script 2 - Equip Items'),
(2522000, 9, 4, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 65, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Civilian Recruit - Script 2 - Resume WP'),
(2522000, 9, 5, 0, 0, 0, 100, 0, 4000, 5000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 19, 25222, 0, 0, 0, 0, 0, 0, 'Civilian Recruit - Script 2 - Say'),
(2522001, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 19, 25222, 0, 0, 0, 0, 0, 0, 'Civilian Recruit - Script 1 - Say'),
(2522001, 9, 1, 0, 0, 0, 100, 0, 7000, 7000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Civilian Recruit - Scrip 2 - Say'),
(2522001, 9, 2, 0, 0, 0, 100, 0, 6000, 7000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 19, 25222, 0, 0, 0, 0, 0, 0, 'Civilian Recruit - Script 3 - Say'),
(2522001, 9, 3, 0, 0, 0, 100, 0, 0, 0, 0, 0, 71, 0, 0, 2178, 143, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Civilian Recruit - Script 3 - Equip Items'),
(2522001, 9, 4, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 65, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Civilian Recruit - Script 3 - Resume WP'),
(2522001, 9, 5, 0, 0, 0, 100, 0, 4000, 5000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 19, 25222, 0, 0, 0, 0, 0, 0, 'Civilian Recruit - Script 2 - Say');

DELETE FROM `creature` WHERE `id` = 25317;
INSERT INTO `creature` VALUES
(117784, 25317, 571,  1, 1, 24821, 1, 2286.79, 5241.67, 11.4799, 5.89921, 300, 0, 0, 6986, 0, 0, 0, 0, 0),
(117785, 25317, 571,  1, 1, 3422, 1, 2293.1, 5238.86, 11.4863, 5.91667, 300, 0, 0, 6986, 0, 0, 0, 0, 0),
(117788, 25317, 571,  1, 1, 3422, 1, 2114.61, 5284.78, 24.7267, 3.87463, 300, 0, 0, 6986, 0, 0, 0, 0, 0),
(117789, 25317, 571,  1, 1, 3422, 1, 2108.56, 5291.6, 25.297, 4.32842, 300, 0, 0, 6986, 0, 0, 0, 0, 0),
(117790, 25317, 571,  1, 1, 24819, 1, 2118.79, 5322.67, 25.3178, 1.36136, 300, 0, 0, 6986, 0, 0, 0, 0, 0),
(117794, 25317, 571,  1, 1, 3422, 1, 2126.98, 5322.85, 24.7275, 2.26893, 300, 0, 0, 6986, 0, 0, 0, 0, 0),
(117796, 25317, 571,  1, 1, 24818, 1, 2282.04, 5239.73, 11.4749, 0.925025, 300, 0, 0, 6986, 0, 0, 0, 0, 0),
(117797, 25317, 571,  1, 1, 3422, 1, 2283.03, 5241.48, 11.4633, 0.872665, 300, 0, 0, 6986, 0, 0, 0, 0, 0),
(117798, 25317, 571,  1, 1, 24821, 1, 2280.82, 5237.54, 11.4874, 0.959931, 300, 0, 0, 6986, 0, 0, 0, 0, 0),
(117799, 25317, 571,  1, 1, 24819, 1, 2284.84, 5242.58, 11.4615, 5.89921, 300, 0, 0, 6986, 0, 0, 0, 0, 0),
(117800, 25317, 571,  1, 1, 24819, 1, 2295.18, 5238.18, 11.4607, 5.89921, 300, 0, 0, 6986, 0, 0, 0, 0, 0),
(117801, 25317, 571,  1, 1, 24818, 1, 2291.11, 5239.73, 11.486, 5.91667, 300, 0, 0, 6986, 0, 0, 0, 0, 0),
(117802, 25317, 571,  1, 1, 24821, 1, 2288.84, 5240.71, 11.4855, 5.89921, 300, 0, 0, 6986, 0, 0, 0, 0, 0);
