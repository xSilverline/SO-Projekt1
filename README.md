# Problem jedzących filozofów

## Instrukcja uruchomienia projektu

Przejdź do folderu `cmake-build-debug` i uruchom program `XD.exe`. Program otrzymuje jako argument liczbę filozofów.


```bash
XD.exe [n]
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

W przyjętym rozwiązaniu skorzystano z propozycji Chandy/Misra. [TODO]

## Reprezentacja wątków

Każdy wątek reprezentuje filozofa, który na zmianę myśli i je.

## Sekcje krytyczne i ich rozwiązanie

Sekcją krytyczną jest tutaj widelec, ponieważ tylko jeden filozof na raz może mieć do niego dostęp. 
Rozwiązano to za pomocą semafora binarnego, który blokuje innym filozofom dostęp do widelca, z którego korzysta dany filozof.
