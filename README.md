# Problem jedzących filozofów



## Instrukcja uruchomienia projektu

### Wymagania
- Standard C++ 20 lub wyższy
- Kompilator C++ (do kompilacji programu z plików źródłowych)
- (Opcjonalnie) IDE do modyfikacji i kompilacji projektu (zalecany CLion)

### Uruchomienie programu

#### GUI
Należy przejść do folderu `cmake-build-release` i uruchomić program `Projekt1.exe`. Program otrzymuje jako argument liczbę filozofów. 
Jeżeli żaden argument nie zostanie podany w przy uruchamianiu programu, 
użytkownik zostanie poproszony o podanie liczby filozofów w trakcie jego pracy.

#### CMD
Należy otworzyć okno konsoli / wiersza poleceń, a następnie przejść do lokalizacji w której znajduje się plik `Projekt1.exe`. 
W ramach polecenia wywołującego należy podać nazwę pliku oraz liczbę filozofów jako argument. Przykład wywołania poniżej:

```cmd
C:\\\{Path_to_file\}> Projekt1.exe 10 
```

## Opis problemu
Problem jedzących filozofów jest klasycznym zagadnieniem informatyki, 
pozwalajacym na zrozumienie wyzwań związanych z synchronizacją. 
Kilku (n) filozofów siedzi przy okrągłym stole, na którym znajduje się n widelców. 
Każdy filozof może korzystać tylko z widelca znajdującego się po jego lewej lub prawej stronie. 
Każdy filozof na zmianę myśli i je, ale żeby jeść, musi zdobyć oba widelce.

Problem ten wiąże się z wieloma wyzwaniami, takimi jak:
- unikanie deadlocków
- unikanie głodzenia (starvation) filozofów
- zapewnienie, że procesy współdzielone są zarządzane efektywnie.

W przyjętym rozwiązaniu skorzystano z propozycji Chandy/Misra.
Rozwiązanie to zakłada że na początku dla każdej pary filozofów tworzy się widelec i wręcza filozofowi o niższym ID. 
Widelce natomiast mogą przyjmować dwa stany - "czysty" oraz "brudny". Tworzone są one jako "brudne".
Nastepnie, gdy filozof chce uzyskać dostęp do zasobów, potrzebuje uzyskać widelec od sąsiadów. Gdy sąsiedni filozof otrzymuje żądanie, 
to jeśli jest w posiadaniu współdzielonego brudnego widelca - przekazuje go żądającemu.
Jeśli ów widelec jest czysty - zatrzymuje go. Po zakończeniu jedzenia filozof odkłada widelce i są oznaczone jako brudne. 
Jeśli podczas jedzenia przyszło żądanie od innego filozofa, to przekazuje mu widelec jako czysty.

Rozwiązanie to jest kompletnie rozproszone i nie wymaga centralnego zarządzania, a także pozwala na duży stopień współbieżności .

## Reprezentacja wątków

Każdy wątek reprezentuje filozofa, który na wykonuje w zapętleniu następujące akcje:
- myśli
- czeka na widelce (sukces oznacza zajęcie sekcji krytycznej)
- je
- oddaje widelce (zwolnienie sekcji krytycznej)

## Sekcje krytyczne i ich rozwiązanie

Sekcją krytyczną jest tutaj widelec, ponieważ tylko jeden filozof na raz może mieć do niego dostęp. 
Rozwiązano to za pomocą semafora binarnego, który blokuje innym filozofom dostęp do widelca, z którego korzysta dany filozof.
Ponadto, rozwiązanie Chandy/Misra wykorzystuje również zmienne pomocnicze w celu zarządzania przekazywaniem dostępu do sekcji krytycznej. 
Jako sekcje krytyczną ustanowiono również operację wypisywania w konsoli, w celu poprawy czytelności otrzymywanych wyników. 
Jest ona blokowana poprzez lock_guard z mutexem. 