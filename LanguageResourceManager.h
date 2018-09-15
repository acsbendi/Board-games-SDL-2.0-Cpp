#ifndef LANGUAGERESOURCEMANAGER_H_INCLUDED
#define LANGUAGERESOURCEMANAGER_H_INCLUDED
#include <string>
#include <vector>
using std::string;
using std::vector;

enum Language { magyar, english };

/** \brief The class for managing all language specific resources - texts, buttons with text on it
 */
class LanguageResourceManager{
    vector<string> strings;
    vector<Language> languages;
    Language current;
public:
    LanguageResourceManager(Language language);
    void setLanguage(Language language);
    const vector<Language>& getLanguages() const;
    const string& getSDLErrorText() const;
    const string& getTTFErrorText() const;
    const string& getIMGErrorText() const;
    const string& getWindowErrorText() const;
    const string& getImageErrorText() const;
    const string& getFontErrorText() const;
    const string& getSnakesAndLaddersWindowTitle() const;
    int getSnakesAndLaddersPlayerNameX(int player) const;
    const string& getSnakesAndLaddersEndScreenText1() const;
    int getSnakesAndLaddersEndScreenText1X() const;
    const string& getSnakesAndLaddersEndScreenText2() const;
    int getSnakesAndLaddersEndScreenText2X() const;
    const string& getSnakesAndLaddersSelectionScreenText1() const;
    int getSnakesAndLaddersSelectionScreenText1X() const;
    const string& getSnakesAndLaddersSelectionScreenText2() const;
    int getSnakesAndLaddersSelectionScreenText2X() const;
    const string& getSnakesAndLaddersSelectionScreenText3() const;
    int getSnakesAndLaddersSelectionScreenText3X() const;
    const string& getApplicationWindowTitle() const;
    const string& getNineMensMorrisWindowTitle() const;
    const string& getNineMensMorrisToMoveText() const;
    int getNineMensMorrisToMoveTextX() const;
    int getNineMensMorrisWhiteX() const;
    int getNineMensMorrisBlackX() const;
    int getNineMensMorrisEndScreenBlackX() const;
    int getNineMensMorrisEndScreenWhiteX() const;
    const string& getNineMensMorrisEndScreenText1() const;
    int getNineMensMorrisEndScreenText1X() const;
    const string& getNineMensMorrisEndScreenText2() const;
    int getNineMensMorrisEndScreenText2X() const;
    const string& getNineMensMorrisRemoveText1() const;
    int getNineMensMorrisRemoveText1X() const;
    const string& getNineMensMorrisRemoveText2() const;
    int getNineMensMorrisRemoveText2X() const;
    const string& getNineMensMorrisCantRemoveText1() const;
    int getNineMensMorrisCantRemoveText1X() const;
    const string& getNineMensMorrisCantRemoveText2() const;
    int getNineMensMorrisCantRemoveText2X() const;
    const string& getGreenName() const;
    const string& getRedName() const;
    const string& getPinkName() const;
    const string& getBlueName() const;
    const string& getWhiteName() const;
    const string& getBlackName() const;
    const string& getRollButtonFileName() const;
    const string& getLanguageSelectionText() const;
    Language getCurrentLanguage() const;
    const string getLanguageString(Language language) const;
    ~LanguageResourceManager();

};



#endif // LANGUAGERESOURCEMANAGER_H_INCLUDED
