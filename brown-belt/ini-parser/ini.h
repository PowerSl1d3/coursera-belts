//
// Created by smarty on 12.10.2020.
//

#ifndef INI_PARSER_INI_H
#define INI_PARSER_INI_H
#include <string>
#include <iostream>
#include <unordered_map>
namespace Ini {
    using Section = std::unordered_map<std::string, std::string>;

    class Document {
    public:
        Section& AddSection(std::string name);
        const Section& GetSection(const std::string& name) const;
        size_t SectionCount() const;

    private:
        std::unordered_map<std::string, Section> sections;
    };

    Document Load(std::istream& input);
}
#endif //INI_PARSER_INI_H
