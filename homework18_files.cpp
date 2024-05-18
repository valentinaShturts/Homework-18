#include <iostream>
#pragma warning(disable : 4996)
using namespace std;


/*Завдання 2. Дан текстовий файл. Необхідно створити
новий файл і записати в нього таку статистику по вихідному файлу:
■ Кількість символів;
■ Кількість рядків;
■ Кількість голосних;
■ Кількість приголосних;
■ Кількість цифр.*/

//структура со статистикой
struct Statistic
{
    int symbols = 0;
    int lines = 0;
    int vowels = 0;
    int consonants = 0;
    int numbers = 0;
};

//ф-ия создания статистики по данной строке
void createStatistic(char line[], Statistic& st)
{
    //создаю новую строку с меньшим размером
    int size = strlen(line);
    char* line_new = new char[size + 1]; 
    strcpy(line_new, line);

    //строки с гласными и согласными
    const char* vowels = "AEIOUYaeiouy";
    const char* consonants = "BCDFGHJKLMNPQRSTVWXYZbcdfghjklmnpqrstvwxyz";

    //подсчитываю каждый символ строки
    for (int i = 0; i < size; i++)
    {
        if (line_new[i] != ' ') st.symbols++; //к-ство символов не считая пробелов
        if (line_new[i] == '.') st.lines++; //количесвто строк, считая по точкам
        bool isVowel = false;
        bool isConsonant = false;

        for (int j = 0; j < 12; j++) //цикл бегающий по гласным
        {
            if (line_new[i] == vowels[j]) //проверка является ли текущий символ гласным
            {
                st.vowels++;
                isVowel = true;
                break;
            }
        }

        if (!isVowel && line_new[i]!=' ') //если символ не есть гласным и пробелом, проверяю является он согласным
        {
            for (int j = 0; j < 42; j++) 
            {
                if (line_new[i] == consonants[j]) 
                {
                    st.consonants++;
                    isConsonant = true;
                    break;
                }
            }
        }
        if (line_new[i] >= 48 && line_new[i] <= 57) st.numbers++; //к-ство цифр

    }
    if (line_new[size-1] != '\n') st.lines++;//если в конце не было точки а переход на новую строку +строка
}

//записываю структуру в файл
void WriteStatisticsToFile(Statistic st, const char* PATH_TO_FILE)
{
    FILE* file = fopen(PATH_TO_FILE, "w"); //открываю файл для записи
    if (file != nullptr)
    {
        //записываю все данные
        fprintf(file, "\t Statistics of file2");
        fputc('\n', file);
        fprintf(file, "Number of\n\t- symbols: %d\n\t- lines: %d\n\t- vowels: %d\n\t- consonants: %d\n\t- numbers: %d", st.symbols, st.lines, st.vowels, st.consonants, st.numbers);

        //закрываю файл
        fclose(file);
    }
    else
    {
        cout << "Error. File didn't open\n";
    }
}

/*Завдання 1. Дано два текстові файли. З'ясувати, чи збігаються їхні рядки.
Якщо ні, то вивести рядок, який не збігається, з кожного файлу.*/

//ф-ия для считывания файла
char* GetLineFromFile(const char* PATH_TO_FILE, char line[])
{
    FILE* file = fopen(PATH_TO_FILE, "r"); //открываю файл для чтения
    if (file != nullptr)
    {
        if (fgets(line, 255, file) != nullptr) //записываю в созданную мной строку строку из файла
        {
            fclose(file);
            return line; //возвращаю эту строку
        }
        fclose(file);
    }
    else
    {
        cout << "Error. File didn't open\n";
    }
    return nullptr;
}

//ф-ия для сравнения идентичности строк из двух файлов
void compareLines(char line1[], char line2[])
{
    if (strcmp(line1, line2) == 0)
    {
        cout << "Lines are identical" << endl;
    }
    else
    {
        cout << "Lines aren't identical" << endl;
    }
    cout << "File1: "<< line1 << endl<<"File2: " << line2 << endl << endl;
}

int main() 
{

    const char* PATH_TO_FILE1 = "file1.txt";
    const char* PATH_TO_FILE2 = "file2.txt";
    const char* PATH_TO_FILE3 = "statistic.txt";

    char line1[255];
    char line2[255];

    GetLineFromFile(PATH_TO_FILE1, line1 );
    GetLineFromFile(PATH_TO_FILE2, line2);

    compareLines(line1, line2);

    Statistic statistics;
    createStatistic(line2, statistics);
    WriteStatisticsToFile(statistics, PATH_TO_FILE3);

    return 0;
}
