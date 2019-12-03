DROP TABLE IF EXISTS `banned_addons`;
CREATE TABLE `banned_addons` (
  `Id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `Name` varchar(255) NOT NULL,
  `Version` varchar(255) NOT NULL DEFAULT '',
  `Timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`Id`),
  UNIQUE KEY `idx_name_ver` (`Name`, `Version`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

TRUNCATE TABLE `addons`;
INSERT INTO `addons` VALUES
('Blizzard_AchievementUI', 1276933997),
('Blizzard_ArenaUI', 1276933997),
('Blizzard_AuctionUI', 1276933997),
('Blizzard_BarbershopUI', 1276933997),
('Blizzard_BattlefieldMinimap', 1276933997),
('Blizzard_BindingUI', 1276933997),
('Blizzard_Calendar', 1276933997),
('Blizzard_CombatLog', 1276933997),
('Blizzard_CombatText', 1276933997),
('Blizzard_DebugTools', 1276933997),
('Blizzard_GlyphUI', 1276933997),
('Blizzard_GMChatUI', 1276933997),
('Blizzard_GMSurveyUI', 1276933997),
('Blizzard_GuildBankUI', 1276933997),
('Blizzard_InspectUI', 1276933997),
('Blizzard_ItemSocketingUI', 1276933997),
('Blizzard_MacroUI', 1276933997),
('Blizzard_RaidUI', 1276933997),
('Blizzard_TalentUI', 1276933997),
('Blizzard_TimeManager', 1276933997),
('Blizzard_TokenUI', 1276933997),
('Blizzard_TradeSkillUI', 1276933997),
('Blizzard_TrainerUI', 1276933997);
