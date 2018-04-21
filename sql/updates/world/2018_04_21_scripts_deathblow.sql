SET @CGUID = 302458;
SET @ADYEN = 18537;
SET @EXARCH = 19466;
SET @ANACHORETIN = 19467;
SET @SOCRETHAR = 20132;
SET @KAYLAN = 20794;
SET @SPELL_POWER_OF_LEGION = 35596;
SET @FACTION_NEW = 1775;
SET @FACTION_ORIGIN = 1743;

UPDATE `creature_template` SET `AIName` = "SmartAI", `flags_extra` = 0 WHERE `entry` IN (@ADYEN, @ANACHORETIN, @EXARCH, @KAYLAN);
UPDATE `creature_template` SET `unit_flags` = `unit_flags` | 768 WHERE `entry` = @SOCRETHAR;
UPDATE `creature_template_addon` SET `bytes1` = 0 WHERE `entry` = 19467;
DELETE FROM `creature_addon` WHERE `guid` = 69727;
INSERT INTO `creature_addon` VALUES
(69727, 0, 0, 6, 4097, 0, NULL);

DELETE FROM `creature` WHERE `guid` IN (@CGUID, @CGUID+1, @CGUID+2);
INSERT INTO `creature` VALUES
(@CGUID, @ADYEN, 530, 1, 1, 0, 0, 4807.84, 3769.87, 210.53, 5.78, 300, 0, 0, 0, 0, 0, 1, 0, 0),
(@CGUID+1, @EXARCH, 530, 1, 1, 0, 0, 4805.436, 3774.735, 210.53439, 5.78, 300, 0, 0, 0, 0, 0, 1, 0, 0),
(@CGUID+2, @ANACHORETIN, 530, 1, 1, 0, 0, 4802.133, 3771.975, 210.53456, 5.78, 300, 0, 0, 0, 0, 0, 1, 0, 0);

DELETE FROM `creature_formations` WHERE `leaderGUID` = @CGUID;
INSERT INTO `creature_formations` VALUES
(@CGUID, @CGUID, 0, 0, 2, 0, 0),
(@CGUID, @CGUID+1, 2, 145, 2, 0, 0),
(@CGUID, @CGUID+2, 2, 225, 2, 0, 0);

DELETE FROM `creature` WHERE `guid` IN (73436,73685, 73683, 73684);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@ADYEN, @ADYEN*100, @ADYEN*100+1, @ADYEN*100+2, @KAYLAN, @KAYLAN*100, @ANACHORETIN*100, @SOCRETHAR*100);
DELETE FROM `smart_scripts` WHERE `entryorguid` = @EXARCH AND `id` IN (1,2,3,4,5,6,7);
DELETE FROM `smart_scripts` WHERE `entryorguid` = @ANACHORETIN;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @SOCRETHAR AND `id` IN (5,6,7,8,9,10,11,12,13);
INSERT INTO `smart_scripts` VALUES
(@ADYEN, 0, 0, 5, 62, 0, 100, 0, 8117, 0, 0, 0, 80, @ADYEN*100, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Adyen - On Gossip Option - Run Script'),
(@ADYEN*100, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, @EXARCH, 10, 0, 0, 0, 0, 0, 'Adyen - Script - Set Data'),
(@ADYEN*100, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, @ANACHORETIN, 10, 0, 0, 0, 0, 0, 'Adyen - Script - Set Data'),
(@ADYEN*100, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 53, 0, @ADYEN, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Adyen - Script - Start WP'),
(@ADYEN*100, 9, 3, 0, 0, 0, 100, 0, 0, 0, 0, 0, 19, 512, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Adyen - Script - Remove flags'),
(@ADYEN*100, 9, 4, 0, 0, 0, 100, 0, 0, 0, 0, 0, 83, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Adyen - Script - Remove flags'),

(@ADYEN, 0, 1, 0, 40, 0, 100, 0, 32, @ADYEN, 0, 0, 80, @ADYEN*100+1, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Adyen - On WP Reached - Run Script'),
(@ADYEN*100+1, 9, 0, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 45, 1, 2, 0, 0, 0, 0, 19, @EXARCH, 10, 0, 0, 0, 0, 0, 'Adyen - Script - Set Data'),
(@ADYEN*100+1, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 1, 2, 0, 0, 0, 0, 19, @ANACHORETIN, 10, 0, 0, 0, 0, 0, 'Adyen - Script - Set Data'),
(@ADYEN*100+1, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 101, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Adyen - Script - Set Home Pos'),
(@ADYEN*100+1, 9, 3, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Adyen - Script - Talk'),
(@ADYEN*100+1, 9, 4, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 0, 0, 0, 0, 0, 0, 19, @SOCRETHAR, 30, 0, 0, 0, 0, 0, 'Adyen - Script - Talk'),
(@ADYEN*100+1, 9, 5, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Adyen - Script - Talk'),
(@ADYEN*100+1, 9, 6, 0, 0, 0, 100, 0, 0, 0, 0, 0, 12, @KAYLAN, 8, 0, 0, 0, 0, 8, 0, 0, 0, 4954.04, 3896.71, 211.86, 4.37, 'Adyen - Script - Summon Kaylan'),
(@ADYEN*100+1, 9, 7, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 19, @SOCRETHAR, 30, 0, 0, 0, 0, 0, 'Adyen - Script - Talk'),
(@ADYEN*100+1, 9, 8, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Adyen - Script - Talk'),

(@ADYEN, 0, 2, 0, 38, 0, 100, 0, 1, 1, 0, 0, 80, @ADYEN*100+2, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Adyen - On Data Set - Run Script'),
(@ADYEN*100+2, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 19, @KAYLAN, 30, 0, 0, 0, 0, 0, 'Adyen - Script - Talk'),
(@ADYEN*100+2, 9, 1, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 1, 0, 0, 0, 0, 0, 19, @KAYLAN, 30, 0, 0, 0, 0, 0, 'Adyen - Script - Talk'),
(@ADYEN*100+2, 9, 2, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 19, @KAYLAN, 30, 0, 0, 0, 0, 0, 'Adyen - Script - Talk'),
(@ADYEN*100+2, 9, 3, 0, 0, 0, 100, 0, 5000, 5000, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, @SOCRETHAR, 30, 0, 0, 0, 0, 0, 'Adyen - Script - Set Data'),
(@ADYEN*100+2, 9, 4, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 1, 2, 0, 0, 0, 0, 0, 19, @SOCRETHAR, 30, 0, 0, 0, 0, 0, 'Adyen - Script - Talk'),
(@ADYEN*100+2, 9, 5, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, @KAYLAN, 30, 0, 0, 0, 0, 0, 'Adyen - Script - Set Data'),
(@ADYEN*100+2, 9, 6, 0, 0, 0, 100, 0, 0, 0, 0, 0, 2, @FACTION_NEW, 0, 0, 0, 0, 0, 19, @ANACHORETIN, 20, 0, 0, 0, 0, 0, 'Adyen - Script - Faction'),
(@ADYEN*100+2, 9, 7, 0, 0, 0, 100, 0, 0, 0, 0, 0, 2, @FACTION_NEW, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Adyen - Script - Faction'),
(@ADYEN*100+2, 9, 8, 0, 0, 0, 100, 0, 0, 0, 0, 0, 2, @FACTION_NEW, 0, 0, 0, 0, 0, 19, @EXARCH, 20, 0, 0, 0, 0, 0, 'Adyen - Script - Faction'),
(@ADYEN, 0, 3, 0, 38, 0, 100, 0, 4, 4, 0, 0, 24, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Adyen - On Data Set - Evade'),
(@ADYEN, 0, 4, 0, 38, 0, 100, 0, 6, 6, 0, 0, 41, 0, 1000, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Adyen - On Data Set - Despawn'),
(@ADYEN, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 42, 10, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Adyen - Set Invinc Hp'),

(@EXARCH, 0, 1, 2, 38, 0, 100, 0, 1, 1, 0, 0, 29, 1, 145, 0, 0, 0, 0, 19, @ADYEN, 10, 0, 0, 0, 0, 0, 'Exarch - On Data Set - Follow Adyen'),
(@EXARCH, 0, 2, 7, 61, 0, 100, 0, 0, 0, 0, 0, 19, 512, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Exarch - On Data Set - Remove flags'),
(@EXARCH, 0, 3, 0, 38, 0, 100, 0, 1, 2, 0, 0, 101, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Exarch - On data set - Set home pos'),
(@EXARCH, 0, 4, 5, 38, 0, 100, 0, 4, 4, 0, 0, 24, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Exard - On data set - Evade'),
(@EXARCH, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0.66, 'Exard - On data set - set orientation'),
(@EXARCH, 0, 6, 0, 38, 0, 100, 0, 6, 6, 0, 0, 41, 1000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Exarch - On data set - despawn'),
(@EXARCH, 0, 7, 0, 61, 0, 100, 0, 0, 0, 0, 0, 42, 10, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Exarch - On data set - Set invinc hp'),
(@ANACHORETIN, 0, 0, 1, 38, 0, 100, 0, 1, 1, 0, 0, 29, 1, 225, 0, 0, 0, 0, 19, @ADYEN, 10, 0, 0, 0, 0, 0, 'Anachoretin - On data set - Follow Adyen'),
(@ANACHORETIN, 0, 1, 8, 61, 0, 100, 0, 0, 0, 0, 0, 19, 512, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Anachoretin - on data set - remove flags'),
(@ANACHORETIN, 0, 2, 0, 38, 0, 100, 0, 1, 2, 0, 0, 101, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Anachoretin - on data set - set home pos'),
(@ANACHORETIN, 0, 3, 4, 38, 0, 100, 0, 4, 4, 0, 0, 69, 3, 0, 0, 0, 0, 0, 8, 0, 0, 0, 4923.89, 3830.24, 211.49, 0.41, 'Anachoretin - on data set - move to pos'),
(@ANACHORETIN, 0, 4, 0, 61, 0, 100, 0, 0, 0, 0, 0, 80, @ANACHORETIN*100, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Anachoretin - on data set - start script'),
(@ANACHORETIN*100, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 0, 19, @SOCRETHAR, 30, 0, 0, 0, 0, 0, 'Anachoretin - Script - talk'),
(@ANACHORETIN*100, 9, 1, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 1, 4, 0, 0, 0, 0, 0, 19, @KAYLAN, 30, 0, 0, 0, 0, 0, 'Anachoretin - Script - talk'),
(@ANACHORETIN*100, 9, 2, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 69, 1, 0, 0, 0, 0, 0, 8, 0, 0, 0, 4939.80, 3829.05, 211.39, 0.83, 'Anachoretin - Script - move point'),
(@ANACHORETIN*100, 9, 3, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 69, 2, 0, 0, 0, 0, 0, 8, 0, 0, 0, 4945.55, 3839.69, 211.50, 1.51, 'Anachoretin - Script - move point'),
(@ANACHORETIN*100, 9, 4, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 1, 5, 0, 0, 0, 0, 0, 19, @KAYLAN, 30, 0, 0, 0, 0, 0, 'Anachoretin - Script - talk'),
(@ANACHORETIN*100, 9, 5, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 1, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Anachoretin - Script - talk'),
(@ANACHORETIN*100, 9, 6, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 1, 4, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Anachoretin - Script - talk'),
(@ANACHORETIN*100, 9, 7, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 1, 4, 0, 0, 0, 0, 0, 19, @SOCRETHAR, 30, 0, 0, 0, 0, 0, 'Anachoretin - Script - talk'),
(@ANACHORETIN*100, 9, 8, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 5, 463, 0, 0, 0, 0, 0, 19,  @SOCRETHAR, 30, 0, 0, 0, 0, 0, 'Anachoretin - Script - play emote'),
(@ANACHORETIN*100, 9, 10, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 29266, 7, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Anachoretin - Script - Die'),
(@ANACHORETIN*100, 9, 9, 0, 0, 0,  100, 0, 0, 0, 0, 0, 45, 3, 3, 0, 0, 0, 0, 19, @KAYLAN, 30, 0, 0, 0, 0, 0, 'Anachoretin - Script - Set data'),
(@ANACHORETIN, 0, 5, 0, 38, 0, 100, 0, 3, 3, 0, 0, 28, 29266, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Anachoretin - On data set - remove aura'),
(@ANACHORETIN, 0, 6, 0, 38, 0, 100, 0, 6, 6, 0, 0, 41, 1000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Anachoretin - On data set - despawn'),
(@ANACHORETIN, 0, 7, 0, 61, 0, 100, 0, 0, 0, 0, 0, 42, 10, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Anachoretin - lin - set invic hp'),

(@KAYLAN, 0, 0, 0, 54, 0, 100, 0, 0, 0, 0, 0, 53, 0, @KAYLAN, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Kaylan - On summoned - start WP'),
(@KAYLAN, 0, 1, 2, 40, 0, 100, 0, 8, 0, 0, 0, 5, 16, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Kaylan - WP Reached - play emote'),
(@KAYLAN, 0, 2, 3, 61, 0, 100, 0, 0, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 3.92, 'Kaylan - WP Reached - Set orientation'),
(@KAYLAN, 0, 3, 13, 61, 0, 100, 0, 0, 0, 0, 0, 101, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Kaylan - WP Reached - set home pos'),
(@KAYLAN, 0, 13, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, @ADYEN, 30, 0, 0, 0, 0, 0, 'Kaylan - WP Reached - set data'),
(@KAYLAN, 0, 4, 5, 38, 0, 100, 0, 1, 1, 0, 0, 2, 16, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Kaylan - on data set - mod faction'),
(@KAYLAN, 0, 5, 6, 61, 0, 100, 0, 0, 0, 0, 0, 42, 10, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Kaylan - on data set - set invic hp'),
(@KAYLAN, 0, 6, 0, 61, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 19, @ADYEN, 30, 0, 0, 0, 0, 0, 'Kaylan - on data set - attack start'),
(@KAYLAN, 0, 7, 8, 2,  0, 100, 0, 0, 15, 3000, 6000, 18, 768, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Kaylan - on hp level - set flags'),
(@KAYLAN, 0, 8, 9, 61,  0, 100, 0, 0, 0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Kaylan - on hp level - evade'),
(@KAYLAN, 0, 9, 10, 61,  0, 100, 0, 0, 0, 0, 0, 45, 4, 4, 0, 0, 0, 0, 19, @ADYEN, 30, 0, 0, 0, 0, 0, 'Kaylan - on hp level - set data'),
(@KAYLAN, 0, 10, 11, 61,  0, 100, 0, 0, 0, 0, 0, 45, 4, 4, 0, 0, 0, 0, 19, @EXARCH, 30, 0, 0, 0, 0, 0, 'Kaylan - on hp level - set data'),
(@KAYLAN, 0, 11, 0, 61, 0, 100, 0, 0, 0, 0, 0, 45, 4, 4, 0, 0, 0, 0, 19, @ANACHORETIN, 30, 0, 0, 0, 0, 0, 'Kaylan - on hp level - set data'),
(@KAYLAN, 0, 12, 0, 38, 0, 100, 0, 3, 3, 0, 0, 80, @KAYLAN*100, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Kaylan - on data set - start script'),
(@KAYLAN, 0, 14, 0, 38, 0, 100, 0, 6, 6, 0, 0, 41, 1000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Kaylan - on data set - despawn'),

(@KAYLAN*100, 9, 0, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 1, 6, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Kaylan - On Script - Say'),
(@KAYLAN*100, 9, 1, 0, 0, 0, 100, 0, 2000, 2000, 0, 0, 28, @SPELL_POWER_OF_LEGION, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Kaylan - On Script - Remove Aura'),
(@KAYLAN*100, 9, 2, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 69, 1, 0, 0, 0, 0, 0, 8, 0, 0, 0, 4942.90, 3840.38, 211.50, 5.10, 'Kaylan - On Script - Move to pos'),
(@KAYLAN*100, 9, 3, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 1, 7, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Kaylan - On Script -  Say'),
(@KAYLAN*100, 9, 4, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 2, @FACTION_ORIGIN, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Kaylan - On Script - Restore faction'),
(@KAYLAN*100, 9, 5, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 11, 13874, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Kaylan - On Script - Cast Divine shield'),
(@KAYLAN*100, 9, 6, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 11, 35599, 0, 0, 0, 0, 0, 19, @ANACHORETIN, 30, 0, 0, 0, 0, 0, 'Kaylan - On Script - Cast Resurec'),
(@KAYLAN*100, 9, 7, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 45, 3, 3, 0, 0, 0, 0, 19, @ANACHORETIN, 30, 0, 0, 0, 0, 0, 'Kaylan - On Script - Set data'),
(@KAYLAN*100, 9, 8, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 45, 3, 3, 0, 0, 0, 0, 19, @SOCRETHAR, 30, 0, 0, 0, 0, 0, 'Kaylan - On Script - set data'),
(@KAYLAN*100, 9, 9, 0, 0, 0, 100, 0, 0, 0, 0, 0, 19, 512, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Kaylan - On Script - remove flags'),
(@KAYLAN*100, 9, 10, 0, 0, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 19, @SOCRETHAR, 30, 0, 0, 0, 0, 0, 'Kaylan - On Script - Attack start'),

(@SOCRETHAR, 0, 5, 0, 38, 0, 100, 0, 1, 1, 0, 0, 11, @SPELL_POWER_OF_LEGION, 0, 0, 0, 0, 0, 19, @KAYLAN, 30, 0, 0, 0, 0, 0, 'Socrethar - On data set - Cast power of legion'),
(@SOCRETHAR, 0, 6, 0, 38, 0, 100, 0, 3, 3, 0, 0, 80, @SOCRETHAR*100, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Socrethar - on data set - run script'),
(@SOCRETHAR*100, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 19, 768, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Socrethar - Script - Remove flags'),
(@SOCRETHAR*100, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 49, 0, 0, 0, 0, 0, 0, 19, @ADYEN, 30, 0, 0, 0, 0, 0, 'Socrethar - Script - Attack Adyen'),
(@SOCRETHAR, 0, 7, 8, 6, 0, 100, 0, 0, 0, 0, 0, 33, @SOCRETHAR, 0, 0, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 'Socrethar - On Death - Quest Credit'),
(@SOCRETHAR, 0, 8, 9, 61, 0, 100, 0, 0, 0, 0, 0, 45, 6, 6, 0, 0, 0, 0, 19, @ADYEN, 30, 0, 0, 0, 0, 0, 'Socrethar - on death - set data'),
(@SOCRETHAR, 0, 9, 10, 61, 0, 100, 0, 0, 0, 0, 0, 45, 6, 6, 0, 0, 0, 0, 19, @ANACHORETIN, 30, 0, 0, 0, 0, 0, 'Socrethar - on death- set data'),
(@SOCRETHAR, 0, 10, 11, 61, 0, 100, 0, 0, 0, 0, 0, 45, 6, 6, 0, 0, 0, 0, 19, @EXARCH, 30, 0, 0, 0, 0, 0, 'Socrethar - on death- set data'),
(@SOCRETHAR, 0, 11, 12, 61, 0, 100, 0, 0, 0, 0, 0, 45, 6, 6, 0, 0, 0, 0, 19, @KAYLAN, 30, 0, 0, 0, 0, 0, 'Socrethar - on death- set data'),
(@SOCRETHAR, 0, 12, 0, 61, 0, 100, 0, 0, 0, 0, 0, 12, 18538, 4, 20000, 0, 0, 0, 8, 0, 0, 0, 4938.65, 3827.24, 211.35, 1.54, 'Socrethar - on death - Summon questender');

DELETE FROM `gossip_menu_option` WHERE `menu_id` = 8117;
INSERT INTO `gossip_menu_option` VALUES
(8117, 0, 0, 'I\'m ready, Adyen.', 1, 1, 0, 0, 0, 0, '');

DELETE FROM `waypoints` WHERE `entry` IN (@ADYEN, @KAYLAN);
INSERT INTO `waypoints` VALUES
(@ADYEN, 1, 4811.175, 3768.585, 210.53613, ''),
(@ADYEN, 2, 4815.609, 3768.435, 210.53462, ''),
(@ADYEN, 3, 4820.966, 3768.678, 210.35030, ''),
(@ADYEN, 4, 4827.773, 3770.291, 209.37112, ''),
(@ADYEN, 5, 4830.862, 3771.247, 208.77676, ''),
(@ADYEN, 6, 4834.206, 3772.281, 208.14052, ''),
(@ADYEN, 7, 4840.188, 3774.295, 207.05385, ''),
(@ADYEN, 8, 4844.815, 3776.524, 205.88878, ''),
(@ADYEN, 9, 4849.446, 3779.222, 203.92104, ''),
(@ADYEN, 10, 4853.118, 3781.712, 202.20966, ''),
(@ADYEN, 11, 4856.723, 3785.028, 200.74072, ''),
(@ADYEN, 12, 4859.720, 3788.597, 199.91502, ''),
(@ADYEN, 13, 4862.702, 3793.052, 199.34169, ''),
(@ADYEN, 14, 4865.335, 3797.181, 199.11320, ''),
(@ADYEN, 15, 4868.755, 3800.667, 198.99863, ''),
(@ADYEN, 16, 4872.782, 3802.529, 198.97151, ''),
(@ADYEN, 17, 4878.320, 3805.528, 198.97151, ''),
(@ADYEN, 18, 4884.076, 3808.629, 198.97151, ''),
(@ADYEN, 19, 4887.565, 3810.484, 200.33882, ''),
(@ADYEN, 20, 4889.630, 3811.581, 202.29007, ''),
(@ADYEN, 21, 4891.847, 3812.865, 203.82068, ''),
(@ADYEN, 22, 4895.633, 3815.153, 206.26067, ''),
(@ADYEN, 23, 4898.434, 3816.852, 208.06783, ''),
(@ADYEN, 24, 4901.606, 3818.803, 209.32941, ''),
(@ADYEN, 25, 4904.154, 3820.458, 210.29524, ''),
(@ADYEN, 26, 4906.877, 3822.253, 211.33192, ''),
(@ADYEN, 27, 4908.615, 3823.408, 211.48836, ''),
(@ADYEN, 28, 4912.311, 3825.865, 211.48836, ''),
(@ADYEN, 29, 4915.412, 3827.927, 211.51134, ''),
(@ADYEN, 30, 4918.909, 3830.252, 211.51001, ''),
(@ADYEN, 31, 4922.208, 3832.446, 211.50261, ''),
(@ADYEN, 32, 4924.796, 3834.038, 211.49635, ''),
(@KAYLAN, 1, 4952.173, 3892.548, 212.03270, ''),
(@KAYLAN, 2, 4950.742, 3888.600, 212.26793, ''),
(@KAYLAN, 3, 4947.327, 3878.907, 211.90157, ''),
(@KAYLAN, 4, 4943.760, 3871.056, 211.49380, ''),
(@KAYLAN, 5, 4940.155, 3862.214, 211.62221, ''),
(@KAYLAN, 6, 4936.038, 3852.307, 211.52544, ''),
(@KAYLAN, 7, 4939.792, 3849.567, 211.48964, ''),
(@KAYLAN, 8, 4940.077, 3846.815, 211.50746, '');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceEntry` = @EXARCH;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 15 AND `SourceGroup` = 8117;
INSERT INTO `conditions` VALUES
(22, 1, @EXARCH, 0, 0, 4, 0, 3523, 0, 0, 1, 0, 0, '', 'Run sai if not in Netherstorm'),
(15, 8117, 0, 0, 0, 9, 0, 10409, 0, 0, 0, 0, 0, '', 'Show gossip if on quest');

UPDATE `creature_template` SET `flags_extra` = `flags_extra` | 2097152 WHERE `entry` = 20132;

UPDATE `quest_template` SET `Flags` = 130, `SpecialFlags` = 0 WHERE `id` = 10409;
DELETE FROM `creature_text` WHERE `entry` IN (@ADYEN, @SOCRETHAR, @KAYLAN);
DELETE FROM `creature_text` WHERE `entry` = @ANACHORETIN AND `groupid` IN (3,4);
INSERT INTO `creature_text` VALUES
(@ADYEN, 0, 0, 'We\'re here for you, lost brother. It is custom to offer you a chance to repent before you are destroyed. We offer you this chance, as the naaru\'s law commands.', 12, 0, 100, 0, 0, 0, 0, ''),
(@ADYEN, 1, 0, 'We may be few, Socrethar, but our faith is strong. Something you will never understand. Now that custom has been served, prepare to meet your end.', 12, 0, 100, 0, 0, 0, 0, ''),
(@ADYEN, 2, 0, 'How... how could you?!', 12, 0, 100, 0, 0, 0, 0, ''),
(@ADYEN, 3, 0, 'Socrethar is clouding your mind, Kaylaan! You do not mean these words! I remember training you when you were but a youngling. Your will was strong even then!', 12, 0, 100, 0, 0, 0, 0, ''),

(@KAYLAN, 0, 0, 'My heart has been filled with hate since our sworn enemies were allowed into our city. I knew the one known as Voren\'thal before he was called a Seer. It was by his hand that my brother was slain.', 12, 0, 100, 0, 0, 0, 0, ''),
(@KAYLAN, 1, 0, 'I turned that hate on the Illidari and the Burning Legion... but they weren\'t the ones who betrayed us. We were the naaru\'s chosen! We lived and died for them!', 12, 0, 100, 0, 0, 0, 0, ''),
(@KAYLAN, 2, 0, 'Once the hatred in my heart became focused, everything became clear to me. Shattrath must be destroyed and the naaru with it.', 12, 0, 100, 0, 0, 0, 0, ''),
(@KAYLAN, 3, 0, 'You are wrong, Adyen. My mind has never been clearer.', 12, 0, 100, 0, 0, 0, 0, ''),
(@KAYLAN, 4, 0, 'Yes... master.', 12, 0, 100, 0, 0, 0, 0, ''),
(@KAYLAN, 5, 0, 'Teacher...', 12, 0, 100, 0, 0, 0, 0, ''),
(@KAYLAN, 6, 0, 'No! What have I done?', 12, 0, 100, 0, 0, 0, 0, ''),
(@KAYLAN, 7, 0, 'Light grant me strength!', 14, 0, 100, 0, 0, 0, 0, ''),

(@SOCRETHAR, 0, 0, 'Do not make me laugh. Is this the mighty Aldor army that\'s come to defeat me?', 14, 0, 100, 11, 0, 0, 0, ''),
(@SOCRETHAR, 1, 0, 'Yes, let us settle this. Before we begin, however, there\'s somebody I\'d like you to meet.', 14, 0, 100, 1, 0, 0, 0, ''),
(@SOCRETHAR, 2, 0, 'Slay these dogs, Kaylaan! Earn your place in the Burning Legion!', 14, 0, 100, 25, 0, 0, 0, ''),
(@SOCRETHAR, 3, 0, 'What are you waiting for? Finish them, young one. Let your hatred burn!', 14, 0, 100, 0, 0, 0, 0, ''),
(@SOCRETHAR, 4, 0, 'You foolish old hag... Why would I do that when I can have you both?', 14, 0, 100, 0, 0, 0, 0, ''),
(@SOCRETHAR, 5, 0, 'Oh, please! This is sickening; I\'m going to have to kill you all myself.', 14, 0, 100, 0, 0, 0, 0, ''),

(@ANACHORETIN, 3, 0, 'The Light wants its lost son back, Socrethar.', 12, 0, 100, 0, 0, 0, 0, ''),
(@ANACHORETIN, 4, 0, 'I offer myself in exchange. You will have Ishanah, the High Priestess of the Aldor, as your prisoner if you release Kaylaan from your dark grasp.', 12, 0, 100, 0, 0, 0, 0, '');

