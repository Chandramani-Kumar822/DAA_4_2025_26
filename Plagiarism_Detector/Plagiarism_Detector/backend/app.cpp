#include <bits/stdc++.h>
using namespace std;

// ---------------- Normalize ----------------
string normalize(string text) {
    for (char &c : text) {
        if (isupper(c)) c = tolower(c);
        if (!isalnum(c) && c != ' ') c = ' ';
    }
    return text;
}

// ---------------- Read File ----------------
string readFile(string filename) {
    ifstream file(filename);
    if (!file) return "";

    string content, line;
    while (getline(file, line)) content += line + " ";

    return normalize(content);
}

// ---------------- Split Words ----------------
vector<string> getWords(string text) {
    vector<string> words;
    stringstream ss(text);
    string w;
    while (ss >> w) words.push_back(w);
    return words;
}

// ---------------- K-grams ----------------
vector<string> createKgrams(vector<string> &words, int k) {
    vector<string> res;
    if (words.size() < k) return res;

    for (int i = 0; i + k <= words.size(); i++) {
        string s = "";
        for (int j = 0; j < k; j++)
            s += words[i + j] + " ";
        res.push_back(s);
    }
    return res;
}

// ---------------- Hash ----------------
long long hashString(const string &s) {
    long long h = 0;
    for (char c : s) h = h * 31 + c;
    return h;
}

// ---------------- Similarity ----------------
double computeSimilarity(vector<string> &s1, vector<string> &s2) {
    unordered_set<long long> st;

    for (auto &s : s1)
        st.insert(hashString(s));

    int match = 0;
    for (auto &s : s2)
        if (st.count(hashString(s))) match++;

    int total = s1.size() + s2.size();
    if (total == 0) return 0;

    return (2.0 * match) / total * 100;
}

// ---------------- KMP ----------------
vector<int> computeLPS(string pat) {
    vector<int> lps(pat.size(), 0);
    for (int i = 1, len = 0; i < pat.size();) {
        if (pat[i] == pat[len]) lps[i++] = ++len;
        else if (len) len = lps[len - 1];
        else lps[i++] = 0;
    }
    return lps;
}

int KMP(string text, string pat) {
    if (pat.empty()) return 0;

    vector<int> lps = computeLPS(pat);
    int i = 0, j = 0, count = 0;

    while (i < text.size()) {
        if (text[i] == pat[j]) { i++; j++; }

        if (j == pat.size()) {
            count++;
            j = lps[j - 1];
        } else if (i < text.size() && text[i] != pat[j]) {
            if (j) j = lps[j - 1];
            else i++;
        }
    }
    return count;
}

// ---------------- Rabin-Karp ----------------
int rabinKarp(string text, string pat) {
    if (pat.empty()) return 0;

    int d = 256, q = 101;
    int m = pat.size(), n = text.size();

    if (n < m) return 0;

    int p = 0, t = 0, h = 1;

    for (int i = 0; i < m - 1; i++)
        h = (h * d) % q;

    for (int i = 0; i < m; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + text[i]) % q;
    }

    int count = 0;

    for (int i = 0; i <= n - m; i++) {
        if (p == t && text.substr(i, m) == pat)
            count++;

        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;
            if (t < 0) t += q;
        }
    }
    return count;
}

// ---------------- Boyer-Moore ----------------
int boyerMoore(string text, string pat) {
    if (pat.empty()) return 0;

    unordered_map<char, int> bad;
    for (int i = 0; i < pat.size(); i++)
        bad[pat[i]] = i;

    int n = text.size(), m = pat.size();
    int shift = 0, count = 0;

    while (shift <= n - m) {
        int j = m - 1;

        while (j >= 0 && pat[j] == text[shift + j])
            j--;

        if (j < 0) {
            count++;
            shift += (shift + m < n) ? m - bad[text[shift + m]] : 1;
        } else {
            shift += max(1, j - bad[text[shift + j]]);
        }
    }
    return count;
}

// ---------------- SMART MATCH ----------------
vector<string> getMatches(string t1, string t2) {

    auto w1 = getWords(t1);
    auto w2 = getWords(t2);

    auto k3_1 = createKgrams(w1, 3);
    auto k3_2 = createKgrams(w2, 3);

    unordered_set<string> s1(k3_1.begin(), k3_1.end());
    unordered_set<string> s2(k3_2.begin(), k3_2.end());

    vector<string> res;

    for (auto &x : s1)
        if (s2.count(x)) res.push_back(x);

    if (!res.empty()) return res;

    auto k2_1 = createKgrams(w1, 2);
    auto k2_2 = createKgrams(w2, 2);

    s1 = unordered_set<string>(k2_1.begin(), k2_1.end());
    s2 = unordered_set<string>(k2_2.begin(), k2_2.end());

    for (auto &x : s1)
        if (s2.count(x)) res.push_back(x);

    if (!res.empty()) return res;

    unordered_set<string> wset1(w1.begin(), w1.end());
    unordered_set<string> wset2(w2.begin(), w2.end());

    for (auto &w : wset1)
        if (wset2.count(w) && w.length() > 4)
            res.push_back(w);

    return res;
}

// ---------------- MAIN ----------------
int main(int argc, char* argv[]) {

    int n = argc - 1;

    vector<string> texts;
    vector<vector<string>> shingles;

    for (int i = 1; i <= n; i++) {
        string text = readFile(argv[i]);
        texts.push_back(text);

        auto words = getWords(text);
        shingles.push_back(createKgrams(words, 3));
    }

    vector<vector<double>> matrix(n, vector<double>(n));

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {

            double sim;

            if (i == j) sim = 100;
            else sim = computeSimilarity(shingles[i], shingles[j]);

            matrix[i][j] = matrix[j][i] = sim;
        }
    }

    // -------- OUTPUT --------
    cout << "{ \"matrix\": [";

    for (int i = 0; i < n; i++) {
        cout << "[";
        for (int j = 0; j < n; j++) {
            cout << fixed << setprecision(2) << matrix[i][j];
            if (j != n - 1) cout << ",";
        }
        cout << "]";
        if (i != n - 1) cout << ",";
    }

    cout << "], \"matches\": {";

    bool first = true;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {

            auto matches = getMatches(texts[i], texts[j]);

            if (!first) cout << ",";
            cout << "\"" << i << "-" << j << "\":[";

            for (int k = 0; k < matches.size(); k++) {
                cout << "\"" << matches[k] << "\"";
                if (k != matches.size() - 1) cout << ",";
            }

            cout << "]";
            first = false;
        }
    }

    cout << "}, \"algorithms\": {";

    first = true;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {

            string pattern = (texts[i].size() > 50) ? texts[i].substr(0, 30) : texts[i];

            int kmp = KMP(texts[j], pattern);
            int rk = rabinKarp(texts[j], pattern);
            int bm = boyerMoore(texts[j], pattern);

            if (!first) cout << ",";
            cout << "\"" << i << "-" << j << "\":{";
            cout << "\"KMP\":" << kmp << ",";
            cout << "\"RabinKarp\":" << rk << ",";
            cout << "\"BoyerMoore\":" << bm << "}";

            first = false;
        }
    }

    cout << "} }";

    return 0;
}