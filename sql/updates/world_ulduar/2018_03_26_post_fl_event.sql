DELETE FROM `smart_scripts` WHERE `entryorguid` = 33189;
UPDATE `creature_template` SET `ScriptName` = "npc_liquid_piryte_flame_leviathan", `AIName` = "" WHERE `entry` = 33189;
SET @GOSSIP_ENTRY:= 21401;
SET @TEXT_ID:= 14471;

DELETE FROM `gossip_menu` WHERE `entry` = @GOSSIP_ENTRY;
INSERT INTO `gossip_menu` VALUES
(@GOSSIP_ENTRY, @TEXT_ID);

/* FLAME LEVIATHAN EVENT */
UPDATE `creature_template` SET `AIName` = "", `ScriptName` = "npc_brann_bronzebeard_flame_leviathan", `gossip_menu_id` = @GOSSIP_ENTRY WHERE `entry` = 34119;

DELETE FROM `creature_text` WHERE `entry` IN (34119, 33696);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `TextRange`, `comment`) VALUES
(34119, 0, 0, "What a battle! Did you see that, Rhydian?!", 14, 0, 100, 0, 0, 0, 0, "Brann bronzebeard post FL event"),
(34119, 1, 0, "Perhaps so, but it's only a matter of time until we break back into Ulduar. Any luck finding a way to teleport inside?", 14, 0, 100, 0, 0, 0, 0, "Brann bronzebeard post FL event"),
(34119, 2, 0, "Oi. So we'll have to contend with that thing after all then?", 14, 0, 100, 0, 0, 0, 0, "Brann bronzebeard post FL event"),
(34119, 3, 0, "What about the plated proto-drake and the fire giant that were spotted nearby? Think your mages can handle those?", 14, 0, 100, 0, 0, 0, 0, "Brann bronzebeard post FL event"),
(34119, 4, 0, "Sneak?! What do you think we are, marmots?", 14, 0, 100, 0, 0, 0, 0, "Brann bronzebeard post FL event"),
(34119, 5, 0, "Fine. If our allies are going to be the ones getting their hands dirty, we'll leave it to them to decide how to proceed.", 14, 0, 100, 0, 0, 0, 0, "Brann bronzebeard post FL event"),

(33696, 0, 0, '%s nods.', 16, 0, 100, 0, 0, 0, 0, 'Archmage Rhydian to Player'),
(33696, 1, 0, '%s whispers something to Brann.', 16, 0, 100, 0, 0, 0, 0, 'Archmage Rhydian to Player'),

(33696, 2, 0, "Our friends fought well, Brann, but we're not done yet.", 14, 0, 100, 0, 0, 0, 0, "Archmage Rhydian post FL event"),
(33696, 3, 0, "None at all. I suspect it has something to do with that giant mechanical construct that our scouts spotted in front of the gate.", 14, 0, 100, 0, 0, 0, 0, "Archmage Rhydian post FL event"),
(33696, 4, 0, "The Kirin Tor can't possibly spare any additional resources to take on anything that size. We may not have to though.", 14, 0, 100, 0, 0, 0, 0, "Archmage Rhydian post FL event"),
(33696, 5, 0, "We can sneak past them. As long as we can take down that construct in front of the gate, we should be able to get inside.", 14, 0, 100, 0, 0, 0, 0, "Archmage Rhydian post FL event"),
(33696, 6, 0, "We're hunting an old god, Brann. ", 14, 0, 100, 0, 0, 0, 0, "Archmage Rhydian post FL event");
