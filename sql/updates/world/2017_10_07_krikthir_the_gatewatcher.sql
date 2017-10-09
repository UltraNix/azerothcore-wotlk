DELETE FROM `creature_summon_groups` WHERE `summonerId`=28684 AND `summonerType`=0;
INSERT INTO `creature_summon_groups` (`summonerId`,`summonerType`,`groupId`,`entry`,`position_x`,`position_y`,`position_z`,`orientation`,`summonType`,`summonTime`) VALUES
(28684,0,1,28729,511.8097,666.4934,776.2781,0.9773844,6,45000),
(28684,0,1,28732,506.5164,664.3796,776.9759,0.9250245,6,30000),
(28684,0,1,28733,506.1783,669.9266,776.3057,0.8552113,6,30000),
(28684,0,2,28730,526.6636,663.6053,775.8052,1.239184 ,6,45000),
(28684,0,2,28732,531.0308,658.1731,776.2396,1.343904 ,6,30000),
(28684,0,2,28734,521.8148,659.4708,776.3131,1.186824 ,6,30000),
(28684,0,3,28731,543.8261,665.1234,776.2453,1.553343 ,6,45000),
(28684,0,3,28734,550.0461,668.131 ,776.2789,1.658063 ,6,30000),
(28684,0,3,28733,549.6929,662.0067,776.9927,1.64061  ,6,30000);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry` IN (52438,52449,52343);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition`,`Comment`) VALUES
(13,1,52438,0,0,31,0,3,22515,0,0,"Summon Skittering Swarmer - Target World Trigger"),
(13,1,52449,0,0,31,0,3,22515,0,0,"Summon Skittering Infector - Target World Trigger"),
(13,1,52343,0,0,31,0,3,28729,0,0,"Krik'thir Subboss Aggro Trigger - Target Watcher Narjil"),
(13,1,52343,0,1,31,0,3,28730,0,0,"Krik'thir Subboss Aggro Trigger - Target Watcher Garsha"),
(13,1,52343,0,2,31,0,3,28731,0,0,"Krik'thir Subboss Aggro Trigger - Target Watcher Silthik");

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (28735, 28736, 28730, 28729, 28731, 28732, 28734, 28733) AND `source_type`=0;

UPDATE `creature_template` SET `AIName`="",`ScriptName`="npc_skittering_swarmer" WHERE `entry`=28735;
UPDATE `creature_template` SET `AIName`="",`ScriptName`="npc_skittering_infector" WHERE `entry`=28736;

UPDATE `creature_template` SET `AIName`="",`ScriptName`="npc_watcher_gashra" WHERE `entry`=28730;
UPDATE `creature_template` SET `AIName`="",`ScriptName`="npc_watcher_narjil" WHERE `entry`=28729;
UPDATE `creature_template` SET `AIName`="",`ScriptName`="npc_watcher_silthik" WHERE `entry`=28731;

UPDATE `creature_template` SET `AIName`="",`ScriptName`="npc_anub_ar_warrior" WHERE `entry`=28732;
UPDATE `creature_template` SET `AIName`="",`ScriptName`="npc_anub_ar_skirmisher" WHERE `entry`=28734;
UPDATE `creature_template` SET `AIName`="",`ScriptName`="npc_anub_ar_shadowcaster" WHERE `entry`=28733;

DELETE FROM `spell_script_names` WHERE `scriptname` = "spell_gatewatcher_subboss_trigger";
INSERT INTO `spell_script_names` (`spell_id`,`scriptname`) VALUES 
(52343,"spell_gatewatcher_subboss_trigger");

DELETE FROM `spell_script_names` WHERE `scriptname` = "spell_anub_ar_skirmisher_fixtate";
INSERT INTO `spell_script_names` (`spell_id`,`scriptname`) VALUES 
(52536,"spell_anub_ar_skirmisher_fixtate");

DELETE FROM `spell_script_names` WHERE `scriptname` = "spell_gatewatcher_web_wrap";
INSERT INTO `spell_script_names` (`spell_id`,`scriptname`) VALUES 
(52086,"spell_gatewatcher_web_wrap");
UPDATE `creature_template` SET `AIName`='',`ScriptName`="npc_gatewatcher_web_wrap" WHERE `entry`=28619;
