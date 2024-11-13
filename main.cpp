#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <exception>

using namespace std;

//user class is given to us in the problem so paste it here
class User {
private:
    int m_id;
    string m_name;

public:
    User(int id, string name) : m_id(id), m_name(name) {}

    virtual string toString() {
        stringstream ss;
        ss << "ID(" << m_id << ") NAME(" << m_name << ")";
        return ss.str();
    }

    string getName() {
        return m_name;
    }

    bool isIDLarger(User & another) {
        return m_id > another.m_id;
    }

    bool isIDDifferent(User & another) {
        return m_id != another.m_id;
    }

    virtual bool contains(string search) = 0;
};

//problem 1
class StudentInfoException : public exception {
private:
//private variables, attributes of the exception for student
    string m_reason;
    string m_errorMessage;
    string m_badValue;

public:
    //constructor
    StudentInfoException(const string& reason, const string& errorMessage, const string& badValue) : m_reason(reason), m_errorMessage(errorMessage), m_badValue(badValue) {}

    //return the error message
    const char* what() const noexcept override {
        return m_errorMessage.c_str();
    }

    //getter function to return the reason
    string getReason() const {
        return m_reason;
    }

    //getter funciton to return a bad value
    string getBadValue() const {
        return m_badValue;
    }
};

//problem 2, student class inherits from user
class Student : public User {
private:
    //attributes to the student, major and gpa.
    string m_major;
    double m_gpa;

public:
    //constructor
    Student(int id, const string& name, const string& major, double gpa) : User(id, name), m_major(major), m_gpa(gpa) {
        //check if negative, throw negative error, return in format problem states
        if (id < 0) 
            throw StudentInfoException("Invalid ID", "Student ID cannot be negative", to_string(id));
        //make sure gpa is not out of bounds either, otherwise return exception in format
        if (gpa < 0.0 || gpa > 4.0) 
            throw StudentInfoException("Invalid GPA", "GPA must be between 0.0 and 4.0", to_string(gpa));
    }

    //override toString method, use string stream to return student information
    string toString() override {
        stringstream ss;
        ss << User::toString() << " MAJOR(" << m_major << ") GPA(" << fixed << setprecision(2) << m_gpa << ")"; //format given to us
        return ss.str();
    }

    //boolean function to see if gpa is better than another 
    bool hasBetterGPA(const Student& other) const {
        return m_gpa > other.m_gpa;
    }
    
    //see if student is contained, override
    bool contains(string search) override {
        stringstream ss;
        ss << fixed << setprecision(2) << m_gpa; //use set precision to go to 2 decimals
        return getName().find(search) != string::npos || m_major.find(search) != string::npos || ss.str().find(search) != string::npos;
    }
};

//graduate class problem 3
class Graduate : public Student {
private:
    //attributes for graduate student, including graduation class, inherits student
    int m_graduationYear;

public:
    Graduate(int id, const string& name, const string& major, double gpa, int graduationYear) : Student(id, name, major, gpa), m_graduationYear(graduationYear) {
        if (graduationYear < 1900 || graduationYear > 2024)  //graduation year should be within these bounds
            throw StudentInfoException("Invalid Year", "Graduation year must be between 1900 and 2024", to_string(graduationYear));
    }

    //override string method use student and output graduation year in format given in question
    string toString() override {
        return Student::toString() + " GRAD (" + to_string(m_graduationYear) + ")";
    }

    //see if student contained or not, find graduation year as well
    bool contains(string search) override {
        return Student::contains(search) || to_string(m_graduationYear).find(search) != string::npos;
    }
};

// question 4, student manager class
class StudentMgr {
private:
    vector<User*> m_students; //attributes, vector of students

public:
    //method for adding unique student
    bool addUnique(User* student) {
        bool isUnique = true; //needed to not have multiple returns
        
        for (const auto& s : m_students) {
            if (!s->isIDDifferent(*student)) {
                isUnique = false;
                break;
            }
        }
        if (isUnique) 
            m_students.push_back(student);

        return isUnique;
    }


    void getAscendingLargest(User*& largest, bool& isAscending) {
        if (m_students.empty()) {
            largest = nullptr;
            isAscending = true;
            return;
        }

        largest = m_students[0];
        isAscending = true;

        for (size_t i = 1; i < m_students.size(); i++) {
            if (!m_students[i-1]->isIDLarger(*m_students[i])) {
                if (m_students[i]->isIDLarger(*largest)) 
                    largest = m_students[i];
            } 
            else 
                isAscending = false;
        }
    }
    int removeContains(const string& search) {
        int count = 0;
        auto it = m_students.begin();
        while (it != m_students.end()) {
            if ((*it)->contains(search)) {
                delete *it;
                it = m_students.erase(it);
                ++count;
            } 
            else 
                it++;
        }
        return count;
    }

    //iterate through and delete to save memory
    ~StudentMgr() {
        for (auto student : m_students) {
            delete student;
        }
    }
};

//problem 5
void getGraduateStudentList(
    //all of the attributes
    int ids[], string names[], string majors[], double gpas[], int years[], int size,
    StudentMgr*& mgr, int& badId, int& badGPA, int& badYear) {
    
    //create a new student Mgr instance
    /*initialie default values*/
    mgr = new StudentMgr();
    badId = 0;
    badGPA = 0;
    badYear = 0;

    for (int i = 0; i < size; i++) {
        try {
            Graduate* grad = new Graduate(ids[i], names[i], majors[i], gpas[i], years[i]);
            if (!mgr->addUnique(grad)) 
                delete grad;
        } 
        catch (const StudentInfoException& e) {
            if (e.getReason() == "Invalid Year") {
                badYear++;
                try {
                    Student* student = new Student(ids[i], names[i], majors[i], gpas[i]); //attempt to create a new student and add
                    if (!mgr->addUnique(student)) 
                        delete student;
                } 
                //if fails, catch the exception and throw reason. Either a bad id or invalid gpa
                catch (const StudentInfoException& e) {
                    if (e.getReason() == "Invalid ID") 
                        badId++;
                    else if (e.getReason() == "Invalid GPA") 
                        badGPA++;
                }
            } 
            /*similar logic just copy paste, independent of the try catch*/
            else if (e.getReason() == "Invalid ID") 
                badId++;
            else if (e.getReason() == "Invalid GPA") 
                badGPA++;
        }
    }
}

int main() {
    try {
        //create new instances of student and graduates.
        Student* s1 = new Student(1001, "John Doe", "Computer Science", 3.5);
        cout << "Student 1: " << s1->toString() << endl;

        Graduate* g1 = new Graduate(2001, "Jane Smith", "Physics", 3.8, 2023);
        cout << "Graduate 1: " << g1->toString() << endl;

        //test case for studentmgr class
        StudentMgr* mgr = new StudentMgr();
        mgr->addUnique(s1); // Pass dynamic instance
        mgr->addUnique(g1); // Pass dynamic instance

        //testing ascending yes or no
        User* largest;
        bool isAscending;
        mgr->getAscendingLargest(largest, isAscending);
        cout << "Largest ID: " << largest->toString() << endl;
        cout << "Is Ascending: " << (isAscending ? "Yes" : "No") << endl;

        //test the removecontains function
        int removed = mgr->removeContains("Physics");
        cout << "Removed " << removed << " student(s) containing 'Physics'" << endl; //output removed

        //test for graduate student list
        int ids[] = {3001, -1, 3002, 3003}; //give a negative number
        string names[] = {"Alice", "Bob", "Charlie", "David"};
        string majors[] = {"Math", "English", "Chemistry", "Biology"};
        double gpas[] = {3.9, 4.1, 3.7, 3.5}; //4.1 is out of bounds
        int years[] = {2022, 2023, 1899, 2024}; //1899 is out of bounds as well

        StudentMgr* gradMgr;
        int badId, badGPA, badYear;
        getGraduateStudentList(ids, names, majors, gpas, years, 4, gradMgr, badId, badGPA, badYear); //pass in parameters to test getGradStudentList

        //output total counts for bad id's, gpa, and years
        cout << "Bad IDs: " << badId << endl;
        cout << "Bad GPAs: " << badGPA << endl;
        cout << "Bad Years: " << badYear << endl;

        // Clean up the memory by deleting the dynamically allocated objects
        delete mgr;
        delete gradMgr;

    } 
    //catch any exceptions
    catch (const StudentInfoException& e) {
        cout << "StudentInfoException: " << e.what() << endl;
        cout << "Reason: " << e.getReason() << endl;
        cout << "Bad Value: " << e.getBadValue() << endl;
    } catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
    }

    return 0;
}
