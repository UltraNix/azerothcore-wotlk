-- First group after teleport
DELETE FROM `creature_formations` WHERE `leaderGUID`=136557;
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`)  VALUES 
(136557, 136557, 3, 260, 5),
(136557, 136603, 3, 260, 5),
(136557, 136610, 3, 260, 5),
(136557, 1979707, 3, 260, 5),
(136557, 1979705, 3, 260, 5),
(136557, 1979703, 3, 260, 5);
-- First pair (Rune Etched Sentry)
DELETE FROM `creature_formations` WHERE `leaderGUID`=136595;
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`)  VALUES 
(136595, 136595, 3, 260, 5),
(136595, 136596, 3, 260, 5);
-- Second pair (Rune Etched Sentry)
DELETE FROM `creature_formations` WHERE `leaderGUID`=136597;
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`)  VALUES 
(136597, 136597, 3, 260, 5),
(136597, 136598, 3, 260, 5);
-- Group before Kologarn
DELETE FROM `creature_formations` WHERE `leaderGUID`=1979706;
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`)  VALUES 
(1979706, 1979706, 3, 260, 5),
(1979706, 136602, 3, 260, 5),
(1979706, 136556, 3, 260, 5),
(1979706, 136609, 3, 260, 5),
(1979706, 1979704, 3, 260, 5),
(1979706, 1979702, 3, 260, 5);
