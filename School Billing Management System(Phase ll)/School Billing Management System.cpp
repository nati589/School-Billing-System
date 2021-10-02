               /* School Billing Management System
                  * Register, Update, Delete student information and produce receipt
                  * Administrator sets course payment and intake capacity
                  * Produce various statistical reports in tabular format
                  * Move across the program with ease
                  * Compiler: C++ 17 standard
                  * Full name of student must be entered for proper saving of record
                  * ADMIN Password = 1234
               */
#include<iostream>
#include<string.h>
#include <vector>
#include<iomanip>
#include<fstream>
using namespace std;

struct Courselist{
    string cNames[5];
    float price[5]{};
};

struct Date{
    int dd, mm, yy;
};
//stores student information
struct studInfo{
	char name[30],lname[15],sex;
	int age,stud_id{};
    Date reg_date, pay_date;
    Courselist courses;
    float total_pay{};

};

struct Schoolinfo{
    float total,expense;
    float net;
};
//Global variables
int intake_cap{1000};
int id = 1000;
int stud_count{};  //counts enrolled students
float prices[5]{700, 500, 550, 450, 600}; // default course price
float ctaken[5]{};
vector<studInfo> stud{};
//functions used
void new_reg();
void admin();
void set_intake();
void set_pay();
void overdue();
void profit();
void Coursechoice(studInfo *s, int j);
inline void table(int i);  // output table records
void reorder();  //order records in ascending order
void statreport();
void searching();
void edit();  // edit record
void deletion();  // delete record
inline void retrial(int a);  //for traversing program
void getInfo(){
     ifstream cfile("Course count.txt");
     cfile >> ctaken[0] >> ctaken[1] >> ctaken[2]
           >> ctaken[3] >> ctaken[4];
     cfile.close();
     ifstream id_count("ID.txt");
     id_count >> id;
     id_count.close();
     int check{};
     ifstream counter("Student count.txt");
     counter >> check;
     counter.close();
     if (check > 0){
         stud_count = check;
         stud.resize(stud_count);
         ifstream ifile("User.txt");
         int i{};
         if (ifile){
           while (i < stud_count){
             ifile >> stud[i].name >> stud[i].lname >> stud[i].age >> stud[i].sex
                   >> stud[i].reg_date.dd >> stud[i].reg_date.mm
                   >> stud[i].reg_date.yy >> stud[i].pay_date.dd
                   >> stud[i].pay_date.mm >> stud[i].pay_date.yy
                   >> stud[i].stud_id >> stud[i].total_pay;
             for (int j{}; j < 5; j++){
               ifile >> stud[i].courses.cNames[j] >> stud[i].courses.price[j];
             }
             strcat(stud[i].name," ");
             strcat(stud[i].name,stud[i].lname);
             i += 1;
           }
         }
         ifile.close();
     }
}
void menu(){  // master table
    system ("cls");
    int n;
    here:
    cout << "\n\t\t   Sidney Middle School." << endl;
    cout << "\t\tBilling Management Directory." << endl;
    cout << "\n\t\t\tMain Menu" << endl;
    cout << "\n\t\t1. Registration options." << endl;
    cout << "\t\t2. Administration options." << endl;
    cout << "\t\t3. Statistical reports." << endl;
    cout << "\t\t4. System developers." << endl;
    cout << "\n\t Choice: ";
    cin >> n;
    switch (n){
       case 1: new_reg();
                break;
       case 2: admin();
                break;
       case 3: statreport();
                break;
       case 4: system ("cls");
               cout << "\n\tDevelopers: " << endl;
               cout << "\n\t\tName               ID" << endl;
               cout << "\n\t1. Elsabeth Kahsay    ETS 0241/12" << endl;
               cout << "\t2. Elshaday Dereje    ETS 0243/12" << endl;
               cout << "\t3. Eyobed Mesfin      ETS 0271/12" << endl;
               cout << "\t4. Natan Mekebib      ETS 1029/12 (Group Leader)" << endl;
               cout << "\n\n\tInstructor: Chere Lemma." << endl;
               retrial(1);  // goes to menu
                break;
       default: retrial(2); // goes to previous page
                goto here;
    }
}
void saveinfo(){
         ofstream ofile("User.txt");
         for (int i{};i < stud_count; i++){
           ofile << ' ' << stud[i].name << ' ' << stud[i].age << ' ' << stud[i].sex
                 << ' ' << stud[i].reg_date.dd << ' ' << stud[i].reg_date.mm
                 << ' ' << stud[i].reg_date.yy << ' ' << stud[i].pay_date.dd
                 << ' ' << stud[i].pay_date.mm << ' ' << stud[i].pay_date.yy
                 << ' ' << stud[i].stud_id << ' ' << stud[i].total_pay << ' ';
           for (int j{}; j < 5; j++){
             ofile << stud[i].courses.cNames[j] << ' ' << stud[i].courses.price[j] << ' ';
           }
          ofile << '\n';
         }
         ofile.close();
}
int main(){
   system("color f0");  //white cmd screen
   getInfo();
   menu(); // displays the main menu
}
inline void retrial(int a){
   char retry;
   switch(a){
       case 1: cout << "\n Do you want to go back to the main menu(y/n)" << endl;
               cout << "Choice: ";
               cin >> retry;
               if (tolower(retry) == 'y'){
                   menu();
                  exit(0);
               }
               else{
                  system ("cls");
                  cout << "Have a nice day!" << endl;
                  exit(0);
               }
               break;
      case 2: cout << "Invalid choice, would you like to try again(y/n)?" << endl;
              cin >> retry;
              if (tolower(retry) == 'y'){
                 system ("cls");
                 return;
              }
              else{
                 system ("cls");
                 cout << "Have a nice day!" << endl;
                 exit(0);
              }
              break;
   }
}
void new_reg(){
      system ("cls");
      start:
      int choice;
      cout << "\tUser menu" << endl;
      cout << "\n\t1. Register a student." << endl;
      cout << "\t2. Check payment status." << endl;
      cout << "\t3. Enrollment availability and courses." << endl;
      cout << "\t4. Search options." << endl;
      cout << "\t5. Edit record." << endl;
      cout << "\t6. Delete record." << endl;
      cout << "\n Choice: ";
      cin >> choice;
      switch (choice){
       case 1: break;
       case 2: overdue();
                break;
       case 3: system ("cls");
               cout << "\n\t    Courses" << endl;
               cout << "\t1. Mathematics." << endl;
               cout << "\t2. Physics." << endl;
               cout << "\t3. Biology." << endl;
               cout << "\t4. Chemistry." << endl;
               cout << "\t5. English." << endl;
               cout << "\nThere are " << intake_cap - stud_count
                    << " available spots for this academic year." << endl;
                  retrial(1);
                  break;
       case 4: searching();
                  break;
       case 5: edit();
                  break;
       case 6: deletion();
                  break;
       default: retrial(2);
                goto start;  //wrong input retry
    }
      int num;
      cout << "\nEnter the number of people to register: ";
      cin >> num;
      if(stud_count + num > intake_cap){  // check for vacancy
        cout << "Sorry there isn't enough vacancies for this academic term!" << endl;
        retrial(1);
      }
      system ("cls");
      studInfo student;
      bool check = false;
      for (int i = stud_count;i < stud_count + num;i++){
          cout << "--------------------";
          cout << "\nFull Name(with spaces): "; cin.ignore();
          gets(student.name);
          strupr(student.name);   //change all letters to CAPITAL
          for (int j{}; j < 30 && student.name[j] != '\0';j++){
            if (isspace(student.name[j])){
                check = true;
            }
            else
                continue;
          }
          if (!check){
            strcat(student.name," |NULL|");
          }
          fix_age:
          cout << "\nAge: ";
          cin >> student.age;
          if (student.age > 20 || student.age < 10){
            cout << "Invalid entry try again!" << endl;
            goto fix_age;
          }
          fix_sex:
          cout << "\nSEX(M/F): ";
          cin >> student.sex;
          if (!(toupper(student.sex) == 'M' || toupper(student.sex == 'F'))){
            cout << "Invalid entry try again!" << endl;
            goto fix_sex;
          }
          fix_date:
          cout << "\nToday's date(dd/mm/yyyy): with spaces: ";
          cin >> student.reg_date.dd >> student.reg_date.mm
              >> student.reg_date.yy;
          if (student.reg_date.dd > 31 || student.reg_date.mm > 12 || student.reg_date.yy > 2025){
            cout << "Invalid entry try again!" << endl;
            goto fix_date;
          }
          student.pay_date.dd = student.reg_date.dd;
          student.pay_date.mm = student.reg_date.mm;
          student.pay_date.yy = student.reg_date.yy + 1;  //latest payment option is 1 year after registration
          student.stud_id = id++;  // id is assigned
          Coursechoice(&student,1);
          system("cls");
          char pay;
          cout << "Would you like to pay now(y/n): ";
          cin >> pay;
          if (toupper(pay) == 'Y'){
            strcat(student.name,"(PAID)");
          }
          stud.push_back(student);
          system ("cls");
      }
      for (int i = stud_count;i < stud_count + num;i++){  //display receipt for user
          cout << "\nReceipt: " << endl;
          cout << "----------------------------" << endl;
          cout << "\nStudent ID: SMS" << stud[i].stud_id << endl;
          cout << "Name: " << stud[i].name << endl;
          cout << "Age: " << stud[i].age << " ";
          cout << "\nSEX: " << char(toupper(stud[i].sex)) << endl;
          cout << "Payment date: " << stud[i].pay_date.dd << "/"
               << stud[i].pay_date.mm << "/" << stud[i].pay_date.yy << endl;
          for (int j{};stud[i].courses.price[j];j++){
                cout << stud[i].courses.cNames[j] << " Price: "
                     << stud[i].courses.price[j] << endl;
          }
          cout << "Total Payment: "<< stud[i].total_pay << " birr." << endl;
          cout << "----------------------------\n" << endl;
      }
      stud_count += num;
      ofstream counter("Student count.txt");
      counter << stud_count;
      counter.close();
      ofstream id_count("ID.txt");
      id_count << id;
      id_count.close();
      ofstream cfile("Course count.txt");
      cfile << ctaken[0] << " " << ctaken[1] << " "
              << ctaken[2] << " " << ctaken[3] << " " << ctaken[4];
      cfile.close();
      reorder();  // put in ascending order after entry
      saveinfo();
      retrial(1);
}
void admin(){
    system ("cls");
    int password{1234};  // admin password
    int num;
    cout << "\nAdministrator access required!" << endl;
    cout << "Password: ";
    cin >> num;
    for (int i = 0; i < 3;i++){
       if (num != password ){
            cout << "Wrong password!" << endl;
            cout << "Try again: ";
            cin >> num;
       }
       else
            goto start;
    }
    cout << "Too many attempts!" << endl;
    cout << "Good bye!!!" << endl;
          exit(0);
    start:
    system ("cls");
    int n;
    cout << "\tAdministrator menu" << endl;
    cout << "\n\t1. Set intake capacity." << endl;
    cout << "\t2. Set payment for courses." << endl;
    cout << "\t3. School expenses/Profit report." << endl;
    cout << "\n Choice: ";
    cin >> n;
    switch (n){
       case 1: set_intake();
                  break;
       case 2: set_pay();
                  break;
       case 3: profit();
                  break;
       default: retrial(2);
                goto start;
    }
}
void set_intake(){  // change student intake
       cout << "Enter new intake capacity: ";
       cin >> intake_cap;
       if (stud_count >= intake_cap){
            cout << "You have removed " << stud_count - intake_cap
                 << " students from the registration list." << endl;
            stud_count = intake_cap;
            ofstream counter("Student count.txt");
            counter << stud_count;
            counter.close();
            stud.resize(stud_count);
       }
        retrial(1);
}
void set_pay(){   // change course prices
    system ("cls");
    int cnum;
    cout << "\n\t    Courses" << endl;
    cout << "\t1. Mathematics." << endl;
    cout << "\t2. Physics." << endl;
    cout << "\t3. Biology." << endl;
    cout << "\t4. Chemistry." << endl;
    cout << "\t5. English." << endl;
    cout << "\n How many course prices will you be changing(max = 5): ";
    cin >> cnum;
    int cchoice;
    if (cnum >= 1 && cnum <= 5){
        for (int i{};i < cnum; i++){
            cout << "Course number: ";
            cin >> cchoice;
            cout << "Enter new price: ";
            cin >> prices[cchoice];
        }
    }
    retrial(1);
}
void overdue(){  // notify payment overdue
    int countt{};
    Date today;
    cout << "Enter today's date with spaces (dd/mm/yy): ";
    cin >> today.dd >> today.mm >> today.yy;
    system ("cls");
    cout << "Result:" << endl;
    cout << "----------------------------------------------------------------------------------------------------------------" << endl;
    cout << " ID " << setw(4) << " " << "| Name "
         << setw(26) << " " << "| Age " << setw(1) << " "
         << "| SEX " << setw(3) << " " << "| Payment date " << setw(3) << " "
         << "|Total Payment " << setw(10) << " " << endl;
    cout << "----------------------------------------------------------------------------------------------------------------" << endl;
    for (int i{};i < stud_count;i++){                // check todays date with pay date
        if (today.yy <= stud[i].pay_date.yy){
             continue;
        }
        else{
          table(i);  //generates individual table elements
          countt++;
        }
    }
     if (countt == 0){
        cout << "No overdue payments." << endl;
      }
    retrial(1);
}
void Coursechoice(studInfo *s,int j){   // input courses to take
    start:
    system ("cls");
    int cnum;
    cout << "\n\t\tCourse Menu" << endl;
    cout << "\n\t1. Mathematics." << endl;
    cout << "\t2. Physics." << endl;
    cout << "\t3. Biology." << endl;
    cout << "\t4. Chemistry." << endl;
    cout << "\t5. English." << endl;
    cout << "\n How many courses will you be taking: ";
    cin >> cnum;
    if (cnum > 5 && cnum < 1){
            retrial(2);
            goto start;
    }
    if (cnum < 5){        // Untaken courses are set to null
        for( int i = cnum;i < 5;i++){
            s->courses.cNames[i] = ("Null");
            s->courses.price[i] = 0;
        }
    }
    int choices;
    s->total_pay = 0;
    switch(j){
     case 1:
        for (int i{};i < cnum;i++){
            here:
            cout << "Course number: ";
            cin >> choices;
            switch(choices){
                case 1: s->courses.cNames[i] = ("Mathematics");
                        s->courses.price[i] = prices[0];
                        ctaken[0]++;   // count students in Maths course
                        break;
                case 2: s->courses.cNames[i] = ("Physics");
                        s->courses.price[i] = prices[1];
                        ctaken[1]++;  // count students in Physics course
                        break;
                case 3: s->courses.cNames[i] = ("Biology");
                        s->courses.price[i] = prices[2];
                        ctaken[2]++;  //...
                        break;
                case 4: s->courses.cNames[i] = ("Chemistry");
                        s->courses.price[i] = prices[3];
                        ctaken[3]++;  //...
                        break;
                case 5: s->courses.cNames[i] = ("English");
                        s->courses.price[i] = prices[4];
                        ctaken[4]++;  //...
                        break;
                default:  cout << "Invalid input." << endl;
                        cout << "Try again!" << endl;
                        goto here;
                        break;
            }
            s->total_pay += s->courses.price[i];  //calculate total pay
            }
            break;
     case 2:
        for (int i{};i < cnum;i++){
            there:
            cout << "Course number: ";
            cin >> choices;
            switch(choices){
                case 1: s->courses.cNames[i] = ("Mathematics");
                        s->courses.price[i] = prices[0];
                        break;
                case 2: s->courses.cNames[i] = ("Physics");
                        s->courses.price[i] = prices[1];
                        break;
                case 3: s->courses.cNames[i] = ("Biology");
                        s->courses.price[i] = prices[2];
                        break;
                case 4: s->courses.cNames[i] = ("Chemistry");
                        s->courses.price[i] = prices[3];
                        break;
                case 5: s->courses.cNames[i] = ("English");
                        s->courses.price[i] = prices[4];
                        break;
                default:  cout << "Invalid input." << endl;
                        cout << "Try again!" << endl;
                        goto there;
                        break;
            }
            s->total_pay += s->courses.price[i];  //calculate total pay
        }
            break;
    }
}
void profit(){   // school profit
    float tot{};
    Schoolinfo school;
    cout << "\n  Profit report: " << endl;
    cout << "------------------------------------------------------------------------------" << endl;
    cout << "Number of students: ";
    cout << stud_count << endl;
    cout << "------------------------------------------------------------------------------" << endl;
    for (int i{};i < stud_count;i++){
        tot += stud[i].total_pay;
    }
    school.total = tot;
    school.expense = tot * 0.75;    // each course costs 75% of total profit
    school.net = (school.total - school.expense) * 0.85;  // profit after expenses and tax
    cout << "Total profit: ";
    cout << school.total << " birr." <<endl;
    cout << "------------------------------------------------------------------------------" << endl;
    cout << "Expenses: " << school.expense << " birr." << endl;
    cout << "------------------------------------------------------------------------------" << endl;
    cout << "Net profit: " << school.net << " birr." << endl;
    cout << "------------------------------------------------------------------------------" << endl;
    retrial(1);
}
void table(int i){  // output individual table elements
      int name;
          name = 31 - strlen(stud[i].name);
          cout << "SMS" << stud[i].stud_id << " | " << stud[i].name << setw(name) << " "
               << "| " << setw(4) << stud[i].age <<" | " << setw(6) << char(toupper(stud[i].sex))
               <<" | " << setw(7) << stud[i].pay_date.dd << "/" << setw(2) << stud[i].pay_date.mm << "/"
               << setw(4) << stud[i].pay_date.yy << " | " << setw(4) << stud[i].total_pay << " birr." << endl;
          cout << "----------------------------------------------------------------------------------------------------------------" << endl;
}
void reorder(){   // orders records by name
    studInfo temp;
    for (int i{};i < stud_count;i++){
        for (int j{};j < stud_count - 1;j++){
            if (stricmp(stud[j + 1].name, stud[j].name) <= 1 || stud[j].stud_id == 0){
                swap(stud[j+1],stud[j]);
            }
        }
    }
}
void statreport(){  // produce statistical reports
    system ("cls");
    int countt{};
    start:
    cout << "\n\t\tStatistics and Report Menu" << endl;
    cout << "\n\t1. Student list." << endl;
    cout << "\t2. Students above 15 years of age." << endl;
    cout << "\t3. Students less than 15 years of age." << endl;
    cout << "\t4. Number of students taking each course." << endl;
    cout << "\t5. Students paying over 1000 birr." << endl;
    cout << "\n Choice: ";
    int report;
    cin >> report;
    system ("cls");
    cout << "Result:" << endl;
    cout << "----------------------------------------------------------------------------------------------------------------" << endl;
    cout << " ID " << setw(4) << " " << "| Name "
         << setw(26) << " " << "| Age " << setw(1) << " "
         << "| SEX " << setw(3) << " " << "| Payment date " << setw(3) << " "
         << "|Total Payment " << setw(10) << " " << endl;
    cout << "----------------------------------------------------------------------------------------------------------------" << endl;
    switch(report){
       case 1: for (int i{};i < stud_count;i++){
                 table(i);  // output list 1 by 1
                 countt++;
               }
               if (countt == 0){
                  cout << "No results." << endl;
               }
                retrial(1);
               break;
       case 2: for (int i{};i < stud_count;i++){
                 if (stud[i].age >= 15){   // output age above 15
                      table(i);
                      countt++;
                 }
               }
               if (countt == 0){
                  cout << "No results." << endl;
               }
                retrial(1);
                break;
       case 3: for (int i{};i < stud_count;i++){
                 if (stud[i].age < 15){
                      table(i);
                      countt++;
                 }
               }
               if (countt == 0){
                  cout << "No results." << endl;
               }
                retrial(1);
                break;
       case 4: system ("cls");  // students taking each course
               cout << "_________________________________" << endl;
               cout << "| Courses     | No. of students |" << endl;
               cout << "---------------------------------" << endl;
               cout << "| Mathematics | " << setw(10) << ctaken[0] << setw(7) <<"|"<< endl;
               cout << "| Physics     | " << setw(10) << ctaken[1] << setw(7) <<"|"<< endl;
               cout << "| Biology     | " << setw(10) << ctaken[2] << setw(7) <<"|"<< endl;
               cout << "| Chemistry   | " << setw(10) << ctaken[3] << setw(7) <<"|"<< endl;
               cout << "| English     | " << setw(10) << ctaken[4] << setw(7) <<"|"<< endl;
               cout << "---------------------------------" << endl;
                retrial(1);
                  break;
       case 5: for (int i{};i < stud_count;i++){
                 if (stud[i].total_pay >= 1000){
                      table(i);
                      countt++;
                 }
               }
               if (countt == 0){
                  cout << "No results." << endl;
               }
                retrial(1);
                break;
       default: system ("cls");
                retrial(2);
                 goto start;
      }
}
void searching(){   // search function
      system ("cls");
      int countt{},num;
      char str[30];
      cout << "Enter search by \n1. Name or \n2. ID: " << endl;
      cout << "Choice: "; cin >> num;
      system ("cls");
      if (num == 1){
          cout << "Enter the name: "; cin.ignore();
          cin >> str;
      }
      else if (num == 2){
          cout << "Enter the ID: ";
          cin >> num;
      }
      else
          retrial(1);
      system ("cls");
      cout << "\nResult: " << endl;
      cout << "----------------------------------------------------------------------------------------------------------------" << endl;
      for (int i{}; i < stud_count; i++){
        if (strnicmp(str,stud[i].name,3) == 0 || stud[i].stud_id == num){  // checks for name or id
            table(i);
            countt++;
        }
      }
      if (countt == 0){
        cout << "No matching results." << endl;
      }
      retrial(1);
}
void edit(){   // edit record
      system ("cls");
      bool check = false;
      int num, countt{};
      cout << "Enter your ID number:";
      cin >> num;
      for (int i{}; i < stud_count; i++){
        if (stud[i].stud_id == num){
          cout << "--------------------";
          cout << "\nFull Name(with spaces): "; cin.ignore();
          gets(stud[i].name);
          strupr(stud[i].name);
          for (int j{}; j < 30 && stud[i].name[j] != '\0';j++){
            if (isspace(stud[i].name[j])){
                check = true;
            }
            else
                continue;
          }
          if (!check){
            strcat(stud[i].name," |NULL|");
          }
          cout << "\nAge: ";
          cin >> stud[i].age;
          cout << "\nSEX(M/F): ";
          cin >> stud[i].sex;
          Coursechoice(&stud[i],2);
          char pay;
          cout << "Have you paid the receipt(y/n): ";
          cin >> pay;
          if (toupper(pay) == 'Y'){
            strcat(stud[i].name,"(PAID)");
          }
          system ("cls");
          countt++;  // if 0 no results match
        }
      }
      if (countt == 0){
        cout << "No matching results." << endl;
      }
      else
        cout << "Successfully edited entry!" << endl;
      reorder(); // reorder after editing record
      saveinfo();
      retrial(1);
}
void deletion(){  // delete record
      system ("cls");
      int num, countt{};
      cout << "Enter your ID number:";
      cin >> num;
      for (int i{}; i < stud_count; i++){
        if (stud[i].stud_id == num){   // delete individual entries
          stud[i].stud_id = 0;
          countt++;
        }
      }
      for (int i{};i < stud_count;i++){
        for (int j{};j < stud_count - 1;j++){
            if (stud[j].stud_id == 0){
                swap(stud[j+1],stud[j]);
            }
        }
     }
      if (countt > 0){
        stud.pop_back();
        cout << "Successfully deleted entry!" << endl;
        --stud_count;  // decrease student count after deleting
      }
      else{
        cout << "No matching results." << endl;
      }
      ofstream counter("Student count.txt");
      counter << stud_count;
      counter.close();
      saveinfo();
      retrial(1);
}

