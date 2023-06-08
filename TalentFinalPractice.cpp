#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

struct Info{
    int ID;
    bool TypePlay;
    int Play;
    double Money;
};

class cBinaryOption{
    protected:
        int id;
    public:
        virtual int getType() = 0;
        virtual int getID() = 0;
};

class Dealer : public cBinaryOption{
    private:
        double AccountBalance;
    public:
        void setAccountBalance(int value){
            AccountBalance = value;
        };

        int getType(){
            return 1;
        };

        int getID(){
            return id;
        }
};

class Decoy: public cBinaryOption{
    private:
        int inviteID;
    public:
        void setInviteID(int invID){
            inviteID = invID;
        };

        int getType(){
            return 2;
        };
        
        void setID(int newID){
            id = newID;
        }

        int getID(){
            return id;
        }

        int getInviteID(){
            return inviteID;
        }
};

class Trader : public cBinaryOption{
    private:
        double AccountBalance;
        int typePlay;
    public:
        void setAccountBalance(int value){
            AccountBalance = value;
        };

        int getAccountBalance(){
            return AccountBalance;
        };

        int getType(){
            return 3;
        };

        int getID(){
            return id;
        }
};

int main(){
    int n, m; 
    cin >> n >> m;
    vector <cBinaryOption*> a(n);
    map <int, double> curMoney;
    int idNC = 0;
    for (int i = 0; i < n; ++i){
        int id, type, info; cin >> id >> type >> info;
        switch (type){
            case 1:
                a[i] = new Dealer;
                ((Dealer*)a[i]) -> setAccountBalance(info);
                idNC = id;
                curMoney[idNC] = info;
                break;
            case 2:
                a[i] = new Decoy;
                ((Decoy*)a[i]) -> setInviteID(info);
                ((Decoy*)a[i]) -> setID(id);
                break;
            case 3:
                a[i] = new Trader;
                ((Trader*)a[i]) -> setAccountBalance(info);
                curMoney[id] = info;
                break;
        }
    }
    
    map <int, int> prev;    
    vector <Info> Player;
    map <int, double> cost;
    for (int i = 1; i <= m; ++i){
        int id; Player.clear();
        while (true){
            cin >> id;
            if (id == -1) break;
            bool typePlay; int go, money; 
            cin >> typePlay >> go >> money;
            Info p;
            p.ID = id;
            p.TypePlay = typePlay;
            p.Play = go;
            p.Money = money;
            Player.push_back(p);
        }

        if (id == -1){
            double cnt_up = 0, cnt_down = 0; 
            for (auto p : Player){
                if (p.TypePlay == 0){
                    if (p.Play == 1) cnt_up += p.Money * 2;
                      else cnt_down += p.Money * 2;
                    prev[p.ID] = p.Play;
                }

                if (p.TypePlay == 1){
                    double hs = 1.5;
                    int cur = prev[p.ID];

                    // case 1: Down -> Up
                    if (cur == 1){
                        cnt_up += p.Money * hs;
                        prev[p.ID] = 1;
                    }

                    // case 0: Up / Down -> Up / Down
                    if (cur == 0){
                        if (prev[p.ID] == 0){
                            cnt_down += p.Money * hs;
                        } else {
                            cnt_up += p.Money * hs;
                        }
                    }

                    // case -1: Down -> Up
                    if (cur == -1){
                        cnt_down += p.Money * hs;
                        prev[p.ID] = 0;
                    }
                }
            }

            bool turnNC;
            if (cnt_up < cnt_down){
                turnNC = 1;
            } else {
                turnNC = 0;
            }

            for (auto p : Player){
                if (curMoney[p.ID] < p.Money) continue;
                cost[p.ID] += p.Money * 0.01;
                if (p.TypePlay == 0){
                    if (p.Play != turnNC){
                        curMoney[p.ID] -= p.Money;
                        curMoney[idNC] += p.Money - (p.Money * 0.01);
                    } else {
                        double j = p.Money * 0.01;
                        curMoney[p.ID] += p.Money - j;
                        curMoney[idNC] -= p.Money;
                    }
                }

                if (p.TypePlay == 1){
                    if (prev[p.ID] != turnNC){
                        curMoney[p.ID] -= p.Money;
                        curMoney[idNC] += p.Money - (p.Money * 0.01);
                    } else {
                        double j = p.Money * 0.5 * 0.01;
                        curMoney[p.ID] += p.Money * 0.5 - j;
                        curMoney[idNC] += (p.Money * 0.5 - j) * 0.01;

                    }
                }
            }
        }
    }  
    
    vector <pair <int, double> > result;
    for (auto i : curMoney){
        result.push_back({i.first, i.second});
    }

    for (int i = 0; i < n; ++i){
        if (a[i] -> getType() == 2){
            int idx = a[i] -> getID();
            result.push_back({idx, cost[((Decoy*)a[i]) -> getInviteID()]});
        }
    }

    sort(result.begin(), result.end());

    for (auto i : result){
        cout << i.first << ' ' << i.second << endl;
    }

    return 0;
}

/*
==================================================+
INPUT                                             |
--------------------------------------------------|
5 3
1 1 100
2 3 100
3 3 100
4 2 2
5 2 3
2 0 0 20
3 0 1 30
-1
2 0 0 100
3 0 1 30
-1
2 1 1 30
3 1 1 30
-1
--------------------------------------------------|
==================================================+
OUTPUT                                            |
--------------------------------------------------|
1 208.4
2 19.8
3 69.7
4 1.2
5 0.9
--------------------------------------------------|
==================================================+
*/