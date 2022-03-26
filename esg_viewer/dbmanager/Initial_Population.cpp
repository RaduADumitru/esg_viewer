#include <iostream>
#include <string>
#include <QVector>
#include <sstream>
#include <stdexcept>
#include <fstream>



QVector<QVector<std::string>> Gen_Providers()
{
    QVector<QVector<std::string>> content;
    QVector<std::string> row;
    std::string line, word;

    std::fstream file ("C:\\Users\\Lenovo\\Desktop\\HackItAll\\esg_viewer\\data\\providers.csv");
    if(!file.is_open()) throw std::runtime_error("Could not open file");

    while(getline(file, line))
    {
        row.clear();

        std::stringstream str(line);

        while(getline(str, word, ','))
            row.push_back(word);
        content.push_back(row);
    }

    for(int i=0;i<content.size();i++)
       {
           for(int j=0;j<content[i].size();j++)
           {
               std::cout<<content[i][j]<<" ";
           }
           std::cout<<"\n";
       }
    return content;
}

QVector<QVector<std::string>> Gen_Companies()
{
    QVector<QVector<std::string>> content;
    QVector<std::string> row;
    std::string line, word;

    std::fstream file ("..\\data\\companies.csv", std::ios::in);
    if(!file.is_open()) throw std::runtime_error("Could not open file");

    while(getline(file, line))
    {
        row.clear();

        std::stringstream str(line);

        while(getline(str, word, ','))
            row.push_back(word);
        content.push_back(row);
    }

    return content;
}

int main()
{
    Gen_Providers();

}
