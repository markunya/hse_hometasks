# Zip

Реализуйте шаблонную версию функции `Zip`, аналогичную функции `zip` в языке Python.

Функция `Zip` принимает на вход две последовательности и возвращает последовательность пар, где i-я пара состоит из i-х элементов первой и второй последовательности.
Выходная последовательность должна быть равной по длине меньшей из входных последовательностей.

Вы можете использовать функции `std::begin()` и `std::end()`,
чтобы получить итераторы начала и конца этих последовательностей.

## Реализация

Реализация должна быть однопроходной. Результирующие пары должны генерироваться на лету при разыменовании
итератора без предварительного накопления в памяти. Аллокация динамической памяти запрещена.