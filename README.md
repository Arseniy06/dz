# Строковый калькулятор на языке C++
## Требования
По запросу с клавиатуры в консольном приложении вводится строка, которая может содержать: знаки операций +, -, *, /; константы (целые или вещественные). Строка задает некоторое правильное математическое выражение (формулу в инфиксной форме), программа вычисляет значение, выдает результат. В формуле дополнительно использовать скобки () для задания приоритета операций, имена функций sin, cos, tg, ctg, exp, переменную x, а также проверку правильности введенного выражения, в случае ошибок ввода выдавать сообщения об ошибках.
## Принцип работы
Калькулятор работает, проверяя корректность входной строки и переводя ее в обратную польскую нотацию, затем помещает все операции в стек и производит вычисления.
