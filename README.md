This is a Uni project using RTOS POSIX stadnards. 
Overall project specifications below:
PL
Projekt 1
Napisz bibliotekę dostarczającą systemu logowania do plików stanu aplikacji sterowanego sygnałami.
System logowania powinien spełniać następujące założenia:
• powinien być sterowany sygnałami czasu rzeczywistego i wykorzystywać przenoszone z nimi
dane;
• obsługa sygnałów powinna być realizowana przez kod wykonywany asynchronicznie;
• jeden z sygnałów sterujących powinien umożliwiać zapis do oddzielnego pliku aktualnego
stanu wewnętrznego aplikacji (dump), zawartość pliku powinna być zależna od aplikacji i w
niej konfigurowalna, każde wystąpienie sygnału powinno generować oddzielny plik;
• drugi z sygnałów powinien włączać/wyłączać logowanie zdarzeń do pliku logowania (log);
• powinna istnieć też możliwość przełączenia poziomu szczegółowości logowania (trzy
poziomy: MIN, STANDARD, MAX);
• funkcja zapisująca wiadomość do pliku logowania powinna przyjmować jako argument jego
istotność, decyzja o zapisie komunikatu lub jego zaniechaniu powinna być podejmowana na
podstawie porównania jego istotności z aktualnym poziomem szczegółowości;
• biblioteka musi działać prawidłowo w aplikacjach wielowątkowych;
• aplikacja powinna być zgodna ze standardami POSIX i języka C.

EN
Project 1
Write a library providing a signal-controlled logging system for application state files.  

The logging system should meet the following requirements:  
- It should be controlled by real-time signals and utilize the data carried with them.  
- Signal handling should be performed by asynchronously executed code.  
- One of the control signals should enable saving the current internal state of the application (dump) to a separate file. The file's content should be configurable within the application, and each signal occurrence should generate a separate file.  
- Another signal should toggle event logging to the log file on or off.  
- There should also be an option to switch the logging verbosity level (three levels: MIN, STANDARD, MAX).  
- The function responsible for writing messages to the log file should accept their importance as an argument. The decision to log or discard a message should be based on comparing its importance to the current verbosity level.  
- The library must function correctly in multithreaded applications.  
- The application should comply with POSIX standards and be written in C.
