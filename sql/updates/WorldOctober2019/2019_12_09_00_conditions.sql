DELETE FROM `conditions` WHERE `SourceEntry`=45942 AND `SourceTypeOrReferenceId`=17;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(17, 0, 45942, 0, 0, 29, 0, 25829, 100, 0, 1, 0, 0, "", "Spell 'Summon Alluvius' cannot be cast if NPC 'Lord Kryxix' is nearby"),
(17, 0, 45942, 0, 0, 36, 0, 0, 0, 0, 0, 0, 0, "", "Spell 'Summon Alluvius' cannot be cast if nearby NPC 'Lord Kryxix' is alive"),
(17, 0, 45942, 0, 0, 29, 0, 25742, 100, 0, 1, 0, 0, "", "Spell 'Summon Alluvius' cannot be cast if NPC 'Alluvius' is nearby");