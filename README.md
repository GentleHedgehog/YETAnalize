# YETAnalize
### Environment 
The program was written using Qt (5.7.0, MinGW 5.3.0 x32). Testing was performed on Windows 7 x64, Windows 10 x64

*.pro file notes:
#DEFINES += LANG_EN - uncomment this line to switch to the English interface

***

Analize of YET (Russian abbreviation) (conditional unit of labor intensity of the worker). Calculates its sum.

### Work with program
You can put text in the input line:

CODE_TYPE CODE1 CODE2*2 CODE3..  CODE_TYPE2 CODE1 CODE2 CODE3 ...

At the moment, each code is tied to a YET number inside the program code. 
In the future, you can do this from a separate file to upload. 
The program accepts codes separated by commas or spaces. 
Unknown codes are displayed in the corresponding window. 
Codes with a multiplier are processed correctly and their value is multiplied by the multiplier.

***

Анализ УЕТ. 
Рассчитывает сумму УЕТ (условная единица трудоёмкости работника) по введенной строке кодов УЕТ. 

### Работа с программой

В строку ввода можно поместить текст вида: 

ТИП_КОДА КОД1 КОД2*2 КОД3   ТИП_КОДА2 КОД1 КОД2 ...

На данный момент к каждому коду привязано число УЕТ внутри кода программы. 
В дальнейшем можно это вынести в отдельный файл для подгрузки.
Программа принимает коды, разделенные запятыми или пробелами. 
Неизвестные коды выводятся в соответствующем окне. 
Коды с множителем обрабатываются правильно и их значение в результате умножается на множитель.
