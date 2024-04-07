#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

int main() {
    ifstream fin(R"(resources/input.txt)");
    ofstream fout(R"(resources/output.txt)");

    int nr_states;
    fin >> nr_states;

    unordered_map<int, int> normalization;
    for (int i = 1; i <= nr_states; i++) {
        int state;
        fin >> state;

        normalization[state] = i;
    }

    int nr_transitions;
    fin >> nr_transitions;

    unordered_map<char, unordered_map<int, int>> transitions;
    for (int i = 1; i <= nr_transitions; i++) {
        int start, end;
        char symbol;

        fin >> start >> end >> symbol;
        transitions[symbol][normalization[start]] = normalization[end];
    }

    int initial_state;
    fin >> initial_state;
    initial_state = normalization[initial_state];

    int nr_final_states;
    fin >> nr_final_states;

    unordered_map<int, bool> final_states;
    for (int i = 1; i <= nr_final_states; i++) {
        int state;
        fin >> state;

        final_states[normalization[state]] = true;
    }

    int nr_words;
    fin >> nr_words;

    for (int i = 1; i <= nr_words; i++) {
        string word;
        fin >> word;

        bool accepted = true;

        int current_state = initial_state;
        for (char &a: word) {
            current_state = transitions[a][current_state];

            if (current_state == 0) {
                accepted = false;
                break;
            }
        }

        if (!final_states[current_state])
            accepted = false;

        fout << (accepted ? "DA" : "NU") << "\n";
    }


    return 0;
}
