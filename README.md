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
			2.3. Вычисление арифметических выражений с помощью постфиксной формы.
			2.4. Реализация условного перехода if(if - else).
			2.5. Вычисление условных выражений с помощью постфиксной формы.
 
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
    5. Разработка пустых (add failure) версий модульных тестов для методов классов.
    6. Разработка тестов и кода.
    
# Список объектов #
  - Иерархический список
  - Аналитический модуль
  - Компилятор
  - Таблица - дерево поиска
  - Постфиксная форма
    - Условные выражения
    - Арифметические выражения
	
# Список основных алгоритмов #
  - Аналитический модуль
    - чтение текста из файла
    - синтаксический контроль
    - создание иерархического списка
  - Компилятор
    - выполнение программы
    - создание переменных
    - создание констант
    - выполнение функции Write
    - выполнение функции Read
    - вычисление арифметического выражения
    - вычисление условного выражения
	
# Описание моделей объектов #
  - Иерархический список - шаблонный класс реализации структуры данных иерархический список. структура содержит данные, стек погружения на нижние уровни
    - Операции:
      - ввод текста
      - перейти к следуещему звену
      - перейти на уровень ниже
      - перейти на уровень выше
      - прочитать текущее звено
      - вставка в подуровень
      - вставка на этом же уровне
      - присваивание перемещением
      
  - Аналитический модуль - класс реализующий просмотр и проверку текста и инициализацию иерархического списка. содержит данные, массив строк текста
    - Операции:
      - чтение текста из файла
      - синтаксический контроль
      - создание иерархического списка

  - Компилятор - класс реализующий последовательное выполнение программы. содержит данные, дерево констант типа double, дерево констант типа int, дерево переменных типа double, дерево переменных типа int, иерархический список
    - Операции:
      - выполнение программы
      - создание переменных
      - создание констант
      - выполнение функции Write
      - выполнение функции Read
      - вычисление арифметического выражения
      - вычисление условного выражения

  - Таблица (дерево поиска) - динамическая структура данных, сбалансированное по высоте двоичное дерево поиска, каждый элемент которого дополнительно содержит разницу высот поддеревьев, указатель на 2 следующих элемента(один указатель относится к элементу, который лексиграфичечки меньше этого, другой - к большему) и на 1 предыдущий. Первое поле всех записей таблицы является ключом. Структура хранения состоит из ключа, значения, где ключ - название переменной
    - Операции:
      - вставка
      - поиск
      - балансировка

  - Арифметическая постфиксная форма - класс вычисляющий арифметические выражения, приводя их к постфиксной форме
    - Операции:
      - создание
      - вычисление

  - Условная постфиксная форма - класс вычисляющий условные выражения, приводя их к постфиксной форме
    - Операции:
      - вычисление арифметических подвыражений
      - создание
      - вычисление
	  
# Описание основных алгоритмов #

  - Иерархический список
      - ввод текста - передаётся текст для заполнения списка, затем для каждой строки текста создаётся звено на высшем уровне, для каждой строки создаётся набор звеньев(слов из этой строки) на подуровне звена высшего, созданного для этой строки;
      - перейти к следуещему звену - переход к следующему звену текущего уровня, возвращает логическое значение описывающее произошел переход или нет;
      - перейти на уровень ниже - перейти на подуровень звена, возвращает логическое значение описывающее произошел переход или нет;
      - перейти на уровень выше - перейти на надуровень звена, возвращает логическое значение описывающее произошел переход или нет;
      - прочитать текущее звено - получить значение текущего звена;
      - вставка в подуровень - передаётся строка для вставки, затем создаётся звено в подуровне куда заноситься строка;
      - вставка на этом же уровне - передаётся строка для вставки, затем создаётся звено на этом же уровне куда заноситься строка;
      - присваивание перемещением - передача данных из одно иерархического списка в другой путём копирование указателя из старого объекта в новый и зануление указателя в старом объекте;

  - Аналитический модуль
    - чтение текста из файла - передается название файла содержащего текст кода Pascal--, затем массив строк заполняется строками из текста;
    - синтаксический контроль - проходя по массиву строк проверяется наличие: ( скобки для каждой ), begin для каждого end, then для каждого if, значения для констант, типа у переменных и констант, уникальности имён переменных и констант, переменные инициализованны перед использованием, открывающей " и закрывающей " для блока текста;
    - создание иерархического списка - массив строк передаётся для создания иерархического списка;

  - Компилятор
      - выполнение программы - передаётся иерархический список содержащий код программы на Pascal--, затем производится последовательный проход по списку и выполнение блоков программы: const - создание констант, var - создание переменных, begin-end - присваивание значений переменных, выполнение функции Write, выполнение функции Read, выполнение условного перехода if(if-else), вычисление арифметических выражений, вычисление условных выражений;
      - создание переменных - передаёться строка с инициализацией переменных, переменные заносятся в деревья переменных;
      - создание констант - передаёться строка с инициализацией констант, переменные заносятся в деревья констант;
      - выполнение функции Write - передаёться строка с функцией Write, функция интерпретируется для языка C++ и выполняется;
      - выполнение функции Read - передаёться строка с функцией Read, функция интерпретируется для языка C++ и выполняется;
      - вычисление арифметического выражения - передаёться подстрока содержащая арифметическое выражение целиком, затем выражение вычисляется с помощью арифметической постфиксной формы;
      - вычисление условного выражения - передаёться подстрока содержащая условное выражение целиком, затем выражение вычисляется с помощью условной постфиксной формы;

  - Таблица (дерево поиска)
      - вставка - передается запись, производится поиск вставляемой записи в таблице, в случае нахождения бросается ошибка, иначе вставляем по лексиграфическому порядку, затем пересчитываются разницы высот для всех родительских вершин, и производим балансировку при необходимостиева;
      - поиск - передается ключ, производится сравнение с корневым элементом, если меньше то идем по указателю на меньший элемент, если больше - на больший элемент. В случае равенства возвращается ссылка на значение. В случае ненахождения возвращается nullptr;
      - балансировка - http://www.itmm.unn.ru/files/2019/02/3.3.-Predstavlenie-tablits-s-ispolzovaniem-derevev-poiska.pptx (слайд 36 и далее)

  - Арифметическая постфиксная форма
      - создание - передаётся строка с инфиксной формой(перед этим в строке все переменные заменяются на их значения), затем создаётся постфиксная форма;
      - вычисление - вычисление постфиксной формы;

  - Условная постфиксная форма
      - вычисление арифметических подвыражений - передаётся строка с инфиксной формой, затем с помощью арифметической постфиксной формы вычисляется результат;
      - создание - передаётся строка с инфиксной формой(перед этим в строке все переменные заменяются на их значения), после этого происходит вычисление арифметических подвыражений(если они есть), затем создаётся постфиксная форма;
      - вычисление - вычисление постфиксной формы;