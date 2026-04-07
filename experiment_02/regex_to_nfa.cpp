#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct State {
    int id;
};

struct Transition {
    int from;
    char symbol;
    int to;
};

struct NFA {
    int start;
    int accept;
    vector<Transition> transitions;
};

int stateCount = 0;

// Create basic NFA for single character
NFA createBasicNFA(char symbol) {
    NFA nfa;
    nfa.start = stateCount++;
    nfa.accept = stateCount++;

    nfa.transitions.push_back({nfa.start, symbol, nfa.accept});
    return nfa;
}

// Concatenation
NFA concatenate(NFA first, NFA second) {
    NFA result;
    result.start = first.start;
    result.accept = second.accept;

    result.transitions = first.transitions;
    result.transitions.insert(result.transitions.end(),
                              second.transitions.begin(),
                              second.transitions.end());

    result.transitions.push_back({first.accept, '\0', second.start});
    return result;
}

// Union (|)
NFA unite(NFA first, NFA second) {
    NFA result;
    result.start = stateCount++;
    result.accept = stateCount++;

    result.transitions = first.transitions;
    result.transitions.insert(result.transitions.end(),
                              second.transitions.begin(),
                              second.transitions.end());

    result.transitions.push_back({result.start, '\0', first.start});
    result.transitions.push_back({result.start, '\0', second.start});
    result.transitions.push_back({first.accept, '\0', result.accept});
    result.transitions.push_back({second.accept, '\0', result.accept});

    return result;
}

// Kleene Star (*)
NFA kleeneStar(NFA nfa) {
    NFA result;
    result.start = stateCount++;
    result.accept = stateCount++;

    result.transitions = nfa.transitions;

    result.transitions.push_back({result.start, '\0', nfa.start});
    result.transitions.push_back({nfa.accept, '\0', nfa.start});
    result.transitions.push_back({result.start, '\0', result.accept});
    result.transitions.push_back({nfa.accept, '\0', result.accept});

    return result;
}

int main() {
    string regex;
    cout << "Enter Regular Expression (use . for concat, | for union, * for star): ";
    cin >> regex;

    stack<NFA> st;

    for (char c : regex) {
        if (isalpha(c)) {
            st.push(createBasicNFA(c));
        }
        else if (c == '.') {
            NFA second = st.top(); st.pop();
            NFA first = st.top(); st.pop();
            st.push(concatenate(first, second));
        }
        else if (c == '|') {
            NFA second = st.top(); st.pop();
            NFA first = st.top(); st.pop();
            st.push(unite(first, second));
        }
        else if (c == '*') {
            NFA top = st.top(); st.pop();
            st.push(kleeneStar(top));
        }
    }

    NFA result = st.top();

    cout << "\nNFA Transitions:\n";
    for (auto t : result.transitions) {
        cout << t.from << " -- " << t.symbol << " --> " << t.to << endl;
    }

    cout << "\nStart State: " << result.start << endl;
    cout << "Accept State: " << result.accept << endl;

    return 0;
}