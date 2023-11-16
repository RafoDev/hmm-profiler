#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

vector<int> indentifyMatchingStates(vector<string> &sequences)
{
    int threshold = sequences.size() / 2;
    int seqLength = sequences[0].size();
    vector<int> matchingStates;
    for (int col = 0; col < seqLength; col++)
    {
        int residueCount = 0;
        for (auto &seq : sequences)
        {
            if (seq[col] != '-')
                ++residueCount;
        }
        if (residueCount > threshold)
        {
            matchingStates.push_back(col);
        }
    }
    return matchingStates;
}

int main()
{
    vector<string> sequences = {
        "VGA--HAGEY",
        "V----NVDEV",
        "VEA--DVAGH",
        "VKG------D",
        "VYS--TYETS",
        "FNA--NIPKH",
        "IAGADNGAGY"};

    vector<int> matchingStates = indentifyMatchingStates(sequences);
    int states = matchingStates.size();

    cout << "* Cantidad de estados: " << states << '\n';
    int i = 0;
    for (; i < states - 1; i++)
    {
        int state = matchingStates[i];
        int nextState = matchingStates[i + 1];

        cout << "* State " << state << '\n';
        int seqLength = sequences.size();
        map<char, int> transFreq;
        for (auto &seq : sequences)
        {
            if (seq[state] != '-')
            {
                transFreq[seq[state]]++;
            }
        }

        transFreq['0'] = 0;
        cout << " - Emission Probabilities:\n";
        for (auto freq : transFreq)
        {
            cout << "   - residue: " << freq.first << " freq: " << freq.second + 1 << "/" << seqLength + 20 << '\n';
        }
        cout << " - Transition Probabilities:\n";
        int matchProbs = 0;
        int insertProbs = 0;
        int eliminationProbs = 0;
        for (auto &seq : sequences)
        {
            if (seq[state] != '-' && seq[nextState] != '-')
                matchProbs++;
            if (
                (seq[state] == '-' && seq[nextState] != '-') ||
                (seq[state] != '-' && seq[nextState] == '-'))
            {
                eliminationProbs++;
            }
        }
        for (int idx = state + 1; idx < nextState; ++idx)
        {
            for (auto &seq : sequences)
            {
                if (seq[idx] != '-' && find(matchingStates.begin(), matchingStates.end(), idx) == matchingStates.end())
                {
                    insertProbs++;
                    break;
                }
            }
        }
        cout << "   - Match to Match: " << matchProbs + 1 << "/" << sequences.size() + 3 << '\n';
        cout << "   - Match to Insert: " << insertProbs + 1 << "/" << sequences.size() + 3 << '\n';
        cout << "   - Match to Delete: " << eliminationProbs + 1 << "/" << sequences.size() + 3 << '\n';
    }
    i += 1;
    int state = matchingStates[i];
    cout << "* State " << state << '\n';
    int seqLength = sequences.size();
    map<char, int> transFreq;
    for (auto &seq : sequences)
    {
        if (seq[state] != '-')
        {
            transFreq[seq[state]]++;
        }
    }

    transFreq['0'] = 0;
    cout << " - Emission Probabilities:\n";
    for (auto freq : transFreq)
    {
        cout << "   - residue: " << freq.first << " freq: " << freq.second + 1 << "/" << seqLength + 20 << '\n';
    }
    return 0;
}