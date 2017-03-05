#include <string>
#include <locale>
#include "ctype.h"
#include <iostream>
#include <fstream>


class Text
{
private:
    struct TextElem	{
        std::string data;
        TextElem * prev;
        TextElem * next;
    } * Word;

public:
    ~Text()
    {
        while (Word != nullptr) {
            TextElem * next = Word->next;
            delete Word;
            Word = next;
        }
    }

    Text()
            : Word(nullptr)
    {}

    void Add(const std::string data)
    {
        if (Word == nullptr)
        {
            Word = new TextElem;
            Word->data = data;
            Word->next = nullptr;
            Word->prev = nullptr;
            return;
        }

        TextElem * lastWord = Word;
        while (lastWord->next != nullptr)
        {
            lastWord = lastWord->next;
        }
        lastWord->next = new TextElem;
        lastWord->next->data = data;
        lastWord->next->next = nullptr;
        lastWord->next->prev = lastWord;
    }

    void Print(std::ostream & stream, const std::string & sWord, size_t count)
    {
        TextElem * lastWord = Word;
        while (lastWord != nullptr) {
            if (lastWord->data == sWord) {

                TextElem * printedWord = lastWord;
                size_t i = 0;
                while (printedWord->prev != nullptr && i < count) {
                    printedWord = printedWord->prev;
                    i++;
                }
                for (size_t j = 0; j < i + 1 + count; j++) {
                    if (printedWord == nullptr) break;
                    stream << printedWord->data << " ";
                    printedWord = printedWord->next;
                }
                stream << std::endl;

            }
            lastWord = lastWord->next;
        }
    }
};

bool openDialog(std::ifstream & fin) //+
{
    std::string file;
    std::cout << "Enter name of file: ";
    do
    {
        std::cin >> file;
        if (file == "exit") return false;

        fin.open(file, std::ios_base::in);
        if (fin.is_open())
        {
            return true;
        }
        else
        {
            std::cout << "Error" << std::endl <<"You can try enter a name of other file or >>'end'<< to exit:" << std::endl;
        }
    } while (true);
}

Text * split(std::string & str)
{
    Text * words = new Text;
    std::string word = "";
    for (size_t i = 0; i < str.size(); i++)
    {
        if (ispunct(str[i]) or str[i] == ' ')
        {
            if (word != "")
            {
                words->Add(word);
                word = "";
            }
        }
        else
        {
            word += str[i];
        }
    }

    if (word != "")
    {
        words->Add(word);
    }
    return words;
}





int main()
{
    std::ifstream fin;
    if (!openDialog(fin)) return 0; //+


    //+
    std::string sWord;
    std::cout << "What do you want to find? ";
    std::cin >> sWord;

    size_t n = 0;
    std::cout << "How many words to show from both sides? ";
    std::cin >> n;

    std::string buf;
    while (getline(fin, buf))
    {
        Text * words = split(buf);
        words->Print(std::cout, sWord, n);
        delete words;
    }

    fin.close();
    return 0;
}