#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cctype>
#include <limits>

using namespace std;

double gradeToPoints(const string& grade) {
    string g = "";
    for (char c : grade) g += toupper(c);

    if (g == "A+" || g == "A") return 4.0;
    if (g == "A-") return 3.7;
    if (g == "B+") return 3.3;
    if (g == "B")  return 3.0;
    if (g == "B-") return 2.7;
    if (g == "C+") return 2.3;
    if (g == "C")  return 2.0;
    if (g == "D")  return 1.0;
    if (g == "F")  return 0.0;
    
    return -1.0; // Signal invalid grade entry
}

struct Course {
    string name;
    string grade;
    double credits;
    double gradePoints;
    double qualityPoints;

    Course(string n, string g, double c, double gp) 
        : name(n), grade(g), credits(c), gradePoints(gp) {
        qualityPoints = gradePoints * credits;
    }
};

class Semester {
private:
    int semesterNumber;
    vector<Course> courses;
    double totalCredits;
    double totalQualityPoints;

public:
    Semester(int num) : semesterNumber(num), totalCredits(0.0), totalQualityPoints(0.0) {}

    void addCourse(const string& name, const string& grade, double credits, double gradePoints) {
        Course course(name, grade, credits, gradePoints);
        courses.push_back(course);
        totalCredits += course.credits;
        totalQualityPoints += course.qualityPoints;
    }

    double getSemesterGPA() const {
        return (totalCredits > 0) ? (totalQualityPoints / totalCredits) : 0.0;
    }

    double getTotalCredits() const { return totalCredits; }
    double getTotalQualityPoints() const { return totalQualityPoints; }

    void displaySemesterReport() const {
        cout << "\n==================================================\n";
        cout << "                 SEMESTER " << semesterNumber << " REPORT                 \n";
        cout << "==================================================\n";
        cout << left << setw(15) << "Course" 
             << setw(8)  << "Grade" 
             << setw(10) << "Credits" 
             << setw(15) << "Quality Points" << "\n";
        cout << "--------------------------------------------------\n";

        for (const auto& c : courses) {
            cout << left << setw(15) << c.name 
                 << setw(8)  << c.grade 
                 << setw(10) << fixed << setprecision(1) << c.credits 
                 << setw(15) << fixed << setprecision(2) << c.qualityPoints << "\n";
        }
        cout << "--------------------------------------------------\n";
        cout << "Semester Credits: " << fixed << setprecision(1) << totalCredits << "\n";
        cout << "Semester GPA:     " << fixed << setprecision(2) << getSemesterGPA() << "\n";
    }
};

// Helper function for safe numerical input
template <typename T>
T getValidInput(const string& prompt) {
    T val;
    while (true) {
        cout << prompt;
        if (cin >> val && val > 0) {
            return val;
        }
        cout << "Invalid input. Please enter a positive number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    cout << "======================================\n";
    cout << "      C++ CGPA & GPA CALCULATOR       \n";
    cout << "======================================\n";

    int totalSemesters = getValidInput<int>("Enter total number of semesters: ");

    vector<Semester> academicRecord;
    double overallQualityPoints = 0.0;
    double overallCredits = 0.0;

    for (int sem = 1; sem <= totalSemesters; ++sem) {
        cout << "\n---> Entering Data for Semester " << sem << " <---\n";
        int numCourses = getValidInput<int>("Enter number of courses: ");

        Semester currentSemester(sem);

        for (int c = 1; c <= numCourses; ++c) {
            string courseName, grade;
            double credits;
            double gradePoints = -1.0;

            cout << "\nCourse " << c << " Name/Code (e.g., CS101): ";
            cin >> courseName;

            while (gradePoints < 0) {
                cout << "Grade (A+, A, A-, B+, B, B-, C+, C, D, F): ";
                cin >> grade;
                gradePoints = gradeToPoints(grade);
                if (gradePoints < 0) {
                    cout << "Invalid grade format. Please try again.\n";
                }
            }

            credits = getValidInput<double>("Credit Hours: ");
            currentSemester.addCourse(courseName, grade, credits, gradePoints);
        }

        academicRecord.push_back(currentSemester);
        overallQualityPoints += currentSemester.getTotalQualityPoints();
        overallCredits += currentSemester.getTotalCredits();
    }

    for (const auto& sem : academicRecord) {
        sem.displaySemesterReport();
    }

    double overallCGPA = (overallCredits > 0) ? (overallQualityPoints / overallCredits) : 0.0;

    cout << "\n==================================================\n";
    cout << "              FINAL CUMULATIVE SUMMARY            \n";
    cout << "==================================================\n";
    cout << "Total Earned Credits: " << fixed << setprecision(1) << overallCredits << "\n";
    cout << "Cumulative GPA (CGPA): " << fixed << setprecision(2) << overallCGPA << "\n";
    cout << "==================================================\n";

    return 0;
}