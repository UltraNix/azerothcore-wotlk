UPDATE `creature_template` SET `ScriptName` = "npc_rejek_sholazar_event" WHERE `entry` = 29043;

DELETE FROM `conditions` WHERE `sourceEntry` = 53170;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13, 1, 53170, 0, 0, 31, 0, 3, 29043, 0, 0, 0, 0, '', 'Ride rejek requires rejek nearby');


DELETE FROM `creature_text` WHERE `entry` IN (29043, 28139);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `TextRange`, `comment`) VALUES
(29043, 0, 0, "Who wants to see Rejek's new helmet?", 12, 0, 100, 113, 0, 0, 0, 'Rejek'),
(29043, 1, 0, "Ok, Rejek show!", 12, 0, 100, 0, 0, 0, 0, 'Rejek'),
(29043, 2, 0, "What you think?", 12, 0, 100, 0, 0, 0, 0, 'Rejek'),

(28139, 0, 0, "I wanna see!", 12, 0, 100, 0, 0, 0, 0, "frenzyheart pup"),
(28139, 1, 0, "Show me too!", 12, 0, 100, 0, 0, 0, 0, "frenzyheart pup 2"),
(28139, 2, 0, "Metalhead ate Rejek! Run!", 12, 0, 100, 0, 0, 0, 0, "frenzyheart pup 2");
