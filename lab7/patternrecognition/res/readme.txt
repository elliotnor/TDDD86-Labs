/**********************************************************************
 *  M�nsterigenk�nning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga k�rtider i sekunder
 *  analys      n�r det k�nns vettigt att v�nta p� hela ber�kningen.
 *              Ge uppskattningar av k�rtiden i �vriga fall.
 *
 **********************************************************************/
    
      N       brute       sortering
 ----------------------------------
    150      32 ms           9 ms
    200      99 ms           55 ms
    300      246 ms          84 ms
    400      592 ms          86 ms
    800      4828 ms         313 ms
   1600      38306 ms        1160 ms
   3200      295376* ms       4493 ms
   6400      2353008* ms      18336 ms
  12800      18700000* ms     77145 ms

* = Teoretisk beräkning. I verkligheten kraschar programmet.

/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck f�r v�rstafallstiden f�r programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute:    O(N⁴)

Sortering: O((N^2)*log(n))
