#include <iostream>
#include <fstream>
#include <iterator>
#include <cstdlib>
#include "LanguageResourceManager.h"


LanguageResourceManager::LanguageResourceManager(Language language)
{
    setLanguage(language);
}
void LanguageResourceManager::setLanguage(Language language)
{
    current = language;
    strings.clear();
    std::ifstream file;
    switch(language)
    {
    case magyar:
        file.open("resources/texts/magyar.txt");
        break;
    case english:
        file.open("resources/texts/english.txt");
        break;
    default:
        break;
    }
   string line;
while (std::getline(file, line))
{
   strings.push_back(line);
}
    file.close();
}

const string& LanguageResourceManager::getSDLErrorText() const
{
    return strings[0];
}

const string& LanguageResourceManager::getImageErrorText() const
{
    return strings[3];
}

const string& LanguageResourceManager::getWindowErrorText() const
{
    return strings[4];
}

const string& LanguageResourceManager::getTTFErrorText() const
{
    return strings[2];
}

const string& LanguageResourceManager::getFontErrorText() const
{
    return strings[5];
}

const string& LanguageResourceManager::getApplicationWindowTitle() const
{
    return strings[6];
}

const string& LanguageResourceManager::getNineMensMorrisWindowTitle() const
{
    return strings[7];
}

const string& LanguageResourceManager::getSnakesAndLaddersWindowTitle() const
{
    return strings[8];
}

const string& LanguageResourceManager::getIMGErrorText() const
{
    return strings[1];
}

const string& LanguageResourceManager::getBlackName() const
{
    return strings[9];
}

const string& LanguageResourceManager::getBlueName() const
{
    return strings[10];
}

const string& LanguageResourceManager::getGreenName() const
{
    return strings[11];
}

const string& LanguageResourceManager::getPinkName() const
{
    return strings[12];
}

const string& LanguageResourceManager::getRedName() const
{
    return strings[13];
}

const string& LanguageResourceManager::getWhiteName() const
{
    return strings[14];
}

const string& LanguageResourceManager::getSnakesAndLaddersEndScreenText1() const
{
    return strings[15];
}

int LanguageResourceManager::getSnakesAndLaddersEndScreenText1X() const
{
    return atoi(strings[16].c_str());
}

const string& LanguageResourceManager::getSnakesAndLaddersEndScreenText2() const
{
    return strings[17];
}

int LanguageResourceManager::getSnakesAndLaddersEndScreenText2X() const
{
    return atoi(strings[18].c_str());
}

int LanguageResourceManager::getSnakesAndLaddersPlayerNameX(int player) const
{
    std::cout << player;
    return atoi(strings[19+player].c_str());
}

const string& LanguageResourceManager::getSnakesAndLaddersSelectionScreenText1() const
{
    return strings[25];
}

int LanguageResourceManager::getSnakesAndLaddersSelectionScreenText1X() const
{
    return atoi(strings[26].c_str());
}

const string& LanguageResourceManager::getSnakesAndLaddersSelectionScreenText2() const
{
    return strings[27];
}

int LanguageResourceManager::getSnakesAndLaddersSelectionScreenText2X() const
{
    return atoi(strings[28].c_str());
}

const string& LanguageResourceManager::getSnakesAndLaddersSelectionScreenText3() const
{
    return strings[29];
}

int LanguageResourceManager::getSnakesAndLaddersSelectionScreenText3X() const
{
    return atoi(strings[30].c_str());
}

int LanguageResourceManager::getNineMensMorrisWhiteX() const
{
    return atoi(strings[31].c_str());
}

int LanguageResourceManager::getNineMensMorrisBlackX() const
{
    return atoi(strings[32].c_str());
}

const string& LanguageResourceManager::getNineMensMorrisToMoveText() const
{
    return strings[33];
}

int LanguageResourceManager::getNineMensMorrisToMoveTextX() const
{
    return atoi(strings[34].c_str());
}

int LanguageResourceManager::getNineMensMorrisEndScreenWhiteX() const
{
    return atoi(strings[35].c_str());
}

int LanguageResourceManager::getNineMensMorrisEndScreenBlackX() const
{
    return atoi(strings[36].c_str());
}

const string& LanguageResourceManager::getNineMensMorrisEndScreenText1() const
{
    return strings[37];
}

int LanguageResourceManager::getNineMensMorrisEndScreenText1X() const
{
    return atoi(strings[38].c_str());
}

const string& LanguageResourceManager::getNineMensMorrisEndScreenText2() const
{
    return strings[39];
}

int LanguageResourceManager::getNineMensMorrisEndScreenText2X() const
{
    return atoi(strings[40].c_str());
}

const string& LanguageResourceManager::getNineMensMorrisRemoveText1() const
{
    return strings[41];
}

int LanguageResourceManager::getNineMensMorrisRemoveText1X() const
{
    return atoi(strings[42].c_str());
}

const string& LanguageResourceManager::getNineMensMorrisRemoveText2() const
{
    return strings[43];
}

int LanguageResourceManager::getNineMensMorrisRemoveText2X() const
{
    return atoi(strings[44].c_str());
}

const string& LanguageResourceManager::getRollButtonFileName() const
{
    return strings[45];
}

const vector<Language>& LanguageResourceManager::getLanguages() const
{
    return languages;
}

const string& LanguageResourceManager::getLanguageSelectionText() const
{
    return strings[46];
}

Language LanguageResourceManager::getCurrentLanguage() const
{
    return current;
}

const string LanguageResourceManager::getLanguageString(Language language) const
{
    switch (language)
    {
    case english:
        return string("English");
    case magyar:
        return string("magyar");
    default:
        return string();
    }
}

LanguageResourceManager::~LanguageResourceManager()
{

}
