DELETE FROM `hellforge_boss_stats` WHERE `StatId` BETWEEN 0 AND 499;
INSERT INTO `hellforge_boss_stats` (`StatId`, `StatValue`, `StatVariance`, `StatComment`) VALUES
-- boss one stats
(0, 2500, 1.0, "Boss one fire aura damage"),
(1, 25000, 1.0, "Boss one explode damage"),
(2, 500000, 1.0, "Boss one fire nova damage, level damage calculations"),
(3, 12499000, 1.0, "Boss one max health"),
(4, 62000, 0.88, "Boss one melee damage"),
(5, 28000, 0.82, "Boss one add one max health"),
(6, 2000, 0.5, "Boss one add one melee damage"),
(7, 25000, 0.9, "Boss add add two explode damage"),

-- boss two stats
(8, 25400000, 1.0, "Boss two health"),
(9, 11999999, 1.0, "Boss two add health"),
(10, 89000, 0.79, "Boss two melee damage"),
(11, 62000, 0.90, "Boss two add melee damage"),

-- boss two spells
(12, 8500, 0.85, "Boss two blight crystal direct damage"),
(13, 7500, 0.80, "Boss two blight crystal periodic"),
(14, 25000, 0.75, "Boss two venom breath"),
(15, 1, 0.1, "Boss two - final phase - percent of health to set"),
(16, 25000, 0.76, "Boss two soaker explosion"),
(17, 20, 1.0, "Boss two add energy per soak"),
(18, 14000, 0.85, "Boss two mojo wave damage"),
(19, 16500, 0.76, "Boss two chaotic light damage"),
(20, 20, 1.0, "Boss two explosion percentage"),
(21, 30000, 0.85, "Boss two explosion damage"),
(22, 1, 2.0, "Boss two crossfire HasInLine radius"),
(23, 35000, 1.0, "Boss two crossfire damage"),
(24, 1, 5.0, "Boss two snake spreader distance from position"),

-- boss three
(25, 3499000, 1.0, "Simon max health"),
(26, 71000, 0.84, "Simon melee damage"),
(27, 15, 1.0, "Simon petrified bark charges"),
(28, 25000, 0.85, "Simon arctic winds"),

-- boss four
(29, 25123500, 1.0, "Boss four max health"),
(30, 92000, 0.77, "Boss four melee damage"),
(31, 60, 1.0, "Boss four first transition percentage"),
(32, 20, 1.0, "Boss four second transition percentage"),
(33, 30000, 1.0, "Boss four emp shockwave damage"),
(34, 50000, 0.90, "Boss four starfire damage"),
(35, 1, 0.95, "Boss four hammer throw health pct"),
(36, 2, 1.0, "Boss four mind warp player count"),
(37, 500000, 1.0, "Boss four frost nova damage"),
(38, 3, 1.0, "Boss four reflect charges amount"),
(39, 150, 1.0, "Boss four cleave weapon pct damage"),
(40, 500000, 1.0, "Boss four arcane explosion damage"),
(41, 30000, 1.0, "Boss four lightning nova damage"),
(42, 6000, 0.83, "boss four blizzard damage"),
(43, 300000, 1.0, "Boss four soul charge duration"),
(44, 8000, 1.0, "Boss four cold slap damage"),
(45, 6000, 0.83, "Boss four chain lightning"),
(46, 10000, 1.0, "Boss four lightning nova 2"),
(47, 100, 1.0, "Boss four lightning shield charges count"),

-- boss five
(48, 29499000, 1.0, "Boss five max health"),
(49, 65000, 0.86, "Boss five melee damage"),
(50, 1, 0.95, "Boss five shadow word: death"),
(51, 55000, 1.0, "Boss five sonic screech"),
(52, 8000, 0.75, "Boss five shadow bolt"),

(53, 48000, 1.0, "Boss five add bat health"),
(54, 6000, 0.83, "Boss five add bat shadow bolt"),

(55, 219000, 1.0, "Boss five crystal health"),

(56, 112000, 1.0, "Boss five add mindmaster health"),
(57, 89000, 1.0, "Boss five add mindmaster mana"),

(58, 798000, 1.0, "Boss five add slaughter health"),
(59, 41000, 0.82, "Boss five add slaugther melee"),

(60, 109000, 1.0, "Boss five add warlock health"),
(61, 99000, 1.0, "boss five add warlock mana"),

(62, 12000, 0.66, "boss five mindmaster wither damage"),

(63, 5000, 0.7, "boss five warlock mana burn damage"),

(64, 140, 1.0, "Boss five add slaughter cleave dmg"),

(65, 100, 1.0, "Boss five add slaughter hamstring dmg"),

(66, 4500, 0.77, "Boss five add mindmaster wither dot damage"),

(67, 23000, 0.65, "Boss five caster add melee damage"),

(68, 15000, 1.0, "Gargoyle gauntlet empowered shockwave"),
(69, 129000, 1.0, "Gargoyle gauntlet max health"),
(70, 7000, 0.71, "Gargoyle shadow bolt damage"),
(71, 320000, 1.0, "risen madman max health"),
(72, 30000, 0.66, "risen madman melee damage"),

(73, 8000, 1.0, "Simon tornado damage"),
(74, 12000, 1.0, "Simon sand trap damage"),

(75, 10, 1.0, "boss one add count first wave"),
(76, 20, 1.0, "boss one add count second wave"),
(77, 30, 1.0, "boss one add count third wave"),
(78, 8849700, 1, "Frost Worgen health"),
(79, 1, 0.5, "Boss one add one buffet chance"),

(80, 5000, 1.0, "Boss three slay time timer, in miliseconds"),
(81, 20000, 1.5, "Boss five worgen melee dmg"),

(82, 50000, 1.0, "Boss five shadowbreath damage"),
(83, 10000, 1.0, "Boss five flame damage");