#ifndef ROOM_H
#define ROOM_H
#include <string>
#include <vector>
enum RoomMode { SINGLE_ROOM=0, ONEONONE_ROOM, RANKING_ROOM, ROOMMODE_COUNT};
class Card{};
class Deck{};
class Desk{
public:
    Desk(Deck d1, Deck d2, std::string n1, std::string n2){}
};
class Player
{
public:
    Player(int id, std::string name, Deck deck) : _ID(id), _name(name), _deck(deck){}
    int getID() const { return _ID; }
    std::string getName() const { return _name; }
    Deck getDeck() const { return _deck; }
private:
    int _ID;
    std::string _name;
    Deck _deck;
};

class Room
{
public:
    Room(int id, std::string name, std::string word, Player* player);
    int getID() const { return _ID; }
    std::string getName() const { return _name; }
    std::vector<Player*> getPlayers() const { return _player; }
    bool isPasswordCorrect(std::string word) const { return _password=="" || _password==word; }
    virtual bool isFull() const =0;
    virtual bool addPlayer(Player* player)=0;
	virtual void startGame()=0;
protected:
    int _ID;
    std::string _name;
    std::string _password;
    std::vector<Player*> _player;
};
class OneOnOneRoom : public Room
{
public:
    OneOnOneRoom(int id, std::string name, std::string word, Player* player) : Room(id, name, word, player) {}
    bool isFull() const override { return _player.size()>=MaxPlayerNum; }
    bool addPlayer(Player* player) override;
	void startGame() override;
private:
    static constexpr short MaxPlayerNum=2;
};

class Arena
{
public:
    Arena();
    ~Arena();
    void enterRoom(int playerID, std::string playerName, Deck playerDeck, RoomMode mode);
    void createRoom(int playerID, std::string playerName, Deck playerDeck, RoomMode mode, std::string name, std::string password);
private:
    std::vector<Room*> _room[ROOMMODE_COUNT];
    void initArena();
    int getNonRepeatRandomRoomID(RoomMode mode);
    std::string getRandomString(RoomMode mode);
    std::string getNonRepeatRandomRoomName(RoomMode mode);
    void createRoom(Player* player, RoomMode mode, int id, std::string name, std::string password);
    void freeRoom();
};

#endif
