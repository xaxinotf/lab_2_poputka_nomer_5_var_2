#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

struct Automaton {
    int numInputs;
    int numStates;
    int initialState;
    std::unordered_set<int> finalStates;
    std::unordered_map<int, std::unordered_map<char, int>> transitions;
};

void DFS(int state, Automaton &automaton, std::unordered_set<int> &visited) {
    visited.insert(state);
    for (auto &transition : automaton.transitions[state]) {
        int next_state = transition.second;
        if (visited.find(next_state) == visited.end()) {
            DFS(next_state, automaton, visited);
        }
    }
}

int main() {
    // Read from file
    std::ifstream file("test.txt");
    if (!file.is_open()) {
        std::cerr << "Unable to open file.\n";
        return 1;
    }

    Automaton automaton;

    file >> automaton.numInputs;
    file >> automaton.numStates;
    file >> automaton.initialState;
    int numFinalStates;
    file >> numFinalStates;
    for (int i = 0; i < numFinalStates; i++) {
        int state;
        file >> state;
        automaton.finalStates.insert(state);
    }

    int s, s_prime;
    char a;
    while (file >> s >> a >> s_prime) {
        automaton.transitions[s][a] = s_prime;
    }
    file.close();

    // Identify unreachable states
    std::unordered_set<int> visited;
    DFS(automaton.initialState, automaton, visited);

    std::cout << "Unreachable States: ";
    for (int i = 0; i < automaton.numStates; i++) {
        if (visited.find(i) == visited.end()) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;

    // Identify deadlock states
    std::cout << "Deadlock States: ";
    for (int i = 0; i < automaton.numStates; i++) {
        if (automaton.transitions.find(i) == automaton.transitions.end()) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;

    return 0;
}
