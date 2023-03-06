// Copyright 314CC Miron Andreea Cristiana

Structuri de date si algoritmi

Tema #3
Grafuri

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	Initial, se citesc primele date despre graf si se creeaza graful g de 
tip structura GrafP, ce retine n(nr. de varfuri), m(nr. de muchii) si 
c(matricea de costuri). Odata cu citirea muchiilor impreuna cu costul lor, se
formeaza si matricea de costuri.
	Se citesc si nodurile ce reprezinta depozitele, fiind salvate intr-un
vector de int, deposits.
	De asemenea, se citeste de la tastatura si numarul de taskuri, ceea
ce inseamna ca se vor executa nr_task-uri de ori task-uri. Odata cu citirea 
unui task, se identifica task-ul si se apeleaza functia asociata, ce are 
programul intr-un alt fisier .c pentru o vizualizare mai clara a codului.
	Asociere task - functie este urmatoarea:
	- task 1 - e1
	- task 2 - e2
	- task 3 - e3
	La final se elibereaza memoria pentru matricea de costuri, graf si 
vectorul de depozite. 

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Task #1 

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	In variabilele s vom memora depozitul din care se incarca marfa, 
respectiv in k numarul de magazine ce vor fi aprovizionate. Pentru fiecare
magazin dorim sa aflam costul minim de dus si de intors. Pentru rezolvarea 
acestui task, am considerat algoritmul dijkstra cel mai potrivit. Astfel,
in vectorul p vom retine drumul pentru costul minim in urma unui apel la
functia dijkstra. Pentru ca intai de toate trebuie sa afisam cele doua costuri,
vom apela initial dijkstra pentru drumul de intoarcere pentru a salva costul,
apoi dijkstra pentru drumul de dus. Aceste valori pot fi afisate. Deoarece in
vectorul p este memorat traseul de dus, o vom afisa prin apelarea functiei 
print_road. Pentru drumul de intoarcere vom apela dijkstra din nou, iar apoi
afisam din nou traseul salvat din p. Cele doua valori de cost minim al 
traseelor de dus si intors se adauga la o varibila sum, ce va fi afisata la
finalizarea tuturor traseelor, reprezentand costul total.

	Functia dijkstra este putin modificata fata de cea obisnuita, singura
diferenta fiind reprezentata de oprirea algoritmului in momentul in care am
aflat distanta minima pana la un nod final dorit, distanta minima pentru
celelalte noduri fiind irelevanta in acest task. In cadrul functiei se aloca
memorie pentru un vector de distante minime d si un vector s ce marcheaza
nodurile pentru care s-a aflat distanta minima. Se initializeaza vectorii p si
d, se marcheaza nodul sursa si se calculeaza distantele minime pentru fiecare 
nod. Daca tocmai s-a aflat distanta minima pentru nodul dorit, atunci se 
incheie din a cauta alte distante minime si functia se incheie.

	Pentru afişarea vârfurilor de pe un drum minim in cadrul functiei 
print_road, trebuie parcurs în sens invers vectorului p (de la ultimul element 
la primul).

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Task #2 

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	Pentru rezolvarea acestui task trebuie sa aflam componentele conexe cu
componenta lor.
	In cadrul functiei e2, alocam initial memorie pentru un vector de 
indici de componente tari conexe(fr). Parcurgem nodurile, iar pentru fiecare 
nod verificam daca nu face parte dintr-o componenta conexa si daca nu este 
depozit. Daca conditia se indeplineste, atunci s-a mai gasit o componenta tare 
conexa si vom afla si ce noduri o constituie prin marcarea lor in vectorul fr. 
Pentru marcarea lor vom face 2 parcurgeri in arbori, una in directia normala
a arcelor si alta in directia opusa arcelor, prin apelarea functiilor DFS_nor
si DFS_inv. Inainte de apelari alocam memorie pentru un vector de vizite. 
Daca dupa parcurgeri, un nod are marcat cu 2 in vectorul de vizite, atunci se
marcheaza in vectorul fr cu indicele componentei actuale. 
	Dupa ce s-au gasit toate componentele, se afiseaza numarul lor, urmata
de afisarea efectiva a componentelor lor prin parcurgerea componentelor si 
verificarii care noduri se afla in compenentul actual cautat.

	Verificarea daca un nod este depozit(mentionat mai sus ca se face o 
astfel de verificare) se face prin apelarea functiei is_depozit, ce cauta in
vectorul de depozite daca nodul cautat se afla printre ele.

	Functiile DFS_nor si DFS_inv reprezeinta parcurgerea in adancime a 
grafului.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Task #3 

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	In cadrul functiei e3 se citeste numarul de zone in variabila r.
	Pentru fiecare zona se creeaza un vector zone ce reprez. marcarea 
nodurilor ce fac parte din zona curenta, care se citeste de la tastatura. In
variabila dmin vrem sa memoram costul minim al traseului din zona respectiva.
Pentru aflarea lui, vom verifica toate traseele care pleaca din diferite 
depozite, iar traseul cu cost minim este va fi salvat in dmin. Cand aflam
costul minim pentru o plecare dintr-un depozit, se initializeaza o coada q
de tip queue si se adauga nodul de plecare, adica depozitul. Datele esentiale,
pentru un element de coada sunt:
	- x : indicele nodului
	- sum : costul pana in punctul actual al tradeului
	- stare : vectorul de vizite
	- traseu : daca nodul se afla in traseul verificat in acel moment
	Pentru aflarea costului minim se apeleaza functia BFS, in care printre
parametri se afla graful g, coada q, pozitia actuala, nodul de plecare si 
vectorul zone.
	Se elibereaza memorie pentru tot ce a fost alocat, iar pentru fiecare 
zona se afiseaza costul minim al traseului din acea zona.

	In cadrul functiei BFS se scoate un element din coada si se verifica daca
s-a ajuns la finalul traseului. Daca da, se compara cu costul minim actual. Daca
nu, se continua parcurgerea. Se ia in considerare fiecare vecin si se creeaza o
stare actuala pentru acel vecin. Pentru a verifica daca se poate continua
drumul pe acel vecin trebuiesc indeplinite urmatoarele conditii:
	- nu s-a depasit costul minim
	- exista muchie
	- vecinul face parte din zona dorita
	- daca n-a mai existat ulterior pe traseu cu aceias stare
	Daca conditiile se indeplinesc, atunci vecinul se adauga in coada cu
datele lui esentiale si se apeleaza iar functia BFS.
	
	In cadrul functiei BFS au fost folosite 2 functii:
	-is_equal : pentru a verifica daca 2 vectori sunt identici
	-copy : copiaza datele dintr-un vector in altul

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
