#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Employer {
public:
    Employer(Employer* boss, int id, string* language_list) {
        this->boss = boss;
        this->id = id;
        this->language_list = language_list;
    }
    char getLanguage() {
        return language;
    }
    Employer* getBoss() {
        return boss;
    }

    void countBariers(vector<int>* barier_list) {
        Employer* curr_boss = boss;
        while (curr_boss != nullptr && curr_boss->getBoss() != nullptr)
        {
            if (curr_boss->getLanguage() != language) {
                ++barier_count;
                curr_boss = curr_boss->getBoss();
            }
            else {
                break;
            }
        }
        (*barier_list)[id] = barier_count;
        for (auto& employer : slaves)
        {
            employer->countBariers(barier_list);
        }
    }
    void takeSlaves() {
        int slave_id;
        while (true)
        {
            cin >> slave_id;

            if (slave_id == id) {
                return;
            }
            else {
                Employer* slave = new Employer(this, slave_id, language_list);
                slave->takeLanguage();
                slave->takeSlaves();
                slaves.push_back(slave);
            }
        }
    }
    void takeLanguage() {
        language = (*language_list)[id];
    }

private:
    int id = 0;
    int barier_count = 0;
    char language = 0;
    Employer* boss = nullptr;
    vector<Employer*> slaves;
    string* language_list = nullptr;
};

int main() {
    string out;
    string language_list;
    Employer bigg_boss(nullptr, 0, &language_list);    
    int slaves_num;
    language_list = "0";
    vector<int> barier_list;    

    cin >> slaves_num;
    barier_list.resize(slaves_num + 1, 0);

    for (int i = 0; i < slaves_num; i++)
    {
        char lang;
        cin >> lang;
        language_list += lang;
    }
    int trash;
    cin >> trash;
    bigg_boss.takeSlaves();

    bigg_boss.countBariers(&barier_list);

    out = "0";
    for (int i = 2; i < slaves_num + 1; ++i) {
        out += " " + std::to_string(barier_list[i]);
    }
    cout << out;
    return 0;
}
