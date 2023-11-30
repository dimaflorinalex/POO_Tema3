# Laborator POO - 2023/2024 - Tema 3
## Dima Florin-Alexandru - Grupa 262 - CTI, FMI Unibuc

Titlu: Calculator matrice rare

Descriere: Calculator de matrice rare cu numar restrans de operatii (suma, produs) si CLI

### Functiile aplicatiei:
0. Stinge calculatorul > Inchide aplicatia
1. Seteaza tipul de date folosit > Interpreteaza valorile din matrice ca int, double, unsigned char (uchar)
2. Suma a 2 matrice
3. Produsul a 2 matrice

- Exista protectie impotriva optiunilor invalide.

### Clase
1. Calculator - Wrapper pentru functiile ce tin de interfata calculatorului (navigatie, IO, operare date). Design patterns: Singleton, State
2. SparseMatrix, Direction, Value - Logica pentru matrice rara (stocare, parcurgere, adunare, inmultire etc)

- Observatie: Pentru date de tip "unsigned char" exista o specializare a functiei de atribuire valori in matrice - maparea valorilor in plaja 'a' - 'z'
