DELETE FROM `spell_group` WHERE `id`=1035;
INSERT INTO `spell_group` (`id`, `spell_id`, `special_flag`) VALUES
(1035, 116, 0x010),
(1035, 205, 0x010),
(1035, 837, 0x010),
(1035, 7322, 0x010),
(1035, 8406, 0x010),
(1035, 8407, 0x010),
(1035, 8408, 0x010),
(1035, 10179, 0x010),
(1035, 10180, 0x010),
(1035, 10181, 0x010),
(1035, 25304, 0x010),
(1035, 27071, 0x010),
(1035, 27072, 0x010),
(1035, 38697, 0x010),
(1035, 42841, 0x010),
(1035, 42842, 0x010),
(1035, 59638, 0x010);
DELETE FROM `spell_group_stack_rules` WHERE `group_id`=1035;
INSERT INTO `spell_group_stack_rules` (`group_id`, `stack_rule`, `description`) VALUES
(1035, 0x01, "Mage Frostbolt and Mirror Image Frostbolt");
