# JIMP_LMP8

Grzegorz Jewusiak i Filip Majewski

### Kompilacja

Nalezy skompilować program do analizatora leksykalnego tak: `make alex`

Zaś tester funkcji do stosów: `make funstack`

### Wywołanie

Do analizatora leksykalnego należy podać jako argumenty wszystkie pliki analiozwanych programów, np:

`alex-w fx/p.c fx/fa.c`

### Tester stosu

Wywołanie: `funstack-w`

Kolejne rzeczy które testuje tester:

1. Kładzie na stos dwie funkcje
2. Zwraca poziom stosu
3. Zwraca funkcję na górze stosu oraz usuwa element
4. Zwraca poziom stosu
5. Zwraca funkcję na górze stosu oraz usuwa element
6. Zwraca poziom stosu (zerowy, gdyż stos jest pusty)
7. Próbuje pobrać funkcję z góry stosu i ją usunąć, ale stos jest pusty. W tym momencie zwracany jest kod błędu 50,
   świadczący o poprawności działania kodu.

Tester nie powinien zwrócić kodu "0" gdyż stos ma jedynie 2 elementy, a próbujemy w testerze usunąć 3.
