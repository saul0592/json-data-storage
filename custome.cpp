#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace std;



struct customer
    {
        string name;
        string adress;
        double acount_Balance ;
    };
void save_JsonDoc(const customer& cust);
void open_and_read_Json(json& data);
void showMenu();
void option1();
void option2();
void modify_account(int number_account_reference);
void option_3();

int main(){
    int select_count;
    while(true){ 
        showMenu();
        cin >> select_count;
        cin.ignore();

        switch (select_count)
        {
        case 1:
            option1();
            break;
            
        case 2:
            option2();
            break;
        case 3:
            option_3();
            break;
        case 4:
            cout << "Exiting program. Goodbye!" << endl;
            return 0;  // Exits only when user selects option 4
        default:
            cout << "still not";
        }

    }
        
}
void open_and_read_Json(json& data){
   ifstream input_file("data.json");

   if(!input_file.is_open()){
    cout << "Sorry we can't read the file";
    data = json::object();
   }else{
    try{
            input_file >> data;  // Try to read the JSON data
        } catch (const json::parse_error& e) {
            cout << "Error parsing the existing JSON file, starting fresh!" << endl;
            data = json::object();  // If parsing fails, initialize an empty JSON object
        }
        input_file.close();
   }
   }

void showMenu(){
    cout << "Hello this is a menu interactive, please select one of the options" <<endl;
    cout << "1. Enter new account information" << endl
         << "2. Change account information "<< endl 
         << "3. Display all account information" <<endl
         << "4. Exit the program" << endl;
}

void option1(){
    customer cust;
    cout << "What is your name" << endl;
    getline(cin, cust.name);
    cout << "What is your adress number" << endl;
    getline(cin, cust.adress);
    cout << "what is your account balance" << endl;
    cin >> cust.acount_Balance ;
    cin.ignore();
    
    save_JsonDoc(cust);


}

void save_JsonDoc(const customer& cust){

    //data Json
    // Cargar datos previos
    json data ;
    ifstream input_file("data.json");
    if (input_file) {
        // Try to read the existing file
        try {
            input_file >> data;
        } catch (const json::parse_error& e) {
            cout << "Error parsing the existing JSON file, starting fresh!" << endl;
            data = json::object(); // importante
        }
        input_file.close();
    
    
    }else{
        data = json::object();
    }
    int account_number = data.size()+1;


    json new_account;
    new_account["name"] = cust.name;
    new_account["adress"] = cust.adress;
    new_account["balance"] = cust.acount_Balance;
    
    //Add the new account depend on the side
    string account_key = "Account" + to_string(account_number);
    data[account_key]= new_account;
    cout << "Preparing to write the following data to data.json:" << endl;
    cout << data.dump(4) << endl;


    ofstream output_file("data.json");

    if (output_file.is_open()) {
        output_file << data.dump(4); // Guarda el archivo en formato bonito
        output_file.close();
        cout << "Account saved successfully!" << endl;
    } else {
        cout << "Error: Could not open the file to save data." << endl;
    }
}

void option2(){
    cout << "We will display the account"<< endl;
    json data;
    open_and_read_Json(data);
    cout << data.dump(4) << endl;
    cout << "which account would you like to change, pleases enter just the number of the account"<<endl;
    int number_account_reference;
    cin >> number_account_reference;
    cin.ignore();

    modify_account(number_account_reference);


}

void modify_account(int number_account_reference){
    json data;
    open_and_read_Json(data);
    
    string key_account = "Account" + to_string(number_account_reference);
    if(data.contains(key_account)){
        cout << "We found your account"<<endl;
        cout << "We will change your information"<<endl;

        string new_name, new_address;
        double new_account_balance;
        cout << "What is your name" << endl;
        getline(cin, new_name);
        cout << "What is your adress number" << endl;
        getline(cin, new_address);
        cout << "what is your account balance" << endl;
        cin >> new_account_balance;
        cin.ignore();
        

        //uptadete the data and check that everything had been filled!!
        if(!new_name.empty())data[key_account]["name"]=new_name;
        if(!new_address.empty())data[key_account]["adress"]=new_address;
        if(new_account_balance != 0)data[key_account]["balance"]=new_account_balance;


        ofstream output_file("data.json");
        if(output_file.is_open()){
            output_file << data.dump(4);
            output_file.close();
            cout << "We change your data succesfully"<< endl;
        }else{
            cout<<"sorry we coudn't open the file!"<< endl;
        }
    }else{
        cout<< "Sorry!, we aren't able to find your account try again!"<<endl;
    }

}

void option_3(){
    json data;
    open_and_read_Json(data);
    cout << data.dump(4) << endl;
    cout << "This is the accounts we have, do you want to anything else y/n?";
    char choice;
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        return;  // Esto regresará al ciclo en main() y mostrará el menú nuevamente
    } else {
        cout << "Exiting program. Goodbye!" << endl;
        return;  // Termina el programa si elige 'n'
    }

}
