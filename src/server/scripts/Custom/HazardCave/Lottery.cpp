/*
* Copyright (C)
* Copyright (C)
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "Lottery.h"

bool Lottery::randomItemWithPercent(Player * player, uint32 itemId, float winChance)
{
    uint32 win = uint32(winChance * 100);
    uint32 chance = urand(1, 10000);

    if (chance < win)
    {
        player->AddItem(itemId, 1);
        sLog->outRewards("Player with GUID: %u, won item with id: %u", player->GetGUIDLow(), itemId);
        return true;
    }

    return false;
}

std::string dataBaseNames[] = { "lottery_gold_bets", "lottery_sunwell_coins_bets"};
bool Lottery::AddNumbers(const char * code, Player * player, Creature * pCreature, LotteryType type)
{
    char * charCode = (char*)code;
    std::string strCode = (char*)code;
    char * tmp;
    int32 checkNumber = 0;
    uint32 number[LOTTERY_FIELDS];
    std::stringstream error;
    error << "Wpisales zle liczby. Musisz wpisac " << LOTTERY_FIELDS << " liczby (oddzielone znakami spacji) od 1 - " << LOTTERY_MAXNUMBER << ".";
    std::string duplicateError = "Juz obstawiales takie liczby. ";
    std::string numberDuplicateError = "Twoje liczby sie powatrzaja.";
    std::string sNumbers;

    tmp = strtok(charCode, " ");
    for (int8 n = 0; n < LOTTERY_FIELDS; n++)
    {
        if (tmp != NULL)
        {
            checkNumber = atoi(tmp);
            sLog->outBasic("Numer %d", checkNumber);
            if(Lottery::contains(number, n, checkNumber))
            {
                pCreature->MonsterWhisper(numberDuplicateError.c_str(), player);
                player->CLOSE_GOSSIP_MENU();
                return false;
            }
            if (checkNumber <= 0 || checkNumber > LOTTERY_MAXNUMBER)
            {
                pCreature->MonsterWhisper(error.str().c_str(), player);
                player->CLOSE_GOSSIP_MENU();
                return false;
            }
            else number[n] = uint32(checkNumber);
            tmp = strtok(NULL, " ");
        }
        else
        {
            pCreature->MonsterWhisper(error.str().c_str(), player);
            player->CLOSE_GOSSIP_MENU();
            return false;
        }
    }

    QueryResult pBet = CharacterDatabase.PQuery("SELECT bet FROM %s WHERE guid = %u ", dataBaseNames[type].c_str(), player->GetGUIDLow());
    if (pBet) 
    {
        do 
        {
            Field *fBet = pBet->Fetch();
            std::string bet = fBet[0].GetString();
            uint32 numberDB[LOTTERY_FIELDS];
            char * tmp;
            tmp = strtok((char*)bet.c_str(), " ");
            for (int8 n = 0; n < LOTTERY_FIELDS; ++n)
            {
                if (tmp != NULL)
                {
                    numberDB[n] = uint32(atoi(tmp));
                    tmp = strtok(NULL, " ");
                }
            }
            if (Lottery::equals(numberDB, number)) {
                pCreature->MonsterWhisper(duplicateError.c_str(), player);
                player->CLOSE_GOSSIP_MENU();
                return false;
            }
        } while (pBet->NextRow());
    }

    std::stringstream ssNumber;
    for (int i = 0; i < LOTTERY_FIELDS; i++)
    {
        ssNumber << number[i];
        if (i < LOTTERY_FIELDS - 1)
            ssNumber << " ";
    }

    sNumbers = "Twoje liczby sa nastepujace: " + ssNumber.str();

    uint32 betMaxID = 0;
    QueryResult qbetMaxID = CharacterDatabase.PQuery("SELECT MAX(id) FROM %s", dataBaseNames[type].c_str());

    if (qbetMaxID)
        betMaxID = qbetMaxID->Fetch()->GetUInt32();

    CharacterDatabase.PExecute("INSERT INTO %s (id, name, guid, bet) VALUES ('%u', '%s', '%u', '%s');", dataBaseNames[type].c_str(), betMaxID + 1, player->GetName().c_str(), player->GetGUIDLow(), ssNumber.str().c_str());
    pCreature->MonsterWhisper(sNumbers.c_str(), player);

    player->CLOSE_GOSSIP_MENU();
    return true;
}

bool Lottery::contains(uint32 * arrayWithNumbers, uint32 size, uint32 value)
{
    for (uint32 i = 0; i < size; i++)
        if (arrayWithNumbers[i] == value)
            return true;
    return false;
}

bool Lottery::equals(uint32 * arrayFirst, uint32 * arraySecond)
{
    for (int8 i = 0; i < LOTTERY_FIELDS; i++)
        if(!Lottery::contains(arraySecond, LOTTERY_FIELDS, arrayFirst[i]))
            return false;
    return true;
}

#define EVENT_ID 132
std::string dataBaseLotteryNames[] = { "lottery_gold", "lottery_sunwell_coins" };
void Lottery::findWinners(Creature * pCreature, LotteryType type)
{
    // Amount of bets
    QueryResult qMaxID = CharacterDatabase.PQuery("SELECT MAX(id) FROM %s", dataBaseNames[type].c_str()); 

    if (!qMaxID)
    {
        pCreature->SetVisible(true);
        return;
    }

    uint32 betMaxID = qMaxID->Fetch()->GetUInt32();
    uint32 luckyNumber[LOTTERY_FIELDS];
    std::stringstream sLuckyNumber;
    uint32 lotteryID;

    uint32 winnerCount[LOTTERY_FIELDS];

    typedef std::list<sWinner> tdJW;
    tdJW lJackpotWinners;
    tdJW lWinners;

    SQLTransaction ctrans = CharacterDatabase.BeginTransaction();

    for (int i = 0; i < LOTTERY_FIELDS; i++)
        winnerCount[i] = 0;

    // Number of Lottery
    QueryResult qlotteryID = CharacterDatabase.PQuery("SELECT MAX(id) FROM %s", dataBaseLotteryNames[type].c_str());

    if (!qlotteryID)
        lotteryID = 0;
    else
        lotteryID = qlotteryID->Fetch()->GetUInt32();

    // Getting earlier jakcpot from db
    uint32 jackpot = 0;

    QueryResult qJackpot = CharacterDatabase.PQuery("SELECT jackpot FROM %s WHERE id = '%u'", dataBaseLotteryNames[type].c_str(), lotteryID);

    if (qJackpot)
        jackpot = qJackpot->Fetch()->GetUInt32();

    // All jackpot money
    uint32 stakes; 
    if (type == GOLD_LOTTERY) stakes = (betMaxID * LOTTERY_BETCOST) + jackpot;
    if (type == SUNWELL_COINS_LOTTERY) stakes = jackpot + (LOTTERY_SC_BETCOST * betMaxID);

    // Getting all bets for Lottery
    uint32 tmp;

    QueryResult qBets = CharacterDatabase.PQuery("SELECT guid, bet, name FROM %s", dataBaseNames[type].c_str());
    if (qBets)
    {
        // Random numbers for Lottery
        for (int8 n = 0; n < LOTTERY_FIELDS; n++)
        {
            tmp = urand(1, LOTTERY_MAXNUMBER);
            if (contains(luckyNumber, n, tmp))
                n--;
            else 
                luckyNumber[n] = tmp;
        }

        // Transform into stringstream
        for (int i = 0; i < LOTTERY_FIELDS; i++)
        {
            sLuckyNumber << luckyNumber[i];

            if (i < LOTTERY_FIELDS - 1)
                sLuckyNumber << " ";
        }

        do
        {
            // Read all fields
            Field *fBets = qBets->Fetch();
            uint32 guid = fBets[0].GetUInt32();
            std::string bet = fBets[1].GetString();
            std::string rBet = bet;
            std::string name = fBets[2].GetString();
            uint32 points = 0;

            int32 number[LOTTERY_FIELDS];
            char * tmp;

            tmp = strtok((char*)bet.c_str(), " ");

            // Tranform into array
            for (int8 n = 0; n < LOTTERY_FIELDS; ++n)
            {
                if (tmp != NULL)
                {
                    number[n] = atoi(tmp);
                    tmp = strtok(NULL, " ");
                }
            }

            for (int8 n = 0; n < LOTTERY_FIELDS; ++n)
                if (contains(luckyNumber, LOTTERY_FIELDS, number[n]))
                {
                    points++;
                    number[n] = 0;
                }

            if (points <= 2)
                continue;
            //Assign winner
            sWinner winner;
            winner.guid = guid;
            winner.bets = rBet;
            winner.name = name;
            winner.points = points;

            if (points == LOTTERY_FIELDS)
                lJackpotWinners.push_back(winner);
            else
                lWinners.push_back(winner);

            winnerCount[points - 1]++;

        } while (qBets->NextRow());

        for (tdJW::const_iterator itr = lWinners.begin(); itr != lWinners.end(); itr++)
        {
            uint32 cash = ((stakes * 0.25f) / winnerCount[LOTTERY_FIELDS - 2]);

            std::stringstream text;
            text << "Gratulacje trafile poprawnie liczby!\n\n";
            text << "Twoje liczby: " << itr->bets.c_str() << "\n";
            text << "Szczesliwe liczby: " << sLuckyNumber.str().c_str() << "\n\n";
            text << "Trafien: " << itr->points << "\n";
            text << "Liczb w ilosci " << itr->points << " trafilo: " << winnerCount[itr->points - 1] << "postaci";

            if (type)
                text << "\nTwoje " + std::to_string(cash) + " Sunwell Coinsow powinny byc na koncie";
            else
                text << "\nOto twoja wygrana w wysokosci: " + std::to_string(uint32(cash * 0.0001f)) + " zlota";

            Player *pWinner = ObjectAccessor::FindPlayerInOrOutOfWorld(itr->guid);
            MailDraft mail("Wygrana", text.str());
            MailSender sender(MAIL_CREATURE, 3460607 + type /* Lottery guys */);

            if (type) 
                Lottery::modifySunwellPoints(itr->name, cash);
            else 
                mail.AddMoney(cash);

            mail.SendMailTo(ctrans, MailReceiver(pWinner, itr->guid), sender);
            CharacterDatabase.PExecute("INSERT INTO lottery_winners (id, name, guid, bet, betPoints, betType, time) VALUES (%u, '%s', '%u', '%s', '%u', '%u', CURRENT_TIMESTAMP())", lotteryID + 1, itr->name.c_str(), itr->guid, itr->bets.c_str(), itr->points, type ? 1 : 0);
        }

        if (winnerCount[LOTTERY_FIELDS - 1] > 0)
        {
            uint32 cash = ((stakes * 0.7f) / winnerCount[LOTTERY_FIELDS - 1]);

            for (tdJW::const_iterator itr = lJackpotWinners.begin(); itr != lJackpotWinners.end(); itr++)
            {
                std::stringstream text;
                text << "Gratulacje, trafiles wszystkie liczby\n\n";
                text << "Twoje liczby: " << itr->bets.c_str() << "\n";
                text << "Szczesliwe liczby: " << sLuckyNumber.str().c_str() << "\n\n";
                text << "Trafien: " << itr->points << "\n";
                text << "Liczb w ilosci " << itr->points << " trafilo: " << winnerCount[itr->points - 1] << "postaci";

                if (type)
                    text << "\nTwoje" + std::to_string(cash) + " Sunwell Coinsow powinny byc na koncie";
                else 
                    text << "\nOto twoja wygrana w wysokosci: " + std::to_string(uint32(cash * 0.0001f)) + " zlota";

                Player *pJPWinner = ObjectAccessor::FindPlayerInOrOutOfWorld(itr->guid);
                MailSender sender(MAIL_CREATURE, 3460607 + uint32(type) /* Lottery guys */);
                MailDraft mail("Wygrana!", text.str().c_str());

                if (type) 
                    Lottery::modifySunwellPoints(itr->name, cash);
                else
                    mail.AddMoney(cash);

                mail.SendMailTo(ctrans, MailReceiver(pJPWinner, itr->guid), sender);
                CharacterDatabase.PExecute("INSERT INTO lottery_winners (id, name, guid, bet, betPoints, betType, time) VALUES (%u, '%s', '%u', '%s', '%u', '%u', CURRENT_TIMESTAMP());", lotteryID + 1, itr->name.c_str(), itr->guid, itr->bets.c_str(), itr->points, type ? 1 : 0);
            }

            if (winnerCount[LOTTERY_FIELDS - 1] == 1)
                sWorld->SendWorldText(LANG_LOTTERY_ANNOUNCE_JACKPOT, betMaxID, sLuckyNumber.str().c_str(), lJackpotWinners.begin()->name.c_str(), uint32(stakes * 0.7f * (type ? 1 : 0.0001f)), type ? "Sunwell Coinsow" : "zlota");
            else
                sWorld->SendWorldText(LANG_LOTTERY_ANNOUNCE_JACKPOT_M_PLAYERS, betMaxID, sLuckyNumber.str().c_str(), winnerCount[LOTTERY_FIELDS - 1], uint32(stakes * 0.7f * (type ? 1 : 0.0001f))/ winnerCount[LOTTERY_FIELDS - 1], type ? "Sunwell Coinsow" : "zlota");

            jackpot = 0;
        }
        else
        {
            jackpot = stakes * 0.7f;
            if (!winnerCount[LOTTERY_FIELDS - 2]) 
                jackpot += stakes *0.25f;

            sWorld->SendWorldText(LANG_LOTTERY_ANNOUNCE, betMaxID, sLuckyNumber.str().c_str(), uint32(stakes * 0.7f * (type ? 1 : 0.0001f)), type ? "Sunwell Coinsow" : "zlota" );
        }

        CharacterDatabase.PExecute("INSERT INTO %s (numbers, jackpot) VALUES ('%s', '%u');", dataBaseLotteryNames[type].c_str(), sLuckyNumber.str().c_str(), jackpot);
        CharacterDatabase.PExecute("DELETE FROM %s;", dataBaseNames[type].c_str());

        CharacterDatabase.CommitTransaction(ctrans);

        pCreature->SetVisible(false);
    }
    sGameEventMgr->StopEvent((EVENT_ID + type), true);
}

void Lottery::modifyLotteryPoints(Player *player, int32 amount) 
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_ACCOUNT_BY_NAME);
    stmt->setString(0, player->GetName());
    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (result)
    {
        Field* field = result->Fetch();
        QueryResult lotteryCoins = LoginDatabase.PQuery("SELECT vp FROM account WHERE id = %u", field[0].GetUInt32());
        if (lotteryCoins)
        {
            uint32 amountLC = lotteryCoins->Fetch()->GetUInt32();
            if (amount < 0) 
            {
                if (abs(amount) > amountLC)
                    return;
                else
                    LoginDatabase.PExecute("UPDATE account SET vp = %u WHERE id = %u", amountLC - uint32(abs(amount)), field[0].GetUInt32());
            }
            else 
                LoginDatabase.PExecute("UPDATE account SET vp = vp + %u WHERE id = %u", amount, field[0].GetUInt32());
        }
    }
}

bool Lottery::hasLotteryPoints(Player *player, uint32 amount) 
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_ACCOUNT_BY_NAME);
    stmt->setString(0, player->GetName());
    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (result)
    {
        Field* field = result->Fetch();
        QueryResult lotteryCoins = LoginDatabase.PQuery("SELECT vp FROM account WHERE id = %u", field[0].GetUInt32());
        if (lotteryCoins) 
        {
            uint32 amountLC = lotteryCoins->Fetch()->GetUInt32();
            if (amountLC >= amount) 
                return true;
        }
    }
    return false;
}

void Lottery::modifySunwellPoints(Player * player, int32 amount)
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_ACCOUNT_BY_NAME);
    stmt->setString(0, player->GetName());
    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (result)
    {
        Field* field = result->Fetch();
        QueryResult sunwellCoins = LoginDatabase.PQuery("SELECT dp FROM account WHERE id = %u", field[0].GetUInt32());

        if (sunwellCoins) 
        {
            uint32 amountSC = sunwellCoins->Fetch()->GetUInt32();
            if (amount < 0) 
            {
                if (abs(amount) > amountSC)
                    return;
                else 
                    LoginDatabase.PExecute("UPDATE account SET dp = %u WHERE id = %u", amountSC - uint32(abs(amount)), field[0].GetUInt32());
            }
            else 
                LoginDatabase.PExecute("UPDATE account SET dp = dp + %u WHERE id = %u", amount, field[0].GetUInt32());
        }
    }
}

void Lottery::modifySunwellPoints(std::string name, int32 amount)
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_ACCOUNT_BY_NAME);
    stmt->setString(0, name);
    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (result)
    {
        Field* field = result->Fetch();
        QueryResult sunwellCoins = LoginDatabase.PQuery("SELECT dp FROM account WHERE id = %u", field[0].GetUInt32());
        if (sunwellCoins) 
        {
            uint32 amountSC = sunwellCoins->Fetch()->GetUInt32();
            if (amount < 0)
            {
                if (abs(amount) > amountSC)
                    return;
                else 
                    LoginDatabase.PExecute("UPDATE account SET dp = %u WHERE id = %u", amountSC - uint32(abs(amount)), field[0].GetUInt32());
            }
            else 
                LoginDatabase.PExecute("UPDATE account SET dp = dp + %u WHERE id = %u", amount, field[0].GetUInt32());
        }
    }
}

bool Lottery::hasSunwellPoints(Player * player, uint32 amount)
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_ACCOUNT_BY_NAME);
    stmt->setString(0, player->GetName());
    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (result)
    {
        Field* field = result->Fetch();
        QueryResult lotteryCoins = LoginDatabase.PQuery("SELECT dp FROM account WHERE id = %u", field[0].GetUInt32());

        if (lotteryCoins)
        {
            uint32 amountSC = lotteryCoins->Fetch()->GetUInt32();
            if (amountSC >= amount) 
                return true;
        }
    }
    return false;
}

void Lottery::showNumbers(Creature *pCreature, Player *player, LotteryType type) 
{
    QueryResult numbers = CharacterDatabase.PQuery("SELECT bet FROM %s WHERE guid = %u",dataBaseNames[type].c_str(), player->GetGUIDLow());
    std::stringstream numberStream;

    if (numbers)
    {
        numberStream << "Twoje liczby sa nastepujace: \n";
        do 
        {
            Field *field = numbers->Fetch();
            numberStream << field->GetString() << "\n";
        } while(numbers->NextRow());
    }
    else 
        numberStream << "Nie masz obstawionych zadnych liczb!";

    pCreature->MonsterWhisper(numberStream.str().c_str(), player);
}


