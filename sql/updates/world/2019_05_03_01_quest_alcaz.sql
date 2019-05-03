-- Core/Quest: Survey Alcaz Island - add outro event
DELETE FROM `creature_text` WHERE `entry` = 4968;
INSERT INTO `creature_text` VALUES 
(4968, 0, 0, 'Perhaps I should explain...', 12, 0, 100, 0, 0, 0, 0, 'Lady Jaina Proudmore'),
(4968, 1, 0, 'I had arranged for a secret summit between Warchief Thrall and King Wrynn, here in Theramore.', 12, 0, 100, 0, 0, 0, 0, 'Lady Jaina Proudmore'),
(4968, 2, 0, 'The King was to travel here by ship, in secret. But the ship never arrived, and King Wrynn disappeared.', 12, 0, 100, 0, 0, 0, 0, 'Lady Jaina Proudmore'),
(4968, 3, 0, 'Your help enabled us to connect the Defias to the mastermind behind the abduction, Onyxia, who was posing as a member of the royal court.', 12, 0, 100, 0, 0, 0, 0, 'Lady Jaina Proudmore'),
(4968, 4, 0, 'Meanwhile, the king managed to escape his captors, and returned to Stormwind to deal with Onyxia.', 12, 0, 100, 0, 0, 0, 0, 'Lady Jaina Proudmore'),
(4968, 5, 0, 'I will send word that you have discovered the link to the Defias. I was a fool to think them broken with the defeat of Edwin Van Cleef, and King Wrynn will want to make an example of all who remain.', 12, 0, 100, 0, 0, 0, 0, 'Lady Jaina Proudmore');
