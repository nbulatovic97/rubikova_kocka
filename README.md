# rubikova_kocka

Projekat RG

Pre pokretanja:


Za pokretanje je potrebno instalirati biblioteku ---Eigen--- koja je koriscena u izradi projekta(takodje i biblioteke za opengl).
Eigen se moze preuzeti i instalirati potpuno standardno kao i svaka biblioteka koja se preuzme zatim instalira.(npr NuGet Eigen oprija za korisnike Microsoft MS ili pomocu komande sudo apt install libeigen3-dev za linux)
Takodje se moze i samo linkovati kod posto je biblioteka Eigen header only, pa se ne mora ni instalirati.


Nakon pokretanja:


Prilikom pokretanja programa kamera gleda u "pocetni deo" gde se nalazi spisak komadi za igru i 2 dugmeta "Iskljuci" i "pokreni"
klikom na "iskljuci" gasi se program
klikom na "pokreni" pogled se pomera u desno ka vec iscrtanoj kocki

*na pocetku, kocka je sklozena*

zadrzavanjem levog klika mozemo rotirati pogled oko kocke i gledati je sa bilo koje strane

Komande za rotaciju(Z X C V B N) nalaze se i na pocetnoj strani i sluze za rotaciju kocke(prednja zadnja gornja donja leva i desna rotacija)
***funkcija dugmica je obrnuta ukoliko je upaljen CAPSLOCK ili zadrzimo shift*
dakle Z i z rade rotaciju istog dela kocke ali u suprotnom smeru

Klikom na dugme R, radi se nasumican potez, zadrzavanjem dugmeta R postizemo mesanje kocke koju kasnije mozemo slagati

Kocka je postavljena na 3x3,
kako je korisceno "#define kocka 3" moguce je promeniti velicinu kocke na bilo koji broj medjutim samo vrednosti 2 i 3 imaju punu funkcionalnost
Za ostale vrednosti samo ce se iscrtati kocka ali bez mogucnosti da se resi pa nije suvise funkcionalna

ispod kocke nalaze se 2 dugmeta, jedno za vracanje na pocetnu ukoliko zelimo videti komande ponovo, drugo za ispisivanje koraka kojim dolazimo do resenja prateci korake 
sa leva na desno

za pronalazak resenja koriscen je neki vid bfs algoritma koji u slucajevima kada je kocka suvise izmesana zahteva ogromnu kolicinu vremena pa program moze da zakoci 
ali za neku osnovnu primenu radi dovoljno dobro

takodje boje pozadine kao i brzina prelaza iz jedne u drugu boju, mogu se menjati u kodu
