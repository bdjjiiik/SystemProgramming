### Задача 3.11
Запустите docker-контейнер и поэкспериментируйте с максимальным лимитом ресурсов
открытых файлов. Для этого выполните команды в указаннном порядке:
```
$ ulimit -n
$ ulimit -aS |grep "open files"
$ ulimit -aH |grep "open files"
$ ulimit -n 3000
$ ulimit -aS |grep "open files"
$ ulimit -aH |grep "open files"
$ ulimit -n 3001
$ ulimit -n 2000
$ ulimit -n
$ ulimit -aS |grep "open files"
$ ulimit -aH |grep "open files"
$ ulimit -n 3000
```
В качестве следующего упражнения проделайте перечисленные команды с root
правами.

### Задача 3.2
В docker-контейнере установите утилиту perf(1). Поэкспериментируйте с достижением
процессом установленного лимита.

### Задача 3.3
Напишите программу, имитирующую бросание шестигранной кости. Имитируйте броски.
Результаты записывайте в файл, для которого предварительно установите ограничения
на его максимальный размер (max file size). Корректно обработайте ситуацию
возникновения превышения лимита.

### Задача 3.4
Напишите программу, имитирующую лотереи, выбрав 7 различных целых чисел в
диапазоне от 1 до 49, и еще 6 из 36. Установите ограничение на время ЦП (max CPU
time) и генерируйте результаты выбора чисел (7 из 49, 6 из 36). Обработайте ситуацию,
когда лимит ресурса будет исчерпан.

### Задача 3. 5
Напишите программу для копирования одного именованного файла в другой
именованный файл. Два имени файла указываются в качестве первых двух аргументов
программы.
Скопируйте файл по блокам (512 байт) за раз. Установите ограничения на размер файла.
Проверьте:
    - что программа имеет два аргумента, или напечатайте «Program need two
arguments»;
    - что первый файл (первое имя файла) доступен для чтения, или напечатайте
«Cannot open file .... for reading»;
    - что второй файл доступен для записи, или напечатайте «Cannot open file .... for
writing";
    - что установленные ограниячения на размер файла работают правильно.
Обработайте в коде программы возникновение такой ситуации.

### Задача 3.6
Напишите программу, демонстрирующую использование установленного ограничения
(max stack segment size). Подсказка: рекурсивная программа активно использует
стек. 