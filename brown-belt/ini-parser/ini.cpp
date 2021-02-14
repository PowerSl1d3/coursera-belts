//
// Created by smarty on 12.10.2020.
//
#include <string>
#include <iostream>

#include "ini.h"
namespace Ini {
    Section& Document::AddSection(std::string name) {
        return sections[name];
    }

    const Section& Document::GetSection(const std::string &name) const {
        return sections.at(name);
    }

    size_t Document::SectionCount() const {
        return sections.size();
    }

    Document Load(std::istream& is) {
        Document doc;
        //Section actual_section;//maybe delete
        std::string input_line;
        std::string actual_sec;

        while (getline(is, input_line)) {
            if (input_line.empty()) {
                continue;
            }
            if (input_line[0] == '[') {
                actual_sec = input_line.substr(1,input_line.size() - 2);
                doc.AddSection(actual_sec);
                continue;
            }

            size_t equal_pos = input_line.find('=');
            doc.AddSection(actual_sec)[input_line.substr(0, equal_pos)] = input_line.substr(equal_pos + 1);
        }

        return doc;
    }
}