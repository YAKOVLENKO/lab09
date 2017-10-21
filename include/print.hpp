#include <string>
#include <fstream>
#include <iostream>
/*!
	\brief Функция копирования

        \code
                void print(const std::string& text, std::ostream& out = std::cout);
        \endcode

	Функция потокового вывода

	\param[in] text Копируемая строка
	\param[out] out Вывод строки
	
	
*/
void print(const std::string& text, std::ostream& out = std::cout);
/*!
	 \brief Функция копирования

        \code
               void print(const std::string& text, std::ofstream& out);
        \endcode

	Функция вывода в файл

        \param[in] text Копируемая строка
        \param[out] out Вывод строки 

*/
void print(const std::string& text, std::ofstream& out);
