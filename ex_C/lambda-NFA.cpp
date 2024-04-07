#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>

const int MAX_CYCLES = 1000000;

using namespace std;
int main() {
    ifstream fin(R"(resources/input.txt)");
    ofstream fout(R"(resources/output.txt)");

    int nr_states;
    fin >> nr_states;

    for (int i = 1; i <= nr_states; i++) {
        int state;
        fin >> state;
    }

    int nr_transitions;
    fin >> nr_transitions;

    unordered_map<char, unordered_map<int, vector<int>>> transitions;
    for (int i = 1; i <= nr_transitions; i++) {
        int start, end;
        char symbol;

        fin >> start >> end >> symbol;
        transitions[symbol][start].push_back(end);
    }

    int initial_state;
    fin >> initial_state;

    int nr_final_states;
    fin >> nr_final_states;

    unordered_map<int, bool> final_states;
    for (int i = 1; i <= nr_final_states; i++) {
        int state;
        fin >> state;

        final_states[state] = true;
    }

    int nr_words;
    fin >> nr_words;

    for (int i = 1; i <= nr_words; i++) {
        string word;
        fin >> word;

        bool accepted = false;
        int cycles = 0;

        queue<pair<int, int>> path;
        path.emplace(initial_state, 0);

        while (!path.empty()) {
            pair<int, int> current = path.front();
            path.pop();

            int current_state = current.first, position = current.second;

            if (position == word.length() && final_states[current_state]) {
                accepted = true;
                break;
            }

            if (cycles > MAX_CYCLES)
                break;

            for (int &next_state: transitions[word[position]][current_state])
                path.emplace(next_state, position + 1);

            for (int &next_state: transitions['0'][current_state])
                path.emplace(next_state, position);

            cycles += 1;
        }

        fout << (accepted ? "DA" : "NU") << "\n";
    }

    return 0;
}
