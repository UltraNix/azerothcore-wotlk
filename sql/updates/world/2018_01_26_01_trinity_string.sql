UPDATE trinity_string SET content_default = '|cff77a5c4The Battle for|r |cff76bae8%s (%u-%u)|r |cff77a5c4has begun!|r' WHERE entry = 717; 
UPDATE trinity_string SET content_default = '|cff77a5c4The Battle for|r |cff76bae8Wintergrasp|r |cff77a5c4has begun!|r' WHERE entry = 20078;
UPDATE trinity_string SET content_default = '|cff77a5c4Queue status for %s (level %u to %u):|r\n|cff77a5c4Alliance in queue: %u (need at least %u).|r\n|cff77a5c4Horde in queue: %u (need at least %u).|r' WHERE entry = 711;
UPDATE trinity_string SET content_default = '|cff77a5c4Queue status for %s (level %u to %u):|r\n|cff77a5c4Alliance in queue: %u + random queue (need at least %u).|r\n|cff77a5c4Horde in queue: %u + random queue (need at least %u).|r' WHERE entry = 712; 
UPDATE trinity_string SET content_default = '|cff77a5c4Queue status for %s (level %u to %u):|r\n|cff77a5c4Alliance in queue: %u + specific queue.|r\n|cff77a5c4Horde in queue: %u + specific queue.|r' WHERE entry = 713;
DELETE FROM trinity_string WHERE entry = 788;
INSERT INTO trinity_string(entry,content_default) VALUES (788, "|cff77a5c4The Battle for|r |cff76bae8%s (80)|r |cff77a5c4has begun!|r");