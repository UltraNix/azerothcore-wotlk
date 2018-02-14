DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=17 AND `SourceEntry`=48290;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition`,`ErrorType`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(17,0,48290,0,0,31,1,3,27213,0,0,0,0,'','Only Onslaught Warhorse is a target for Onslaught Riding Crop'),
(17,0,48290,0,0,1,1,43671,0,0,1,0,0,'','Only NOT RIDDEN Onslaught Warhorse is a target for Onslaught Riding Crop');

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` IN (27213);
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES
(27213,43671,0,0);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=18 AND `SourceGroup`=27213 AND `SourceEntry` IN (43671);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(18,27213,43671,0,0,31,0,3,0,0,0,0,'','Only npcs can use Onslaught Warhorse spellclick');

DELETE FROM `vehicle_template_accessory` WHERE `entry`=27213;
INSERT INTO `vehicle_template_accessory` (`entry`,`accessory_entry`,`seat_id`,`minion`,`description`,`summontype`) VALUES
(27213,27206,0,0, 'Onslaught Warhorse - Onslaught Knight', 8);
