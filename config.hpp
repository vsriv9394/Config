#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#ifndef config_namespace
#define config_namespace config
#endif

namespace config_namespace {

    class ConfigEntry {

        std::string value;

        public:

        ConfigEntry(void) { }

        ConfigEntry(const std::string& val) : value(val) { }

        operator int() const
        { return stoi(value); }

        operator double() const
        { return stod(value); }

        operator std::string() const
        { return std::string(value.c_str()); }

        operator std::vector<int>() const
        { std::vector<int> v; std::stringstream ss(value); int t; while(ss>>t) v.push_back(t); return v; }

        operator std::vector<double>() const
        { std::vector<double> v; std::stringstream ss(value); double t; while(ss>>t) v.push_back(t); return v; }

        operator std::vector<std::string>() const
        { std::vector<std::string> v; std::stringstream ss(value); std::string t; while(ss>>t) v.push_back(t); return v; }

    };

    class Config {

        std::map<std::string, ConfigEntry> configMap;

        public:

        ConfigEntry& operator[](const std::string& name) { return configMap[name]; }

        const ConfigEntry& operator[](const std::string& name) const { return configMap.at(name); }

        void addDefault(const std::string& name, const std::string& value) {
            if(configMap.find(name)==configMap.end()) configMap[name] = ConfigEntry(value);
        }

        void writeToTerminal(void) {
            for(auto& entry : configMap) {
                std::cout << entry.first << " = \"" << (std::string)entry.second << "\"" << std::endl;
            }
        }

        void writeToFile(const std::string& filename) {
            std::ofstream outfile(filename.c_str());
            for(auto& entry : configMap) {
                outfile << entry.first << " = \"" << (std::string)entry.second << "\"" << std::endl;
            }
            outfile.close();
        }

        void readFromFile(const std::string& filename) {
            std::ifstream infile(filename.c_str());
            std::vector<std::string> nameVec, valueVec;
            std::string name, value, buffer; bool valueMode;
            nameVec.push_back("");
            while(std::getline(infile, buffer)) {
                std::stringstream ss(buffer);
                valueMode = false; valueVec.clear();
                while(ss>>buffer) {
                    if(buffer=="{") nameVec.push_back("");
                    else if(buffer=="}") nameVec.pop_back();
                    else if(buffer=="#") break;
                    else if(buffer==":") valueMode = true;
                    else if (valueMode) valueVec.push_back(buffer);
                    else { nameVec.pop_back(); nameVec.push_back(buffer); }
                }
                if (valueMode) {
                    name = nameVec[0]; for(int i=1; i<nameVec.size(); i++) name = name + "." + nameVec[i];
                    value = valueVec[0]; for(int i=1; i<valueVec.size(); i++) value = value + " " + valueVec[i];
                    configMap[name] = ConfigEntry(value);
                }
            }
            infile.close();
        }

    };

}