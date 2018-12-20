#include <iostream>
#include <boost/property_tree/xml_parser.hpp>

using namespace std;

int main()
{
    boost::property_tree::ptree propertyTree;

    std::string xmlCode = "<ParamList>\
        <Param1>P1</Param1>\
        <Param2>P2</Param2>\
        </ParamList>";

    std::stringstream stream(xmlCode);

    boost::property_tree::read_xml(stream, propertyTree);

    std::string param1, param2;

    for(auto it : propertyTree.get_child("ParamList"))
    {
        if(it.first == "Param1")
        {
            param1 = it.second.get<std::string>("");
        }
        if(it.first == "Param2")
        {
            param2 = it.second.get<std::string>("");
        }
    }

    std::cout << "Param1 = " << param1 << " Param2 = " << param2;


    return 0;
}

