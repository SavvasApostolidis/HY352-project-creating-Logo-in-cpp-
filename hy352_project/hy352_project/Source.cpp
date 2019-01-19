#include "./LOGO.h"
#ifdef APPLE
#include <allegro5/allegro.h>
#endif

TO test WITH lala FSTART //allazei th timh tou list prwtou item apo hello se 3
SHOW : ARG(NUMBER : 1)
	SHOW : ITEM({ NUMBER:2 }, lala)
	MAKE x = ARG(NUMBER : 1)
	SHOW : x
	SETITEM({ NUMBER:1 }, lala, NUMBER:3)
	FEND


	//DISCLAIMER,EXOUME AFISEI POLLES COMMENT OUT ENTOLES GIATI TO UNCOMMENT MIAS MPOREI NA KANEI MIA ALLH ENTOLH INVALID,OMWS ESTW SAS PAREXOYME ETSI ENA PARADEIGMATAKI GIA KA8E FEATURE
	//UNCOMMENT WISELY
	//merika if den einai sth macro morfh,htan tote pou testarame tous operator == an leitourgoun gia grhgorada
	START_PROGRAM

	MAKE hello = WORD: "hello"
	MAKE number = NUMBER : 50
	MAKE number2 = NUMBER : 30
	MAKE list = LIST[hello, ARRAY{number,number2}]
	MAKE list2 = LIST[hello, ARRAY{ number,number2}]
	//MAKE a = WORD:"a"
	//MAKE b = WORD:"b"
	//MAKE sentence = SENTENCE(WORD:"HI", WORD:"KAPPA")
	MAKE tmp = ARRAY{ number,list }
	MAKE tmp2 = ARRAY{ number,list2 }
	MAKE x = ARRAY{ number,tmp}
	MAKE x2 = ARRAY{ number,tmp2}
	//MAKE x3 = x
	//MAKE please = LIST[hello, number, ARRAY{ number,x }]
	//FOREACH list DO
	//SHOW: ELEM
	//SETITEM({NUMBER:1},list2,ELEM)
	//END
	//FOREACH list2 DO
	//SHOW : ELEM
	//END
	//SHOW :ITEM({ NUMBER:1 }, x)
	//FORWARD number
	SETXY number, number2
	////expression  number, number2
	CALL test(list) //printarei thn alagmenh timh
	FOREACH list DO
	SHOW : ELEM
	END
	////MAKE x3 = ARRAY{}
	////SETITEM({ NUMBER:1 }, x, list)
	//SUM((NUMBER : 12), ITEM({ NUMBER:2,NUMBER : 2 }, x),number)
	////ITEM({NUMBER:3,NUMBER:2},x2).print()
	////v.print()
	//MAKE xminus = myminus(ITEM({NUMBER:1},x))
	//xminus.print()
	//MAKE numberquot = myquot(number2,number)
	//numberquot.print()
	//MAKE numberproduct = myproduct(number2, number)
	//numberproduct.print()
	if ( (x == x2)) { cout << "yes" << endl; }
	//IF(x != x2) DO cout << "yes2" << endl; END
	//MAKE fal = BOOLEAN:false
	//IF  AND(number == (NUMBER:4), list2 == list, ITEM({ NUMBER:1 }, x) == ITEM({NUMBER:1},x))DO
	//cout << "please me th prwth" << endl
	//ELIF number == 2 DO
	//cout << "will miracles happen" << endl
	//END



	//
	//SETITEM({ (NUMBER:2) }, x, DIFFERENCE(number, (NUMBER: 1)))
	//ITEM({ NUMBER:2 }, x).print()
	//CALL test(please)




	//
	//REPEAT NUMBER : 5 TIMES
	//DO
	//REPCOUNT // number of the current iteration
	//MAKE testnumber = REPCOUNT
	//SHOW:testnumber
	//FORWARD(NUMBER : 100)// move turtle 100 steps
	//RIGHT(NUMBER : 90) // turtle turns right 90 degrees
	//END


	REPEAT WHILE number > (NUMBER:47)
	DO
	REPCOUNT // number of the current iteration
	MAKE testnumber = REPCOUNT
	SHOW : testnumber
	ASSIGN number = DIFFERENCE(number,REPCOUNT)
	END


REPEAT 2 TIMES
DO
cout << endl
SHOW : REPCOUNT

	REPEAT 5 TIMES
	DO
		SHOW : REPCOUNT
	END
cout << endl
END

//REPEAT WHILE number > 48
//DO
//SHOW: REPCOUNT
//cout << endl
//	ASSIGN number = DIFFERENCE(number, NUMBER:1)
//	REPEAT NUMBER : 5 TIMES
//		DO
//		SHOW : REPCOUNT
//		END
//END

MAKE turtleMoves = LIST[
	    ARRAY{ (WORD:"FORWARD"), (NUMBER: 100) },
		ARRAY{ (WORD:"RIGHT"), (NUMBER: 90) },
		ARRAY{ (WORD:"FORWARD"), (NUMBER: 100) },
		ARRAY{ (WORD:"RIGHT"), (NUMBER: 90) },
		ARRAY{ (WORD:"FORWARD"), (NUMBER: 100) },
		ARRAY{ (WORD: "LEFT"), (NUMBER: 90) },
		ARRAY{ (WORD: "FORWARD"), (NUMBER: 100) },
		ARRAY{ (WORD: "LEFT"), (NUMBER: 90) }];
CENTER
REPEAT 2 TIMES
DO
FOREACH turtleMoves DO
IF ITEM({ (NUMBER: 1) }, ELEM) == (WORD: "FORWARD") DO
FORWARD ITEM({ (NUMBER: 2) }, ELEM)
ELIF ITEM({ (NUMBER: 1) }, ELEM) == (WORD: "BACK") DO
BACK ITEM({ (NUMBER: 2) }, ELEM)
ELIF ITEM({ (NUMBER: 1) }, ELEM) == (WORD: "LEFT") DO
LEFT ITEM({ (NUMBER: 2) }, ELEM)
ELSE
RIGHT ITEM({ (NUMBER: 2) }, ELEM)
END
END
END
PENUP
CENTER
RIGHT(NUMBER: 90)
FORWARD(NUMBER: 150)
PENDOWN
REPEAT(NUMBER: 360) TIMES DO
FORWARD(NUMBER: 2)
RIGHT(NUMBER: 1)
END



END_PROGRAM
