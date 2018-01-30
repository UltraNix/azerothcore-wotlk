UPDATE `trinity_string` SET `content_default` =  '|cFFFFD700[|cffff9933SUNWELL|cFFFFD700] |cFFFFD700%s' WHERE `trinity_string`.`entry` = 3;
UPDATE `trinity_string` SET `content_default` =  '|cFFFFD700[|cffff9933Event Message|cFFFFD700]: |cffff9933%s|r' WHERE `trinity_string`.`entry` = 4;
UPDATE `trinity_string` SET `content_default` =  '|cFFFFD700Connected players: |cffff9933%u |cFFFFD700Characters in world: |cffff9933%u|r' WHERE `trinity_string`.`entry` = 12;
UPDATE `trinity_string` SET `content_default` =  '|cFFFFD700Server uptime: |cffff9933%s|r' WHERE `trinity_string`.`entry` = 13;
UPDATE `trinity_string` SET `content_default` =  '|cFFFFD700Update time diff: |cffff9933%ums |cFFFFD700average: |cffff9933%ums|r' WHERE `trinity_string`.`entry` = 19;
UPDATE `trinity_string` SET `content_default` =  '|cFFFFD700List of commands:|r' WHERE `trinity_string`.`entry` = 69;
UPDATE `trinity_string` SET `content_default` =  '|cffff9933.info|cFFFFD700 - shows you the information about the server.|r' WHERE `trinity_string`.`entry` = 70;
UPDATE `trinity_string` SET `content_default` =  '|cffff9933.premium|cFFFFD700 - displays the status of your Premium Privileges.|r' WHERE `trinity_string`.`entry` = 71;
UPDATE `trinity_string` SET `content_default` =  '|cffff9933.pvpinfo|cFFFFD700 - toggles the visibility of PvP related announcements.|r' WHERE `trinity_string`.`entry` = 72;
UPDATE `trinity_string` SET `content_default` =  '|cffff9933.blizzlike|cFFFFD700 - toggles x1 experience rate.|r' WHERE `trinity_string`.`entry` = 73;
UPDATE `trinity_string` SET `content_default` =  '|cffff9933.dodge|cFFFFD700 - hides your location at /who (requires |cffff99332000 |cFFFFD700Arena Rating).|r' WHERE `trinity_string`.`entry` = 74;
UPDATE `trinity_string` SET `content_default` =  '|cFFFFD700Server time: |cffff9933%s|r' WHERE `trinity_string`.`entry` = 63;
UPDATE `trinity_string` SET `content_default` =  '|cFFFFD700Connected players: |cffff9933%u |cFFFFD700Characters in world: |cffff9933%u |cFFFFD700Queue: |cffff9933%u|r' WHERE `trinity_string`.`entry` = 60;
UPDATE `trinity_string` SET `content_default` =  '|cFFFFD700Sunwell.pl (|cffff9933%s|cFFFFD700) - Rev: |cffff9933%u|cFFFFD700 (|cffff9933%s|cFFFFD700)|r' WHERE `trinity_string`.`entry` = 65;
UPDATE `trinity_string` SET `content_default` =  '|cFFFFD700Sunwell.pl (|cffff9933%s|cFFFFD700) - Rev: |cffff9933%s' WHERE `trinity_string`.`entry` = 64;
UPDATE `trinity_string` SET `content_default` =  '|cFFFFD700DEV wavg: |cffff9933%ums|cFFFFD700 nsmax: |cffff9933%ums|cFFFFD700 nsavg: |cffff9933%ums |cFFFFD700LFG avg: |cffff9933%ums|cFFFFD700 max: |cffff9933%ums|cFFFFD700|r' WHERE `trinity_string`.`entry` = 66;
UPDATE `trinity_string` SET `content_default` =  '|cFFFFD700[|cffff9933WARNING|cFFFFD700] Server will |cffff9933%s|cFFFFD700 in: |cffff9933%s|r' WHERE `trinity_string`.`entry` = 67;
UPDATE `trinity_string` SET `content_default` =  '|cFFFFD700Reason: |cffff9933%s|cFFFFD700.|r' WHERE `trinity_string`.`entry` = 68;
UPDATE `trinity_string` SET `content_default` =  '|cFFFFD700Current Message of the day: |cffff9933%s.|r' WHERE `trinity_string`.`entry` = 56;

REPLACE INTO `trinity_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES 
('11002', '|cFFFFD700# # # |cffff9933( ( ( Underground ) ) ) |cFFFFD700# # #|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11003', '|cFFFFD700Connected players: |cffff9933%u |cFFFFD700Characters in world: |cffff9933%u|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11004', '|cffff9933|cFFFFD700Connected players: |cffff9933%u |cFFFFD700Characters in world: |cffff9933%u|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11005', '|cff00ff00Player: |cffff00ff%s |cff00ff00(GUID: |cffff00ff%u|cff00ff00) (Account ID: |cffff00ff%u|cff00ff00) has been reported due to possible DOS flooding! opCode: |cffff00ff%u |cff00ff00count: |cffff00ff%u|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11006', '|cff00ff00Player: |cffff00ff%s |cff00ff00(GUID: |cffff00ff%u|cff00ff00) (Account ID: |cffff00ff%u|cff00ff00) has been reported due to casted spell: |cffff00ff%u |cff00ff00over: |cffff00ff%u |cff00ff00times! Possible gold cheater!|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11007', '|cFFFFD700WRONG GUID! Player doesn''t exists in database.|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11008', '|cFFFFD700Success! Player with GUID: |cffff9933%u|cFFFFD700 has been added to ninja looter list.|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11009', '|cFFFFD700WRONG GUID! Player doesn''t exists in database.|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11010', '|cFFFFD700Success! Player with GUID: |cffff9933%u |cFFFFD700has been removed from ninja looter list.|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11011', '|cFFFFD700There are no ninja looters on the list. Sounds good, isn\'t it?|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11012', '|cFFFFD700Warning! Player: |cffff9933%s |cFFFFD700at ninja looter list!|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11013', '|cFFFFD700Your experience rate has been changed to blizzlike (|cffff9933x1|cFFFFD700). You have to relog for the change to apply.|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11014', '|cFFFFD700Your experience rate has been changed to |cffff9933default|cFFFFD700. You have to relog for the change to apply.|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11015', '|cFFFFD700PvP announcements are |cffff9933enabled|cFFFFD700. You have to relog for the change to apply.|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11016', '|cFFFFD700PvP announcements are |cffff9933disabled|cFFFFD700. You have to relog for the change to apply.|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11017', '|cffff99332000|cFFFFD700 Personal Rating is required to use this command.|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11018', '|cFFFFD700Dodge mode has been |cffff9933enabled|cFFFFD700, display of your location is disabled.|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11019', '|cFFFFD700Dodge mode has been |cffff9933disabled|cFFFFD700, display of your location is enabled.|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11020', '|cff00ff00Player |cffff00ff%s |cff00ff00has |cffff00ffenabled|cff00ff00 Blizzlike Mode.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11021', '|cff00ff00Player |cffff00ff%s |cff00ff00has |cffff00ffdisabled|cff00ff00 Blizzlike Mode.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11022', '|cff00ff00Game Master: [|cffff00ff%s|cff00ff00] has banned player: [|cffff00ff%s|cff00ff00] for gold selling.|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11023', '|cff00ff00Game Master: [|cffff00ff%s|cff00ff00] has banned player: [|cffff00ff%s|cff00ff00] for speed hack.|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11024', '|cff00ff00The anticheat system has reported several times that you may be cheating. You will be monitored to confirm if this is accurate.|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11025', '|cff00ff00There is no player.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11026', '|cff00ff00Information about player: |cffff00ff%s|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11027', '|cff00ff00Average: |cffff00ff%f |cff00ff00|| Total Reports: |cffff00ff%u', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11028', '|cff00ff00Speed Reports: |cffff00ff%u |cff00ff00|| Fly Reports: |cffff00ff%u |cff00ff00|| Jump Reports: |cffff00ff%u|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11029', '|cff00ff00Walk On Water Reports: |cffff00ff%u  |cff00ff00|| Teleport To Plane Reports: |cffff00ff%u', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11030', '|cff00ff00Climb Reports: |cffff00ff%u|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11031', '|cFFFFD700You have no active Premium Privileges.|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11032', '|cffff9933%s |cFFFFD700is|r |cffff9933enabled|cFFFFD700. Expires: |cffff9933%s |cFFFFD700Realm Time.|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11033', '|cFFFFD700Drogi graczu, na Sunwellu dziala system geolokalizacji, ktory automatycznie przypisuje graczy do kanalow zalezenie od jezyka. Nasz system wykryl, ze jestes z Polski, dlatego automatycznie przypiszemy Cie do kanalu polskiego. Zyczymy milej gry na Sunwellu!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
('11034', '|cFFFFD700Dear community, there is a Geolocalization System on Sunwell that automatically invites players to chat channels by their language. Our system detected, that you are based outside of Poland, that\'s why you are in an English group. If you are Polish and play outside of Poland, write: /join world', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);