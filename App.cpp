#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

struct Currency
{
    string name;
    float value;
};

struct Balance
{
    Currency currency;
    float amount;
};

class Account
{
public:
    Balance balance[50];
    string username;
};

class AgiotageAccount : public Account {};

class Wallet
{
private:
    Currency currency[50];
    int currency_num;
    int account_num;
    Account account[50];
    AgiotageAccount agiotage;

public:
    Wallet();
    void addCurrency(string name, float value);
    void addAccount(float amounts[], string username);
    void set_agiotage_account(float amounts[], string username);
    int check_to_have_money(Account account, string name, float amount);
    int check_to_have_account(string username);
    int find_currency_index(string name);
    void WITHDRAW(string name, string username, float amount);
    void DEPOSIT(string name, string username, float amount);
    void EXCHANGE(string name1, string name2, string username, float amount);
    void TRANSFER(string username1, string username2, float amount, string name);
    void REPORT(string username);
    void show_datas();
    void update_class_datas();
    void update_files_datas();
    bool is_agiotage_account(string username);
    void log_file(string output);
    int get_currency_num();
    int get_account_num();
};

// ---------------------------------------------------------------- WALLET ----------------------------------------------------------------

Wallet ::Wallet()
{
    currency_num = 0;
    account_num = 0;
    ofstream newfile;
    newfile.open("log.txt");
    newfile.close();
}

void Wallet :: addCurrency(string name, float value)
{
    currency[currency_num].name = name;
    currency[currency_num].value = value;
    currency_num++;
}

void Wallet :: addAccount(float amounts[], string username)
{
    account[account_num].username = username;
    for (int i = 0; i < currency_num; i++)
    {
        account[account_num].balance[i].amount = amounts[i];
        account[account_num].balance[i].currency.name = currency[i].name;
        account[account_num].balance[i].currency.value = currency[i].value;
    }
    account_num++;
}

void Wallet :: set_agiotage_account(float amounts[], string username)
{
    agiotage.username = username;
    for (int i = 0; i < currency_num; i++)
    {
        agiotage.balance[i].amount = amounts[i];
        agiotage.balance[i].currency.name = currency[i].name;
        agiotage.balance[i].currency.value = currency[i].value;
    }
}

int Wallet :: check_to_have_money(Account account, string name, float amount)
{
    for (int i = 0; i < currency_num; i++)
    {
        if (currency[i].name == name)
        {
            if (account.balance[i].amount >= amount)
                return i;
            break;
        }
    }
    return -1;
}

int Wallet ::check_to_have_account(string username)
{
    for (int i = 0; i < account_num; i++)
    {
        if (account[i].username == username)
            return i;
    }
    return -1;
}

int Wallet :: find_currency_index(string name)
{
    for (int i = 0; i < currency_num; i++)
    {
        if (currency[i].name == name)
            return i;
    }
    return -1;
}

bool Wallet :: is_agiotage_account(string username) {
    if (agiotage.username == username) return true;
    return false;
}

void Wallet :: WITHDRAW(string name, string username, float amount)
{
    int account_index, currency_index;
    account_index = check_to_have_account(username);
    currency_index = find_currency_index(name);
    string query = username + " WITHDRAW " + username + " " + name + " " + to_string(int(amount));

    if (account_index != -1)
    {
        if (check_to_have_money(account[account_index], name, amount) != -1)
        {
            account[account_index].balance[currency_index].amount -= amount;
            agiotage.balance[currency_index].amount += amount;
            log_file(query + " 1");
        }
        else
            log_file(query + " 0");

    }
    else
        log_file(query + " 0");

}

void Wallet :: DEPOSIT(string name, string username, float amount)
{
    int account_index, currency_index;
    account_index = check_to_have_account(username);
    currency_index = find_currency_index(name);

    string query = username + " DEPOSIT " + username + " " + name + " " + to_string(int(amount));


    if (account_index != -1)
    {
        if (check_to_have_money(agiotage, name, amount) != -1)
        {
            agiotage.balance[currency_index].amount -= amount;
            account[account_index].balance[currency_index].amount += amount;
            log_file(query + " 1");
        }
        else
            log_file(query + " 0");
    }
    else
        log_file(query + " 0");
}

void Wallet :: EXCHANGE(string name1, string name2, string username, float amount)
{
    int account_index, currency1_index, currency2_index;
    account_index = check_to_have_account(username);
    currency1_index = find_currency_index(name1);
    currency2_index = find_currency_index(name2);
    float transfer_cash = amount * currency[currency1_index].value / currency[currency2_index].value;
    string query = username + " EXCHANGE " + username + " " + name1 + " "  + name2 + " " + to_string(int(amount));

    if (account_index != -1)
    {
        if (amount <= 1000)
        {
            if (check_to_have_money(account[account_index], name1, amount * 1.01) != -1)
            {
                if (check_to_have_money(agiotage, name2, transfer_cash) != -1)
                {
                    account[account_index].balance[currency1_index].amount -= amount * 1.01;
                    agiotage.balance[currency1_index].amount += amount * 1.01;
                    agiotage.balance[currency2_index].amount -= transfer_cash;
                    account[account_index].balance[currency2_index].amount += transfer_cash;
                    log_file(query + " 1");
                }
                else
                    log_file(query + " 0");
            }
            else
                log_file(query + " 0");
        }
        else
        {
            float dec_cash = amount + 10 / currency[currency1_index].value;
            if (check_to_have_money(account[account_index], name1, dec_cash) != -1)
            {
                if (check_to_have_money(agiotage, name2, transfer_cash) != -1)
                {
                    account[account_index].balance[currency1_index].amount -= dec_cash;
                    agiotage.balance[currency1_index].amount += dec_cash;
                    agiotage.balance[currency2_index].amount -= transfer_cash;
                    account[account_index].balance[currency2_index].amount += transfer_cash;
                    log_file(query + " 1");
                }
                else
                    log_file(query + " 0");
            }
            else
                log_file(query + " 0");
        }
    }
    else
        log_file(query + " 0");
}

void Wallet ::TRANSFER(string username1, string username2, float amount, string name)
{
    int account1_index, currency_index, account2_index;
    account1_index = check_to_have_account(username1);
    account2_index = check_to_have_account(username2);
    currency_index = find_currency_index(name);
    string query = " TRANSFER" + username1 + " " + username2 + " " + name + " " + to_string(int(amount));

    if (account1_index != -1)
    {
        if (account2_index != -1)
        {
            if (amount <= 100)
            {
                if (check_to_have_money(account[account1_index], name, amount * 1.1) != -1)
                {
                    account[account1_index].balance[currency_index].amount -= amount * 1.1;
                    account[account2_index].balance[currency_index].amount += amount;
                    agiotage.balance[currency_index].amount += amount * 0.1;
                    log_file(username1 + query + " 1");
                    log_file(username2 + query + " 1");
                }
                else {
                    log_file(username1 + query + " 0");
                    log_file(username2 + query + " 0");
                }
            }
            else
            {
                float dec_cash = amount + 10 / currency[currency_index].value;
                if (check_to_have_money(account[account1_index], name, dec_cash) != -1)
                {
                    account[account1_index].balance[currency_index].amount -= dec_cash;
                    account[account2_index].balance[currency_index].amount += amount;
                    agiotage.balance[currency_index].amount += 10 / currency[currency_index].value;
                    log_file(username1 + query + " 1");
                    log_file(username2 + query + " 1");
                }
                else {
                    log_file(username1 + query + " 0");
                    log_file(username2 + query + " 0");
                }
            }
        }
        else {
            log_file(username1 + query + " 0");
            log_file(username2 + query + " 0");
        }
    }
    else {
        log_file(username1 + query + " 0");
        log_file(username2 + query + " 0");
    }
}

void Wallet :: REPORT(string username) {
    ifstream report;
    report.open("log.txt");
    string line;
    while (getline(report, line)) {
        if (line.find(username) != string::npos) {
            cout << line << endl;
        }
    }
    report.close();
}

void Wallet :: show_datas()
{
    for (int i = 0; i < currency_num; i++)
    {
        cout << setprecision(2) << fixed << agiotage.balance[i].amount;
        if (i != currency_num - 1)
            cout << " ";
        else
            cout << endl;
    }
    for (int j = 0; j < account_num; j++)
    {
        for (int i = 0; i < currency_num; i++)
        {
            cout << std::setprecision(2) << fixed << account[j].balance[i].amount;
            if (i != currency_num - 1)
                cout << " ";
            else
                cout << endl;
        }
    }
}

void Wallet ::update_class_datas()
{

    // clean datas
    currency_num = 0;
    account_num = 0;

    // get currencies
    ifstream fin;
    fin.open("currencies.txt");
    while (!fin.eof())
    {
        string tmp_name = "";
        float tmp_value = 0;
        fin >> tmp_name >> tmp_value;
        if (tmp_value != 0 && tmp_name != "")
            addCurrency(tmp_name, tmp_value);
    }
    fin.close();

    // get accounts
    ifstream currencies_fin[currency_num];
    // open currencies files
    for (int i = 0; i < currency_num; i++)
    {
        currencies_fin[i].open("currencies/" + currency[i].name + ".txt");
    }
    // data for agiotage
    float tmp_amounts[currency_num];
    string tmp_username;
    for (int i = 0; i < currency_num; i++)
    {
        currencies_fin[i] >> tmp_username >> tmp_amounts[i];
    }
    set_agiotage_account(tmp_amounts, tmp_username);
    // data for accounts
    while (!currencies_fin[0].eof())
    {
        float tmp_amounts[currency_num];
        string tmp_username;
        for (int i = 0; i < currency_num; i++)
        {
            currencies_fin[i] >> tmp_username >> tmp_amounts[i];
        }
        if (tmp_username != "")
            addAccount(tmp_amounts, tmp_username);
    }
    // close currencies files
    for (int i = 0; i < currency_num; i++)
    {
        currencies_fin[i].close();
    }
}

void Wallet ::update_files_datas()
{

    // update currencies files
    ofstream fout;
    fout.open("currencies.txt");
    for (int i = 0; i < currency_num; i++)
    {
        fout << currency[i].name << " " << round(currency[i].value) << endl;
    }
    fout.close();

    // update each currency with accounts
    ofstream currencies_fout[currency_num];
    // open currencies files
    for (int i = 0; i < currency_num; i++)
    {
        currencies_fout[i].open("currencies/" + currency[i].name + ".txt");
    }
    // data for agiotage
    for (int i = 0; i < currency_num; i++)
    {
        currencies_fout[i] << agiotage.username << " " << agiotage.balance[i].amount << endl;
    }
    // data for accounts
    for (int j = 0; j < account_num; j++)
    {
        for (int i = 0; i < currency_num; i++)
        {
            currencies_fout[i] << account[j].username << " " << account[j].balance[i].amount << endl;
        }
    }
    // close currencies files
    for (int i = 0; i < currency_num; i++)
    {
        currencies_fout[i].close();
    }
}

void Wallet :: log_file(string output) {
    FILE *f = fopen("log.txt", "a");
    fprintf(f, "%s\n", output.c_str());
    fclose(f);
}

int Wallet :: get_account_num() {
    return account_num;
}

int Wallet :: get_currency_num() {
    return currency_num;
}

// ---------------------------------------------------------------- RSA ALGORITHM ----------------------------------------------------------------

long int bmm(int x, int y)
{
    if (y == 0)
        return x;
    return bmm(y, x % y);
}

int oiler(int num)
{
    int answer = 1;
    for (int i = 2; i < num; i++)
    {
        int tmp = bmm(i, num);
        if (tmp == 1)
            answer++;
    }
    return answer;
}

void RSA_pu(char input[], int e, int n, long long answer[16])
{
    for (int i = 0; i < 16; i++)
    {
        long long po = 1;
        for (long long j = 0; j < e; j++)
        {
            po *= input[i];
            po = po % n;
        }
        answer[i] = po;
    }
}

void RSA_pr(char answer[], int d, int n, long long input[], int size)
{
    for (int i = 0; i < size; i++)
    {
        long long po = 1;
        for (long long j = 0; j < d; j++)
        {
            po *= input[i];
            po = po % n;
        }
        answer[i] = po;
    }
}

void hash_func(char input[], char *answer) {
    for (int i = 0; input[i] != '\0'; i++) {
        input[i] = (char) ((((int) (input[i]) * 3 + 17) % 26) + 65);
    }
    for (int i = 0; i < 16; i++) {
        int sum = 0;
        for (int j = 0; input[j] != '\0'; j++) {
            if (j % 16 == i) {
                sum += input[j];
            }
        }
        answer[i] = (sum % 26) + 65;
    }
    answer[16] = '\0';
}

long long n_generator() {
    long long primes_list[25] = {227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 503, 509, 599};
    long long n;
    int reapet = 0;
    while (1 > 0)
    {
        n = primes_list[rand() % 25] * primes_list[rand() % 25];
        ifstream users;
        users.open("users.txt");
        while (!users.eof())
        {
            string tmp1, tmp2, tmp3;
            long long file_n;
            users >> tmp1 >> tmp2 >> tmp3 >> file_n;
            if (file_n == n) reapet = 1;
            if (reapet) break;
        }
        users.close();
        if (!reapet) break;
    }
    return n;
}

int main()
{
    Wallet my_wallet;
    my_wallet.update_class_datas();
    int choise;

    cout << "<<------------------------------------>>\n" << endl;
    cout << "Sign Up:(1)\nLog In:(2)\nExit:(3)\n\n";
    cin >> choise;
    cout << "<<------------------------------------>>\n" << endl;
    while (choise != 3) {

        // log in part
        if (choise == 2) {
            string username;
            int is_loged_in = 0;
            char password[50], hash_input_password[16];
            cout << "Please Enter Your Username: ";
            cin >> username;
            cout << "Please Enter Your Password: ";
            cin >> password;
            password[sizeof(password)] = '\0';
            hash_func(password, hash_input_password);
            string input_hash_password = hash_input_password;

            // open users and check we have id with this password
            ifstream users;
            users.open("users.txt");
            while (!users.eof()) {
                string file_username;
                char file_hash_password[16];
                long long e, n;
                users >> file_username >> file_hash_password >> e >> n;
                if (username == file_username & string(file_hash_password) == input_hash_password) {

                    
                    // break loop
                    cout << "\nTo EXIT Please ENTER 0" << endl;
                    while (1 > 0) {

                        // get Query
                        string operation, input_username, name_or_username[2];
                        float amount;
                        cin >> operation;
                        // break loop
                        if (operation == "0") break;
                        if (operation == "DEPOSIT") 
                        {
                            cin >> input_username >> name_or_username[0];
                            cin >> amount;
                        } 
                        else if (operation == "EXCHANGE" || operation == "TRANSFER")
                        {
                            cin >> input_username >> name_or_username[0] >> name_or_username[1];
                            cin >> amount;
                        } 
                        else 
                        {
                            cin >> input_username >> name_or_username[0];
                            cin >> amount;
                        }
                        
                        // update class datats
                        my_wallet.update_class_datas();
                        // methods        
                        cout << operation << " " << input_username << " " << name_or_username[0] << " " << amount << endl;
                        if (operation == "DEPOSIT" && my_wallet.is_agiotage_account(username)) 
                            my_wallet.DEPOSIT(name_or_username[0], input_username, amount);
                        else if (operation == "WITHDRAW")
                            my_wallet.WITHDRAW(name_or_username[0], input_username, amount);
                        else if (operation == "EXCHANGE")
                            my_wallet.EXCHANGE(name_or_username[0], name_or_username[1], input_username, amount);
                        else if (operation == "TRANSFER")
                            my_wallet.TRANSFER(input_username, name_or_username[0], amount, name_or_username[1]);
                        else if (operation == "REPORT") 
                            my_wallet.REPORT(input_username);
                        else
                        {
                            cout << "Invalid Command" << endl;
                            continue;
                        }
                        
                        // update file datas
                        my_wallet.update_files_datas();
                    }
                    is_loged_in = 1;
                    break;
                }
            }
            if (!is_loged_in) cout << "Please Sign Up\n";
            users.close();
            
        } 

        // Sign Up Part
        else if (choise == 1) {
            string new_username;
            char new_password[100];
            cout << "Please Enter Your New Username: ";
            cin >> new_username;
            cout << "Please Enter Your New Password: ";
            cin >> new_password;

            long long n = n_generator();
            long long n_oiler = oiler(n);
            long long e, d;
            // compute e
            for (int i = 2; i < n_oiler; i++)
            {
                int tmp = bmm(i, n_oiler);
                if (tmp == 1)
                {
                    e = i;
                    break;
                }
            }
            // compute d
            float tmp = 1;
            while (1 > 0)
            {
                double tmp2 = (tmp * n_oiler + 1) / e;
                long long tmp3 = tmp2;
                if ((double)(tmp3) == tmp2)
                {
                    d = tmp3;
                    break;
                }
                tmp++;
            }
            cout << "\nYour Private key: " << d << endl;
            cout << "Your Public key: " << e << endl;

            // add to Wallet
            float amounts[my_wallet.get_currency_num()];
            for (int i = 0; i < my_wallet.get_currency_num(); i++) {
                amounts[i] = 0;
            }
            my_wallet.addAccount(amounts, new_username);

            // add to users.txt
            FILE *users = fopen("users.txt", "a");
            char hash_password[16];
            hash_func(new_password, hash_password);
            fprintf(users, "%s %s %lld %lld\n", new_username.c_str(), hash_password, e, n);
            fclose(users);

            // add to each currency file
            ifstream currency;
            currency.open("currencies.txt");
            while(!currency.eof()) {
                string currency_name = "currencies/", tmp, tmp_currency_name;
                currency >> tmp_currency_name >> tmp;
                if (tmp_currency_name != "") {
                    currency_name += tmp_currency_name + ".txt";
                    FILE *each_currency = fopen(currency_name.c_str(), "a");
                    fprintf(each_currency, "%s 0", new_username.c_str());
                    fclose(each_currency);
                }
            }
            currency.close();
        }

        cout << "\n<<------------------------------------>>\n" << endl;
        cout << "Sign Up:(1)\nLog In:(2)\nExit:(3)\n\n";
        cin >> choise;
        cout << "<<------------------------------------>>\n" << endl;
    }

    return 0;
}