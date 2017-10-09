-- Alliance reputation split
DELETE FROM `reputation_spillover_template` WHERE `faction`=72;
INSERT INTO `reputation_spillover_template` (`faction`, `faction1`, `rate_1`, `rank_1`, `faction2`, `rate_2`, `rank_2`, `faction3`, `rate_3`, `rank_3`, `faction4`, `rate_4`, `rank_4`) VALUES 
(72, 47, 0.25, 7, 69, 0.25, 7, 930, 0.25, 7, 54, 0.25, 7);

DELETE FROM `reputation_spillover_template` WHERE `faction`=47;
INSERT INTO `reputation_spillover_template` (`faction`, `faction1`, `rate_1`, `rank_1`, `faction2`, `rate_2`, `rank_2`, `faction3`, `rate_3`, `rank_3`, `faction4`, `rate_4`, `rank_4`) VALUES 
(47, 72, 0.25, 7, 69, 0.25, 7, 930, 0.25, 7, 54, 0.25, 7);

DELETE FROM `reputation_spillover_template` WHERE `faction`=69;
INSERT INTO `reputation_spillover_template` (`faction`, `faction1`, `rate_1`, `rank_1`, `faction2`, `rate_2`, `rank_2`, `faction3`, `rate_3`, `rank_3`, `faction4`, `rate_4`, `rank_4`) VALUES 
(69, 72, 0.25, 7, 47, 0.25, 7, 930, 0.25, 7, 54, 0.25, 7);

DELETE FROM `reputation_spillover_template` WHERE `faction`=930;
INSERT INTO `reputation_spillover_template` (`faction`, `faction1`, `rate_1`, `rank_1`, `faction2`, `rate_2`, `rank_2`, `faction3`, `rate_3`, `rank_3`, `faction4`, `rate_4`, `rank_4`) VALUES 
(930, 72, 0.25, 7, 47, 0.25, 7, 69, 0.25, 7, 54, 0.25, 7);

DELETE FROM `reputation_spillover_template` WHERE `faction`=54;
INSERT INTO `reputation_spillover_template` (`faction`, `faction1`, `rate_1`, `rank_1`, `faction2`, `rate_2`, `rank_2`, `faction3`, `rate_3`, `rank_3`, `faction4`, `rate_4`, `rank_4`) VALUES 
(54, 72, 0.25, 7, 47, 0.25, 7, 69, 0.25, 7, 930, 0.25, 7);


-- Horde reputation split
DELETE FROM `reputation_spillover_template` WHERE `faction`=68;
INSERT INTO `reputation_spillover_template` (`faction`, `faction1`, `rate_1`, `rank_1`, `faction2`, `rate_2`, `rank_2`, `faction3`, `rate_3`, `rank_3`, `faction4`, `rate_4`, `rank_4`) VALUES 
(68, 81, 0.25, 7, 911, 0.25, 7, 530, 0.25, 7, 76, 0.25, 7);

DELETE FROM `reputation_spillover_template` WHERE `faction`=81;
INSERT INTO `reputation_spillover_template` (`faction`, `faction1`, `rate_1`, `rank_1`, `faction2`, `rate_2`, `rank_2`, `faction3`, `rate_3`, `rank_3`, `faction4`, `rate_4`, `rank_4`) VALUES 
(81, 68, 0.25, 7, 911, 0.25, 7, 530, 0.25, 7, 76, 0.25, 7);

DELETE FROM `reputation_spillover_template` WHERE `faction`=911;
INSERT INTO `reputation_spillover_template` (`faction`, `faction1`, `rate_1`, `rank_1`, `faction2`, `rate_2`, `rank_2`, `faction3`, `rate_3`, `rank_3`, `faction4`, `rate_4`, `rank_4`) VALUES 
(911, 68, 0.25, 7, 81, 0.25, 7, 530, 0.25, 7, 76, 0.25, 7);

DELETE FROM `reputation_spillover_template` WHERE `faction`=530;
INSERT INTO `reputation_spillover_template` (`faction`, `faction1`, `rate_1`, `rank_1`, `faction2`, `rate_2`, `rank_2`, `faction3`, `rate_3`, `rank_3`, `faction4`, `rate_4`, `rank_4`) VALUES 
(530, 68, 0.25, 7, 81, 0.25, 7, 911, 0.25, 7, 76, 0.25, 7);

DELETE FROM `reputation_spillover_template` WHERE `faction`=76;
INSERT INTO `reputation_spillover_template` (`faction`, `faction1`, `rate_1`, `rank_1`, `faction2`, `rate_2`, `rank_2`, `faction3`, `rate_3`, `rank_3`, `faction4`, `rate_4`, `rank_4`) VALUES 
(76, 68, 0.25, 7, 81, 0.25, 7, 911, 0.25, 7, 530, 0.25, 7);

