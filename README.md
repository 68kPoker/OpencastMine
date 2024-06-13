# OpencastMine

### Instalacja:

## Wersja CPLEX:
Zaimportować pliki z folderu CPlex version do projektu OPL w CPLEX, i uruchomić

## Wersja Python:
Wymaga Python 3.10. oraz pakietu docplex. Należy uruchomić plik z folderu Python version z wiersza poleceń lub IDE

## Wersja C++:
Wymaga Visual Studio 2022 oraz CPLEX, po pobraniu repozytorium należy uruchomić solucję (plik .sln), po czym przestawić tryb budowania na Release. 
W przypadku korzystania z wersji innej niż 2211 (inny numer wersji lub wersja Community) lub innej lokalizacji instalacji CPLEX niż standardowa, należy we właściwościach projektu w Visual Studio zmodyfikować w sekcji Katalog VC++ ścieżki dla zewnętrznych katalogów dyrektyw include oraz katalogów bibliotek, tak aby ścieżka odpowiadała faktycznej lokalizacji odpowiednich katalogów na dysku.

## Zadanie
Zadanie do rozwiązania przez model dotyczyło uproszczonego modelu kopalnii odkrywkowej. Jest ona reprezentowana jako odwrócona piramida, składająca się z bloków o różnej wartości. Wydobycie bloku na danym poziomie kosztuje określoną kwotę pieniędzy, jednakowoż, aby dostać się do bloków na niższych warstwach należy wydobyć wszystkie bloki go zakrywające - na jednym bloku poziomu n+1 znajduje się cztery bloki poziomu n (n+1 jest głębiej niż n). Bloki poziomu n mogą znajdować się jednocześnie na jednym, dwóch lub czterech blokach pozimou n+1, zależnie od ich położenia.
Celem zadania jest wyznaczenie optymalnych bloków do wykopania, aby zmaksymalizować zyski.

## Wyniki
Wynikiem działania modelu jest optymalny zysk z wykopania bloków z zadanej kopalnii, oraz oznaczenie bloków, które powinny być wykopane.
Bloki są oznaczone względem konkretnej warstwy licząc od 0, w związku z czym najgłębszy z bloków jest określany jako W_[najgłębszy_poziom]_0_0

Uwaga: Wersja Python informuje tylko o blokach, które powinny zostać wydobyte.
Po uruchomieniu wersji C++ w katalogu projektu pojawi się plik z informacją o wszystkich blokach, czy powinny być wydobyte, czy też nie.
