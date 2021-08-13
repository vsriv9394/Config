#pragma once

#include <vector>
#include <string>
#include <sstream>


namespace vs
{
    class config_entry
    {
        private: std::string value;
        
        
        
        public: config_entry(void)
        {
            // Do nothing
        }
        
        
        
        public: config_entry(const std::string& val)
        {    
            value = val;
        }
        
        
        
        public: config_entry(const int& val)
        {
            value = std::to_string(val);
        }
        
        
        
        config_entry(const double& val)
        {    
            value = std::to_string(val);
        }
        
        
        
        config_entry(const std::vector<int>& vec)
        {
            value = std::to_string(vec[0]);
            
            for(int i=1; i<vec.size(); i++)
            {
                value += " " + std::to_string(vec[i]); 
            }
        }
        
        
        
        config_entry(const std::vector<double>& vec)
        {
            value = std::to_string(vec[0]);
            
            for(int i=1; i<vec.size(); i++)
            {
                value += " " + std::to_string(vec[i]); 
            }
        }
        
        
        
        config_entry(const std::vector<std::string>& vec)
        {
            value = vec[0];
            
            for(int i=1; i<vec.size(); i++)
            {
                value += " " + vec[i]; 
            }
        }
        
        
        
        inline operator int() const
        {
            return stoi(value);
        }
        
        
        
        inline operator double() const
        {
            return stod(value);
        }
        
        
        
        inline operator std::string() const
        {
            return std::string(value.c_str());
        }
        
        
        
        inline operator std::vector<int>() const
        {
            std::vector<int> vec; int item;
            std::stringstream ss(value);
            
            while(ss>>item)
            {
                vec.push_back(item);
            }
            
            return vec;
        }
        
        
        
        inline operator std::vector<double>() const
        {
            std::vector<double> vec; double item;
            std::stringstream ss(value);
            
            while(ss>>item)
            {
                vec.push_back(item);
            }
            
            return vec;
        }
        
        
        
        inline operator std::vector<std::string>() const
        {
            std::vector<std::string> vec; std::string item;
            std::stringstream ss(value);
            
            while(ss>>item)
            {
                vec.push_back(item);
            }
            
            return vec;
        }
    };
}