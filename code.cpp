#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <unistd.h>
#include <vector>

using namespace std;

class FileEditor {
public:
  void searchAndEdit() {
    system("clear"); // clear console
    string filename;
    string name;
    cout << "list of files... \n database/arrivals.txt \n database/baggage.txt \n database/departures.txt \n database/parking_spots.txt \n database/users.txt.\n\n Please enter full file path : ";
    cin.ignore();
    getline(cin, filename);
    system("clear");// get file name from user input

    ifstream infile(filename);
    if (infile.is_open()) {
      string line;
      vector<string> lines;
      int lineNum = 0;
      bool found = false;
      while (getline(infile, line)) {
        lineNum++;
        if (line.find(name) != string::npos) {
          found = true;
          cout << "Line " << lineNum << ": " << line << endl;
          lines.push_back(line);
        }
      }
      infile.close();
      if (!found) {
        cout << "No lines found with name: " << name << endl;
        return;
      }

      cout << "Enter line number to edit/delete (0 to cancel): ";
      int choice;
      cin >> choice;
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer
      if (choice <= 0 || choice > lines.size()) {
        cout << "Invalid choice. Operation cancelled." << endl;
        return;
      }

      cout << "Selected line: " << lines[choice - 1] << endl;
      cout << "Enter new line to replace (or DELETE to delete): ";
      string newLine;
      getline(cin, newLine);
      if (newLine == "DELETE") {
        lines.erase(lines.begin() + choice - 1);
      } else {
        lines[choice - 1] = newLine;
      }

      ofstream outfile(filename, ios::trunc);
      if (outfile.is_open()) {
        for (const auto &line : lines) {
          outfile << line << endl;
        }
        outfile.close();
        cout << "Line updated/deleted successfully." << endl;
        sleep(2);
        system("clear");
      } else {
        cout << "Error: could not open file" << endl;
      }
    } else {
      cout << "Error: could not open file" << endl;
      return; // return early on file open failure
    }
  }
};
class LogoOutput {
  public:
      void logo() {
  cout << "--------------------------------------------------------------------"
          "---------------------------------\n";
  cout << "##       #### ########   #######   ######  ########    ###         "
          "########  ####  ######      ###   \n";
  cout << "##        ##  ##     ## ##     ## ##    ##    ##      ## ##        "
          "##     ##  ##  ##    ##    ## ##  \n";
  cout << "##        ##  ##     ## ##     ## ##          ##     ##   ##       "
          "##     ##  ##  ##         ##   ## \n";
  cout << "##        ##  ##     ## ##     ##  ######     ##    ##     ##      "
          "########   ##  ##   #### ##     ## \n";
  cout << "##        ##  ##     ## ##     ##       ##    ##    #########      "
          "##   ##    ##  ##    ##  #########  \n";
  cout << "##        ##  ##     ## ##     ## ##    ##    ##    ##     ##      "
          "##    ##   ##  ##    ##  ##     ## \n";
  cout << "######## #### ########   #######   ######     ##    ##     ##      "
          "##     ## ####  ######   ##     ##  \n";
  cout << "--------------------------------------------------------------------"
          "---------------------------------";
}
};
class TextFileSorter {
public:
    TextFileSorter() = default;

    void Sort() {
        string file_name;
        cout << "list of sortable files... : \n database/arrivals.txt \n database/baggage.txt \n database/departures.txt \n database/parking_spots.txt \n database/users.txt.\n\n Please enter full file path : ";
        cin >> file_name;

        ifstream file(file_name);
        if (!file.is_open()) {
            cout << "Failed to open file: " << file_name << endl;
            return;
        }

        vector<string> lines;
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }

        selectionSort(lines);

        file.close();

        ofstream sorted_file(file_name, ios::out | ios::trunc);
        if (!sorted_file.is_open()) {
            cout << "Failed to sort file: " << file_name << endl;
            return;
        }

        for (const auto& sorted_line : lines) {
            sorted_file << sorted_line << endl;
        }

        sorted_file.close();

        system("clear");

        cout << "File sorted successfully!" << endl;
        sleep(2);
        system("clear");
    }

private:
    void selectionSort(vector<string>& lines) {
        int n = lines.size();
        for (int i = 0; i < n - 1; ++i) {
            int min_idx = i;
            for (int j = i + 1; j < n; ++j) {
                if (lines[j] < lines[min_idx]) {
                    min_idx = j;
                }
            }
            if (min_idx != i) {
                swap(lines[i], lines[min_idx]);
            }
        }
    }
};
class Arrival {
public:
  void addArrival() {
    string answer = "y";
    while (answer == "y") {
      string airport_;
      string time_;
      ofstream outfile("database/arrivals.txt", ios::app);
      if (outfile.is_open()) {
        system("clear");
        LogoOutput output;
        output.logo();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl << "Enter the arrival time: ";
        getline(cin, time_);
        cout << "\nEnter from which airport: ";
        getline(cin, airport_);
        outfile << time_ << " " << airport_ << "\n";
        outfile.close();
        cout << "Arrival added successfully!" << endl;
      } else {
        cout << "Error: could not open file" << endl;
      }
      cout << "Do you want to add another arrival? (y/n): ";
      getline(cin, answer);
      system("clear");
    }
  }

  void viewArrivals() {
  string line;
  ifstream myfile("database/arrivals.txt");
  if (myfile.is_open()) {
    system("clear");
    LogoOutput output;
    output.logo();// Add this line to display the logo
    cout << "\n";
    while (getline(myfile, line)) {
      string airport_;
      string time_;
      istringstream iss(line);
      iss >> airport_ >> time_;
      cout << airport_ << " " << time_ << endl;
    }
    myfile.close();
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
    system("clear");
  } else {
    cout << "Unable to open file";
  }
}
};

class Departure {
public:
  void addDepartures() {
    string answer = "y";
    while (answer == "y") {
      ofstream outfile("database/departures.txt", ios::app);
      if (outfile.is_open()) {
        system("clear");
        LogoOutput obj;
        obj.logo();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nEnter the departure time: ";
        getline(cin, time_);
        cout << "Enter the destination airport: ";
        getline(cin, destination_);
        outfile << time_ << " " << destination_ << "\n";
        outfile.close();
        cout << "Departure added successfully!" << endl;
        sleep(2);
        system("clear");
      } else {
        cout << "Error: could not open file" << endl;
      }
      cout << "Do you want to add another departure? (y/n): ";
      getline(cin, answer);
      while (answer != "y" && answer != "n") {
        cout << "Invalid input. Please enter 'y' or 'n': ";
        getline(cin, answer);
      }
    }
  }

  void viewDepartures() {
    ifstream infile("database/departures.txt");
    if (infile.is_open()) {
      string line;
      system("clear");
      LogoOutput output;
      output.logo();
      while (getline(infile, line)) {
        istringstream iss(line);
        cout << "\n";
        iss >> destination_ >> time_;
        cout << destination_ << " " << time_;
      }
      infile.close();
      cout << "\nPress Enter to continue...";
      cin.ignore();
      cin.get();
      system("clear");
    } else {
      cout << "Error: could not open file" << endl;
    }
  }

private:
  string destination_;
  string time_;
};
class ParkingSpot {
public:
  string spot;
  string status;

  void addParkingSpots() {
    string answer = "y";
    while (answer == "y") {
      ofstream outfile("database/parking_spots.txt", ios::app);
      if (outfile.is_open()) {
        system("clear");
        LogoOutput output;
        output.logo();
        string spot, status;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nEnter the parking spot: ";
        getline(cin, spot);
        cout << "Enter the parking status: ";
        getline(cin, status);
        outfile << spot << " " << status << "\n";
        outfile.close();
        cout << "Parking spot added successfully!" << endl;
      } else {
        cout << "Error: could not open file" << endl;
      }
      cout << "Do you want to add another parking spot? (y/n): ";
      getline(cin, answer);
      system("clear");
    }
  }

  vector<ParkingSpot> viewParkingSpots() {
    vector<ParkingSpot> parking_spots;
    ParkingSpot parking_spot;
    string line;
    ifstream myfile("database/parking_spots.txt");
    if (myfile.is_open()) {
      while (getline(myfile, line)) {
        istringstream iss(line);
        iss >> parking_spot.spot >> parking_spot.status;
        parking_spots.push_back(parking_spot);
      }
      myfile.close();
      system("clear");
      LogoOutput output;
      output.logo();
      cout << "\n";
      for (const auto &ps : parking_spots) {
        cout << ps.spot << " - " << ps.status << endl;
      }
      cout << "Press Enter to continue...";
      cin.ignore();
      cin.get();
      system("clear");
    } else {
      cout << "Unable to open file" << endl;
    }
    return parking_spots;
  }
};
class BaggageManagement {
public:
  void addBaggage() {
    string answer = "y";
    while (answer == "y") {
      ofstream outfile("database/baggage.txt", ios::app);
      if (outfile.is_open()) {
        system("clear");
        LogoOutput output;
        output.logo();
        string weight, details;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nEnter baggage weight: ";
        getline(cin, weight);
        cout << "Enter baggage details: ";
        getline(cin, details);
        outfile << weight << "kg, details -  " << details << "\n";
        outfile.close();
        cout << "Information about baggage is successfully added!" << endl;
      } else {
        cout << "Error: could not open file" << endl;
      }
      cout << "Do you want to add another bag? (y/n): ";
      getline(cin, answer);
      system("clear");
    }
  }

  vector<string> viewBaggage() {
    vector<string> baggage;
    string line;
    ifstream myfile("database/baggage.txt");
    if (myfile.is_open()) {
      while (getline(myfile, line)) {
        baggage.push_back(line);
      }
      myfile.close();
      system("clear");
      LogoOutput output;
      output.logo();
      cout << "\n";
    } else {
      cout << "Unable to open file" << endl;
      return baggage; // return empty vector if file cannot be opened
    }

    for (const auto &item : baggage) {
      cout << item << endl;
    }
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
    system("clear");
    return baggage;
  }
};
struct MyFunctions {
  void whichLogin() {
  string WhoLogin;
  string LogOrReg;
  system("clear");
  LogoOutput obj;
  obj.logo();
  cout << "\nAdmin or user? : ";
  cin >> WhoLogin;
  if (WhoLogin == "Admin") {
    adminLogin();
  } else if (WhoLogin == "user") {
    cout << "Login or Register? : ";
    cin >> LogOrReg;
    if (LogOrReg == "Login") {
      login();
    } else if (LogOrReg == "Register") {
      registry();
    }
  }


    
  else {
    whichLogin();
  }
}

void login() {
    string UserName, Password;
    string UseEnter, PassEnter;
    bool On_Off = true;
    bool Off = true;
    int countt = 0;
    int left = 4;
    system("clear");
    cout << "**** Login to your account ****\n";
    while (On_Off) {
      fstream user;
      user.open("database/users.txt", ios::in);
      cout << "enter your given username: ";
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      getline(cin, UseEnter);
      cout << "Password: ";
      getline(cin, PassEnter);
      string read;
      while (getline(user, read)) {
        stringstream convertor(read);
        convertor >> UserName >> Password;
        if (UseEnter == UserName && PassEnter == Password) {
          Off = false;
        }
      }
      user.close();
      if (!Off) {
        int choice;
        On_Off = false;
        system("clear");
        do {
          LogoOutput output;
          output.logo();
          cout << "\n------------------------------------------------------------"
                  "-----------------------------------------";
          cout << "\nPlease select an option:" << endl;
          cout << "1. View arrivals" << endl;
          cout << "2. View departures" << endl;
          cout << "3. View parking spots" << endl;
          cout << "4. View luggage details" << endl;
          cout << "5. Quit" << endl;
          cout << "--------------------------------------------------------------"
                  "---------------------------------------\n";
          cin >> choice;
          switch (choice) {
            case 1:{
              Arrival obj1;
              obj1.viewArrivals();
              break;
            }
            case 2:{
              Departure obj2;
              obj2.viewDepartures();
              break;
            }
            case 3:{
              ParkingSpot obj3;
              obj3.viewParkingSpots();
              break;
            }
            case 4:{
              BaggageManagement obj4;
              obj4.viewBaggage();
              break;
            }
          }
        } while (choice != 5);
      } else if (Off) {
        cout << "password you have provided is wrong!";
        system("clear");
        On_Off = false;
      }
    }
  }

  void registry() {
    string newName, checkName, newPass, confirmPass;
    int MiniPass;
    bool if_ON = true;
    bool oo = true;
    cout << "\n**** create a new account ****\n" << endl;
    while (oo) {
      system("clear");
      cout << "enter new username: ";
      getline(cin, newName);
      MiniPass = newName.length();
      fstream yusers;
      yusers.open("database/users.txt", ios::in);
      if (if_ON && MiniPass >= 1 && yusers.is_open()) {
        string readd;
        while (getline(yusers, readd)) {
          stringstream OnlyUsers(readd);
          OnlyUsers >> checkName;
          if (newName == checkName) {
            system("clear");
            cout << newName << " this username already exists";
            if_ON = false;
          }
        }
        if (!if_ON) {
          if_ON = true;
        } else {
          oo = false;
        }
      }
    }
  while (true) {
    system("clear");
    cout << "enter new password: ";
    getline(cin, newPass);
    cout << "confirm the new password: ";
    getline(cin, confirmPass);
    MiniPass = newPass.length();

    if (MiniPass < 5) {
      system("clear");
      cout << "your password is weak, needs to be atleast 5 digits";
    } else if (confirmPass == newPass) {
      fstream users;
      users.open("database/users.txt", ios::app);
      if (users.is_open()) {
        users << newName + " " + newPass << endl;
        users.close();
        break;
      }
    }
  }
}

    void adminLogin() {
    int choice;
    string UserName, Password;
    string UseEnter, PassEnter;
    bool On_Off = true;
    bool Off = true;

    while (On_Off) {
        fstream user;
        user.open("database/admin.txt", ios::in);
        if (Off && user.is_open()) {
            cout << "Enter your given username: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, UseEnter);
            cout << "Enter your password: ";
            getline(cin, PassEnter);
        }
        string read;
        while (getline(user, read)) {
            stringstream convertor(read);
            convertor >> UserName >> Password;
            if (UseEnter == UserName && PassEnter == Password) {
                Off = false;
            }
        }
        user.close();
        if (!Off) {
            cout << "Welcome" << endl;
            system("clear");
            On_Off = false;
        } else {
            cout << "\nInvalid username or password. Please try again." << endl;
            sleep(2);
            system("clear");
        }
    }

    do {
        LogoOutput output;
        output.logo();
        cout << "\n----------------------------------------------------------------"
                "-------------------------------------";
        cout << "\nPlease select an option:" << endl;
        cout << "1. Add arrival" << endl;
        cout << "2. View arrivals" << endl;
        cout << "3. Add departure" << endl;
        cout << "4. View departures" << endl;
        cout << "5. Add parking spot" << endl;
        cout << "6. View parking spots" << endl;
        cout << "7. Add luggage" << endl;
        cout << "8. View luggage details" << endl;
        cout << "9. Search data" << endl;
        cout << "10. Sort data" << endl;
        cout << "11. Quit" << endl;
        cout << "------------------------------------------------------------------"
                "-----------------------------------\n";
        cin >> choice;
      

        switch (choice) {
            case 1: {
                Arrival obj11;
                obj11.addArrival();
                break;
            }
            case 2: {
                Arrival obj00;
                obj00.viewArrivals();
                // process arrivals vector here
                break;
            }
            case 3: {
                Departure obj12;
                obj12.addDepartures();
                break;
            }
            case 4: {
                Departure obj13;
                obj13.viewDepartures();
                break;
            }
            case 5: {
                ParkingSpot obj14;
                obj14.addParkingSpots();
                break;
            }
            case 6: {
                ParkingSpot obj15;
                obj15.viewParkingSpots();
                break;
            }
            case 7: {
                BaggageManagement obj16;
                obj16.addBaggage();
                break;
            }
            case 8: {
                BaggageManagement obj17;
                obj17.viewBaggage();
                break;
            }
            case 9: {
                FileEditor obj18;
                obj18.searchAndEdit();
                break;
            }
            case 10: {
            TextFileSorter obj11;
            obj11.Sort();
            break;
            }
            case 11: {
                cout << "Quitting...";
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 11);
}
};

