#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class Student {
private:
    int ID;
    string Name;
    string Program;
    string Email;
    string PhoneNumber;
    float Attendance;
    float CGPA;

public:
    Student(int id, const string& name, const string& program, const string& email, const string& phone, float attendance, float cgpa)
        : ID(id), Name(name), Program(program), Email(email), PhoneNumber(phone), Attendance(attendance), CGPA(cgpa) {}

    int getID() const 
    { 
        return ID; 
    }
    string getName() const 
    { 
        return Name; 
    }
    string getProgram() const 
    { 
        return Program; 
    }
    string getEmail() const 
    { 
        return Email; 
    }
    string getPhoneNumber() const 
    { 
        return PhoneNumber; 
    }
    float getAttendance() const 
    { 
        return Attendance; 
    }
    float getCGPA() const 
    { 
        return CGPA; 
    }

    void setProgram(const string& program) 
    { 
        Program = program; 
    }
    void setEmail(const string& email) 
    { 
        Email = email; 
    }
    void setPhoneNumber(const string& phone) 
    { 
        PhoneNumber = phone; 
    }
    void setAttendance(float attendance) 
    { 
        Attendance = attendance; 
    }
    void setCGPA(float cgpa) 
    { 
        CGPA = cgpa; 
    }

    void display() const 
    {
        cout << "Student ID: " << ID << endl;
        cout << "Name: " << Name << endl;
        cout << "Program: " << Program << endl;
        cout << "Email: " << Email << endl;
        cout << "Phone Number: " << PhoneNumber << endl;
        cout << "Attendance: " << Attendance << endl;
        cout << "CGPA: " << CGPA << endl;
    }
    void writeToFile(ofstream& outFile) const 
    {
        outFile << ID << " " << Name << " " << Program << " " << Email << " " << PhoneNumber << " " << fixed << setprecision(2) << Attendance << " " << CGPA << endl;
    }
};

void createNewAccount();
bool login();
void studentDatabaseMenu();
void listAllStudents();
void listStudentsByProgram();
void addNewStudent();
void searchStudent();
void modifyStudentData();
void deleteStudent();
bool checkID(int id);
string checkStringInput(const string& message);
float checkFloatInput(const string& message);
int checkIntInput(const string& message);

int main() 
{
    char choice;
    do 
    {
        int option;
        cout << "************************************************************************************************************************************************************" << endl;
        cout << left << "*" << "\t\t\t" << "This lab assignment is submitted by Mohammad Kaddam Ansari with Student Id 151021227" << "\t\t\t" << "*" << endl;
        cout << "************************************************************************************************************************************************************" <<endl<< endl;
        system("pause");
        system("cls");
        cout <<"______________________________________" << endl;
        cout<<"|\t\t\t\t     |" << endl;
        cout<<"|\tSTUDENT DATABASE MENU \t     |"<<endl;
        cout<<"|------------------------------------|"<<endl;
        cout<<"|\t\t\t\t     |" << endl;
        cout<<"|\t1- Existing User.\t     |" << endl;
        cout<<"|\t2- New User.\t\t     |"<<endl;
        cout<<"|____________________________________|" << endl;
        cout<<endl<< "Please enter an option: ";
        cin >> option;

        switch (option) 
        {
        case 1:
            if (login())
                studentDatabaseMenu();
            break;
        case 2:
            createNewAccount();
            break;
        default:
            cout << "Invalid option. Exiting program." << endl;
            return 0;
        }

        cout <<endl<< "Do you want to perform another operation?: ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    return 0;
}

void createNewAccount() 
{
    string userName, password;
    cout << "Please enter your User Name without any space: ";
    cin >> userName;
    cout << "Please enter your Password without any space: ";
    cin >> password;

    ofstream outfile("user_data.txt", ios::app);
    outfile << userName << " " << password << endl;
    outfile.close();

    cout <<endl<< "Login Created Successfully!" << endl;
}

bool login() 
{
    string userName, password;
    cout << "Please enter your User Name without any space: ";
    cin >> userName;
    cout << "Please enter your Password without any space: ";
    cin >> password;

    ifstream infile("user_data.txt");
    string storedUsername, storedPassword;

    while (infile >> storedUsername >> storedPassword) {
        if (storedUsername == userName && storedPassword == password) {
            infile.close();
            cout <<endl<< "Login Successful." << endl;
            return true;
        }
    }

    infile.close();
    cout <<endl<< "Username or Password was incorrect. Please try again." << endl;
    return false;
}

void studentDatabaseMenu() 
{
    char choice;
    do 
    {
        int option;
        system("pause");
        system("cls");
        cout <<endl<<"__________________________________" << endl;
        cout <<"|\t\t\t\t |"<< endl;
        cout <<"|\t\tMENU\t\t |"<<endl;
        cout <<"|--------------------------------|" << endl;
        cout <<"|1- List all students. \t\t |" << endl;
        cout <<"|2- List students by program. \t |" << endl;
        cout <<"|3- Add a new student.\t\t |" << endl;
        cout <<"|4- Search a student.\t\t |" << endl;
        cout <<"|5- Modify data of a student.\t |" << endl;
        cout <<"|6- Delete a student.\t\t |" << endl;
        cout <<"|________________________________|" << endl;
        cout <<endl<< "Please enter an option: ";
        cin >> option;

        switch (option) 
        {
        case 1:
            listAllStudents();
            break;
        case 2:
            listStudentsByProgram();
            break;
        case 3:
            addNewStudent();
            break;
        case 4:
            searchStudent();
            break;
        case 5:
            modifyStudentData();
            break;
        case 6:
            deleteStudent();
            break;
        default:
            cout << "Invalid option." << endl;
        }

        cout <<endl<< "Do you have another operation to perform? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
}

void listAllStudents() 
{
    ifstream infile("students.txt");
    if (!infile) 
    {
        cout << "Unable to open students file." << endl;
        return;
    }

    int id;
    string name, program, email, phone;
    float attendance, cgpa;
    cout <<endl<< "\t\t\t|--------------------------------|"<<endl;
    cout <<"\t\t\t|\tList of all students\t |" <<endl;
    cout << "\t\t\t|________________________________|" << endl;
    cout <<endl<< "Student ID\t" << "Name\t\t" << "Program\t\t" << "Email\t\t\t" << "\tPhone Number\t" << "Attendance\t" << "CGPA\t" << endl;
    while (infile >> id >> name >> program >> email >> phone >> attendance >> cgpa) 
    {
    
        cout<<endl <<"   " <<id << "\t\t" << name << "\t" << program << "\t\t" << email << "\t\t" << phone << "\t   " << attendance << "\t\t " << cgpa << endl;
    }

    infile.close();
}

void listStudentsByProgram() 
{
    string program;
    cout << "Please enter the program name: ";
    cin >> program;

    ifstream infile("students.txt");
    if (!infile) 
    {
        cout << "Unable to open students file." << endl;
        return;
    }

    int id;
    string name, storedProgram, email, phone;
    float attendance, cgpa;

    cout <<endl<< "List of students in program " << program << ":" << endl;
    while (infile >> id >> name >> storedProgram >> email >> phone >> attendance >> cgpa) 
    {
        if (storedProgram == program) 
        {
            cout << "Student ID: " << id << endl;
            cout << "Name: " << name << endl;
            cout << "Program: " << storedProgram << endl;
            cout << "Email: " << email << endl;
            cout << "Phone Number: " << phone << endl;
            cout << "Attendance: " << attendance << endl;
            cout << "CGPA: " << cgpa << endl << endl;
        }
    }

    infile.close();
}

void addNewStudent() 
{
    int id;
    string name, program, email, phone;
    float attendance, cgpa;

    id = checkIntInput("Please enter Student's ID: ");
    cin.ignore();
    name = checkStringInput("Please enter Student's Name: ");
    program = checkStringInput("Please enter Student's Program: ");
    email = checkStringInput("Please enter Student's Email: ");
    phone = checkStringInput("Please enter Student's Phone Number: ");
    attendance = checkFloatInput("Please enter Student's Attendance: ");
    cgpa = checkFloatInput("Please enter Student's CGPA: ");

    ofstream outfile("students.txt", ios::app);
    outfile << id << " " << name << " " << program << " " << email << " " << phone << " " << fixed << setprecision(2) << attendance << " " << cgpa << endl;
    outfile.close();

    cout<<endl << "Student added successfully." << endl;
}

void searchStudent() 
{
    int id;
    cout<<endl << "Please enter Student ID to search: ";
    cin >> id;

    ifstream infile("students.txt");
    if (!infile) 
    {
        cout << "Unable to open students file." << endl;
        return;
    }

    int studentID;
    string name, program, email, phone;
    float attendance, cgpa;
    bool found = false;

    while (infile >> studentID >> name >> program >> email >> phone >> attendance >> cgpa) {
        if (studentID == id) 
        {
            found = true;
            cout << "Student found:" << endl;
            cout << "Student ID: " << studentID << endl;
            cout << "Name: " << name << endl;
            cout << "Program: " << program << endl;
            cout << "Email: " << email << endl;
            cout << "Phone Number: " << phone << endl;
            cout << "Attendance: " << attendance << endl;
            cout << "CGPA: " << cgpa << endl;
            break;
        }
    }

    if (!found) 
    {
        cout <<endl<< "Student with ID " << id << " not found." << endl;
    }

    infile.close();
}

void modifyStudentData() 
{
    int id;
    cout <<endl<< "Please enter Student ID to modify: ";
    cin >> id;

    ifstream infile("students.txt");
    ofstream outfile("temp.txt");

    int studentID;
    string name, program, email, phone;
    float attendance, cgpa;
    bool found = false;

    while (infile >> studentID >> name >> program >> email >> phone >> attendance >> cgpa) {
        if (studentID == id) 
        {
            found = true;
            cout << "Student found:" << endl;
            
            cout << "Student ID: " << studentID << endl;
            cout << "Name: " << name << endl;
            cout << "Program: " << program << endl;
            cout << "Email: " << email << endl;
            cout << "Phone Number: " << phone << endl;
            cout << "Attendance: " << attendance << endl;
            cout << "CGPA: " << cgpa << endl;

            char choice;
            cout << "Which data do you want to modify?" << endl;
            cout << endl << "__________________________________" << endl;
            cout << "|\t\t\t\t |" << endl;
            cout << "|\t\tMENU\t\t |" << endl;
            cout << "|--------------------------------|" << endl;
            cout << "|1.Modify Program \t\t |" << endl;
            cout << "|2.Modify Email \t\t |" << endl;
            cout << "|3.Modify Phone Number \t\t |" << endl;
            cout << "|4.Modify Attendance \t\t |" << endl;
            cout << "|5.Modify CGPA \t\t\t |" << endl;
            cout << "|________________________________|"<<endl;
            cout <<endl<< "Enter your choice : ";
            cin >> choice;

            switch (choice) 
            {
            case '1':
                cout << "Enter new Program: ";
                cin >> program;
                break;
            case '2':
                cout << "Enter new Email: ";
                cin >> email;
                break;
            case '3':
                cout << "Enter new Phone Number: ";
                cin >> phone;
                break;
            case '4':
                cout << "Enter new Attendance: ";
                cin >> attendance;
                break;
            case '5':
                cout << "Enter new CGPA: ";
                cin >> cgpa;
                break;
            default:
                cout << "Invalid choice." << endl;
                break;
            }
        }
        outfile << studentID << " " << name << " " << program << " " << email << " " << phone << " " << fixed << setprecision(2) << attendance << " " << cgpa << endl;
    }

    if (!found) 
    {
        cout <<endl<< "Student with ID " << id << " not found." << endl;
    }
    else 
    {
        cout <<endl<< "Student data modified successfully." << endl;
    }

    infile.close();
    outfile.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
}

void deleteStudent() 
{
    int id;
    cout <<endl<< "Please enter Student ID to delete: ";
    cin >> id;

    ifstream infile("students.txt");
    ofstream outfile("temp.txt");

    int studentID;
    string name, program, email, phone;
    float attendance, cgpa;
    bool found = false;

    while (infile >> studentID >> name >> program >> email >> phone >> attendance >> cgpa) 
    {
        if (studentID == id) 
        {
            found = true;
            cout <<endl<< name << " was deleted from the student's list." << endl;
        }
        else 
        {
            outfile << studentID << " " << name << " " << program << " " << email << " " << phone << " " << fixed << setprecision(2) << attendance << " " << cgpa << endl;
        }
    }

    if (!found) 
    {
        cout <<endl<< "Student with ID " << id << " not found." << endl;
    }

    infile.close();
    outfile.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
}

bool checkID(int id) 
{
    ifstream infile("students.txt");
    int studentID;
    while (infile >> studentID) 
    {
        if (studentID == id) 
        {
            cout <<endl<< "ID already exists. Please enter a different ID." << endl;
            infile.close();
            return false;
        }
    }
    infile.close();
    return true;
}

string checkStringInput(const string& message) 
{
    string input;
    do 
    {
        cout << message;
        getline(cin, input);
    } 
    while (input.empty());
    return input;
}

float checkFloatInput(const string& message) 
{
    float input;
    do 
    {
        cout << message;
        cin >> input;
        if (cin.fail()) 
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout <<endl<< "Invalid input. Please enter a valid number." << endl;
        }
    } 
    while (cin.fail());
    return input;
}

int checkIntInput(const string& message) 
{
    int input;
    do 
    {
        cout << message;
        cin >> input;
        if (cin.fail()) 
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout <<endl<< "Invalid input. Please enter a valid integer." << endl;
        }
    } 
    while (cin.fail());
    return input;
}
