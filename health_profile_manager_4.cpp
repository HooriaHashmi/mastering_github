#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

class HealthProfile {
protected:
    string name;
    double weight;
    double height;
    double bodyTemperature;
    double bloodSugarLevel;

public:
    HealthProfile(string name, double weight, double height, double bodyTemperature = 0.0, double bloodSugarLevel = 0.0) 
        : name(name), weight(weight), height(height), bodyTemperature(bodyTemperature), bloodSugarLevel(bloodSugarLevel) {}

    void setWeight(double w) { weight = w; }
    void setHeight(double h) { height = h; }
    void setBodyTemperature(double temp) { bodyTemperature = temp; }
    void setBloodSugarLevel(double level) { bloodSugarLevel = level; }
    
    string getName() const { return name; }
    double getWeight() const { return weight; }
    double getHeight() const { return height; }
    double getBodyTemperature() const { return bodyTemperature; }
    double getBloodSugarLevel() const { return bloodSugarLevel; }

    double calculateBMI() const {
        return weight / pow(height, 2);
    }

    string bmiCategory() const {
        double bmi = calculateBMI();
        if (bmi < 18.5) return "Underweight";
        else if (bmi < 24.9) return "Normal weight";
        else if (bmi < 29.9) return "Overweight";
        else return "Obese";
    }

    string temperatureStatus() const {
        if (bodyTemperature < 36.1) return "Low";
        else if (bodyTemperature <= 37.2) return "Normal";
        else return "High";
    }

    string bloodSugarStatus() const {
        if (bloodSugarLevel < 70) return "Low";
        else if (bloodSugarLevel <= 140) return "Normal";
        else return "High";
    }

    void displayProfile() const {
        cout << setw(15) << "Name: " << name << "\n"
             << setw(15) << "Weight: " << weight << " kg\n"
             << setw(15) << "Height: " << height << " m\n"
             << setw(15) << "BMI: " << fixed << setprecision(2) << calculateBMI() << " (" << bmiCategory() << ")\n"
             << setw(15) << "Temperature: " << bodyTemperature << " °C (" << temperatureStatus() << ")\n"
             << setw(15) << "Blood Sugar: " << bloodSugarLevel << " mg/dL (" << bloodSugarStatus() << ")\n\n";
    }
};

class HealthProfileManager : public HealthProfile {
private:
    vector<HealthProfile> profiles;

public:
    HealthProfileManager() : HealthProfile("", 0.0, 0.0) {}

    void createProfile(string name, double weight, double height, double bodyTemperature, double bloodSugarLevel) {
        profiles.push_back(HealthProfile(name, weight, height, bodyTemperature, bloodSugarLevel));
        cout << "Profile for " << name << " created successfully.\n";
    }

    void readProfile(string name) const {
        for (const auto& profile : profiles) {
            if (profile.getName() == name) {
                profile.displayProfile();
                return;
            }
        }
        cout << "Profile not found.\n";
    }

    void updateProfile(string name, double newWeight, double newHeight, double newBodyTemperature, double newBloodSugarLevel) {
        for (auto& profile : profiles) {
            if (profile.getName() == name) {
                profile.setWeight(newWeight);
                profile.setHeight(newHeight);
                profile.setBodyTemperature(newBodyTemperature);
                profile.setBloodSugarLevel(newBloodSugarLevel);
                cout << "Profile updated.\n";
                return;
            }
        }
        cout << "Profile not found.\n";
    }

    void deleteProfile(string name) {
        for (auto it = profiles.begin(); it != profiles.end(); ++it) {
            if (it->getName() == name) {
                profiles.erase(it);
                cout << "Profile deleted.\n";
                return;
            }
        }
        cout << "Profile not found.\n";
    }

    void saveToFile() const {
        ofstream file("health_profiles.txt");
        if (!file) {
            cerr << "Error opening file.\n";
            return;
        }
        for (const auto& profile : profiles) {
            file << profile.getName() << " " << profile.getWeight() << " " 
                 << profile.getHeight() << " " << profile.getBodyTemperature() << " "
                 << profile.getBloodSugarLevel() << " " << profile.calculateBMI() << " " 
                 << profile.bmiCategory() << " " << profile.temperatureStatus() << " "
                 << profile.bloodSugarStatus() << "\n";
        }
        cout << "Profiles saved to file.\n";
    }
        
    void loadFromFile() {
        ifstream file("health_profiles.txt");
        if (!file) {
            cerr << "Error opening file.\n";
            return;
        }
        string name, bmiCategory, tempStatus, sugarStatus;
        double weight, height, bodyTemperature, bloodSugarLevel, bmi;
        profiles.clear();
        while (file >> name >> weight >> height >> bodyTemperature >> bloodSugarLevel >> bmi >> bmiCategory >> tempStatus >> sugarStatus) {
            profiles.push_back(HealthProfile(name, weight, height, bodyTemperature, bloodSugarLevel));
        }
        cout << "Profiles loaded from file.\n";
    }

    void displayAllProfiles() const {
        for (const auto& profile : profiles) {
            profile.displayProfile();
        }
    }

    void menu() {
        int choice;
        do {
            cout << "\nHealth Profile Manager\n";
            cout << "1. Create Profile\n";
            cout << "2. View Profile\n";
            cout << "3. Update Profile\n";
            cout << "4. Delete Profile\n";
            cout << "5. Save Profiles to File\n";
            cout << "6. Load Profiles from File\n";
            cout << "7. Display All Profiles\n";
            cout << "8. Exit\n";
            cout << "Choose an option: ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number between 1 and 8.\n";
                continue;
            }

            string name;
            double weight, height, bodyTemperature, bloodSugarLevel;

            switch (choice) {
                case 1:
                    cout << "Enter name: ";
                    cin >> name;
                    cout << "Enter weight (kg): ";
                    cin >> weight;
                    while (weight <= 0) {
                        cout << "Weight must be positive. Enter weight (kg): ";
                        cin >> weight;
                    }
                    cout << "Enter height (m): ";
                    cin >> height;
                    while (height <= 0) {
                        cout << "Height must be positive. Enter height (m): ";
                        cin >> height;
                    }
                    cout << "Enter body temperature (°C): ";
                    cin >> bodyTemperature;
                    while (bodyTemperature <= 0) {
                        cout << "Body temperature must be positive. Enter body temperature (°C): ";
                        cin >> bodyTemperature;
                    }
                    cout << "Enter blood sugar level (mg/dL): ";
                    cin >> bloodSugarLevel;
                    while (bloodSugarLevel < 0) {
                        cout << "Blood sugar level cannot be negative. Enter blood sugar level (mg/dL): ";
                        cin >> bloodSugarLevel;
                    }
                    createProfile(name, weight, height, bodyTemperature, bloodSugarLevel);
                    break;
                case 2:
                    cout << "Enter name: ";
                    cin >> name;
                    readProfile(name);
                    break;
                case 3:
                    cout << "Enter name: ";
                    cin >> name;
                    cout << "Enter new weight (kg): ";
                    cin >> weight;
                    while (weight <= 0) {
                        cout << "Weight must be positive. Enter new weight (kg): ";
                        cin >> weight;
                    }
                    cout << "Enter new height (m): ";
                    cin >> height;
                    while (height <= 0) {
                        cout << "Height must be positive. Enter new height (m): ";
                        cin >> height;
                    }
                    cout << "Enter new body temperature (°C): ";
                    cin >> bodyTemperature;
                    while (bodyTemperature <= 0) {
                        cout << "Body temperature must be positive. Enter new body temperature (°C): ";
                        cin >> bodyTemperature;
                    }
                    cout << "Enter new blood sugar level (mg/dL): ";
                    cin >> bloodSugarLevel;
                    while (bloodSugarLevel < 0) {
                        cout << "Blood sugar level cannot be negative. Enter new blood sugar level (mg/dL): ";
                        cin >> bloodSugarLevel;
                    }
                    updateProfile(name, weight, height, bodyTemperature, bloodSugarLevel);
                    break;
                case 4:
                    cout << "Enter name: ";
                    cin >> name;
                    deleteProfile(name);
                                        break;
                case 5:
                    saveToFile();
                    break;
                case 6:                
                    loadFromFile();
                    break;
                case 7:
                    displayAllProfiles();
                    break;
                case 8:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 8);
    }
};

int main() {
    HealthProfileManager manager;
    manager.menu();
    return 0;
}

