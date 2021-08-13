#pragma once

#include <map>
#include <list>
#include <sstream>

#include "config_entry.hpp"

namespace vs
{
    class config
    {
        private: std::map<std::string, config_entry> config_map;



        public: inline config_entry& operator[](const std::string& name)
        {
            return config_map[name];
        }



        public: inline const config_entry& operator[](const std::string& name) const
        {
            return config_map.at(name);
        }



        public: inline void add_default(const std::string& name, const std::string& value)
        {
            if(config_map.find(name)==config_map.end())
            {
                config_map[name] = config_entry(value);
            }
        }



        private: void add_empty_entry_to_name_cascade(std::list<std::string>& name_cascade)
        {
            if (name_cascade.size()>0)
            {
                name_cascade.push_back(name_cascade.back() + ".");
            }

            else
            {
                name_cascade.push_back("");
            }
        }



        private: void process_line(std::stringstream& stream, std::list<std::string>& name_cascade)
        {
            std::string buffer;
            bool value_insertion_mode = false;
            std::vector<std::string> value_vec;

            while (stream >> buffer)
            {
                if      (buffer    ==     "{")
                { add_empty_entry_to_name_cascade(name_cascade); }
                else if (buffer    ==     "}")
                { name_cascade.pop_back(); name_cascade.pop_back(); add_empty_entry_to_name_cascade(name_cascade); }
                else if (buffer    ==     ":")
                { value_insertion_mode = true; }
                else if (buffer    ==     "#")
                { break; }
                else if (value_insertion_mode)
                { value_vec.push_back(buffer); }
                else
                { name_cascade.back() += buffer; }
            }

            if (value_insertion_mode)
            {
                config_map[name_cascade.back()] = config_entry(value_vec);
                name_cascade.pop_back();
                add_empty_entry_to_name_cascade(name_cascade);
            }
        }



        public: inline void write_to_stream(std::ostream& out_stream)
        {
            for(auto& entry : config_map)
            {
                std::string entry_name  = entry.first;
                std::string entry_value = entry.second;

                out_stream << entry_name;
                out_stream << " = ";
                out_stream << "\"" << entry_value << "\"";
                out_stream << std::endl;
            }
        }



        public: inline void read_from_stream(std::istream& in_stream)
        {
            std::list<std::string> name_cascade;
            name_cascade.push_back("");

            std::string buffer;
            while(std::getline(in_stream, buffer))
            {
                std::stringstream ss(buffer);
                process_line(ss, name_cascade);
            }
        }
    };
}