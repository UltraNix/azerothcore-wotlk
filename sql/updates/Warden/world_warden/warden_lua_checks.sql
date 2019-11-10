DROP TABLE IF EXISTS `warden_lua_checks`;
CREATE TABLE `warden_lua_checks`
(
 `CheckId` INT(3) UNSIGNED NOT NULL auto_increment primary key,
 `LuaCode` TEXT NOT NULL,
 `CheckType` INT(3) UNSIGNED NOT NULL COMMENT 'Check WardenLuaCheckType enum in WorldCache.h for explanation',
 `Description` VARCHAR(100) NOT NULL DEFAULT 'Fill this or im gonna yell at you',
 `FalsePositiveChance` ENUM('None', 'Low', 'High') DEFAULT 'Low',
 `ShouldRelay` TINYINT(1) DEFAULT 1,
 `CheckComment` VARCHAR(150) NOT NULL DEFAULT 'Developer comment'
);

INSERT INTO `warden_lua_checks` (`CheckId`, `LuaCode`, `CheckType`, `Description`, `FalsePositiveChance`, `ShouldRelay`, `CheckComment`) VALUES
(1, 'if not _tainted then local f = CreateFrame(\'frame\') f:SetScript(\'OnEvent\',function(s, e)@addonSuccess end)f:RegisterEvent\'MACRO_ACTION_FORBIDDEN\' _tainted = true end;', 4, 'Addon sending frame', 'None', 1, 'Setup a frame that will send us addon messages'),
(2, 'RunMacroText(\'/run TargetNearest()\')StaticPopup_Hide(\'MACRO_ACTION_FORBIDDEN\')', 3, 'Clean client will always trigger MACRO_ACTION_FORBIDDEN event, unlocked will not', 'High', 1, 'Unlocked lua check'),
(3, 'if (issecure()) then @addonSuccess else @addonFailure end', 1, 'Unlocked lua check', 'High', 1, 'This should return something, otherwise its unlocked?'),
(4, 'forceinsecure() if (issecure())then @addonFailure else @addonSuccess end', 1, 'Unlocked lua check', 'High', 1, 'This should always return insecure, there are cheats that set lua state multiple times a second'),
(5, 'if(rcbn==nil and CastSpellByName~=nil)then rcbn=CastSpellByName CastSpellByName=function(a) if(strfind(debugstack(2),\'Secure\')==nil)then @addonSuccess end rcbn(a) CastSpellByName=rcbn rcbn=nil end end', 2, 'Client called protected function!', 'Low', 1, 'hooks a sendaddon message when CastSpellByName is called'),
(6, '@CreateSendAddonMessage', 5, 'Addon message sending function', 'None', 1, 'Setup a function that will get called and send addon message to us'),
(7, 'if (UIParent) then if (qoeKxhg == nil)then @addonSuccess else @addonFailure end end', 1, 'Probably botting', 'High', 1, 'Check if cheat created a frame called qoeKxhg, thats warmane check. probably a cheat?'),
(8, 'if (UIParent) then if (PQR_EventFrame == nil)then @addonSuccess else @addonFailure end end', 1, 'Check if PQR frame has been created', 'Low', 1, 'This should never false-pasitive'),
(9, 'local c=0 for i,v in pairs(_G) do if (type(v)=="table" and v["PQR_EventFrame"] ~= nil)then c=c+1 if (c>1)then break end end end if(c<2)then @addonSuccess else @addonFailureend', 1, 'PQR CHECK', 'Low', 1, 'check global tables for PQR frames'),
(10, 'if(PQR_EventFrame~=nil)then @addonFailure else @addonSuccess end', 1, 'PQR check', 'Low', 1, 'another pqr check with reversed logic'),
(11, 'local s,c,f=\'cFF32CD32EWT\',0,string; mc=DEFAULT_CHAT_FRAME:GetNumMessages() for i=1,mc do t=DEFAULT_CHAT_FRAME:GetMessageInfo(i) if f.find(t,s)~=nil and f.find(t,\'says\')==nil then c=c+1 end end if(c==0)then @addonSuccessend', 1, 'Found EWT cheat or has been detoured, do a check on this account', 'High', 1, 'Search for string on default chat frame. If client do not respond then string found or check detoured, in both cases - cheating'),
(12, 'if (UIParent) then if (PQR_EventFrame == nil) then @addonSuccess else @addonFailure end end', 1, 'PQR Check', 'Low', 1, 'Checks whether client has a frame called PQR_EventFrame'),
(13, 'if(CastSpellOnUnit)then @addonFailure else @addonSuccess end', 1, 'Bot check', 'High', 1, 'Checks whether client has a function CastSpellOnUnit which is used by some bots'),
(14, 'local s,c="\\124cffff7d0a<\\124r\\124cffffd200PQR",0; mc=DEFAULT_CHAT_FRAME:GetNumMessages() for i=1,mc do if string.find(DEFAULT_CHAT_FRAME:GetMessageInfo(i),s) ~= nil then c=c+1 end end if (c == 0)then @addonSuccess end', 1, 'Found PQR cheat or has been detoured, do a check on this account', 'High', 1, 'Search for string on default chat frame. If client do not respond then string found or check detoured, in both cases - cheating'),
(15, 'local s,c="\\124cFFFF4400WoWPlus \\124 ",0; mc=DEFAULT_CHAT_FRAME:GetNumMessages() for i=1,mc do if string.find(DEFAULT_CHAT_FRAME:GetMessageInfo(i),s) ~= nil then c=c+1 end end if (c == 0)then @addonSuccess end', 1, 'Found WoWPlus cheat or has been detoured, do a check on this account', 'High', 1, 'Search for string on default chat frame. If client do not respond then string found or check detoured, in both cases - cheating');
