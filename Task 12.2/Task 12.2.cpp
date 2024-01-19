#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <Windows.h>

using namespace std;
using namespace filesystem;

class Record
{
private:
    string name;
    string owner;
    string phone;
    string address;
    string activity;
public:
    Record(string name, string owner, string phone, string address, string activity)
    {
        this->name = name;
        this->owner = owner;
        this->phone = phone;
        this->address = address;
        this->activity = activity;
    }
    string get_name() { return name; }
    string get_owner() { return owner; }
    string get_phone() { return phone; }
    string get_activity() { return activity; }
    friend ostream& operator<<(ostream& out, Record& record)
    {
        out << "Название:\t\t" << record.name << endl;
        out << "Владелец:\t\t" << record.owner << endl;
        out << "Телефон:\t\t" << record.phone << endl;
        out << "Адрес:\t\t\t" << record.address << endl;
        out << "Род деятельности:\t" << record.activity << endl;
        return out;
    }
    void save_record()
    {
        path path_to_guide = current_path() += "\\Files";
        path_to_guide += "\\Guide.txt";
        ofstream file;
        file.open(path_to_guide, ios::app);
        file << name << endl;
        file << owner << endl;
        file << phone << endl;
        file << address << endl;
        file << activity << endl;
        file << endl;
        file.close();
    }
};

class Guide
{
private:
    vector<Record> records;
    void search_by_name()
    {
        string target;
        cout << "Введите текст для поиска: ";
        getline(cin, target);
        transform(target.begin(), target.end(), target.begin(), ::tolower);
        for (vector<Record>::iterator record = records.begin(); record != records.end(); record++)
        {
            string bufer = record->get_name();
            transform(bufer.begin(), bufer.end(), bufer.begin(), ::tolower);
            if (bufer.find(target) != bufer.npos) cout << *record << endl;
        }
        system("pause");
    }
    void search_by_owner()
    {
        string target;
        cout << "Введите текст для поиска: ";
        getline(cin, target);
        transform(target.begin(), target.end(), target.begin(), ::tolower);
        for (vector<Record>::iterator record = records.begin(); record != records.end(); record++)
        {
            string bufer = record->get_owner();
            transform(bufer.begin(), bufer.end(), bufer.begin(), ::tolower);
            if (bufer.find(target) != bufer.npos) cout << *record << endl;
        }
        system("pause");
    }
    void search_by_phone()
    {
        string target;
        cout << "Введите текст для поиска: ";
        getline(cin, target);
        transform(target.begin(), target.end(), target.begin(), ::tolower);
        for (vector<Record>::iterator record = records.begin(); record != records.end(); record++)
        {
            string bufer = record->get_phone();
            transform(bufer.begin(), bufer.end(), bufer.begin(), ::tolower);
            if (bufer.find(target) != bufer.npos) cout << *record << endl;
        }
        system("pause");
    }
    void search_by_activity()
    {
        string target;
        cout << "Введите текст для поиска: ";
        getline(cin, target);
        transform(target.begin(), target.end(), target.begin(), ::tolower);
        for (vector<Record>::iterator record = records.begin(); record != records.end(); record++)
        {
            string bufer = record->get_activity();
            transform(bufer.begin(), bufer.end(), bufer.begin(), ::tolower);
            if (bufer.find(target) != bufer.npos) cout << *record << endl;
        }
        system("pause");
    }
    void load_guide()
    {
        path path_to_guide = current_path() += "\\Files";
        path_to_guide += "\\Guide.txt";
        ifstream file;
        file.open(path_to_guide, ios::app);
        while (!file.eof())
        {
            string name;
            string owner;
            string phone;
            string address;
            string activity;
            getline(file, name);
            if(name=="\0") getline(file, name);
            if (name == "\0") break;
            getline(file, owner);
            getline(file, phone);
            getline(file, address);
            getline(file, activity);
            records.push_back(Record(name, owner, phone, address, activity));
        }
        file.close();
    }
    void add_record()
    {
        string name, owner, phone, address, activity;
        cout << "Введите название фирмы: ";
        getline(cin, name);
        cout << "Введите ФИО владельца: ";
        getline(cin, owner);
        cout << "Введите телефон фирмы: ";
        getline(cin, phone);
        cout << "Введите адрес фирмы: ";
        getline(cin, address);
        cout << "Введите род деятельности фирмы: ";
        getline(cin, activity);
        records.push_back(Record(name, owner, phone, address, activity));
        (records.end() - 1)->save_record();
        system("pause");
    }
    void show_guide()
    {
        for (vector<Record>::iterator record = records.begin(); record != records.end(); record++)
        {
            cout << *record << endl;
        }
        system("pause");
    }
public:
    Guide() { load_guide(); }
    void menu()
    {
        int command = 0;
        do
        {
            do
            {
                system("cls");
                cout << "1.\tПросмотреть все записи\n";
                cout << "2.\tДобавить запись\n";
                cout << "3.\tПоиск по названию\n";
                cout << "4.\tПоиск по владельцу\n";
                cout << "5.\tПоиск по номеру телефона\n";
                cout << "6.\tПоиск по роду деятельности\n\n";
                cout << "0.\tВыход\n\n";
                (cin >> command).get();
            } while (command < 0 or command > 6);
            switch (command)
            {
            case(1):show_guide();
                break;
            case(2):add_record();
                break;
            case(3):search_by_name();
                break;
            case(4):search_by_owner();
                break;
            case(5):search_by_phone();
                break;
            case(6):search_by_activity();
                break;
            default:cout << "Завершение работы...";
                break;
            }
        } while (command);
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Guide guide;
    guide.menu();

    return 0;
}
