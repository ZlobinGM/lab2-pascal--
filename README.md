# Лабораторная работа №2
Лабораторная работа "Среда исполнения программ на языке Pascal--"

# Постановка задачи #
- Разработать интегрированную среду разработки для программ на языке Pascal--.
- Среда должна обеспечивать возможность написания и выполнения программ.
- Работа с кодом программы на языке Pascal--:
    1. Синтаксический контроль корректности текста программы.
    2. Создание иерархического списка хранящего текст программы.
- Работа с иерархическим списком хранящим текст программы.
    1. Хранение переменных и констант в дереве поиска.
    2. Выполнение кода программы в блоке begin - end.
    	2.1. Присваивание значений переменным.
    	2.2. Выполнение функций Write, Read.
    	2.2. Вычисление арифметических выражений с помощью постфиксной формы
    	2.3. Реализация условного перехода if(if - else).
    	2.3. Вычисление условных выражений с помощью постфиксной формы
 
# Сроки выполнения #
	Начало - 27 марта 2020
	Окончание - 22 мая 2020
    
# Требования #
- Программная система должна обеспечивать выполнение следующих функций:
    1. Должен выполняться синтаксический контроль корректности текста программы.
    2. Условные операторы м.б. вложенными.
    3. Текст программы должен храниться в виде иерархического списка.
    4. Переменные и константы должны храниться в таблице - на выбор: упорядоченная, дерево поиска, хеш-таблица.
    5. Вычисление арифметических и условных выражений должно выполняться с помощью постфиксной формы.

- Программная система разрабатывается в Microsoft Visual Studio 2019

# Разработка #
- Этапы разработки
    1. Анализирование предметной области, выделить объекты и наиболее важные алгоритмы.
    2. Описание модели выделенных объектов.
    3. Подготовка проекта программной системы.
    4. Заготовка классов в h-файле.
    5. Заготовка форм.
    6. Разработка пустых (add failure) версий модульных тестов для методов классов.
    7. Разработка тестов и кода.