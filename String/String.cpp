#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string.h>
#include <iomanip>
#pragma warning (disable: 4996)

/*
        Задание 1: Дополните класс str
        Реализуйте следующие методы:
++++++++  front возвращает первый символ строки
++++++++  back возвращает последний символ строки
++++++++  append для добавления строки в конец
++++++++  append(c-string)
++++++++  append(str)
++++++++  find(char) для поиска позиции символа char в str - (поиск ведется от начала, возвращается первая подходящая позиция)
++++++++  rfind(char) для поиска позиции символа char в str - (поиск ведется от конца, возвращается первая подходящая позиция)
++++++++  clear для очистки строки
++++++++   substr(start, count) - возвращает новый объект str, который включает в себя count символов начиная с позиции start исходной строки
++++++++  empty() проверяет, является ли строка пустой
++++++++  ltrim() убирает пробелы слева, если они есть
++++++++  rtrim() убирает пробелы справа, если они есть
++++++++  trim() убирает пробелы справа и слева, если они есть
++++++++  to_upper() приводит все символы строки к верхнему регистру str.to_upper();
++++++++  to_lower() приводит все символы строки к нижнему регистру
++++++++  ucfirst() приводит первый символ строки к верхнему, а все остальные символы к нижнему регистру
++++++++  reverse() переворачивает строку
++++++++  starts_with проверяет, совпадает ли начало строки с заданным образцом
++++++++  starts_with(c-string)
++++++++  starts_with(str)
    */


class str
{
public:

    str() {}

    str(const char* source)
    {
        cpy(source);
    }

    void assign(const char* source)
    {
        if (m_arr) {
            delete[] m_arr;
        }

        cpy(source);
    }

    char front() {
        if (m_arr) {
            return m_arr[0];
        }
        return NULL;
    }

    char back() {
        if (m_arr) {
            return m_arr[m_length - 1];
        }
        return NULL;
    }

    str(const str& other)
    {
        m_length = other.m_length;
        m_arr = new char[m_length + 1];
        strcpy(m_arr, other.m_arr);
    }

    int length()
    {
        return m_length;
    }

    char* data()
    {
        return m_arr;
    }

    void print() {
        for (int i = 0; i < m_length; i++) {
            std::cout << m_arr[i];
        }
        std::cout << "\n\n" << "m_size = " << m_length << "\n=======================================\n\n";
    }

    ~str()
    {
        delete[] m_arr;
    }

    int find(char simvol)
    {
        for (int i = 0; i < m_length; i++)
        {
            if (m_arr[i] == simvol)
            {
                return i;
            }
        }
        return NOT_VALUE;
    }

    int rfind(char simvol)
    {
        for (int i = m_length - 1; i >= 0; i--)
        {
            if (m_arr[i] == simvol)
            {
                return i;
            }
        }
        return NOT_VALUE;
    }

    bool arrayStatus()
    {
        return (m_length > 0);
    }

    void clear() {
        if (m_arr)
        {
            m_arr = nullptr;
            m_length = 0;
        }
    }

    void reverse()
    {
        if (m_arr)
        {
            char* tmp = new char[m_length + 1];
            for (int i = 0; i < m_length; i++)
            {
                tmp[m_length - i - 1] = m_arr[i];
            }
            delete[] m_arr;
            tmp[m_length] = '\0';
            m_arr = tmp;
        }
    }

    void ltrim()
    {
        if (m_arr)
        {
            int spaceStartCount = 0;

            for (int i = 0; m_arr[i] == ' '; i++)
                spaceStartCount++;

            int newSize = m_length - spaceStartCount;

            char* tmp = new char[newSize + 1];
            for (int i = spaceStartCount, j = 0; i < m_length; j++, i++)
            {
                tmp[j] = m_arr[i];
            }
            delete[] m_arr;
            tmp[newSize] = '\0';
            m_length = newSize;

            m_arr = tmp;
        }
    }

    void rtrim()
    {
        if (m_arr)
        {
            int spaceEndCount = 0;
            for (int i = m_length - 1; m_arr[i] == ' '; i--)
                spaceEndCount++;

            int newSize = m_length - spaceEndCount;

            char* tmp = new char[newSize + 1];
            for (int i = 0; i < newSize; i++)
            {
                tmp[i] = m_arr[i];
            }
            delete[] m_arr;
            tmp[newSize] = '\0';
            m_length = newSize;
            m_arr = tmp;
        }
    }

    void trim()
    {
        if (m_arr)
        {
            ltrim();
            rtrim();
        }
    }

    void to_upper()
    {
        if (m_arr)
        {
            for (int i = 0; i < m_length; i++)
            {
                if (m_arr[i] >= 97 && m_arr[i] <= 122)
                {
                    m_arr[i] -= 32;
                }
            }
        }
    }

    void to_lower()
    {
        if (m_length)
        {
            for (int i = 0; i < m_length; i++)
            {
                if (m_arr[i] >= 65 && m_arr[i] <= 90)
                {
                    m_arr[i] += 32;
                }
            }
        }
    }

    void ucfirst()
    {
        if (m_length)
        {
            if (m_arr[0] >= 97 && m_arr[0] <= 122)
            {
                m_arr[0] -= 32;
            }
            for (int i = 1; i < m_length; i++)
            {
                if (m_arr[i] >= 65 && m_arr[i] <= 90)
                {
                    m_arr[i] += 32;
                }
            }
        }
    }

    void append(const char* source)
    {
        if (m_arr)
        {
            int sizeSource = strlen(source);
            int newSize = sizeSource + m_length + 1;
            char* tmp = new char[newSize + 1]{};
            strcpy(tmp, m_arr);
            strcat(tmp, " ");
            strcat(tmp, source);
            delete[] m_arr;
            m_length = newSize;
            m_arr = tmp;
        }
        else {
            cpy(source);
        }
    }



    void append(str& other)
    {
        append(other.m_arr);
    }

    char* substr(int star, int count)
    {


        if (star < 0)star = 0;

        if (count > m_length)count = m_length;


        int num;
        int newSize = count - star;
        char* tmp = new char[newSize + 1];
        for (int i = star, j = 0; j < newSize; j++, i++)
        {
            tmp[j] = m_arr[i];
        }

        tmp[newSize] = '\0';
        delete[] m_arr;
        m_arr = tmp;
        return m_arr;

    }




    bool starts_with(const char* source)
    {
        int sourceSize = strlen(source);
        for (int i = 0; i < sourceSize; i++)
        {
            if (m_arr[i] != source[i])
            {
                return false;
            }
        }
        return true;
    }

    bool starts_with(str& other)
    {
        append(other.m_arr);
    }

    void setLenght(int value)
    {
        m_length = value;
    }

    static int const NOT_VALUE = -1;
private:

    char* m_arr = nullptr;
    size_t m_length = 0;

    void cpy(const char* source)
    {
        m_length = strlen(source);
        m_arr = new char[m_length + 1];
        strcpy(m_arr, source);
    }
};


str substr(const char* words, int star, int count)
{
    str tmp(words);
    if (star < 0)star = 0;

    if (count > tmp.length())count = tmp.length();

    char* word = new char[tmp.length() + 1];

    strcpy(word, tmp.data());
    int num;
    int newSize = count - star;

    char* new_tmp = new char[newSize + 1];
    for (int i = star, j = 0; j < newSize; j++, i++)
    {
        new_tmp[j] = word[i];
    }

    new_tmp[newSize] = '\0';
    delete[] word;
    tmp.assign(new_tmp);
    return tmp;
}

int main()
{
    str a("Farid");
    str b("Farid");
    str c("F");

    std::cout << std::boolalpha;
         std::cout << "a.print() = ";
         a.print();
      
         std::cout << "a.ltrim() = ";
      	a.ltrim();
      	a.print();  
      
         std::cout << "a.rtrim() = ";
      	a.rtrim();
      	a.print();
      
         std::cout << "a.trim() = ";
      	a.trim();
         a.print();
      
      
         std::cout << "a.clear() = ";
      	a.clear() ;
         a.print();
      
      
         std::cout << "a.assign() = ";
      	a.assign("Abdullayev Farid");
         a.print();
      
      
      	
    
          std::cout << "a.front() = ";
    	   if (a.front()!=NULL)
          {
          std::cout << a.front();
          }
          else
          {
          std::cout << "Not DATA\n";
          }
          std::cout << "\n======================================\n\n";
      
      
         std::cout << "a.back() = ";
         if (a.back()!=NULL)
          {
              std::cout << a.back();
          }else
          {
              std::cout << "Not DATA\n";
          }
          std::cout<< "\n======================================\n\n";
      	
      
      
           std::cout << "a.find() = ";
           if (a.find('t')!=a.NOT_VALUE)
           {
               std::cout << a.find('t');
           }else
           {
               std::cout << "Not found\n";
           }
           std::cout << "\n======================================\n\n";
      
      	
      
           std::cout << "a.rfind() = ";
           if (a.rfind('f') ==a.NOT_VALUE)
           {
               std::cout << "Not found\n";
           }else
           {
               std::cout << a.rfind('d');
           }
      
           std::cout<<"\n======================================\n\n";
      
      
      	
         std::cout << "a.arrayStatus() = " << a.arrayStatus() ;
      
      
      
         std::cout << "a.reverse() = ";
      	a.reverse(); 
         a.print();
      
      
      
        std::cout << "a.to_upper() = "; a.to_upper();
        a.print();
      
      
      	
        std::cout << "a.to_lower() = ";
    	a.to_lower();
        a.print();
      	
      
         std::cout << "a.ucfirst() = "; a.ucfirst(); 
         a.print();
      
      
         std::cout << "a.append(c-string) = ";
         a.append("123");
         a.print();
      
         std::cout << "a.append(str) = "; a.append(b); 
         a.print();
         b.print();
      
         std::cout << "a.starts_with(c-string) = "<< a.starts_with(" Fa") ;
      	
      
         std::cout << "a.starts_with(str) = "<< a.starts_with(c.data()) ;
    
      
      
         std::cout << "a.substr(star,count)(c-string) = "<< a.substr(-100, 100) ;
      
      
      
      	std::cout << "a.substr(star,count)(str) = ";
      	 a.print();
          str one = substr("Azerbaycan", 4, 7); 
          one.print();


}









