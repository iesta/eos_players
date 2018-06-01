#include "Players.hpp"

const int MAX_HEALTH = 10000;
const int DEFAULT_HEALTH = 1000;

namespace Oasis {
    using namespace eosio;
    using std::string;

    class Players : public contract {
        using contract::contract;
        
        public:
            Players(account_name self):contract(self) {}

            //@abi action
            void add(
              const account_name account, 
              string& username, 
              uint64_t level
            ) 
            {
                    require_auth(account);
                    playerIndex players(_self, _self);
                    auto iterator = players.find(account);
                    eosio_assert(iterator == players.end(), "Address for account already exists");
                    players.emplace(account, [&](auto& player) {
                        player.account_name = account;
                        player.username = username;
                        player.level = 1;
                        player.health_points = DEFAULT_HEALTH;
                        player.energy_points = 1000;
                        player.karma_points = 1000;

                  });   
            }

            //@abi action
            void update(  
                account_name account, 
                uint64_t level, 
                int64_t healthPoints, 
                int64_t energyPoints, 
                int64_t karmaPoints
              ) 
             
              {
                require_auth(account);

                playerIndex players(_self, _self);

                auto iterator = players.find(account);
                eosio_assert(iterator != players.end(), "Address for account not found");

                /**
                 * We add the new player in the table
                 * The first argument is the payer of the storage which will store the data
                */
                players.modify(iterator, account, [&](auto& player) {
                    player.level = level;

                    if ((player.health_points - healthPoints) < 0) {
                        player.health_points = 0;
                    } else {
                        player.health_points -= healthPoints;
                    }

                    if ((player.energy_points - energyPoints) < 0) {
                        player.energy_points = 0;
                    } else {
                        player.energy_points -= energyPoints;
                    }

                    if ((player.karma_points - karmaPoints) < 0) {
                        player.karma_points = 0;
                    } else {
                        player.karma_points -= karmaPoints;
                    }
                });
            }

            //@abi action
            void getplayer(const account_name account) {
                playerIndex players(_self, _self);
                auto iterator = players.find(account);
                eosio_assert(iterator != players.end(), "Address for account not found");
                auto currentPlayer = players.get(account);
                print("Username: ", 
                  currentPlayer.username.c_str(), 
                  " Level: ", currentPlayer.level, 
                  " Health: ", currentPlayer.health_points, 
                  " Energy: ", currentPlayer.energy_points,
                  " Karma: ", currentPlayer.karma_points);
                  ;
            }

            //@abi action
            void removeplayer(const account_name account) {
                require_auth(_self);
                playerIndex players(_self, _self);
                auto iterator = players.find(account);
                eosio_assert(iterator != players.end(), "Address for account not found");
                auto currentPlayer = players.get(account);
                print("Removing username: ", currentPlayer.username.c_str());
                players.erase(iterator);
            }

            //@abi action
            void countplayers() {
              require_auth(_self);
              uint32_t i = 0;
              playerIndex players(_self, _self);
              auto itr = players.begin();
              // eosio_assert(itr != players.end(), "No value in table: 0");
              if(itr != players.end()) {
                i = 0;
              } else {
                while (itr != players.end()) {
                  i++;
                  itr++;
                }
              } 
              print("#players: ", i);
            }

            void boosthealth(const account_name account, uint32_t points) {
              require_auth(_self);
              playerIndex players(_self, _self);
              auto iterator = players.find(account);
              eosio_assert(iterator != players.end(), "Address for account not found");
              players.modify(iterator, account, [&](auto& player) {
                uint32_t t = player.health_points + points;
                });
            }

            //@abi action
            void listplayers() {
              require_auth(_self);
              playerIndex players(_self, _self);
              print("Player list: ");
            }

            //@abi action
            void removeall() {
              require_auth(_self);
              playerIndex players(_self, _self);
              print("Remove all players");
              auto itr = players.begin();
              eosio_assert(itr != players.end(), "Table is empty");
              while (itr != players.end()) {
                  itr = players.erase(itr);
              }
            }

        private:

            //@abi table player i64
            struct player {
                uint64_t account_name;
                string username;
                uint64_t level;
                uint64_t health_points = 1000;
                uint64_t energy_points = 1000;
                uint64_t karma_points = 1000;

                uint64_t primary_key() const { return account_name; }

                EOSLIB_SERIALIZE(player, (account_name)(username)(level)(health_points)(energy_points)(karma_points))
            };

            typedef multi_index<N(player), player> playerIndex;
    };

    EOSIO_ABI(Players, (add)(update)(getplayer)(removeplayer)(countplayers)(listplayers)(removeall)(boosthealth))
}