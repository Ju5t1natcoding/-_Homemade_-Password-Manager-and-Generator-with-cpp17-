/**
    Frățeanu Iustin-Alexandru
**/
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <windows.h>
#include <conio.h>
#include "xor_crypto.hpp"
#include "sha_crypto.hpp"
///#include "aes_crypto.hpp"
using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using ull = unsigned ll;
using i128 = __int128;
using sint = short int;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vpi = vector<pii>;
using vpl = vector<pll>;
template<typename T>
using vvector = vector<vector<T>>;
template<typename K, typename V>
using umap = unordered_map<K, V>;
template<typename T>
using uset = unordered_set<T>;
template<typename T>
using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename A, typename B>
using vp = vector<pair<A, B>>;
#define FAST ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#define all(v) begin(v), end(v)
#define rall(v) rbegin(v), rend(v)
#define pb push_back
#define pf push_front
#define eb emplace_back
#define ef emplace_front
#define pob pop_back
#define pof pop_front
#define fs first
#define sd second
#define inf 0x3f3f3f3f
#define infll 0xfffffffffffffff
#define sz(v) (int)v.size()

static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void clearScreen() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD written;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD cells = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hConsole, ' ', cells, {0,0}, &written);
    SetConsoleCursorPosition(hConsole, {0,0});
}

void setColor(WORD attributes) {
    SetConsoleTextAttribute(hConsole, attributes);
}

void setCursorPos(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(hConsole, coord);
}

int getKey() {
    int c = _getch();

    if (c == 0 || c == 224) {
        int arrow = _getch();

        switch (arrow) {
            case 72:
                return -1; ///sus
            case 80:
                return 1; ///jos
            case 75:
                return -2; ///stanga
            case 77:
                return 2; ///dreapta
        }
    }

    return c;
}

const string s1 = "abcdefghijklmnopqrstuvwxyz";
const string s2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string s3 = "0123456789";
const string s4 = "!@#$%^&*()-_=+[]{};:,.<>?";

int lg;
bool lm, lM, cif, simb;
string ans;
vector<string> v;

string password_gen() {
    string s = (lm ? s1 : "") + (lM ? s2 : "") + (cif ? s3 : "") + (simb ? s4 : "");

    if (s.empty()) {
        return "";
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, sz(s) - 1);

    string rez;
    for (int i = 0; i < lg; ++i) {
        rez += s[dist(gen)];
    }

    return rez;
}

string lower(const string& s) {
    string t = s;
    for (int i = 0; i < sz(t); ++i) {
        t[i] = tolower(t[i]);
    }

    return t;
}

void XOR(const string& s) {
    setCursorPos(3, 11);
    cout << "Introduceti master password pentru criptare (scurta): ";
    string master;
    getline(cin, master);
    string blob = xor_encrypt_blob(s, master);
    string hexblob = to_hex(blob);
    time_t now = time(nullptr);
    tm* lt = localtime(&now);
    ostringstream oss;
    oss << hexblob << "|1|Salvat pe data de: " << put_time(lt, "%d/%m/%Y %H:%M:%S") << "\n";
    v.pb(oss.str());
    setCursorPos(3, 12);
    cout << "Parola salvata cu succes! Apasati orice tasta ca sa va intoarceti la meniul principal.";
    int key = getKey();
    return;
}

void SHA(const string& s) {
    setCursorPos(3, 11);
    cout << "ATENTIE: SHA-256 este ireversibil (nu poate sa fie recuperata parola). Doresti sa continui operatiunea? (Y / N) ";
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    string ans;
    getline(cin, ans);

    if (lower(ans) == "y") {
        string stored = sha256_store_format(s);
        time_t now = time(nullptr);
        tm* lt = localtime(&now);
        ostringstream oss;
        oss << stored << "|2|Salvat pe data de: " << put_time(lt, "%d/%m/%Y %H:%M:%S") << "\n";
        v.pb(oss.str());
        setCursorPos(3, 12);
        cout << "Parola salvata cu succes! Acest entry nu se mai poate recupera. Apasati orice tasta ca sa va intoarceti la meniul principal.";
        int key = getKey();
        return;
    }

    setCursorPos(3, 12);
    cout << "Operatiune abandonata. Apasati orice tasta ca sa va intoarceti la meniul principal.";
    int key = getKey();
}

///void AES(const string& s) {
///    cout << "Introduceti master password pentru decriptare (folosit pentru a deriva cheia): ";
///    string master;
///    getline(cin, master);
///    string hexblob = aes_encrypt_with_password_hex(s, master);
///    time_t now = time(nullptr);
///    tm* lt = localtime(&now);
///    ostringstream oss;
///    oss << hexblob << "|3|Salvat pe data de: " << put_time(lt, "%d/%m/%Y %H:%M:%S") << "\n";
///    v.pb(oss.str());
///}

void save(const string& s) {
    clearScreen();
    setCursorPos(1, 1);
    setColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "==== SALVARE PAROLA ====";
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    setCursorPos(3, 3);
    cout << "Doriti sa salvati parola prin criptare (mai sigur)? (Y / N) ";
    string ans;
    getline(cin, ans);

    if (lower(ans) == "y") {
        vector<string> opts = {"1. Cifru XOR cu salt aleator", "2. SHA-256 cu salt"/**, "3. AES-256"**/};
        int selectat = 0;

        while (true) {
            clearScreen();
            setCursorPos(3, 3);
            cout << "Alege metoda de criptare:";

            for (int i = 0; i < sz(opts); ++i) {
                if (i == selectat) {
                    setCursorPos(1, 4 + i);
                    setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                    cout << ">";
                } else {
                    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }

                setCursorPos(5, 4 + i);
                cout << opts[i] << "\n";
            }

            int key = getKey();

            if (key == -1 && selectat) {
                selectat--;
            } else if (key == 1 && selectat + 1 < sz(opts)) {
                selectat++;
            } else if (key == 13) {
                switch (selectat) {
                    case 0:
                        XOR(s);
                        break;
                    case 1:
                        SHA(s);
///                    break;
///                case 2:
///                   AES(s);
                }

                return;
            }
        }
    } else {
        time_t now = time(nullptr);
        tm* lt = localtime(&now);
        ostringstream oss;
        oss << s << "|0|Salvat pe data de: " << put_time(lt, "%d/%m/%Y %H:%M:%S") << "\n";
        v.pb(oss.str());
        setCursorPos(3, 5);
        cout << "Parola salvata cu succes! Apasati orice tasta ca sa va intoarceti la meniul principal.";
        int key = getKey();
        return;
    }
}

void generare() {
    clearScreen();
    setCursorPos(1, 1);
    setColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "==== GENERARE PAROLA ====";
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    setCursorPos(3, 3);
    cout << "Bine ati venit! Va rugam sa introduceti lungimea parolei: ";
    cin >> lg;
    setCursorPos(3, 5);
    cout << "Acum va rugam sa marcati cu un raspuns simplu de da (marcat cu " << '"' << "Y" << '"' <<") sau nu (marcat cu " << '"' << "N" << '"' <<") la intrebarile de mai jos:";
    setCursorPos(3, 7);
    cout << "1. Poate parola sa contina litere mici?";
    setCursorPos(3, 8);
    cin.ignore();
    getline(cin, ans);

    if (lower(ans) == "y" || lower(ans) == "da") {
        lm = true;
    } else {
        lm = false;
    }

    setCursorPos(3, 10);
    cout << "2. Poate parola sa contina litere mari?";
    setCursorPos(3, 11);
    getline(cin, ans);

    if (lower(ans) == "y" || lower(ans) == "da") {
        lM = true;
    } else {
        lM = false;
    }

    setCursorPos(3, 13);
    cout << "3. Poate parola sa contina cifre?";
    setCursorPos(3, 14);
    getline(cin, ans);

    if (lower(ans) == "y" || lower(ans) == "da") {
        cif = true;
    } else {
        cif = false;
    }

    setCursorPos(3, 16);
    cout << "4. Poate parola sa contina simboluri?";
    setCursorPos(3, 17);
    getline(cin, ans);

    if (lower(ans) == "y" || lower(ans) == "da") {
        simb = true;
    } else {
        simb = false;
    }

    string pswrd = password_gen();
    setCursorPos(3, 19);

    if (pswrd != "") {
        cout << "Parola generata dupa criteriile dumneavoastra este: " << pswrd << ". Doriti sa o salvati? (Y / N)";
        setCursorPos(3, 20);
        getline(cin, ans);

        if (lower(ans) == "y") {
            save(pswrd);
        } else {
            setCursorPos(3, 22);
            cout << "Doriti sa generati o noua parola?\n(Y / N)";
            getline(cin, ans);

            if (lower(ans) == "y") {
                generare();
                return;
            } else {
                return;
            }
        }
    } else {
        cout << "Parola nu a putut fi generata din cauza invalibilitatii campurilor de selectie. Incercati din nou? (Y / N)";
        setCursorPos(3, 20);
        getline(cin, ans);

        if (lower(ans) == "n") {
            return;
        } else {
            generare();
            return;
        }
    }
}

void af(int x) {
    string t = "";
    bool ok = true;
    char c;

    for (int i = 0; i < sz(v[x]); ++i) {
        if (v[x][i] == '|') {
            if (v[x][i + 1] == '2') {
                ok = false;
            } else {
                c = v[x][i + 1];
            }

            break;
        }

        t += v[x][i];
    }

    if (!ok) {
        cout << "Parola indescifrabila. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
        int key = getKey();
        return;
    }

    if (c == '0') {
        cout << "Parola: " << t << "\n";
        this_thread::sleep_for(chrono::seconds(5 + sz(t) / 10));
        return;
    } else {
        cout << "Introduceti master password pentru decriptare: ";
        string master;
        getline(cin, master);
        string blob = from_hex(t);
        string s = xor_decrypt_blob(blob, master);

        if (s == "") {
            cout << "Eroare: parola master gresita sau blob corupt.";
            int key = getKey();
            return;
        } else {
            cout << "Parola: " << s << "\n";
            this_thread::sleep_for(chrono::seconds(5 + sz(s) / 10));
            return;
        }
    }
}

void sel(int& x) {
    int selectat = 0;
    vector<string> opts = {"1. Stergere parola", "2. Afisare parola"};

    while (true) {
        clearScreen();
        setCursorPos(1, 1);
        setColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        cout << "==== MANAGER DE PAROLE ====";
        setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        setCursorPos(3, 3);
        cout << "Pentru a iesi din acest meniu apasati tasta ESC(Escape).";
        setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        setCursorPos(3, 4);
        cout << "Ati selectat parola numarul " << x + 1 << ". Ce doriti sa faceti?";

        for (int i = 0; i < sz(opts); ++i) {
            if (i == selectat) {
                setCursorPos(1, 5 + i);
                setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << ">";
            } else {
                setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }

            setCursorPos(4, 5 + i);
            cout << opts[i] << "\n";
        }

        int key = getKey();

        if (key == -1 && selectat) {
            selectat--;
        } else if (key == 1 && selectat + 1 < sz(opts)) {
            selectat++;
        } else if (key == 13) {
            switch (selectat) {
                case 0:
                    v.erase(begin(v) + selectat);

                    if (x) {
                        x--;
                    }

                    return;
                case 1:
                    af(x);
            }
        } else if (key == 27) {
            return;
        }
    }
}

void adauga() {
    while (true) {
        clearScreen();
        setCursorPos(1, 1);
        setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "==== ADAUGARE PAROLA ====";
        setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        setCursorPos(3, 3);
        cout << "Doriti sa adaugati o parola? (Y / N) ";
        getline(cin, ans);
        setCursorPos(3, 5);

        if (lower(ans) == "y") {
            cout << "Introduceti parola pe care doriti sa o adaugati: ";
            string s;
            getline(cin, s);
            setCursorPos(3, 7);
            cout << "Doriti sa salvati parola prin criptare (mai sigur)? (Y / N) ";
            getline(cin, ans);

            if (lower(ans) == "y") {
                vector<string> opts = {"1. Cifru XOR cu salt aleator", "2. SHA-256 cu salt"/**, "3. AES-256"**/};
                int selectat = 0;

                while (true) {
                    clearScreen();
                    setCursorPos(3, 3);
                    cout << "Alege metoda de criptare:";

                    for (int i = 0; i < sz(opts); ++i) {
                        if (i == selectat) {
                            setCursorPos(1, 4 + i);
                            setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                            cout << ">";
                        } else {
                            setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                        }

                        setCursorPos(5, 4 + i);
                        cout << opts[i] << "\n";
                    }

                    int key = getKey();

                    if (key == -1 && selectat) {
                        selectat--;
                    } else if (key == 1 && selectat + 1 < sz(opts)) {
                        selectat++;
                    } else if (key == 13) {
                        switch (selectat) {
                            case 0:
                                XOR(s);
                                break;
                            case 1:
                                SHA(s);
        ///                    break;
        ///                case 2:
        ///                   AES(s);
                        }

                        return;
                    }
                }
            } else {
                time_t now = time(nullptr);
                tm* lt = localtime(&now);
                ostringstream oss;
                oss << s << "|0|Salvat pe data de: " << put_time(lt, "%d/%m/%Y %H:%M:%S") << "\n";
                v.pb(oss.str());
                setCursorPos(3, 5);
                cout << "Parola salvata cu succes! Apasati orice tasta ca sa va intoarceti la meniul principal.";
                int key = getKey();
                return;
            }
        } else {
            cout << "Operatiue finalizata! Apasati orice tasta pentru a reveni la meniul principal.";
            int key = getKey();
            return;
        }
    }
}

void MeniuM() {
    int selectat = 0;

    while (true) {
        if (v.empty()) {
            return;
        }

        clearScreen();
        setCursorPos(1, 1);
        setColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        cout << "==== MANAGER DE PAROLE ====";
        setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        setCursorPos(3, 3);
        cout << "Pentru a iesi din acest meniu apasati tasta ESC(Escape).";
        setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        setCursorPos(3, 4);
        cout << "Lista parolelor salvate:";

        for (int i = 0; i < sz(v); ++i) {
            if (i == selectat) {
                setCursorPos(1, 5 + i);
                setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << ">";
            } else {
                setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }

            setCursorPos(4, 5 + i);
            string t = "";

            for (char c : v[i]) {
                if (c == '|') {
                    break;
                }

                t += c;
            }

            cout << t << "\n";
        }

        int key = getKey();

        if (key == -1 && selectat) {
            selectat--;
        } else if (key == 1 && selectat + 1 < sz(v)) {
            selectat++;
        } else if (key == 13) {
            sel(selectat);
        } else if (key == 27) {
            return;
        }
    }
}

signed main() {
    int selectat = 0;
    vector<string> opts = {"1. Generare parola", "2. Adauga parola", "3. Manageriaza parole", "3. Inchidere program"};
    ifstream fin("parole.txt");

    string s;
    while (getline(fin, s)) {
        if (s != "") {
            v.pb(s + "\n");
        }
    }

    while (true) {
        clearScreen();
        setCursorPos(1, 1);
        setColor(FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "==== MANAGER SI GENERATOR DE PAROLE ====";
        setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        setCursorPos(3, 3);
        cout << "Folositi tastele sageata sus/jos pentru navigare si ENTER pentru selectare";

        for (int i = 0; i < sz(opts); ++i) {
            if (i == selectat) {
                setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                setCursorPos(1, 5 + i);
                cout << ">";
            } else {
                setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }

            setCursorPos(4, 5 + i);
            cout << opts[i] << "\n";
        }

        int key = getKey();

        if (key == -1 && selectat) {
            selectat--;
        } else if (key == 1 && selectat + 1 < sz(opts)) {
            selectat++;
        } else if (key == 13) {
            switch (selectat) {
                case 0:
                    generare();
                    break;
                case 1:
                    adauga();
                    break;
                case 2:
                    MeniuM();
                    break;
                case 3:
                    clearScreen();
                    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    ofstream fout("parole.txt");

                    for (string& s : v) {
                        fout << s;
                    }

                    fout.close();
                    exit(0);
            }
        }
    }
}
