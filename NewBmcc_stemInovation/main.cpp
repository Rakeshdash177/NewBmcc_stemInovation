#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class Student{
private:
    string firstName, lastName;
    int studentId;
    string studentAddress;
    string studentEmail;
    string major;
    char gender;
    string password;
public:
    Student(){
        firstName = lastName = " ";
        studentId = 0;
        studentAddress = " ";
        studentEmail = "";
        major = " ";
        gender = ' ';
        password= " ";
    }
    Student operator=(const Student &obj){
        this->firstName = obj.firstName;
        this->lastName = obj.lastName;
        this->studentId = obj.studentId;
        this->studentEmail = obj.studentEmail;
        this->major = obj.major;
        this->gender = obj.gender;
        this->password = obj.password;
        return *this;
    }
    void setStudentFirstName(string fname){firstName = fname;}
    string getStudentFirstName()const{return firstName;}
    void setStudentLastName(string lName){lastName = lName;}
    string getStudentLastName()const{return lastName;}
    void setStudentId(int stuId){studentId = stuId;}
    int getStudentId()const{return studentId;}
    void setStudentEmailId(string &email){studentEmail = email;}
    string getStudentEmailId()const{ return studentEmail;}
    void setStudentMajor(string Ymajor){major = Ymajor;}
    
    string getStudentMajor()const{return major;}
    void setStudentAdress(string adress){studentAddress =  adress;}
    string getStudentAdress()const {return studentAddress;}
    void setGender(char sex){gender = sex;}
    char getGender()const{return gender;}
    void setPassword(string pass){password = pass;}
    string getPassword(){return password;}
};
struct Address{
    int buildingNum;
    string streetName;
    string apartment;
    string city;
    string state;
    int zipCode;
};

class RentingProperty{
    Address rentingAdress;
    double rentAmount;
    string note;
    int numOfPeopleAllowed;
public:
    RentingProperty(){
        rentingAdress = Address();
        rentAmount = 0.0;
        note = " ";
        numOfPeopleAllowed = 0;
    }
    void setRentingAdress(Address rentAddress){rentingAdress = rentAddress;}
    Address getRentAddress()const {return rentingAdress;}
    void setRentAmount(double rent){rentAmount = rent;}
    double getRentAmount()const{return rentAmount;}
    void setNumOfAllowedPeople(int maxNum){numOfPeopleAllowed = maxNum;}
    int getNumOfAllowedPeople()const {return numOfPeopleAllowed;}
    void setNote(string sideNote){note = sideNote;}
    string getNote()const {return note;}
    
};


class Host{
private:
    string hostFirstName;
    string hostLastName;
    string hostAddress;
    string hostEmail;
    int hostID;
    string password;
public:
    Host(){
        hostFirstName = " ";
        hostLastName = " ";
        hostAddress = " ";
        hostEmail = " ";
        hostID = 0;
        password = " ";
    }
    void setHostFirstName(string fname){hostFirstName = fname;}
    string getHostFirstName()const{ return hostFirstName;}
    void setHostLastName(string lName){ hostLastName = lName;}
    string getHostLastName()const{return hostLastName;}
    void setHostAddress(string address){hostAddress = address;}
    string getHostAddress()const{ return hostAddress;}
    void setHostEmail(string email){hostEmail = email;}
    string getHostEmail()const{return hostEmail;}
    void setHostID(int hId){hostID = hId;}
    int getHostId()const{return hostID;}
    void setHostPassword(string pass){password = pass;}
    string getHostPassword(){return password;}
    
};
class Host_Query{
private:
    Host hostDetail;
    fstream hostFile;
public:
    void read_host_record(){
        string fName, lName,adress, email;
        string pass1, pass2;
        cout <<  "Enter the first Name: ";
        cin >> fName;
        hostDetail.setHostFirstName(fName);
        cout <<"Enter the last Name: ";
        cin >> lName;
        cin.ignore();
        hostDetail.setHostLastName(lName);
        cout << "Enter the address: ";
        getline(cin, adress);
        hostDetail.setHostAddress(adress);
        cout << "Enter the email adress(Email will be username): ";
        cin >>email;
        hostDetail.setHostEmail(email);
        do{
            cout << "Enter your passWord: ";
            cin >> pass1;
            cout << "Confirm your passWord: ";
            cin >> pass2;
            if(pass1 != pass2){
                cout << "Attention!!! password in both field should match\n";
                cout << "Enter your passWord: ";
                cin >> pass1;
                cout << "Confirm your passWord: ";
            }
            else{
              hostDetail.setHostPassword(pass2);
            }
        }while(pass1 != pass2);
        
    }
    void addHostRecord(){
        hostFile.open("hostFile.dat", ios::binary | ios::out | ios::app);
        if(hostFile.is_open()){
            read_host_record();
            hostFile.write(reinterpret_cast<char*>(&hostDetail), (sizeof(Host)));
            hostFile.close();
        }
        else{
            cout << "Error!!! File cannot open\n";
        }
        
    }
    void writeHostRecord(){
        cout << "\n***********************************************************************\n";
        cout << "Host Deatail\n";
        cout << "Host First Name: " << hostDetail.getHostFirstName() << endl;
        cout << "Host Last Name: " << hostDetail.getHostLastName() << endl;
        cout << "Host Email: " << hostDetail.getHostEmail() << endl;
        cout << "Host Adress: " << hostDetail.getHostAddress() << endl;
        
        cout << "***********************************************************************\n";
    }
    void showHostRecord(){
        hostFile.open("hostFile.dat", ios::binary | ios::in);
        if(hostFile.is_open()){
            hostFile.read(reinterpret_cast<char*>(&hostDetail), (sizeof(Host)));
            while(!hostFile.eof()){
                writeHostRecord();
                hostFile.read(reinterpret_cast<char*>(&hostDetail), sizeof(Host));
            }
            hostFile.close();
            
        }
    }
    void checkHostRecord(){
        string password, userName;
       Host temp;
        
        cout << "Please Enter your userName: ";
        cin >> userName;
        cout << "\nEnter the password: ";
        cin >> password;
        
        hostFile.open("hostFile.dat", ios::binary | ios::in);
        if(hostFile.is_open()){
            hostFile.read(reinterpret_cast<char*>(&hostDetail), sizeof(Host));
            while(hostDetail.getHostEmail() !=userName && !hostFile.eof()){
                hostFile.read(reinterpret_cast<char*>(&hostDetail), sizeof(Host));
            }
            temp = hostDetail;
            if(temp.getHostEmail() == " "){
                cout << "UserId can not found\n";
            }
            else if(temp.getHostPassword() !=password){
                cout << "Your password doesnot match\n";
            }
            else{
                cout << "Welcome!!!\n";
                cout << temp.getHostFirstName() << " " << temp.getHostLastName() << endl;
            }
        }
    }
};

class Student_Query{
private:
    Student renter;
    fstream renterFile;
public:
    void readRecord(){
        string fName, lName, adress, email, major, pass1, pass2;
        int idNumber;
        char sex;
        cout << "Enter the First name: ";
        cin >>fName;
        renter.setStudentFirstName(fName);
        cout << "\nEnter the last name: ";
        cin >> lName;
        renter.setStudentLastName(lName);
        cin.ignore();
        cout << "\nEnter your address:  ";
        getline(cin, adress);
        cin.ignore();
        renter.setStudentAdress(adress);
        cout << "\nEnter your Major: ";
        getline(cin, major);
        renter.setStudentMajor(major);
        cout << "Enter your gender(M/F): ";
        cin >> sex;
        renter.setGender(sex);
        cout << "\nEnter your student ID: ";
        cin >> idNumber;
        renter.setStudentId(idNumber);
        cout << "\nEnter your email address(Email will be userName): ";
        cin >> email;
        renter.setStudentEmailId(email);
        
        do{
            cout << "Enter your passWord: ";
            cin >> pass1;
            cout << "Confirm your passWord: ";
            cin >> pass2;
            if(pass1 != pass2){
                cout << "Attention!!! password in both field should match\n";
                cout << "Enter your passWord: ";
                cin >> pass1;
                cout << "Confirm your passWord: ";
            }
            else{
                renter.setPassword(pass2);
            }
        }while(pass1 != pass2);
        
        

        }
    void addRecord(){
        renterFile.open("renterFile.dat", ios::binary | ios::out | ios::app);
            if(renterFile.is_open()){
                readRecord();
                renterFile.write(reinterpret_cast<char*>(&renter),(sizeof(Student)));
                renterFile.close();
            }
            else{
                cout << "Error::File can not open\n";
            }
        }

    
    void writeRecord(){
        cout << "\n***********************************************************************\n";
        cout << "Detail of renter student\n";
        cout << "Student ID "<< renter.getStudentId() << '\n';
        cout << "First name: " <<renter.getStudentFirstName() << '\n';
        cout << "Last name: " << renter.getStudentLastName() << '\n';
        cout << "Major: " << renter.getStudentMajor() << '\n';
        cout << "Adress: " << renter.getStudentAdress() << '\n';
        cout << "Email ID: " << renter.getStudentEmailId() << '\n';
        cout << "Gender: " << renter.getGender() << '\n';
        cout << "***********************************************************************\n";
    }
    void show_rec(){
        renterFile.open("renterFile.dat", ios::binary | ios::in);
        if(renterFile.is_open()){
            renterFile.read(reinterpret_cast<char*>(&renter), sizeof(Student));
            while(!renterFile.eof()){
                writeRecord();
                renterFile.read(reinterpret_cast<char*>(&renter), sizeof(Student));
            }
            renterFile.close();
        }
        else{
            cout << "Error::File can not open\n";
        }
    }
    void  CheckStudentRecord(){
       
        string password, userName;
        Student temp;
        
        cout << "Please Enter your userName: ";
        cin >> userName;
        cout << "\nEnter the password: ";
        cin >> password;
        
        renterFile.open("renterFile.dat", ios::binary | ios::in);
        if(renterFile.is_open()){
            renterFile.read(reinterpret_cast<char*>(&renter), sizeof(Student));
            while(renter.getStudentEmailId() !=userName && !renterFile.eof()){
                renterFile.read(reinterpret_cast<char*>(&renter), sizeof(Student));
            }
            //temp = renter;
            if(renter.getStudentEmailId() == " "){
                cout << "UserId can not found\n";
            }
            else if(renter.getPassword() !=password){
                cout << "Your password doesnot match\n";
            }
            else{
                cout << "Welcome!!!\n";
                cout  << renter.getStudentFirstName() << " " << temp.getStudentLastName() << endl;
                
            }
        }
            
    }
    
    
};
//----------------------------------------------------------------------------
void listProperty(){
    RentingProperty property;
    Address propertyAdress;
    double rent;
    string sideNote;
    int maxAllowedPeople;
    cout << "Enter the apartment detail\n";
    cout << "\nEnter the building number: ";
    cin >> propertyAdress.buildingNum;
    cin.ignore();
    cout << "\nEnter the street name: ";
    getline(cin, propertyAdress.streetName) ;
    cout << "\nEnter the apartment: ";
    cin >> propertyAdress.apartment;
    cin.ignore();
    cout << "\nEnter the city name: ";
    getline(cin, propertyAdress.city) ;
    cout << "\nEnter the state: ";
    getline(cin, propertyAdress.state);
    cout << "\nEnter the zipcode: ";
    cin >> propertyAdress.zipCode;
    property.setRentingAdress(propertyAdress);
    cout << "\nEnter the apartment rent: ";
    cin >>rent;
    property.setRentAmount(rent);
    cout << "\nEnter the max number of person allowed to live: ";
    cin >> maxAllowedPeople;
    cin.ignore();
    property.setNumOfAllowedPeople(maxAllowedPeople);
    cout << "\nEnter the side note for renter: ";
    getline(cin, sideNote);
    property.setNote(sideNote);
    
    fstream propertyListFile;
    propertyListFile.open("propertylist.dat", ios::out| ios::binary |ios::app);
    if(propertyListFile.is_open()){
        propertyListFile.write(reinterpret_cast<char *>(&property), (sizeof(RentingProperty)));
    }
    else{
        cout << "Error:: File can not find\n";
    }
}

void showListedProperty(RentingProperty property){
    
    Address a = property.getRentAddress();
    cout << "----------------------------------------------------------------------\n";
    cout << "Apartment detail\n";
    cout << "\nAddress\n";
    cout << a.buildingNum << " " << a.streetName << " " << a.apartment << '\n';
    cout << a.city << " " << a.state << a.zipCode << endl;
    cout << "Rent: " << property.getRentAmount() << endl;
    cout << "Note: " << property.getNote() << endl;
    cout << "----------------------------------------------------------------------\n";
}
void showRentProperty(){
    
    RentingProperty property;
    fstream propertyListFile;
   
    
    propertyListFile.open("propertylist.dat", ios::binary | ios::in);
    if(propertyListFile.is_open()){
        propertyListFile.read(reinterpret_cast<char* >(&property), (sizeof(RentingProperty)));
        while(!propertyListFile.eof()){
            showListedProperty(property);
            propertyListFile.read(reinterpret_cast<char*>(&property), (sizeof(RentingProperty)));
        }
        propertyListFile.close();
    }
    
}

//--------------------------------------------------------------------------------



int main(){
    
    Student_Query student;
    Host_Query host;
    int response, hostOrRenter, option;
    char isRegister;
    string password, userName;
    
    do{
        cout << "Choose one from Below\n";
        cout << "1.Property List\n";
        cout << "2.View listed Propery\n";
        cout << "3.Create Account\n";
        cout << "4.Renter List(person looking for Rent)\n";
        cout << "5.Exit\n";
        cout << "Enter your response please: ";
        cin >> option;
        if(option == 1){
            listProperty();
        }
        else if(option == 2){
            showRentProperty();
        }
        else if(option == 3){
            cout << "Are you Registered?(Y for yes/ N for No)  ";
            cin >> isRegister;
            if(isRegister == 'Y' | isRegister == 'y'){
                cout << "Please select one of the following(1 for Renter/ 2 for Host): ";
                cin >> response;
                if(response == 1){
                    student.CheckStudentRecord();
                }
                else{
                    host.checkHostRecord();
                }
            }
            else{
                cout << "Do you wanna register as host or Renter(1 for Renter/ 2 for Host): ";
                cin >> hostOrRenter;
                if(hostOrRenter == 1){
                    student.addRecord();
                }
                else{
                    host.addHostRecord();
                }
            }
        }
        else if(option == 4){
            student.show_rec();
        }
        else if(option ==5 ){
            EXIT_SUCCESS;
        }
        else{
            cout << "Wrong Input\n";
        }
        
       
    }while(option != 5);
    
    
    
    
    
   
    
    
    
    return 0;
}

