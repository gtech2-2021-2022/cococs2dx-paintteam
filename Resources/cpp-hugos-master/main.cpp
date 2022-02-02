#include <iostream>
#include <windows.h>
#include "entities.h"
#include "map.h"
#include "item.h"

int main()
{
    srand(time(0));
    Player player;
    Map map;
    std::string _name;
    std::cout << "What's your player name ?\n";
    std::cin >> _name;
    player.setName(_name);
    system("CLS");
    player.setPlayerY(map.getPlayerY());
    player.setPlayerX(map.getPlayerX());
    std::string direction;
    std::string action;
    int monsterKilled = 0;
    int recoveredTreasures = 0;
    while (player.isAlive() && !(map.win()))
    {
        auto currentRoom = &map.getRoom(player.getPlayerY(), player.getPlayerX());
        system("CLS");
        std::cout << "------ Map ------\n\n" << map.stringRepresentation(player);
        if (currentRoom->hasMonster())
        {
            Monster* monster = currentRoom->getMonster();
            if (monster->getName() == "enderman")
            {
                std::cout << "Oops ! There is an " << monster->getName() << " blocking your way. You must kill him if you want to continue.\nDo you want to fight with him ? (y,n)\n";
            }
            else
            {
                std::cout << "Oops ! There is a " << monster->getName() << " blocking your way. You must kill him if you want to continue.\nDo you want to fight with him ? (y,n)\n";
            }
            do
            {
                std::cin >> action;
                if (!(action == "y" || "n"))
                {
                    std::cout << "Invalid choice, please retry.\n";
                }
            } while (!(action == "y" || "n"));
            if (action == "y")
            {
                if (player.getGold() > 5)
                {
                    std::cout << "You have " << player.getGold() << " gold. Do you want to use 5 gold to heal yourself ?\n";
                    do
                    {
                        std::cin >> action;
                        if (!(action == "y" || "n"))
                        {
                            std::cout << "Invalid choice, please retry.\n";
                        }
                    } while (!(action == "y" || "n"));
                    if (action == "y")
                    {
                        player.heal();
                    }
                }
                std::string playerName = player.GetName();
                playerName[0] = toupper(playerName[0]);
                std::string monsterName = monster->getName();
                monsterName[0] = toupper(monsterName[0]);
                while (player.isAlive() && monster->isAlive())
                {
                    std::cout << "You attack the " << monster->getName() << " and deal " << player.getWeaponDamage(player.getWeapon()) << " damage points.\n";
                    monster->receiveDammage(player.getWeaponDamage(player.getWeapon()));
                    if (monster->isAlive())
                    {
                        std::cout << "The " << monster->getName() << " attacks you and deals you " << monster->getDamage() - player.getDefense() << " damage points.\n\n";
                        player.receiveDammage(monster->getDamage() - player.getDefense());
                        std::cout << playerName << "'s life : " << player.getLife() << "\n";
                        std::cout << monsterName << "'s life : " << monster->getLife() << "\n\n";
                        Sleep(1000);
                    }
                    else
                    {
                        std::cout << "You killed the " << monster->getName() << " and got 3 gold.\n\n";
                        currentRoom->deleteMonster();
                        player.setGold(3);
                        monsterKilled++;
                        Sleep(1000);
                    }
                }
                if (!(player.isAlive()))
                {
                    std::cout << "The " << monster->getName() << " killed you. You lost.\n\n";
                    exit(0);
                }
            }
            else
            {
                if (direction == "n")
                {
                    player.setPlayerY(player.getPlayerY() + 1);
                }
                else if (direction == "s")
                {
                    player.setPlayerY(player.getPlayerY() - 1);
                }
                else if (direction == "e")
                {
                    player.setPlayerX(player.getPlayerX() - 1);
                }
                else if (direction == "w")
                {
                    player.setPlayerX(player.getPlayerX() + 1);
                }
                currentRoom = &map.getRoom(player.getPlayerY(), player.getPlayerX());
                system("CLS");
                std::cout << "------ Map ------\n\n" << map.stringRepresentation(player);
            }
        }
        if (currentRoom->hasWeapon())
        {
            std::cout << "Wow ! You just found a weapon ! Do you want to take it ? (y,n)\n";
            do
            {
                std::cin >> action;
                if (!(action == "y" || "n"))
                {
                    std::cout << "Invalid choice, please retry.\n";
                }
            } while (!(action == "y" || "n"));
            if (action == "y")
            {
                if (currentRoom->getWeaponName() == "Iron Sword")
                {
                    std::cout << "Wow ! You just found an " << currentRoom->getWeaponName() << " ! ";
                }
                else
                {
                    std::cout << "Wow ! You just found a " << currentRoom->getWeaponName() << " ! ";
                }
                currentRoom->takeWeapon(player);
            }
            else {
                std::cout << "\n";
            }
        }
        if (currentRoom->hasHelmet() || currentRoom->hasChestplate() || currentRoom->hasLegging() || currentRoom->hasBoots())
        {
            std::cout << "Wow ! You just found a piece of armor ! Do you want to take it ? (y,n)\n";
            do
            {
                std::cin >> action;
                if (!(action == "y" || "n"))
                {
                    std::cout << "Invalid choice, please retry.\n";
                }
            } while (!(action == "y" || "n"));
            if (action == "y")
            {
                if (currentRoom->hasHelmet())
                {
                    if (currentRoom->getArmorName(currentRoom->getHelmet()) == "Iron Helmet")
                    {
                        std::cout << "Wow ! You just found an " << currentRoom->getArmorName(currentRoom->getHelmet()) << " ! ";
                    }
                    else
                    {
                        std::cout << "Wow ! You just found a " << currentRoom->getArmorName(currentRoom->getHelmet()) << " ! ";
                    }
                    currentRoom->takeArmor(player, currentRoom->getHelmet());
                }
                else if (currentRoom->hasChestplate())
                {
                    if (currentRoom->getArmorName(currentRoom->getChestplate()) == "Iron Chestplate")
                    {
                        std::cout << "Wow ! You just found an " << currentRoom->getArmorName(currentRoom->getChestplate()) << " ! ";
                    }
                    else
                    {
                        std::cout << "Wow ! You just found a " << currentRoom->getArmorName(currentRoom->getChestplate()) << " ! ";
                    }
                    currentRoom->takeArmor(player, currentRoom->getChestplate());
                }
                else if (currentRoom->hasLegging())
                {
                    if (currentRoom->getArmorName(currentRoom->getLegging()) == "Iron Legging")
                    {
                        std::cout << "Wow ! You just found an " << currentRoom->getArmorName(currentRoom->getLegging()) << " ! ";
                    }
                    else
                    {
                        std::cout << "Wow ! You just found a " << currentRoom->getArmorName(currentRoom->getLegging()) << " ! ";
                    }
                    currentRoom->takeArmor(player, currentRoom->getLegging());
                }
                else if (currentRoom->hasBoots())
                {
                    if (currentRoom->getArmorName(currentRoom->getBoots()) == "Iron Boots")
                    {
                        std::cout << "Wow ! You just found an " << currentRoom->getArmorName(currentRoom->getBoots()) << " ! ";
                    }
                    else
                    {
                        std::cout << "Wow ! You just found a " << currentRoom->getArmorName(currentRoom->getBoots()) << " ! ";
                    }
                    currentRoom->takeArmor(player, currentRoom->getBoots());
                }
            }
            else
            {
                std::cout << "\n";
            }
        }
        if (currentRoom->hasTreasure())
        {
            std::cout << "Wow ! You just found a treasure ! Do you want to open it ? (y,n)\n";
            do
            {
                std::cin >> action;
                if (!(action == "y" || "n"))
                {
                    std::cout << "Invalid choice, please retry.\n";
                }
            } while (!(action == "y" || "n"));
            if (action == "y")
            {
                std::cout << "You opened the treasure and found " << currentRoom->getTreasureGold() << " gold.\n\n";
                currentRoom->takeTreasure(player);
                recoveredTreasures++;
            }
            else {
                std::cout << "\n\n";
            }
        }
        if (player.isAlive() && !(map.win()))
        {
            std::cout << "To see your inventory, press 'i' or press 'n' if you don't want.\n";
            do
            {
                std::cin >> action;
                if (!(action == "i" || "n"))
                {
                    std::cout << "Invalid choice, please retry.\n";
                }
            } while (!(action == "i" || "n"));
            if (action == "i")
            {
                std::cout << "\nLife : " << player.getLife() << "\n";
                std::cout << "Attack : " << player.getWeaponDamage(player.getWeapon()) << "\n";
                std::cout << "Defense : " << player.getDefense() << "\n";
                std::cout << "Weapon : " << player.getWeaponName(player.getWeapon()) << "\n";
                if (player.getHelmet() != nullptr)
                {
                    std::cout << "Helmet : " << player.getArmorName(player.getHelmet()) << "\n";
                }
                else {
                    std::cout << "Helmet :\n";
                }
                if (player.getChestplate() != nullptr)
                {
                    std::cout << "Chestplate : " << player.getArmorName(player.getChestplate()) << "\n";
                }
                else {
                    std::cout << "Chestplate :\n";
                }
                if (player.getLegging() != nullptr)
                {
                    std::cout << "Legging : " << player.getArmorName(player.getLegging()) << "\n";
                }
                else {
                    std::cout << "Legging :\n";
                }
                if (player.getBoots() != nullptr)
                {
                    std::cout << "Boots : " << player.getArmorName(player.getBoots()) << "\n\n";
                }
                else {
                    std::cout << "Boots :\n\n";
                }
            }
            else
            {
                std::cout << "\n";
            }
            std::string finalString;
            std::string tempString = "You have a room to the ";
            std::string tempString2 = " Where do you wan to go ? ";
            std::string tempString3;
            std::string tempString4;
            if (currentRoom->hasNorthLink())
            {
                tempString3 = "north";
                tempString4 = "(n";
            }
            if (currentRoom->hasSouthLink())
            {
                if (currentRoom->hasNorthLink())
                {
                    tempString3 = tempString3 + ", south";
                    tempString4 = tempString4 + ",s";
                }
                else
                {
                    tempString3 = tempString3 + "south";
                    tempString4 = tempString4 + "(s";
                }
            }
            if (currentRoom->hasEastLink())
            {
                if (currentRoom->hasNorthLink() || currentRoom->hasSouthLink())
                {
                    tempString3 = tempString3 + ", east";
                    tempString4 = tempString4 + ",e";
                }
                else
                {
                    tempString3 = tempString3 + "east";
                    tempString4 = tempString4 + "(e";
                }
            }
            if (currentRoom->hasWestLink())
            {
                if (currentRoom->hasNorthLink() || currentRoom->hasSouthLink() || currentRoom->hasEastLink())
                {
                    tempString3 = tempString3 + ", west";
                    tempString4 = tempString4 + ",w";
                }
                else
                {
                    tempString3 = tempString3 + "west";
                    tempString4 = tempString4 + "(w";
                }
            }
            tempString3 = tempString3 + ".";
            tempString4 = tempString4 + ")";
            finalString = tempString + tempString3 + tempString2 + tempString4;
            std::cout << finalString << "\n";
            std::cin >> direction;
            if (direction == "n" && currentRoom->hasNorthLink())
            {
                player.setPlayerY(player.getPlayerY() - 1);
            }
            else if (direction == "s" && currentRoom->hasSouthLink())
            {
                player.setPlayerY(player.getPlayerY() + 1);
            }
            else if (direction == "e" && currentRoom->hasEastLink())
            {
                player.setPlayerX(player.getPlayerX() + 1);
            }
            else if (direction == "w" && currentRoom->hasWestLink())
            {
                player.setPlayerX(player.getPlayerX() - 1);
            }
            else
            {
                std::cout << "Invalid direction, please retry.\n";
            }
        }
    }
    std::cout << "Congratulation ! You win !\n\n";
    std::cout << "Monsters killed : " << monsterKilled << "\n";
    std::cout << "Treasures recovered : " << recoveredTreasures << "\n\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
