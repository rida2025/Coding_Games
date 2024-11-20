#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

typedef struct zombie_detail{
    int id;
    int current_x;
    int current_y;
    int next_x;
    int next_y;
} zombie;

typedef struct human_detail{
    int id;
    int current_x;
    int current_y;
} human;

pair<int, int> get_target(map<int, human> human_list, map<int, zombie> zombie_list, int x, int y) {
    pair<int, int> result = {-1, -1};

    for (const auto& human_entry : human_list) {
        bool state = true;
        const human& h = human_entry.second;
        float human_distance_sq = sqrt(pow(h.current_x - x, 2) + pow(h.current_y - y, 2));
        float hero_steps = human_distance_sq / 1000 -2;
        
        for (const auto& zombie_entry : zombie_list) {
            const zombie& z = zombie_entry.second;
            float zombie_distance_sq = sqrt(pow(z.current_x - h.current_x, 2) + pow(z.current_y - h.current_y, 2));
            float zombie_steps = zombie_distance_sq / 400;
            cerr << h.id << " " << hero_steps << " " << z.id << " " << zombie_steps << endl;
            if (hero_steps > zombie_steps){
                state = false;
                break ;
            }
        }
        if (state == true){
            result.first = h.current_x;
            result.second = h.current_y;
            return (result);
        }
    }
    return result;
}


int main()
{
    pair<int, int> position;
    while (1) {
        int x;
        int y;
        cin >> x >> y; cin.ignore();
        int human_count;
        cin >> human_count; cin.ignore();
        map<int, human> human_list;
        for (int i = 0; i < human_count; i++) {
            int human_id;
            int human_x;
            int human_y;
            cin >> human_id >> human_x >> human_y; cin.ignore();
            human h = {human_id, human_x, human_y};
            human_list[human_id] = h;
        }
        int zombie_count;
        cin >> zombie_count; cin.ignore();
        map<int, zombie> zombie_list;
        for (int i = 0; i < zombie_count; i++) {
            int zombie_id;
            int zombie_x;
            int zombie_y;
            int zombie_xnext;
            int zombie_ynext;
            cin >> zombie_id >> zombie_x >> zombie_y >> zombie_xnext >> zombie_ynext; cin.ignore();
            zombie z = {zombie_id, zombie_x, zombie_y,zombie_xnext, zombie_ynext};
            zombie_list[zombie_id] = z;
        }
        position = get_target(human_list, zombie_list, x, y);
        cout << position.first << " " << position.second << endl;
    }
}