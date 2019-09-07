DELETE FROM `hellforge_boss_stats` WHERE `StatId` BETWEEN 150 AND 450;
INSERT INTO `hellforge_boss_stats` VALUES
/** diablo **/
(150, 20, 1.0, "Diablos health percentage when first napalam shell start to rain"),
(151, 8, 1.0, "Napalam shell repeat timer, before re-adjustments"),
(152, 10, 1.0, "Health percentage when napalam shells start to fire faster"),
(153, 1, 1.0, "Napalam shell normal count"),
(154, 2, 1.0, "Napalam shell re-adjusted count"),
(155, 50, 1.0, "Percentage when intermission starts"),
(156, 60000, 1.0, "Shadow step explosion damage"),
(157, 22500, 1.0, "Shadow step explosion radius ratio"),
(158, 14000, 0.8, "Napalam shell damage"),
(159, 10000, 1.0, "Napalm shell radius ratio"),
(160, 70, 1.0, "shadow realm timer"),
(161, 6, 1.0, "Knockback phbase one first timer"),
(162, 17, 1.0, "Knockback phase one repeat timer"),
(163, 15, 1.0, "Shadowstep phase one first timer"),
(164, 18, 1.0, "Shadowstep phase one repeatTimer"),
(165, 6, 1.0, "Shadowstep or knockback phase two first timer"),
(166, 12, 1.0, "Shadowstep or knockback phase two repeat timer"),
(167, 20, 1.0, "Fire elementals first spawn time"),
(168, 20, 1.0, "Fire elementals repeat timer"),
(169, 45, 1.0, "plasma ray first timer"),
(170, 45, 1.0, "plasma ray repeat timer"),
(171, 6, 1.0, "Pheonix first timer"),
(172, 30, 1.0, "Pheonix second timer, after first one finishes cleanly"),
(173, 10, 1.0, "Firebeam timer after successul or not shadow realm"),
(174, 1, 0.9, "How fast the ball of flames are traveling, uses move run as default"),
(175, 50000, 1.0, "Plasma ray damage"),
(176, 65, 1.0, "Timer, in seconds, when diablo starts casting his wipe spell that has to be interrupted"),
(177, 15000, 1.0, "Diablo wipe spell cast time, in milliseconds"),
(178, 2, 1.0, "How many ashes of alar is supposed to spawn"),
(179, 2, 1.0, "How many shadow drakes is supposed to spanw"),
(180, 30, 1.0, "Shadowrealm fail timer, how long, in seconds, can player stay in shadow realm without completing it"),
(181, 3500, 1.0, "Armageddon duration"),
(182, 6666, 1.0, "Armageddon radius ratio"),
(183, 100000, 1.0, "Armageddon damage"),
(184, 110000, 1.0, "Winds fall damage"),
(185, 4000, 1.0, "Spirit burn damage (siphon soul)"),
(186, 1, 1.1, "plasma ray width"),
(187, 1500, 1.0, "thundershock damage"),

/** demons **/
(200, 5, 1, "Demon shadow nova timer"),
(201, 8000, 1.0, "Demon shadow nova radius ratio"),
(202, 20000, 1.0, "Demon shadow nova damage"),
(203, 2, 1.0, "Demon shadow nova repeat timer"),
(204, 20, 1.0, "Demon switch timer (reflect and shadow nova types)"),
(205, 10, 1.0, "nearby demon radius, in yards"),
(206, 2, 1.0, "Nearby demon check, timer in seconds"),

/** Fire beam **/
(207, 25000, 1.0, "Firebeam explosion damage"),
(208, 5000, 1.0, "Firebeam explosion radius ratio"),
(209, 10, 1.0, "Firebeam flame patch percent damage"),
(210, 5000, 1.0, "Firebeam flame patch radius ratio"),
(211, 20, 1.0, "Firebeam despawn timer"),

/** player clone stats **/
(212, 3, 1.0, "Playerclone comet count per tick"),
(213, 4, 1.0, "playerclone comet first timer"),
(214, 14, 1.0, "playerclone comet repeat timer"),

/** Comet stats **/
(215, 10, 1.0, "Comet hit timer, in seconds"),
(216, 18000, 1.0, "comet hit damage"),
(217, 10000, 1.0, "meteor hit radius ratio"),
(218, 0, 1.0, "meteor hit target players only, 0 - false | 1 - true"),

/** infernal stats **/
(219, 2, 1.0, "Infernal hellfire first cast timer"),
(220, 12000, 1.0, "infernal hellfire damage"),
(221, 5000, 1.0, "Infernal hellfire radius ratio"),
(222, 4, 1.0, "Infernal hellfire repeat timer"),

/** increased damage & flame buffet trigger, shadow realm phase **/
(223, 2, 1.0, "increased damage trigger check timer in seconds"),
(224, 35000, 1.0, "flame buffet aura duration"),
(225, 5000, 1.0, "flame buffet base damage"),
(226, 1, 1.0, "Flame buffet radius ratio, small one, this spell has 500k base radius. Only whole numbers"),

/** Elemental stats **/
(227, 1, 0.5, "Distance to diable that triggers explosion"),
(228, 1, 0.1, "elementals self-damage every X seconds, this value controls how much of MaxHealth they deal to self"),
(229, 2, 1.0, "elemental check timer"),
(230, 3000, 1.0, "Elemental explosion damage"),
(231, 100000, 1.0, "Elemental explosion radius ratio"),

/** Shadow drake **/
(232, 10, 1.0, "Shadow drake devouring flame timer"),

/** Health & Misc **/
(233, 1, 10.0, "Buffeting winds, radius of nearby players that get booted up as well"),
(234, 50, 1.0, "five fat fingers proc chance"),
(235, 9350, 1.0, "diablo offhand proc damage"),

(236, 120000, 1.0, "abyssal knight health"),
(237, 1500000, 1.0, "pit lord health"),
(238, 37459000, 1.0, "diablo health"),
(239, 5800000, 1.0, "heartbeam health"),
(240, 1000, 1.0, "shadow crystal health"),
(241, 119000, 1.0, "Shadow drake health"),
(242, 89000, 1.0, "phoenix health"),
(243, 112000, 1.0, "wandering elemental health"),

/** Melee **/
(244, 14000, 0.64, "Abyssal knight melee damage"),
(245, 45000, 0.555, "Pit lord melee damage"),
(246, 69000, 0.65, "Diablo melee damage"),

/** Additional spell damages **/
(247, 10000, 0.7, "napalm shell dot damage"),
(248, 7000, 0.83, "conversion beam damage"),
(249, 2, 1.0, "shadow drake void blast timer"),
(250, 12000, 1.0, "Shadow drake devouring flame damage"),
(251, 9000, 0.88, "Shadow drake void blast damage"),
(252, 9000, 0.55, "runic lightning damage"),
(253, 0, 0.8, "fire elemental speed rate, walk");
