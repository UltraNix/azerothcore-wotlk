DELETE FROM `world_relay_json_strings` WHERE `RelayType` = 1;
INSERT INTO `world_relay_json_strings` VALUES (1, '{{\n    "attachments":\n	[\n		{{\n			"author_icon": "https://sunwell.pl/favicon/favicon-32x32.png",\n			"author_link": "https://sunwell.pl/armory/{}/{}",\n			"author_name": "{}",\n			"color": "{}",\n			"fields":\n			[\n				{{\n					"short": true,\n					"value": "Level: {}  ![](https://sunwell.pl/images/icons/small20/race/{}-0.jpg) ![](https://sunwell.pl/images/icons/small20/class/{}.jpg)"\n				}},\n				{{\n					"short": false,\n					"value": "GUID: _{}_ Account Id: _{}_"\n				}},\n				{{\n					"short": false,\n					"value": "Zone: _{}_ Area: _{}_"\n				}}\n			]\n		}},\n		{{\n			"fields":\n			[\n				{{\n					"short": false,\n					"value": "{}"\n				}}\n			]\n		}}\n    ],\n    "text": "New ticket on {} (#{})",\n    "username": "{}"\n}}');

DELETE FROM `world_relay_json_strings` WHERE `RelayType` = 6;
INSERT INTO `world_relay_json_strings` VALUES
(6, '{{\r\n  "text": "{}",\r\n  "username": "{}"\r\n}}');
