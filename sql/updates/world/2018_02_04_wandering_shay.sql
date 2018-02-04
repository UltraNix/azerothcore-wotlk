DELETE FROM `smart_scripts` WHERE `entryorguid` = 7774;
UPDATE `creature_template` SET `AIName` = "", `ScriptName` = "npc_shay_wanderer" WHERE `entry` = 7774;

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry`=11402;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(13, 1, 11402, 0, 0, 31, 0, 3, 7774, 0, 0, 0, 0, '', 'Shays Bell targets Shay Leafrunner');

DELETE FROM `creature_text` WHERE `entry`IN(7774,7765);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `TextRange`, `comment`) VALUES 
(7774, 0, 0, 'Don''t forget to get my bell out of the chest here. And remember, if do happen to wander off, just ring it and i''ll find you again.', 12, 0, 100, 0, 0, 0, 0, 'Shay Leafrunner'),
(7774, 1, 0, 'This is quite an adventure!', 12, 0, 100, 0, 0, 0, 0, 'Shay Leafrunner'),
(7774, 1, 1, 'Oh, I wandered off again. I''m sorry.', 12, 0, 100, 0, 0, 0, 0, 'Shay Leafrunner'),
(7774, 1, 2, 'The bell again, such a sweet sound.', 12, 0, 100, 0, 0, 0, 0, 'Shay Leafrunner'),
(7774, 1, 3, 'I can''t help it, really. This is just such a beautiful place.', 12, 0, 100, 0, 0, 0, 0, 'Shay Leafrunner'),
(7774, 2, 0, '%s begins to wander off.', 16, 0, 100, 0, 0, 0, 0, 'Shay Leafrunner'),
(7774, 3, 0, 'Are we taking the scenic route?', 12, 0, 100, 0, 0, 0, 0, 'Shay Leafrunner'),
(7774, 3, 1, 'Oh, what a beautiful flower over there.', 12, 0, 100, 0, 0, 0, 0, 'Shay Leafrunner'),
(7774, 3, 2, 'These trees are quite glorious, aren''t they? ', 12, 0, 100, 0, 0, 0, 0, 'Shay Leafrunner'),
(7774, 3, 3, 'Are you sure this is the right way? Maybe we should go this way instead...', 12, 0, 100, 0, 0, 0, 0, 'Shay Leafrunner'),
(7774, 4, 0, 'Oh, here you are, Rockbiter! I''m sorry, I know I''m not supposed to wander off.', 12, 0, 100, 0, 0, 0, 0, 'Shay Leafrunner'),
(7765, 0, 0, 'I''m glad yer back, Shay. Please, don''t ever run off like that again! What would i tell yer parents if I lost ya?"', 12, 0, 100, 0, 0, 0, 0, 'Shay Leafrunner');
