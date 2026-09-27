#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Reading { int hour; int pulses; };
const double PULSES_PER_KWH = 1000.0; // Change to match the simulated meter
const string DATA_FILE = "data/readings.csv";
const string REPORT_FILE = "reports/energy_report.txt";
const string ALERT_FILE = "reports/alerts.csv";
const string CYAN = "\033[36m", GREEN = "\033[32m", YELLOW = "\033[33m";
const string RED = "\033[31m", BOLD = "\033[1m", RESET = "\033[0m";
vector<Reading> readings;

double energy(int pulses) { return pulses / PULSES_PER_KWH; }
int totalPulses() { int n = 0; for (const auto &r : readings) n += r.pulses; return n; }
double totalEnergy() { return energy(totalPulses()); }
double averageEnergy() { return readings.empty() ? 0 : totalEnergy() / readings.size(); }
int peakIndex() { if (readings.empty()) return -1; int best = 0; for (size_t i = 1; i < readings.size(); ++i) if (readings[i].pulses > readings[best].pulses) best = static_cast<int>(i); return best; }
bool isAnomaly(const Reading &r) { return readings.size() >= 3 && averageEnergy() > 0 && energy(r.pulses) > 1.5 * averageEnergy(); }

void banner() {
    cout << CYAN << BOLD << "\n+======================================================+\n"
         << "|          SMART METER  /  ENERGY ANALYTICS            |\n"
         << "|              C++  *  LINUX  *  SIMULATION           |\n"
         << "+======================================================+\n" << RESET;
}
void pause() { cout << "\nPress ENTER to continue..."; cin.get(); }
int inputInt(const string &prompt, int minValue, int maxValue) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= minValue && value <= maxValue) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << RED << "Please enter a number from " << minValue << " to " << maxValue << ".\n" << RESET;
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
double inputRate() {
    double rate;
    while (true) {
        cout << "Enter sample tariff (Rs/kWh): ";
        if (cin >> rate && isfinite(rate) && rate >= 0 && rate <= 1000) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); return rate;
        }
        cout << "Enter a valid nonnegative rate (0-1000).\n";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
void saveCSV() {
    ofstream out(DATA_FILE);
    if (!out) { cout << RED << "Could not write " << DATA_FILE << ". Run from the project root.\n" << RESET; return; }
    out << "hour,pulses,energy_kwh\n";
    out << fixed << setprecision(4);
    for (const auto &r : readings) out << r.hour << ',' << r.pulses << ',' << energy(r.pulses) << '\n';
    cout << GREEN << "Saved " << readings.size() << " readings to " << DATA_FILE << RESET << '\n';
}
void loadCSV() {
    ifstream in(DATA_FILE);
    if (!in) { cout << YELLOW << "No saved data yet. Choose sample data or add readings.\n" << RESET; return; }
    string line; getline(in, line); // CSV header
    vector<Reading> loaded;
    while (getline(in, line)) {
        if (line.empty()) continue;
        istringstream row(line); string h, p, unused;
        if (!getline(row,h,',') || !getline(row,p,',')) continue;
        try {
            size_t hpos = 0, ppos = 0;
            int hour = stoi(h, &hpos), pulses = stoi(p, &ppos);
            if (hpos == h.size() && ppos == p.size() && hour >= 1 && hour <= 24 && pulses >= 0 && pulses <= 1000000) {
                bool duplicate = false;
                for (const auto &r : loaded) if (r.hour == hour) duplicate = true;
                if (!duplicate) loaded.push_back({hour,pulses});
            }
        } catch (...) { /* Skip malformed rows */ }
    }
    sort(loaded.begin(), loaded.end(), [](const Reading &a, const Reading &b) { return a.hour < b.hour; });
    readings = loaded;
    cout << GREEN << "Loaded " << readings.size() << " saved readings.\n" << RESET;
}
void addReading() {
    int hour = inputInt("Enter hour (1-24): ", 1, 24);
    int pulses = inputInt("Enter pulses during that hour (0-1000000): ", 0, 1000000);
    for (auto &r : readings) if (r.hour == hour) { r.pulses = pulses; cout << GREEN << "Updated hour " << hour << ".\n" << RESET; return; }
    readings.push_back({hour,pulses});
    sort(readings.begin(), readings.end(), [](const Reading &a, const Reading &b) { return a.hour < b.hour; });
    cout << GREEN << "Reading added.\n" << RESET;
}
void sampleData() {
    readings = {{1,120},{2,145},{3,130},{4,110},{5,125},{6,160},{7,180},{8,430},{9,155},{10,140},{11,170},{12,135}};
    cout << GREEN << "Loaded 12 demonstration readings (hour 8 has a usage spike).\n" << RESET;
}
void table() {
    if (readings.empty()) { cout << YELLOW << "No readings. Add readings or load sample data.\n" << RESET; return; }
    cout << "\n" << BOLD << left << setw(10) << "Hour" << setw(14) << "Pulses" << setw(17) << "Energy (kWh)" << "Usage" << RESET << '\n';
    cout << string(53, '-') << '\n' << fixed << setprecision(3);
    for (const auto &r : readings) {
        cout << left << setw(10) << r.hour << setw(14) << r.pulses << setw(17) << energy(r.pulses)
             << (isAnomaly(r) ? RED + string("HIGH") + RESET : GREEN + string("Normal") + RESET) << '\n';
    }
    cout << string(53, '-') << "\nTotal pulses: " << totalPulses() << " | Total energy: " << totalEnergy() << " kWh\n";
}
void dashboard() {
    if (readings.empty()) { cout << "No readings to analyze.\n"; return; }
    int peak = peakIndex();
    cout << fixed << setprecision(3) << "\n" << CYAN << BOLD << "ENERGY OVERVIEW\n" << RESET
         << "Total pulses       : " << totalPulses() << '\n'
         << "Total energy       : " << totalEnergy() << " kWh\n"
         << "Avg hourly energy  : " << averageEnergy() << " kWh (recorded hours only)\n"
         << "Peak recorded hour : " << readings[peak].hour << " (" << energy(readings[peak].pulses) << " kWh)\n";
    cout << "\nHOURLY CONSUMPTION (each # ~ 0.02 kWh)\n";
    for (const auto &r : readings) {
        int bars = min(50, static_cast<int>(round(energy(r.pulses) / 0.02)));
        cout << "H" << setw(2) << r.hour << " | " << string(bars, '#') << " " << energy(r.pulses) << " kWh\n";
    }
}
void agent() {
    if (readings.empty()) { cout << "No readings to analyze.\n"; return; }
    cout << "\n" << CYAN << BOLD << "ANALYTICS AGENT\n" << RESET;
    if (readings.size() < 3) { cout << YELLOW << "Add at least 3 readings for anomaly detection.\n" << RESET; return; }
    cout << fixed << setprecision(3) << "Baseline: " << averageEnergy() << " kWh per recorded hour\n"
         << "Alert threshold: " << averageEnergy()*1.5 << " kWh\n";
    int alerts = 0;
    for (const auto &r : readings) if (isAnomaly(r)) {
        ++alerts;
        cout << RED << "[ALERT] Hour " << r.hour << ": " << energy(r.pulses) << " kWh (above threshold)\n" << RESET;
    }
    if (alerts) cout << "Suggestion: Check whether high-power appliances ran during flagged hours.\n";
    else cout << GREEN << "No readings exceeded the chosen threshold.\n" << RESET;
    cout << "Note: A statistical alert is not proof of an electrical fault.\n";
}
void bill() {
    if (readings.empty()) { cout << "No readings available.\n"; return; }
    double rate = inputRate();
    cout << fixed << setprecision(2) << "Energy: " << totalEnergy() << " kWh | Estimated usage cost: Rs "
         << totalEnergy()*rate << "\nExcludes fixed charges, slabs, taxes and other fees.\n";
}
void report() {
    if (readings.empty()) { cout << "No readings available.\n"; return; }
    ofstream out(REPORT_FILE), alerts(ALERT_FILE);
    if (!out || !alerts) { cout << "Cannot write reports. Run from the project root.\n"; return; }
    out << fixed << setprecision(3) << "SMART METER - ENERGY REPORT\n===========================\n"
        << "Mode: software simulation (no physical meter)\nPulse constant: " << PULSES_PER_KWH << " pulses/kWh\n"
        << "Recorded hours: " << readings.size() << "\nTotal pulses: " << totalPulses()
        << "\nTotal energy: " << totalEnergy() << " kWh\nAverage recorded-hour energy: " << averageEnergy() << " kWh\n"
        << "Peak recorded hour: " << readings[peakIndex()].hour << "\n\nREADINGS\n";
    alerts << "hour,pulses,energy_kwh,threshold_kwh\n";
    int n = 0;
    for (const auto &r : readings) {
        out << "Hour " << r.hour << ": " << r.pulses << " pulses, " << energy(r.pulses) << " kWh";
        if (isAnomaly(r)) { out << " [HIGH]"; alerts << r.hour << ',' << r.pulses << ',' << energy(r.pulses) << ',' << averageEnergy()*1.5 << '\n'; ++n; }
        out << '\n';
    }
    out << "\nAlerts: " << n << "\nRule: > 1.5x average, with at least 3 readings.\n"
        << "Alerts indicate unusual usage, not a confirmed fault.\n";
    cout << GREEN << "Created " << REPORT_FILE << " and " << ALERT_FILE << RESET << '\n';
}
int main() {
    banner(); loadCSV();
    while (true) {
        cout << "\n" << CYAN << BOLD << "MAIN MENU" << RESET << '\n'
             << "  1  Add / update hourly pulse reading\n"
             << "  2  Load demonstration data\n"
             << "  3  View all readings\n"
             << "  4  Energy dashboard\n"
             << "  5  Run analytics agent\n"
             << "  6  Estimate usage cost\n"
             << "  7  Save readings (CSV)\n"
             << "  8  Generate text + CSV reports\n"
             << "  9  Exit\n";
        int choice = inputInt("Choose an option (1-9): ", 1, 9);
        if (choice == 9) { cout << "Goodbye! Save readings with option 7 if needed.\n"; break; }
        switch (choice) {
            case 1: addReading(); break;
            case 2: sampleData(); break;
            case 3: table(); break;
            case 4: dashboard(); break;
            case 5: agent(); break;
            case 6: bill(); break;
            case 7: saveCSV(); break;
            case 8: report(); break;
        }
        pause();
    }
}
