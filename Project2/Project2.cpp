#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
struct DETAL {
    string NAME;
    string SORT;
    int DATE[3];  
    int QUANT;
    double COST;
};

void printDetal(const DETAL& detal) {
    cout << "Name: " << detal.NAME << endl;
    cout << "Product grade: " << detal.SORT << endl;
    cout << "Date of manufacture: " << detal.DATE[0] << '.' << detal.DATE[1] << '.' << detal.DATE[2] << endl;
    cout << "Quantity: " << detal.QUANT << endl;
    cout << "Unit price: " << detal.COST << endl;
}

void readDetal(ifstream& file, DETAL& detal) {
    file >> detal.NAME >> detal.SORT >> detal.DATE[0] >> detal.DATE[1] >> detal.DATE[2] >> detal.QUANT >> detal.COST;
}

void writeDetal(ofstream& file, const DETAL& detal) {
    file << detal.NAME << ' ' << detal.SORT << ' ' << detal.DATE[0] << ' ' << detal.DATE[1] << ' ' << detal.DATE[2] << ' ' << detal.QUANT << ' ' << detal.COST << '\n';
}

void editRecord(vector<DETAL>& database, int recordIndex) {
    if (recordIndex < 0 || recordIndex >= database.size()) {
        cout << "Incorrect record index." << endl;
        return;
    }

    cout << "Enter new data to correct the record:" << endl;

    DETAL newDetal;
    cout << "Name: ";
    cin >> newDetal.NAME;
    cout << "Product grade: ";
    cin >> newDetal.SORT;
    cout << "Date of manufacture (day month year): ";
    cin >> newDetal.DATE[0] >> newDetal.DATE[1] >> newDetal.DATE[2];
    cout << "Quantity: ";
    cin >> newDetal.QUANT;
    cout << "Unit price: ";
    cin >> newDetal.COST;

    database[recordIndex] = newDetal;

    cout << "The entry was successfully edited." << endl;
}

void searchByField(const vector<DETAL>& database, const string& fieldName, const string& value) {
    bool found = false;

    for (const DETAL& detal : database) {
        if (fieldName == "NAME" && detal.NAME == value) {
            printDetal(detal);
            found = true;
        }
        else if (fieldName == "SORT" && detal.SORT == value) {
            printDetal(detal);
            found = true;
        }
        else if (fieldName == "DATE" && (to_string(detal.DATE[0]) + "." + to_string(detal.DATE[1]) + "." + to_string(detal.DATE[2])) == value) {
            printDetal(detal);
            found = true;
        }
        else if (fieldName == "QUANT" && to_string(detal.QUANT) == value) {
            printDetal(detal);
            found = true;
        }
        else if (fieldName == "COST" && to_string(detal.COST) == value) {
            printDetal(detal);
            found = true;
        }
    }

    if (!found) {
        cout << "No records were found for the specified field." << endl;
    }
}

void addRecord(vector<DETAL>& database) {
    DETAL newDetal;
    cout << "Enter the data for the new record:" << endl;
    cout << "Name: ";
    cin >> newDetal.NAME;
    cout << "Product grade: ";
    cin >> newDetal.SORT;
    cout << "Date of manufacture (day month year): ";
    cin >> newDetal.DATE[0] >> newDetal.DATE[1] >> newDetal.DATE[2];
    cout << "Quantity: ";
    cin >> newDetal.QUANT;
    cout << "Unit price: ";
    cin >> newDetal.COST;

    database.push_back(newDetal);

    cout << "The new entry was successfully added." << endl;
}

void deleteRecord(vector<DETAL>& database, int recordIndex) {
    if (recordIndex < 0 || recordIndex >= database.size()) {
        cout << "Incorrect record index." << endl;
        return;
    }

    database.erase(database.begin() + recordIndex); // видалаяє елемент за вказаним індкесом

    cout << "The record was successfully deleted." << endl;
}

int main() {
    vector<DETAL> database;
    ifstream inputFile("database.txt");
    if (!inputFile.is_open()) {
        cerr << "Error opening a database file." << endl;
        return 1;
    }

    while (true) {
        DETAL detal;
        readDetal(inputFile, detal);
        if (inputFile.eof()) { // eof перевіряє чи досягнуто кінець файлу 
        }
        database.push_back(detal);
    }

    inputFile.close();

    int choice;
    do {
        cout << "\nSelect an option:" << endl;
        cout << "1. Print all records\n";
        cout << "2. Edit the selected entry\n";
        cout << "3. Search by field\n";
        cout << "4. Add a new entry\n";
        cout << "5. Delete the selected entry\n";
        cout << "0. Exit.\n";
        cin >> choice;

        if (choice == 1) {
            cout << "\nAll records in the database:\n";
            for (const DETAL& detal : database) {
                printDetal(detal);
                cout << "---------------------------\n";
            }
        }
        else if (choice == 2) {
            int editIndex;
            cout << "Enter the index of the record you want to edit: ";
            cin >> editIndex;
            editRecord(database, editIndex);
        }
        else if (choice == 3) {
            cout << "Enter the search field (NAME, SORT, DATE, QUANT, COST): ";
            string fieldName;
            cin >> fieldName;
            cout << "Enter a value to search for: ";
            string value;
            cin >> value;
            searchByField(database, fieldName, value);
        }
        else if (choice == 4) {
            addRecord(database);
        }
        else if (choice == 5) {
            int deleteIndex;
            cout << "Enter the index of the record to delete: ";
            cin >> deleteIndex;
            deleteRecord(database, deleteIndex);
        }
        else if (choice == 0) {
            cout << "The program has completed its work.\n";
        }
        else {
            cout << "Incorrect selection. Please try again.\n";
        }

    } while (choice != 0);

    ofstream outputFile("database.txt");
    if (!outputFile.is_open()) {
        cerr << "Error opening a database file for writing." << endl;
        return 1;
    }

    for (const DETAL& detal : database) {
        writeDetal(outputFile, detal);
    }

    outputFile.close();
    return 0;
}


