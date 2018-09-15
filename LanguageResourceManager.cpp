#include <iostream>
#include <fstream>
#include <iterator>
#include <cstdlib>
#include "LanguageResourceManager.h"


LanguageResourceManager::LanguageResourceManager(Language language) : current(language) {
    setLanguage(language);
}

void LanguageResourceManager::setLanguage(Language language) {
    current = language;
    strings.clear();
    std::ifstream file;
    file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    switch (language) {
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
    try {
        while (std::getline(file, line)) {
            strings.push_back(line);
        }
    } catch (std::exception& e) {

    }
    file.close();
}

const string& LanguageResourceManager::getSDLErrorText() const {
    return strings[0];
}

const string& LanguageResourceManager::getImageErrorText() const {
    return strings[3];
}

const string& LanguageResourceManager::getWindowErrorText() const {
    return strings[4];
}

const string& LanguageResourceManager::getTTFErrorText() const {
    return strings[2];
}

const string& LanguageResourceManager::getFontErrorText() const {
    return strings[5];
}

const string& LanguageResourceManager::getApplicationWindowTitle() const {
    return strings[6];
}

const string& LanguageResourceManager::getNineMensMorrisWindowTitle() const {
    return strings[7];
}

const string& LanguageResourceManager::getSnakesAndLaddersWindowTitle() const {
    return strings[8];
}

const string& LanguageResourceManager::getIMGErrorText() const {
    return strings[1];
}

const string& LanguageResourceManager::getBlackName() const {
    return strings[9];
}

const string& LanguageResourceManager::getBlueName() const {
    return strings[10];
}

const string& LanguageResourceManager::getGreenName() const {
    return strings[11];
}

const string& LanguageResourceManager::getPinkName() const {
    return strings[12];
}

const string& LanguageResourceManager::getRedName() const {
    return strings[13];
}

const string& LanguageResourceManager::getWhiteName() const {
    return strings[14];
}

const string& LanguageResourceManager::getSnakesAndLaddersEndScreenText1() const {
    return strings[15];
}

int LanguageResourceManager::getSnakesAndLaddersEndScreenText1X() const {
    return stoi(strings[16]);
}

const string& LanguageResourceManager::getSnakesAndLaddersEndScreenText2() const {
    return strings[17];
}

int LanguageResourceManager::getSnakesAndLaddersEndScreenText2X() const {
    return stoi(strings[18]);
}

int LanguageResourceManager::getSnakesAndLaddersPlayerNameX(int player) const {
    std::cout << player;
    return stoi(strings[19 + player]);
}

const string& LanguageResourceManager::getSnakesAndLaddersSelectionScreenText1() const {
    return strings[25];
}

int LanguageResourceManager::getSnakesAndLaddersSelectionScreenText1X() const {
    return stoi(strings[26]);
}

const string& LanguageResourceManager::getSnakesAndLaddersSelectionScreenText2() const {
    return strings[27];
}

int LanguageResourceManager::getSnakesAndLaddersSelectionScreenText2X() const {
    return stoi(strings[28]);
}

const string& LanguageResourceManager::getSnakesAndLaddersSelectionScreenText3() const {
    return strings[29];
}

int LanguageResourceManager::getSnakesAndLaddersSelectionScreenText3X() const {
    return stoi(strings[30]);
}

int LanguageResourceManager::getNineMensMorrisWhiteX() const {
    return stoi(strings[31]);
}

int LanguageResourceManager::getNineMensMorrisBlackX() const {
    return stoi(strings[32]);
}

const string& LanguageResourceManager::getNineMensMorrisToMoveText() const {
    return strings[33];
}

int LanguageResourceManager::getNineMensMorrisToMoveTextX() const {
    return stoi(strings[34]);
}

int LanguageResourceManager::getNineMensMorrisEndScreenWhiteX() const {
    return stoi(strings[35]);
}

int LanguageResourceManager::getNineMensMorrisEndScreenBlackX() const {
    return stoi(strings[36]);
}

const string& LanguageResourceManager::getNineMensMorrisEndScreenText1() const {
    return strings[37];
}

int LanguageResourceManager::getNineMensMorrisEndScreenText1X() const {
    return stoi(strings[38]);
}

const string& LanguageResourceManager::getNineMensMorrisEndScreenText2() const {
    return strings[39];
}

int LanguageResourceManager::getNineMensMorrisEndScreenText2X() const {
    return stoi(strings[40]);
}

const string& LanguageResourceManager::getNineMensMorrisRemoveText1() const {
    return strings[41];
}

int LanguageResourceManager::getNineMensMorrisRemoveText1X() const {
    return stoi(strings[42]);
}

const string& LanguageResourceManager::getNineMensMorrisRemoveText2() const {
    return strings[43];
}

int LanguageResourceManager::getNineMensMorrisRemoveText2X() const {
    return stoi(strings[44]);
}

const string& LanguageResourceManager::getRollButtonFileName() const {
    return strings[45];
}

const vector<Language>& LanguageResourceManager::getLanguages() const {
    return languages;
}

const string& LanguageResourceManager::getLanguageSelectionText() const {
    return strings[46];
}

Language LanguageResourceManager::getCurrentLanguage() const {
    return current;
}

const string& LanguageResourceManager::getNineMensMorrisCantRemoveText1() const {
    return strings[47];
}

int LanguageResourceManager::getNineMensMorrisCantRemoveText1X() const {
    return stoi(strings[48]);
}

const string& LanguageResourceManager::getNineMensMorrisCantRemoveText2() const {
    return strings[49];
}

int LanguageResourceManager::getNineMensMorrisCantRemoveText2X() const {
    return stoi(strings[50]);
}


const string LanguageResourceManager::getLanguageString(Language language) const {
    switch (language) {
        case english:
            return string("English");
        case magyar:
            return string("magyar");
        default:
            return string();
    }
}

LanguageResourceManager::~LanguageResourceManager() = default;