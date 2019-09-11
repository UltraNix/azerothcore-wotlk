-- DB/Spell: Basic Campfire - Cozy Fire buff should not be applied to hostile targets
DELETE FROM conditions WHERE SOURCEentry = 7353;
INSERT INTO `conditions` VALUES 
(13, 1, 7353, 0, 0, 34, 0, 1, 248, 0, 0, 0, 0, '', 'Only neutral to Exalted reaction');
